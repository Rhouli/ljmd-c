#include "Force.h"

/* Full constructor */ 
void Force::Init(std::string _pot, std::string _pot_type, double arg1, double arg2){
  pot = _pot;
  if(_pot=="PAIR") {
    pair = new Pair();
    pair->Init(_pot_type, arg1, arg2);
  }
}
/* Deconstructor */
Force::~Force(){
  if(!(pot=="PAIR")){
    delete pair;
  }
}

void Force::ComputeForce(Atoms *atom){
  if(!(pot=="PAIR")){
    pair->ComputeForce(atom);
  }
}
