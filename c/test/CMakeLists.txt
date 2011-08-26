#CMake Lists for Tests

include_directories(${main_source_dir}/src)

add_executable(correlogramTest ColorCorrelogramTest)

target_link_libraries(correlogramTest ColorCorrelogram)