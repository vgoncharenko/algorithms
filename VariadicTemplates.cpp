//
// Created by Vitaliy on 8/3/20.
//

#include "VariadicTemplates.h"

template<typename T>
void VariadicTemplates::print(const T &t) {
  std::cout << "[" << t << "]";
}

template<typename... T>
void VariadicTemplates::print(const T & ... t) {
  (void)std::initializer_list<int>{(print(t), 0)...};
}