#ifndef CorrelogramType
#define CorrelogramType

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

void deleteList(FileList ** list);
CorrelogramArray newArray(int numElements);
void deleteArray(CorrelogramArray ca);
int correlogramArrayLength(CorrelogramArray ca);
Correlogram** correlogramArrayPtr(CorrelogramArray ca);
void addFile(FileList**,char*);
#endif
