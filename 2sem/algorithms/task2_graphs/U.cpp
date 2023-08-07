#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Graph {
 public:
  std::vector<std::pair<std::vector<int>, int>> adjacency_list_;
};

bool NotDouble(const std::vector<std::pair<int, int>>& vector, int v, int i) {
  for (size_t j = 0; j < vector.size(); j++) {
    if (vector[j].first == v && vector[j].second != i) {
      return false;
    }
  }
  return true;
}

void DFS(const Graph& graph, std::vector<int>& used, std::vector<int>& time_in, std::vector<int>& time_up, int& timer,
         int& our_bridges, int& v, int& p) {
  used[v] = 1;
  time_in[v] = time_up[v] = timer++;
  for (size_t i = 0; i < graph.adjacency_list_[v].first.size(); i++) {
    int to = graph.adjacency_list_[v].first[i];
    if (to == p) {
      continue;
    }
    if (used[to] == 1) {
      time_up[v] = std::min(time_up[v], time_in[to]);
    }
    if (used[to] == 0) {
      DFS(graph, used, time_in, time_up, timer, our_bridges, to, v);
      time_up[v] = std::min(time_up[v], time_up[to]);
      if (time_up[to] > time_in[v]) {
        our_bridges += 1;
      }
    }
  }
  used[v] = 2;
}

bool Check(Graph& graph, int n) {
  for (int i = 1; i < n + 1; i++) {
    if (graph.adjacency_list_[i].second == 1) {
      if (graph.adjacency_list_[i].first.size() != 4) {
        return false;
      }
    }
    if (graph.adjacency_list_[i].second == 0) {
      if (graph.adjacency_list_[i].first.size() != 1) {
        return false;
      }
      int neighbour = graph.adjacency_list_[i].first[0];
      if (graph.adjacency_list_[neighbour].second != 1) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.adjacency_list_.resize(n + 1);
  std::string molecule;
  std::cin >> molecule;
  for (int i = 0; i < n; i++) {
    if (molecule[i] == 'C') {
      graph.adjacency_list_[i + 1].second = 1;
    } else {
      graph.adjacency_list_[i + 1].second = 0;
    }
  }
  for (int i = 1; i < m + 1; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.adjacency_list_[k].first.emplace_back(l);
    graph.adjacency_list_[l].first.emplace_back(k);
  }
  std::vector<int> used(n + 1, 0);
  std::vector<int> time_in(n + 1, 0);
  std::vector<int> time_up(n + 1, 0);
  int timer = 0;
  int p = -1;
  int our_bridges = 0;
  int flag = 0;
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      DFS(graph, used, time_in, time_up, timer, our_bridges, i, p);
      if (i != 1) {
        flag = 1;
        break;
      }
    }
  }
  if (Check(graph, n) && our_bridges == m && flag == 0) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}
