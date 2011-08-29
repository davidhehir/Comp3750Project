#include <stdio.h>
#include "cv.h"

struct Correlogram
{
  CvMat* src; // brg representation of image (is this needed?)
  CvMat* hsv; // hsv representation of image 
  const int searchDistance; // how far away from reference pixel to search
};

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


static int calcPixelCount(struct Correlogram correlogram, int x,int y,CvScalar refColor)
{
  int pixCount = 0;
  int i;
  int width = cvGetSize(correlogram.src).width;
  int height = cvGetSize(correlogram.src).height;
  for (i = correlogram.searchDistance + 1; i >= 1; i--)
    {
      // check that the horizontal count is within image range
      if ((y + i >= 0) && (y + i < height))
	pixCount += lambdaH(correlogram,x-i,y+1,2*i,refColor);
      if ((y - i >= 0) && (y - i < height))
	pixCount += lambdaH(correlogram,x-i,y-1,2*i,refColor);
      // check vertical count is within image range
      if ((x - i >= 0) && (x - i < width))
	pixCount += lambdaV(correlogram,x-i,y-i+1,2*i,refColor);
      if ((x + i >= 0) && (x + i < width))
	pixCount += lambdaV(correlogram,x+i,y-i+1,2*i,refColor);
    }
  return pixCount;
}




int lambdaH(struct Correlogram correlogram,int x, int y, int k,CvScalar refColor)
{
  // tmp sum of all pixels within k distance that contain refColor
  int sum = 0;
  int i;
  int maxX = cvGetSize(correlogram.src).width;
  CvScalar tmpPixel;

  for ( i = 0; i < k; i++ )
    {
      if ((x + i) >= maxX)
        break;
      else if ((x + i ) >= 0)
        {
          tmpPixel = cvGet2D( correlogram.hsv, y,x+i);
	  if (CompareScalar(refColor,tmpPixel))
	    sum++;
	}
    }
  return sum;
}

/*

*/
int lambdaV(struct Correlogram correlogram,int x, int y, int k, CvScalar refColor)
{
  int sum=0;
  int i;
  int maxY = cvGetSize(correlogram.hsv).height;
  CvScalar tmpPixel;
  
  for ( i = 0; i < k; i++ )
    {
      if ((y + i) >= maxY)
	break;
      else if ((y + i ) >= 0) 
	{
	  tmpPixel = cvGet2D( correlogram.hsv, x, y+i );
	  if (CompareScalar(refColor,tmpPixel))
	    sum++;
	}
    }
  return sum;
}


