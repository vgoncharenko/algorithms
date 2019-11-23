//
// Created by Vitaliy on 2019-09-25.
//

#include "deep_copy_list_with_random_pointer.h"

Node *DeepCopyListWithRandomPointer::copyRandomList(Node *head) {
  if (nullptr == head) {
    return nullptr;
  }
  Node *result = new Node(head->val, head->next, head->random);
  map<int, Node*> map1;
  vector<Node*> randomList;

  map1.insert(make_pair(head->val, result));
  if (nullptr != head->random) {
    randomList.push_back(result);
  }
  Node *temp = head->next,
       *current = nullptr,
       *prev = result;
  while (temp != nullptr) {
    current = new Node(temp->val, temp->next, temp->random);
    prev->next = current;
    if (nullptr != temp->random) {
      randomList.push_back(current);
    }

    map1.insert(make_pair(temp->val, current));

    temp = temp->next;
    prev = current;
  }

  for (Node* item : randomList) {
    item->random = map1.find(item->random->val)->second;
  }

  return result;
}
