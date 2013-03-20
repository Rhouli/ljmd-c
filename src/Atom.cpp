/**
 * Atoms class
 *
 * @short This class provides an abstract summary of all atoms in the system
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */


static const double _def_ = -999;


/**
 * Default constructor
 * ___________________________________________________________________________________
 */
Atoms::Atoms() :
    m_isInitialized(false),
    m_natoms(0),
    m_mass(_def_),
    m_kinenergy(_def_),
    m_potenergy(_def_),
    m_position(NULL),
    m_velocity(NULL),
    m_force(NULL),
    m_temperature(_def_),
    m_radcut(_def_),
    m_boxsize(_def_),
    m_npairs(0),
    m_pairlist(NULL),
    m_ncells(0),
    m_natoms_in_cell(NULL),
    m_cells(0, std::vector<int>(0))
{};


/**
 * Default destructor
 * ___________________________________________________________________________________
 */
Atoms::~Atoms()
{
    if(this.m_position)       delete this.m_position;
    if(this.m_velocity)       delete this.m_velocity;
    if(this.m_force)          delete this.m_force;
    if(this.m_pairlist)       delete this.m_pairlist;
    if(this.m_natoms_in_cell) delete this.m_natoms_in_cell;
};


/**
 * Init atoms
 * ___________________________________________________________________________________
 */
bool Atoms::Init(int natoms) 
{
    //Sanity check
    if(natoms==0) {
        std::cout << "( ERROR ) Atoms::Init(): number of atoms is 0. Abort!" << std::endl;
        return false;
    }

    //Set number of atoms
    this.m_natoms = natoms;

    //Sanity check 2
    if(this.m_position || this.m_velocity || this.m_force) {
        std::cout << "( ERROR ) Atoms::Init(): Bug hint > position, velocity or force arrays already defined. Abort!" << std::endl;
        return false;
    }

    //Init position, velocity and force arrays
    this.m_position = new double[natoms];
    this.m_velocity = new double[natoms];
    this.m_force    = new double[natoms];

    //No errors
    return true;
};


/**
 * Set position of atoms by index
 * ___________________________________________________________________________________
 */
bool Atoms::SetPosition(int idx, double pos)
{
    //Check index
    if(idx<0 || idx>(this.m_natoms-1)) {
        std::cout << "( ERROR ) Atoms::SetPosition(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    //Set position
    this.m_position[idx] = pos;

    //No errors
    return true;
};


/**
 * Set velocity of atoms by index
 * ___________________________________________________________________________________
 */
bool Atoms::SetVelocity(int idx, double vel)
{
    //Check index
    if(idx<0 || idx>(this.m_natoms-1)) {
        std::cout << "( ERROR ) Atoms::SetVelocity(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    //Set velocity
    this.m_velocity[idx] = vel;

    //No errors
    return true;
};


/**
 * Set force acting on atoms by index
 * ___________________________________________________________________________________
 */
bool Atoms::SetForce(int idx, double force)
{
    //Check index
    if(idx<0 || idx>(this.m_natoms-1)) {
        std::cout << "( ERROR ) Atoms::SetForce(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    //Set force
    this.m_force[idx] = force;

    //No errors
    return true;
};


/**
 * Set number of cells (and setup cells and pairlist container)
 * ___________________________________________________________________________________
 */
int Atoms::SetNCells(int ncells)
{
    //Set number of cells
    this.m_ncells = ncells;

    //Define cell data container ------>
    this.m_cells.clear();
    this.m_cells.resize(ncells);
    
    if(this.m_natoms_in_cell) delete this.m_natoms_in_cell;
    this.m_natoms_in_cell = new int[ncells];
    
    int nidx = 2 * this.m_natoms / ncells + 2;
    nidx = ((nidx/2) + 1) * 2;

    for(int i=0; i<ncells; ++i) {
        this.m_cells[i].resize(nidx);
    } //-------------------------------<

    //Define pair list container
    if(this.m_pairlist) delete this.m_pairlist;
    this.m_pairlist = new int[2*ncells*ncells];

    //Index for Integrator class
    return nidx;
};


/**
 * Set item in pair list container
 * ___________________________________________________________________________________
 */
bool Atoms::SetPairItem(int idx, int pair)
{
    //Check index
    if(idx<0 || idx>(2*this.m_ncells*this.m_ncells-1)) {
        std::cout << "( ERROR ) Atoms::SetPairItem(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    //Set pair item
    this.m_pairlist[idx] = pair;

    //No errors
    return true;
};


/**
 * Set cell data by index
 * ___________________________________________________________________________________
 */
bool Atoms::SetCellIndex(int cellID, int idxID, int idx)
{
    //Sanity checks
    if(cellID>this.m_cells.size()) {
        std::cout << "( ERROR ) Atoms::SetCellIndex(): cellID index out-of-bound. Abort!" << std::endl;
        return false;
    }
    if(idxID>this.m_cells[cellID].size()) {
        std::cout << "( ERROR ) Atoms::SetCellIndex(): idxID index out-of-bound. Abort!" << std::endl;
        return false;
    }

    //Set cell data item
    this.m_cells[cellID][idxID] = idx;

    //No errors
    return true;
};


/**
 * Set number of atoms per cell by index
 * ___________________________________________________________________________________
 */
bool Atoms::SetCellNAtoms(int cellID, int natoms)
{
    //Sanity checks
    if(cellID>this.m_cells.size()) {
        std::cout << "( ERROR ) Atoms::SetCellNAtoms(): cellID index out-of-bound. Abort!" << std::endl;
        return false;
    }

    //Set number of atoms
    this.m_natoms_in_cell[cellID] = natoms;

    //No errors
    return true;
};


/* ######################################################################################################## */


/**
 * Get position of atoms by index
 * ___________________________________________________________________________________
 */
double Atoms::GetPosition(int idx)
{
    //Check index
    if(idx<0 || idx>(this.m_natoms-1)) {
        std::cout << "( ERROR ) Atoms::GetPosition(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_position[idx];
};


/**
 * Get velocity of atoms by index
 * ___________________________________________________________________________________
 */
double Atoms::GetVelocity(int idx)
{
    //Check index
    if(idx<0 || idx>(this.m_natoms-1)) {
        std::cout << "( ERROR ) Atoms::GetVelocity(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_velocity[idx];
};


/**
 * Get force acting on atoms by index
 * ___________________________________________________________________________________
 */
double Atoms::GetForce(int idx)
{
    //Check index
    if(idx<0 || idx>(this.m_natoms-1)) {
        std::cout << "( ERROR ) Atoms::GetForce(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_force[idx];
};


/**
 * Get item in pair list container
 * ___________________________________________________________________________________
 */
int Atoms::GetPairItem(int idx)
{
    //Check index
    if(idx<0 || idx>(2*this.m_ncells*this.m_ncells-1)) {
        std::cout << "( ERROR ) Atoms::GetPairItem(): Index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_pairlist[idx];
};


/**
 * Get cell index by index
 * ___________________________________________________________________________________
 */
int Atoms::GetCellIndex(int cellID, int idxID)
{
    //Sanity checks
    if(cellID>this.m_cells.size()) {
        std::cout << "( ERROR ) Atoms::GetCellIndex(): cellID index out-of-bound. Abort!" << std::endl;
        return false;
    }
    if(idxID>this.m_cells[cellID].size()) {
        std::cout << "( ERROR ) Atoms::GetCellIndex(): idxID index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_cells[cellID][idxID];
};


/**
 * Get cell vector by index
 * ___________________________________________________________________________________
 */
std::vector<int> Atoms::GetCellIndex(int cellID)
{
    //Sanity checks
    if(cellID>this.m_cells.size()) {
        std::cout << "( ERROR ) Atoms::GetCellIndex(): cellID index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_cells[cellID];
};


/**
 * Get cell vector size by index
 * ___________________________________________________________________________________
 */
int Atoms::GetCellIndex(int cellID)
{
    //Sanity checks
    if(cellID>this.m_cells.size()) {
        std::cout << "( ERROR ) Atoms::GetCellIndex(): cellID index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_cells[cellID].size();
};


/**
 * Get number of atoms per cell by index
 * ___________________________________________________________________________________
 */
int Atoms::GetCellNAtoms(int cellID)
{
    //Sanity checks
    if(cellID>this.m_cells.size()) {
        std::cout << "( ERROR ) Atoms::GetCellNAtoms(): cellID index out-of-bound. Abort!" << std::endl;
        return false;
    }

    return this.m_natoms_in_cell[cellID];
};

