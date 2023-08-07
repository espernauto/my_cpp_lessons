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

std::ostream& operator<<(std::ostream& out, const Point& point) {
  std::cout << point.x_ << " " << point.y_ << '\n';
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

bool operator<(Vector vector_1, Vector vector_2) {
  if (CrossProduct(vector_1, vector_2) == 0) {
    return vector_1.Length() < vector_2.Length();
  }
  return CrossProduct(vector_1, vector_2) < 0;
}

bool operator==(Vector& vector_1, Vector& vector_2) {
  return vector_1.x_ == vector_2.x_ && vector_1.y_ == vector_2.y_;
}

bool operator!=(Vector& vector_1, Vector& vector_2) {
  return vector_1.x_ != vector_2.x_ || vector_1.y_ != vector_2.y_;
}

bool operator<=(Vector vector_1, Vector vector_2) {
  return vector_1 < vector_2 || vector_1 == vector_2;
}

std::vector<Vector> Jarvis(std::vector<Point>& points) {
  Point left = points[0];
  std::vector<Vector> vectors;
  for (std::vector<Point>::size_type i = 0; i < points.size(); i++) {
    vectors.emplace_back(points[i].x_, points[i].y_);
    if (points[i].x_ < left.x_ || (points[i].x_ == left.x_ && points[i].y_ < left.y_)) {
      left = points[i];
    }
  }
  std::vector<Vector> vectors_stack;
  Vector left_vector = Vector(left.x_, left.y_);
  vectors_stack.emplace_back(left_vector);
  while (true) {
    Vector candidate = left_vector;
    for (std::vector<Vector>::size_type j = 0; j < vectors.size(); j++) {
      if (candidate - vectors_stack.back() < vectors[j] - vectors_stack.back()) {
        candidate = vectors[j];
      }
      if (CrossProduct(vectors[j] - vectors_stack.back(), candidate - vectors_stack.back()) == 0 &&
          (candidate - vectors_stack.back()) < (vectors[j] - vectors_stack.back()) &&
          candidate != vectors_stack.back() && vectors[j] != vectors_stack.back()) {
        candidate = vectors[j];
      }
    }
    if (candidate == vectors_stack.back() || candidate == left_vector) {
      break;
    }
    vectors_stack.emplace_back(candidate);
  }
  return vectors_stack;
}

void Square(std::vector<Vector>& result) {
  int64_t square = 0;
  for (std::vector<Point>::size_type i = 0; i < result.size() - 1; i++) {
    square += CrossProduct(result[i] - result[0], result[i + 1] - result[0]);
  }
  std::cout << square / 2;
  if (square % 2 != 0) {
    std::cout << ".5" << '\n';
  } else {
    std::cout << ".0" << '\n';
  }
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
    points.emplace_back(a);
  }
  std::vector<Vector> result = Jarvis(points);
  std::cout << result.size() << '\n';
  std::cout << result[0] << '\n';
  for (std::vector<Vector>::size_type i = result.size() - 1; i > 0; i--) {
    std::cout << result[i] << '\n';
  }
  Square(result);
}
