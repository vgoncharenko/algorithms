//
// Created by Vitaliy on 2019-09-25.
//

#include "repeat-and-missing-number-array.h"

vector<int> RepeatAndMissingNumberArray::repeatedNumber(const vector<int> &A){
  if (A.size() == 0) return {};
  vector <int> AA(A);
  vector <int> result = {};
  sort(AA.begin(), AA.end());
  int f = -1,
      s = -1,
      tmpS = 1;
  for(int i=0; i<AA.size(); i++, tmpS++){
    if(s == -1 && AA[i] != tmpS)
      s = tmpS;

    if(i+1 < AA.size() && f == -1 && AA[i] == AA[i+1]) {
      f = AA[i];
      tmpS--;
    }

    if (f != -1 && s != -1)
      break;
  }

  if (f != -1)
    result.push_back(f);
  if (s != -1)
    result.push_back(s);

  return result;
}
