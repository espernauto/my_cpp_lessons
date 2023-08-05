#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int64_t m_;
  int64_t n_;

 public:
  Rational() {
    m_ = 0;
    n_ = 1;
  }

  Rational(int64_t m) {  // NOLINT
    m_ = m;
    n_ = 1;
  }

  Rational(int64_t m, int64_t n) {
    if (n == 0) {
      throw RationalDivisionByZero{};
    }
    m_ = m;
    n_ = n;
    Reductor();
  }

  void Reductor();
  void Validator();
  int64_t GetNumerator() const;
  int64_t GetDenominator() const;
  void SetNumerator(int32_t val);
  void SetDenominator(int32_t val);
  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);
  Rational operator+() const;
  Rational operator-() const;
  Rational& operator++();
  Rational operator++(int32_t);
  Rational& operator--();
  Rational operator--(int32_t);
  friend std::istream& operator>>(std::istream& in, Rational&);
};

Rational operator+(const Rational& a, const Rational& other);
Rational operator-(const Rational& a, const Rational& other);
Rational operator*(const Rational& a, const Rational& other);
Rational operator/(const Rational& a, const Rational& other);
bool operator>(const Rational& a, const Rational& other);
bool operator>=(const Rational& a, const Rational& other);
bool operator<(const Rational& a, const Rational& other);
bool operator<=(const Rational& a, const Rational& other);
bool operator==(const Rational& a, const Rational& other);
bool operator!=(const Rational& a, const Rational& other);
std::ostream& operator<<(std::ostream& out, const Rational& a);
#endif
