//
// Created by Vitaliy on 2019-09-23.
//

#include "b_tree.h"

/*
 * =================== TESTS ZONE ====================
 */

void testCheckCount(BTree::Node *node) {
  if (node->childCount > 0) {
    u_int8_t nodeCount = 0;
    for (u_int8_t inode = 0; inode < node->childCount; inode++) {
      if (node->children[inode] == NULL) {
        break;
      }
      nodeCount++;
      testCheckCount(node->children[inode]);
    }

    if (nodeCount != node->childCount) {
      std::cout << printf("FAIL: Node element count:\nActual: %d;\nExpected: %d", nodeCount, node->childCount)
           << std::endl;
    }
  }

  if (node->liefCount > 0) {
    u_int8_t liefCount = 0;
    BTree::Lief *itemLief = node->lief;
    for (u_int8_t ilief = 0; ilief < node->liefCount; ilief++) {
      if (itemLief == nullptr) {
        break;
      }
      liefCount++;
      itemLief = itemLief->next;
    }

    if (liefCount != node->liefCount) {
      std::cout << printf("FAIL: Lief count:\nActual: %d;\nExpected: %d", liefCount, node->liefCount) << std::endl;
    }
  }
}

void testInsert(BTree *tree) {
  tree->insert("apple");
  tree->insert("apple2");
  tree->insert("apple3");
  tree->insert("apple1");
  tree->insert("apple1");
  tree->insert("apple1");
  tree->insert("apple2");
  tree->insert("apple2");
  tree->insert("apple3");
  tree->insert("apple4555");
  tree->insert("apple4565");

  // child count test
  if (tree->getRoot()->childCount != 1) {
    std::cout << "FAIL: childCount" << std::endl;
  }

  // test first
  if (tree->getRoot()->children[0]->lief->v != "apple") {
    std::cout << "FAIL: first element" << std::endl;
  }

  // test second
  if (tree->getRoot()->children[0]->lief->next->v != "apple1") {
    std::cout << "FAIL: second element" << std::endl;
  }

  // test third
  if (tree->getRoot()->children[0]->lief->next->next->v != "apple1") {
    std::cout << "FAIL: third element" << std::endl;
  }

  // test fifth
  if (tree->getRoot()->children[0]->lief->next->next->next->next->v != "apple2") {
    std::cout << "FAIL: fifth element" << std::endl;
  }

  // test list links
  if (tree->getRoot()->children[0]->lief->next->prev->v != "apple"
      || tree->getRoot()->children[0]->lief->next->next->prev->v != "apple1"
      || tree->getRoot()->children[0]->lief->next->next->prev->next->v != "apple1"
          ) {
    std::cout << "FAIL: links" << std::endl;
  }

  // test of node splitting
  u_int16_t i = 2000;
  while (--i > 0) {
    tree->insert("bar" + std::to_string(random()));
    testCheckCount(tree->getRoot());
  }

  //TODO: test balancing.
}

void testSearch(BTree *tree) {
  std::string res = tree->search("apple3");
  if ("apple3" != res) {
    std::cout << "Fail search: " + res << std::endl;
  }
  res = tree->search("apple3123123");
  if ("Nothing was found." != res) {
    std::cout << "Fail search: " + res << std::endl;
  }
}

void testPrefixSearch(BTree *tree) {
  std::string res = tree->startsWith("apple4");
  if ("apple4555" != res) {
    std::cout << "Fail PrefixSearch: " + res << std::endl;
  }
  res = tree->startsWith("apple45657");
  if ("Nothing was found." != res) {
    std::cout << "Fail PrefixSearch: " + res << std::endl;
  }
  res = tree->startsWith("apple");
  if ("apple" != res) {
    std::cout << "Fail PrefixSearch: " + res << std::endl;
  }
}

void testBTree() {
  auto *tree = new BTree();
  testInsert(tree);
  testSearch(tree);
  testPrefixSearch(tree);
}

/*
 * =================== std::end TESTS ZONE ====================
 */

