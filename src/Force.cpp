#include <string.h> 
#include "Force.h"

/* Full constructor */ 
Force::Force (char* _pot, char* _pot_type, double arg1, double arg2){
 if(!strcmp(_pot,"PAIR")) {
  pair = new Pair(_pot_type, arg1, arg2);
 }
 pot=(char*)malloc((strlen(_pot)+1)*sizeof(char));
 sprintf(pot,"%s",_pot);
}

/* Deconstructor */
Force::~Force(){
 if(!strcmp(pot,"PAIR"))
 {
  delete pair;
 }
 free(pot);
}

void Force::ComputeForce(Atom* atom){
 if(!strcmp(pot,"PAIR")){
  pair->ComputeForce(atom);
 }
}
