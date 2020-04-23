//
// Created by Vitaliy on 2019-09-26.
//

void rvalue_lvalue() {
  vector<int> x = {1,2,3,4,5,6};
  vector<int> y = move(x);
//  vector<int>&z = y;
  vector<int>&&z = move(y);

  cout << "X is empty now:" << endl;
  for_each(x.begin(), x.end(), [](int a){cout << a << endl;});
  cout << "===========" << endl;

  cout << "Y got the ownership on memory belongs to X before:" << endl;
  for_each(y.begin(), y.end(), [](int a){cout << a << endl;});
  cout << "===========" << endl;

//  cout << "Y':" << endl;
//  z.clear();
//  for_each(y.begin(), y.end(), [](int a){cout << a << endl;});
//  cout << "===========" << endl;

  cout << "Z:" << endl;
  y.clear();
  for_each(z.begin(), z.end(), [](int a){cout << a << endl;});
}