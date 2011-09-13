#CMake Lists for Tests

include_directories(. ../src)
add_definitions(`pkg-config --cflags --libs opencv`)

add_executable(ColorCorrelogramTest ColorCorrelogramTest.c)
add_executable(OpenCVHelperTest OpenCVHelperTest.c)
target_link_libraries(ColorCorrelogramTest ColorCorrelogram)
target_link_libraries(OpenCVHelperTest OpenCVHelper)
target_link_libraries(OpenCVHelperTest ${OpenCV_LIBS})
target_link_libraries(ColorCorrelogramTest ${Open_CV_LIBS})
ENABLE_TESTING()
ADD_TEST(ColorCorrelogramTest ColorCorrelogramTest)
ADD_TEST(OpenCVHelperTest OpenCVHelperTest)


