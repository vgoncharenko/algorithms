//
// Created by Vitaliy on 2019-09-26.
//

bool alg_1_1(string s)
{
  u_int64_t mask = 0,
            bit = 0;
  for (int i=0; i<s.size(); i++) {
    bit = 1 << (s[i] - 'a');
    if (mask & bit) {
      return false;
    } else {
      mask |= bit;
    }
  }

  return true;
}

void testAlg_1_1()
{
  string variationName,
         s;
  bool expected,
       res;

  //
  variationName = "ex1";
  s = "asdasdasd";
  res = alg_1_1(s);
  expected = false;
  if (res != expected)
    cout << "FAIL " + variationName + ": testAlg_1_1: \nres: " << res << "\nexpected: " << expected << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  variationName = "ex2";
  s = "asdfghjklopiuytrewq";
  res = alg_1_1(s);
  expected = true;
  if (res != expected)
    cout << "FAIL " + variationName + ": testAlg_1_1: \nres: " << res << "\nexpected: " << expected << endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}


vector<int> alg_5_3_prepareVector(int v) {
  if (v == 0) return {0};
  vector<int> res;
  const uint8_t MAX_RANGE = 64;
  int range = 0;
  while (v > 0) {
    if (range++ > MAX_RANGE)
      return {};
    if (v & 1)
      res.push_back(1);
    else
      res.push_back(0);
    v >>= 1;
  }
  reverse(res.begin(), res.end());
  return res;
}

int alg_5_3(int val)
{
  vector<int> v = alg_5_3_prepareVector(val);
  if (v.empty()) return 0;
  unsigned long n = v.size();
  if (n == 1) return 1;
  int i = 0, j = 1, k = 1;
  while(j < n) {
    if(v[j++] == 0) k--;
    if(k<0 && v[i++] == 0) k++;
  }

  return j-i+1+k > n ? n : j - i + 1 + k;
}

void testAlg_5_3()
{
  string variationName;
  int v;
  int expected,
      res;

  //
  variationName = "ex1";
  v = 490623;
  res = alg_5_3(v);
  expected = 9;
  if (res != expected)
    cout << "FAIL " + variationName + ": testAlg_5_3: \nres: " << res << "\nexpected: " << expected << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  variationName = "ex2";
  v = 63;
  res = alg_5_3(v);
  expected = 6;
  if (res != expected)
    cout << "FAIL " + variationName + ": testAlg_5_3: \nres: " << res << "\nexpected: " << expected << endl;
  else
    cout << variationName + " SUCCESS!" << endl;

  variationName = "ex3";
  v = 0;
  res = alg_5_3(v);
  expected = 1;
  if (res != expected)
    cout << "FAIL " + variationName + ": testAlg_5_3: \nres: " << res << "\nexpected: " << expected << endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void alg_8_6(int n, stack<int> &s1, stack<int> &s2, stack<int> &s3)
{
  if (n <= 0) return;
  alg_8_6(n-1, s1, s3, s2);
  s3.push(s1.top());
  s1.pop();
  alg_8_6(n-1, s2, s1, s3);
}

void testAlg_8_6()
{
  stack<int> s1, s2, s3;
  s1.push(5);
  s1.push(4);
  s1.push(3);
  s1.push(2);
  s1.push(1);
  alg_8_6(5, s1, s2, s3);
}
