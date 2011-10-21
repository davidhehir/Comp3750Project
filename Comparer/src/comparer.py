#!/usr/bin/env python
# This program adds up integers in the command line
import sys
import os
import re

class TruthStorage:
  def __init__(self,fileName):
    self.InSet = []
    self.OutSet = []
    self.File = fileName

def NumberImagesInJsonFile(file):
  count=0
  for line in open(file):
    if '.jpg' in line:
      count = count + 1
  return count -1

def FindImageInJsonFiles(jsonFolder,imgId):
  for subdir,dirs, files in os.walk(jsonFolder):
    for file in files:
      for line in open(os.path.join(jsonFolder,file)):
        if '/'+imgId+'.jpg' in line:
          return file
  return 'none'


def ReadTruthTable(path,fileName):
  ''' File format 
        imageID FileName 1/0 (1 if in set 0 otherwise)
  '''
  file = os.path.join(path,fileName)
  f = open(file,'r')
  match = '(?P<imgId>\d*) .* (?P<imgInSet>\d*)'
  matcher = re.compile(match)
  lines = f.readlines()
  setStorage = TruthStorage(fileName)

  for line in lines:
    # do something with the line
    m = matcher.match(line)
    if m:
      imgId = m.group('imgId')
      if imgId:
        imgInSet = m.group('imgInSet')
        # what do i do with this information?
        if imgInSet:
          setStorage.InSet.append(imgId)
        else:
          setStorage.OutSet.append(imgId)
      
  f.close()
  return setStorage

if len(sys.argv) != 8:
  print "Usage <Location of ColorCorrelogram> <Location of FeatureMatcher> <Input Images> <Output Images> <search radius> <tau> <truth file folder>"
else:

  ColorCorrelogram = sys.argv[1]
  FeatureMatcher = sys.argv[2]
  inputImages = sys.argv[3]
  outputFolder = sys.argv[4]
  
  correlogramFolder = os.path.join(outputFolder,'correlogram/')
  featureMatcherFolder = os.path.join(outputFolder,'matches/')
  if not os.path.isdir(correlogramFolder):
    os.mkdir(correlogramFolder)
  if not os.path.isdir(featureMatcherFolder):
    os.mkdir(featureMatcherFolder)
  radius = sys.argv[5]
  tau = sys.argv[6]
  truthFolder = sys.argv[7] 
 
  truthStorageList = []
 
  for subdir,dirs, files in os.walk(truthFolder):
    for file in files:
      truthStorageList.append(ReadTruthTable(truthFolder,file))
  
  correlogramCall = ColorCorrelogram + ' ' + inputImages + ' ' + correlogramFolder + ' ' + radius + ' > '+ outputFolder+'CorrelogramOutput.txt'
  print correlogramCall
  #os.system(correlogramCall)
  print "Correlogram complete"

  featureMatcherCall = FeatureMatcher + ' ' + os.path.join(correlogramFolder,'MaxFeatureVector.json') + ' ' + featureMatcherFolder + ' ' + tau + ' >' + outputFolder+'FeatureMatcherOutput.txt'
  print featureMatcherCall
  os.system(featureMatcherCall)
  print 'Feature Matcher Complete'

  avgPrec = 0.0
  avgRecall = 0.0  
  for truthStorage in truthStorageList:
    hash = {}
    for imgId in truthStorage.InSet:
      file = FindImageInJsonFiles(featureMatcherFolder,imgId)
      if file in hash:
  	hash[file] = hash[file] + 1
      else:
        hash[file] = 1 
    maxFile=''
    for file in hash:
      if file != 'none':
        if maxFile == '':
          maxFile = file
        elif hash[maxFile] < hash[file]:
          maxFile = file
    if maxFile == '':
      print 'images not found in any set'
    else:
      images = NumberImagesInJsonFile(os.path.join(featureMatcherFolder,maxFile))
      precision = float(hash[maxFile])/float(images)
      recall = float(hash[maxFile])/float(len(truthStorage.InSet))
      print 'precision = ' + str(precision) + ' recall = ' + str(recall)
      avgRecall = avgRecall + recall
      avgPrec = avgPrec + precision

  avgRecall = avgRecall / len(truthStorageList)
  avgPrec= avgPrec / len(truthStorageList)
  print 'average precision = ' + str(avgPrec) + ' average recall = ' + str(avgRecall)

