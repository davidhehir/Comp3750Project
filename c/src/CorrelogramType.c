/**
    @file CorrelogramType.c

    This file contains several data structures used in batch calculation
    of color correlograms. The correlogram structure has been kept to a
    minimum for memory constrains since this is the structure that will
    be serialized to disk for use with feature matching (i.e. use with
    FLANN application).


    @brief Contains data structures to calculate the color correlogram
    of several images. Contains several helper functions to create
    add and clean up memory for each data structure

    @author David Hehir

    @version 0.1
*/

#include <stdlib.h>
#include <stdio.h>
#include "cv.h"

typedef struct FileList
{
    char* fileName;
    struct FileList* next;
} FileList;

typedef struct Correlogram
{
    char* fileName; // unique identifier
	//IplImage* src; // brg representation of image (is this needed?)
	double* FeatureVector;

} Correlogram;

typedef struct CorrelogramArray
{
    Correlogram** array;
    int elements;
} CorrelogramArray;

typedef struct CorrelogramCollection
{
    CorrelogramArray* correlograms;
    double* MaxFeatureVector;
    double tau;     // value used to threshold feature vectors
    int NumBins;
    int searchDistance; // how far away from reference pixel to search
} CorrelogramCollection;

CorrelogramArray newArray(int);
void deleteArray(CorrelogramArray);
int correlogramArrayLength(CorrelogramArray);
Correlogram** correlogramArrayPtr(CorrelogramArray);
void addFile(FileList**,char*);
void deleteList(FileList ** list);

CorrelogramArray newArray(int numElements)
{
    Correlogram** array = (Correlogram **) malloc(sizeof(Correlogram*)*numElements);
    CorrelogramArray ca = {array,numElements};
    return ca;
}

void deleteArray(CorrelogramArray ca)
{
    free(ca.array);
}

int correlogramArrayLength(CorrelogramArray ca)
{
    return ca.elements;
}
Correlogram** correlogramArrayPtr(CorrelogramArray ca)
{
    return ca.array;
}





void addFile(FileList ** list,char* file)
{
    FileList * current = (FileList*) malloc(sizeof(FileList));
    current->fileName = (char*) malloc(strlen(file)+1);
    strcpy(current->fileName,file);
    current->next = *list;
    *list = current;
}

void deleteList(FileList ** list)
{
    FileList* entry;
    FileList* saved;
    if ((*list) != NULL)
    {
        entry= (*list);
        do
        {
            saved = entry->next;
            free(entry->fileName);
            free(entry);
            entry = saved;
        } while(entry!= NULL);
    }
}
