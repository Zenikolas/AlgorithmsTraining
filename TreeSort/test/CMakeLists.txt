set(CMAKE_CXX_STANDARD 11)

set(SRC treeSortTest.cpp ../src/TreeSort.cpp)

add_executable(treeSortTest ${SRC})

target_link_libraries(treeSortTest ${GTEST_BOTH_LIBRARIES} pthread)

gtest_discover_tests(treeSortTest)