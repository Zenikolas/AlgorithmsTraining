set(CMAKE_CXX_STANDARD 11)

set(SRC localMinimumTest.cpp ../src/LocalMinimum.cpp)

add_executable(localMinimumTest ${SRC})

target_link_libraries(localMinimumTest ${GTEST_BOTH_LIBRARIES} pthread)

gtest_discover_tests(localMinimumTest)