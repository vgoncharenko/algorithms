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

