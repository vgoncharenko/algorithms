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
          if (substr.length() == n) {
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

string LongestPalindrome::find3(string s) {
  if (s.size() <= 1) {
    return s;
  }

//  string t = "#";
//  for (char i : s) {
//    t += i;
//    t += "#";
//  }

  int N = (int) s.size(),
          LPS[N],
          center = 1,
          centerR = 2,
          curL = 0,
          maxLPSLength = 0,
          maxLPSCenterPosition = 0;

  LPS[0] = 0;
  LPS[1] = 1;
  bool expand;

  for (int curR = 2; curR < N; curR++) {
    curL = 2 * center - curR;
    //Reset expand - means no expansion required
    expand = false;
    //If currentRightPosition is within centerRightPosition
    if (centerR - curR > 0) {
      if (LPS[curL] < centerR - curR) {
//      Case 1: L[currentRightPosition] = L[currentLeftPosition] applies when:
//      i-left palindrome is completely contained in center palindrome
//      i-left palindrome is NOT a prefix of center palindrome
//      Both above conditions are satisfied when
//      L[currentLeftPosition] < centerRightPosition – currentRightPosition
        LPS[curR] = LPS[curL];
      } else if (LPS[curL] == centerR - curR && curR == N - 1) {
//      Case 2: L[currentRightPosition] = L[currentLeftPosition] applies when:
//      i-left palindrome is prefix of center palindrome (means completely contained also)
//      center palindrome is suffix of input string
//      Above conditions are satisfied when
//      L[currentLeftPosition] = centerRightPosition – currentRightPosition (For 1st condition) AND
//      centerRightPosition = 2*N where N is input string length N (For 2nd condition).
        LPS[curR] = LPS[curL];
      } else if (LPS[curL] == centerR - curR && curR < N - 1) {
//      Case 3: L[currentRightPosition] > = L[currentLeftPosition] applies when:
//      i-left palindrome is prefix of center palindrome (and so i-left palindrome is completely contained in center palindrome)
//      center palindrome is NOT suffix of input string
//      Above conditions are satisfied when
//      L[currentLeftPosition] = centerRightPosition – currentRightPosition (For 1st condition) AND
//      centerRightPosition < 2*N where N is input string length N (For 2nd condition).
        LPS[curR] = LPS[curL];
        expand = true;  // expansion required
//        centerR = curR + LPS[curR];
//        curR = curR + LPS[curR];
      } else if (LPS[curL] > centerR - curR) {
//      Case 4: L[currentRightPosition] > = centerRightPosition – currentRightPosition applies when:
//      i-left palindrome is NOT completely contained in center palindrome
//      Above condition is satisfied when
//      L[currentLeftPosition] > centerRightPosition – currentRightPosition
//      In this case, length of i-right palindrome is at least as long (centerRightPosition – currentRightPosition) and there is a possibility of i-right palindrome expansion.
        LPS[curR] = centerR - curR;
        expand = true;  // expansion required
//        centerR = curR + LPS[curR];
//        curR = curR + LPS[curR];
      }
    } else {
      LPS[curR] = 0;
      expand = true;  // expansion required
    }

    //Attempt to expand palindrome centered at currentRightPosition
    //Here for odd positions, we compare characters and
    //if match then increment LPS Length by ONE
    //If even position, we just increment LPS by ONE without
    //any character comparison
    if (expand) {
      while (((curR + LPS[curR]) < N && (curR - LPS[curR]) > 0) &&
             (((curR + LPS[curR] + 1) % 2 == 0) ||
              (s[(curR + LPS[curR] + 1) / 2] == s[(curR - LPS[curR] - 1) / 2]))) {
        LPS[curR]++;
      }
    }

    if(LPS[curR] > maxLPSLength)  // Track maxLPSLength
    {
      maxLPSLength = LPS[curR];
      maxLPSCenterPosition = curR;
    }

    // If palindrome centered at currentRightPosition
    // expand beyond centerRightPosition R,
    // adjust centerPosition C based on expanded palindrome.
    if (curR + LPS[curR] > centerR)
    {
      center = curR;
      centerR = curR + LPS[curR];
    }

  }

  return s.substr(static_cast<unsigned long>((maxLPSCenterPosition - maxLPSLength) / 2),
                  static_cast<unsigned long>(maxLPSLength - 1));
}
