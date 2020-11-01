//
// Created by Vitaliy on 2019-09-26.
//
#include <vector>
#include <iostream>

void rvalue_lvalue() {
  std::vector<int> x = {1,2,3,4,5,6};
  std::vector<int> y = move(x);
//  std::vector<int>&z = y;
  std::vector<int>&&z = move(y);

  std::cout << "X is empty now:" << std::endl;
  for_each(x.begin(), x.end(), [](int a){std::cout << a << std::endl;});
  std::cout << "===========" << std::endl;

  std::cout << "Y got the ownership on memory belongs to X before:" << std::endl;
  for_each(y.begin(), y.end(), [](int a){std::cout << a << std::endl;});
  std::cout << "===========" << std::endl;

//  std::cout << "Y':" << std::endl;
//  z.clear();
//  for_each(y.begin(), y.end(), [](int a){cout << a << std::endl;});
//  std::cout << "===========" << std::endl;

  std::cout << "Z:" << std::endl;
  y.clear();
  for_each(z.begin(), z.end(), [](int a){std::cout << a << std::endl;});
}