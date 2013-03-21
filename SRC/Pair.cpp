#include "Pair.h"

/* Constructor */

void Pair::Init(std::string _pot_type, double arg1, double arg2){
  this->pot_type = _pot_type;
  if(this->pot_type=="LJ") {
    LJ = new Pair_LJ(arg1, arg2);
  }
}
/* Deconstructor */
Pair::~Pair(){
  if(pot_type =="LJ") {
    delete LJ;
  }
}

void Pair::ComputeForce(Atoms *atom){
 if(pot_type=="LJ"){
    LJ->ComputeForce(atom);
 }
}
