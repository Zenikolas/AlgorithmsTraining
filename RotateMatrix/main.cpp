#include <gtest/gtest.h>

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

template <size_t N>
void rotateMatrix(uint32_t (&arr)[N][N]) {
    if (N < 2) {
        return;
    }

    for (size_t i = 0; i < N / 2; ++i) {
        for (size_t j = i; j < N - 1 - i; ++j) {
            size_t ir = i;
            size_t jr = j;
            uint32_t buffer;
            buffer = arr[ir][jr];
            do {
                size_t tmp = ir;
                ir = jr;
                jr = N - 1 - tmp;
                std::swap(buffer, arr[ir][jr]);
            } while (ir != i || jr != j);
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