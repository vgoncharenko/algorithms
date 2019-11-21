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

  if (result->next == result->random)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nnext: " << result->next << "\nrandom: " << result->random << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  if (result->next->random == result->next)
    cout << "FAIL " + variationName + ": testDeepCopyListWithRandomPointerTest: \nresult->next->random: " << result->next->random << "\nresult->next: " << result->next << endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}
