#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int& x : a) {
    std::cin >> x;
  }

  int x;
  std::cin >> x;
  auto it = std::remove_if(a.begin(), a.end(), [&x](const int& v) { return v != x; });
  std::cout << (it - a.begin()) << '\n';
}
