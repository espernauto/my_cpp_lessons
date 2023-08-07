#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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
  void BFS(int start, std::vector<int> &dist, std::vector<int> &parent) {
    std::queue<int> queue;
    queue.push(start);
    dist[start] = 0;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (auto u : adjacency_list_[v]) {
        if (dist[u] == -1) {
          queue.push(u);
          dist[u] = dist[v] + 1;
          parent[u] = v;
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
  int start, end;
  std::cin >> start >> end;
  for (int i = 0; i < m; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.Push(k, l);
    graph.Push(l, k);
  }
  std::vector<int> dist;
  dist.resize(n + 1, -1);
  std::vector<int> parent;
  parent.resize(n + 1, -1);
  graph.BFS(start, dist, parent);
  if (dist[end] == -1) {
    std::cout << -1;
  } else {
    std::cout << dist[end] << '\n';
    std::vector<int> path(1, end);
    while (parent[end] != -1) {
      end = parent[end];
      path.push_back(end);
    }
    for (int i = path.size() - 1; i >= 0; i--) {
      std::cout << path[i] << ' ';
    }
    std::cout << '\n';
  }
}
