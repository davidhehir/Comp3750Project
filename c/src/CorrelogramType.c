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
	IplImage* src; // brg representation of image (is this needed?)
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
