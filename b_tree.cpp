//
// Created by Vitaliy on 2019-09-23.
//

#include "b_tree.h"


BTree::Node *BTree::addNode(std::string v, Node *parent, Node *prev, Node *next) {
  Node *node = new Node();
  parent->children[parent->childCount] = node;
  parent->childCount++;
  node->parent = parent;
  node->lief = BTree::addLief(v);
  node->liefCount++;
  node->max = v;
  node->prev = prev;
  node->next = next;

  if (parent->max.compare(v) > 0) {
    parent->max = v;
  }

  if (prev != nullptr) {
    prev->next = node;
  }
  if (next != nullptr) {
    next->prev = node;
  }

  return node;
}

BTree::Lief *BTree::addLief(std::string v, Lief *prev, Lief *next) {
  Lief *lief = new Lief();
  lief->v = v;
  lief->prev = prev;
  lief->next = next;
  if (prev != nullptr) {
    prev->next = lief;
  }
  if (next != nullptr) {
    next->prev = lief;
  }

  return lief;
}

void BTree::changeMax(std::string newMax, Node *node) {
  while (node != nullptr) {
    if (node->max.compare(newMax) < 0) {
      node->max = newMax;
      changeMax(newMax, node->parent);
    }
    return;
  }
}

BTree::Lief *BTree::traverseLief(const std::string &term, const Node *seekNode) const {
  Lief *seekLief = seekNode->lief;

  while (seekLief->next != nullptr) {
    if (seekLief->v.compare(term) >= 0) {
      return seekLief->prev;
    } else {
      seekLief = seekLief->next;
    }
  }

  return seekLief;
}

BTree::Lief *BTree::traverseLiefToStrongEqual(const std::string &term, const Node *seekNode, bool prefix) const {
  Lief *seekLief = seekNode->lief;
  std::string value;
  while (seekLief != nullptr) {
    if (prefix) {
      value = seekLief->v.substr(0, term.length());
    } else {
      value = seekLief->v;
    }
    if (value == term) {
      return seekLief;
    } else {
      seekLief = seekLief->next;
    }
  }

  return nullptr;
}

BTree::Node *BTree::lookupNode(const std::string &term, Node *node) const {
  Node *seekNode = nullptr;

  for (int i = 0; i < node->childCount; i++) {
    if (node->children[i]->max >= term) {
      seekNode = node->children[i];
      if (seekNode->childCount > 0) {
        seekNode = lookupNode(term, seekNode);
      }
      break;
    }
  }

  return seekNode;
}

BTree::Node *BTree::getTailNode(Node *node) const {
  Node *seekNode = node->children[node->childCount - 1];
  if (seekNode->childCount > 0) {
    return getTailNode(seekNode); //TODO: tail of recursion? really good to use? or compilers already cover this?
  }

  return seekNode;
}

void BTree::splitMiddleNode(Node *node) {
  if (node->parent->childCount + 1 > MAX_CHILDREN) {
    splitMiddleNode(node->parent);
  }
  int middle = node->childCount / 2;
  node->max = node->children[middle - 1]->max;
  Node *newNode = addNode(node->max, node->parent);

  for (int i = middle; i < node->childCount; i++) {
    newNode->children[newNode->childCount] = node->children[i];
    newNode->childCount++;
  }
  node->childCount = node->childCount - (u_int8_t) middle;

  node->parent->children[node->parent->childCount] = newNode;
}

void BTree::splitLiefNode(Node *node) {
  if (node->parent->childCount + 1 > MAX_CHILDREN) {
    splitMiddleNode(node->parent);
  }

  int lcount, i = lcount = node->liefCount / 2;
  Lief *next, *lief = node->lief;
  while (i > 0) {
    i--;
    lief = lief->next;
  }

  next = lief->next;
  lief->next = nullptr;
  next->prev = nullptr;
  Node *newNode = addNode(node->max, node->parent, node);
  node->max = lief->v;
  newNode->lief = next;
  newNode->liefCount = node->liefCount - (u_int8_t) lcount - (u_int8_t) 1;
  node->liefCount = (u_int8_t) lcount + (u_int8_t) 1;
}

/** Initialize your data structure here. */
BTree::BTree() {
  root = new Node();
}

BTree::Node *BTree::getRoot() const { return root; }

/** Inserts a word into the trie. */
void BTree::insert(std::string word) {
  // Handle the 1 child for root. Like first input
  if (root->children[0] == nullptr) {
    addNode(word, root);
    return;
  }

  // Node lookup
  Node *seekNode = lookupNode(word, root);
  bool isTail = false;
  if (nullptr == seekNode) {
    isTail = true;
    seekNode = getTailNode(root);
  }

  // rebalance tree TODO: of course better to do this async, but it's just example anyway.
  if (seekNode->liefCount + 1 > MAX_CHILDREN * K_NODE_CAPACITY) {
    splitLiefNode(seekNode);
    if (isTail) {
      seekNode = getTailNode(root);
    } else {
      seekNode = lookupNode(word, seekNode->parent);
    }
  }

  // lief traverse
  Lief *seekLief = traverseLief(word, seekNode);

  // Insert lines
  Lief *next = nullptr, *prev;
  prev = seekLief;

  if (seekLief == nullptr) {
    next = seekNode->lief;
  } else if (seekLief->next != nullptr) {
    next = seekLief->next;
  }

  Lief *newLief = addLief(word, prev, next);
  if (seekLief == nullptr) {
    seekNode->lief = newLief;
  }
  seekNode->liefCount++;

  if (next == nullptr) {
    changeMax(newLief->v, seekNode);
  }
}

/** Returns if the word is in the trie. */
std::string BTree::search(std::string word) {
  // Node lookup
  Node *seekNode = lookupNode(word, root);

  // lief traverse
  if (Lief *lief = traverseLiefToStrongEqual(word, seekNode)) {
    return lief->v;
  }

  return "Nothing was found.";
}

/** Returns if there is any word in the trie that starts with the given prefix. */
std::string BTree::startsWith(std::string prefix) {
  // Node lookup
  Node *seekNode = lookupNode(prefix, root);

  // lief traverse
  if (Lief *lief = traverseLiefToStrongEqual(prefix, seekNode, true)) {
    return lief->v;
  }

  return "Nothing was found.";
}
