#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H
#include <iostream>
#include <cmath>
#include "point.h"

namespace geometry {
    class Vector {
    public:
      int64_t x_;
      int64_t y_;

      Vector() {
        x_ = 0;
        y_ = 0;
      }

      Vector(int64_t x1, int64_t y1) {
        x_ = x1;
        y_ = y1;
      }

      Vector(Point a, Point b) {
        x_ = b.x_ - a.x_;
        y_ = b.y_ - a.y_;
      }

      friend std::istream &operator>>(std::istream &in, Vector &);

      Vector operator+() const;

      Vector operator-() const;

      Vector &operator+=(const Vector &other);

      Vector &operator-=(const Vector &other);

      Vector &operator*=(int x);

      Vector &operator/=(int x);

      double Length();
    };
    Vector operator+(const Vector &a, const Vector &b);
    Vector operator-(const Vector &a, const Vector &b);
    Vector operator*(const Vector &a, int x);
    Vector operator/(const Vector &a, int x);
    bool operator==(const Vector &a, const Vector &other);
    bool operator!=(const Vector &a, const Vector &other);
    std::ostream &operator<<(std::ostream &out, const Vector &r);
    int64_t Scalar(const Vector &a, const Vector &b);
    int64_t Cross(const Vector &a, const Vector &b);
    int Sign(int x);
}

#endif //UNTITLED1_VECTOR_H
