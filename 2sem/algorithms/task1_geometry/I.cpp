#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct Point {
  int64_t x_;
  int64_t y_;
  Point() {
    x_ = 0;
    y_ = 0;
  }
  Point(int64_t x1, int64_t y1) {
    x_ = x1;
    y_ = y1;
  }
};

std::istream& operator>>(std::istream& in, Point& point) {
  int64_t x1, y1;
  std::cin >> x1 >> y1;
  point = Point(x1, y1);
  return in;
}

std::ostream& operator<<(std::ostream& out, Point r) {
  std::cout << r.x_ << " " << r.y_ << '\n';
  return out;
}

int64_t Cross(const Point& a, const Point& b) {
  return a.x_ * b.y_ - a.y_ * b.x_;
}

Point operator+(const Point& a, const Point& b) {
  Point v(a.x_ + b.x_, a.y_ + b.y_);
  return v;
}

Point operator-(const Point& a, const Point& b) {
  Point v(a.x_ - b.x_, a.y_ - b.y_);
  return v;
}

double Length(const Point& a) {
  return sqrt((a.x_) * (a.x_) + (a.y_) * (a.y_));
}

int main() {
  int n;
  std::cin >> n;
  std::vector<Point> points;
  for (int i = 0; i < n; i++) {
    Point a;
    std::cin >> a;
    points.push_back(a);
  }
  int64_t square = 0;
  for (std::vector<Point>::size_type i = 1; i < points.size() - 1; i++) {
    square += Cross(points[i] - points[0], points[i + 1] - points[0]);
  }
  if (square < 0) {
    square = -square;
  }
  std::cout << square / 2;
  if (square % 2 != 0) {
    std::cout << ".5";
  } else {
    std::cout << ".0";
  }
}
