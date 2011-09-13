int lambdaH(IplImage* hsv,int x,int y,int k, CvScalar refColor);
int lambdaV(IplImage* hsv,int x,int y,int k, CvScalar refColor);
IplImage* quantizeHSV(IplImage* image);
int quantizePixel(double pixelValue,double interval,double maxValue);
int calculateBin(double pixelValue,double interval, double maxValue);
void CalculateCorrelogram(Correlogram* correlogram, int numBins,int searchDistance,double** maxFeatures);
int calcPixelCount(IplImage * hsv, int searchDistance, int x,int y,CvScalar refColor);
void calcNumerator(IplImage* hsv,int searchDistance,int * numeratorVector);
