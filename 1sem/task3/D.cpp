#include <iostream>

int main() {
  int n;
  std::cin >> n;
  auto* x = new int[n];
  x[0] = 3;
  if (n > 1) {
    x[1] = 8;
  }
  for (int i = 2; i < n; i++) {
    x[i] = x[i - 1] * 3 - x[i - 2] + x[i - 2] * 3 - x[i - 1];
  }
  std::cout << x[n - 1];
  delete[] x;
}
