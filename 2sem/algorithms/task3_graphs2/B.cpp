#include <iostream>
#include <vector>
#include <algorithm>

int DSUGet(int v, std::vector<std::pair<int, int>>& p) {
  return (v == p[v].first) ? v : (p[v].first = DSUGet(p[v].first, p));
}

void DSUUnite(int a, int b, std::vector<std::pair<int, int>>& p) {
  a = DSUGet(a, p);
  b = DSUGet(b, p);
  if (a != b) {
    p[a].first = b;
  }
}

class Graph {
 private:
  std::vector<std::pair<int, std::pair<int, int>>> adjacency_list_;

 public:
  void Push(int begin, int end, int value) {
    adjacency_list_.emplace_back(value, std::make_pair(begin, end));
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  void Check(int m, std::vector<std::pair<int, int>>& p, int value) {
    int a = adjacency_list_[m].second.first;
    int b = adjacency_list_[m].second.second;
    int new_length = p[DSUGet(a, p)].second + value;
    if (DSUGet(a, p) != DSUGet(b, p)) {
      new_length = p[DSUGet(a, p)].second + p[DSUGet(b, p)].second + value;
      DSUUnite(a, b, p);
    }
    p[DSUGet(a, p)].second = new_length;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  int m = 0;
  std::cin >> m;
  Graph graph;
  int start = 0;
  int end = 0;
  std::vector<std::pair<int, int>> p(n + 1);
  for (int j = 0; j < n + 1; j++) {
    p[j] = std::make_pair(j, 0);
  }
  int count = 0;
  for (int i = 0; i < m; i++) {
    int command = 0;
    int value = 0;
    std::cin >> command;
    if (command == 1) {
      std::cin >> start >> end >> value;
      graph.Push(start, end, value);
      graph.Check(count, p, value);
      count++;
    } else {
      int number = 0;
      std::cin >> number;
      std::cout << p[DSUGet(number, p)].second << '\n';
    }
  }
}
