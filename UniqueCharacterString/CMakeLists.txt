cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

add_executable(uniqueCharacterString main.cpp)

target_link_libraries(uniqueCharacterString gtest gtest_main pthread)