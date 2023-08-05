#include <iostream>

int main() {
  char s[100000];
  char a = getchar();
  int len = 0;
  while (a != 35) {
    s[len] = a;
    a = getchar();
    len++;
  }
  for (int i = 0; i < len; i = i + 2) {
    std::cout << s[i];
  }
  if (len % 2 == 0) {
    for (int i = len - 1; i > 0; i = i - 2) {
      std::cout << s[i];
    }
  } else {
    for (int i = len - 2; i > 0; i = i - 2) {
      std::cout << s[i];
    }
  }
}
