#include <iostream>
#include <algorithm>

void FindSequence(int* x, int n) {
  auto* d = new int[n + 1];
  auto* pos = new int[n + 1];
  auto* prev = new int[n + 1];
  int length = 0;
  pos[0] = -1;
  d[0] = -10001;
  for (int i = 1; i < n + 1; i++) {
    d[i] = 10001;
  }
  for (int i = 0; i < n; i++) {
    int j = std::lower_bound(d, d + n, x[i]) - d;
    if (d[j - 1] < x[i] && x[i] < d[j]) {
      d[j] = x[i];
      pos[j] = i;
      prev[i] = pos[j - 1];
      length = std::max(length, j);
    }
  }
  auto* result = new int[length + 1];
  int j = length;
  int p = pos[j];
  while (p != -1) {
    result[j] = x[p];
    p = prev[p];
    j--;
  }
  for (int i = 1; i < length + 1; i++) {
    std::cout << result[i] << " ";
  }
  delete[] result;
  delete[] d;
  delete[] pos;
  delete[] prev;
}
