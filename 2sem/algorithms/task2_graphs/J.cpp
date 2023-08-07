#include <iostream>
#include <vector>

class Graph {
 public:
  std::vector<std::vector<int>> adjacency_list_;

  void DFS(std::vector<int>& used, std::vector<int>& path, int& v, int& flag) {
    used[v] = 1;
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      int to = adjacency_list_[v][i];
      if (used[to] == 1) {
        flag = 1;
      }
      if (used[to] == 0) {
        DFS(used, path, to, flag);
      }
    }
    used[v] = 2;
    path.emplace_back(v);
  }

  void Resize(int n) {
    adjacency_list_.resize(n + 1);
  }

  void Push(int begin, int end) {
    adjacency_list_[begin].emplace_back(end);
  }
};

void TopSort(Graph& graph, std::vector<int>& used, std::vector<int>& path, int& flag, int n) {
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      graph.DFS(used, path, i, flag);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n);
  std::vector<int> used(n + 1, 0);
  std::vector<int> path;
  for (int i = 0; i < m; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.Push(k, l);
  }
  int flag = 0;
  TopSort(graph, used, path, flag, n);
  if (flag == 1) {
    std::cout << -1;
  } else {
    for (auto i = static_cast<int>(path.size() - 1); i >= 0; i--) {
      std::cout << path[i] << ' ';
    }
  }
}
