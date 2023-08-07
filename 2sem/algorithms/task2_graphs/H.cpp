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

  void DFS(std::vector<int>& used, int& v, int& flag) {
    if (flag == 1) {
      return;
    }
    used[v] = 1;
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      int to = adjacency_list_[v][i];
      if (used[to] == 1) {
        flag = 1;
        return;
      }
      if (used[to] == 0) {
        DFS(used, to, flag);
      }
      if (flag == 1) {
        return;
      }
    }
    used[v] = 2;
  }
};

int main() {
  int n;
  std::cin >> n;
  Graph graph;
  graph.Resize(n + 1);
  std::vector<int> used(n + 1, 0);
  for (int i = 1; i < n + 1; i++) {
    int k;
    std::cin >> k;
    graph.Push(k, i);
  }
  int flag = 0;
  int count = 0;
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      graph.DFS(used, i, flag);
      if (flag == 1) {
        count++;
        flag = 0;
      }
    }
  }
  std::cout << count;
}
