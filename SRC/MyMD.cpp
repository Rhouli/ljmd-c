/******************************************************************************/
#include "MyMD.h"


/* Constructor. */

MyMD::MyMD() {

/* Obtain the number of threads. */
#if defined(_OPENMP)
#pragma omp parallel
    {
        if(0 == omp_get_thread_num()) {
            nthreads=omp_get_num_threads();
            printf("Running OpenMP version using %d threads\n", nthreads);
        }
    }
#else
    nthreads=1;
#endif

  /* Read input and allocate classes memory. */
  readInput();
  allocateMemory();

  /* Load initial position and velocity. */ 
  readRestart();

  /* Open energy and trajectory output files. */
  erg=fopen(ergfile,"w");
  traj=fopen(trajfile,"w");

  /* Initializes forces and energies. */
  nfi = 0;
  force->ComputeForce(atoms);
  ekin(&atoms);
}

/******************************************************************************/
/* Destructor. */

MyMD::~MyMD() {
  delete atoms;
  delete force;
  delete integrator;

  /* clean up: close files, free memory */
  fclose(erg);
  fclose(traj);
  free(atoms->pos);
  free(atoms->vel);
  free(atoms->frc);
  printf("Simulation Done.\n");
}

/******************************************************************************/
/* Main MD loop. */

void MyMD::MyLoop() {
  printf("Starting simulation with %d atoms for %d steps.\n",atoms.natoms, atoms.nsteps);
  printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
  output();
  
  for(nfi=1; nfi <= atoms->nsteps; ++nfi) {

    /* Write output, if requested. */
    if ((nfi % nprint) == 0) output();

    /* Propagate atoms and recompute energies. */
    integrator->VelVerlet(&atoms);
    integrator->ekin(&atoms);

    /* Update cell list. */
    if ((nfi % cellfreq) == 0)
          updcells(&atoms);
  }
}

/******************************************************************************/
/* Read input file. */

void MyMD::readInput() {
  char line[BLEN];
  if(get_a_line(stdin,line)) return 1;
  atoms->natoms=atoi(line);
  if(get_a_line(stdin,line)) return 1;
  atoms->mass=atof(line);
  if(get_a_line(stdin,line)) return 1;
  force->epsilon=atof(line);
  if(get_a_line(stdin,line)) return 1;
  force->sigma=atof(line);
  if(get_a_line(stdin,line)) return 1;
  atoms->rcut=atof(line);
  if(get_a_line(stdin,line)) return 1;
  box=atof(line);
  if(get_a_line(stdin,restfile)) return 1;
  if(get_a_line(stdin,trajfile)) return 1;
  if(get_a_line(stdin,ergfile)) return 1;
  if(get_a_line(stdin,line)) return 1;
  nsteps=atoi(line);
  if(get_a_line(stdin,line)) return 1;
  integrator->dt=atof(line);
  if(get_a_line(stdin,line)) return 1;
  nprint=atoi(line);
}

/******************************************************************************/
/* Read restart. */

void MyMD::readRestart() {
  FILE *fp=fopen(restfile,"r");
  if(fp) {
    int natoms=atoms->natoms;

    for (i=0; i<natoms; ++i) {
      fscanf(fp,"%lf%lf%lf",atoms->pos+i, atoms->pos+natoms+i, atoms->pos+2*natoms+i);
    }
    for (i=0; i<natoms; ++i) {
      fscanf(fp,"%lf%lf%lf",atoms->vel+i, atoms->vel+natoms+i, atoms->vel+2*natoms+i);
    }
    fclose(fp);
    azzero(atoms->frc, 3*nthreads*atoms->natoms);
  } else {
    perror("cannot read restart file");
    exit(1);
  }
}

/******************************************************************************/
/* Allocate classes memory. */

void MyMD::allocateMemory() {
  atoms = new Atoms();
  force = new Force;
  integrator = new Integrator;
}

/******************************************************************************/
/* Append data to output. */

void MyMD::output() {
  int i, natoms;
  natoms=atoms->natoms;
  
  printf("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", nfi, atoms->temp, atoms->ekin, atoms->epot, atoms->ekin+atoms->epot);
  fprintf(erg,"% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", nfi, atoms->temp, atoms->ekin, atoms->epot, atoms->ekin+atoms->epot);
  fprintf(traj,"%d\n nfi=%d etot=%20.8f\n", atoms->natoms, nfi, atoms->ekin+atoms->epot);
  for (i=0; i<natoms; ++i) {
      fprintf(traj, "Ar  %20.8f %20.8f %20.8f\n", atoms->pos[i], atoms->pos[natoms+i], atoms->pos[2*natoms+i]);
  }
}

/******************************************************************************/
