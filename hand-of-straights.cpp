//
// Created by Vitaliy on 2019-09-23.
//

#include "hand-of-straights.h"

using namespace std;

bool HandOfStraights::isNStraightHand(vector<int>& hand, int W){
  int n = hand.size();
  if (n == 0 || W == 0 || n%W != 0)
    return false;

  if (W == 1)
    return true;

  sort(hand.begin(), hand.end());

  int start = 0,
          curP = start,
          cur = hand[curP],
          curW = 1,
          nextStart = 0;
  hand[start] = -1;

  do {
    int next = cur+1;
    for (int i=curP+1; i<n; i++) {
      if (next == hand[i]) {
        curP = i;
        cur = hand[curP];
        hand[i] = -1;
        curW++;
        next = -1;
        break;
      } else if (hand[i] > -1 && nextStart == start) {
        nextStart = i;
      }
    }

    if (next != -1)
      return false;

    if (curW == W) {
        if (nextStart == start) {
          nextStart = start = curP+1;
        }
        for (int i=nextStart; i<n; i++) {
          if (hand[i] > -1) {
            nextStart = start = i;
            break;
          }
        }

      if (start >= n)
        return true;

      curP = start;
      cur = hand[curP];
      hand[curP] = -1;
      curW = 1;
    }
  } while (curP<n);

  if (curW > 1 && curW < W)
    return false;

  return true;
}
