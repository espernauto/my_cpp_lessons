#include <iostream>

void Check(uint64_t* a, uint64_t* tmp, uint64_t* res, uint64_t n, int m, int pos = 0, uint64_t sum = 0) {
  uint64_t len_tmp = tmp[0];
  if (pos == m) {
    if (sum == n) {
      if (len_tmp < res[0]) {
        a[m] = 1;
        for (uint64_t i = 0; i < len_tmp + 1; i++) {
          res[i] = tmp[i];
        }
      }
      return;
    }
    return;
  }
  Check(a, tmp, res, n, m, pos + 1, sum);
  tmp[tmp[0] + 1] = a[pos];
  tmp[0]++;
  Check(a, tmp, res, n, m, pos + 1, sum + a[pos]);
  tmp[tmp[0] + 1] = a[pos];
  tmp[0]++;
  Check(a, tmp, res, n, m, pos + 1, sum + 2 * a[pos]);
  tmp[0]--;
  tmp[0]--;
}

int main() {
  uint64_t n;
  int m;
  std::cin >> n >> m;
  auto* a = new uint64_t[m + 1];
  uint64_t max_sum = 0;
  for (int i = 0; i < m; i = i + 1) {
    std::cin >> a[i];
    max_sum += 2 * a[i];
  }
  a[m] = 0;
  if (max_sum < n) {
    std::cout << -1;
  } else {
    auto* tmp = new uint64_t[2 * m + 1];
    auto* res = new uint64_t[2 * m + 1];
    tmp[0] = 0;
    res[0] = 2 * m + 1;
    Check(a, tmp, res, n, m);
    if (a[m] == 0) {
      res[0] = 0;
    }
    std::cout << res[0] << '\n';
    for (uint64_t i = 1; i < res[0] + 1; i++) {
      std::cout << res[i] << " ";
    }
    delete[] tmp;
    delete[] res;
  }
  delete[] a;
}
