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

  std::vector<std::vector<int64_t>> BellmanFord(int start, int k, int n, int64_t inf) {
    std::vector<std::vector<int64_t>> distances(n);
    for (size_t i = 0; i < distances.size(); i++) {
      distances[i].resize(n, inf);
    }
    distances[start][0] = 0;
    for (int i = 0; i < k; ++i) {
      int prev = i % 2;
      int current = 1 - (i % 2);
      for (auto edge : adjacency_list_) {
        if (distances[edge.b_][current] > distances[edge.a_][prev] + edge.cost_) {
          distances[edge.b_][current] = distances[edge.a_][prev] + edge.cost_;
        }
      }
      for (int j = 0; j < n; ++j) {
        distances[j][current] = std::min(distances[j][current], distances[j][prev]);
      }
    }
    return distances;
  }

  int64_t ShortestPath(int start, int end, int k, int n) {
    int64_t inf = 1000000;
    auto distances = BellmanFord(start, k, n, inf);
    if (distances[end][k % 2] < inf) {
      return distances[end][k % 2];
    }
    return -1;
  }
};

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  int start = 0;
  int end = 0;
  std::cin >> n >> m >> k >> start >> end;
  Graph graph;
  for (int i = 0; i < m; i++) {
    int from = 0;
    int to = 0;
    int value = 0;
    std::cin >> from >> to >> value;
    graph.Push(Edge(from - 1, to - 1, value));
  }
  std::cout << graph.ShortestPath(start - 1, end - 1, k, n);
}
