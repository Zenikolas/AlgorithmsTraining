// Description:
// Given a 2D array, print it in spiral form
#include <gtest/gtest.h>

void printSpiral(int** arr, size_t N, size_t M) {
    bool visited[N][M];
    for (auto& line: visited) {
        for (auto& row: line) {
            row = false;
        }
    }

    size_t i = 0, j = 0;
    enum Direction {
        hr,
        vd,
        hl,
        vu
    };
    Direction dirLoop[] = {hr, vd, hl, vu};
    std::cout << arr[i][j];
    visited[0][0] = true;

    while (true) {
        for (auto& dir: dirLoop) {
            size_t printedPerTry = 0;
            while(true) {
                switch (dir) {
                    case hr:
                        if (j + 1 < M && !visited[i][j + 1])  ++j;
                        break;
                    case hl:
                        if (j > 0 && !visited[i][j - 1]) --j;
                        break;
                    case vd:
                        if (i + 1 < N && !visited[i + 1][j]) ++i;
                        break;
                    case vu:
                        if (i > 0 && !visited[i - 1][j]) --i;
                        break;
                    default:
                        assert(false);
                }

                if (visited[i][j]) {
                    break;
                } else {
                    visited[i][j] = true;
                    std::cout << ' ' << arr[i][j] << std::flush;
                    ++printedPerTry;
                }
            }

            if (printedPerTry == 0) {
                return;
            }
        }
    }
}

TEST(PrintSpiralTeest, TwoXTwo) {
    const size_t N = 2;
    const size_t M = 2;
    int** arr = new int*[N];
    for (size_t i = 0; i < N; ++i) {
        arr[i] = new int[M];
    }

    for (size_t i = 0; i < N; ++i) {
        arr[i] = new int[M];
    }
    [N] = {{1,2}, {3,4}};
    int* arrp = &arr[0][0];
    printSpiral(&arrp, N, M);
    //expected output: 1 2 4 3
}

//TEST(PrintSpiralTeest, FourXFour) {
//    const size_t N = 4;
//    const size_t M = 4;
//    int arr[N][M] = {{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}};
//
//    printSpiral((int**)arr, N, M);
//    //expected output: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
//}
//
//TEST(PrintSpiralTeest, NotSquare) {
//    const size_t N = 3;
//    const size_t M = 6;
//    int arr[N][M] = {{1, 2, 3, 4, 5, 6}, {7, 8, 9, 10, 11, 12}, {13, 14, 15, 16, 17, 18}};
//
//    printSpiral((int**)arr, N, M);
//    //expected output: 1 2 3 4 5 6 12 18 17 16 15 14 13 7 8 9 10 11
//}