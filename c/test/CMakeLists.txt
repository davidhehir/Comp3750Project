#CMake Lists for Tests

include_directories(. ${main_source_dir}/src)
add_definitions(`pkg-config --cflags --libs opencv`)

add_executable(ColorCorrelogramTest ColorCorrelogramTest.c)
add_executable(OpenCVHelperTest OpenCVHelperTest.c)
target_link_libraries(ColorCorrelogramTest ColorCorrelogram)
target_link_libraries(OpenCVHelperTest OpenCVHelper)
ENABLE_TESTING()
ADD_TEST(ColorCorrelogramTest ColorCorrelogramTest)
ADD_TEST(OpenCVHelperTest OpenCVHelperTest)


