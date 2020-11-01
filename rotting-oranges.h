//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/rotting-oranges/
//

#ifndef TREE_ROTTING_ORANGES_H
#define TREE_ROTTING_ORANGES_H

#include <vector>
#include <iostream>



class RottingOranges {
public:
    int orangesRotting(std::vector<std::vector<int>>& grid);
    void h(std::vector<std::vector<int>>& grid, int i, int j, int n, int m, int &f, int &ff, int Min, std::vector<int> r, std::vector<int> c);
};

#endif //TREE_ROTTING_ORANGES_H
