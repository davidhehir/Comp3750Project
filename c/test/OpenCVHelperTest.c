#include "cv.h"
#include "../src/OpenCVHelper.h"    
#include <stdio.h>
#include "minunit.h"
int tests_run = 0;

int x = 6;
CvScalar scalar1;
CvScalar scalar2;

static char * test_framework()
{
  mu_assert("error, x!=6",x==6);
  return 0;
}

static char * CompareScalarTest()
{
  scalar1 = cvScalar(0,0,0,0);
  scalar2 = cvScalar(0,0,0,0);
  mu_assert("error, scalar1!=scalar2",CompareScalar(scalar1,scalar2));
  scalar2 = cvScalar(0,1,0,0);
  mu_assert("error, scalar1==scalar2",!CompareScalar(scalar1,scalar2));
  return 0;
}

static char * OpenCVHelperTestSuite()
{
  mu_run_test(test_framework);
  mu_run_test(CompareScalarTest);
  return 0;
}

int main(int argc, char **argv)
{
  char *result = OpenCVHelperTestSuite();
  printf("number of tests run: %d\n",tests_run);
  if (result) printf("FAIL: %s\n",result);
      
  return result != 0;
}
