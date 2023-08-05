#include <iostream>
#include <algorithm>

int main() {
  int m, n;
  std::cin >> m >> n;
  auto** a = new int64_t*[m + 1];
  for (int i = 0; i < m + 1; i++) {
    a[i] = new int64_t[n + 1];
  }
  for (int i = 0; i < m + 1; i++) {
    for (int j = 0; j < n + 1; j++) {
      a[i][j] = 0;
    }
  }
  a[0][0] = 1;
  for (int i = 1; i < m + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      for (int k = 1; k < j + 1; k++) {
        a[i][j] = a[i][j] + a[i - 1][k - 1] + a[i - 1][k];
      }
    }
  }
  std::cout << a[m][n];
  for (int i = 0; i < m + 1; i++) {
    delete[] a[i];
  }
  delete[] a;
}
