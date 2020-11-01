//
// Created by Vitaliy on 2019-09-25.
//

#include "length_of_longest_substring.h"

int lengthOfLongestSubstring::getLength(std::string s) {
  int ans = 0, n = s.length();
    std::unordered_map<char, int> map;

  for(int i = 0, j = 0 ; j < n; j++) {
    auto index = map.find(s[j]);
    if (index != map.end() && i < index->second) {
      i = std::max(i, index->second);
    }

    ans = std::max(ans, j - i + 1);
    map[s[j]] = j + 1;
  }

  return ans;
}

int lengthOfLongestSubstring::getLength2(std::string s) {
  int max = 0, index;
  std::string subString;

  for (char c : s) {
    index = subString.find_first_of(c);
    if (index != std::string::npos) {
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

int lengthOfLongestSubstring::getLength3(std::string s) {
  int max = 0, n = s.length(), i = 0, j = 0;
    std::unordered_set<char> myset;

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
