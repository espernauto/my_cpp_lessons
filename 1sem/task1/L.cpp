#include <iostream>

template <typename F>
void QSort(F* a, int size) {
  int i = 0;
  int j = size - 1;
  F m = a[size / 2];
  do {
    while (a[i] < m) {
      i++;
    }
    while (a[j] > m) {
      j--;
    }
    if (i <= j) {
      int tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      i++;
      j--;
    }
  } while (i <= j);
  if (j > 0) {
    QSort(a, j + 1);
  }
  if (i < size) {
    QSort(&a[i], size - i);
  }
}

template <typename F>
F* Extra(F* a, int len) {
  F save = a[0];
  auto* new_a = new uint64_t[len + 1];
  new_a[1] = save;
  int j = 2;
  for (int i = 1; i < len; i++) {
    if (a[i] != save) {
      new_a[j] = a[i];
      j++;
      save = a[i];
    }
  }
  new_a[0] = j;
  return new_a;
}

int main() {
  int n, m;
  std::cin >> n;
  auto* a = new uint64_t[n];
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cin >> m;
  auto* b = new uint64_t[m];
  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
  }
  QSort(a, n);
  QSort(b, m);
  auto* new_a = Extra(a, n);
  auto* new_b = Extra(b, m);
  int len_a = new_a[0];
  int len_b = new_b[0];
  int flag = 0;
  if (len_a != len_b) {
    std::cout << "NO";
    flag = 1;
  } else {
    for (int i = 0; i < len_a; i++) {
      if (new_a[i] != new_b[i]) {
        std::cout << "NO";
        flag = 1;
        break;
      }
    }
  }
  if (flag == 0) {
    std::cout << "YES";
  }
  delete[] a;
  delete[] b;
  delete[] new_a;
  delete[] new_b;
}
