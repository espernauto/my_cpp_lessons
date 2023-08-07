#include "../polygon.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {
    Polygon &Polygon::Move(const Vector &v) {
      for (size_t i = 0; i < points_.size(); i++) {
        points_[i].x_ += v.x_;
        points_[i].y_ += v.y_;
      }
      return *this;
    }

    bool Polygon::ContainsPoint(const Point &p) const {
      int counter = 0;
      int flag = 0;
      Segment segment(p, Point(105434, 11897));
      for (size_t i = 0; i < points_.size() - 1; i++) {
        Segment s(points_[i], points_[i + 1]);
        if (segment.CrossesSegment(s) && !s.ContainsPoint(p)) {
          counter++;
        }
        if (s.ContainsPoint(p)) {
          counter = 1;
          flag = 1;
          break;
        }
      }
      Segment s(points_[points_.size() - 1], points_[0]);
      if (segment.CrossesSegment(s) && !s.ContainsPoint(p) && flag == 0) {
        counter++;
      }
      if (s.ContainsPoint(p)) {
        return s.ContainsPoint(p);
      }
      return counter % 2 == 1;
    }

    bool Polygon::CrossesSegment(const Segment &segment) const {
      for (size_t i = 0; i < points_.size() - 1; i++) {
        Segment s(points_[i], points_[i + 1]);
        if (s.CrossesSegment(segment)) {
          return true;
        }
      }
      return false;
    }

    Polygon *Polygon::Clone() const {
      auto *a = new Polygon;
      *a = *this;
      return a;
    }

    std::string Polygon::ToString() {
      std::string result = "Polygon(";
      for (size_t i = 0; i < points_.size() - 1; i++) {
        result += points_[i].ToString();
        result += ", ";
      }
      result += points_[points_.size() - 1].ToString();
      result += ")";
      return result;
    }
}
