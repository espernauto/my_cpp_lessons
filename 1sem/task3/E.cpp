#include <iostream>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  int64_t s = 0;
  auto** a = new int64_t*[10];
  for (int i = 0; i < 10; i++) {
    a[i] = new int64_t[n + 1];
  }
  if (n == 1) {
    s = 8;
  } else {
    a[0][2] = 2;
    a[1][2] = 2;
    a[2][2] = 2;
    a[3][2] = 2;
    a[4][2] = 3;
    a[5][2] = 0;
    a[6][2] = 3;
    a[7][2] = 2;
    a[8][2] = 2;
    a[9][2] = 2;
    for (int k = 3; k < n + 1; k++) {
      a[0][k] = a[4][k - 1] + a[6][k - 1];
      a[1][k] = a[6][k - 1] + a[8][k - 1];
      a[2][k] = a[7][k - 1] + a[9][k - 1];
      a[3][k] = a[4][k - 1] + a[8][k - 1];
      a[4][k] = a[0][k - 1] + a[3][k - 1] + a[9][k - 1];
      a[5][k] = 0;
      a[6][k] = a[0][k - 1] + a[1][k - 1] + a[7][k - 1];
      a[7][k] = a[2][k - 1] + a[6][k - 1];
      a[8][k] = a[1][k - 1] + a[3][k - 1];
      a[9][k] = a[2][k - 1] + a[4][k - 1];
    }
    for (int i = 0; i < 10; i++) {
      s += a[i][n];
    }
    s -= a[8][n];
    s -= a[0][n];
  }
  std::cout << s;
  for (int i = 0; i < 10; i++) {
    delete[] a[i];
  }
  delete[] a;
}
