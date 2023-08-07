//
// Created by ars1suhod on 08.03.23.
//

#include "../line.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {
    Line &Line::Move(const Vector &v) {
      this->a_.x_ += v.x_;
      this->a_.y_ += v.y_;
      this->b_.x_ += v.x_;
      this->b_.y_ += v.y_;
      return *this;
    }

    bool Line::ContainsPoint(const Point &p) const {
      Vector a, b, c;
      a = Vector(p.x_ - this->a_.x_, p.y_ - this->a_.y_);
      b = Vector(this->a_, this->b_);
      return Cross(a, b) == 0;
    }

    bool Line::CrossesSegment(const Segment &segment) const {
      Vector v = Vector(this->a_, this->b_);
      Vector a = Vector(segment.a_, a_);
      Vector b = Vector(segment.b_, a_);
      return Cross(v, a) * Cross(v, b) <= 0;
    }

    Line *Line::Clone() const {
      auto *a = new Line;
      *a = *this;
      return a;
    }

    std::string Line::ToString() {
      int a = b_.y_ - a_.y_;
      int b = a_.x_ - b_.x_;
      int c = -(a * a_.x_ + b * a_.y_);
      return "Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
    }
}
