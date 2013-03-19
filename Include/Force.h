/**
 * Force class
 *
 * @short This class provides force calculations
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_FORCE_H
#define MD_FORCE_H

//Includes (TODO)
#include "Atom.h"

class Force {

    public:
    /**
     * Default constructor
     */
    Force();

    /**
     * Default constructor
     */
    Force(char* pot, char* pot_type, double arg1, double arg2);

    /**
     * Default destructor
     */
    virtual ~Force();

    /**
     * Init
     * @param Pointer to atom class
     * @return Standard error code
     */
    static void ComputeForce(Atom* atom);

    /**
     * Calculate different kinds of pair-potentials
     * @return a pointer to an object of class Pair
    */
    class Pair *pair;
    char *pot;

};

#endif //> !class
