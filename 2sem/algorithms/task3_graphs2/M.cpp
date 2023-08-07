#include <iostream>
#include <vector>
#include <algorithm>

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Push(int begin, int end, int value) {
    adjacency_list_[begin][end] = value;
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
    for (int i = 0; i < n; i++) {
      adjacency_list_[i].resize(n);
    }
  }

  void FloydWarshall(int n) {
    int inf = 101;
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (adjacency_list_[i][k] < inf && adjacency_list_[k][j] < inf) {
            adjacency_list_[i][j] = std::min(adjacency_list_[i][j], adjacency_list_[i][k] + adjacency_list_[k][j]);
          }
        }
      }
    }
  }

  void Print(int i, int j) {
    std::cout << adjacency_list_[i][j] << ' ';
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph;
  graph.Resize(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int value = 0;
      std::cin >> value;
      if (value < 100000 && value > -100000) {
        graph.Push(i, j, value);
      }
    }
  }
  std::vector<std::vector<int>> ways;
  ways.resize(n);
  for (int i = 0; i < n; i++) {
    ways[i].resize(0);
  }
  graph.FloydWarshall(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      graph.Print(i, j);
    }
    std::cout << '\n';
  }
}
