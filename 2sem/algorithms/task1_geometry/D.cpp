#include <iostream>
#include <cmath>
#include <vector>

class Point {
 public:
  int x_;
  int y_;

  Point() : x_(0), y_(0) {
  }

  Point(int x, int y) : x_(x), y_(y) {
  }
};

class Vector {
 public:
  int x_;
  int y_;
  Vector() : x_(0), y_(0) {
  }
  Vector(int x1, int y1) : x_(x1), y_(y1) {
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

int ScalarProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x_ * vector_2.x_ + vector_1.y_ * vector_2.y_;
}

int CrossProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x_ * vector_2.y_ - vector_1.y_ * vector_2.x_;
}

std::istream& operator>>(std::istream& in, Vector& vector) {
  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  vector = Vector(x2 - x1, y2 - y1);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
  std::cout << vector.x_ << " " << vector.y_;
  return out;
}

class Line {
 public:
  Point first_;
  Point second_;

  Line() : first_(Point(0, 0)), second_(Point(0, 0)) {
  }

  Line(Point a, Point b) : first_(a), second_(b) {
  }

  Vector DirVector() {
    return first_ - second_;
  }

  double Distance(const Point& point) {
    Vector ab(point.x_ - first_.x_, point.y_ - first_.y_);
    Vector v(second_.x_ - first_.x_, second_.y_ - first_.y_);
    return abs((CrossProduct(ab, v))) / Length(v);
  }
};

class Ray {
 public:
  Point begin_;
  Point other_;

  Ray() : begin_(Point(0, 0)), other_(Point(0, 0)) {
  }

  Ray(Point begin, Point end) : begin_(begin), other_(end) {
  }

  double Distance(const Point& point) {
    Vector ab(point.x_ - begin_.x_, point.y_ - begin_.y_);
    Vector v(other_.x_ - begin_.x_, other_.y_ - begin_.y_);
    if (ScalarProduct(v, ab) > 0) {
      return abs((CrossProduct(ab, v))) / Length(v);
    }
    return Length(ab);
  }
};

class Segment {
 public:
  Point begin_;
  Point end_;

  Segment() : begin_(Point(0, 0)), end_(Point(0, 0)) {
  }

  Segment(Point begin, Point end) : begin_(begin), end_(end) {
  }

  double Distance(const Point& point) {
    Vector ab(point.x_ - begin_.x_, point.y_ - begin_.y_);
    Vector ac(point.x_ - end_.x_, point.y_ - end_.y_);
    Vector v(end_.x_ - begin_.x_, end_.y_ - begin_.y_);
    if (ScalarProduct(v, ab) > 0 && ScalarProduct(v, ac) < 0) {
      return abs((CrossProduct(ab, v))) / Length(v);
    }
    return std::min(Length(ab), Length(ac));
  }
};

int main() {
  std::cout.setf(std::ios::fixed);
  std::cout.precision(10);
  int x1, y1, x2, y2, x3, y3;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
  Point point = Point(x1, y1);
  Line line = Line(Point(x2, y2), Point(x3, y3));
  Ray ray = Ray(Point(x2, y2), Point(x3, y3));
  Segment segment = Segment(Point(x2, y2), Point(x3, y3));
  std::cout << line.Distance(point) << '\n';
  std::cout << ray.Distance(point) << '\n';
  std::cout << segment.Distance(point) << '\n';
}
