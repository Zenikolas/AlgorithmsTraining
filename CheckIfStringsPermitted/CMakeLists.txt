cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)


add_executable(checkIfStringsPermitted main.cpp)

target_link_libraries(checkIfStringsPermitted gtest gtest_main pthread)
