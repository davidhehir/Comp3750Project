/* OpenCVHelper.h */
IplImage *ConvertBGR2HSV(IplImage* input);
CvHistogram* CreateHSVHistogram(IplImage* image);
int CompareScalar(CvScalar a, CvScalar b);
double Norm(double* vector);
