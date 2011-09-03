#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cv.h"
#include "OpenCVHelper.h"
#include <errno.h>
#include <string.h>

typedef struct Correlogram
{
	IplImage* src; // brg representation of image (is this needed?)
	IplImage* hsv; // hsv representation of image
	const int searchDistance; // how far away from reference pixel to search
	double* FeatureVector;
	const int NumBins;
} Correlogram;

#define NUM_BINS 162

const int HBINS=18;
const int SVBINS=3;
const int MAXH=180;
const int MAXSV=255;

extern int errno;

void CalculateCorrelogram(Correlogram correlogram,double *);
void calcNumerator(Correlogram,int* );
int calcPixelCount(Correlogram,int,int,CvScalar);
int lambdaH(IplImage*,int,int,int, CvScalar);
int lambdaV(IplImage*,int,int,int,CvScalar);
IplImage* quantizeHSV(IplImage*);
int quantizePixel(double,double,double);
int calculateBin(double,double,double);

void CalculateCorrelogram1(Correlogram* correlogram);
int calcPixelCount1(IplImage * hsv, int searchDistance, int x,int y,CvScalar refColor);
void calcNumerator1(IplImage* hsv,int searchDistance,int * numeratorVector);



void CalculateCorrelogram1(Correlogram* correlogram)
{
	IplImage * hsv;
	IplImage * hsvq;
	int * numerator;
	CvHistogram* hist;
	int h,s,v;
	int i;
	double d;

    hsv = ConvertBGR2HSV(correlogram->src);
    hsvq = quantizeHSV(hsv);
    numerator = (int *) calloc(correlogram->NumBins,sizeof(int));
    if (numerator==NULL)
    {
        puts("CalculateCorrelogram Failed: numerator calloc");
        puts(strerror(errno));
        exit(EXIT_FAILURE);
    }
	calcNumerator1(hsvq,correlogram->searchDistance,numerator);
	hist = CreateHSVHistogram(hsvq);

    for (i=0; i<correlogram->NumBins; i++)
	{
		// calculate index->h,s,v values to query histogram
		h = i/9;
		s = (i/3)%3;
		v = i%3;
		d = ((double)(8*correlogram->searchDistance*cvQueryHistValue_3D(hist,h,s,v)));
		d != 0 ? correlogram->FeatureVector[i] = ((double)numerator[i])/d : 0;
	}

    // clean up heap values before returning
    cvReleaseImage(&hsv);
    cvReleaseImage(&hsvq);
    cvReleaseHist(&hist);
    free(numerator);
}

/* Function CalculateCorrelogram:
Calculates the color correlogram
feature vector for a given input
image. Implements Autocorrelogram
function only.
  src: input img
  k: search distance

 */
void CalculateCorrelogram(Correlogram correlogram,double * featureVector)
{
	int * numerator = (int *) calloc(correlogram.NumBins,sizeof(int));
	int h,s,v;
	int i;
	double n,d;
	CvHistogram* hist;

	// calculate numerator section
	calcNumerator(correlogram,numerator);
	// calculate denominator section
	hist = CreateHSVHistogram(correlogram.hsv);

	for (i=0; i<correlogram.NumBins; i++)
	{
		// calculate index->h,s,v values to query histogram
		h = i/9;
		s = (i/3)%3;
		v = i%3;
		d = ((double)(8*correlogram.searchDistance*cvQueryHistValue_3D(hist,h,s,v)));
		d != 0 ? featureVector[i] = ((double)numerator[i])/d : 0;
	}

	// deallocate dynamic memory
	cvReleaseHist(&hist);
}


void calcNumerator1(IplImage* hsv,int searchDistance,int * numeratorVector)
{
	int i,j;
	int hBin,sBin,vBin;
	int index;
	CvScalar refColor;

	for (i=0; i<cvGetSize(hsv).height; i++)
	{
		for (j=0; j<cvGetSize(hsv).width; j++)
		{
			refColor = cvGet2D(hsv,i,j);
			hBin = calculateBin(refColor.val[0],MAXH/HBINS,MAXH);
			sBin = calculateBin(refColor.val[1],MAXSV/SVBINS,MAXSV);
			vBin = calculateBin(refColor.val[2],MAXSV/SVBINS,MAXSV);

			// assume array is indexed by (h,s,v).
			//Converting a 3 element index to single index by the following formula
			index = 9*hBin+3*sBin + vBin;
			numeratorVector[index]+=calcPixelCount1(hsv,searchDistance,j,i,refColor);
		}
	}
}

/* calcNumerator:
Calculates the numerator component of the feature vector
by calculating the number of pixels within a distance d
away from pixel p that have the same color as p.

@param[in] correlogram: correlogram structure to calculate
the numerator for.
 */
void calcNumerator(Correlogram correlogram,int * featureVector)
{
	int i;
	int j;
	// values to calculate feature vector index;
	int hBin,sBin,vBin;
	// value to hold calculated index value from bin values
	int index;
	CvScalar refColor;


	for (i=0; i<cvGetSize(correlogram.src).height; i++)
	{
		for (j=0; j<cvGetSize(correlogram.src).width; j++)
		{
			refColor = cvGet2D(correlogram.hsv,i,j);
			hBin = calculateBin(refColor.val[0],MAXH/HBINS,MAXH);
			sBin = calculateBin(refColor.val[1],MAXSV/SVBINS,MAXSV);
			vBin = calculateBin(refColor.val[2],MAXSV/SVBINS,MAXSV);

			// assume array is index by (h,s,v)
			index = 9*hBin+3*sBin + vBin;
			index >= 162 ? printf("index = %d\n",index):0;
			featureVector[index]+=calcPixelCount(correlogram,j,i,refColor);
		}
	}

}

int calcPixelCount1(IplImage * hsv, int searchDistance, int x,int y,CvScalar refColor)
{
	int pixCount = 0;
	int i;
	int width = cvGetSize(hsv).width;
	int height = cvGetSize(hsv).height;
	for (i = searchDistance ; i >= 1; i--)
	{
		// check that the horizontal count is within image range
		if ((y + i >= 0) && (y + i < height))
			pixCount += lambdaH(hsv,x-i,y+1,2*i,refColor);
		if ((y - i >= 0) && (y - i < height))
			pixCount += lambdaH(hsv,x-i,y-1,2*i,refColor);
		// check vertical count is within image range
		if ((x - i >= 0) && (x - i < width))
			pixCount += lambdaV(hsv,x-i,y-i+1,2*i,refColor);
		if ((x + i >= 0) && (x + i < width))
			pixCount += lambdaV(hsv,x+i,y-i+1,2*i,refColor);
	}
	return pixCount;
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
	for (i = correlogram.searchDistance ; i >= 1; i--)
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
			tmpPixel = cvGet2D( hsv, y+i, x );
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


	// Number of values between each quantization value
	const double hInterval = ((double) MAXH )/ ((double) HBINS);
	const double sInterval = ((double) MAXSV )/ ((double) SVBINS);
	const double vInterval = ((double) MAXSV )/ ((double) SVBINS);  // tmp quantized pixel values

	int tmpH,tmpS,tmpV;
	CvScalar oldPixel,newPixel;

	qhsv = cvCreateImage(cvSize(width,height),8,3);

	for (i=0; i<height; i++)
	{
		for (j=0; j<width; j++)
		{
			oldPixel = cvGet2D(image,i,j);

			tmpH = quantizePixel(oldPixel.val[0],hInterval,MAXH);
			tmpS = quantizePixel(oldPixel.val[1],sInterval,MAXSV);
			tmpV = quantizePixel(oldPixel.val[2],vInterval,MAXSV);

			newPixel = cvScalar(tmpH,tmpS,tmpV,0);

			cvSet2D(qhsv,i,j,newPixel);
		}
	}

	return qhsv;
}

int quantizePixel(double pixelValue,double interval,double maxValue)
{
	int newPixelValue;
	int bin = calculateBin(pixelValue,interval,maxValue);
	newPixelValue = interval/2 + interval *(bin);

	return newPixelValue;
}

int calculateBin(double pixelValue,double interval, double maxValue)
{
	int bin = ((int)pixelValue)/((int) interval);
	if (pixelValue == maxValue)
	{
		bin -=1;
	}
	return bin;
}
