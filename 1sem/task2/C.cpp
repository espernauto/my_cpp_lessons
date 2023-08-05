#include <iostream>
#include <algorithm>

struct Dim {
  uint64_t x;
  uint64_t y;
  uint64_t Max() {
    if (x < y) {
      return y;
    }
    return x;
  }
};

int main() {
  int n;
  std::cin >> n;
  uint64_t count = 0;
  auto* boxes = new Dim[n];
  for (int i = 0; i < n; i++) {
    std::cin >> boxes[i].x >> boxes[i].y;
    count += boxes[i].Max();
  }
  std::cout << count;
  delete[] boxes;
}
