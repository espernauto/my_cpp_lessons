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
  int m = 0;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n + 1);
  for (int i = 0; i < m; i++) {
    int64_t start = 0;
    int64_t end = 0;
    int64_t value = 0;
    std::cin >> start >> end >> value;
    graph.Push(start - 1, end - 1, value);
    graph.Push(end - 1, start - 1, value);
  }
  int64_t inf = 1000000000;
  std::vector<int64_t> min_e(n, inf);
  std::vector<int64_t> sel_e(n, 0);
  graph.Prim(min_e, sel_e);
}
