#ifndef UNTITLED1_CIRCLE_H
#define UNTITLED1_CIRCLE_H

#include "IShape.h"
#include "point.h"

namespace geometry {
    struct Circle : IShape {
      Point a_;
      int64_t r_;

      Circle() {
        a_ = Point(0, 0);
        r_ = 0;
      }

      Circle(Point a, int64_t r) {
        a_ = a;
        r_ = r;
      }
      
      ~Circle() override = default;

      Circle &Move(const Vector &) override;

      bool ContainsPoint(const Point &) const override;

      bool CrossesSegment(const Segment &) const override;

      Circle *Clone() const override;

      std::string ToString() override;
    };
}


#endif //UNTITLED1_CIRCLE_H
