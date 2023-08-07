#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Push(int begin, int end) {
    adjacency_list_[begin].emplace_back(end);
  }

  void Resize(int n) {
    adjacency_list_.resize(n + 1);
  }

  void DFS(std::vector<int>& used, std::vector<int>& path, int& v, int& flag) {
    if (flag == 1) {
      return;
    }
    used[v] = 1;
    path.emplace_back(v);
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      int to = adjacency_list_[v][i];
      if (used[to] == 1) {
        path.emplace_back(to);
        flag = 1;
        return;
      }
      if (used[to] == 0) {
        DFS(used, path, to, flag);
      }
      if (flag == 1) {
        return;
      }
    }
    used[v] = 2;
    path.pop_back();
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n + 1);
  std::vector<int> used(n + 1, 0);
  std::vector<int> path;
  for (int i = 0; i < m; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.Push(k, l);
  }
  int flag = 0;
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      graph.DFS(used, path, i, flag);
      if (flag == 1) {
        break;
      }
    }
  }
  if (flag == 1) {
    int to = path.back();
    size_t i = path.size() - 2;
    while (path[i] != to) {
      i--;
    }
    std::cout << "YES\n";
    for (; i < path.size() - 1; i++) {
      std::cout << path[i] << ' ';
    }
  } else {
    std::cout << "NO";
  }
}
