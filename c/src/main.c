#include <stdio.h>
#include <cv.h>
#include "OpenCVHelper.h"

int main()
{
  CvScalar s = cvScalar(0,0,0,0);
  printf("%d",CompareScalar(s,s));
  printf("hello");
  
}
