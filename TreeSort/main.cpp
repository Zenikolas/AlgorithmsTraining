#include <iostream>
#include "TreeSort.h"


int main() {
  int arr[] = {15, 48, 2001, 95, 140, 3000, 5000, 3, 10000};
  size_t size = sizeof(arr) / sizeof(int);
  std::cout << "Input array:" << std::endl;
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  int swaps = n_swaps(arr, size);
  std::cout << "Sorted array:" << std::endl;
  for (int i = 0; i < size; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Quantity off swaps: " << swaps << std::endl;

  return 0;
}