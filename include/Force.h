/**
 * Force class
 *
 * @short This class provides force calculations
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_FORCE_H
#define MD_FORCE_H

//Includes (TODO)

class Force {

    public:
    /**
     * Default constructor
     */
    Force() {}

    /**
     * Default destructor
     */
    virtual ~Force() {}

    /**
     * Init
     * @param Pointer to atom class
     * @return Standard error code
     */
    static bool Init(Atom *atom);

    /**
     * Calculate different kinds of pair-potentials
     * @return a pointer to an object of class Pair
    */
    class Pair *pair;
    char *pair_type;

};

#endif //> !class
