#include <iostream>
#include <vector>
#include <algorithm>

int64_t DSUGet(int64_t v, std::vector<int64_t>& p) {
  return (v == p[v]) ? v : (p[v] = DSUGet(p[v], p));
}

void DSUUnite(std::vector<int64_t>& parent, std::vector<int64_t>& rank, int64_t x, int64_t y) {
  int64_t x_root = DSUGet(x, parent);
  int64_t y_root = DSUGet(y, parent);
  if (rank[x_root] < rank[y_root]) {
    parent[x_root] = y_root;
  } else if (rank[x_root] > rank[y_root]) {
    parent[y_root] = x_root;
  } else {
    parent[y_root] = x_root;
    rank[x_root]++;
  }
}

class Graph {
 private:
  std::vector<std::vector<int64_t>> adjacency_list_;

 public:
  void Push(int64_t begin, int64_t end, int64_t value) {
    adjacency_list_.emplace_back(std::vector{begin, end, value});
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  void Boruvka(int n) {
    std::vector<int64_t> parent(n + 1);
    std::vector<int64_t> rank(n + 1);
    std::vector<std::vector<int64_t>> cheapest(n + 1, std::vector<int64_t>(3, -1));
    int trees_number = n;
    int64_t weight = 0;
    for (int node = 0; node < n; node++) {
      parent[node] = node;
      rank[node] = 0;
    }
    while (trees_number > 1) {
      for (size_t i = 0; i < adjacency_list_.size(); i++) {
        int64_t u = adjacency_list_[i][0];
        int64_t v = adjacency_list_[i][1];
        int64_t w = adjacency_list_[i][2];
        int64_t set1 = DSUGet(u, parent);
        int64_t set2 = DSUGet(v, parent);
        if (set1 != set2) {
          if (cheapest[set1][2] == -1 || cheapest[set1][2] > w) {
            cheapest[set1] = {u, v, w};
          }
          if (cheapest[set2][2] == -1 || cheapest[set2][2] > w) {
            cheapest[set2] = {u, v, w};
          }
        }
      }
      for (int node = 0; node < n; node++) {
        if (cheapest[node][2] != -1) {
          int64_t u = cheapest[node][0];
          int64_t v = cheapest[node][1];
          int64_t w = cheapest[node][2];
          int64_t set1 = DSUGet(u, parent);
          int64_t set2 = DSUGet(v, parent);
          if (set1 != set2) {
            weight += w;
            DSUUnite(parent, rank, set1, set2);
            trees_number--;
          }
        }
      }
      for (int node = 0; node < n; node++) {
        cheapest[node][2] = -1;
      }
    }
    std::cout << weight;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  int m = 0;
  std::cin >> m;
  Graph graph;
  int64_t start = 0;
  int64_t end = 0;
  int64_t value = 0;
  for (int i = 0; i < m; i++) {
    std::cin >> start >> end >> value;
    graph.Push(start, end, value);
  }
  graph.Boruvka(n);
}
