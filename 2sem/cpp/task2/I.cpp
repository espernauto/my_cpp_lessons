#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> q;
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    q.push_back(x);
  }
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_q(q.begin(), q.end());
  double res = 0;
  while (min_q.size() > 1) {
    double s = min_q.top();
    min_q.pop();
    s += min_q.top();
    min_q.pop();
    res += s;
    min_q.push(s);
  }
  std::cout << res * 5 / 100;
}
