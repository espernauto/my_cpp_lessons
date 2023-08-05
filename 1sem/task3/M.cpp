#include <iostream>

void Levenshtein(char* s1, char* s2, int m, int n) {
  auto** d = new int*[m + 1];
  for (int i = 0; i < m + 1; i++) {
    d[i] = new int[n + 1];
  }
  d[0][0] = 0;
  for (int j = 1; j < n; j++) {
    d[0][j] = d[0][j - 1] + 1;
  }
  for (int i = 1; i < m + 1; i++) {
    d[i][0] = d[i - 1][0] + 1;
    for (int j = 1; j < n + 1; j++) {
      if (s1[i - 1] != s2[j - 1]) {
        d[i][j] = std::min(std::min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + 1);
      } else {
        d[i][j] = d[i - 1][j - 1];
      }
    }
  }
  std::cout << d[m][n];
  for (int i = 0; i < m + 1; i++) {
    delete[] d[i];
  }
  delete[] d;
}

int main() {
  char s1[5000];
  char s2[5000];
  char a = getchar();
  int i = 0;
  while (a != '\n') {
    s1[i] = a;
    a = getchar();
    i++;
  }
  int j = 0;
  a = getchar();
  while (a != '\n') {
    s2[j] = a;
    a = getchar();
    j++;
  }
  Levenshtein(s1, s2, i + 1, j + 1);
}
