#include <stdlib.h>
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "OpenCVHelper.h"
#include "CorrelogramType.h"
#include "ColorCorrelogram.h"
#include <time.h>
#include <dirent.h>


// currently main is just a test shell to
// quickly test some basic functionality
int main(int argc, char *argv[])
{
    DIR *pDIR;
    struct dirent *entry;
    int files=0;
    FileList *list = NULL;
    CorrelogramArray * correlograms;
    CorrelogramCollection collection;
    int NumBins = 162;
    char* dir = argv[1];
    char tmpFile[255] ="";
    if (pDIR=opendir(dir))
    {
        while (entry = readdir(pDIR))
        {
            if (strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..") != 0)
            {
               strcpy(tmpFile,dir);
               strcat(tmpFile,entry->d_name);
                // foreach file in the directory. create a correlogram struct
                // and add it to the Correlogram Array
                //printf("list file=%s address %p\n",entry->d_name,list);
                addFile(&list,tmpFile);

                //strcat(list->fileName,entry->d_name);
                //addFile(&list,entry->d_name);
                printf("full name %s\n",list->fileName);
                files++;
            }
        }

    }

    //correlograms = (newArray(files));
    correlograms = (CorrelogramArray *) malloc(sizeof(CorrelogramArray));

    correlograms->array = (Correlogram**)malloc(sizeof(Correlogram*)*files);

    correlograms->elements = files;
    FileList* i=list;
    int index =0;
    Correlogram * tmp;
    while (i!= NULL)
    {
        tmp = (Correlogram *) malloc(sizeof(Correlogram));
        tmp->fileName = (char *) malloc((strlen(i->fileName)+1) );
        printf("length %d\n",strlen(i->fileName));
        if (tmp==NULL)
        {
            printf("Malloc failed at index %d: tmp",index);
            exit(1);
        }
        strcpy(tmp->fileName,i->fileName);
        //tmp->fileName = list->fileName;
        correlograms->array[index] = tmp;
        printf("file name=%s",correlograms->array[index]->fileName);
        i = i->next;
        index++;
    }
    //deleteList(&list);

    collection.correlograms = correlograms;
    collection.NumBins = NumBins;
    collection.searchDistance = 1;
    // todo need to set this value to 1 (or maybe -1 as a flag
    collection.MaxFeatureVector = (double*) calloc(NumBins,sizeof(double));



    printf("number of read files = %d\n",files);
    int j;
    for (index = 0;index <collection.correlograms->elements;index++)
    {

            CalculateCorrelogram(collection.correlograms->array[index],collection.NumBins,collection.searchDistance,&(collection.MaxFeatureVector));

        printf("Norm for %s = %f\n",collection.correlograms->array[index]->fileName,Norm(collection.correlograms->array[index]->FeatureVector,collection.NumBins));

           /* for (j = 0;j<162;j++)
            {
                printf("i:%f\n",collection.correlograms->array[index]->FeatureVector[j]);
            }*/
    }

    //free(tmp);
    //deleteList(&list);
    free(entry);
    closedir(pDIR);

/*	IplImage* image=0;
	//IplImage* image2 = cvLoadImage();
	IplImage* hsvq;
	CvScalar scalar = cvScalar(0,0,0,0);
	double features [162] = {0.0};//= (double*)calloc(162,sizeof(double));
	double maxFeatures [162] = {0.0};

	Correlogram c = {argv[1],0,features};
    clock_t start= clock();
    clock_t diff;

    CalculateCorrelogram(&c,162,1,maxFeatures);
    diff = clock()-start;
    double sum2 = Norm(c.FeatureVector,162);
    printf("L2 Distance= %f\n",sum2);
    printf("Diff = %f\n",Distance(c.FeatureVector,c.FeatureVector,162));
    int msec = diff *1000/ CLOCKS_PER_SEC;
    printf("Time taken %d.%d msec \n",msec/1000,msec%1000);
*/
    //free(features);
    //cvReleaseHist(&hist);

}
