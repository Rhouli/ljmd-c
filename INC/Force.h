/**
 * Force class
 *
 * @short This class provides force calculations
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#ifndef MD_FORCE_H
#define MD_FORCE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
//#include "Helper.h"

//Includes (TODO)
#include "Atoms.h"
#include "Pair.h"

class Force {  
 public:
  Force(){}
  
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
  static void ComputeForce(Atoms* atom);
  
  /**
   * Calculate different kinds of pair-potentials
   * @return a pointer to an object of class Pair
   */
  class Pair *pair;
  char *pot;
};

#endif //> !class
