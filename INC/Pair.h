/**
 * Pair class
 *
 * @short This class provides what is needed to compute pair forces
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_PAIR_H
#define MD_PAIR_H

//Includes (TODO)
#include "Atoms.h"
#include "Pair_LJ.h"

class Pair {
  
 public:
    /**
     * Default constructor
     */
    Pair(){}

    /**
     * Full constructor
     */
    Pair(char* pot_type, double arg1, double arg2);

    /**
     * Default destructor
     */
    virtual ~Pair();

    /**
     * Init
     * @param Pointer to atom class
     * @return Standard error code
     */
    void ComputeForce(Atoms *atom);
    class Pair_LJ* LJ;
//    class Morse* Pair_Morse;
    char *pot_type;
};

#endif //> !class
