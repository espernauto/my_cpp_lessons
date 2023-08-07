#ifndef UNTITLED1_SEGMENT_H
#define UNTITLED1_SEGMENT_H
#include "IShape.h"
#include "point.h"

namespace geometry {
    struct Segment : IShape {
      Point a_;
      Point b_;

      Segment() {
        a_ = Point(0, 0);
        b_ = Point(0, 0);
      }

      Segment(Point a, Point b) {
        a_ = a;
        b_ = b;
      }
      
      ~Segment() override = default;

      Segment &Move(const Vector &) override;

      bool ContainsPoint(const Point &) const override;

      bool CrossesSegment(const Segment &) const override;

      Segment *Clone() const override;

      std::string ToString() override;
    };
}


#endif //UNTITLED1_SEGMENT_H
