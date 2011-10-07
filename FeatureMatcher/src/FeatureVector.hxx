/** Simple container for a Feature Vector
 *  The main values are to be stored in a CvMat (OpenCV matrix container)
 * such that the FLANN module can be easily used
 */

#include <vector>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <jansson.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <sys/types.h>
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/highgui/highgui.hpp"

//#include <cv.h>
//#include <highgui.h>

struct FeatureVector
{
    char FileName[255];
    float L2Norm;
    //cv::Mat * FeatureVector;
    int vectorIndex;
};

FeatureVector* CreateFeatureVector(std::string,const float*,int, std::vector<cv::Mat> *);

int _deserializeFile(std::string file, const double* maxFeatureVector);

/*class FeatureVector
{
public:
    FeatureVector(std::string file,const double* maxFeatureVector);
    // Public accessor methods
    // TODO: check these are read only!
    cv::Mat GetVectorValues();
    std::string GetFileName();
private:
    int _deserializeFile(std::string file, const double* maxFeatureVector);
    cv::Mat _featureVector;
    std::string _fileName;
};

*/
