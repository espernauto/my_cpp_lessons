#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Graph {
 public:
  std::vector<std::vector<int64_t>> adjacency_list_;
};

void DFS(const Graph& graph, std::vector<int64_t>& used, std::vector<int64_t>& time_in, std::vector<int64_t>& time_up,
         int64_t& timer, std::set<int64_t>& our_points, int64_t v, int n, int64_t p = -1) {
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
      DFS(graph, used, time_in, time_up, timer, our_points, to, n, v);
      time_up[v] = std::min(time_up[v], time_up[to]);
      if (time_up[to] >= time_in[v] && p != -1) {
        if (v > n) {
          our_points.insert(v);
        }
      }
    }
  }
  if (p == -1 && children > 1) {
    if (v > n) {
      our_points.insert(v);
    }
  }
  used[v] = 2;
}

int main() {
  int64_t n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.adjacency_list_.resize(n + 1 + m);
  std::vector<int64_t> used(n + 1 + m, 0);
  std::vector<int64_t> time_in(n + 1 + m, 0);
  std::vector<int64_t> time_up(n + 1 + m, 0);
  int64_t timer = 0;
  std::set<int64_t> our_points;
  for (int64_t i = 1; i < m + 1; i++) {
    int64_t first, second, third;
    std::cin >> first >> second >> third;
    graph.adjacency_list_[i + n].emplace_back(first);
    graph.adjacency_list_[i + n].emplace_back(second);
    graph.adjacency_list_[i + n].emplace_back(third);
    graph.adjacency_list_[first].emplace_back(i + n);
    graph.adjacency_list_[second].emplace_back(i + n);
    graph.adjacency_list_[third].emplace_back(i + n);
  }
  for (int64_t i = n + 1; i < n + m + 1; i++) {
    if (used[i] == 0) {
      DFS(graph, used, time_in, time_up, timer, our_points, i, n);
    }
  }
  std::cout << our_points.size() << '\n';
  for (auto it = our_points.begin(); it != our_points.end(); it++) {
    std::cout << (*it) - n << '\n';
  }
}
