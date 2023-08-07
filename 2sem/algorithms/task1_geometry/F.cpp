#include <iostream>
#include <cmath>

class Point {
 public:
  int64_t x_;
  int64_t y_;

  Point() : x_(0), y_(0) {
  }

  Point(int64_t x, int64_t y) : x_(x), y_(y) {
  }
};

std::istream& operator>>(std::istream& in, Point& point) {
  std::cin >> point.x_ >> point.y_;
  return in;
}

class Vector {
 public:
  int64_t x_;
  int64_t y_;
  Vector() : x_(0), y_(0) {
  }
  Vector(int64_t x1, int64_t y1) : x_(x1), y_(y1) {
  }
  Vector(const Point& first, const Point& second) {
    x_ = second.x_ - first.x_;
    y_ = second.y_ - first.y_;
  }
};

Vector operator-(Point& a, Point& b) {
  return Vector(b.x_ - a.x_, b.y_ - a.y_);
}

Vector operator+(const Vector& vector_1, const Vector& vector_2) {
  Vector vector(vector_1.x_ + vector_2.x_, vector_1.y_ + vector_2.y_);
  return vector;
}

double Length(const Vector& vector_1) {
  return sqrt((vector_1.x_) * (vector_1.x_) + (vector_1.y_) * (vector_1.y_));
}

int64_t ScalarProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x_ * vector_2.x_ + vector_1.y_ * vector_2.y_;
}

int64_t CrossProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x_ * vector_2.y_ - vector_1.y_ * vector_2.x_;
}

std::istream& operator>>(std::istream& in, Vector& vector) {
  int64_t x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  vector = Vector(x2 - x1, y2 - y1);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
  std::cout << vector.x_ << " " << vector.y_;
  return out;
}

int Sign(int64_t x) {
  if (x > 0) {
    return 1;
  }
  if (x == 0) {
    return 0;
  }
  return -1;
}

class Segment {
 public:
  Point begin_;
  Point end_;

  Segment() : begin_(Point(0, 0)), end_(Point(0, 0)) {
  }

  Segment(Point begin, Point end) : begin_(begin), end_(end) {
  }

  bool CrossesSegment(const Segment& other) const {
    Vector ac = Vector(begin_, other.begin_);
    Vector ad = Vector(begin_, other.end_);
    Vector bc = Vector(end_, other.begin_);
    Vector bd = Vector(end_, other.end_);
    Vector ab = Vector(begin_, end_);
    Vector cd = Vector(other.begin_, other.end_);
    int sign_1 = Sign(CrossProduct(ac, ab)) * Sign(CrossProduct(ab, ad));
    int sign_2 = Sign(CrossProduct(ac, cd)) * Sign(CrossProduct(cd, bc));
    if (CrossProduct(ac, ab) == 0 && CrossProduct(ab, ad) == 0) {
      return (ScalarProduct(ab, ac) * ScalarProduct(ab, bc) <= 0) ||
             (ScalarProduct(ab, bd) * ScalarProduct(ab, ad) <= 0) ||
             (ScalarProduct(ac, cd) * ScalarProduct(ad, cd) <= 0) ||
             (ScalarProduct(bc, cd) * ScalarProduct(bd, cd) <= 0);
    }
    return (sign_1 >= 0 && sign_2 >= 0);
  }
};

double Distance(Point& point, Segment& segment) {
  Vector ab(point.x_ - segment.begin_.x_, point.y_ - segment.begin_.y_);
  Vector ac(point.x_ - segment.end_.x_, point.y_ - segment.end_.y_);
  Vector v(segment.end_.x_ - segment.begin_.x_, segment.end_.y_ - segment.begin_.y_);
  if (ScalarProduct(v, ab) > 0 && ScalarProduct(v, ac) < 0) {
    return abs((CrossProduct(ab, v))) / Length(v);
  }
  return std::min(Length(ab), Length(ac));
}

int main() {
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  Segment first, second;
  std::cin >> first.begin_ >> first.end_ >> second.begin_ >> second.end_;
  if (first.CrossesSegment(second)) {
    std::cout << 0;
  } else {
    std::cout << std::min(std::min(Distance(first.begin_, second), Distance(first.end_, second)),
                          std::min(Distance(second.begin_, first), Distance(second.end_, first)));
  }
}
