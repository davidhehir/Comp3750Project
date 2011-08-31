#include <stdio.h>
#include "minunit.h"

int tests_run = 0;

int x = 7;

static char * test_framework()
{
  mu_assert("error, x!=7",x==7);
  return 0;
}

static char * calculateCorrelogram()
{
  
  return 0;
}

static char * ColorCorrelogramTestSuite()
{
  mu_run_test(test_framework);
  return 0;
}

int main(int argc, char **argv)
{
  char *result = ColorCorrelogramTestSuite();
  if (result != 0)
    {
      printf("%s\n",result);
    }
  else
    {
      printf("Tests Rune: %d\n",tests_run);
    }

  return result != 0;
}
