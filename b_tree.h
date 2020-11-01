//
// Created by Vitaliy on 2019-09-23.
//

#ifndef TREE_B_TREE_H
#define TREE_B_TREE_H

#include <iostream>
#include <vector>
#include <string>


class BTree {
public:
    const static int MAX_CHILDREN = 100;
    constexpr static float K_NODE_CAPACITY = 0.66;
    struct Lief {
        Lief *next;
        Lief *prev;
        std::string v;
    };

    struct Node {
        Node *parent;
        Node *next;
        Node *prev;
        Node *children[MAX_CHILDREN];
        u_int8_t childCount = 0;
        u_int8_t liefCount = 0;
        Lief *lief;
        std::string max;
    };

    BTree();

    Node *getRoot() const;

    void insert(std::string word);

    std::string search(std::string word);

    std::string startsWith(std::string prefix);

private:
    Node *root;

    Node *addNode(std::string v = "", Node *parent = nullptr, Node *prev = nullptr, Node *next = nullptr);

    Lief *addLief(std::string v = "", Lief *prev = nullptr, Lief *next = nullptr);

    void changeMax(std::string newMax, Node *node);

    Lief *traverseLief(const std::string &term, const Node *seekNode) const;

    Lief *traverseLiefToStrongEqual(const std::string &term, const Node *seekNode, bool prefix = false) const;

    Node *lookupNode(const std::string &term, Node *node) const;

    Node *getTailNode(Node *node) const;

//    Node *lookupNode2(const std::string &term, Node *node) const;

    void splitMiddleNode(Node *node);

    void splitLiefNode(Node *node);
};


#endif //TREE_B_TREE_H
