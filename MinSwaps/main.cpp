#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int minimumSwaps(vector<int> arr) {
  size_t swaps = 0;
  if (arr.empty()) {
    return  swaps;
  }

  int positions[arr.size()];
  for (int i = 0; i < arr.size(); ++i) {
    positions[arr[i] - 1] = i;
  }

  for (int i = 0; i < arr.size(); ++i) {
    if (positions[i] != i) {
      ++swaps;
      int moved = arr[i]; // 4
      int returned = arr[positions[i]]; // 1
      swap(arr[i], arr[positions[i]]);
      swap(positions[moved - 1], positions[returned - 1]);
    }
  }

  return swaps;
}

int main()
{
  vector<int> arr = {4, 1, 3, 5, 2};
  cout << minimumSwaps(arr) << endl;

  return 0;
}