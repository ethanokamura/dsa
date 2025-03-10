/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file BigInteger.cpp
 * @brief Implementation of Big Integer ADT
 * @status: working / tested
 */

#include "BigInteger.h"

#include <math.h>

#include <sstream>
#include <stdexcept>

// Global Var --------------------------------------------------------------
const int power = 9;
const long base = std::pow(10, power);

// Helpers -----------------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List &S) {
  S.moveBack();
  while (S.position() > 0) {
    long val = S.movePrev();
    S.setAfter(-val);
  }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List &S, List A, List B, int sgn) {
  S.clear();
  A.moveBack();
  B.moveBack();
  while (A.position() > 0 || B.position() > 0) {
    long value{};
    if (A.position() > 0) value += A.movePrev();
    if (B.position() > 0) value += B.movePrev() * sgn;
    S.insertAfter(value);
  }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List &S) {
  if (S.length() == 0) return 0;
  int carry{};
  S.moveBack();
  while (S.position() > 0) {
    long data = S.movePrev() + carry;
    carry = 0;
    if (data >= base) {
      carry = data / base;
      data %= base;
    } else if (data < 0) {
      carry = (data - base + 1) / base;
      data -= carry * base;
    }
    S.setAfter(data);
  }

  if (carry == 0) {
    // trim leading zeros
    while (S.length() > 0 && S.peekNext() == 0) {
      S.eraseAfter();
    }

    if (S.length() == 0) return 0;
  }

  if (carry < 0) return -1;
  if (carry > 0) {
    S.insertBefore(carry);
  }

  return 1;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List &S, int p) {
  S.moveBack();
  for (int i = 0; i < p; i++) {
    S.insertAfter(0);
  }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List &S, ListElement m) {
  S.moveBack();
  while (S.position() > 0) {
    long val = S.movePrev();
    S.setAfter(val * m);
  }
}

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger() : signum(0), digits(){};

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
  if (x == 0) {
    signum = 0;
    return;
  }
  signum = x > 0 ? 1 : -1;
  if (x < 0) x = -x;
  while (x > 0) {
    digits.insertAfter(x % base);
    x /= base;
  }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) : signum(0) {
  if (s.length() == 0)
    throw std::invalid_argument("BigInteger: Constructor: empty string");
  int digit{1}, value{};
  bool sig{};
  if (s[0] == '-') {
    signum = -1;
    sig = true;
  } else if (s[0] == '+') {
    signum = 1;
    sig = true;
  }

  bool non_zero{false};
  int leading_zero = sig ? 1 : 0;
  while (s[leading_zero] == '0') {
    leading_zero++;
  }

  for (int i = s.length() - 1; i >= leading_zero; i--) {
    if (s[i] > '9' || s[i] < '0')
      throw std::invalid_argument(
          "BigInteger: Constructor: non-numeric string");
    value += static_cast<int>(s[i] - '0') * digit;
    digit *= 10;
    if (digit == base) {
      if (value > 0) non_zero = true;
      digits.insertAfter(value);
      value = 0;
      digit = 1;
    }
  }
  if (value != 0) {
    digits.insertAfter(value);
    non_zero = true;
  }
  if (!non_zero) return;
  if (signum != -1) signum = 1;
  // if (non_zero && signum != -1) {
  //   signum = 1;
  // }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger &N) {
  digits = N.digits;
  signum = N.signum;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger() {}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const { return signum; }

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
// use the helper operators!
int BigInteger::compare(const BigInteger &N) const {
  if (*this == N) return 0;
  if (*this > N) return 1;
  return -1;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
  digits.clear();
  signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
  if (signum == 0) return;
  signum = -signum;
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
// use the helper operators!
BigInteger BigInteger::add(const BigInteger &N) const {
  if (signum == 0) return *this;
  if (N.signum == 0) return N;

  BigInteger B;

  // check for subtraction
  if (signum != N.signum) {
    if (signum < 0) {
      B = *this;
      B.negate();
      return N.sub(B);
    } else {
      B = N;
      B.negate();
      return sub(B);
    }
  }

  // vector sum
  sumList(B.digits, digits, N.digits, 1);
  // normalize
  normalizeList(B.digits);
  B.signum = signum;
  return B;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
// use the helper operators!
BigInteger BigInteger::sub(const BigInteger &N) const {
  if (N.signum == 0) return *this;

  BigInteger B;

  if (signum == 0) {
    B = N;
    B.negate();
    return B;
  }

  // case 1: A == B
  if (*this == N) return B;

  // case 2: addition (-A - B OR A - (-B))
  if (signum != N.signum || (signum < 0 && N.signum < 0)) {
    B = N;
    B.negate();
    return add(B);
  }
  // vector diff
  sumList(B.digits, digits, N.digits, -1);
  // A < B
  bool neg = *this < N;
  // negate digit list if needed
  if (neg) negateList(B.digits);
  // normalize and store sign
  B.signum = normalizeList(B.digits);
  if (neg) B.negate();
  return B;
}

// mult()
// Returns a BigInteger representing the product of this and N.
// use the helper operators!
BigInteger BigInteger::mult(const BigInteger &N) const {
  BigInteger B;
  // mult by 0
  if (N.signum == 0 || signum == 0) return B;
  // check to see if one number is negative using XOR
  B.signum = ((N.signum < 0) ^ (signum < 0)) ? -1 : 1;
  // copy N.digits
  List ND = N.digits;
  // shift amount
  int shift{};
  ND.moveBack();
  // for each digit in N
  while (ND.position() > 0) {
    List D = digits;
    // shift D
    shiftList(D, shift++);
    // multiply A.digits by the current digit
    long current = ND.movePrev();
    scalarMultList(D, current);
    // add the multiplied number
    sumList(B.digits, B.digits, D, 1);
    // normalize
    normalizeList(B.digits);
  }
  return B;
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
  if (digits.length() == 0) return "0";
  std::ostringstream oss;
  oss << (signum == -1 ? "-" : "");
  digits.moveFront();
  bool first{};
  while (digits.position() < digits.length()) {
    std::string str = std::to_string(digits.moveNext());
    if (!first && str == "0") continue;
    if (first) {
      for (int i = str.length(); i < power; i++) oss << '0';
    }
    oss << str;
    first = true;
  }
  if (oss.str().empty()) return "0";
  return oss.str();
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream &operator<<(std::ostream &stream, BigInteger N) {
  return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==(const BigInteger &A, const BigInteger &B) {
  return ((A.signum == B.signum) && (A.digits.equals(B.digits)));
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<(const BigInteger &A, const BigInteger &B) {
  if (A == B) return false;

  // compare signs
  // -A vs (+B or 0)
  if (A.signum < B.signum) return true;
  // (+A or 0) vs -B
  if (A.signum > B.signum) return false;

  // we now know A.signum == B.signum

  // compare lengths
  // if A is positive and has less digits or if A is negative and has more
  // digits
  if ((A.signum > 0 && A.digits.length() < B.digits.length()) ||
      (A.signum < 0 && A.digits.length() > B.digits.length()))
    return true;
  if ((A.signum > 0 && A.digits.length() > B.digits.length()) ||
      (A.signum < 0 && A.digits.length() < B.digits.length()))
    return false;

  // compare msd to lsd
  List AD = A.digits;
  List BD = B.digits;
  AD.moveFront();
  BD.moveFront();

  int len = AD.length();
  // for each number in the list
  for (int i = 0; i < len; i++) {
    long A_val = AD.moveNext();
    long B_val = BD.moveNext();
    // if A digit < B digit and its positive
    if (A_val < B_val) return A.signum > 0;
    // if A digit > B digit and its negative
    if (A_val > B_val) return A.signum < 0;
  }
  return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger &A, const BigInteger &B) { return !(A > B); }

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger &A, const BigInteger &B) {
  if (A == B) return false;

  // compare signs
  // A vs (-B or 0)
  if (A.signum > B.signum) return true;
  // (-A or 0) vs +B
  if (A.signum < B.signum) return false;

  // we now know A.signum == B.signum

  // compare lengths
  if ((A.signum > 0 && A.digits.length() < B.digits.length()) ||
      (A.signum < 0 && A.digits.length() > B.digits.length()))
    return false;
  if ((A.signum > 0 && A.digits.length() > B.digits.length()) ||
      (A.signum < 0 && A.digits.length() < B.digits.length()))
    return true;

  // compare msd to lsd
  List AD = A.digits;
  List BD = B.digits;
  AD.moveFront();
  BD.moveFront();

  int len = AD.length();
  // for each number in the list
  for (int i = 0; i < len; i++) {
    long A_val = AD.moveNext();
    long B_val = BD.moveNext();
    // if A digit > B digit and its positive
    if (A_val > B_val) return A.signum > 0;
    // if A digit < B digit and its negative
    if (A_val < B_val) return A.signum < 0;
  }
  return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger &A, const BigInteger &B) { return !(A < B); }

// operator+()
// Returns the sum A+B.
BigInteger operator+(const BigInteger &A, const BigInteger &B) {
  return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger &A, const BigInteger &B) {
  A = A.add(B);
  return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-(const BigInteger &A, const BigInteger &B) {
  return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger &A, const BigInteger &B) {
  A = A.sub(B);
  return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*(const BigInteger &A, const BigInteger &B) {
  return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=(BigInteger &A, const BigInteger &B) {
  A = A * B;
  return A;
}