
void CalculateCorrelogram();
static int* calcNumerator(Correlogram correlogram,int* featureVector);
int calcPixelCount(Correlogram correlogram,int x,int y,CvScalar refColor);
int lambdaH(IplImage* hsv,int x,int y,int k, CvScalar refColor);
int lambdaV(IplImage* hsv,int x,int y,int k, CvScalar refColor);
IplImage* quantizeHSV(IplImage* image);
double quantizePixel(double pixelValue,double interval);
