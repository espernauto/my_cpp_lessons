#ifndef UNTITLED1_RAY_H
#define UNTITLED1_RAY_H

#include "IShape.h"
#include "point.h"

namespace geometry {
    class Ray : public IShape {
    public:
      Point a_;
      Point b_;

      Ray() {
        a_ = Point(0, 0);
        b_ = Point(0, 0);
      }

      Ray(Point a, Point b) {
        a_ = a;
        b_ = b;
      }
      
      ~Ray() override = default;

      Ray &Move(const Vector &) override;

      bool ContainsPoint(const Point &) const override;

      bool CrossesSegment(const Segment &) const override;

      Ray *Clone() const override;

      std::string ToString() override;

    };
}


#endif //UNTITLED1_RAY_H
