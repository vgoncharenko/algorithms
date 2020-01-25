//
// Created by Vitaliy on 2019-09-25.
//

#include "median_of_two_sorted_arrays.h"

double MedianOfTwoSortedArrays::findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
  int N = nums1.size(),
          M = nums2.size(),
          I = (N + M) / 2,
          i = 0,
          j = 0,
          k = 0;
  bool isPair = !((N + M) % 2);
  vector<int> v(2);

  do {
    if ((j <= M - 1 && i <= N - 1 && nums1[i] >= nums2[j]) || i > N - 1)
      v[k] = nums2[j++];
    else
      v[k] = nums1[i++];

    if (isPair && I - 1 == 0)
      k++;
  } while (--I >= 0);

  return isPair
         ? ((v[0] + v[1]) * 1.0) / 2
         : v[0];
}
