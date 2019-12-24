#include "TreeSort.h"
#include <gtest/gtest.h>

TEST(TreeSortTest, grownArray)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int swaps = n_swaps(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(swaps, 0);
}

TEST(TreeSortTest, lessArray)
{
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int swaps = n_swaps(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(swaps, 0);
}

TEST(TreeSortTest, smoke)
{
    int arr[] = {13, 3, 1992, 25, 11, 1986, 3, 6, 2018};
    int swaps = n_swaps(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(swaps, 7);
}

TEST(TreeSortTest, random)
{
    int arr[] = {15, 48, 2001, 95, 140, 3000, 5000, 3, 10000};
    int swaps = n_swaps(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(swaps, 7);
}