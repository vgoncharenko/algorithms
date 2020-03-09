//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/rotting-oranges/
//

#ifndef TREE_ROTTING_ORANGES_H
#define TREE_ROTTING_ORANGES_H

#include <vector>

using namespace std;

class RottingOranges {
public:
    int orangesRotting(vector<vector<int>>& grid);
    void h(vector<vector<int>>& grid, int i, int j, int n, int m, int &f, int &ff, int Min, vector<int> r, vector<int> c);
};

#endif //TREE_ROTTING_ORANGES_H
