#include <stdlib.h>
#include <stdio.h>
#include "cv.h"
#include "highgui.h"
#include "OpenCVHelper.h"
#include "CorrelogramType.h"
#include "ColorCorrelogram.h"
#include "IOHelper.h"
#include <time.h>
#include <dirent.h>


void usage();
// currently main is just a test shell to
// quickly test some basic functionality
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        usage();
        return 1;
    }
    DIR *pDIR;
    struct dirent *entry;
    int files=0;
    FileList *list = NULL;
    CorrelogramArray * correlograms;
    CorrelogramCollection collection;
    int NumBins = 162;
    char* dir = argv[1];
    char * outputFolder = argv[2];
    const int RADIUS = atoi(argv[3]);
    char tmpFile[255] ="";
    time_t t0,t1;
    clock_t c0,c1;
    t0 = time(NULL);
    c0 = clock();

    printf ("\tbegin (wall):            %ld\n", (long) t0);
    printf ("\tbegin (CPU):             %d\n", (int) c0);

    if (!isDir(outputFolder))
    {
        printf("Failure:Output folder %s does not exist\n",outputFolder);
        exit(1);
    }
    FindImagesInFolders(argv[1],&files,&list);

    /*
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

    } */

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
        if (tmp==NULL)
        {
            printf("Malloc failed at index %d: tmp",index);
            exit(1);
        }
        strcpy(tmp->fileName,i->fileName);
        //tmp->fileName = list->fileName;
        correlograms->array[index] = tmp;
        //printf("\n\nfile name = %s\n\n",tmp->fileName);
        //printf("file name=%s",correlograms->array[index]->fileName);
        i = i->next;
        index++;
    }
    deleteList(&list);

    collection.correlograms = correlograms;
    collection.NumBins = NumBins;
    collection.searchDistance = RADIUS;
    // todo need to set this value to 1 (or maybe -1 as a flag
    collection.MaxFeatureVector = (double*) calloc(NumBins,sizeof(double));



    printf("number of read files = %d\n",files);
    int j;
    //char * outputFolder = "json/";
    char fileName[255] ="";
    char stringIndex[10]="";
    for (index = 0; index <collection.correlograms->elements; index++)
    {

        CalculateCorrelogram(collection.correlograms->array[index],collection.NumBins,collection.searchDistance,&(collection.MaxFeatureVector));
        strcpy(fileName,outputFolder);
        sprintf(stringIndex, "%d", index);
        strcat(fileName,stringIndex);
        strcat(fileName,".json");
        //        CreateJSONCorrelogram(collection.correlograms->array[index], collection.NumBins,fileName);
        //  printf("Norm for %s = %f\n",collection.correlograms->array[index]->fileName,Norm(collection.correlograms->array[index]->FeatureVector,collection.NumBins));

        /* for (j = 0;j<162;j++)
         {
             printf("i:%f\n",collection.correlograms->array[index]->FeatureVector[j]);
         }*/
         if (index % 7000 == 0)
         {
             printf("index=%d",index);
         }
    }
    strcpy(fileName,outputFolder);
    strcat(fileName,"MaxFeatureVector.json");

    SerializeAllToJson(collection.correlograms->array,collection.MaxFeatureVector,NumBins,fileName,collection.correlograms->elements);
    //CreateJSONMaxFeatureVector(collection.MaxFeatureVector,collection.NumBins,fileName);

    free(collection.correlograms->array);
    free(collection.MaxFeatureVector);
    free(collection.correlograms);
    t1 = time(NULL);
    c1 = clock();

    printf ("\tend (wall):              %ld\n", (long) t1);
    printf ("\tend (CPU);               %d\n", (int) c1);
    printf ("\telapsed wall clock time: %ld\n", (long) (t1 - t0));
    printf ("\telapsed CPU time:        %f\n", (float) (c1 - c0)/CLOCKS_PER_SEC);


    //free(tmp);
    //deleteList(&list);


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


void usage()
{
    printf("Usages ./main <Input Image folder> <output folder> <search radius (integer)> \n");
}
