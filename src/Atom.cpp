/**
 * Atoms class
 *
 * @short This class provides an abstract summary of all atoms in the system
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */


static const double _def_ = -999;


/**
 * Default constructor
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
    m_cells(new std::vector<int>(0))
{};


/**
 * Default destructor
 */
Atoms::~Atoms()
{
    if(this.m_position) delete this.m_position;
    if(this.m_velocity) delete this.m_velocity;
    if(this.m_force)    delete this.m_force;
    if(this.m_pairlist) delete this.m_pairlist;
};


/**
 * Init atoms
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
 * Set number of cells (reserve memory: cells, pairlist)
 */
bool Atoms::SetNCells(int ncells)
{
    //Set number of cells
    this.m_ncells = ncells;

    //Sanity check
    if(this.m_pairlist) {
        std::cout << "( ERROR ) Atoms::SetNCells(): Bug hint > pairlist array already defined. Abort!" << std::endl;
        return false;
    }

    //Define pair list container
    this.m_pairlist = new int[2*ncells*ncells];

    //No errors
    return true;
};



