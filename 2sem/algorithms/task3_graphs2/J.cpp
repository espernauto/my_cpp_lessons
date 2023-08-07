#include <iostream>
#include <vector>

class Graph {
 public:
  std::vector<std::vector<int64_t>> adjacency_list_;

  std::vector<int64_t> Neighbors(int v) {
    std::vector<int64_t> neighbors;
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      neighbors.emplace_back(adjacency_list_[v][i]);
    }
    return neighbors;
  }
};

void Relax(int64_t i, int j, std::vector<int64_t> &dist, Graph &graph) {
  if (dist[i] + graph.adjacency_list_[i][j] < dist[j]) {
    dist[j] = dist[i] + graph.adjacency_list_[i][j];
  }
}

void Dijkstra(int n, std::vector<int64_t> &dist, std::vector<int64_t> &used, Graph &graph) {
  for (int i = 1; i < n; i++) {
    int64_t min = 1000000000;
    int64_t v = -1;
    for (int j = 1; j <= n; j++) {
      if (used[j] == 0 && dist[j] < min) {
        min = dist[j];
        v = j;
      }
    }
    if (v < 0) {
      break;
    }
    for (int j = 1; j <= n; j++) {
      if (used[j] == 0 && graph.adjacency_list_[v][j] != -1) {
        Relax(v, j, dist, graph);
      }
    }
    used[v] = 1;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Graph graph;
  graph.adjacency_list_.resize(n + 1);
  int start = 0;
  int end = 0;
  std::cin >> start >> end;
  for (size_t i = 1; i < graph.adjacency_list_.size(); i++) {
    graph.adjacency_list_[i].resize(n + 1, -1);
  }
  std::vector<int64_t> used(n + 1, 0);
  std::vector<int64_t> dist(n + 1, 1000000000);
  dist[start] = 0;
  for (int i = 1; i < n + 1; i++) {
    for (int j = 1; j < n + 1; j++) {
      int value = 0;
      std::cin >> value;
      graph.adjacency_list_[i][j] = value;
    }
  }
  Dijkstra(n, dist, used, graph);
  if (dist[end] == 1000000000) {
    std::cout << -1;
  } else {
    std::cout << dist[end];
  }
}
