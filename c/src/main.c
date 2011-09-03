#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include "OpenCVHelper.h"
#include "ColorCorrelogram.h"


// currently main is just a test shell to
// quickly test some basic functionality
int main()
{
	IplImage* image = cvLoadImage("../../TestFiles/landscape.jpg",3);
	IplImage* image2 = cvLoadImage();
	IplImage* hsvq;
	CvScalar scalar = cvScalar(0,0,0,0);
	double features [162] = {0.0};//= (double*)calloc(162,sizeof(double));
	double features2 [162] = {0.0};
	Correlogram c = {image,ConvertBGR2HSV(image),1,features2,162};


	CvHistogram* hist=CreateHSVHistogram(c.hsv);
	int h,s,v;
	int i,j;
	CvScalar pix;
	hsvq = quantizeHSV(c.hsv);
	c.hsv = hsvq;
	//calcNumerator(c,features);
	CalculateCorrelogram(c,features);
    for (i=0;i<sizeof(features)/sizeof(double);i++)
    {
        printf("a");
        h=i/9;
        v=i%3;
        s = (i/3)%3;
        printf("(%d,%d,%d)=%f  index = %d\n",h,s,v,features[i],i);
    }
    double sum = Norm(features,162);
    CalculateCorrelogram1(&c);
    double sum2 = Norm(c.FeatureVector,162);
    printf("L2 Distance=%f new function = %f\n",sum,sum2);


    //free(features);
    //cvReleaseHist(&hist);

}
