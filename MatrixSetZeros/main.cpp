#include <gtest/gtest.h>

template <size_t M, size_t N>
void setZeroMatrix(uint32_t (&arr)[M][N]) {
  std::vector<bool> lines(M, false);
  std::vector<bool> columnes(N, false);

  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (arr[i][j] == 0) {
        lines[i] = true;
        columnes[j] = true;
      }
    }
  }

  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (lines[i] || columnes[j]) {
        arr[i][j] = 0;
      }
    }
  }
}

template <size_t M, size_t N>
bool isEqual(const uint32_t (&lhs)[M][N], const uint32_t (&rhs)[M][N]) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (lhs[i][j] != rhs[i][j]) {
        std::cout << "lhs: " << lhs[i][j] << " and rhs: " << rhs[i][j]
                  << std::endl;
        return false;
      }
    }
  }

  return true;
}

template <size_t M, size_t N>
void copyMatrix(uint32_t (&lhs)[M][N], const uint32_t (&rhs)[M][N]) {
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      lhs[i][j] = rhs[i][j];
    }
  }
}

TEST(RotateMatrix, DoubleTest) {
  constexpr size_t N = 2;
  uint32_t arr[N][N] = {{1, 0}, {3, 4}};
  uint32_t expected_arr[N][N] = {{0, 0}, {3, 0}};

  setZeroMatrix(arr);

  EXPECT_TRUE(isEqual(arr, expected_arr));
}

TEST(RotateMatrix, TripleTest) {
  constexpr size_t N = 3;
  uint32_t arr[N][N] = {{1, 2, 3}, {4, 0, 6}, {7, 8, 9}};
  uint32_t expected_arr[N][N] = {{1, 0, 3}, {0, 0, 0}, {7, 0, 9}};

  setZeroMatrix(arr);

  EXPECT_TRUE(isEqual(arr, expected_arr));
}

TEST(RotateMatrix, RectangleTest) {
  constexpr size_t M = 2;
  constexpr size_t N = 3;
  uint32_t arr[M][N] = {{1, 2, 3}, {4, 0, 6}};
  uint32_t expected_arr[M][N] = {{1, 0, 3}, {0, 0, 0}};

  setZeroMatrix(arr);

  EXPECT_TRUE(isEqual(arr, expected_arr));
}