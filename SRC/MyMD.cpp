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
  allocateMemory();
  readInput();

  /* Load initial position and velocity. */ 
  readRestart();

  /* Open energy and trajectory output files. */
  erg=fopen(ergfile,"w");
  traj=fopen(trajfile,"w");

  /* Initializes forces and energies. */
  nfi = 0;
  integrator->UpdateCells();
  force->ComputeForce(atoms);
  integrator->CalcKinEnergy();
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
  printf("Simulation Done.\n");
}

/******************************************************************************/
/* Main MD loop. */

void MyMD::MDLoop() {
  printf("Starting simulation with %d atoms for %d steps.\n",atoms->GetNAtoms(), nsteps);
  printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");  
  output();
  for(nfi=1; nfi <= this->nsteps; ++nfi) {

    /* Write output, if requested. */
    if ((nfi % nprint) == 0) output();

    /* Propagate atoms and recompute energies. */
    integrator->CalcVelocity();
    integrator->CalcKinEnergy();

    /* Update cell list. */
    if ((nfi % cellfreq) == 0)
      integrator->UpdateCells();
  }
}

/******************************************************************************/
/* Read input file. */

bool MyMD::readInput() {
  char line[BLEN];
  if(get_a_line(stdin,line)) return 1;
  atoms->Init(atoi(line));
  fprintf(stderr, "%d", atoms->GetNAtoms());
  if(get_a_line(stdin,line)) return 1;
  atoms->SetMass(atof(line));
  if(get_a_line(stdin,line)) return 1;
  double epsilon=atof(line);
  if(get_a_line(stdin,line)) return 1;
  double sigma=atof(line);
  force->Init("PAIR", "LJ", epsilon, sigma);  
  if(get_a_line(stdin,line)) return 1;
  atoms->SetRadCut(atof(line));
  if(get_a_line(stdin,line)) return 1;
  atoms->SetBoxSize(atof(line));
  if(get_a_line(stdin,restfile)) return 1;
  if(get_a_line(stdin,trajfile)) return 1;
  if(get_a_line(stdin,ergfile)) return 1;
  if(get_a_line(stdin,line)) return 1;
  this->nsteps=atoi(line);
  if(get_a_line(stdin,line)) return 1;
  integrator->SetTimestep(atof(line));
  if(get_a_line(stdin,line)) return 1;
  this->nprint=atoi(line);
}

/******************************************************************************/
/* Read restart. */

void MyMD::readRestart() {
  FILE *fp=fopen(restfile,"r");
  if(fp) {
    int natoms=atoms->GetNAtoms();
    double index1, index2, index3;
    index1=index2=index3=0;
    for(int i=0; i<natoms; ++i) {
      fscanf(fp,"%lf%lf%lf", &index1, &index2, &index3);
      atoms->SetPosition(i, index1);
      atoms->SetPosition(i+natoms, index2);
      atoms->SetPosition(i+2*natoms, index3);
    }
    for(int i=0; i<natoms; ++i) {
      fscanf(fp,"%lf%lf%lf", &index1, &index2, &index3);
      atoms->SetVelocity(i, index1);
      atoms->SetVelocity(i+natoms,  index2);
      atoms->SetVelocity(i+2*natoms, index3);
    }
    fclose(fp);
    azzero(atoms->GetForce(), 3*nthreads*natoms);
  } else {
    perror("cannot read restart file");
    exit(1);
  }
}

/******************************************************************************/
/* Allocate classes memory. */

void MyMD::allocateMemory() {
  atoms = new Atoms();
  force = new Force();
  integrator = new Integrator();
  integrator->Init(atoms, force);
}

/******************************************************************************/
/* Append data to output. */

void MyMD::output() {
  int i, natoms;
  natoms=atoms->GetNAtoms();
  printf("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", nfi, atoms->GetTemp(), atoms->GetKinEnergy(), 
	 atoms->GetPotEnergy(), atoms->GetKinEnergy()+atoms->GetPotEnergy());
  fprintf(erg,"% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", nfi, atoms->GetTemp(), atoms->GetKinEnergy(), 
	  atoms->GetPotEnergy(), atoms->GetKinEnergy()+atoms->GetPotEnergy());
  fprintf(traj,"%d\n nfi=%d etot=%20.8f\n", natoms, nfi, atoms->GetKinEnergy()+atoms->GetPotEnergy());
  for (i=0; i<natoms; ++i) {
    fprintf(traj, "Ar  %20.8f %20.8f %20.8f\n", atoms->GetPosition(i), 
	    atoms->GetPosition(natoms+i), atoms->GetPosition(2*natoms+i));
  }
}

/******************************************************************************/
