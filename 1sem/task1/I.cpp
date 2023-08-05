#include <iostream>

int main() {
  int64_t w;
  int64_t h;
  int64_t n;
  std::cin >> w >> h >> n;
  int64_t a = 0;
  int64_t b;
  if (w < h) {
    b = w * n;
  } else {
    b = h * n;
  }
  b = std::min(b, 100000000000000000);
  while (a < b) {
    int64_t m = (a + b) / 2;
    if ((m / (h * w)) * m < n) {
      a = m + 1;
    } else {
      b = m;
    }
  }
  std::cout << a;
}
