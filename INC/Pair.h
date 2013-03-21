/**
 * Pair class
 *
 * @short This class provides what is needed to compute pair forces
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_PAIR_H
#define MD_PAIR_H

//Includes (TODO)

#include <string.h>
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

    void Init(std::string, double, double);
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
    Pair_LJ* LJ;
    std::string pot_type;
};

#endif //> !class
