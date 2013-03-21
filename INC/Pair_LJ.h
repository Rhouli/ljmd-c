/**
 * Pair_LJ class
 *
 * @short This class provides what is needed to compute pair forces of Lennard-Jones type
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_PAIR_LJ_H
#define MD_PAIR_LJ_H

#include "Atoms.h"

class Pair_LJ {  
 public:
  Pair_LJ(){}
  /**
   * Default constructor
   * @param Pointer to atom class
   */
  Pair_LJ(double _epsilon, double _sigma){
    epsilon = _epsilon;
    sigma = _sigma;
  };
    
  /**
   * Default destructor
   */
  virtual ~Pair_LJ(){}
  
  /**
   * Force computer
   * @return Standard error code
   */
  void ComputeForce(Atoms *atom);
  
  /* variables */
  double sigma,epsilon;
};

#endif //> !class
