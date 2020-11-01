//
// Created by Vitaliy on 2019-09-25.
//

#include "reverse_words_in_a_string.h"

// Function to reverse any sequence
// starting with pointer begin and
// std::ending with pointer std::end
void reverse(char *begin, char *end) {
  char temp;
  while (begin < end) {
    temp = *begin;
    *begin++ = *end;
    *end-- = temp;
  }
}

// Function to reverse words*/
std::string ReverseWordsInAString::reverseWords(std::string s) {
  if (s.empty()) {
    return s;
  }
  char *wordBegin = &s.at(0);

  int skip = 0,
          N = s.size(),
          wordCount = 0;

  // Word boundary
  char *temp = &s.at(0);
  char *first = &s.at(0);
  char *last = &s.back();

  // Reversing individual words as
  // explained in the first step
  while (*temp) {
    if (temp == last) {
      if (temp - skip == wordBegin && *wordBegin == ' ' && wordBegin != first) {
        skip++;
      }
      if (*temp == ' ') {
        skip++;
      }
      wordCount++;
      reverse(wordBegin, ((*temp == ' ') ? temp - 1 : temp));
    } else if (*temp == ' ') {
      if (temp == first || (*(temp - 1) == ' ')) {
        skip++;
      } else {
        wordCount++;
        reverse(wordBegin, temp - 1);
        temp -= skip;
        wordBegin = temp + 1;
        skip = 0;
      }
    }
    temp++;
  }

  // Reverse the entire std::string
  reverse(&s.at(0), temp - 1 - skip);

  return skip > 0 ? s.erase(N - skip) : s;
}
