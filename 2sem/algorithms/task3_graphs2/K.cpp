#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int a_ = 0;
  int b_ = 0;
  int cost_ = 0;

  Edge() = default;

  Edge(int a, int b, int cost) {
    a_ = a;
    b_ = b;
    cost_ = cost;
  }
};

class Graph {
 private:
  std::vector<Edge> adjacency_list_;

 public:
  void Push(Edge edge) {
    adjacency_list_.emplace_back(edge);
  }

  void BellmanFord(int n, int m) {
    int inf = 1000000;
    std::vector<int> d(n);
    std::vector<int> p(n, -1);
    int x = -1;
    for (int i = 0; i < n; i++) {
      x = -1;
      for (int j = 0; j < m; j++) {
        if (d[adjacency_list_[j].b_] > d[adjacency_list_[j].a_] + adjacency_list_[j].cost_) {
          d[adjacency_list_[j].b_] = std::max(d[adjacency_list_[j].a_] + adjacency_list_[j].cost_, -inf);
          p[adjacency_list_[j].b_] = adjacency_list_[j].a_;
          x = adjacency_list_[j].b_;
        }
      }
    }
    if (x == -1) {
      std::cout << "NO" << '\n';
    } else {
      std::cout << "YES" << '\n';
      int y = x;
      for (int i = 0; i < n; ++i) {
        y = p[y];
      }
      std::vector<int> path;
      for (int cur = y;; cur = p[cur]) {
        path.push_back(cur);
        if (cur == y && path.size() > 1) {
          break;
        }
      }
      reverse(path.begin(), path.end());
      std::cout << path.size() << '\n';
      for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] + 1 << ' ';
      }
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph;
  int m = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int value = 0;
      std::cin >> value;
      if (value < 100000 && value >= -100000) {
        m += 1;
        graph.Push(Edge(i, j, value));
      }
    }
  }
  graph.BellmanFord(n, m);
}
