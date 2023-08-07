#ifndef UNTITLED1_LINE_H
#define UNTITLED1_LINE_H


#include "IShape.h"
#include "point.h"

namespace geometry {
    struct Line : public IShape {
      Point a_;
      Point b_;

      Line() {
        a_ = Point(0, 0);
        b_ = Point(0, 0);
      }

      Line(Point a, Point b) {
        a_ = a;
        b_ = b;
      }
      
      ~Line() override = default;

      Line &Move(const Vector &) override;

      bool ContainsPoint(const Point &) const override;

      bool CrossesSegment(const Segment &) const override;

      Line *Clone() const override;

      std::string ToString() override;
    };
}


#endif //UNTITLED1_LINE_H
