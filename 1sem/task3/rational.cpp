#include <iostream>
#include "rational.h"
#include <numeric>

void Rational::Reductor() {
  int64_t x;
  int64_t sign = 1;
  Validator();
  if (m_ < 0) {
    m_ = -m_;
    sign *= -1;
  }
  if (n_ < 0) {
    n_ = -n_;
    sign *= -1;
  }
  x = std::gcd(m_, n_);
  m_ = sign * m_ / x;
  n_ = n_ / x;
}

void Rational::Validator() {
  if (n_ == 0) {
    throw RationalDivisionByZero{};
  }
}

int64_t Rational::GetNumerator() const {
  return m_;
}

int64_t Rational::GetDenominator() const {
  return n_;
}

void Rational::SetNumerator(int32_t val) {
  m_ = val;
  Reductor();
}

void Rational::SetDenominator(int32_t val) {
  if (val == 0) {
    throw RationalDivisionByZero{};
  }
  n_ = val;
  Reductor();
}

Rational operator+(const Rational& a, const Rational& other) {
  int64_t m = a.GetNumerator() * other.GetDenominator() + other.GetNumerator() * a.GetDenominator();
  int64_t n = a.GetDenominator() * other.GetDenominator();
  Rational r = Rational(m, n);
  return r;
}

Rational operator-(const Rational& a, const Rational& other) {
  int64_t m = a.GetNumerator() * other.GetDenominator() - other.GetNumerator() * a.GetDenominator();
  int64_t n = a.GetDenominator() * other.GetDenominator();
  Rational r = Rational(m, n);
  return r;
}

Rational operator*(const Rational& a, const Rational& other) {
  Rational r = Rational(a.GetNumerator() * other.GetNumerator(), a.GetDenominator() * other.GetDenominator());
  return r;
}

Rational operator/(const Rational& a, const Rational& other) {
  Rational r = Rational(a.GetNumerator() * other.GetDenominator(), a.GetDenominator() * other.GetNumerator());
  return r;
}

bool operator>(const Rational& a, const Rational& other) {
  return ((a.GetNumerator() * other.GetDenominator() - a.GetDenominator() * other.GetNumerator()) > 0);
}

bool operator>=(const Rational& a, const Rational& other) {
  return ((a.GetNumerator() * other.GetDenominator() - a.GetDenominator() * other.GetNumerator()) >= 0);
}

bool operator<(const Rational& a, const Rational& other) {
  return (other > a);
}

bool operator<=(const Rational& a, const Rational& other) {
  return (other >= a);
}

bool operator==(const Rational& a, const Rational& other) {
  return (a.GetNumerator() * other.GetDenominator() == a.GetDenominator() * other.GetNumerator());
}

bool operator!=(const Rational& a, const Rational& other) {
  return (a.GetNumerator() * other.GetDenominator() != a.GetDenominator() * other.GetNumerator());
}

Rational& Rational::operator+=(const Rational& other) {
  *this = *this + other;
  Reductor();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  *this = *this - other;
  Reductor();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  *this = *this * other;
  Reductor();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  *this = *this / other;
  Reductor();
  return *this;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  return 0 - *this;
}

Rational& Rational::operator++() {
  m_ += n_;
  Reductor();
  return *this;
}

Rational Rational::operator++(int32_t) {
  Rational old_value{*this};
  m_ += n_;
  Reductor();
  return old_value;
}

Rational& Rational::operator--() {
  m_ -= n_;
  Reductor();
  return *this;
}

Rational Rational::operator--(int32_t) {
  Rational old_value{*this};
  m_ -= n_;
  Reductor();
  return old_value;
}

std::ostream& operator<<(std::ostream& out, const Rational& a) {
  Rational r = a;
  if (r.GetDenominator() != 1) {
    return out << r.GetNumerator() << "/" << r.GetDenominator();
  }
  return out << r.GetNumerator();
}

std::istream& operator>>(std::istream& in, Rational& r) {
  int64_t m;
  int64_t n = 1;
  in >> m;
  if (in.peek() == '/') {
    in.ignore(1, '/');
    in >> n;
  }
  if (n == 0) {
    throw RationalDivisionByZero{};
  }
  r = Rational(m, n);
  r.Reductor();
  return in;
}
