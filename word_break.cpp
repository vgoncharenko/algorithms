//
// Created by Vitaliy on 2019-09-25.
//

#include "word_break.h"

bool check(TrieNode *root, std::string s, uint32_t pos, uint32_t N) {
  if (pos == N) return true;
  for (uint32_t i = 1; i <= N - pos; ++i) {
    if (Trie::search(root, s, pos, pos + i) && check(root, s, pos + i, N))
      return true;
  }

  return false;
}

bool check2(TrieNode *root, std::string s) {
  uint32_t N = s.length();
  if (0 == N)
    return true;

  bool **d = new bool *[N + 1];
  for (int i = 0; i <= N; i++) {
    d[i] = new bool[N + 1];
    for (int j = 0; j <= N; j++) {
      d[i][j] = false;
    }
  }

  for (uint32_t l = 1; l <= N; ++l) {
    for (uint32_t i = 0, j; i <= N - l; ++i) {
      j = i + l - 1;
      if (Trie::search(root, s, i, j + 1)) {
        d[i][j] = true;
      } else {
        for (uint32_t k = i; k <= j; k++)
          d[i][j] = d[i][j] || (d[i][k] & d[k + 1][j]);
      }
    }
  }

  return d[0][N-1];
}

bool WordBreak::wordBreak(std::string s, std::vector<std::string> &wordDict) {
  uint32_t dictSize = wordDict.size(),
          stringLen = s.length();
  if (dictSize == 0 || stringLen == 0)
    return false;

  TrieNode *root = Trie::createNode();
  for (uint32_t i = 0; i < dictSize; ++i) {
    Trie::insert(root, wordDict[i]);
  }

  return check2(root, s);
}
