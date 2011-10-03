#include "cv.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <jansson.h>
#include <ctime>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <sys/types.h>
#include "debug.hpp"
#include "FeatureVector.hxx"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <flann/flann.hpp>
//#include <flann/io/hdf5.h

//#include "FeatureVector.hpp"

using namespace cv;
using namespace std;

void usage();
int getfiles(string dir,vector<string> &files,float** MaxFeatureVector);
void createFilePath(char * destination[], const char* directory, const char * file);
void createFilePath(char * destination[], string directory, const char * file);
int createMaxFeatureVector(float** featureVector, const char* filePath);

vector<cv::Mat> buildMask(int images);

int errno;



int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage();
        return -1;
    }
     time_t  t0, t1; /* time_t is defined on <time.h> and <sys/types.h> as long */
  clock_t c0, c1; /* clock_t is defined on <time.h> and <sys/types.h> as int */
  t0 = time(NULL);
  c0 = clock();

  cout << "begin (wall):            "<<  t0 << endl;
  cout <<"begin (CPU):             " <<c0 << endl;

    //1. Deserialize json files
    vector<string> files = vector<string>();
    string jsonFiles = argv[1];
    // holder for feature vector values
    // bins is currently hard coded, can I expose this somewhere else?
    float* MaxFeatureVector = (float*) malloc(sizeof(float)*162);
    // read json files from directory

    if (getfiles(jsonFiles,files,&MaxFeatureVector))
    {
        cout << "Cannot read files from directory correctly" << endl;
        return 1;
    }
    vector<cv::Mat> dbFeatureVectors = vector<cv::Mat>();

    int fileIndex;
    vector<FeatureVector*> featureVectors = vector<FeatureVector*>();
    cout << "Deserializing files [";
    for (fileIndex=0;fileIndex<files.size();fileIndex++)
    {
        featureVectors.push_back(CreateFeatureVector(files[fileIndex],MaxFeatureVector,fileIndex,&dbFeatureVectors));
        if (fileIndex % 1000==0) { cout << fileIndex << endl;}
        //cout << "index " << fileIndex << endl;
    }
    cout << "]" << endl;

    int i;






    FlannBasedMatcher m;
    vector< DMatch>  ma;
/*
    m.match(dbDescriptors.row(0),dbDescriptors,ma);

        for (i=0;i<ma.size();i++)
        {
            cout << "file " << ma[i].trainIdx << "or" << ma[i].imgIdx << endl;
            cout << featureVectors[ma[i].imgIdx]->FileName << endl;
            //cout << " " << featureVectors[matches[i].trainIdx]->FileName  << " or " << featureVectors[matches[i].imgIdx]->FileName<< endl;

        }

*/
    FlannBasedMatcher matcher;
    cv::BruteForceMatcher<cv::L2<float> > bruteMatcher;
    bruteMatcher.add(dbFeatureVectors);

    matcher.add(dbFeatureVectors);

    matcher.train();
    std::vector<cv::DMatch > matches;
    vector<DMatch> bruteMatches;



    int index;
/*
    for (index=0;index<dbFeatureVectors[0].size[0];index++)
    {
        cout << (dbFeatureVectors[0]).at<float>(index,0) << endl;
    }*/



 //   for (fileIndex=0;fileIndex<1;fileIndex++)
   // {
   vector<cv::Mat> mask = buildMask(dbFeatureVectors.size());
    vector<cv::Mat> tmpMask =  vector<cv::Mat>();
    tmpMask.push_back(mask[0]);
   for (i=0;i<mask.size();i++)
   {
  //     cout << mask[i].row(0).col(0) << " " << mask[i].row(0).col(1) << " " << endl;
   }

    cout << featureVectors[1]->FileName << endl;

        matcher.match(dbFeatureVectors[1],matches,mask);
        vector<vector<cv::DMatch> > kMatches ;
        matcher.knnMatch(dbFeatureVectors[1],kMatches,50,tmpMask);

        for (i=0;i<kMatches[0].size();i++)
        {
            cout << "file " << kMatches[0][i].trainIdx << "or " << kMatches[0][i].imgIdx << endl;
            cout << "file path " << featureVectors[kMatches[0][i].imgIdx]->FileName << endl;
        }
        //bruteMatcher.match (dbDescriptors,bruteMatches);
        if (fileIndex % 1000==0) { cout << fileIndex << endl;}
       // int i;

       cout << "number of matches" << matches.size() << endl;
        cout << "k matches " << kMatches[0].size() << endl;
        for (i=0;i<matches.size();i++)
        {
            cout << "file " << matches[i].trainIdx << "or" << matches[i].imgIdx << "with query " << matches[i].queryIdx<< endl;
            int j;
            //for (j=0;j<matcher.getTrainDescriptors()[matches[i].trainIdx].size().width;j++)
            //{
            //    cout << matcher.getTrainDescriptors()[matches[i].queryIdx].row(0).col(j) << " " << matcher.getTrainDescriptors()[matches[i].trainIdx].row(0).col(j) << endl;
            //}
            cout << featureVectors[matches[i].trainIdx]->FileName << endl;
            //cout << " " << featureVectors[matches[i].trainIdx]->FileName  << " or " << featureVectors[matches[i].imgIdx]->FileName<< endl;
        }
        cout << endl << endl;
/*
        for (i=0;i<bruteMatches.size();i++)
        {
             cout << "brute file " << bruteMatches[i].trainIdx << "or" << bruteMatches[i].imgIdx;
            cout << " " << featureVectors[bruteMatches[i].imgIdx]->FileName  << " or " << featureVectors[bruteMatches[i].imgIdx]->FileName<< endl;

        } */
    // }
    FileStorage fs("test.yml",FileStorage::WRITE);


    // loop over files, deserialize

    //2. Normalize using the MaxVector

    //3. Match vectors using FLANN

    //4. Output results


    //clean up

    while(!featureVectors.empty())
    {
        free(featureVectors.back());
        featureVectors.pop_back();
    }
    free(MaxFeatureVector);




  t1 = time(NULL);
  c1 = clock();
    cout << "end (Wall):              " << t1 << endl;
    cout << "end (CPU):               " << c1 << endl;
    cout << "elapsed wall clock time: " << (t1 - t0) << endl;
    cout << "\telapsed CPU time:        "<< (c1 - c0)/CLOCKS_PER_SEC << endl;

}


int getfiles(string dir,vector<string> & files, float ** MaxFeatureVector)
{
    DIR *dp;
    struct dirent *dirp;
    char* fileName= (char *) malloc(sizeof(char)*255);
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL)
    {
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
    free(fileName);
    closedir(dp);
    free(dirp);
    return 0;
}

int createMaxFeatureVector(float** featureVector, const char* filePath)
{
    json_error_t jsonError;
    json_t* jsonFeatureVector;
    json_t* maxJson = json_load_file(filePath,0,&jsonError);
    if(!maxJson)
    {
        cout << "Error reading in file " << filePath<< " jansson error: " << jsonError.text << " at line " << jsonError.line << std::endl;
        return 1;
    }

    int i;
    jsonFeatureVector = json_object_get(maxJson,"FeatureVector");
    for (i=0; i<json_array_size(jsonFeatureVector); i++)
    {
        (*featureVector)[i] = (float) json_real_value(json_array_get(jsonFeatureVector,i));

    }
    // clean up pointers
    json_decref(jsonFeatureVector);

    json_decref(maxJson);
    return 0;
}


vector<cv::Mat> buildMask(int images)
{
    vector<cv::Mat> maskVec=vector<cv::Mat>();

    int i,j;

    for(i=0;i<images;i++)
    {
        cv::Mat mask (1,images,CV_32FC1);

        for(j=0;j<images;j++)
        {
            mask.row(0).col(j)= (i==j ? 0.0:1.0);

        }

        maskVec.push_back(mask);
    }

    return maskVec;
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
