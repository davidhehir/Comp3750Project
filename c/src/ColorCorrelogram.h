typedef struct Correlogram
{
  IplImage* src; // brg representation of image (is this needed?)
  IplImage* hsv; // hsv representation of image
  const int searchDistance; // how far away from reference pixel to search
  int* FeatureVector;
} Correlogram;


void CalculateCorrelogram(Correlogram correlogram,double * featureVector);
void calcNumerator(Correlogram correlogram,int* featureVector);
int calcPixelCount(Correlogram correlogram,int x,int y,CvScalar refColor);
int lambdaH(IplImage* hsv,int x,int y,int k, CvScalar refColor);
int lambdaV(IplImage* hsv,int x,int y,int k, CvScalar refColor);
IplImage* quantizeHSV(IplImage* image);
int quantizePixel(double pixelValue,double interval,double maxValue);
int calculateBin(double pixelValue,double interval, double maxValue);
