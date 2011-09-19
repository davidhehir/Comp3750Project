#include "cv.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <jansson.h>

#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include "debug.hpp"
#include "FeatureVector.hxx"

//#include "FeatureVector.hpp"

using namespace cv;
using namespace std;

void usage();
int getfiles(string dir,vector<string> &files,double** MaxFeatureVector);
void createFilePath(char * destination[], const char* directory, const char * file);
void createFilePath(char * destination[], string directory, const char * file);
int createMaxFeatureVector(double** featureVector, const char* filePath);
int errno;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    usage();
    return -1;
  }
      Mat M(7,7,CV_32FC2,cv::Scalar(1,3));

  //1. Deserialize json files
  vector<string> files = vector<string>();
  string jsonFiles = argv[1];
  // holder for feature vector values
  // bins is currently hard coded, can I expose this somewhere else?
  double* MaxFeatureVector = new double[162];
  // read json files from directory

  if (getfiles(jsonFiles,files,&MaxFeatureVector))
  {
    cout << "Cannot read files from directory correctly" << endl;
    return 1;
  }

  FeatureVector v(files[0],MaxFeatureVector);

    cout << "File Name = " << v.GetFileName() << endl;

    int k ;
    for (k=0;k<162;k++)
    {
        cout << v.GetVectorValues().col(0).row(k) << endl;
    }
  // loop over files, deserialize

  //2. Normalize using the MaxVector

  //3. Match vectors using FLANN

  //4. Output results

}


int getfiles(string dir,vector<string> & files, double ** MaxFeatureVector)
{
  DIR *dp;
  struct dirent *dirp;
  char* fileName= new char[255];
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name,".") != 0 && (strcmp(dirp->d_name,"..") ) != 0)
    {

        #ifdef DEBUG
          //cout << " File " << dirp->d_name << endl;
        #endif
        // reset tmp filename variable
        strcpy(fileName,"");
        createFilePath(&fileName,dir,dirp->d_name);

        if (strcmp(dirp->d_name,"MaxFeatureVector.json") == 0)
        {
            if (createMaxFeatureVector(MaxFeatureVector,fileName))
                {
                    cout << "Error reading in max feature vector json file" << std::endl;
                    return 1;
                }
        }
        else
        {
            //cout << fileName << endl;
            files.push_back(string(fileName));
        }
    }
  }
  closedir(dp);
  free(dirp);
  return 0;
}

int createMaxFeatureVector(double** featureVector, const char* filePath)
{
    json_error_t jsonError;
        json_t* jsonFeatureVector;
        json_t* maxJson = json_load_file(filePath,0,&jsonError);
        if(!maxJson) {
            cout << "Error reading in file " << filePath<< " jansson error: " << jsonError.text << " at line " << jsonError.line << std::endl;
            return 1;
        }

        int i;
        jsonFeatureVector = json_object_get(maxJson,"FeatureVector");
        for (i=0;i<json_array_size(jsonFeatureVector);i++)
        {
            (*featureVector)[i] = json_real_value(json_array_get(jsonFeatureVector,i));
            cout << "Vector val " << (*featureVector)[i] << endl;
        }
    // clean up pointers
    json_object_clear(maxJson);

    return 0;
}



void createFilePath(char * destination[], const char* directory, const char * file)
{
    // get directory part.
    memcpy(*destination,directory,strlen(directory)+1);
    // check that there is a slash at the end (to ensure well formed path)

    (*destination)[strlen(directory)-1] == '/' ? NULL: strcat((*destination),"/");

    // concat the file part to the end
    strcat((*destination),file);
}

void createFilePath(char * destination[], string directory, const char * file)
{
    createFilePath(destination,directory.c_str(),file);
}

void usage()
{
  std::cout << "Usage ./FeatureMatcher <Json Folder> " << std::endl;
}
