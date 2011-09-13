/* OpenCVHelper.h */
IplImage *ConvertBGR2HSV(IplImage* input);
CvHistogram* CreateHSVHistogram(IplImage* image);
int CompareScalar(CvScalar a, CvScalar b);
double Norm(double* vector,int size);
double Distance(double* vector1,double* vector2,int size);
