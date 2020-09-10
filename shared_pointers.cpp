//
// Created by Vitaliy on 9/9/20.
//

#include <memory>
#include <iostream>

class SharedPTest {
public:
    int x = 10;
};

void constSharedF(std::shared_ptr<const SharedPTest> p) {
//  p->x = 20;
}

void constSharedF2(std::shared_ptr<const SharedPTest> p1, std::shared_ptr<const SharedPTest> p2) {
//  *p1 = *p2;
}

void sharedPointerTest() {
  std::shared_ptr<SharedPTest> p = std::make_shared<SharedPTest>();
  std::shared_ptr<SharedPTest> p2 = std::make_shared<SharedPTest>();
  constSharedF(p);
  std::cout << p->x << std::endl;
  constSharedF2(p, p2);
  std::cout << p->x << std::endl;
}

