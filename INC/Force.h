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
   /**
    * Default constructor
    */
   Force(){}

   /**
    * Default destructor
    */
   virtual ~Force();

   void Init(std::string, std::string, double, double);
   /**
    * Init
    * @param Pointer to atom class
    * @return Standard error code
    */
   void ComputeForce(Atoms *atom);

   /**
    * Calculate different kinds of pair-potentials
    * @return a pointer to an object of class Pair
    */
   Pair *pair;
   std::string pot;
};

#endif //> !class
