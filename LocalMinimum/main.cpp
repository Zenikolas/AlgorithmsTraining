#include <iostream>
#include "LocalMinimum.h"

int main()
{
    int arr[] = {15, 15, 60, 1, 41, 41};
    size_t size = sizeof(arr) / sizeof(int);
    int idx = getLocalMinimumIdx(arr, size);
    std::cout << "For array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Local minimum idx: " << idx << std::endl;


    return 0;
}