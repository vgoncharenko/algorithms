//
// Created by Vitaliy on 2019-09-26.
//

#include "longest_palindrome.h"

string LongestPalindrome::find(string s) {
  if (s.size() <= 1) {
    return s;
  }

  string result = "",
          substr = "",
          middle = "";
  typedef vector<int> IndexSet;
  map<string, IndexSet> map1, map2;
  int n = s.length(), max = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (s[j - 1] == s[j] || s[j - 1] == s[j + 1]) {
        map1[s.substr(i, j - i)].push_back(j - 1);
      }
      if (s[n - i] == s[n - i - 1] || s[n - i] == s[n - i - 2]) {
        substr = s.substr(n - j, j - i);
        reverse(substr.begin(), substr.end());
        map2[substr].push_back(n - j);
      }
    }
  }

  for (auto item : map1) {
    auto seekItem = map2.find(item.first);
    if (seekItem != map2.end()) {
      int indexCorrelation = checkIndexesCorrelation(item.second, seekItem->second);
      if (indexCorrelation >= -1) {
        if (max < item.first.size() + seekItem->first.size()) {
          middle = "";
          max = item.first.size() + seekItem->first.size();
          if (indexCorrelation >= 0) {
            max++;
            middle = s[indexCorrelation + 1];
          }
          substr = seekItem->first;
          reverse(substr.begin(), substr.end());
          result = item.first + middle + substr;
        }
      } else if (indexCorrelation == -2 && max < item.first.size()) {
        max = item.first.size();
        result = item.first;
      }
    }
  }

  return result;
}

string LongestPalindrome::find2(string s) {
  if (s.size() <= 1) {
    return s;
  }

  string substr = "",
         substr1 = "",
         substr2 = "";
  priority_queue<TermMax, vector<TermMax>, TermMaxComparator> maxHeap;
  unsigned long n = s.length();

  maxHeap.push(TermMax(s.substr(0, 1), 1));

  for (unsigned long i = 0; i < n; i++) {
    for (unsigned long j = i + 1; j < n; j++) {
      substr = "";

      if (s[j - 1] == s[j + 1] && j + j - i < n && s[i] == s[j + j - i]) {
        substr1 = s.substr(i, j - i);
        substr2 = s.substr(j + 1, j - i);
        substr = substr1;
        substr += s[j];
      } else if (s[j - 1] == s[j] && j + j - i - 1 < n && s[i] == s[j + j - i - 1]) {
        substr1 = s.substr(i, j - i);
        substr2 = s.substr(j, j - i);
        substr = substr1;
      }

      if (!substr.empty()) {
        substr += substr2;
        reverse(substr2.begin(), substr2.end());
        if (substr1 == substr2) {
          if (substr.length() == n ) {
            return substr;
          }
          maxHeap.push(TermMax(substr, substr.length()));
        }
      }
    }
  }

  return maxHeap.top().term;
}

int LongestPalindrome::checkIndexesCorrelation(vector<int> &v1, vector<int> &v2) {
  vector<int> results = {-3};
  for (int i : v1) {
    for (int j : v2) {
      if (i == j - 1) {
        results.push_back(-1);
      }
      if (i == j - 2) {
        results.push_back(i);
      }
      if (i == j) {
        results.push_back(-2);
      }
    }
  }

  return *max_element(results.begin(), results.end());
}