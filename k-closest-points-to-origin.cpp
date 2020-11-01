//
// Created by Vitaliy on 2019-09-25.
//

#include "k-closest-points-to-origin.h"

std::vector<std::vector<int> > KClosestPointsToOrigin::kClosest(std::vector<std::vector<int> > & points, int K) {
  int n = points.size();
  if (n == 0) return {};
    std::priority_queue< std::pair<double, std::pair<int, int> > > maxheap;

  for (int i=0; i<n; i++) {
    maxheap.push(make_pair(sqrt(pow(points[i][0], 2) + pow(points[i][1], 2)), std::make_pair(points[i][0], points[i][1])));

    while (maxheap.size() > K)
      maxheap.pop();
  }

  std::vector<std::vector<int>> result;
  while (maxheap.size()) {
      std::pair<double, std::pair<int, int> > top = maxheap.top();
    result.push_back({top.second.first, top.second.second});
    maxheap.pop();
  }

  return result;
}
