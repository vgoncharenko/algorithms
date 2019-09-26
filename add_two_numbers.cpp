//
// Created by Vitaliy on 2019-09-25.
//

#include "add_two_numbers.h"

vector<int> AddTwoNumbers::sum(vector<int> input1, vector<int> input2){
  vector <int> output;
  unsigned long count1 = input1.size(), count2 = input2.size();
  int carryBit = 0;

  // align inputs
  if (count1 > count2) {
    for (int i = (int)count2; i < count1; i++) {
      input2[i] = 0;
    }
  } else {
    for (int i = (int)count1; i < count2; i++) {
      input1[i] = 0;
    }
  }

  for (int i = 0; i < input1.size(); i++) {
    output.push_back(input1[i] + input2[i] + carryBit);
    carryBit = 0;
    if (output[i] >= 10) {
      carryBit = 1;
      output[i] -= 10;
    }
  }
  if (carryBit) {
    output[input1.size()] = carryBit;
  }

  return output;
}