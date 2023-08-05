#include <iostream>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  int64_t count = 0;
  auto* a = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  auto* dp = new int[n];
  for (int i = 0; i < n; i++) {
    dp[i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) {
        dp[i] += dp[j];
        dp[i] = dp[i] % 1000000;
      }
    }
    count += dp[i];
  }
  std::cout << count % 1000000;
  delete[] a;
  delete[] dp;
}
