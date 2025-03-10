/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file BigIntegerTest.cpp
 * @brief Main testing file BigInteger ADT
 * @status: working / tested
 */

#include <iostream>
#include <stdexcept>

#include "BigInteger.h"

/**
 * @brief Custom assertion function that throws an exception on failure.
 * @param condition The condition to check.
 * @param message The error message to display if the condition is false.
 */
void expect(bool condition, const std::string &message) {
  if (!condition) {
    throw std::runtime_error("Test failed: " + message);
  }
}

/**
 * @brief Runs a test function and reports success or failure.
 * @param test_func The test function to run.
 * @param test_name The name of the test.
 */
int run_test(void (*test_func)(), const std::string &test_name) {
  try {
    test_func();
    std::cout << test_name << ": PASSED\n";
  } catch (const std::exception &e) {
    std::cerr << test_name << " FAILED: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return 1;
}

/**
 * @brief Runs a test function and reports success or failure.
 * @param test_func The test function to run.
 * @param test_name The name of the test.
 */
int run_specific_test(int (*test_func)(), const std::string &test_name) {
  try {
    std::string res = "Expected 0: " + test_name;
    expect(test_func, res);
    std::cout << test_name << ": PASSED\n";
  } catch (const std::exception &e) {
    std::cerr << test_name << " FAILED: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return 1;
}

/**
 * @brief Tests the constructors of BigInteger.
 */
void test_constructors() {
  BigInteger A;
  expect(A.sign() == 0, "Default constructor should have sign 0");
  BigInteger B(12345);
  expect(B.sign() == 1, "Positive number should have sign 1");
  BigInteger C(-12345);
  expect(C.sign() == -1, "Negative number should have sign -1");
  BigInteger D("00000");
  expect(D.sign() == 0, "String '00000' should have sign 0");
  BigInteger E("12345");
  expect(E.sign() == 1, "String '12345' should have sign 1");
  BigInteger F("-12345");
  expect(F.sign() == -1, "String '-12345' should have sign -1");
  BigInteger G = F;
  expect(G.sign() == -1, "Copy constructor should have sign -1");
  BigInteger H = B;
  expect(H.sign() == 1, "Copy constructor should have sign 1");
}

void test_addition() {
  // positives
  BigInteger A(14);
  BigInteger B(2009);
  BigInteger res1 = A.add(B);
  expect(res1.sign() == 1, "positive addition should have sign 1");

  // positives
  BigInteger X(-14);
  BigInteger Y(-2009);
  expect((X + Y).sign() == -1, "negative addition should have sign -1");

  BigInteger C("99");
  BigInteger D(100000009);
  BigInteger res2 = C + D;
  expect(res2.sign() == 1, "positive addition should have sign 1");

  // negatives
  BigInteger E("99");
  BigInteger F(-100);
  BigInteger res3 = E + F;
  expect(res3.sign() == -1, "negative addition should have sign -1");

  BigInteger G("-882133");
  BigInteger H(659179);
  BigInteger res4 = G + H;
  expect(res4.sign() == -1, "negative addition should have sign -1");

  // Edge cases
  BigInteger I(0);
  BigInteger J(0);
  BigInteger res5 = I + J;
  expect(res5.sign() == 0, "0 + 0 should have sign 0");

  BigInteger K(99999999);
  BigInteger L(-99999999);
  BigInteger res6 = K + L;
  expect(res6.sign() == 0, "99999999 + (-99999999) should have sign 0");
}

void test_subtraction() {
  BigInteger A(10);
  BigInteger B(10);
  // case 1: A == B
  expect((A - B).sign() == 0, "A == B should return 0");
  // case 2: A - (-B)
  B.negate();
  expect((A - B).sign() == 1, "A - (-B) should return positive");
  // case 3: -(A) - (-B)
  A.negate();
  expect((A - B).sign() == 0, "(-A) - (-B) should return 0");
  // case 4: -(A) - B
  B.negate();
  expect((A - B).sign() == -1, "-(A) - B should return negative");
  // case 5: A - B
  A.negate();
  expect((A - B).sign() == 0, "A - B should return 0");
  // Case with large values
  BigInteger largeA("987654321987654321");
  BigInteger largeB("123456789123456789");
  BigInteger largeRes = largeA - largeB;
  expect(largeRes.sign() == 1, "Large subtraction should be positive");
  // Edge case: subtracting zero
  BigInteger zero(0);
  BigInteger resZeroSub = A - zero;
  expect(resZeroSub.sign() == 1, "A - 0 should give A");
}

void test_multiplication() {
  // A < B
  BigInteger A(200);
  BigInteger B(11);
  BigInteger C(0);

  // case 1: A * B
  expect((A * B).sign() == 1, "A * B should return positive");

  // case 2: B * A
  expect((B * A).sign() == 1, "A * B should return positive");

  // case 3: A * (-B)
  B.negate();
  expect((A * B).sign() == -1, "A * (-B) should return negative");

  // case 4: -(A) * (-B)
  A.negate();
  expect((A * B).sign() == 1, "(-A) * (-B) should return positive");

  // case 5: -(A) * B
  B.negate();
  expect((A * B).sign() == -1, "-(A) * B should return negative");

  // case 6: A * 0
  A.negate();
  expect((A * C).sign() == 0, "A * 0 should return 0");

  // A == B
  BigInteger F(100);
  BigInteger G(100);
  // case 1: F * G
  expect((F * G).sign() == 1, "F * G should return positive");
  // case 2: F * (-G)
  G.negate();
  expect((F * G).sign() == -1, "F * (-G) should return negative");
  // case 3: -(F) * (-G)
  F.negate();
  expect((F * G).sign() == 1, "(-F) * (-G) should return positive");
  // case 4: -(F) * G
  G.negate();
  expect((F * G).sign() == -1, "-(F) * G should return negative");
}

int add_test() {
  /*
   * Adding numbers fall into one of 4 cases, denote pos = positive number,
   * neg = negative number
   *
   * pos + pos = pos
   *
   * pos + neg = 0
   *           < 0
   *           > 0
   *
   * neg + pos = 0
   *           < 0
   *           > 0
   *
   * neg + neg = neg
   */
  BigInteger A = BigInteger("+111122223333");
  BigInteger B = BigInteger("+222211110000");

  // pos + pos = pos
  BigInteger D = BigInteger("+333333333333");
  BigInteger C = A + B;

  if (!(C == D)) return 1;

  // add a positive and a negative integer
  //-> pos + neg = 0
  B = BigInteger("-111122223333");
  C = A + B;
  if (C.sign() != 0) return 2;

  //-> pos + neg > 0
  B = BigInteger("-110122223333");
  D = BigInteger("1000000000");
  C = A + B;
  if (C.sign() != 1) return 31;
  if (!(C == D)) return 32;

  //-> pos + neg < 0
  B = BigInteger("-112122223333");
  D = BigInteger("-1000000000");
  C = A + B;
  if (C.sign() != -1) return 41;
  if (!(C == D)) return 42;

  //-> neg + neg = neg
  A = BigInteger("-221211110000");
  D = BigInteger("-333333333333");
  C = A + B;
  if (!(C == D)) return 5;

  return 0;
}
int add_assign_test() {
  BigInteger A = BigInteger("+111122223333");
  BigInteger B = BigInteger("+222211110000");

  // pos + pos = pos
  BigInteger D = BigInteger("+333333333333");
  A += B;

  if (!(A == D)) return 1;

  // add a positive and a negative integer
  //-> pos + neg = 0

  A = BigInteger("+111122223333");
  B = BigInteger("-111122223333");
  A += B;
  if (A.sign() != 0) return 2;

  //-> pos + neg > 0

  A = BigInteger("+111122223333");
  B = BigInteger("-110122223333");
  D = BigInteger("1000000000");
  A += B;
  if (A.sign() != 1) return 31;
  if (!(A == D)) return 32;

  //-> pos + neg < 0
  A = BigInteger("+111122223333");
  B = BigInteger("-112122223333");
  D = BigInteger("-1000000000");
  A += B;
  if (A.sign() != -1) return 41;
  if (!(A == D)) return 42;

  //-> neg + neg = neg
  A = BigInteger("-221211110000");
  B = BigInteger("-112122223333");
  D = BigInteger("-333333333333");
  A += B;
  if (!(A == D)) return 5;

  return 0;
}
int subtract_test() {
  /*
   * subtracting numbers fall into one of 4 cases, denote pos = positive
   * number, neg = negative number
   *
   * pos - pos = 0
   *           < 0
   *           > 0
   *
   * pos - neg = pos
   *
   * neg - pos = neg
   *
   * neg - neg = 0
   *           < 0
   *           > 0
   */

  // pos - pos = 0
  BigInteger A = BigInteger("+111122223333");
  BigInteger B = BigInteger("+111122223333");

  BigInteger C = A - B;
  if (C.sign() != 0) return 1;

  // pos - pos < 0
  B = BigInteger("121122223333");
  BigInteger D = BigInteger("-10000000000");
  C = A - B;
  if (C.sign() != -1) return 21;
  if (!(C == D)) return 22;

  // pos - pos > 0
  B = BigInteger("101122223333");
  D = BigInteger("10000000000");
  C = A - B;
  if (C.sign() != 1) return 31;
  if (!(C == D)) return 32;

  // pos - neg = pos
  B.negate();
  D = BigInteger("212244446666");
  C = A - B;
  if (C.sign() != 1) return 41;
  if (!(C == D)) return 42;

  // neg - pos = neg
  D.negate();
  C = B - A;
  if (C.sign() != -1) return 51;
  if (!(C == D)) return 52;

  return 0;
}
int subtract_assign_test() {
  BigInteger A = BigInteger("-111122223333");
  BigInteger B = BigInteger("-111122223333");

  // neg - neg = 0
  A -= B;
  if (A.sign() != 0) return 1;

  // neg - neg > 0
  A = BigInteger("-111122223333");
  B = BigInteger("-112122223333");
  BigInteger D = BigInteger("1000000000");
  A -= B;
  if (A.sign() != 1) return 21;
  if (!(A == D)) return 22;

  // neg - neg < 0
  A = BigInteger("-111122223333");
  B = BigInteger("-110122223333");
  D = BigInteger("-1000000000");
  A -= B;
  if (A.sign() != -1) return 31;
  if (!(A == D)) return 32;

  // neg - pos = neg
  A = BigInteger("-111122223333");
  B.negate();
  D = BigInteger("-221244446666");
  A -= B;
  if (A.sign() != -1) return 41;
  if (!(A == D)) return 42;

  return 0;
}

int main() {
  run_test(test_constructors, "Testing Constructors");
  run_test(test_addition, "Testing Addition");
  run_test(test_subtraction, "Testing Subtraction");
  run_test(test_multiplication, "Testing Multiplication");
  run_specific_test(add_test, "ClassTest: Testing Addition");
  run_specific_test(add_assign_test, "ClassTest: Testing Addition Assign");
  run_specific_test(subtract_test, "ClassTest: Testing Subtraction");
  run_specific_test(subtract_assign_test,
                    "ClassTest: Testing Subtraction Assign");
  return EXIT_SUCCESS;
}
