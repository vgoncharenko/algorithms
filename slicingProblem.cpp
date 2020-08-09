//
// Created by Vitaliy on 8/9/20.
//

#include "slicingProblem.h"
#include <vector>
#include <memory>
#include <iostream>

void do_something3(const fileBase &f) {
  std::cout << f.b << ":" << f.x << std::endl;
}

void do_something1(std::vector<std::unique_ptr<fileBase>> v) {
  for (auto &it: v) {
    std::cout << it->b << ":" << it->x;
  }
}

void do_something2(const std::vector<fileBase> &v) {
  for (fileBase it: v) {
    std::cout << it.b << ":" << it.x << std::endl;
  }
}

void slicingProblem::slicingProblemTest1() {
//  std::vector<std::unique_ptr<fileBase>> v = {
//         std::make_unique<fileBase>(fileBase()),
//         std::make_unique<fileDerived>(fileDerived())
//  };
//  do_something1(v);

  std::vector<fileBase> v2 = {
          new fileBase(),
          new fileDerived() // slicing problem
  };
//  do_something2(v2);

  fileDerived d;
  do_something3(d);
}
