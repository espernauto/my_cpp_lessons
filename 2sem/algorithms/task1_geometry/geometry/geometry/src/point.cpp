#include "../point.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {
    Point Point::operator-() const {
      return Point(-this->x_, -this->y_);
    }

    Point &Point::Move(const Vector &v) {
      this->x_ += v.x_;
      this->y_ += v.y_;
      return *this;
    }

    bool Point::ContainsPoint(const Point &p) const {
      return this->x_ == p.x_ && this->y_ == p.y_;
    }

    bool Point::CrossesSegment(const Segment &s) const {
      Vector pa(*this, s.a_);
      Vector pb(*this, s.b_);
      Vector ab(s.a_, s.b_);
      return Cross(pa, ab) == 0 && Sign(Scalar(pa, pb)) <= 0;
    }

    Point *Point::Clone() const {
      auto *a = new Point;
      *a = *this;
      return a;
    }

    std::string Point::ToString() {
      std::string x = std::to_string(x_);
      std::string y = std::to_string(y_);
      return "Point(" + x + ", " + y + ")";
    }

    Vector operator-(const Point &a, const Point &b) {
      return Vector(a.x_ - b.x_, a.y_ - b.y_);
    }

    std::ostream &operator<<(std::ostream &out, const Point &r) {
      std::cout << r.x_ << " " << r.y_;
      return out;
    }

    std::istream &operator>>(std::istream &in, Point &vector) {
      int64_t x1, y1;
      std::cin >> x1 >> y1;
      vector.x_ = x1;
      vector.y_ = y1;
      return in;
    }
}
