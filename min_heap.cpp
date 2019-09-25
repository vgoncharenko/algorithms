//
// Created by Vitaliy on 2019-09-19.
//

#include "min_heap.h"

Term::Term(string _term, uint8_t _frequency) {
  term = move(_term);
  frequency = _frequency;
}

uint8_t Term::getFrequency() const { return frequency; }

int TermComparator::operator()(const Term &t1, const Term &t2) {
  return t1.getFrequency() > t2.getFrequency();
}
