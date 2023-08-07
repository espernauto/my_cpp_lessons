#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;
  std::vector<std::vector<int64_t>> capacity_;

 public:
  void Push(int begin, int end, int64_t value) {
    adjacency_list_[begin].emplace_back(end);
    adjacency_list_[end].emplace_back(begin);
    capacity_[begin][end] = value;
    if (!capacity_[end][begin]) {
      capacity_[end][begin] = 0;
    }
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
    capacity_.resize(n);
    for (int i = 0; i < n; i++) {
      capacity_[i].resize(n, -1);
    }
  }

  int64_t EdmondsKarp(int start, int n, std::vector<int>& used) {
    std::queue<std::pair<int, int64_t>> queue;
    int64_t inf = 1000000000001;
    std::fill(used.begin(), used.end(), -1);
    used[0] = 0;
    queue.push(std::make_pair(start, inf));
    while (!queue.empty()) {
      int current = queue.front().first;
      int64_t flow = queue.front().second;
      queue.pop();
      for (auto next : adjacency_list_[current]) {
        if (used[next] == -1 && capacity_[current][next] > 0) {
          used[next] = current;
          int64_t new_flow = std::min(flow, capacity_[current][next]);
          if (next == n - 1) {
            return new_flow;
          }
          queue.push({next, new_flow});
        }
      }
    }
    return 0;
  }

  int64_t MaxFlow(int s, int n, std::vector<int>& used) {
    int64_t flow = 0;
    int64_t new_flow = EdmondsKarp(s, n, used);
    while (new_flow > 0) {
      flow += new_flow;
      int cur = n - 1;
      while (cur != s) {
        int prev = used[cur];
        capacity_[prev][cur] -= new_flow;
        capacity_[cur][prev] += new_flow;
        cur = prev;
      }
      new_flow = EdmondsKarp(s, n, used);
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
  std::vector<int> used(n, -1);
  std::cout << graph.MaxFlow(0, n, used);
}
