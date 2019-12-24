#include "LocalMinimum.h"
#include <gtest/gtest.h>

TEST(LocalMinimumTest, oneElementArray)
{
    int arr[] = {100};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, -1);

}

TEST(LocalMinimumTest, emptyArray)
{
    int idx = getLocalMinimumIdx(NULL, 0);
    ASSERT_EQ(idx, -1);

}

TEST(LocalMinimumTest, beginLocalMinArray)
{
    int arr[] = {5, 15, 16, 41, 43};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 0);

}

TEST(LocalMinimumTest, endLocalMinArray)
{
    int arr[] = {20, 17, 15, 10, 5};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 4);

}

TEST(LocalMinimumTest, midOddLocalMinArray)
{
    int arr[] = {17, 15, 3, 41, 43};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 2);

}

TEST(LocalMinimumTest, midEvenLocalMinArray)
{
    int arr[] = {100, 70, 60, 3, 41, 42};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 3);

}

TEST(LocalMinimumTest, midAfterLocalMinArray)
{
    int arr[] = {18, 17, 16, 3, 41};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 3);

}

TEST(LocalMinimumTest, midBeforeLocalMinArray)
{
    int arr[] = {10000, 200, 2, 3, 4, 5};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 2);

}

TEST(LocalMinimumTest, longleftPartLocalMinArray)
{
    int arr[] = {15, 7, 5, 1, 18, 19, 43, 878, 1000, 12312, 22312, 24312, 30890, 48000, 56000, 65000};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 3);

}

TEST(LocalMinimumTest, longRightPartLocalMinArray)
{
    int arr[] = {11111, 5001, 2047, 1024, 723, 600, 567, 43, 15, 7, 5, 1, 30890, 48000, 56000, 65000};
    int idx = getLocalMinimumIdx(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(idx, 11);

}