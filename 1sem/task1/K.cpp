#include <iostream>

int main() {
  int k;
  std::cin >> k;
  char s[1000000];
  char a = getchar();
  a = getchar();
  int len = 0;
  while (a != '\n') {
    s[len] = a;
    a = getchar();
    len++;
  }
  int script_counter = 0;
  int consequent = 1;
  for (int i = 0; i < len - k; i++) {
    if (s[i] == s[i + k]) {
      script_counter += consequent;
      consequent++;
    } else {
      consequent = 1;
    }
  }
  std::cout << script_counter;
}
