//
// Created by Vitaliy on 2019-09-25.
//

#include "length_of_longest_substring.h"

int lengthOfLongestSubstring::getLength(string s) {
  int max = 0, n = s.length();
  unordered_map<char, int> map;

  for(int i = 0, j = 0 ; j < n; j++) {
    auto index = map.find(s[j]);
    if (index != map.end() && i < index->second) {
      i = index->second;
    }

    if (max < j - i + 1) {
      max = j - i + 1;
    }

    map[s[j]] = j + 1;
  }

  return max;
}

int lengthOfLongestSubstring::getLength2(string s) {
  int max = 0, index;
  string subString;

  for (char c : s) {
    index = subString.find_first_of(c);
    if (index != string::npos) {
      if (max < subString.size()) {
        max = subString.size();
      }
      subString = subString.substr(index + 1);
    }
    subString += c;
  }

  if (max < subString.size()) {
    max = subString.size();
  }

  return max;
}

int lengthOfLongestSubstring::getLength3(string s) {
  int max = 0, n = s.length(), i = 0, j = 0;
  unordered_set<char> myset;

  while (i < n && j < n) {
    if (myset.find(s[j]) == myset.end()) {
      myset.insert(s[j++]);
      if (max < j - i) {
        max = j - i;
      }
    } else {
      myset.erase(s[i++]);
    }
  }

  return max;
}
