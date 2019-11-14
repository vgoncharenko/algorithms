//
// Created by Vitaliy on 2019-09-26.
//

#include "longest_palindrome.h"

void ruTest (string input, string expected, string variationName) {
  auto solution = new LongestPalindrome();
  string result = solution->find3(input);
  if (expected != result)
    cout << "FAIL " + variationName + ": testLongestPalindrome: \nexpected: " << expected << "\nactual: " << result << " size: " << result.length() << endl;
  else
    cout << variationName + " SUCCESS!" << endl;
}

void testLongestPalindrome() {
  string input,
         expected,
         variationName;

  variationName = "ex0";
  input = "saippuakivikauppias";
  expected = "saippuakivikauppias";
  ruTest(input, expected, variationName);

  variationName = "ex1";
  input = "asdasdasdsaippuakivikauppias";
  expected = "saippuakivikauppias";
  ruTest(input, expected, variationName);

  variationName = "ex2";
  input = "babad";
  expected = "bab";
  ruTest(input, expected, variationName);

  variationName = "ex3";
  input = "acbdft";
  expected = "c";
  ruTest(input, expected, variationName);

  variationName = "ex4";
  input = "ac";
  expected = "c";
  ruTest(input, expected, variationName);

  variationName = "ex5";
  input = "a";
  expected = "a";
  ruTest(input, expected, variationName);

  variationName = "ex6";
  input = "cbbd";
  expected = "bb";
  ruTest(input, expected, variationName);

  variationName = "ex7";
  input = "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth";
  expected = "ranynar";
  ruTest(input, expected, variationName);

  variationName = "ex8";
  input = "aaaa";
  expected = "aaaa";
  ruTest(input, expected, variationName);

  variationName = "ex9";
  input = "abcdasdfghjkldcba";
  expected = "b";
  ruTest(input, expected, variationName);

  variationName = "ex10";
  input = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";
  expected = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
  ruTest(input, expected, variationName);

  variationName = "ex11";
  input = "cbcdcbedcbc";
  expected = "bcdcb";
  ruTest(input, expected, variationName);
}
