//
// Created by Vitaliy on 9/27/20.
//
#include <string_view>

void testStringViewExample() {
  std::string_view sv = "asdasdasdasdasdasdad";
  //sv += "asd";         // bad, std::string_view is a read only data structure
  std::cout << sv << std::endl;
}

void testPointerVsReference() {
  int a = 10;
  int *pa = &a;
  int &ra = a;

  *pa = 11;
  std::cout << "Original a: " << a << std::endl;
  std::cout << "Ref to a: " << ra << std::endl;

  ra = 12;
  std::cout << "Original a: " << a << std::endl;
  std::cout << "Pointer to a: " << *pa << std::endl;
}

void testPointersComparisonOperator() {
  int a = 10;
  int *pa1 = &a;
  int *pa2 = &a;
  if (pa1 > pa2)
    std::cout << "pa1 > pa2";
  else
    std::cout << "pa1 < pa2";
}