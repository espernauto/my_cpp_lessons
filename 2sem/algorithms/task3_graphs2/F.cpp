#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<std::pair<int64_t, int64_t>>> adjacency_list_;

 public:
  void Push(int64_t begin, int64_t end, int64_t value) {
    adjacency_list_[begin].emplace_back(std::make_pair(end, value));
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  void Prim(std::vector<int64_t>& min_e, std::vector<int64_t>& sel_e) {
    min_e[0] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    int64_t sum = 0;
    q.push(std::make_pair(0, 0));
    while (!q.empty()) {
      std::pair<int, int> c = q.top();
      q.pop();
      int dst = c.first;
      int v = c.second;
      if (sel_e[v]) {
        continue;
      }
      sel_e[v] = 1;
      sum += dst;
      for (std::pair<int, int> e : adjacency_list_[v]) {
        int u = e.first;
        int len_vu = e.second;
        if (!sel_e[u]) {
          q.push({len_vu, u});
        }
      }
    }
    std::cout << sum;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph;
  graph.Resize(n + 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int64_t value = 0;
      std::cin >> value;
      if (value != 0) {
        graph.Push(i, j, value);
        graph.Push(j, i, value);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    int price = 0;
    std::cin >> price;
    graph.Push(i, n, price);
    graph.Push(n, i, price);
  }
  int64_t inf = 1000000000;
  std::vector<int64_t> min_e(n + 1, inf);
  std::vector<int64_t> sel_e(n + 1, 0);
  graph.Prim(min_e, sel_e);
}
