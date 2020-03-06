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

Node *DeepCopyListWithRandomPointer::copyRandomListInPlace(Node *head) {
  if (head == nullptr)
    return nullptr;

  Node* tmp = head;
  while (tmp != nullptr){
    tmp->next = new Node(tmp->val, tmp->next, tmp->random);
    tmp = tmp->next->next;
  }
  tmp = head->next;
  while (tmp->next != nullptr){
    if (tmp->random != nullptr)
      tmp->random = tmp->random->next;
    tmp = tmp->next->next;
  }
  head = head->next;
  tmp = head;
  while (tmp->next != nullptr){
    tmp->next = tmp->next->next;
    tmp = tmp->next;
  }

  return head;
}
