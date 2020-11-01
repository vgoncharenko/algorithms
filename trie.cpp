//
// Created by Vitaliy on 2019-09-19.
//

#include "trie.h"

uint8_t Trie::getIndex(char c) {
  return c - 'a';
}

TrieNode *Trie::createNode() {
  TrieNode *node = new TrieNode;
  node->isEndOfWord = false;
  for (uint8_t i = 0; i < TrieNode::ALPHABET_SIZE; ++i) {
    node->children[i] = nullptr;
  }

  return node;
}

void Trie::insert(struct TrieNode *root, std::string &str) {
  uint32_t size = str.length();
  if (size == 0)
    return;
  TrieNode *temp = root;
  for (uint32_t i = 0; i < size; ++i) {
    uint8_t index = getIndex(str[i]);
    if (nullptr == temp->children[index])
      temp->children[index] = createNode();

    temp = temp->children[index];
  }
  temp->isEndOfWord = true;
}

bool Trie::search(struct TrieNode * root, std::string &str) {
  uint32_t size = str.length();
  if (size == 0)
    return false;
  TrieNode *temp = root;
  for (uint32_t i = 0; i < size; ++i) {
    uint8_t index = getIndex(str[i]);
    if (nullptr == temp->children[index])
      return false;
    temp = temp->children[index];
  }

  return (nullptr != temp && temp->isEndOfWord);
}

bool Trie::search(struct TrieNode * root, std::string &str, uint32_t index, uint32_t N) {
  TrieNode *temp = root;
  for (uint32_t i = index; i < N; ++i) {
    uint8_t index = getIndex(str[i]);
    if (nullptr == temp->children[index])
      return false;
    temp = temp->children[index];
  }

  return (nullptr != temp && temp->isEndOfWord);
}
