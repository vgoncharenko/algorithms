//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/k-closest-points-to-origin/
// Priority Queue:
// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
// https://www.geeksforgeeks.org/priority-queue-of-pairs-in-c-ordered-by-first/
// https://www.geeksforgeeks.org/store-data-triplet-vector-c/
//

#ifndef TREE_K_CLOSEST_POINTS_TO_ORIGIN_H
#define TREE_K_CLOSEST_POINTS_TO_ORIGIN_H

#include <queue>
#include <vector>

using namespace std;

class KClosestPointsToOrigin {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K);
};


#endif //TREE_K_CLOSEST_POINTS_TO_ORIGIN_H
