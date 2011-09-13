/**
    @file IOHelper.c

    @brief Contains various helper functions to facilitate various tasks such as gathering a list of files through to serialization/deserialization

    @author David Hehir

*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "CorrelogramType.h"
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <jansson.h>

int isDir(const char * dirName);
void FindImagesInFolders(char * folder,int *files, FileList ** list);
void CreateJSONCorrelogram(Correlogram * correlogram, const int bins,char * filename);
void CreateJSONMaxFeatureVector(double * MaxFeatureVector,const int bins,char * filename);
extern int errno;

/**
FindImagesInFolders:

    @param[in] folder: string specifying the folder that contains images to find file names
    @param[intout] files: number of files found (not initialized in function.
    @param[inout] list:  A list of files
*/
void FindImagesInFolders(char * folder,int *files, FileList ** list)
{
    DIR *pDIR;
    struct dirent *entry;
    // reset file counter
    char tmpFile[255] ="";

    if (pDIR=opendir(folder))
    {
        while (entry = readdir(pDIR))
        {
            if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..") != 0)
            {
               strcpy(tmpFile,folder);
               strcat(tmpFile,entry->d_name);
               // check if file name is actually a folder:
               if (isDir(tmpFile))
               {
                   strcat(tmpFile,"/");
                    FindImagesInFolders(tmpFile,files,list);
               }
               else
               {
                   if (strstr(entry->d_name,".jpg")!=0)
                   {
                    addFile(list,tmpFile);
                    (*files)++;
                   }
                }

            }
        }

    }

    closedir(pDIR);
    free(entry);
}

/** isDir
Checks if input directory name is a directory. This is most likely not portable
and may only work on linux (need to check this at a later date)
    @param[in] dirName: directory name to be checked
    @return 1 if directory otherwise 0
*/
int isDir(const char * dirName)
{
    struct stat statbuf;
    stat(dirName, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}

void CreateJSONCorrelogram(Correlogram * correlogram, const int bins,char * filename)
{
    json_t* corr = json_object();
    json_t* jsonFileName = json_string(correlogram->fileName);
    json_t* featureVector = json_array();
    json_t* vectorVals;
    int i;

    // Build feature vector json array
    for (i=0;i<bins;i++)
    {
        vectorVals = json_real(correlogram->FeatureVector[i]);
        if (json_array_append_new(featureVector,vectorVals))
        {
            printf("Cannot append %f to json array",correlogram->FeatureVector[i]);
            puts(strerror(errno));
            exit(1);
        }
    }
    // add both feature vector and file name to json object
    json_object_set_new(corr,"FileName",jsonFileName);
    json_object_set_new(corr,"FeatureVector",featureVector);

    json_dump_file(corr,filename,JSON_INDENT(2));

    //free correlogram
    free(correlogram->fileName);
    free(correlogram->FeatureVector);
    free(correlogram);
    // need to call jansson specific free
    json_object_clear(corr);
    //json_decref(corr);
    //free(corr);
    //free(fileName);
    //free(featureVector);
    //free(vectorVals);
}

void CreateJSONMaxFeatureVector(double * MaxFeatureVector,const int bins,char * filename)
{
    json_t* corr = json_object();
    json_t* jsonFileName = json_string("MaxFeatureVector");
    json_t* featureVector = json_array();
    json_t* vectorVals;
    int i;

    // Build feature vector json array
    for (i=0;i<bins;i++)
    {
        vectorVals = json_real(MaxFeatureVector[i]);
        if (json_array_append_new(featureVector,vectorVals))
        {
            printf("Cannot append %f to json array",MaxFeatureVector[i]);
            puts(strerror(errno));
            exit(1);
        }
    }
    // add both feature vector and file name to json object
    json_object_set_new(corr,"FileName",jsonFileName);
    json_object_set_new(corr,"FeatureVector",featureVector);

    json_dump_file(corr,filename,JSON_INDENT(2));


    // need to call jansson specific free
    json_object_clear(corr);

}
