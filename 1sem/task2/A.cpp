#include <iostream>
#include <algorithm>

struct Students {
  char name[40];
  char surname[40];
  int sum_mark;
  int position;
};

bool Cmp(Students &a, Students &b) {
  if (a.sum_mark != b.sum_mark) {
    return a.sum_mark > b.sum_mark;
  }
  return a.position < b.position;
}

int main() {
  int n;
  std::cin >> n;
  auto *list = new Students[n];
  for (int i = 0; i < n; i++) {
    int a, b, c;
    std::cin >> list[i].name >> list[i].surname >> a >> b >> c;
    list[i].sum_mark = a + b + c;
    list[i].position = i;
  }
  std::sort(list, list + n, Cmp);
  for (int i = 0; i < n; i++) {
    std::cout << list[i].name << " " << list[i].surname << '\n';
  }
  delete[] list;
}
