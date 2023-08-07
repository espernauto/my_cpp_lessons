#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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

std::ostream& operator<<(std::ostream& out, const Point& r) {
  std::cout << r.x_ << " " << r.y_ << '\n';
  return out;
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
  double Length();
};

Vector operator-(Point& point_1, Point& point_2) {
  return Vector(point_1.x_ - point_2.x_, point_1.y_ - point_2.y_);
}

Vector operator-(Vector& vector_1, Vector& vector_2) {
  return Vector(vector_1.x_ - vector_2.x_, vector_1.y_ - vector_2.y_);
}

Vector operator+(const Vector& vector_1, const Vector& vector_2) {
  Vector vector(vector_1.x_ + vector_2.x_, vector_1.y_ + vector_2.y_);
  return vector;
}

int64_t ScalarProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x_ * vector_2.x_ + vector_1.y_ * vector_2.y_;
}

int64_t CrossProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x_ * vector_2.y_ - vector_1.y_ * vector_2.x_;
}

std::istream& operator>>(std::istream& in, Vector& vector) {
  int x1, y1;
  std::cin >> x1 >> y1;
  vector = Vector(x1, y1);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
  std::cout << vector.x_ << " " << vector.y_;
  return out;
}

double Vector::Length() {
  return sqrt((x_) * (x_) + (y_) * (y_));
}

bool Cmp(Vector& first, Vector& second) {
  if (CrossProduct(first, second) == 0) {
    return first.Length() < second.Length();
  }
  return CrossProduct(first, second) > 0;
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

  std::vector<Vector> Graham();
};

std::vector<Vector> Polygon::Graham() {
  Point left_point = points_[0];
  std::vector<Vector> vectors;
  for (std::vector<Point>::size_type i = 0; i < points_.size(); i++) {
    if (points_[i].x_ < left_point.x_ || (points_[i].x_ == left_point.x_ && points_[i].y_ < left_point.y_)) {
      left_point = points_[i];
    }
  }
  for (std::vector<Point>::size_type i = 0; i < points_.size(); i++) {
    vectors.emplace_back(points_[i] - left_point);
  }
  std::sort(vectors.begin(), vectors.end(), Cmp);
  std::vector<Vector> vectors_stack;
  for (std::vector<Vector>::size_type i = 0; i < vectors.size(); i++) {
    while (vectors_stack.size() >= 2) {
      Vector new_vector = vectors[i] - vectors_stack.back();
      Vector last_vector = vectors_stack.back() - vectors_stack[vectors_stack.size() - 2];
      if (CrossProduct(new_vector, last_vector) >= 0) {
        vectors_stack.pop_back();
      } else {
        break;
      }
    }
    vectors_stack.emplace_back(vectors[i]);
  }
  vectors_stack.emplace_back(Vector(Point(0, 0), left_point));
  return vectors_stack;
}

int64_t DoubleSquare(std::vector<Vector>& result) {
  int64_t double_square = 0;
  for (std::vector<Point>::size_type i = 0; i < result.size() - 2; i++) {
    double_square += CrossProduct(result[i], result[i + 1]);
  }
  return double_square;
}

int main() {
  std::cout.setf(std::ios::fixed);
  std::cout.precision(1);
  int n;
  std::cin >> n;
  std::vector<Point> points;
  for (int i = 0; i < n; i++) {
    Point a;
    std::cin >> a;
    points.push_back(a);
  }
  Polygon polygon(points);
  std::vector<Vector> result = polygon.Graham();
  std::cout << result.size() - 1 << '\n';
  std::cout << result[result.size() - 1] << '\n';
  for (std::vector<Vector>::size_type i = result.size() - 2; i > 0; i--) {
    std::cout << result[i] + result[result.size() - 1] << '\n';
  }
  int64_t square = 0;
  for (std::vector<Point>::size_type i = 1; i < result.size() - 2; i++) {
    square += CrossProduct(result[i], result[i + 1]);
  }
  std::cout << DoubleSquare(result) / 2;
  if (DoubleSquare(result) % 2 != 0) {
    std::cout << ".5" << '\n';
  } else {
    std::cout << ".0" << '\n';
  }
}
