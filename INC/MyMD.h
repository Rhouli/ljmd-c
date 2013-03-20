#ifndef MD_MYMD_H
#define MD_MYMD_H

#include "Integrator.h"
#include "Force.h"
#include "Atoms.h"
#include "Helper.h"

/* generic file- or pathname buffer length */
#define BLEN 200
/* number of MD steps between cell list updates */
const int cellfreq=4;

class MyMD {
  public:
    /* Variables */
    Atoms *atoms;
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
    MyMD();
    ~MyMD();
    void MDLoop();
  private:
    void readInput();
    void allocateMemory();
    void readRestart();
    void output();
};

#endif
