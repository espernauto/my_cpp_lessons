#include <iostream>
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

class Segment {
 public:
  Point begin_;
  Point end_;

  Segment() : begin_(Point(0, 0)), end_(Point(0, 0)) {
  }

  Segment(Point begin, Point end) : begin_(begin), end_(end) {
  }

  bool ContainsPoint(const Point& point) const {
    Vector point_to_begin, point_to_end, direct;
    point_to_begin = Vector(point, begin_);
    point_to_end = Vector(point, end_);
    direct = Vector(this->begin_, this->end_);
    if (CrossProduct(point_to_begin, point_to_end) == 0) {
      if (ScalarProduct(point_to_begin, direct) <= 0) {
        return ScalarProduct(point_to_begin, point_to_end) <= 0;
      }
    }
    return false;
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

  bool ContainsPoint(const Point& point) const {
    Vector point_to_segment, direct;
    point_to_segment = Vector(begin_, point);
    direct = Vector(begin_, other_);
    if (CrossProduct(point_to_segment, direct) == 0) {
      return (ScalarProduct(point_to_segment, direct) >= 0);
    }
    return false;
  }

  bool CrossesSegment(const Segment& segment) const {
    Vector v = Vector(begin_, other_);
    Vector a = Vector(begin_, segment.begin_);
    Vector b = Vector(begin_, segment.end_);
    if (CrossProduct(a, v) == 0 && ScalarProduct(a, v) < 0) {
      return CrossProduct(b, v) == 0 && ScalarProduct(b, v) > 0;
    }
    if (CrossProduct(a, v) * CrossProduct(v, b) >= 0) {
      return CrossProduct(a, b) * CrossProduct(a, v) >= 0;
    }
    return false;
  }

  bool ContainsSegment(const Segment& segment) const {
    return this->ContainsPoint(segment.begin_) && this->ContainsPoint(segment.end_);
  }
};

class Polygon {
 public:
  std::vector<Point> points_;

  Polygon() {
    points_.emplace_back(Point(0, 0));
  }

  explicit Polygon(std::vector<Point> points) {
    for (size_t i = 0; i < points.size(); i++) {
      points_.emplace_back(points[i]);
    }
  }
};

int main() {
  int n;
  int counter = 0;
  int flag = 0;
  std::cin >> n;
  std::vector<Point> points;
  Point point;
  std::cin >> point.x_ >> point.y_;
  Ray ray(point, Point(point.x_ + 4, point.y_ + 3));
  for (int i = 0; i < n; i++) {
    int64_t x, y;
    std::cin >> x;
    std::cin >> y;
    points.emplace_back(Point(x, y));
  }
  Polygon polygon(points);
  for (size_t i = 0; i < points.size() - 1; i++) {
    Segment segment(polygon.points_[i], polygon.points_[i + 1]);
    if (ray.CrossesSegment(segment) && !ray.ContainsPoint(polygon.points_[i]) &&
        !ray.ContainsPoint(polygon.points_[i + 1])) {
      counter++;
    }
    if (ray.ContainsPoint(polygon.points_[i])) {
      counter++;
    }
    if (segment.ContainsPoint(point)) {
      counter = 1;
      flag = 1;
      break;
    }
  }
  Segment segment(polygon.points_[points.size() - 1], polygon.points_[0]);
  if (ray.CrossesSegment(segment) && !ray.ContainsPoint(polygon.points_[0]) &&
      !ray.ContainsPoint(polygon.points_[points.size() - 1]) && flag == 0) {
    counter++;
  }
  if (ray.ContainsPoint(polygon.points_[points.size() - 1])) {
    counter++;
  }
  if (segment.ContainsPoint(point)) {
    counter = 1;
  }
  if (counter % 2 == 1) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
