#include <iostream>

int* Exchange(int* a, int pos, int n) {
  auto* b = new int[n];
  for (int i = 0; i < n; i++) {
    if (i == pos) {
      if (a[i] == 0) {
        b[i] = 1;
      } else {
        b[i] = 0;
      }
    } else {
      b[i] = a[i];
    }
  }
  delete[] a;
  return b;
}

int Sum(int* a, int n) {
  int k = 0;
  for (int i = 0; i < n; i++) {
    k += a[i];
  }
  return k;
}

int* Step(int* a, int n) {
  int pos = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] != 0) {
      pos = i + 1;
      break;
    }
  }
  if (pos <= n - 1) {
    a = Exchange(a, pos, n);
    if (a[pos] == 0) {
      std::cout << -(pos + 1) << " ";
    } else {
      std::cout << pos + 1 << " ";
    }
  }
  if (n != 2 && Sum(a, n) < n) {
    a = Exchange(a, 0, n);
    if (a[0] == 1) {
      std::cout << 1 << " ";
    } else {
      std::cout << -1 << " ";
    }
  }
  return a;
}

int main() {
  int n;
  std::cin >> n;
  auto* a = new int[n];
  for (int i = 0; i < n; i++) {
    a[i] = 0;
  }
  a[0] = 1;
  std::cout << 1 << " ";
  while (Sum(a, n) < n) {
    a = Step(a, n);
  }
  delete[] a;
}
