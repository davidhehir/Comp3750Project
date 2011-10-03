cmake_minimum_required(VERSION 2.6)
 
PROJECT(FeatureMatcher)
 
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ljansson") 


ADD_LIBRARY(FeatureVector FeatureVector.cxx) 
ADD_EXECUTABLE(FeatureMatcher FeatureMatcher.cxx)
TARGET_LINK_LIBRARIES(FeatureMatcher ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(FeatureMatcher FeatureVector)
