#include <iostream>
#include <algorithm>

int Multiplication(int l, int r, int** dp, int* v) {
  if (dp[l][r] == -1) {
    if (l == r - 1) {
      dp[l][r] = 0;
    } else {
      dp[l][r] = 1000000000;
      for (int i = l + 1; i < r; i++) {
        dp[l][r] = std::min(dp[l][r], v[l] * v[i] * v[r] + Multiplication(l, i, dp, v) + Multiplication(i, r, dp, v));
      }
    }
  }
  return dp[l][r];
}

int main() {
  int n;
  std::cin >> n;
  auto* sizes = new int[n + 1];
  for (int i = 0; i < n; i++) {
    std::cin >> sizes[i];
  }
  auto** dp = new int*[n + 1];
  for (int i = 0; i < n; i++) {
    dp[i] = new int[n + 1];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dp[i][j] = -1;
    }
  }
  std::cout << Multiplication(0, n - 1, dp, sizes);
  for (int i = 0; i < n; i++) {
    delete[] dp[i];
  }
  delete[] dp;
  delete[] sizes;
}
