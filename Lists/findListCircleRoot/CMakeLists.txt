cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)


add_executable(findListCircleRoot main.cpp)

target_link_libraries(findListCircleRoot gtest gtest_main pthread)
