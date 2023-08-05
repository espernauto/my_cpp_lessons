#include <iostream>

struct Operation {
  int count_operation;
};

int main() {
  int n;
  std::cin >> n;
  auto* x = new Operation[n + 1];
  x[1].count_operation = 0;
  x[0].count_operation = 0;
  for (int i = 2; i < n + 1; i++) {
    x[i].count_operation = 1000000;
  }
  for (int i = 0; i < n; i++) {
    if (x[i + 1].count_operation > x[i].count_operation + 1) {
      x[i + 1].count_operation = x[i].count_operation + 1;
    }
    if (i * 2 <= n && x[i * 2].count_operation > x[i].count_operation + 1) {
      x[i * 2].count_operation = x[i].count_operation + 1;
    }
    if (i * 3 <= n && x[i * 3].count_operation > x[i].count_operation + 1) {
      x[i * 3].count_operation = x[i].count_operation + 1;
    }
  }
  std::cout << x[n].count_operation;
  delete[] x;
}
