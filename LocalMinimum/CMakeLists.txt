cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 98)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(localMinimum main.cpp src/LocalMinimum.cpp)


option(BUILD_TEST "Build gtest for localMinimum project" ON)

if (${BUILD_TEST})
    enable_testing()
    add_subdirectory(test)
endif()