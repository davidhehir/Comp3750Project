#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include "OpenCVHelper.h"
#include "ColorCorrelogram.h"


// currently main is just a test shell to
// quickly test some basic functionality
int main()
{
	IplImage* image = cvLoadImage("../../TestFiles/black.jpg",3);
	IplImage* hsvq;
	CvScalar scalar = cvScalar(0,0,0,0);
	int a[3] = {1,2,3};
	double* features = (double*)calloc(162,sizeof(double));
	Correlogram c = {image,ConvertBGR2HSV(image),1,a};


	CvHistogram* hist=CreateHSVHistogram(c.hsv);
	int h,s,v;
	int i,j;
	CvScalar pix;
	hsvq = quantizeHSV(c.hsv);
	c.hsv = hsvq;
	//calcNumerator(c,features);
	CalculateCorrelogram(c,features);
    printf("bins =%d\n",sizeof(features)/sizeof(double));
    for (i=0;i<sizeof(features)/sizeof(double);i++)
    {
        printf("a");
        h=i/9;
        v=i%3;
        s = (i/3)%3;
        printf("(%d,%d,%d)=%f  index = %d\n",h,s,v,features[i],i);
    }
    double sum = Norm(features);
    printf("L2 Distance=%f",sum);
	printf("hello");

    free(features);
    cvReleaseHist(&hist);

}
