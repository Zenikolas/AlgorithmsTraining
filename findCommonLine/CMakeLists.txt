cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)


add_executable(findCommonLine main.cpp)

target_link_libraries(findCommonLine gtest gtest_main pthread)
