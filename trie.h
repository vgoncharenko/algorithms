//
// Created by Vitaliy on 2019-09-19.
//

#ifndef TREE_TRIE_H
#define TREE_TRIE_H

#include <iostream>
#include <string>



struct TrieNode {
    const static int ALPHABET_SIZE = 26;
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

class Trie {
public:
    static TrieNode *createNode();

    static void insert(TrieNode *root, std::string &str);

    static bool search(TrieNode *root, std::string &str);

    static bool search(TrieNode *root, std::string &str, uint32_t index, uint32_t N);

    static uint8_t getIndex(char c);
};

#endif //TREE_TRIE_H
