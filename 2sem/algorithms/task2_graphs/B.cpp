#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Push(int begin, int end) {
    adjacency_list_[begin][end] = 1;
    adjacency_list_[end][begin] = 1;
  }

  void Resize(int n) {
    adjacency_list_.resize(n + 1);
    for (size_t i = 1; i < adjacency_list_.size(); i++) {
      adjacency_list_[i].resize(n + 1, 0);
    }
  }

  void DFS(std::vector<int> &used, int v, int color, int n, int &possible) {
    if (possible) {
      return;
    }
    used[v] = color;
    for (int i = 1; i <= n; i++) {
      if (adjacency_list_[v][i]) {
        if (!used[i]) {
          DFS(used, i, 3 - color, n, possible);
        } else {
          if (used[v] == used[i]) {
            possible = 1;
          }
        }
      }
    }
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n + 1);
  std::vector<int> used(n + 1);
  for (int i = 0; i < m; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.Push(k, l);
  }
  int possible = 0;
  for (int i = 1; i <= n; i++) {
    if (!used[i]) {
      graph.DFS(used, i, 1, n, possible);
    }
  }
  if (possible == 0) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
}
