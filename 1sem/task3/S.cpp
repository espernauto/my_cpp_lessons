#include <iostream>
#include <algorithm>

int PalSubSeq(int left, int right, char* s, int** d) {
  if (d[left][right] == -1) {
    if (s[left] == s[right]) {
      d[left][right] = PalSubSeq(left + 1, right - 1, s, d) + 2;
    } else {
      d[left][right] = std::max(PalSubSeq(left + 1, right, s, d), PalSubSeq(left, right - 1, s, d));
    }
  }
  return d[left][right];
}

int main() {
  char s1[10000];
  char a = getchar();
  int len = 0;
  while (a != '\n') {
    s1[len] = a;
    a = getchar();
    len++;
  }
  auto** d = new int*[len];
  for (int i = 0; i < len; i++) {
    d[i] = new int[len];
  }
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      if (i == j) {
        d[i][j] = 1;
      }
      if (i > j) {
        d[i][j] = 0;
      }
      if (i < j) {
        d[i][j] = -1;
      }
    }
  }
  std::cout << len - PalSubSeq(0, len - 1, s1, d);
  for (int i = 0; i < len; i++) {
    delete[] d[i];
  }
  delete[] d;
}
