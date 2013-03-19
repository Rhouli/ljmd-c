/**
 * Integrator class
 *
 * @short This class provides integration methods and allows to calculate kinetic energies, velocities and performs cell updates of the MD system.
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */

#ifndef MD_INTEGRATOR_H
#define MD_INTEGRATOR_H

//Includes (TODO)
#include "Atom.h"
#include "Force.h"

class Integrator {

    public:
    /**
     * Default constructor
     */
    Integrator();

    /**
     * Default destructor
     */
    virtual ~Integrator();

    /**
     * Init
     * @param Pointer to atom class
     * @param Pointer to force class
     * @return Standard error code
     */
    static bool Init(Atom *atom, Force *force);

    /**
     * Calculate Kinetic Energy
     * @return Standard error code
    */
    static const bool CalcKinEnergy();

    /**
     * Calculate Velocity
     * @return Standard error code
    */
    static const bool CalcVelocity();

    /**
     * Update cells
     * @return Standard error code
    */
    static const bool UpdateCells();

    private:
        /**
         * Pointer to atoms
         */
        Atom *m_atom;

        /**
         * Pointer to forces
         */
        Force *m_force;


};

#endif //> !class

