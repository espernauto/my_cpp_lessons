#include "../segment.h"
#include "../vector.h"

namespace geometry {
    Segment &Segment::Move(const Vector &v) {
      this->a_.x_ += v.x_;
      this->a_.y_ += v.y_;
      this->b_.x_ += v.x_;
      this->b_.y_ += v.y_;
      return *this;
    }

    bool Segment::ContainsPoint(const Point &point) const {
      Vector a, b, c;
      a = Vector(point, a_);
      b = Vector(point, b_);
      c = Vector(this->a_, this->b_);
      if (Cross(a, b) == 0) {
        if (Scalar(a, c) <= 0) {
          return Scalar(a, b) <= 0;
        }
      }
      return false;
    }

    bool Segment::CrossesSegment(const Segment &b) const {
      Vector ac = Vector(b.a_, a_);
      Vector ad = Vector(b.b_, a_);
      Vector bc = Vector(b.a_, b_);
      Vector bd = Vector(b.b_, b_);
      Vector ab = Vector(b_, a_);
      Vector cd = Vector(b.b_, b.a_);
      int sign_1 = Sign(Cross(ac, ab)) * Sign(Cross(ab, ad));
      int sign_2 = Sign(Cross(ac, cd)) * Sign(Cross(cd, bc));
      if (Cross(ac, ab) == 0 && Cross(ab, ad) == 0) {
        return (Scalar(ab, ac) * Scalar(ab, bc) <= 0) || (Scalar(ab, bd) * Scalar(ab, ad) <= 0) ||
               (Scalar(ac, cd) * Scalar(ad, cd) <= 0) || (Scalar(bc, cd) * Scalar(bd, cd) <= 0);
      }
      return (sign_1 >= 0 && sign_2 >= 0);
    }

    Segment *Segment::Clone() const {
      auto a = new Segment;
      *a = *this;
      return a;
    }

    std::string Segment::ToString() {
      return "Segment(" + a_.ToString() + ", " + b_.ToString() + ")";
    }
}
