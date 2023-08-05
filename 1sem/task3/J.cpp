#include <iostream>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  auto* x = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }
  std::sort(x, x + n);
  auto* dp = new int[n + 1];
  dp[0] = x[1] - x[0];
  if (n > 2) {
    dp[1] = x[2] - x[0];
    for (int i = 2; i < n - 1; i++) {
      dp[i] = std::min(dp[i - 2], dp[i - 1]) + x[i + 1] - x[i];
    }
    std::cout << dp[n - 2] << '\n';
  } else {
    std::cout << dp[0];
  }
  delete[] x;
  delete[] dp;
}
