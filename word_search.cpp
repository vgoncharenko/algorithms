//
// Created by Vitaliy on 2019-09-25.
//

#include "word_search.h"

bool checkBoundaries(int N, int M, int row, int col, const string &word, int pos, vector<vector<bool>> &checked);

bool isMatch(vector<vector<char>> &grid, int row, int col, const string &word, int pos);

bool DFS(vector<vector<char>> &grid, int row, int col, int N, int M, const string &word, int pos, vector<vector<bool>> &checked) {
  bool result = false;
  static int rowNbr[] = {-1, 0, 0, 1};
  static int colNbr[] = {0, -1, 1, 0};

  checked[row][col] = true;

  for (int k = 0; k < 4; ++k) {
    int tempRow = row + rowNbr[k];
    int tempCol = col + colNbr[k];
    if (checkBoundaries(N, M, tempRow, tempCol, word, pos, checked) && isMatch(grid, tempRow, tempCol, word, pos)) {
      if (pos == word.size() - 1) return true;
      result = DFS(grid, tempRow, tempCol, N, M, word, pos + 1, checked);
      if (result) return true;
    }
  }

  checked[row][col] = false;
  return result;
}

bool isMatch(vector<vector<char>> &grid, int row, int col, const string &word, int pos) {
  return grid[row][col] == word[pos];
}

bool checkBoundaries(int N, int M, int row, int col, const string &word, int pos, vector<vector<bool>> &checked) {
  return (row >= 0) && (row < N) && (col >= 0) && (col < M) && word.size() > pos && !checked[row][col];
}

bool WordSearch::exist(vector<vector<char>> &board, string word) {
  if (board.empty() || word.empty()) {
    return false;
  }
  int N = board.size(),
          M = board[0].size(),
          pos = 0;
  bool result = false;

  vector<vector<bool>> checked = vector<vector<bool>>(N, vector<bool>(M, false));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!checked[i][j] && isMatch(board, i, j, word, pos)) {
        if (pos == word.size() - 1) return true;
        result = DFS(board, i, j, N, M, word, pos + 1, checked);
        if (result) return true;
      }
    }
  }

  return result;
}
