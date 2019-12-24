#include <gtest/gtest.h>

template<size_t N>
void rotatePoint(uint32_t (&arr)[N][N], size_t& x, size_t& y, uint32_t& tmp)
{
  auto xprev = x;
  x = y;
  y = N - xprev - 1;
  std::swap(tmp, arr[x][y]);
}

template<size_t N>
void rotateMatrix(uint32_t (&arr)[N][N])
{
  size_t jbegin = 0;
  size_t jend = N - 1;

  for(size_t i = 0; i < N / 2; ++i) {
    for (size_t j = jbegin; j < jend; ++j) {
      uint32_t tmp = arr[i][j];
      size_t x = i;
      size_t y = j;
      rotatePoint(arr, x, y, tmp);
      rotatePoint(arr, x, y, tmp);
      rotatePoint(arr, x, y, tmp);
      rotatePoint(arr, x, y, tmp);
    }
    ++jbegin;
    --jend;
  }
}

template <size_t N>
bool isEqual(const uint32_t (&lhs)[N][N], const uint32_t (&rhs)[N][N]) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (lhs[i][j] != rhs[i][j]) {
        std::cout << "lhs: " << lhs[i][j] << " and rhs: " << rhs[i][j] << std::endl;
        return false;
      }
    }
  }

  return true;
}

template <size_t N>
void copyMatrix(uint32_t (&lhs)[N][N], const uint32_t (&rhs)[N][N])
{
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      lhs[i][j] = rhs[i][j];
    }
  }
}

TEST(RotateMatrix, DoubleTest) {
  constexpr size_t N = 2;
  uint32_t arr[N][N] = {{1, 2}, {3, 4}};
  uint32_t expected_arr[N][N] = {{3, 1}, {4, 2}};

  rotateMatrix(arr);

  EXPECT_TRUE(isEqual(arr, expected_arr));
}

TEST(RotateMatrix, TripleTest) {
  constexpr size_t N = 3;
  uint32_t arr[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  uint32_t expected_arr[N][N] = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};

  rotateMatrix(arr);

  EXPECT_TRUE(isEqual(arr, expected_arr));
}

TEST(RotateMatrix, FullRotateTest) {
  constexpr size_t N = 3;
  uint32_t arr[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  uint32_t copy_arr[N][N];
  copyMatrix(copy_arr, arr);

  rotateMatrix(arr);
  rotateMatrix(arr);
  rotateMatrix(arr);
  rotateMatrix(arr);

  EXPECT_TRUE(isEqual(arr, copy_arr));
}