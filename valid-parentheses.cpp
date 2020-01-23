//
// Created by Vitaliy on 2019-09-25.
//

#include "valid-parentheses.h"

typedef std::unordered_map<char, char> ParenthesesMap;

bool ValidParentheses::isValid(string s) {
  int N = s.size();
  if (N == 0)
    return true;
  ParenthesesMap pMap(
          {
                  {'{', '}'},
                  {'[', ']'},
                  {'(', ')'}
          }
  );
  stack<char*> stack1;
  char *tmp;

  for (int i = 0; i < N; ++i) {
    if(pMap.find(s[i]) != pMap.end()) {
      stack1.push(&s[i]);
    } else {
      if (stack1.empty())
        return false;
      tmp = stack1.top();
      stack1.pop();
      if (s[i] != pMap[*tmp])
        return false;
    }
  }
  if (!stack1.empty())
    return false;

  return true;
}
