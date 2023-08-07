#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

class Graph {
 public:
  std::vector<std::vector<std::pair<int, int>>> adjacency_list_;
};

void BFS(Graph& graph, int start, std::vector<int>& dist) {
  std::deque<int> deque;
  deque.push_front(start);
  dist[start] = 0;
  while (!deque.empty()) {
    int v = deque.front();
    deque.pop_front();
    for (auto u : graph.adjacency_list_[v]) {
      if (dist[v] + u.second < dist[u.first]) {
        if (u.second == 0) {
          deque.push_front(u.first);
        } else {
          deque.push_back(u.first);
        }
        dist[u.first] = dist[v] + u.second;
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.adjacency_list_.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int k, l;
    std::cin >> k >> l;
    if (k != l) {
      graph.adjacency_list_[k].emplace_back(l, 0);
      graph.adjacency_list_[l].emplace_back(k, 1);
    }
  }
  int64_t k;
  std::cin >> k;
  int64_t inf = 1000000000;
  for (int i = 0; i < k; i++) {
    int start, end;
    std::cin >> start >> end;
    std::vector<int> dist;
    dist.resize(n + 1, inf);
    BFS(graph, start, dist);
    if (dist[end] == inf) {
      std::cout << -1 << '\n';
    } else {
      std::cout << dist[end] << '\n';
    }
  }
}
