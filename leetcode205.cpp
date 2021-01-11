//
// Created by Vitaliy on 1/8/21.
//

#include <string>
#include <unordered_map>

bool isIsomorphic(std::string s, std::string t) {
    std::unordered_map<char, char> m1(26), m2(26);
    for (size_t i=0; i<s.size(); ++i) {
        char c1 = s[i];
        bool replaced = false;
        if (auto match = m1.find(s[i]); match != m1.end()) { c1 = m1[s[i]]; replaced = true; }

        char c2 = t[i];
        if (auto match = m2.find(t[i]); match != m2.end()) { c2 = m2[t[i]]; replaced = true; }

        if ((c1 != t[i] || c2 != s[i]) && replaced) return false;

        if (!replaced) {
            m1[s[i]] = t[i];
            m2[t[i]] = s[i];
        }
    }

    return true;
}

void isIsomorphicTest() {
//    isIsomorphic("baba", "abba");
    isIsomorphic("badc", "baba");
}


double myPow(double x, int n) {
    if (n == 0) return 1;
    bool negativ = n < 0;
    n = abs(n);

    double result = x;
    while (--n > 0) {
        result *= x;
    }

    return negativ ? 1/result : result;
}

void testPow() {
//    myPow(2, 10);
    myPow(2, -2);
}
