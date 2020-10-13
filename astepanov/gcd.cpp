//
// Created by Vitaliy on 10/11/20.
//

template<typename T>
T gcd1(T a, T b) {
  if (a == b) return a;
  else if (a > b) return gcd1(a-b, b);
  else return gcd1(a, b-a);
}

template<typename T>
T gcd2(T a, T b) {
  if (a % b == 0) return b;
  else if (a > b) return gcd2(b, a%b);
  else return gcd2(a, b%a);
}


void test_gcd() {
  int a = 196;
  int b = 42;
  int expected = 14;
  int result;

  measure([&a, &b, &result]{ result = gcd1(a, b); });
  assert(expected == result);
  result = 0;

  measure([&a, &b, &result]{ result = gcd2(a, b); });
  assert(expected == result);
  result = 0;
}
