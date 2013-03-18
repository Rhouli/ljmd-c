/**
 * Integrator
 *
 * @short This class provides integration methods and allows to calculate kinetic energies, velocities and performs cell updates of the MD system.
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */

/**
 * Default constructor
 */
Integrator::Integrator() :
    m_atom(NULL),
    m_force(NULL)
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
bool Init(Atom *atom, Force *force)
{
    //Set pointers
    if(!atom) {
        std::cerr << "( ERROR ) Atom null pointer... Abort Init!" << std::endl; 
        return false;
    }
    else m_atom  = atom;
    
    if(!force) {  
        std::cerr << "( ERROR ) Force null pointer... Abort Init!" << std::endl; 
        return false;
    }
    else m_force = force;

    //No error
    return true;
};//Init





