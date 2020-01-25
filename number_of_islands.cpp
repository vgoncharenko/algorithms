//
// Created by Vitaliy on 2019-09-25.
//

#include "number_of_islands.h"


bool checkBoundaries(int N, int M, int row, int col);

bool isLand(vector<vector<char>> &grid, int row, int col, bool *const *checked);

void DFS(vector<vector<char>> &grid, int row, int col, int N, int M, bool **checked) {
  static int rowNbr[] = {-1, 0, 0, 1};
  static int colNbr[] = {0, -1, 1, 0};

  checked[row][col] = true;

  for (int k = 0; k < 4; ++k) {
    int tempRow = row + rowNbr[k];
    int tempCol = col + colNbr[k];
    if (checkBoundaries(N, M, tempRow, tempCol) && isLand(grid, tempRow, tempCol, checked))
      DFS(grid, tempRow, tempCol, N, M, checked);
  }
}

bool isLand(vector<vector<char>> &grid, int row, int col, bool *const *checked) {
  return grid[row][col] == '1' && !checked[row][col];
}

bool checkBoundaries(int N, int M, int row, int col) {
  return (row >= 0) && (row < N) && (col >= 0) && (col < M);
}

int NumberOfIslands::numIslands(vector<vector<char>> &grid) {
  if (grid.empty()) {
    return 0;
  }
  int N = grid.size(),
      M = grid[0].size();
  int islandCount = 0;

  bool **checked = new bool *[N];
  for (int i = 0; i < N; i++) {
    checked[i] = new bool[M];
    for (int j = 0; j < M; j++) {
      checked[i][j] = false;
    }
  }
  //memset(checked, false, sizeof(bool) * N * M);
//  checked = vector<vector<bool>>(N, vector<bool>(M, false));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (isLand(grid, i, j, checked)) {
        DFS(grid, i, j, N, M, checked);
        ++islandCount;
      }
    }
  }

  return islandCount;
}
