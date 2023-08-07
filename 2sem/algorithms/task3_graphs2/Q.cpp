#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int start_;
  int end_;
  int64_t capacity_;
  int64_t flow_;

  Edge(int a, int b, int64_t capacity, int64_t flow) : start_(a), end_(b), capacity_(capacity), flow_(flow) {
  }
};

class Graph {
 private:
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Push(int begin, int end, int64_t value) {
    adjacency_list_[begin].emplace_back(edges_.size());
    edges_.emplace_back(begin, end, value, 0);
    adjacency_list_[end].emplace_back(edges_.size());
    edges_.emplace_back(end, begin, 0, 0);
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  bool BFS(int n, int start, int end, std::vector<int>& dist) {
    int qh = 0;
    int qt = 0;
    std::vector<int> used(n, -1);
    used[qt++] = start;
    dist.clear();
    dist.resize(n, -1);
    dist[start] = 0;
    while (qh < qt && dist[end] == -1) {
      int v = used[qh++];
      for (size_t i = 0; i < adjacency_list_[v].size(); ++i) {
        int id = adjacency_list_[v][i];
        int to = edges_[id].end_;
        if (dist[to] == -1 && edges_[id].flow_ < edges_[id].capacity_) {
          used[qt++] = to;
          dist[to] = dist[v] + 1;
        }
      }
    }
    return dist[end] != -1;
  }

  int64_t DFS(int v, int64_t flow, int end, std::vector<int>& ptr, std::vector<int>& dist) {
    if (!flow) {
      return 0;
    }
    if (v == end) {
      return flow;
    }
    for (; static_cast<size_t>(ptr[v]) < adjacency_list_[v].size(); ++ptr[v]) {
      int id = adjacency_list_[v][ptr[v]];
      int to = edges_[id].end_;
      if (dist[to] != dist[v] + 1) {
        continue;
      }
      int64_t pushed = DFS(to, std::min(flow, edges_[id].capacity_ - edges_[id].flow_), end, ptr, dist);
      if (pushed) {
        edges_[id].flow_ += pushed;
        edges_[id ^ 1].flow_ -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  int64_t Dinic(int n, int start, int end) {
    int64_t inf = 1000000;
    std::vector<int> dist;
    int64_t flow = 0;
    for (;;) {
      if (!BFS(n, start, end, dist)) {
        break;
      }
      std::vector<int> ptr(n, 0);
      while (int64_t pushed = DFS(start, inf, end, ptr, dist)) {
        flow += pushed;
      }
    }
    return flow;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n);
  for (int i = 0; i < m; i++) {
    int begin = 0;
    int end = 0;
    int64_t value = 0;
    std::cin >> begin >> end >> value;
    graph.Push(begin - 1, end - 1, value);
  }
  std::cout << graph.Dinic(n, 0, n - 1);
}
