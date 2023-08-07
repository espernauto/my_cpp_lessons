#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Graph {
 public:
  std::vector<std::vector<int>> adjacency_list_;
};

void DFS(const Graph& graph, std::vector<int64_t>& used, std::vector<int64_t>& time_in, std::vector<int64_t>& time_up,
         int64_t& timer, std::set<int64_t>& our_points, int64_t v, int64_t p = -1) {
  used[v] = 1;
  time_in[v] = time_up[v] = timer++;
  int children = 0;
  for (size_t i = 0; i < graph.adjacency_list_[v].size(); i++) {
    int to = graph.adjacency_list_[v][i];
    if (used[to] == 1) {
      time_up[v] = std::min(time_up[v], time_in[to]);
    }
    if (used[to] == 0) {
      ++children;
      DFS(graph, used, time_in, time_up, timer, our_points, to, v);
      time_up[v] = std::min(time_up[v], time_up[to]);
      if (time_up[to] >= time_in[v] && p != -1) {
        our_points.insert(v);
      }
    }
  }
  if (p == -1 && children > 1) {
    our_points.insert(v);
  }
  used[v] = 2;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.adjacency_list_.resize(n + 1);
  std::vector<int64_t> used(n + 1, 0);
  std::vector<int64_t> time_in(n + 1, 0);
  std::vector<int64_t> time_up(n + 1, 0);
  int64_t timer = 0;
  std::set<int64_t> our_points;
  for (int i = 0; i < m; i++) {
    int64_t k, l;
    std::cin >> k >> l;
    graph.adjacency_list_[k].emplace_back(l);
    graph.adjacency_list_[l].emplace_back(k);
  }
  for (int i = 0; i < n + 1; i++) {
    if (used[i] == 0) {
      DFS(graph, used, time_in, time_up, timer, our_points, i);
    }
  }
  std::cout << our_points.size() << '\n';
  for (auto it = our_points.begin(); it != our_points.end(); it++) {
    std::cout << (*it) << '\n';
  }
}
