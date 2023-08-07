#include <iostream>
#include <cmath>

struct Vector {
  int x = 0;
  int y = 0;
  Vector() : x(0), y(0) {
  }
  Vector(int x1, int y1) : x(x1), y(y1) {
  }
};

Vector operator+(const Vector& vector_1, const Vector& vector_2) {
  Vector vector(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
  return vector;
}

double Length(const Vector& vector_1) {
  return sqrt((vector_1.x) * (vector_1.x) + (vector_1.y) * (vector_1.y));
}

int ScalarProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x * vector_2.x + vector_1.y * vector_2.y;
}

int CrossProduct(const Vector& vector_1, const Vector& vector_2) {
  return vector_1.x * vector_2.y - vector_1.y * vector_2.x;
}

std::istream& operator>>(std::istream& in, Vector& vector) {
  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  vector = Vector(x2 - x1, y2 - y1);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Vector& r) {
  std::cout << r.x << " " << r.y;
  return out;
}

int main() {
  Vector vector_1, vector_2;
  std::cin >> vector_1 >> vector_2;
  std::cout.setf(std::ios::fixed);
  std::cout.precision(6);
  std::cout << Length(vector_1) << " " << Length(vector_2) << '\n';
  std::cout << (vector_1 + vector_2) << '\n';
  std::cout << ScalarProduct(vector_1, vector_2) << " ";
  std::cout << CrossProduct(vector_1, vector_2) << '\n';
  if (CrossProduct(vector_1, vector_2) < 0) {
    std::cout << -static_cast<float>(CrossProduct(vector_1, vector_2)) / 2.0;
  } else {
    std::cout << static_cast<float>(CrossProduct(vector_1, vector_2)) / 2.0;
  }
}

