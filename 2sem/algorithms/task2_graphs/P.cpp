#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Graph {
 public:
  std::vector<std::vector<std::pair<int, int>>> adjacency_list_;
};

bool NotDouble(const std::vector<std::pair<int, int>> &vector, int v, int i) {
  for (size_t j = 0; j < vector.size(); j++) {
    if (vector[j].first == v && vector[j].second != i) {
      return false;
    }
  }
  return true;
}

void DFS(const Graph &graph, std::vector<int> &used, std::vector<int> &time_in, std::vector<int> &time_up, int &timer,
         std::set<int> &our_bridges, int &v, int &p) {
  used[v] = 1;
  time_in[v] = time_up[v] = timer++;
  for (size_t i = 0; i < graph.adjacency_list_[v].size(); i++) {
    int to = graph.adjacency_list_[v][i].first;
    if (to == p) {
      continue;
    }
    if (used[to] == 1) {
      time_up[v] = std::min(time_up[v], time_in[to]);
    }
    if (used[to] == 0) {
      DFS(graph, used, time_in, time_up, timer, our_bridges, to, v);
      time_up[v] = std::min(time_up[v], time_up[to]);
      if (time_up[to] > time_in[v] &&
          NotDouble(graph.adjacency_list_[v], graph.adjacency_list_[v][i].first, graph.adjacency_list_[v][i].second)) {
        our_bridges.insert(graph.adjacency_list_[v][i].second);
      }
    }
  }
  used[v] = 2;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.adjacency_list_.resize(n + 1);
  std::vector<int> used(n + 1, 0);
  std::vector<int> time_in(n + 1, 0);
  std::vector<int> time_up(n + 1, 0);
  int timer = 0;
  int p = -1;
  std::set<int> our_bridges;
  for (int i = 1; i < m + 1; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.adjacency_list_[k].emplace_back(std::make_pair(l, i));
    graph.adjacency_list_[l].emplace_back(std::make_pair(k, i));
  }
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      DFS(graph, used, time_in, time_up, timer, our_bridges, i, p);
    }
  }
  std::cout << our_bridges.size() << '\n';
  for (auto it = our_bridges.begin(); it != our_bridges.end(); it++) {
    std::cout << *it << '\n';
  }
}
