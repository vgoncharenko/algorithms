//
// Created by Vitaliy on 2019-09-25.
//

#include "reverse_words_in_a_string.h"

// Function to reverse any sequence
// starting with pointer begin and
// ending with pointer end
void reverse(char* begin, char* end)
{
  char temp;
  while (begin < end) {
    temp = *begin;
    *begin++ = *end;
    *end-- = temp;
  }
}

// Function to reverse words*/
string ReverseWordsInAString::reverseWords(string s)
{
  if (s.empty()) {
    return s;
  }
  char* word_begin = (char*)s[0];

  // Word boundary
  char* temp = (char*)s[0];

  // Reversing individual words as
  // explained in the first step
  while (*temp) {
    temp++;
    if (*temp == '\0') {
      reverse(word_begin, temp - 1);
    }
    else if (*temp == ' ') {
      reverse(word_begin, temp - 1);
      word_begin = temp + 1;
    }
  }

  // Reverse the entire string
  reverse((char*)s[0], temp - 1);
}

//
//string ReverseWordsInAString::reverseWords(string s) {
//  if (s.empty()) {
//    return s;
//  }
//  int N = s.size(),
//      skip = 0,
//      skipTemp = 0,
//      start = -1,
//      end;
//  char c;
//
//  for (int i = 0; i < N / 2; i++) {
//    c = s[i];
//    s[i] = s[N - 1 - i];
//    s[N - 1 - i] = c;
//  }
//
//  for (int i = 0; i < N; i++) {
//    if (s[i] == ' ' || i + 1 == N) {
//      if (s[i] == ' ' && start != -1 && i - start - skipTemp == 0) {
//        skipTemp++;
//      }
//      if (start == -1) {
//        skipTemp++;
//        start = i;
//      }
//
//      if (i - start - skipTemp - 1 > 1) {
//        end = (i + 1 < N || s[i] == ' ') ? i - 1 : i;
//        for (int j = 0; j <= (end - start) / 2; j++) {
//          c = s[start + j];
//          s[start + j] = s[end - j];
//          s[end - j] = c;
//        }
//        i = i - skipTemp;
//        skip += skipTemp;
//        start = -1;
//        skipTemp = 0;
//      } else {
//        start = -1;
//        skipTemp++;
//      }
//    } else {
//      if (start == -1) {
//        start = i;
//      }
//    }
//  }
//  skip += skipTemp;
//
//  return skip > 0 ? s.erase(N - skip / 2 - 1) : s;
//}
