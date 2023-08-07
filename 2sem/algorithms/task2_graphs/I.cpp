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
};

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n + 1);
  std::vector<int> used(n + 1, 0);
  std::vector<int> path;
  std::vector<size_t> sizes;
  for (int i = 0; i < m; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.Push(k, l);
    graph.Push(l, k);
  }
  int flag = 0;
  int count = 0;
  size_t prev_size = 0;
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      graph.DFS(used, path, i, flag);
      count++;
      sizes.emplace_back(path.size() - prev_size);
      prev_size = path.size();
    }
  }
  std::cout << count << '\n';
  int j = 0;
  std::cout << sizes[0] << '\n';
  for (size_t i = 0; i < path.size(); i++) {
    if (sizes[j] == 0) {
      j++;
      std::cout << '\n' << sizes[j] << '\n';
    }
    sizes[j]--;
    std::cout << path[i] << ' ';
  }
}
