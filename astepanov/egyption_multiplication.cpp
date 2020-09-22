//
// Created by Vitaliy on 9/21/20.
//
#include <iostream>

template<typename T>
T egpt_mult1(T x, T y) {
  T result = 0;
  for (T i=0; i<y; i++) {
    result += x;
  }
  return result;
}

template<typename T>
T egpt_mult2(T x, T y) {
  T min_v = min(x, y);
  T max_v = max(x, y);
  T result = max_v;
  for (T i=1; i<min_v; i++) {
    result += max_v;
  }
  return result;
}

/*
 * a = 4;
 * b = 3;
 *
 * result = a + a + a + a = (a + a) + (a + a)
 */
template<typename T>
T half(T n) {
  return n>>1;
}

template<typename T>
T isOdd(T x) {
  return x & 0x1;
}

template<typename T>
T egpt_mult3_helper(T x, T n) {
  if (n == 1) return x;
  T result = egpt_mult3_helper(x + x, half(n));
  if (isOdd(n)) {
    result += x;
  }

  return result;
}

template<typename T>
T egpt_mult3(T x, T y) {
  T min_v = min(x, y);
  T max_v = max(x, y);

  return egpt_mult3_helper(max_v, min_v);;
}

/**
 * Small optimization for if (n == 1)
 */

template<typename T>
T egpt_mult4_helper(T r, T x, T n) {
  if (isOdd(n)) {
    if (n == 1) return r + x;
    r += x;
  }

  return egpt_mult4_helper(r, x + x, half(n));
}

template<typename T>
T egpt_mult4(T x, T y) {
  T min_v = min(x, y);
  T max_v = max(x, y);

  return egpt_mult4_helper(max_v, max_v, min_v - 1);
}


/**
 * No Recursion.
 */

template<typename T>
T egpt_mult5_helper(T r, T x, T n) {
  while(true) {
    if (isOdd(n)) {
      if (n == 1) return r + x;
      r += x;
    }

    n = half(n);
    x += x;
  }
}

template<typename T>
T egpt_mult5(T x, T y) {
  T min_v = min(x, y);
  T max_v = max(x, y);

  return egpt_mult5_helper(max_v, max_v, min_v - 1);
}

/**
 * Final version.
 */

template<typename T>
T egpt_mult6_helper(T r, T x, T n) {
  while(true) {
    if (isOdd(n)) {
      r += x;
      if (n == 1) return r;
    }

    n = half(n);
    x += x;
  }
}

template<typename T>
T egpt_mult6(T x, T y) {
  T min_v = min(x, y);
  T max_v = max(x, y);

  while (!isOdd(min_v)) {
    max_v += max_v;
    min_v = half(min_v);
  }
  if (min_v == 1) return max_v;

  return egpt_mult6_helper(max_v, max_v + max_v, half(min_v - 1));
}

/**
 * Processor mult
 */

template<typename T>
T egpt_mult7(T x, T y) {
  return x * y;
}

void testEgyptMult() {
//  long x = 9845623;
//  long y = 98459903;
//  long expected = 969399085554569;

//  long x = 8388608;
//  long y = 67108865;
//  long expected = 562949961809920;

  long x = 8388609;
  long y = 67108865;
  long expected = 562950028918785;

//  long x = 99;
//  long y = 100;
//  long expected = 9900;
  long result = 0;

  measure( [&x, &y, &result]{ result = egpt_mult1(x, y); } );
  assert(expected == result);

  result = 0;
  measure( [&x, &y, &result]{ result = egpt_mult2(x, y); } );
  assert(expected == result);

  result = 0;
  measure( [&x, &y, &result]{ result = egpt_mult3(x, y); } );
  assert(expected == result);

  result = 0;
  measure( [&x, &y, &result]{ result = egpt_mult4(x, y); } );
  assert(expected == result);

  result = 0;
  measure( [&x, &y, &result]{ result = egpt_mult5(x, y); } );
  assert(expected == result);

  result = 0;
  measure( [&x, &y, &result]{ result = egpt_mult6(x, y); } );
  assert(expected == result);

  result = 0;
  measure( [&x, &y, &result]{ result = egpt_mult7(x, y); } );
  assert(expected == result);
}