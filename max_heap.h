//
// Created by Vitaliy on 2019-09-19.
//

#ifndef TREE_MAX_HEAP_H
#define TREE_MAX_HEAP_H

#include <iostream>



struct TermMax {
    std::string term = "";
    unsigned long value = 0;
public:
    TermMax(std::string _term = "", unsigned long _value = 0);

    unsigned long getValue() const;
};

// To compare two terms
class TermMaxComparator {
public:
    int operator()(const TermMax &t1, const TermMax &t2);
};


#endif //TREE_MIN_HEAP_H
