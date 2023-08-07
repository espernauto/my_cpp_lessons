#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>

class Graph {
 public:
  std::vector<std::vector<std::pair<int, int>>> adjacency_list_;
};

void BFS(Graph &graph, int start, std::vector<int> &dist, std::vector<int> &used) {
  std::vector<std::queue<int>> verticles_list;
  int k = 30;
  verticles_list.resize(k + 1);
  verticles_list[0].push(start);
  dist[start] = 0;
  int pos = 0, number = 1;
  while (number > 0) {
    while (verticles_list[pos % (k + 1)].empty()) {
      ++pos;
    }
    int u = verticles_list[pos % (k + 1)].front();
    verticles_list[pos % (k + 1)].pop();
    --number;
    if (used[u]) {
      continue;
    }
    used[u] = 1;
    for (auto edge : graph.adjacency_list_[u]) {
      int w = edge.first, cost = edge.second;
      if (dist[u] + cost < dist[w]) {
        dist[w] = dist[u] + cost;
        verticles_list[dist[w] % (k + 1)].push(w);
        ++number;
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  int start, end;
  std::cin >> start >> end;
  Graph graph;
  graph.adjacency_list_.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int k, l, value;
    std::cin >> k >> l >> value;
    if (k != l) {
      graph.adjacency_list_[k].emplace_back(l, value);
    }
  }
  int64_t inf = 1000000000;
  std::vector<int> dist;
  std::vector<int> used(n + 1, 0);
  dist.resize(n + 1, inf);
  BFS(graph, start, dist, used);
  if (dist[end] == inf) {
    std::cout << -1 << '\n';
  } else {
    std::cout << dist[end] << '\n';
  }
}
