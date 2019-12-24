#include "LocalMinimum.h"

int getLocalMinimumIdx(int* arr, size_t size)
{
  if (!arr || size < 1) {
    return -1;
  }

  size_t l = 0;
  size_t r = size - 1;
  while (l < r) {
    if (arr[l] < arr[l + 1]) {
      return l;
    }

    if (arr[r] < arr[r - 1]) {
      return r;
    }

    size_t range = r - l;
    if (range < 2) {
      return -1;
    }

    size_t m = l + (r - l) / 2;
    if (arr[m] < arr[m - 1] && arr[m] < arr[m + 1]) {
      return m;
    }

    if (arr[m - 1] < arr[m]) {
      r = m - 1;
    } else {
      l = m + 1;
    }

  }

  return -1;
}