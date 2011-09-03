#include "cv.h"
#include <stdio.h>
#include <math.h>
/* @file OpenCVHelper.c
Container for various opencv related functions
that will be used throughout different program files

@author David Hehir
*/

IplImage* ConvertBGR2HSV(IplImage*);
int CompareScalar(CvScalar,CvScalar);
CvHistogram* CreateHSVHistogram(IplImage*);
double Norm(double*,int);


/* Norm:
Calculates the L2 Distance (Euclidean Norm) of
the input vector.

@param[in] vector: input vector
@return L2 Distance
*/
double Norm(double* vector,int size)
{
    double sum=0;
    int i;
    for (i=0;i<size;i++)
    {
        sum += vector[i] != 0 ? pow(vector[i],2.0) : 0;
    }

    return sqrt(sum);
}


/* FeatureVectorDistance:

*/
double Distance(double* vector1,double* vector2,int size)
{
    double sum=0;
    int i;
    for (i=0;i<size;i++)
    {
        sum += pow(vector1[i]-vector2[i],2.0);
    }
    return sqrt(sum);

}
/* ConvertBGR2HSV:
A helper function that creates an new image
containing the hsv representive of the input
image
@param[in] input Pointer to IplImage that is to be converted

 */
IplImage* ConvertBGR2HSV(IplImage* input)
{
  int i = input->width;
  CvSize imgSize = cvSize(input->width,input->height);
  IplImage* img = cvCreateImage(imgSize,IPL_DEPTH_8U, 3);
  // Convert from BGR to HSV
  cvCvtColor(input,img,CV_BGR2HSV);
  return img;
}


/* CompareScalar:
Compares the values within a scalar struct
to check if the values are equal.
INPUT:
@param[in] a the first cvScalar
@param[in] b the second cvScalar to compare
@return boolean value, true if the scalars are the same, otherwise false.
 */
int CompareScalar(CvScalar a, CvScalar b)
{
  /* Boolean return value*/
  int same = 1;
  const int MAXINDEX = 3;
  int i;

  /*Two scalars are the same if the values of each element
   in CvScalar->val are equal (by value not reference)
   */
  for (i=0; i<=MAXINDEX;i++)
    {
      if (a.val[i] != b.val[i])
	{
	  same = 0;
	  break;
	}
    }
  return same;
}

/* CreateHSVHistogram:
creates a histogram from a 3 channel hsv image

@param[in] image: input image source. Assumed to be
in HSV form
@param[inout] dst: destination array for histogram data
 */
CvHistogram* CreateHSVHistogram(IplImage* image)
{
  // CvMat value for each color space plane.
  IplImage* h = cvCreateImage(cvGetSize(image),8,1);
  IplImage* s = cvCreateImage(cvGetSize(image),8,1);
  IplImage* v = cvCreateImage(cvGetSize(image),8,1);
  IplImage* planes[] = {h,s,v};

  // the number of histogram bins for each respective channel.
  int h_bins = 18;
  int s_bins = 3;
  int v_bins = 3;
  int bins[] = {h_bins, s_bins, v_bins};
  // define the range of values for each of the channels.
  float hRange[] = {0,180};
  float sRange[] = {0,255};
  float vRange[] = {0,255};
  float *ranges[] = { hRange, sRange, vRange};

  CvHistogram* histogram;

  cvCvtPixToPlane(image,h,s,v,0);
  histogram = cvCreateHist(3,bins,CV_HIST_ARRAY,ranges,1);
  cvCalcHist(planes,histogram,0,0);

  return histogram;
}
