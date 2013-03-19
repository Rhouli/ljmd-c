#ifndef MD_MYMD_H
#define MD_MYMD_H

#include "Integrator.h"
#include "Force.h"
#include "Atom.h"
#include "Helper.h"

/* generic file- or pathname buffer length */
#define BLEN 200
/* number of MD steps between cell list updates */
const int cellfreq=4;

class MyMD {
  public:
    /* Variables */
    Atom *atom;
    Force *force;
    Integrator *integrator;
   
    int nsteps;
    int nfi;
    int nthreads;
    int nprint;
    double box;
    char restfile[BLEN], trajfile[BLEN], ergfile[BLEN];
    FILE *erg, *traj;

    /* Methods */
    void MyMD();
    void ~MyMD();
    void MDLoop();
  private:
    void readInput();
    void allocateMemory();
    void readRestart():
    void output();
}

#endif
