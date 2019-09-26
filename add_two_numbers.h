//
// Created by Vitaliy on 2019-09-25.
// https://leetcode.com/problems/add-two-numbers/
//

#ifndef TREE_ADD_TWO_NUMBERS_H
#define TREE_ADD_TWO_NUMBERS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class AddTwoNumbers {
public:
    struct ListNode {
        int val;
        ListNode *next;

        explicit ListNode(int x) : val(x), next(nullptr) {}
    };

    vector<int> sum(vector<int> input1, vector<int> input2);

    ListNode *sum(ListNode *l1, ListNode *l2);
};


#endif //TREE_ADD_TWO_NUMBERS_H
