/* TestPairLJ()
 * 
 * Header file for LJ Pair Potential Test
 *
 */

#ifndef TEST_PAIR_LJ
#define TEST_PAIR_LJ

#include <iostream>
#include <math.h>
#include "mpi.h"
#include "gtest/gtest.h"
#include "MyMD.h"
#include "Atom.h"
#include "Pair_LJ.h"

class PairLJTest{
 protected:
  PairLJTest();
  virtual ~PairLJTest();
  virtual void Setup();
  virtual void TearDown();
};

#endif
