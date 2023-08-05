#include <iostream>
#include <cstring>
#include <array>

struct Pair {
  int i;
  int j;

  Pair(int a, int b) {
    i = a;
    j = b;
  }

  Pair() {
    i = 0;
    j = 0;
  }

  bool operator==(Pair b) {
    return (i == b.i && j == b.j);
  }
};

void LCS(int *x, int n, int *y, int m, int **lcs, Pair **prev) {
  for (int i = 0; i < n + 1; i++) {
    lcs[i][0] = 0;
  }
  for (int j = 0; j < m + 1; j++) {
    lcs[0][j] = 0;
  }
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < m + 1; j++) {
      if (x[i - 1] == y[j - 1]) {
        lcs[i][j] = lcs[i - 1][j - 1] + 1;
        prev[i][j] = Pair(i - 1, j - 1);
      } else {
        if (lcs[i - 1][j] >= lcs[i][j - 1]) {
          lcs[i][j] = lcs[i - 1][j];
          prev[i][j] = Pair(i - 1, j);
        } else {
          lcs[i][j] = lcs[i][j - 1];
          prev[i][j] = Pair(i, j - 1);
        }
      }
    }
  }
}

void PrintLCS(int *x, int i, int *y, int j, int **lcs, Pair **prev) {
  if (i == 0 || j == 0) {
    return;
  }
  if (prev[i][j] == Pair(i - 1, j - 1)) {
    PrintLCS(x, i - 1, y, j - 1, lcs, prev);
    std::cout << x[i - 1] << " ";
  } else {
    if (prev[i][j] == Pair(i - 1, j)) {
      PrintLCS(x, i - 1, y, j, lcs, prev);
    } else {
      PrintLCS(x, i, y, j - 1, lcs, prev);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n;
  auto *a = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cin >> m;
  auto *b = new int[m];
  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
  }
  auto **lcs = new int *[n + 1];
  for (int i = 0; i < n + 1; i++) {
    lcs[i] = new int[m + 1];
  }
  auto **prev = new Pair *[n + 1];
  for (int i = 0; i < n + 1; i++) {
    prev[i] = new Pair[m + 1];
  }
  LCS(a, n, b, m, lcs, prev);
  PrintLCS(a, n, b, m, lcs, prev);
  for (int i = 0; i < n + 1; i++) {
    delete[] lcs[i];
  }
  for (int i = 0; i < n + 1; i++) {
    delete[] prev[i];
  }
  delete[] lcs;
  delete[] prev;
  delete[] a;
  delete[] b;
}
