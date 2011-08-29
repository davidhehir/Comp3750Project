#include <stdio.h>
#include <math.h>
#include "cv.h"

typedef struct Correlogram
{
  IplImage* src; // brg representation of image (is this needed?)
  IplImage* hsv; // hsv representation of image 
  const int searchDistance; // how far away from reference pixel to search
  int* FeatureVector;
} Correlogram;

#define NUM_BINS 162;


void CalculateCorrelogram();
static int* calcNumerator(Correlogram,int* );
int calcPixelCount(Correlogram,int,int,CvScalar);
int lambdaH(IplImage*,int,int,int, CvScalar);
int lambdaV(IplImage*,int,int,int,CvScalar);
IplImage* quantizeHSV(IplImage*);
double quantizePixel(double,double);


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


/* calcNumerator:
Calculates the numerator component of the feature vector
by calculating the number of pixels within a distance d
away from pixel p that have the same color as p. 

@param[in] correlogram: correlogram structure to calculate
the numerator for.
 */
static int* calcNumerator(Correlogram correlogram,int * featureVector)
{
  int i;
  int j;
  CvScalar refColor;
  for (i=0;i<cvGetSize(correlogram.src).height;i++)
    {
      for (j=0;j<cvGetSize(correlogram.src).width;j++)
	{
	  refColor = cvGet2D(correlogram.hsv,i,j);
	  calcPixelCount(correlogram,j,i,refColor);
	}
    }
  return featureVector;
}



/* calcPixelCount:
Calculates the number of pixels within an square radius containing
the same color as a given reference color

@param[in] correlogram: input correlogram to calculate pixels counts from (i.e. 
contains image information, search radius etc
@param[in] x: starting x position
@param[in] y: starting y position
@param[in] refColor: reference color to compare other pixels to
@return the number of pixels within distance d with color refColor
 */
int calcPixelCount(Correlogram correlogram, int x,int y,CvScalar refColor)
{
  int pixCount = 0;
  int i;
  int width = cvGetSize(correlogram.src).width;
  int height = cvGetSize(correlogram.src).height;
  for (i = correlogram.searchDistance + 1; i >= 1; i--)
    {
      // check that the horizontal count is within image range
      if ((y + i >= 0) && (y + i < height))
	pixCount += lambdaH(correlogram.hsv,x-i,y+1,2*i,refColor);
      if ((y - i >= 0) && (y - i < height))
	pixCount += lambdaH(correlogram.hsv,x-i,y-1,2*i,refColor);
      // check vertical count is within image range
      if ((x - i >= 0) && (x - i < width))
	pixCount += lambdaV(correlogram.hsv,x-i,y-i+1,2*i,refColor);
      if ((x + i >= 0) && (x + i < width))
	pixCount += lambdaV(correlogram.hsv,x+i,y-i+1,2*i,refColor);
    }
  return pixCount;
}



int lambdaH(IplImage* hsv,int x, int y, int k,CvScalar refColor)
{
  // tmp sum of all pixels within k distance that contain refColor
  int sum = 0;
  int i;
  int maxX = cvGetSize(hsv).width;
  CvScalar tmpPixel;

  for ( i = 0; i < k; i++ )
    {
      if ((x + i) >= maxX)
        break;
      else if ((x + i ) >= 0)
        {
          tmpPixel = cvGet2D(hsv, y,x+i);
	  if (CompareScalar(refColor,tmpPixel))
	    sum++;
	}
    }
  return sum;
}

/*

*/
int lambdaV(IplImage* hsv,int x, int y, int k, CvScalar refColor)
{
  int sum=0;
  int i;
  int maxY = cvGetSize(hsv).height;
  CvScalar tmpPixel;
  
  for ( i = 0; i < k; i++ )
    {
      if ((y + i) >= maxY)
	break;
      else if ((y + i ) >= 0) 
	{
	  tmpPixel = cvGet2D( hsv, x, y+i );
	  if (CompareScalar(refColor,tmpPixel))
	    sum++;
	}
    }
  return sum;
}

/* quantizeHSV:
Given a hsv input image, quantize using 162 bin
method (18 h bins, 3 s bins and 3 v bins)

@param[in] image: input image to be quantized. 
MUST be pre converted to hsv
 */
IplImage* quantizeHSV(IplImage* image)
{
  IplImage* qhsv;
  int i;
  int j;
  const int width = cvGetSize(image).width;
  const int height = cvGetSize(image).height;
  /* define maximum hue, saturation and values
     to set range of expected values.
   */
  const int maxH = 180;
  const int maxS = 255;
  const int maxV = 255;

  // define the number of bins for each channel
  const int nHBins = 18;
  const int nSBins = 3;
  const int nVBins = 3;

  // Number of values between each quantization value
  const double hInterval = maxH / nHBins;
  const double sInterval = maxS / nSBins;
  const double vInterval = maxV / nVBins;

  // tmp quantized pixel values
  double tmpH,tmpS,tmpV;
  CvScalar oldPixel,newPixel;

  for (i=0;i<height;i++)
    {
      for (j=0;j<width;j++)
	{
	  oldPixel = cvGet2D(image,i,j);
	  tmpH = quantizePixel(oldPixel.val[0],hInterval);
	  tmpS = quantizePixel(oldPixel.val[1],sInterval);
	  tmpV = quantizePixel(oldPixel.val[2],vInterval);
	  newPixel = cvScalar(tmpH,tmpS,tmpV,0);
	  cvSet2D(qhsv,i,j,newPixel);
	}
    }
  return qhsv;
}

double quantizePixel(double pixelValue,double interval)
{
  double newPixelValue;
  if (( ((int)pixelValue)%((int)interval)) > interval /2)
    {
      newPixelValue = interval * (pixelValue/interval + 1);
    }
  else
    {
      newPixelValue = interval * (pixelValue/interval);
    }
  return newPixelValue;
}
