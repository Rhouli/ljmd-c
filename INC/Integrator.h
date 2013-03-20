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

    /**
     * Set time step
     */
    inline void SetTimestep(double timestep) { this.m_timestep = timestep; };

    /**
     * Set grid layout
     */
    inline void SetNGrid(int ngrid) { this.m_ngrid = ngrid; };

    /**
     * Set size of items in cell container
     */
    inline void SetNIdx(int nidx) { this.m_idx = idx; };

    /**
     * Set Delta
     */
    inline void SetDelta(double delta) { this.m_delta = delta; };

    /* ################################################################################ */

    /**
     * Get time step
     */
    const double GetTimestep() { return this.m_timestep; };

    /**
     * Get grid layout
     */
    const int GetNGrid() { return this.m_ngrid; };

    /**
     * Get size of items in cell container
     */
    const int GetNIdx() { return this.m_idx; };

    /**
     * Get Delta
     */
    const double GetDelta() { return this.m_delta; };

    private:
        /**
         * Pointer to atoms
         */
        Atom *m_atom;

        /**
         * Pointer to forces
         */
        Force *m_force;

        /**
         * Time step between iterations
         * @brief In C version: dt
         */
        double m_timestep;
        
        /**
         * Grid layout
         */
        int m_ngrid;

        /**
         * Size of items in cell container
         */
        int m_nidx;

        /**
         * Ratio: Box size / ngrid
         */
        double m_delta; 

};

#endif //> !class

