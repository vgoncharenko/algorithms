//
// Created by Vitaliy on 2019-09-25.
//

#include "rotting-oranges.h"

int RottingOranges::orangesRotting(std::vector<std::vector<int>>& grid) {
  int n = grid.size();
  if (n == 0) return 0;
  std::vector<int> r = {-1, 0, 1, 0},
          c = {0,  1, 0, -1};
  int Min = 1,
          ff = 0, f = 0,
          m = grid[0].size();
  do {
    ff = 0, f = 0;
    for (int i=0; i<n; i++) {
      for (int j=0; j<m; j++) {
        if (grid[i][j] != 0 && grid[i][j] % 2 == 0 && grid[i][j] < 2+Min*2) {
          h(grid, i, j, n, m, f, ff, Min, r, c);
        } else if (grid[i][j] != 0 && grid[i][j] % 2 != 0 && grid[i][j] < 1+Min*2) {
          grid[i][j] = 1+Min*2;
          f++; ff++;
        }
      }
    }
    Min++;
  } while (ff != 0 && f != ff);

  int result = 0;
  if (f == ff && f != 0) {
    result = -1;
  } else if (f != ff) {
    result = Min-1;
  } else if (f == 0) {
    result = 0;
  }

  return result;
}

void RottingOranges::h(std::vector<std::vector<int>>& grid, int i, int j, int n, int m, int &f, int &ff, int Min, std::vector<int> r, std::vector<int> c) {
  grid[i][j] = 2+Min*2;
  for (int k=0; k<4; k++) {
    if (i+r[k] >= 0 && i+r[k] < n && j+c[k] >= 0 && j+c[k] < m) {
      if (grid[i+r[k]][j+c[k]] != 0 && grid[i+r[k]][j+c[k]] % 2 != 0) {
        if (grid[i+r[k]][j+c[k]] < 1+Min*2)
          f++;
        else
          ff--;

        grid[i+r[k]][j+c[k]] = 2+Min*2;
      }
    }
  }
}
