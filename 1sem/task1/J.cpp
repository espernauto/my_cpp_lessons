#include <iostream>

char* Reverse(char* direct, int new_len) {
  auto* reverse = new char[new_len + 1];
  for (int i = 0; i < new_len; i++) {
    reverse[new_len - i - 1] = direct[i];
  }
  return reverse;
}

char* AppendElement(char* direct, int k, char el, int len) {
  auto* ap = new char[len + 1];
  for (int i = 0; i < len + 1; i++) {
    if (i < k) {
      ap[i] = direct[i];
    }
    if (i == k) {
      ap[i] = el;
    }
    if (i > k) {
      ap[i] = direct[i - 1];
    }
  }
  return ap;
}

char* ChangeElement(char* direct, int k, char el, int len) {
  auto* ch = new char[len];
  for (int i = 0; i < len; i++) {
    if (i < k) {
      ch[i] = direct[i];
    }
    if (i == k) {
      ch[i] = el;
    }
    if (i > k) {
      ch[i] = direct[i];
    }
  }
  return ch;
}

int main() {
  char s[1000000];
  char a = getchar();
  int i = 0;
  while (a != '\n') {
    s[i] = a;
    a = getchar();
    i++;
  }
  int len = i + 1;
  auto* direct = new char[len + 1];
  int new_len = 0;
  char letter_distance = 'a' - 'A';
  for (int i = 0; i < len; i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      direct[new_len] = s[i];
      new_len++;
    }
    if (s[i] >= 'a' && s[i] <= 'z') {
      direct[new_len] = static_cast<char>(static_cast<int>(s[i]) - letter_distance);
      new_len++;
    }
  }
  auto* reverse = Reverse(direct, new_len);
  auto** trash = new char*[6 * new_len + 4];
  int m = 2;
  trash[0] = direct;
  trash[1] = reverse;
  int flag = 0;
  auto* direct_copy = new char[new_len];
  auto* reverse_copy = new char[new_len];
  for (int i = 0; i < new_len; i++) {
    direct_copy[i] = direct[i];
  }
  for (int i = 0; i < new_len; i++) {
    reverse_copy[i] = reverse[i];
  }
  for (int i = 0; i < new_len; i++) {
    if (direct[i] != reverse[i] && flag < 2) {
      reverse = ChangeElement(reverse, i, direct[i], new_len);
      direct = ChangeElement(direct, new_len - i - 1, direct[i], new_len);
      trash[m] = reverse;
      trash[m + 1] = direct;
      m = m + 2;
      flag++;
    } else if (flag == 2) {
      i = new_len;
    }
  }
  if (flag < 2) {
    std::cout << "YES" << std::endl;
    for (int k = 0; k < new_len; k++) {
      std::cout << reverse[k];
    }
  }
  for (int i = 0; i < new_len; i++) {
    direct[i] = direct_copy[i];
  }
  for (int i = 0; i < new_len; i++) {
    reverse[i] = reverse_copy[i];
  }
  if (flag == 2) {
    flag = 0;
    for (int i = 0; i < new_len + 1; i++) {
      if (direct[i] != reverse[i] && flag < 2) {
        reverse = AppendElement(reverse, i, direct[i], new_len);
        direct = AppendElement(direct, new_len - i, direct[i], new_len);
        trash[m] = reverse;
        trash[m + 1] = direct;
        m = m + 2;
        flag++;
      } else if (flag == 2) {
        i = new_len;
      }
    }
    if (flag == 1) {
      std::cout << "YES" << std::endl;
      for (int k = 0; k < new_len + 1; k++) {
        std::cout << reverse[k];
      }
    }
  }
  for (int i = 0; i < new_len; i++) {
    direct[i] = direct_copy[i];
  }
  for (int i = 0; i < new_len; i++) {
    reverse[i] = reverse_copy[i];
  }
  if (flag == 2) {
    flag = 0;
    for (int i = 0; i < new_len + 1; i++) {
      if (direct[i] != reverse[i] && flag < 2) {
        reverse = AppendElement(reverse, new_len - i, reverse[i], new_len);
        direct = AppendElement(direct, i, reverse[i], new_len);
        trash[m] = reverse;
        trash[m + 1] = direct;
        m = m + 2;
        flag++;
      } else if (flag == 2) {
        i = new_len;
      }
    }
    if (flag == 1) {
      std::cout << "YES" << std::endl;
      for (int k = 0; k < new_len + 1; k++) {
        std::cout << reverse[k];
      }
    }
  }
  if (flag == 2) {
    std::cout << "NO";
  }
  delete[] reverse_copy;
  delete[] direct_copy;
  for (int i = 0; i < m; i++) {
    delete[] trash[i];
  }
  delete[] trash;
}
