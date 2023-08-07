#ifndef UNTITLED1_ISHAPE_H
#define UNTITLED1_ISHAPE_H
#include <iostream>

namespace geometry {
    class Point;
    class Vector;
    class Segment;
    class IShape {
    public:
      virtual IShape &Move(const Vector &) = 0;

      virtual bool ContainsPoint(const Point &) const = 0;

      virtual bool CrossesSegment(const Segment &) const = 0;

      virtual IShape *Clone() const = 0;

      virtual std::string ToString() = 0;
      
      virtual ~IShape() = default;
    };
}


#endif //UNTITLED1_ISHAPE_H
