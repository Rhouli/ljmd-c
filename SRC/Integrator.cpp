/**
 * Integrator
 *
 * @short This class provides integration methods and allows to calculate kinetic energies, velocities and performs cell updates of the MD system.
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */

#include "Integrator.h"

const double kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */
const double cellrat=2.0;             /* ratio between cutoff radius and length of a cell */
const int cellfreq=4;                 /* number of MD steps between cell list updates */


/**
 * Default constructor
 */
Integrator::Integrator() :
    m_atom(NULL),
    m_force(NULL),
    m_timestep(0),
    m_ngrid(0),
    m_nidx(0),
    m_delta(0)
{};

/**
 * Default destructor
 */
Integrator::~Integrator()
{
    //Release memory
    if(m_atom)  delete m_atom;
    if(m_force) delete m_force;
};

/**
 * Init
 */
bool Integrator::Init(Atoms *atom, Force *force)
{
    //Set pointers
    if(!atom) {
        std::cerr << "( ERROR ) Atoms null pointer... Abort Init!" << std::endl; 
        return false;
    }
    else this->m_atom = atom;
    
    if(!force) {  
        std::cerr << "( ERROR ) Force null pointer... Abort Init!" << std::endl; 
        return false;
    }
    else this->m_force = force;

    //No error
    return true;
};//Init


/**
 * Calculate Kinetic Energy
 */
bool Integrator::CalcKinEnergy() 
{
    int i=0;
    double ekin=0.0, temp=0.0;

    for (i=0; i< (3 * this->m_atom->GetNAtoms()); ++i) {
        ekin += this->m_atom->GetVelocity(i) * this->m_atom->GetVelocity(i);
    }

    ekin *= 0.5 * mvsq2e * this->m_atom->GetMass();
    this->m_atom->SetKinEnergy(ekin);

    temp = 2.0 * ekin / (3.0 * this->m_atom->GetNAtoms() - 3.0) / kboltz;
    this->m_atom->SetTemp(temp);

    //No error
    return true;
};


/**
 * Calculate Velocity
 */
bool Integrator::CalcVelocity()
{
    int i;
    double dtmf;
    dtmf = 0.5 * this->m_timestep / mvsq2e / this->m_atom->GetMass();

    /* first part: propagate velocities by half and positions by full step */
    for (i=0; i< (3 * this->m_atom->GetNAtoms()); ++i) {
      this->m_atom->SetVelocity(i, this->m_atom->GetVelocity(i)+dtmf * this->m_atom->GetForce(i));
      this->m_atom->SetPosition(i, this->m_atom->GetPosition(i)+ this->m_timestep * this->m_atom->GetVelocity(i));
    }

    /* compute forces and potential energy */
    this->m_force->ComputeForce(this->m_atom);

    /* second part: propagate velocities by another half step */
    for (i=0; i< (3 * this->m_atom->GetNAtoms()); ++i) {
      this->m_atom->SetVelocity(i, this->m_atom->GetVelocity(i)+dtmf * this->m_atom->GetForce(i));
    }

    //No error
    return true;
};


/**
 * Update cells
 */
bool Integrator::UpdateCells()
{
    int i, ngrid, ncell, npair, midx, natoms;
    double delta, boxby2, boxoffs;
    boxby2 = 0.5 * this->m_atom->GetBoxSize();
    natoms = this->m_atom->GetNAtoms();
        
    if (this->m_atom->GetNCells()>=0) { //orig: sys->clist == NULL
        int nidx;
        
        ngrid  = floor(cellrat * this->m_atom->GetBoxSize() / this->m_atom->GetRadCut());
        ncell  = ngrid*ngrid*ngrid;
        delta  = this->m_atom->GetBoxSize() / ngrid;
        boxoffs= boxby2 - 0.5*delta;
       
        this->SetDelta(delta);
        this->SetNGrid(ngrid);
        nidx = this->m_atom->SetNCells(ncell); /* In addition, allocates cell list storage and
                                                 allocate index lists within cell. cell density < 2x avg. density */
        this->m_nidx = nidx;

        /* build cell pair list, assuming newtons 3rd law. */
        npair = 0;
        for (i=0; i < ncell-1; ++i) {
            int j,k;
            double x1,y1,z1;
            
            k  = i/ngrid/ngrid;
            x1 = k*delta - boxoffs;
            y1 = ((i-(k*ngrid*ngrid))/ngrid)*delta - boxoffs;
            z1 = (i % ngrid)*delta - boxoffs;

            for (j=i+1; j<ncell; ++j) {
                double x2,y2,z2,rx,ry,rz;
                
                k  = j/ngrid/ngrid;
                x2 = k*delta - boxoffs;
                y2 = ((j-(k*ngrid*ngrid))/ngrid)*delta - boxoffs;
                z2 = (j % ngrid)*delta - boxoffs;

                rx=pbc(x1 - x2, boxby2, this->m_atom->GetBoxSize());
                ry=pbc(y1 - y2, boxby2, this->m_atom->GetBoxSize());
                rz=pbc(z1 - z2, boxby2, this->m_atom->GetBoxSize());

                /* check for cells on a line that are too far apart */
                if (fabs(rx) > this->m_atom->GetRadCut() + delta) continue;
                if (fabs(ry) > this->m_atom->GetRadCut() + delta) continue;
                if (fabs(rz) > this->m_atom->GetRadCut() + delta) continue;

                /* check for cells in a plane that are too far apart */
                if (sqrt(rx*rx+ry*ry) > (this->m_atom->GetRadCut() +sqrt(2.0)*delta)) continue;
                if (sqrt(rx*rx+rz*rz) > (this->m_atom->GetRadCut() +sqrt(2.0)*delta)) continue;
                if (sqrt(ry*ry+rz*rz) > (this->m_atom->GetRadCut() +sqrt(2.0)*delta)) continue;

                /* other cells that are too far apart */
                if (sqrt(rx*rx + ry*ry + rz*rz) > (sqrt(3.0) * delta + this->m_atom->GetRadCut())) continue;
                
                /* cells are close enough. add to list */
                this->m_atom->SetPairItem(2*npair,   i);
                this->m_atom->SetPairItem(2*npair+1, j);
                ++npair;
            }
        }
        this->m_atom->SetNPairs(npair);
        
	// printf("Cell list has %dx%dx%d=%d cells with %d/%d pairs and "
	//      "%d atoms/celllist.\n", ngrid, ngrid, ngrid, this->m_atom->GetNCells(), 
        //       this->m_atom->GetNPairs(), ncell*(ncell-1)/2, nidx);
    }

    /* reset cell list and sort atoms into cells */
    ncell = this->m_atom->GetNCells();
    delta = this->GetDelta();
    ngrid = this->GetNGrid();
    
    for (i=0; i < ncell; ++i) {
        this->m_atom->SetCellNAtoms(i,0);
    }

    boxoffs= boxby2 - 0.5*delta;
    midx=0;
    for (i=0; i < natoms; ++i) {
        int idx,j,k,m,n;
        
        k=floor((pbc(this->m_atom->GetPosition(i),            
		     boxby2, this->m_atom->GetBoxSize())+boxby2)/delta);
        m=floor((pbc(this->m_atom->GetPosition(natoms + i),   
		     boxby2, this->m_atom->GetBoxSize())+boxby2)/delta);
        n=floor((pbc(this->m_atom->GetPosition(2*natoms + i), 
		     boxby2, this->m_atom->GetBoxSize())+boxby2)/delta);
        j = ngrid*ngrid*k+ngrid*m+n;

        idx = this->m_atom->GetCellNAtoms(j);
        this->m_atom->SetCellIndex(j,idx,i);
        ++idx;
        this->m_atom->SetCellNAtoms(j,idx);
        if (idx > midx) midx=idx;
    }
    if (midx > this->m_nidx) {
        printf("overflow in cell list: %d/%d atoms/cells.\n", midx, this->m_nidx);
        exit(1);
    }

    //No error
    return true;
};


