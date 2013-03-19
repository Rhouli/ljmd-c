/**
 * Atoms class
 *
 * @short This class provides an abstract summary of all atoms in the system
 * @authors Maksim Markov <maxmarkov@gmail.com>, Manuel Proissl <mproissl@cern.ch>
 */

#ifndef MD_ATOM_H
#define MD_ATOM_H

//Includes
#include <iostream>
#include <string>
#include <vector>

class Atoms {

    public:
    /**
     * Default constructor
     */
    Atoms();

    /**
     * Default destructor
     */
    virtual ~Atoms();

    /**
     * Init atoms
     * @param natoms Number of atoms
     * @return Standard error code
     */
    static const bool Init(int natoms=0);

    /**
     * Set mass
     * @param mass of atoms
     */
    inline void SetMass(double mass) { this.m_mass = mass; };

    /**
     * Set kinetic energy
     * @param energy of atoms
     */
    inline void SetKinEnergy(double energy) { this.m_kinenergy = energy; };

    /**
     * Set potential energy
     * @param energy of atoms
     */
    inline void SetPotEnergy(double energy) { this.m_potenergy = energy; };

    /**
     * Set position of atoms by index
     * @param idx Index of atom
     * @param pos Position of atom
     * @return Standard error code
     */
    static const bool SetPosition(int idx, double pos);
    
    /**
     * Set velocity of atoms by index
     * @param idx Index of atom
     * @param pos Velocity of atom
     * @return Standard error code
     */
    static const bool SetVelocity(int idx, double vel);
    
    /**
     * Set force acting on atoms by index
     * @param idx Index of atom
     * @param force Force acting
     * @return Standard error code
     */
    static const bool SetForce(int idx, double force);

    /**
     * Set temperature
     * @param temperature
     */
    inline void SetTemp(double temp) { this.m_temperature = temp; };

    /**
     * Set radial cutoff value
     * @param radcut cutoff
     */
    inline void SetRadCut(double radcut) { this.m_radcut = radcut; };

    /**
     * Set box size
     * @param box size
     */
    inline void SetBoxSize(double boxsize) { this.m_boxsize = boxsize; };

    /**
     * Set number of pairs
     * @param npairs Number of pairs
     */
    inline void SetNPairs(int npairs) { this.m_npairs = npairs; };

    /**
     * Set item in pair list container
     * @param idx Container index
     * @param pair Pair index
     * @return Standard error code
     */
    static const bool SetPairItem(int idx, int pair);

    /**
     * Set number of cells (reserve memory: cells, pairlist)
     * @param ncells Number of cells
     * @return Standard error code
     */
    static const bool SetNCells(int ncells);

    /**
     * Set cell data by index
     * @param vecIdx  Index of cell container
     * @param atomIdx Index of atom
     * @return Standard error code
     */
    static const bool SetCellData(int vecIdx, int atomIdx);

    /* ################################################################################################# */

    /**
     * Get mass
     * @return mass of atoms
     */
    inline double GetMass() { return m_mass; };

    /**
     * Get kinetic energy
     * @return energy of atoms
     */
    inline double GetKinEnergy() { return m_kinenergy; };

    /**
     * Get potential energy
     * @return energy of atoms
     */
    inline double GetPotEnergy() { return m_potenergy; };

    /**
     * Get position of atoms by index
     * @param idx Index of atom
     * @return pos Position of atom
     */
    double GetPosition(int idx);
    
    /**
     * Get velocity of atoms by index
     * @param idx Index of atom
     * @return pos Velocity of atom
     */
    double GetVelocity(int idx);
    
    /**
     * Get force acting on atoms by index
     * @param idx Index of atom
     * @return force Force acting
     */
    double GetForce(int idx);

    /**
     * Get temperature
     * @return temperature
     */
    inline double GetTemp() { return this.m_temperature; };

    /**
     * Get radial cutoff value
     * @return radcut cutoff
     */
    inline double GetRadCut() { return this.m_radcut; };

    /**
     * Get box size
     * @return box size
     */
    inline double GetBoxSize() { return this.m_boxsize; };

    /**
     * Get number of pairs
     * @return npairs Number of pairs
     */
    inline int GetNPairs() { return this.m_npairs; };

    /**
     * Get item in pair list container
     * @param idx Container index
     * @return Pair item index
     */
    const int GetPairItem(int idx);

    /**
     * Get number of cells
     * @return Number of cells
     */
    inline int GetNCells() { return this.m_ncells; };

    /**
     * Get cell data by index
     * @param vecIdx  Index of cell container
     * @return Index of atom
     */
    const int GetCellData(int vecIdx);

    private:
        /**
         * Init flag
         */
        bool m_isInitialized;
    
        /**
         * Number of atoms
         */
        int m_natoms;

        /**
         * Mass for each atom
         */
        double m_mass;

        /**
         * Initial kinetic energy of system
         */
        double m_kinenergy;

        /**
         * Potential energy of system
         */
        double m_potenergy;

        /**
         * Initial position of each atom
         */
        double* m_position;

        /**
         * Initial velocity of each atom
         */
        double* m_velocity;

        /**
         * Force acting on each atom at t0
         */
        double* m_force;

        /**
         * Temperature in system
         */
        double m_temperature;
        
        /**
         * R-boundary max. cut
         */
        double m_radcut;
        
        /**
         * The box size
         */
        double m_boxsize;
        
        /**
         * Number of pairs
         */
        int m_npairs;

        /**
         * Pair list container
         */
        int* m_pairlist;

        /**
         * Number of cells
         */
        int m_ncells;

        /**
         * Cell list data
         */
        std::vector<std::vector<int> > m_cells;

};

#endif //> !class
