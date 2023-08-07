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

struct Edges {
  int begin_ = 0;
  int end_ = 0;
  int value_ = 0;
  Edges() = default;
  Edges(int begin, int end, int value) : begin_(begin), end_(end), value_(value) {
  }
};

bool Cmp(Edges first, Edges second) {
  return first.value_ < second.value_;
}

class Graph {
 private:
  std::vector<Edges> adjacency_list_;

 public:
  void Push(int begin, int end, int value) {
    adjacency_list_.emplace_back(begin, end, value);
  }

  void Sort() {
    std::sort(adjacency_list_.begin(), adjacency_list_.end(), Cmp);
  }

  void Kruskal(int m, std::vector<int64_t>& p, std::vector<int>& res, int n) {
    int cost = 0;
    std::vector<int64_t> rank(n + 1);
    std::sort(adjacency_list_.begin(), adjacency_list_.end(), Cmp);
    for (int node = 0; node < n; node++) {
      p[node] = node;
      rank[node] = 0;
    }
    for (int i = 0; i < m; ++i) {
      int a = adjacency_list_[i].begin_;
      int b = adjacency_list_[i].end_;
      int l = adjacency_list_[i].value_;
      if (DSUGet(a, p) != DSUGet(b, p)) {
        cost += l;
        res.push_back(adjacency_list_[i].value_);
        DSUUnite(p, rank, a, b);
      }
    }
    std::cout << cost;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<int64_t> p(n + 1);
  int m = 0;
  std::cin >> m;
  Graph graph;
  int start = 0;
  int end = 0;
  int value = 0;
  for (int i = 0; i < m; i++) {
    std::cin >> start >> end >> value;
    graph.Push(start, end, value);
  }
  std::vector<int> res;
  p.resize(n);
  graph.Kruskal(m, p, res, n);
}
