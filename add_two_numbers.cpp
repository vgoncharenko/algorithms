//
// Created by Vitaliy on 2019-09-25.
//

#include "add_two_numbers.h"

std::vector<int> AddTwoNumbers::sum(std::vector<int> input1, std::vector<int> input2) {
  std::vector<int> output;
  unsigned long count1 = input1.size(), count2 = input2.size();
  int carryBit = 0;

  // align inputs
  if (count1 > count2) {
    for (int i = (int) count2; i < count1; i++) {
      input2[i] = 0;
    }
  } else {
    for (int i = (int) count1; i < count2; i++) {
      input1[i] = 0;
    }
  }

  for (int i = 0; i < input1.size(); i++) {
    output.push_back(input1[i] + input2[i] + carryBit);
    carryBit = 0;
    if (output[i] >= 10) {
      carryBit = 1;
      output[i] -= 10;
    }
  }
  if (carryBit) {
    output[input1.size()] = carryBit;
  }

  return output;
}

AddTwoNumbers::ListNode *AddTwoNumbers::sum(ListNode *l1, ListNode *l2) {
  AddTwoNumbers::ListNode *output = new AddTwoNumbers::ListNode(0), *item;
  int carryBit = 0;

  item = output;
  while (true) {
    item->val = l1->val + l2->val + carryBit;
    carryBit = 0;
    if (item->val >= 10) {
      carryBit = 1;
      item->val -= 10;
    }

    if (l1->next == nullptr && l2->next == nullptr) {
      break;
    }
    l1 = l1->next;
    l2 = l2->next;
    item->next = new AddTwoNumbers::ListNode(0);
    item = item->next;
  }
  if (carryBit) {
    item->next = new AddTwoNumbers::ListNode(carryBit);
  }

  return output;
}