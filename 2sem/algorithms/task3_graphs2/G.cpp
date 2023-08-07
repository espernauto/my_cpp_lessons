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

  void BellmanFord(int n, int m, int start) {
    int inf = 30000;
    std::vector<int> d(n, inf);
    d[start] = 0;
    for (;;) {
      bool flag = false;
      for (int j = 0; j < m; ++j) {
        if (d[adjacency_list_[j].a_] < inf) {
          if (d[adjacency_list_[j].b_] > d[adjacency_list_[j].a_] + adjacency_list_[j].cost_) {
            d[adjacency_list_[j].b_] = d[adjacency_list_[j].a_] + adjacency_list_[j].cost_;
            flag = true;
          }
        }
      }
      if (!flag) {
        for (int i = 0; i < n; i++) {
          std::cout << d[i] << ' ';
        }
        break;
      }
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  int m = 0;
  std::cin >> m;
  Graph graph;
  for (int i = 0; i < m; i++) {
    int a = 0;
    int b = 0;
    int value = 0;
    std::cin >> a >> b >> value;
    graph.Push(Edge(a - 1, b - 1, value));
  }
  graph.BellmanFord(n, m, 0);
}
