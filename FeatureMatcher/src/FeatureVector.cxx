

#include "FeatureVector.hxx"

//using namespace cv;
using namespace std;


FeatureVector::FeatureVector(string file,const double* maxFeatureVector)
{
  if(_deserializeFile(file,maxFeatureVector))
  {
        std::cout << "Error Deserializing file" << std::endl;
  }
}

int FeatureVector::_deserializeFile(string file,const double* maxFeatureVector)
{
  // Read in file, deserialize vector to object
  json_t *json;
  json_error_t error;
  json_t * jsonFeatureVector;
  json_t * jsonFileName;
  int i;
  vector<double> tmpFeatureVector = vector<double>();
  char* cFile = (char*)file.c_str();

  json = json_load_file(cFile,0, &error);

  if(!json) {
    std::cout << "Error readining in file " << file << " jansson error: " << error.text << " at line " << error.line << std::endl;
    return 1;
  }
  // get the two pieces of information stored.
  // currently keys are hard coded but this seems brittle
  // i.e. these values are set by a different application (in this case
  // ColorCorrelogram, and should instead be set in some form of
  // configuration file.

  // FeatureVector: json array
  // FileName: json string
  jsonFeatureVector = json_object_get(json,"FeatureVector");
  jsonFileName = json_object_get(json,"FileName");
  _fileName = json_string_value(jsonFileName);


  for (i=0;i<json_array_size(jsonFeatureVector);i++)
  {
    tmpFeatureVector.push_back(json_real_value(json_array_get(jsonFeatureVector,i))/maxFeatureVector[i]);
  }

  _featureVector = cv::Mat(tmpFeatureVector,true);
  if (_featureVector.empty())
  {
    std::cout << "Failed to create Feature Vector with file name " << file << std::endl;
    return 1;
  }


  return 0;
}

  // Public accessor methods
// TODO: check these are read only!
cv::Mat FeatureVector::GetVectorValues(){ return _featureVector;}
std::string FeatureVector::GetFileName(){return _fileName;}
