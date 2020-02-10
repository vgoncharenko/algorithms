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

double MedianOfTwoSortedArrays::findMedianSortedArrays2(vector<int> &nums1, vector<int> &nums2) {
  int N = nums1.size(),
          M = nums2.size();
  vector<int> *x, *y;

  if (N > M) {
    x = &nums2;
    y = &nums1;
  } else {
    x = &nums1;
    y = &nums2;
  }
  int xStart = 0,
          xEnd = x->size();
  bool isOdd = ((N + M) % 2);

  while (xStart <= xEnd) {
    int xPartition = xStart + (xEnd - xStart) / 2,
            xLMax = (xPartition == 0) ? INT32_MIN : x->at(xPartition - 1),
            xRMin = (xPartition == x->size()) ? INT32_MAX : x->at(xPartition),
            yPartition = (x->size() + y->size() + 1) / 2 - xPartition,
            yLMax = (yPartition == 0) ? INT32_MIN : y->at(yPartition - 1),
            yRMin = (yPartition == y->size()) ? INT32_MAX : y->at(yPartition);

    if (xLMax <= yRMin && yLMax <= xRMin) {
      return isOdd
             ? max(xLMax, yLMax)
             : (max(xLMax, yLMax) + min(xRMin, yRMin)) * 1.0 / 2;
    } else if (xLMax > yRMin) {
      xEnd = xPartition - 1;
    } else if (yLMax > xRMin) {
      xStart = xPartition + 1;
    }
  }

  return -1;
}
