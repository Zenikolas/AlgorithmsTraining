cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)


add_executable(checkIfStringRotated main.cpp)

target_link_libraries(checkIfStringRotated gtest gtest_main pthread)
