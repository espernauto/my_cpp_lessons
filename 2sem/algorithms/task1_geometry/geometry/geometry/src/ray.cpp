#include "../ray.h"
#include "../vector.h"
#include "../segment.h"
#include "../point.h"

namespace geometry {
    Ray &Ray::Move(const Vector &v) {
      this->a_.x_ += v.x_;
      this->a_.y_ += v.y_;
      this->b_.x_ += v.x_;
      this->b_.y_ += v.y_;
      return *this;
    }

    bool Ray::ContainsPoint(const Point &point) const {
      Vector a, b, c;
      a = Vector(a_, point);
      b = Vector(b_, point);
      c = Vector(a_, b_);
      if (Cross(a, c) == 0) {
        return (Scalar(a, c) >= 0);
      }
      return false;
    }

    bool Ray::CrossesSegment(const Segment &segment) const {
      Vector v = Vector(a_, b_);
      Vector a = Vector(a_, segment.a_);
      Vector b = Vector(a_, segment.b_);
      if (Cross(a, v) == 0 && Scalar(a, v) < 0) {
        return Cross(b, v) == 0 && Scalar(b, v) > 0;
      }
      if (Cross(a, v) * Cross(v, b) >= 0) {
        return Cross(a, b) * Cross(a, v) >= 0;
      }
      return false;
    }

    Ray *Ray::Clone() const {
      auto a = new Ray;
      *a = *this;
      return a;
    }

    std::string Ray::ToString() {
      Vector v(a_, b_);
      std::string x = std::to_string(v.x_);
      std::string y = std::to_string(v.y_);
      return "Ray(" + a_.ToString() + ", Vector(" + x + ", " + y + "))";
    }
}
