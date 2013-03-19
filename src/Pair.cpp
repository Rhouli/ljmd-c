#include <string.h>
#include "Pair.h"

/* Constructor */

Pair::Pair(char* _pot_type, double arg1, double arg2){
  if(!strcmp(_pot_type,"LJ")) {
    LJ = new Pair_LJ(arg1,arg2);
  }
  pot_type=(char*)malloc((strlen(_pot_type)+1)*sizeof(char));
  sprintf(pot_type,"%s",_pot_type);
}

/* Deconstructor */
Pair::~Pair(){
  if(!strcmp(pot_type,"LJ")) {
    delete LJ;
  }
  free(pot_type);
}

void Pair::ComputeForce(Atom *atom){
 if(!strcmp(pot_type,"LJ")){
    LJ->ComputeForce(atom);
 }
}
