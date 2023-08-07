#include <iostream>
#include <cmath>

class Vector {
 public:
  int x;
  int y;
  Vector() : x(0), y(0) {
  }

  Vector(int x1, int y1) : x(x1), y(y1) {
  }
};

Vector operator+(Vector& first, Vector& second) {
  Vector vector(first.x + second.x, first.y + second.y);
  return vector;
}

double Length(Vector& a) {
  return sqrt((a.x) * (a.x) + (a.y) * (a.y));
}

int ScalarProduct(Vector& first, Vector& second) {
  return first.x * second.x + first.y * second.y;
}

int CrossProduct(Vector& a, Vector& b) {
  return a.x * b.y - a.y * b.x;
}

std::istream& operator>>(std::istream& in, Vector& vector) {
  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  vector = Vector(x2 - x1, y2 - y1);
  return in;
}

std::ostream& operator<<(std::ostream& out, Vector& vector) {
  std::cout << vector.x << " " << vector.y << '\n';
  return out;
}

class Point {
 public:
  int64_t x_;
  int64_t y_;

  Point() : x_(0), y_(0) {
  }

  Point(int x, int y) : x_(x), y_(y) {
  }
};

Vector operator-(Point& a, Point& b) {
  return Vector(b.x_ - a.x_, b.y_ - a.y_);
}

class Line {
 public:
  Point a_;
  Point b_;

  Line() : a_(Point(0, 0)), b_(Point(0, 0)) {
  }

  Line(Point& a, Point& b) : a_(a), b_(b) {
  }

  Line(Point a, Point b) : a_(a), b_(b) {
  }

  Vector DirVector() {
    return a_ - b_;
  }
};

void PrintIntersection(Vector& first_vector, Vector& second_vector, int a1, int b1, int c1, int a2, int b2, int c2) {
  if (CrossProduct(first_vector, second_vector) == 0) {
    if (b2 != 0) {
      Vector normal_vector = Vector(a1, b1);
      std::cout << fabs(static_cast<float>(c1 - c2 * b1 / b2) / (Length(normal_vector)));
    } else {
      std::cout << abs(c1 - c2);
    }
  } else {
    std::cout << -static_cast<float>(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1) << " ";
    std::cout << -static_cast<float>(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
  }
}

int main() {
  int a1, b1, c1, a2, b2, c2;
  std::cout.setf(std::ios::fixed);
  std::cout.precision(6);
  std::cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
  Line first(Point(0, 0), Point(b1, -a1));
  Line second(Point(0, 0), Point(b2, -a2));
  Vector first_vector = first.DirVector();
  Vector second_vector = second.DirVector();
  std::cout << first_vector << second_vector;
  PrintIntersection(first_vector, second_vector, a1, b1, c1, a2, b2, c2);
}
