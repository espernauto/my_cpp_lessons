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

class Graph {
 private:
  std::vector<Edges> adjacency_list_;

 public:
  void Push(int begin, int end, int value) {
    adjacency_list_.emplace_back(begin, end, value);
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  bool Check(int m, std::vector<int64_t>& p, std::vector<int64_t>& rank) {
    int a = adjacency_list_[m].begin_;
    int b = adjacency_list_[m].end_;
    if (DSUGet(a, p) != DSUGet(b, p)) {
      DSUUnite(p, rank, a, b);
      return false;
    }
    return true;
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
  int start = 0;
  int end = 0;
  int result = 0;
  std::vector<int64_t> p(n);
  std::vector<int64_t> rank(n);
  for (int j = 0; j < n; ++j) {
    p[j] = j;
    rank[j] = 0;
  }
  for (int i = 0; i < m; i++) {
    std::cin >> start >> end;
    graph.Push(start, end, 1);
    if (!graph.Check(i, p, rank)) {
      result = i + 1;
    }
  }
  if (result == 0) {
    result = m;
  }
  std::cout << result;
}
