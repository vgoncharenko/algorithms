//
// Created by Vitaliy on 2019-09-26.
//

#ifndef TREE_FIND_MEDIAN_SORTED_ARRAYS_H
#define TREE_FIND_MEDIAN_SORTED_ARRAYS_H

#include <vector>

using namespace std;

class FindMedianSortedArrays {
public:
    double compute(vector<int>& nums1, vector<int>& nums2);
    vector<int> merge(vector<int>& nums1, vector<int>& nums2);
};


#endif //TREE_FIND_MEDIAN_SORTED_ARRAYS_H
