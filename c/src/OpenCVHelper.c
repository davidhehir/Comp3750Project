#include "cv.h"
#include <stdio.h>
/* @file OpenCVHelper.c  
Container for various opencv related functions
that will be used throughout different program files

@author David Hehir  
*/


/* ConvertBGR2HSV:
A helper function that creates an new image
containing the hsv representive of the input 
image
@param[in] input Pointer to IplImage that is to be converted

 */
IplImage* ConvertBGR2HSV(IplImage* input)
{
  int i = input->width;
  IplImage* img = cvCreateImage(cvSize(img->width,input->height),IPL_DEPTH_8U, 3);
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

