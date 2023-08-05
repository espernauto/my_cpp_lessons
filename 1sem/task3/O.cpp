#include <iostream>
#include <algorithm>

void Ans(int** a, int* weights, int k, int s) {
  if (a[k][s] == 0 || k == 0) {
    return;
  }
  if (a[k - 1][s] == a[k][s]) {
    Ans(a, weights, k - 1, s);
  } else {
    Ans(a, weights, k - 1, s - weights[k]);
    std::cout << k << " ";
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  auto* weights = new int[n + 1];
  auto* prices = new int[n + 1];
  for (int i = 1; i < n + 1; i++) {
    std::cin >> weights[i];
  }
  for (int i = 1; i < n + 1; i++) {
    std::cin >> prices[i];
  }
  auto** a = new int*[n + 1];
  for (int i = 0; i < n + 1; i++) {
    a[i] = new int[m + 1];
  }
  for (int i = 0; i < m; i++) {
    a[0][i] = 0;
  }
  for (int i = 0; i < n; i++) {
    a[i][0] = 0;
  }
  for (int k = 1; k < n + 1; k++) {
    for (int s = 1; s < m + 1; s++) {
      if (s >= weights[k]) {
        a[k][s] = std::max(a[k - 1][s], a[k - 1][s - weights[k]] + prices[k]);
      } else {
        a[k][s] = a[k - 1][s];
      }
    }
  }
  Ans(a, weights, n, m);
  for (int i = 0; i < n + 1; i++) {
    delete[] a[i];
  }
  delete[] a;
  delete[] weights;
  delete[] prices;
}
