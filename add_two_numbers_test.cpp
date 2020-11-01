//
// Created by Vitaliy on 2019-09-25.
//

#include "add_two_numbers.cpp"

void testAddTwoNumbers() {
  // ex1
  std::vector<int> input1 = {2, 4, 3};
  std::vector<int> input2 = {5, 6, 4};
  std::vector<int> expected = {7, 0, 8};

  auto *sumator = new AddTwoNumbers();
  std::vector<int> output = sumator->sum(input1, input2);

  for (int i = 0; i < output.size(); i++)
    if (expected[i] != output[i])
      std::cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected[i] << "\nactual: " << output[i] << std::endl;

  // ex2
  input1 = {3, 4, 9};
  input2 = {5, 6, 9};
  expected = {8, 0, 9, 1};

  output = sumator->sum(input1, input2);

  for (int i = 0; i < output.size(); i++)
    if (expected[i] != output[i])
      std::cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected[i] << "\nactual: " << output[i] << std::endl;

  // ex3
  input1 = {3, 4};
  input2 = {5, 6, 9};
  expected = {8, 0, 0, 1};

  output = sumator->sum(input1, input2);

  for (int i = 0; i < output.size(); i++)
    if (expected[i] != output[i])
      std::cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected[i] << "\nactual: " << output[i] << std::endl;
}

void testAddTwoNumbers2() {
  // ex1
  auto *input1 = new AddTwoNumbers::ListNode(2);
  input1->next = new AddTwoNumbers::ListNode(4);
  input1->next->next = new AddTwoNumbers::ListNode(3);

  auto *input2 = new AddTwoNumbers::ListNode(5);
  input2->next = new AddTwoNumbers::ListNode(6);
  input2->next->next = new AddTwoNumbers::ListNode(4);

  auto *expected = new AddTwoNumbers::ListNode(7);
  expected->next = new AddTwoNumbers::ListNode(0);
  expected->next->next = new AddTwoNumbers::ListNode(8);

  auto *sumator = new AddTwoNumbers();
  AddTwoNumbers::ListNode *output = sumator->sum(input1, input2);

  while (expected != nullptr) {
    if (expected->val != output->val) {
      std::cout << "FAIL: testAddTwoNumbers: \nexpected: " << expected->val << "\nactual: " << output->val << std::endl;
    }

    expected = expected->next;
    output = output->next;
  }
}