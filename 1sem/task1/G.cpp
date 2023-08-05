#include <iostream>

void Hanoy(int n, int x, int y) {
  if (n == 1) {
    std::cout << n << " " << x << " " << y << std::endl;
  } else {
    Hanoy(n - 1, x, y);
    std::cout << n << " " << x << " " << 6 - x - y << std::endl;
    Hanoy(n - 1, y, x);
    std::cout << n << " " << 6 - x - y << " " << y << std::endl;
    Hanoy(n - 1, x, y);
  }
}

int main() {
  int n;
  std::cin >> n;
  Hanoy(n, 1, 3);
}
