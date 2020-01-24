//
// Created by Vitaliy on 2019-09-26.
//

#include "deep_copy_list_with_random_pointer.h"

void testDeepCopyListWithRandomPointerTest() {
  string variationName;

  //{"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}
  variationName = "ex0";
  Node *temp = new Node();
  Node *input = new Node(1, temp, temp);
  temp->val = 2;
  temp->next = nullptr;
  temp->random = temp;

  auto solution = new DeepCopyListWithRandomPointer();
  Node *result = solution->copyRandomList(input);

  if (input->next == result->next)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \ninput->next: " << input->next << "\nresult->next: " << result->next << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  if (input->next->random == result->next->random)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \ninput->next->random: " << result->next->random << "\nresult->next->random: " << result->next->random << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  //NULL
  variationName = "ex1";
  input = nullptr;

  result = solution->copyRandomList(input);

  if (result != nullptr)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nresult: " << result << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  //{"$id":"1","next":null,"random":{"$ref":"1"},"val":-1}
  variationName = "ex2";
  input = new Node();
  input->val = -1;
  input->next = nullptr;
  input->random = input;

  result = solution->copyRandomList(input);

  if (result == input)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nresult: " << result << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  if (result->random == input->random)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nresult->random: " << result->random << "\ninput->random" << input->random << endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}
