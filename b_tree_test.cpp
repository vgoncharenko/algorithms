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
      cout << printf("FAIL: Node element count:\nActual: %d;\nExpected: %d", nodeCount, node->childCount)
           << endl;
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
      cout << printf("FAIL: Lief count:\nActual: %d;\nExpected: %d", liefCount, node->liefCount) << endl;
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
    cout << "FAIL: childCount" << endl;
  }

  // test first
  if (tree->getRoot()->children[0]->lief->v != "apple") {
    cout << "FAIL: first element" << endl;
  }

  // test second
  if (tree->getRoot()->children[0]->lief->next->v != "apple1") {
    cout << "FAIL: second element" << endl;
  }

  // test third
  if (tree->getRoot()->children[0]->lief->next->next->v != "apple1") {
    cout << "FAIL: third element" << endl;
  }

  // test fifth
  if (tree->getRoot()->children[0]->lief->next->next->next->next->v != "apple2") {
    cout << "FAIL: fifth element" << endl;
  }

  // test list links
  if (tree->getRoot()->children[0]->lief->next->prev->v != "apple"
      || tree->getRoot()->children[0]->lief->next->next->prev->v != "apple1"
      || tree->getRoot()->children[0]->lief->next->next->prev->next->v != "apple1"
          ) {
    cout << "FAIL: links" << endl;
  }

  // test of node splitting
  u_int16_t i = 2000;
  while (--i > 0) {
    tree->insert("bar" + to_string(random()));
    testCheckCount(tree->getRoot());
  }

  //TODO: test balancing.

  cout << "SUCCESS!" << endl;
}

void testSearch(BTree *tree) {
  string res = tree->search("apple3");
  if ("apple3" != res) {
    cout << "Fail search: " + res << endl;
  }
  res = tree->search("apple3123123");
  if ("Nothing was found." != res) {
    cout << "Fail search: " + res << endl;
  }
}

void testPrefixSearch(BTree *tree) {
  string res = tree->startsWith("apple4");
  if ("apple4555" != res) {
    cout << "Fail PrefixSearch: " + res << endl;
  }
  res = tree->startsWith("apple45657");
  if ("Nothing was found." != res) {
    cout << "Fail PrefixSearch: " + res << endl;
  }
  res = tree->startsWith("apple");
  if ("apple" != res) {
    cout << "Fail PrefixSearch: " + res << endl;
  }
}

void testBTree() {
  auto *tree = new BTree();
  testInsert(tree);
  testSearch(tree);
  testPrefixSearch(tree);
}

/*
 * =================== END TESTS ZONE ====================
 */

