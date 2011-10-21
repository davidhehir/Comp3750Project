import os


correlogram = '../../ColorCorrelogram/build/src/main'
featureMatcher = '../../FeatureMatcher/build/FeatureMatcher'
imagesFolder = '../../../../TestData/HousingMarket/docs/images/'
output = '../../../../TestData/HousingMarket/outputs/'
labels = '../../../../TestData/HousingMarket/ingest/DupTruth/labeltable/'

searchRadius = [1,2,3,4]
tauVals = [1,2,3,4]

for r in searchRadius:
  for t in tauVals:
    outputFolder = os.path.join(output,'r'+str(r)+'t'+str(t))
    if not os.path.isdir(outputFolder):
      os.mkdir(outputFolder)
    comparerCall = 'python comparer.py ' + correlogram + ' ' + featureMatcher + ' ' + imagesFolder +' ' +outputFolder + ' ' + str(r) + ' ' + str(t) + ' ' + labels + ' > ' + os.path.join(outputFolder,'result.txt')
    print comparerCall
    os.system(comparerCall) 	

