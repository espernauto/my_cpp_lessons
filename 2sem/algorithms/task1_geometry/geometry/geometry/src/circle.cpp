#include "../point.h"
#include "../vector.h"
#include "../segment.h"
#include "../circle.h"

namespace geometry {
    Circle &Circle::Move(const Vector &v) {
      this->a_.Move(v);
      return *this;
    }

    bool Circle::ContainsPoint(const Point &p) const {
      Vector point = p - a_;
      return (point.x_ * point.x_ + point.y_ * point.y_ <= r_ * r_);
    }

    bool Circle::CrossesSegment(const Segment &segment) const {
      Point b, c;
      b = segment.a_;
      c = segment.b_;
      Vector ab(b, a_);
      Vector ac(c, a_);
      Vector v(c.x_ - b.x_, c.y_ - b.y_);
      if (segment.ContainsPoint(a_)) {
        return true;
      }
      if (Scalar(v, ab) > 0 && Scalar(v, ac) < 0) {
        return (Cross(ab, v) * Cross(ab, v) <= r_ * r_ * (v.x_ * v.x_ + v.y_ * v.y_)) && //
                std::max(ab.x_ * ab.x_ + ab.y_ * ab.y_, ac.x_ * ac.x_ + ac.y_ * ac.y_) >= r_ * r_;
      }
      return (std::min(ab.x_ * ab.x_ + ab.y_ * ab.y_, ac.x_ * ac.x_ + ac.y_ * ac.y_)) <= r_ * r_ && //
              std::max(ab.x_ * ab.x_ + ab.y_ * ab.y_, ac.x_ * ac.x_ + ac.y_ * ac.y_) >= r_ * r_;
    }

    Circle *Circle::Clone() const {
      auto a = new Circle;
      *a = *this;
      return a;
    }

    std::string Circle::ToString() {
      std::string r = std::to_string(r_);
      return "Circle(" + a_.ToString() + ", " + r + ")";
    }
}
