//
// Created by Vitaliy on 2019-09-26.
// https://leetcode.com/problems/median-of-two-sorted-arrays/
//

#include "find_median_sorted_arrays.h"


double FindMedianSortedArrays::compute(vector<int> &nums1, vector<int> &nums2) {
  int n1 = nums1.size(),
          n2 = nums2.size(),
          seekIndex = (n1 + n2) / 2;
  bool parityBit = ((n1 + n2) % 2) == 0;
  vector<int> resultArray;
  double result = -1;


//  resultArray = (n1 > n2) ? merge(nums2, nums1) : merge(nums1, nums2);
//
//  result = parityBit
//           ? (resultArray[seekIndex] + resultArray[seekIndex + 1]) / 2
//           : resultArray[seekIndex];

  return result;
}

vector<int> FindMedianSortedArrays::merge(vector<int> &nums1, vector<int> &nums2) {
  int n1 = nums1.size(),
      n2 = nums2.size(),
      i = n1 / 2,
      j = n2 / 2,
      cursor = 0,
      seekIndex = (n1 + n2) / 2;
  vector<int> resultArray;


  while (cursor <= seekIndex) {
    if (nums1[i] > nums2[j]) {

    }
  }

  return resultArray;
}