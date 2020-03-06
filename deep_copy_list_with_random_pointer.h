//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/copy-list-with-random-pointer/
//

#ifndef TREE_DEEP_COPY_LIST_WITH_RANDOM_POINTER_H
#define TREE_DEEP_COPY_LIST_WITH_RANDOM_POINTER_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
      val = _val;
      next = _next;
      random = _random;
    }
};

class DeepCopyListWithRandomPointer {
public:
    Node* copyRandomList(Node* head);
    Node* copyRandomListInPlace(Node* head);
};


#endif //TREE_DEEP_COPY_LIST_WITH_RANDOM_POINTER_H
