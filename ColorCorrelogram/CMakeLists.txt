cmake_minimum_required (VERSION 2.6)
project (main)

find_package(OpenCV REQUIRED)
add_subdirectory(src)
add_subdirectory(test)
enable_testing()
