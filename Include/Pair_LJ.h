/**
 * Pair_LJ class
 *
 * @short This class provides what is needed to compute pair forces of Lennard-Jones type
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_PAIR_LJ_H
#define MD_PAIR_LJ_H

//Includes (TODO)
#include "Pair.h"

class Pair_LJ {

<<<<<<< HEAD
    public:
    Pair_LJ(){}
     /**
     * Default constructor
     * @param Pointer to atom class
     */
    Pair_LJ(double epsilon, double sigma);

    /**
     * Default destructor
     */
    ~Pair_LJ(){}

    /**
     * Force computer
     * @return Standard error code
     */
    void ComputeForce(Atom *atom);

/* variables */
    double sigma,epsilon;
=======
 public:
  Pair_LJ(){}
  /**
   * Default constructor
   * @param Pointer to atom class
   */
  Pair_LJ(double epsilon, double sigma);
  
  /**
   * Default destructor
   */
  virtual ~Pair_LJ();
  
  /**
   * Force computer
   * @return Standard error code
   */
  void ComputeForce(Atom *atom);
  
  /* variables */
  double sigma,epsilon;
>>>>>>> a4c8521fa412f66d9fe1aa7bc6951ecd1660fe0c

};

#endif //> !class
