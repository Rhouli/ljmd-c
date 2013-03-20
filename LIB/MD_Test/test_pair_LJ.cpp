#include "test_pair_LJ.h"

using namespace std;

namespace {

  class PairLJTest : public ::testing::Test {
  protected:
    PairLJTest() {
      
    }
    
    virtual ~PairLJTest(){
      
    }
    
    /* Pre Test Initializations go in here  */
    /* To be run before every test          */
    virtual void Setup() {
      
    }
    
    /* Post Test deconstructions go in here */
    /* To be run before every test          */
    virtual void TearDown() {
      
    }    
  };
  
  /* Example Test to test the wrong coeff */
  TEST_F(PairLJTest, WrongCoeff) {
    
  }
}

/* Run the actual test                  */
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

  
