#ifndef UNTITLED1_POINT_H
#define UNTITLED1_POINT_H

#include <iostream>
#include "IShape.h"

namespace geometry {
    struct Point : IShape {
      int64_t x_;
      int64_t y_;

      Point() {
        x_ = 0;
        y_ = 0;
      }

      Point(int64_t x, int64_t y) {
        x_ = x;
        y_ = y;
      }
      
      ~Point() override = default;

      Point operator-() const;

      Point &Move(const Vector &) override;

      bool ContainsPoint(const Point &) const override;

      bool CrossesSegment(const Segment &) const override;

      Point *Clone() const override;

      std::string ToString() override;

      friend std::istream &operator>>(std::istream &in, Point &);
    };

    Vector operator-(const Point &a, const Point &b);

    std::ostream &operator<<(std::ostream &out, const Point &r);

}



#endif //UNTITLED1_POINT_H
