cmake_minimum_required(VERSION 2.6)
 
PROJECT(FeatureMatcher)

 
FIND_PACKAGE(OpenCV REQUIRED )
#find_package(Boost 1.42.0  COMPONENTS pending REQUIRED)
FIND_PACKAGE(Boost)
IF (BOOST_FOUND)
    INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()
INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm -ljansson") 


ADD_LIBRARY(FeatureVector FeatureVector.cxx) 
ADD_LIBRARY(DisjointSetWrapper DisjointSetWrapper.cxx)
ADD_EXECUTABLE(FeatureMatcher FeatureMatcher.cxx)
TARGET_LINK_LIBRARIES(FeatureMatcher ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(FeatureMatcher FeatureVector)
TARGET_LINK_LIBRARIES(FeatureMatcher DisjointSetWrapper)
TARGET_LINK_LIBRARIES(FeatureMatcher ${Boost_LIBRARIES})
