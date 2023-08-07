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
    for (int i = 1; i < n + 1; i++) {
      adjacency_list_[i].resize(n + 1, 0);
    }
  }

  void DFS(std::vector<int> &used, std::vector<int> &path, int &v, int &flag) {
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

void Check(Graph &graph, int n) {
  std::vector<int> used(n + 1, 0);
  std::vector<int> path;
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
    std::cout << "NO";
  } else {
    std::cout << "YES";
  }
}

int main() {
  int n;
  std::cin >> n;
  Graph graph;
  std::string line;
  graph.Resize(n + 1);
  for (int i = 1; i < n; i++) {
    std::cin >> line;
    for (size_t j = 0; j < line.size(); j++) {
      if (line[j] == 'R') {
        graph.Push(j + i + 1, i);
      } else {
        graph.Push(i, j + i + 1);
      }
    }
  }
  Check(graph, n);
}
