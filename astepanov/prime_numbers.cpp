//
// Created by Vitaliy on 9/23/20.
//

#include <cstddef>


/**
 * Naive approach O(n^2)
 */
template<typename T>
vector<T> prime1(T n) {
  if (n == 0) return {};
  vector<T> result;

  for (T i=n; i>1; i--) {
    bool isPrime = true;
    for (T j=2; j<i-1; j++) {
      if (i%j == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime) {
      result.push_back(i);
    }
  }
  std::reverse(result.begin(), result.end());

  return result;
}


/**
 * Sieve of Eratosthenes for all positive integers O(n*sqrt(n))
 *
 * A = {1 2 3 4 5 6 7 8 9 10 11 12}
 * P = {  2 3 4 5 6 7 8 9 10 11 12}
 */
template<typename T>
vector<T> prime2(T n) {
  if (n == 0) return {};
  vector<pair<T, bool>> v1(n);
  for(T i=2; i<=n; i++) {
    v1[i-2] = std::make_pair(i, true);
  }

  for (T i=0; i<=sqrt(n); i++) {
    if (v1[i].second == false) continue;
    for (T j=i+v1[i].first; j<=n; j+=v1[i].first) {
      v1[j].second = false;
    }
  }

  vector<T> result;
  for (T i=0; i<n; i++) {
    if (v1[i].second)
      result.push_back(std::move(v1[i].first));
  }

  return result;
}

/**
 * Sieve of Eratosthenes for odd positive integers O(n/2*sqrt(n/2))
 *
 * A = {1 2 3 4 5 6 7 8 9 10 11 12}
 * P = {  2 3   5   7        11   } // only odd numbers
 * B = {3 5 7 9 11}
 */
template<typename T>
vector<T> prime3(T n) {
  if (n == 0) return {};
  vector<pair<T, bool>> v1;
  for(T i=3; i<=n; i+=2) {
    v1.push_back(std::make_pair(i, true));
  }

  for (T i=0; v1[i].first<=sqrt(n); i++) {
    for (size_t j=i+v1[i].first; j<=v1.size(); j+=v1[i].first) {
      v1[j].second = false;
    }
  }

  vector<T> result;
  result.push_back(2);
  for (size_t i=0; i<v1.size(); i++) {
    if (v1[i].second)
      result.push_back(std::move(v1[i].first));
  }

  return result;
}

/**
 * Sieve of Eratosthenes for odd positive integers with value as bool (true/false) O(n/2*sqrt(n/2))
 *
 * A = {1 2 3 4 5 6 7 8 9 10 11 12}
 * P = {  2 3   5   7        11   } // only odd numbers
 * B = {3 5 7 9 11}
 */
template<typename T>
vector<T> prime4(T n) {
  if (n == 0) return {};
  vector<bool> v1(n/2-1, true);

  for (size_t i=0, value = 3, startIndex = 3; startIndex < v1.size(); i++, value = ((i<<1) + 3), startIndex = (value<<1)+i) {
    for (T j=startIndex; j<=v1.size(); j+=value) {
      v1[j] = false;
    }
  }

  vector<T> result;
  result.push_back(2);
  for (size_t i=0; i<v1.size(); i++) {
    if (v1[i]) result.push_back((i<<1) + 3);
  }

  return result;
}

/**
 * Sieve of Eratosthenes for odd positive integers with bitmap as value (1 or 0) O(n/2*sqrt(n/2))
 *
 * A = {1 2 3 4 5 6 7 8 9 10 11 12}
 * P = {  2 3   5   7        11   } // only odd numbers
 * B = {3 5 7 9 11}
 */
template<typename T>
vector<T> prime5(T n) {
  if (n == 0) return {};
  T m = n/2-1;
  u_int64_t bit = 1;
  vector<u_int64_t> v1(m/64+1, INT64_MAX);

  for (size_t i=0, value = 3, startIndex = 3; startIndex < n; i++, value = ((i<<1) + 3), startIndex = (value<<1)+i) {
    for (T j=startIndex; j<=m; j+=value) {
      v1[j/64] &= ~(bit<<(j%64));
    }
  }

  vector<T> result;
  result.push_back(2);
  for (size_t i=0; i<m; i++) {
    if (v1[i/64] & (bit<<(i%64)))
      result.push_back((i<<1) + 3);
  }

  return result;
}

/**
 * Sieve of Eratosthenes for odd positive with std::byte as a bitmap value (1 or 0) O(n/2*sqrt(n/2))
 *
 * A = {1 2 3 4 5 6 7 8 9 10 11 12}
 * P = {  2 3   5   7        11   } // only odd numbers
 * B = {3 5 7 9 11}
 */
template<typename T>
vector<T> prime6(T n) {
  if (n == 0) return {};
  T m = n/2-1;
  std::byte bit { 0b0000'0001 };
  std::byte fullMask { 0b1111'1111 };
  vector<std::byte> v1(m/8+1, fullMask);

  for (size_t i=0, value = 3, startIndex = 3; startIndex < n; i++, value = ((i<<1) + 3), startIndex = (value<<1)+i) {
    for (T j=startIndex; j<=m; j+=value) {
      v1[j/8] &= ~(bit<<(j%8));
    }
  }

  vector<T> result;
  result.push_back(2);
  for (size_t i=0; i<m; i++) {
    if (std::byte b = (bit << (i % 8));
            (v1[i / 8] & b) == b)
      result.push_back((i << 1) + 3);
  }

  return result;
}

/**
 * Results for x = 1'0'000:
 *
Naive approach O(n^2)
Median of time taken by function: 46'738'178 nanoseconds


Sieve of Eratosthenes for all positive integers O(n*sqrt(n)):
Median of time taken by function: 575'578 nanoseconds


Sieve of Eratosthenes for odd positive integers O(n/2*sqrt(n/2)):
Median of time taken by function: 499'823 nanoseconds


Sieve of Eratosthenes for odd positive integers with value as bool (true/false) O(n/2*sqrt(n/2)):
Median of time taken by function: 407'095 nanoseconds


Sieve of Eratosthenes for odd positive integers with bitmap as value (1 or 0) O(n/2*sqrt(n/2)):
Median of time taken by function: 151'625 nanoseconds


Sieve of Eratosthenes for odd positive with std::byte as bitmap value (1 or 0) O(n/2*sqrt(n/2)):
Median of time taken by function: 292'869 nanoseconds
 */
void testPrimeNumbers() {
  long x = 1'0'000;
  vector<long> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
  vector<long> result(x);

  std::cout << "Naive approach O(n^2)" << std::endl;
  measure( [&x, &result]{ result = prime1(x); } );
  //assert(expected == result);

  std::cout << "\n\nSieve of Eratosthenes for all positive integers O(n*sqrt(n)):" << std::endl;
  measure( [&x, &result]{ result = prime2(x); } );
  //assert(expected == result);

  std::cout << "\n\nSieve of Eratosthenes for odd positive integers O(n/2*sqrt(n/2)):" << std::endl;
  measure( [&x, &result]{ result = prime3(x); } );
  //assert(expected == result);

  std::cout << "\n\nSieve of Eratosthenes for odd positive integers with value as bool (true/false) O(n/2*sqrt(n/2)):" << std::endl;
  measure( [&x, &result]{ result = prime4(x); } );
  //assert(expected == result);

  std::cout << "\n\nSieve of Eratosthenes for odd positive integers with bitmap as value (1 or 0) O(n/2*sqrt(n/2)):" << std::endl;
  measure( [&x, &result]{ result = prime5(x); } );
  //assert(expected == result);

  std::cout << "\n\nSieve of Eratosthenes for odd positive with std::byte as bitmap value (1 or 0) O(n/2*sqrt(n/2)):" << std::endl;
  measure( [&x, &result]{ result = prime6(x); } );
  //assert(expected == result);
}
