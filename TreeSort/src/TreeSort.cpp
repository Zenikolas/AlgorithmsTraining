#include "../TreeSort.h"
#include <iterator>

namespace {

template <class Iter>
Iter findMax(Iter begin,
             Iter end)
{
  if (begin == end) {
    return begin;
  }

  Iter it = begin;
  Iter max = it++;
  for (; it != end; ++it) {
    if (*it > *max) {
      max = it;
    }
  }

  return max;
}

template <class Iter>
void nswap(Iter begin, Iter end, bool oposite)
{
  if (begin == end) {
    return;
  }

  if (!oposite) {
    --end;
  }

  for (Iter it = begin; it != end;) {
    Iter lhs = it;
    Iter rhs;
    if (oposite) {
      rhs = --it;
    } else {
      rhs = ++it;
    }
    std::swap(*lhs, *rhs);
  }
}

}

int n_swaps(int* a, size_t size)
{
  int* begin = a;
  int* end = a + size;
  int swaps = 0;
  while (begin + 1 != end) {
    int* max = findMax(begin, end);

    size_t ldistance = std::distance(begin, max);
    size_t rdistance = std::distance(max, end) - 1;
    if (ldistance < rdistance) {
      nswap(max, begin, true);
      ++begin;
      swaps += ldistance;
    } else {
      nswap(max, end, false);
      --end;
      swaps += rdistance;
    }
  }

  return swaps;
}