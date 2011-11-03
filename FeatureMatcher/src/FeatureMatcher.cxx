/**
*   @file FeatureMatcher.cxx
    @brief Calculates the matches given an input set of correlogram feature vectors
    @author David Hehir

    This program calculates the matches of feature vectors from an input JSON file.
    This JSON file is assumed to contain a max feature vector along with the set of
    feature vectors to match (along with file names as unique identifiers. The program
    takes 3 input command line arguments <Json Input File> <output json folder> <tau value>.
    The Json Input File is the file that contains all fo the data calculated from the colour
    correlogram program. The output json folder is the location where all the matches (serialized as
    individual json files) are written out to. Finally, the value of tau is a parameter that alters the
    search radius distance.


**/

#include "cv.h"
#include <math.h>
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
#include <boost/pending/disjoint_sets.hpp>
#include "DisjointSetWrapper.hxx"
#include <boost/unordered_map.hpp>


using namespace cv;
using namespace std;

void usage();
int getfiles(string dir,vector<string> &files,float** MaxFeatureVector);
void createFilePath(char * destination[], const char* directory, const char * file);
void createFilePath(char * destination[], string directory, const char * file);
int createMaxFeatureVector(float** featureVector, const char* filePath);
int SerializeResult(string matchFileName,vector<string> matchedFiles,char * outputFileName);
template <typename Rank, typename Parent>
boost::disjoint_sets<Rank,Parent> algo(Rank& r, Parent& p, std::vector<string>& elements);

vector<cv::Mat> buildMask(int images);

int errno;
const int BINS = 162;


int main(int argc, char** argv)
{
    int i,j;

    if (argc != 4)
    {
        usage();
        return -1;
    }

    //
    const float TAU = atof(argv[3]);
    string outputFolder = argv[2];

    time_t  t0, t1; /* time_t is defined on <time.h> and <sys/types.h> as long */
    clock_t c0, c1; /* clock_t is defined on <time.h> and <sys/types.h> as int */
    t0 = time(NULL);
    c0 = clock();

    cout << "begin (wall):            "<<  t0 << endl;
    cout <<"begin (CPU):             " <<c0 << endl;

    //1. Deserialize json files
    vector<string> files = vector<string>();
    string jsonFiles = argv[1];

    // array of max value for each bins
    float* MaxFeatureVector;
    // read json files from directory

    // set of all read in feature vectors
    vector<cv::Mat> dbFeatureVectors = vector<cv::Mat>();


    int fileIndex;
    vector<FeatureVector*> featureVectors = vector<FeatureVector*>();

    CreateFeatureVectors(jsonFiles,&MaxFeatureVector,&dbFeatureVectors,&featureVectors);

    cout << "Deserialization Complete. Deserialized :" << featureVectors.size() << " files" << endl;

    float tmpValue, L2Norm = 0.0;

    // Normalise all the feature vectors in dbFeatureVector
    // with the MaxFeatureVector
    for (i=0; i<featureVectors.size(); i++)
    {
        L2Norm = 0.0;
        // normalize files
        for (j=0; j<BINS; j++)
        {
            if (MaxFeatureVector[j] > 0.0)
            {
                tmpValue = dbFeatureVectors[i].at<float>(0,j)/MaxFeatureVector[j];
                dbFeatureVectors[i].row(0).col(j) = tmpValue;

            }

            L2Norm += pow(dbFeatureVectors[i].at<float>(0,j),2.0);
        }
        // Store L2 Norm for later date
        featureVectors[i]->L2Norm = sqrt(L2Norm);
    }

    float MaxFeatureVectorNorm = 0.0;

    // calculate MaxFeatureVector L2 Norm
    for (i=0; i<BINS; i++)
    {
        MaxFeatureVectorNorm += pow(MaxFeatureVector[i],2.0);
    }
    MaxFeatureVectorNorm = sqrt(MaxFeatureVectorNorm);

    FlannBasedMatcher matcher;

    std::vector<cv::DMatch > matches;
    vector<vector<cv::DMatch> > kMatches ;
    vector<vector<cv::DMatch> > rMatches;

    matcher.add(dbFeatureVectors);


    int vectorIndex;

    typedef std::map<string,std::size_t> rank_t; // => order on Element
    typedef std::map<string,string> parent_t;
    rank_t rank_map;
    parent_t parent_map;

    boost::associative_property_map<rank_t>   rank_pmap(rank_map);
    boost::associative_property_map<parent_t> parent_pmap(parent_map);
    vector<string> fileNameList = vector<string>();

    for (vectorIndex=0; vectorIndex<featureVectors.size(); vectorIndex++)
    {
        fileNameList.push_back(featureVectors[vectorIndex]->FileName);
    }

    boost::disjoint_sets<boost::associative_property_map<rank_t> ,boost::associative_property_map<parent_t> > dset = algo(rank_pmap, parent_pmap, fileNameList);

    for (vectorIndex=0; vectorIndex<featureVectors.size(); vectorIndex+=1)
    {
        //matcher.knnMatch(dbFeatureVectors[vectorIndex],kMatches,2);
        matcher.train();

        float searchRadius = TAU*featureVectors[vectorIndex]->L2Norm/MaxFeatureVectorNorm;
        //cout << "Image file " << featureVectors[vectorIndex]->FileName <<" Search Radius " << searchRadius <<
        //    "l2 norm " << featureVectors[vectorIndex]->L2Norm << " max vector l2 " << MaxFeatureVectorNorm<< endl;
        matcher.radiusMatch(dbFeatureVectors[vectorIndex],rMatches,searchRadius);

        vector<string> fileNames = vector<string>();
        string referenceFile = featureVectors[vectorIndex]->FileName;
        for (i=1; i<rMatches[0].size(); i++)
        {
            if (strcmp((featureVectors[rMatches[0][i].imgIdx]->FileName),((featureVectors[vectorIndex]->FileName) ))!= 0)
            {
                string foundValue = (featureVectors[rMatches[0][i].imgIdx]->FileName);

                if (dset.find_set(referenceFile) != dset.find_set(foundValue))
                {
                    // union sets
                    dset.union_set(foundValue,referenceFile);
                }
                string matchedFile(featureVectors[rMatches[0][i].imgIdx]->FileName);
                fileNames.push_back(matchedFile);
            }
            // serialise file using JANSSON
        }
    }

    Hash fileNameCluster;

    vector<string> parentList = vector<string>();
    for (vectorIndex=0; vectorIndex<featureVectors.size(); vectorIndex++)
    {
        string fileName = featureVectors[vectorIndex]->FileName;
        string parentName = dset.find_set(fileName);
        if (fileNameCluster.find(parentName)==fileNameCluster.end())
        {
            //cout << "added";
            parentList.push_back(parentName);
            // not in hash, add to hash
            AddNewDisjointSetWrapper(parentName, fileNameCluster);

            //cout << (fileNameCluster.at(parentName)).Elements[0] << endl;
        }
        if (fileName.compare(parentName) != 0)
        {
            // add file if the file name is not the parent
            AddNewElementToDisjointSet(parentName,fileName,fileNameCluster);
        }
    }

    for (vectorIndex=0; vectorIndex<parentList.size(); vectorIndex++)
    {
        //cout << "Parent = " << parentList[vectorIndex] << endl;
        DisjointSetWrapper wrapper = fileNameCluster[parentList[vectorIndex]];
        if (wrapper.Elements.size()> 1)
        {
            stringstream outputStream;
            outputStream << vectorIndex;
            string output = outputFolder;
            output.append(outputStream.str());
            output.append(".json");
            SerializeResult(parentList[vectorIndex],wrapper.Elements,(char*)output.c_str());
        }
    }
    // need to serialize clusters
    cout << endl << endl;


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

    for(i=0; i<images; i++)
    {
        cv::Mat mask (1,images,CV_32FC1);

        for(j=0; j<images; j++)
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

/** createFilePath:

*/
void createFilePath(char * destination[], string directory, const char * file)
{
    createFilePath(destination,directory.c_str(),file);
}

/** usage:
    @brief: Helper function to write out command line usage
*/
void usage()
{
    std::cout << "Usage ./FeatureMatcher <Json Input Folder> <output json folder> <tau value> " << std::endl;
}

/** SerializeResult:
    @brief Given a list of matched files, write them out to disk (as given)
    @param[in] matchFileName: Parent image file name of the set
    @param[in] matchedFiles: vector of file names that are to be written out to disk
    @param[in] outputFileName: output location where jansson will write the file to
    @return integer representing success of failure

*/
int SerializeResult(string matchFileName,vector<string> matchedFiles,char * outputFileName)
{
    // Since we are using a c library (jansson)
    // all strings need to be converted to
    // c strings (i.e char*) using the c_str() method
    int i;
    json_t* jsonFileMatches = json_object();
    json_t* jsonFileName = json_string((char *)matchFileName.c_str());
    json_t* jsonFileVector = json_array();
    json_t* jsonMatchedFile;

    for (i=0; i<matchedFiles.size(); i++)
    {

        jsonMatchedFile = json_string((char*)matchedFiles[i].c_str());
        if (json_array_append_new(jsonFileVector,jsonMatchedFile))
        {
            cout << "Cannot append " << matchedFiles[i] << "to json array" << endl;
            return 1;
        }
    }

    // add both feature vector and file name to json object
    json_object_set_new(jsonFileMatches,"FileName",jsonFileName);
    json_object_set_new(jsonFileMatches,"FileMatches",jsonFileVector);

    // write the serialized result out to file as specified
    json_dump_file(jsonFileMatches,outputFileName,JSON_INDENT(2));


    // need to call jansson specific free
    json_object_clear(jsonFileMatches);

    // success!
    return 0;
}

/* @brief function to build a set based on
    @param[in] r: disjoint set rank
    @param[in] p: disjoint set parent
    @param[in] elements: vector containing file names of images that are considered a match
    @returns: a new disjoint set containing the strings in elements

*/
template <typename Rank, typename Parent>
boost::disjoint_sets<Rank,Parent> algo(Rank& r, Parent& p, std::vector<string>& elements)
{
    boost::disjoint_sets<Rank,Parent> dsets(r, p);
    // build the set for each element within the input vector elements
    for (std::vector<string>::iterator e = elements.begin();
            e != elements.end(); e++)
    {

        dsets.make_set(*e);
    }

    return dsets;
}
