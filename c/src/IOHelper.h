void FindImagesInFolders(char * folder,int *files, FileList ** list);
int isDir(const char * dirName);
void CreateJSONCorrelogram(Correlogram * correlogram, const int bins,char * filename);
void CreateJSONMaxFeatureVector(double * MaxFeatureVector,const int bins,char * fileName);
