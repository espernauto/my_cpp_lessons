#include "cstring.h"

std::size_t Strlen(const char* str) {
  std::size_t i = 0;
  for (; str[i] != '\0'; i++) {
  }
  return i;
}

int Strcmp(const char* first, const char* second) {
  if (Strlen(first) < Strlen(second)) {
    return -1;
  }
  if (Strlen(first) > Strlen(second)) {
    return 1;
  }
  for (size_t i = 0; i < Strlen(first); i++) {
    if (first[i] < second[i]) {
      return -1;
    }
    if (first[i] > second[i]) {
      return 1;
    }
  }
  return 0;
}
int Strncmp(const char* first, const char* second, std::size_t count) {
  std::size_t len_first, len_second;
  if (Strlen(first) < count) {
    len_first = Strlen(first);
  } else {
    len_first = count;
  }
  if (Strlen(second) < count) {
    len_second = Strlen(second);
  } else {
    len_second = count;
  }
  if (len_first < len_second) {
    return -1;
  }
  if (len_first > len_second) {
    return 1;
  }
  for (size_t i = 0; i < len_first; i++) {
    if (first[i] < second[i]) {
      return -1;
    }
    if (first[i] > second[i]) {
      return 1;
    }
  }
  return 0;
}

char* Strcpy(char* dest, const char* src) {
  std::size_t len_first = Strlen(src);
  for (std::size_t i = 0; i < len_first + 1; i++) {
    *(dest + i) = *(src + i);
  }
  return dest;
}

char* Strncpy(char* dest, const char* src, std::size_t count) {
  std::size_t len_first = Strlen(src);
  if (count <= len_first) {
    for (std::size_t i = 0; i < count; i++) {
      *(dest + i) = *(src + i);
    }
  } else {
    for (std::size_t i = 0; i < len_first + 1; i++) {
      *(dest + i) = *(src + i);
    }
    for (std::size_t i = len_first + 1; i < count; i++) {
      *(dest + i) = '\0';
    }
  }
  return dest;
}

char* Strcat(char* to, const char* from) {
  std::size_t a, b;
  a = Strlen(&to[0]);
  b = Strlen(&from[0]);
  for (std::size_t i = 0; i < b; i++) {
    to[a + i] = from[i];
  }
  to[a + b] = '\0';
  return to;
}

char* Strncat(char* to, const char* from, std::size_t count) {
  std::size_t a, b;
  a = Strlen(&to[0]);
  if (Strlen(from) < count) {
    b = Strlen(from);
  } else {
    b = count;
  }
  for (std::size_t i = 0; i < b; i++) {
    to[a + i] = from[i];
  }
  to[a + b] = '\0';
  return to;
}

const char* Strchr(const char* str, char symbol) {
  std::size_t len = Strlen(str) + 1;
  for (std::size_t i = 0; i < len; i++) {
    if (str[i] == symbol) {
      return str + i;
    }
  }
  return nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  std::size_t len = Strlen(str) + 1;
  std::size_t last = len;
  for (size_t i = 0; i < len; i++) {
    if (str[i] == symbol) {
      last = i;
    }
  }
  if (last < len) {
    return str + last;
  }
  return nullptr;
}

std::size_t Strspn(const char* dest, const char* src) {
  std::size_t len = Strlen(dest);
  std::size_t len_src = Strlen(src);
  std::size_t num = 0;
  int flag = 0;
  for (std::size_t i = 0; i < len; i++) {
    char symbol = dest[i];
    for (std::size_t j = 0; j < len_src; j++) {
      if (symbol == src[j]) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) {
      num++;
      flag = 0;
    } else {
      return num;
    }
  }
  return num;
}

std::size_t Strcspn(const char* dest, const char* src) {
  std::size_t len = Strlen(dest);
  std::size_t len_src = Strlen(src);
  std::size_t num = 0;
  int flag = 0;
  for (std::size_t i = 0; i < len; i++) {
    char symbol = dest[i];
    for (std::size_t j = 0; j < len_src; j++) {
      if (symbol == src[j]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      num++;
    } else {
      return num;
    }
  }
  return num;
}
const char* Strpbrk(const char* dest, const char* src) {
  std::size_t len = Strlen(dest);
  std::size_t len_src = Strlen(src);
  for (std::size_t i = 0; i < len; i++) {
    char symbol = dest[i];
    for (std::size_t j = 0; j < len_src; j++) {
      if (symbol == src[j]) {
        return dest + i;
      }
    }
  }
  return nullptr;
}
const char* Strstr(const char* text, const char* pattern) {
  int check = 0;
  std::size_t len_pattern = Strlen(pattern);
  auto* stroka1 = new char[len_pattern];
  std::size_t len_text = Strlen(&text[0]);
  if (len_pattern == 0) {
    delete[] stroka1;
    return text;
  }
  if (len_text == 0) {
    delete[] stroka1;
    return nullptr;
  }
  for (std::size_t j = 0; j < len_text - len_pattern + 1; j++) {
    for (std::size_t i = 0; i < len_pattern; i++) {
      stroka1[i] = text[i + j];
    }
    for (std::size_t i = 0; i < len_pattern; i++) {
      if (pattern[i] != stroka1[i]) {
        check = -1;
      }
    }
    if (check == 0) {
      delete[] stroka1;
      return text + j;
    }
    check = 0;
  }
  delete[] stroka1;
  return nullptr;
}
