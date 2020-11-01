//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/median-of-two-sorted-arrays/
//

#ifndef TREE_MEDIAN_OF_TWO_SORTED_ARRAYS_H
#define TREE_MEDIAN_OF_TWO_SORTED_ARRAYS_H

#include <string>
#include <vector>
#include <exception>
#include <iostream>



class MedianOfTwoSortedArrays {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2);
    double findMedianSortedArrays2(std::vector<int>& nums1, std::vector<int>& nums2);
};

#endif //TREE_MEDIAN_OF_TWO_SORTED_ARRAYS_H
