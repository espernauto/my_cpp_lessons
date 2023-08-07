#ifndef UNTITLED1_POLYGON_H
#define UNTITLED1_POLYGON_H

#include <vector>

#include "IShape.h"
#include "point.h"

namespace geometry {
    struct Polygon : public IShape {
      std::vector<Point> points_;

      Polygon() {
        points_.emplace_back(Point(0, 0));
      }

      explicit Polygon(std::vector<Point> points) {
        for (size_t i = 0; i < points.size(); i++) {
          points_.emplace_back(points[i]);
        }
      }
      
      ~Polygon() override = default;

      Polygon &Move(const Vector &) override;

      bool ContainsPoint(const Point &) const override;

      bool CrossesSegment(const Segment &) const override;

      Polygon *Clone() const override;

      std::string ToString() override;
    };
}


#endif //UNTITLED1_POLYGON_H
