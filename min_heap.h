//
// Created by Vitaliy on 2019-09-19.
//

#ifndef TREE_MIN_HEAP_H
#define TREE_MIN_HEAP_H

#include <iostream>

using namespace std;

struct Term {
    string term = "";
    uint8_t frequency = 0;
public:
    explicit Term(string _term = "", uint8_t _frequency = 0);
    uint8_t getFrequency() const;
};

// To compare two terms
class TermComparator
{
public:
    int operator() (const Term& t1, const Term& t2);
};


#endif //TREE_MIN_HEAP_H
