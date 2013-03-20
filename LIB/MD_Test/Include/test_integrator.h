/* TestIntegrator()
 * 
 * Header file for Test Integrator
 *
 */

#ifndef TEST_INTEGRATOR
#define TEST_INTEGRATOR

#include <iostream>
#include <math.h>
#include "mpi.h"
#include "gtest/gtest.h"
#include "MyMD.h"
#include "Atom.h"
#include "Pair_LJ.h"
#include "Integrator.h"

class IntegratorTest{
 protected:
  IntegratorTest();
  virtual ~IntegratorTest();
  virtual void Setup();
  virtual void TearDown();
};

#endif
