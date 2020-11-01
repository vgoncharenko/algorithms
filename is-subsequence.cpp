//
// Created by Vitaliy on 2019-09-25.
//

#include "is-subsequence.h"


bool IsSubsequence::isSubsequence(std::string s, std::string t)
{
  if (t.size() == 0 && s.size() != 0)
    return false;
  if (s.size() == 0)
    return true;
    std::map<char,std::vector<int>> charMap;
  for (int i=0; i<t.size(); i++) {
    auto index = charMap.find(t[i]);
    if (index == charMap.end())
      charMap.insert({t[i],{i}});
    else
      index->second.push_back(i);
  }
  int last = 0;
  for (int i=0; i<s.size(); i++) {
    auto index = charMap.find(s[i]);
    if (index == charMap.end())
      return false;
    else {
      int l = 0,
              r = index->second.size()-1,
              m = 0,
              closest = index->second.back();
      while (l<=r) {
        m = l+(r-l)/2;
        if (last<index->second[m]) {
          r = m-1;
          closest = index->second[m];
        } else if (last>index->second[m]) {
          l = m+1;
        } else if (last == index->second[m]) {
          closest = index->second[m];
          break;
        }
      }
      if (last<=closest)
        last = closest+1;
      else
        return false;
    }
  }

  return true;
}

