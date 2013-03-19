#ifndef MD_MYMD_H
#define MD_MYMD_H

#include "Integrator.h"
#include "Force.h"
#include "Atom.h"

class MyMD {
  public:
    /* Variables */
    Integrator *integrator;
    Force *force;
    Atom *atom;

    /* Methods */
    void MyMD();
    void ~MyMD();
    void MDLoop();
  private:
    void readInput();
    void allocateMemory();
    void readRestart():
}

#endif
