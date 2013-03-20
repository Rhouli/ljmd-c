#include "test_integrator.h"

using namespace std;
namespace {

  class IntegratorTest : public ::testing::Test {
  protected:
    IntegratorTest() {
      
    }
    
    virtual ~IntegratorTest(){
      
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
  TEST_F(IntegratorTest, WrongCoeff) {
    
  }
}

/* Run the actual test                  */
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

  
