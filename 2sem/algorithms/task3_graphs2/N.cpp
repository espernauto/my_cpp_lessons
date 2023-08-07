#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  int v_;
  int flow_;
  int capacity_;

  Edge(int v, int capacity) : v_(v), flow_(0), capacity_(capacity) {
  }

  int GetCapacity() {
    return capacity_ - flow_;
  }
};

class Graph {
 private:
  std::vector<Edge> edges_;
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Push(int begin, int end, int value) {
    adjacency_list_[begin].emplace_back(edges_.size());
    edges_.emplace_back(end, value);
    adjacency_list_[end].emplace_back(edges_.size());
    edges_.emplace_back(begin, 0);
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  int FordFulkerson(int v, int n, int min_capacity, int timer, std::vector<int>& used) {
    if (v == n) {
      return min_capacity;
    }
    used[v] = timer;
    for (int index : adjacency_list_[v]) {
      if (edges_[index].GetCapacity() == 0) {
        continue;
      }
      if (used[edges_[index].v_] == timer) {
        continue;
      }
      int x = FordFulkerson(edges_[index].v_, n, std::min(min_capacity, edges_[index].GetCapacity()), timer, used);
      if (x) {
        edges_[index].flow_ += x;
        edges_[index ^ 1].flow_ -= x;
        return x;
      }
    }
    return 0;
  }

  void Print() {
    int result = 0;
    for (int index : adjacency_list_[1]) {
      result += edges_[index].flow_;
    }
    std::cout << result;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n + 1);
  int inf = 1000000;
  for (int i = 0; i < m; i++) {
    int begin = 0;
    int end = 0;
    int value = 0;
    std::cin >> begin >> end >> value;
    graph.Push(begin, end, value);
  }
  std::vector<int> used(n + 1, -1);
  int timer = 1;
  while (graph.FordFulkerson(1, n, inf, timer, used)) {
    ++timer;
  }
  graph.Print();
}
