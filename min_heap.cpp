//
// Created by Vitaliy on 2019-09-19.
//

#include "min_heap.h"

Term::Term(std::string _term, uint8_t _value) {
  term = move(_term);
  value = _value;
}

uint8_t Term::getValue() const { return value; }

int TermComparator::operator()(const Term &t1, const Term &t2) {
  return t1.getValue() > t2.getValue();
}
