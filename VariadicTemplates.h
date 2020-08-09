//
// Created by Vitaliy on 8/3/20.
//

#ifndef TREE_VARIADICTEMPLATES_H
#define TREE_VARIADICTEMPLATES_H

#include <iostream>

class VariadicTemplates {
public:
    template<typename T>
    void print(const T &t);

    template<typename ...T>
    void print(const T & ... t);
};

#endif //TREE_VARIADICTEMPLATES_H
