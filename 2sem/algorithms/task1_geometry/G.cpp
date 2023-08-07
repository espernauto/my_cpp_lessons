#include <iostream>
#include <cmath>
#include <vector>

class Point {
 public:
  int64_t x_;
  int64_t y_;

  Point() : x_(0), y_(0) {
  }

  Point(int64_t x, int64_t y) : x_(x), y_(y) {
  }
};

bool operator==(const Point& a, const Point& b) {
  return (a.x_ == b.x_ && a.y_ == b.y_);
}

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

Vector operator-(const Point& a, const Point& b) {
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

class Polygon {
 public:
  std::vector<Point> points_;

  Polygon() {
    points_.emplace_back(Point(0, 0));
  }

  explicit Polygon(std::vector<Point>& points) {
    for (size_t i = 0; i < points.size(); i++) {
      points_.emplace_back(points[i]);
    }
  }

  bool IsConvex() const;
};

bool Polygon::IsConvex() const {
  if (points_[0] == points_[1] || points_[2] == points_[1]) {
    return false;
  }
  int sign = Sign(CrossProduct(points_[2] - points_[1], points_[1] - points_[0]));
  for (std::vector<Point>::size_type i = 3; i < points_.size(); i++) {
    Vector new_vector = points_[i] - points_[i - 1];
    Vector last_vector = points_[i - 1] - points_[i - 2];
    if (points_[i] == points_[i - 1]) {
      return false;
    }
    if (Sign(CrossProduct(new_vector, last_vector)) != sign &&
        sign * Sign(CrossProduct(new_vector, last_vector)) != 0) {
      return false;
    }
    if (Sign(CrossProduct(new_vector, last_vector)) != 0) {
      sign = Sign(CrossProduct(new_vector, last_vector));
    }
  }
  Vector new_vector = points_[1] - points_[0];
  Vector last_vector = points_[0] - points_[points_.size() - 1];
  if (Sign(CrossProduct(new_vector, last_vector)) != sign && sign * Sign(CrossProduct(new_vector, last_vector)) != 0) {
    return false;
  }
  return sign != 0;
}

int main() {
  int64_t n;
  std::cin >> n;
  std::vector<Point> points;
  for (int64_t i = 0; i < n; i++) {
    Point a;
    std::cin >> a;
    points.push_back(a);
  }
  Polygon polygon(points);
  if (polygon.IsConvex()) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
