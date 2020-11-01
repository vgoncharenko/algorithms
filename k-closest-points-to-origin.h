//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/k-closest-points-to-origin/
// Priority std::queue:
// https://www.geeksforgeeks.org/priority-std::queue-in-cpp-stl/
// https://www.geeksforgeeks.org/priority-std::queue-of-pairs-in-c-ordered-by-first/
// https://www.geeksforgeeks.org/store-data-triplet-vector-c/
//

#ifndef TREE_K_CLOSEST_POINTS_TO_ORIGIN_H
#define TREE_K_CLOSEST_POINTS_TO_ORIGIN_H

#include <queue>
#include <vector>
#include <math.h>



class KClosestPointsToOrigin {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int K);
};


#endif //TREE_K_CLOSEST_POINTS_TO_ORIGIN_H
