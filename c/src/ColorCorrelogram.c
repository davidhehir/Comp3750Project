#include <stdio.h>


struct Correlogram
{
  CvMat* img; // brg representation of image (is this needed?)
  CvMat* hsv; // hsv representation of image 
  const int searchDistance; // how far away from reference pixel to search
}

/* Function CalculateCorrelogram:
Calculates the color correlogram
feature vector for a given input
image. Implements Autocorrelogram
function only.
  src: input img 
  k: search distance
  
 */
 void CalculateCorrelogram()			 
 {						 

			
 } 


static int calcPixelCount(int x,int y, int k,CvScalar refColor)
{
  


  return 0;
}




static void lambdaH(Correlogram correlogram,int x, int y, int k,CvScalar refColor)
{
  // tmp sum of all pixels within k distance that contain refColor
  int sum = 0;
  int i;
  CvScalar tmpPixel;

  for ( i = 0; i < k ; i++ )
    {
      tmpPixel = cvGet2D(correlogram.hsv,x,y+i);
      if (refColor==tmpPixel)
	sum++;
    }
  return sum;
}

/*

*/
static void lambdaV(int x, int y, int k, CvScalar refColor)
{
  int sum=0;
  int i;
  CvScalar tmpPixel;
  
  for ( i = 0; i < k; i++ )
    {
      tmpPixel = cvGet2D( correlogram.hsv, x, y+i );
      if (refColor == tmpPixel)
	sum++
    }
  return sum;
}


