//
// Created by Vitaliy on 2019-09-19.
//

#include "max_heap.h"

TermMax::TermMax(string _term, unsigned long _value) {
  term = move(_term);
  value = _value;
}

unsigned long TermMax::getValue() const { return value; }

int TermMaxComparator::operator()(const TermMax &t1, const TermMax &t2) {
  return t1.getValue() < t2.getValue();
}
