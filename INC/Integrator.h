/**
 * Integrator class
 *
 * @short This class provides integration methods and allows to calculate kinetic energies, velocities and performs cell updates of the MD system.
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */

#ifndef MD_INTEGRATOR_H
#define MD_INTEGRATOR_H

//Includes
#include <math.h>
#include "Atoms.h"
#include "Force.h"

class Integrator {

    public:
    /**
     * Default ructor
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
     bool Init(Atoms *atom, Force *force);

    /**
     * Calculate Kinetic Energy
     * @return Standard error code
    */
      bool CalcKinEnergy();

    /**
     * Calculate Velocity
     * @return Standard error code
    */
      bool CalcVelocity();

    /**
     * Update cells
     * @return Standard error code
    */
      bool UpdateCells();

    /**
     * Set time step
     */
    inline void SetTimestep(double timestep) { this->m_timestep = timestep; };

    /**
     * Set grid layout
     */
    inline void SetNGrid(int ngrid) { this->m_ngrid = ngrid; };

    /**
     * Set size of items in cell container
     */
    inline void SetNIdx(int nidx) { this->m_nidx = nidx; };

    /**
     * Set Delta
     */
    inline void SetDelta(double delta) { this->m_delta = delta; };

    /* ################################################################################ */

    /**
     * Get time step
     */
     double GetTimestep() { return this->m_timestep; };

    /**
     * Get grid layout
     */
     int GetNGrid() { return this->m_ngrid; };

    /**
     * Get size of items in cell container
     */
     int GetNIdx() { return this->m_nidx; };

    /**
     * Get Delta
     */
     double GetDelta() { return this->m_delta; };
    
    /** 
     * Helper function: apply minimum image convention
     * @return convention
     */
    inline double pbc(double x,  double boxby2,  double box)
    {
        while (x >  boxby2) x -= box;
        while (x < -boxby2) x += box;
        return x;
    };

    private:
        /**
         * Pointer to atoms
         */
        Atoms *m_atom;

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

