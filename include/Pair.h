/**
 * Pair class
 *
 * @short This class provides what is needed to compute pair forces
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_PAIR_H
#define MD_PAIR_H

//Includes (TODO)

class Pair {

    public:
    /**
     * Default constructor
     */
    Pair() {}

    /**
     * Default destructor
     */
    virtual ~Pair() {}

    /**
     * Init
     * @param Pointer to atom class
     * @return Standard error code
     */
    static bool Init(Atom *atom) {}
    bool Pair_LJ() {}
    bool Pair_Morse() {}

};

#endif //> !class
