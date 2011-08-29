
#ADD Library
include_directories(.)
add_definitions(`pkg-config --cflags --libs opencv`)
add_library(ColorCorrelogram ColorCorrelogram.c)
add_library(OpenCVHelper OpenCVHelper.c)
add_executable(main main.c) 
#target_link_libraries(ColorCorrelogram ${OpenCV_LIBS})
#target_link_libraries(OpenCVHelper ${OpenCV_LIBS})
target_link_libraries(main ColorCorrelogram)
target_link_libraries(main OpenCVHelper)
target_link_libraries(main ${OpenCV_LIBS})
