#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Resize(int n) {
    adjacency_list_.resize(n + 1);
  }

  const std::vector<int> Vertex(int v) {
    std::vector<int> neighbors;
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      neighbors.emplace_back(adjacency_list_[v][i]);
    }
    return neighbors;
  }

  void AddVertex(int u, int v) {
    adjacency_list_[u].emplace_back(v);
    adjacency_list_[v].emplace_back(u);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, k;
  std::cin >> n >> k;
  Graph graph;
  graph.Resize(n);
  for (int i = 0; i < k; i++) {
    int command;
    std::cin >> command;
    if (command == 1) {
      int u, v;
      std::cin >> u >> v;
      graph.AddVertex(u, v);
    } else {
      int u;
      std::cin >> u;
      std::vector<int> vertex = graph.Vertex(u);
      for (size_t j = 0; j < vertex.size(); j++) {
        std::cout << vertex[j] << ' ';
      }
      std::cout << '\n';
    }
  }
}
