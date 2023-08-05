#include <iostream>

int main() {
  int n, t;
  std::cin >> n >> t;
  int** a = new int*[n];
  for (int i = 0; i < n; i++) {
    a[i] = new int[n];
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      std::cin >> a[i][j];
    }
  }
  int** b = new int*[n];
  for (int i = 0; i < n; i++) {
    b[i] = new int[n];
  }
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      b[i][j] = a[i][j];
    }
  }
  for(int k = 0; k < t; k++) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        int sum = static_cast<bool>(i) * b[(n + i - 1) % n][j] + static_cast<bool>(i) * static_cast<bool>(j) * b[(n + i - 1) % n][(n + j - 1) % n] \
        + static_cast<bool>(i) * static_cast<bool>(j - n + 1) *  b[(n + i - 1) % n][(j + 1) % n] + static_cast<bool>(j) * b[i][(n + j - 1) % n] \
        + static_cast<bool>(j - n + 1) * b[i][(j + 1) % n] + static_cast<bool>(j - n + 1) * static_cast<bool>(i - n + 1) * b[(i + 1) % n][(j + 1) % n] \
        + static_cast<bool>(i - n + 1) * b[(i + 1) % n][j] +  static_cast<bool>(i - n + 1) * static_cast<bool>(j) * b[(i + 1) % n][(n + j - 1) % n];
        if (a[i][j] == 1) {
          if (sum != 2) {
            a[i][j] = 0;
          }
        }
        if (a[i][j] == 0) {
          if (sum == 3) {
            a[i][j] = 1;
          }
        }
      }
    }
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        b[i][j] = a[i][j];
      }
    }
  }
  for(int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < n; i++) {
    delete[]a[i];
  }
  for (int i = 0; i < n; i++) {
    delete[]b[i];
  }
  delete[] a;
  delete[] b;
}
