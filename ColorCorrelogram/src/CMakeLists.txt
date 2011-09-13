
#ADD Library
#SET(JANSSON_LIBS `pkg-config --cflags --libs jansson`)
include_directories(.)
add_definitions(`pkg-config --cflags --libs opencv` "-lm -ljansson")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -ljansson")


add_library(ColorCorrelogram ColorCorrelogram.c)
add_library(IOHelper IOHelper.c)
add_library(OpenCVHelper OpenCVHelper.c)
add_library(CorrelogramType CorrelogramType.c)
add_executable(main main.c) 
#target_link_libraries(IOHelper ${JANSSON_LIBS})
target_link_libraries(ColorCorrelogram ${OpenCV_LIBS})
target_link_libraries(OpenCVHelper ${OpenCV_LIBS})
target_link_libraries(CorrelogramType ${OpenCV_LIBS})
target_link_libraries(IOHelper CorrelogramType)
target_link_libraries(main CorrelogramType)
target_link_libraries(main ColorCorrelogram)
target_link_libraries(main OpenCVHelper)
target_link_libraries(main IOHelper)
target_link_libraries(main ${OpenCV_LIBS})
