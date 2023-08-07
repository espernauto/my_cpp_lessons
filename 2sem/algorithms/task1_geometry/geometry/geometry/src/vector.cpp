#include "../vector.h"

namespace geometry {
    std::istream &operator>>(std::istream &in, Vector &vector) {
      int x1, y1;
      std::cin >> x1 >> y1;
      vector = Vector(x1, y1);
      return in;
    }

    Vector operator+(const Vector &a, const Vector &b) {
      Vector v(a.x_ + b.x_, a.y_ + b.y_);
      return v;
    }

    Vector operator-(const Vector &a, const Vector &b) {
      Vector v(a.x_ - b.x_, a.y_ - b.y_);
      return v;
    }

    std::ostream &operator<<(std::ostream &out, const Vector &r) {
      std::cout << r.x_ << " " << r.y_;
      return out;
    }

    Vector operator*(const Vector &a, int x) {
      return Vector(a.x_ * x, a.y_ * x);
    }

    Vector operator/(const Vector &a, int x) {
      return Vector(a.x_ / x, a.y_ / x);
    }

    bool operator==(const Vector &a, const Vector &other) {
      return a.x_ == other.x_ && a.y_ == other.y_;
    }

    bool operator!=(const Vector &a, const Vector &other) {
      return a.x_ != other.x_ || a.y_ != other.y_;
    }

    Vector Vector::operator+() const {
      return *this;
    }

    Vector Vector::operator-() const {
      return Vector(0, 0) - *this;
    }

    Vector &Vector::operator+=(const Vector &other) {
      this->x_ += other.x_;
      this->y_ += other.y_;
      return *this;
    }

    Vector &Vector::operator-=(const Vector &other) {
      this->x_ -= other.x_;
      this->y_ -= other.y_;
      return *this;
    }

    Vector &Vector::operator*=(int x) {
      this->x_ *= x;
      this->y_ *= x;
      return *this;
    }

    Vector &Vector::operator/=(int x) {
      this->x_ /= x;
      this->y_ /= x;
      return *this;
    }

    double Vector::Length() {
      return sqrt((x_) * (x_) + (y_) * (y_));
    }

    int64_t Scalar(const Vector &a, const Vector &b) {
      return a.x_ * b.x_ + a.y_ * b.y_;
    }

    int64_t Cross(const Vector &a, const Vector &b) {
      return a.x_ * b.y_ - a.y_ * b.x_;
    }

    int Sign(int x) {
      if (x > 0) {
        return 1;
      }
      if (x == 0) {
        return 0;
      }
      return -1;
    }
}
