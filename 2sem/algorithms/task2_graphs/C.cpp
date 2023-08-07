#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<int>> adjacency_list_;

 public:
  void Push(int begin, int end) {
    adjacency_list_[begin].emplace_back(end);
  }

  void Resize(int n) {
    adjacency_list_.resize(n + 1);
  }

  void BFS(int start, std::vector<int> &dist, std::vector<int> &parent) {
    std::queue<int> queue;
    queue.push(start);
    dist[start] = 0;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (auto u : adjacency_list_[v]) {
        if (dist[u] == -1) {
          queue.push(u);
          dist[u] = dist[v] + 1;
          parent[u] = v;
        }
      }
    }
  }
};

int AddOne(int n) {
  if (n / 1000 != 9) {
    return n + 1000;
  }
  return n;
}

int MinusOne(int n) {
  if (n % 10 != 1) {
    return n - 1;
  }
  return n;
}

int ShiftLeft(int n) {
  return (n % 1000) * 10 + n / 1000;
}

int ShiftRight(int n) {
  return (n % 10) * 1000 + n / 10;
}

void Path(int n, std::vector<int> &prev, int counter) {
  if (n == -1) {
    std::cout << counter << '\n';
    return;
  }
  counter += 1;
  Path(prev[n], prev, counter);
  std::cout << n << '\n';
}

int main() {
  int start, end;
  std::cin >> start >> end;
  int n = 10000;
  Graph graph;
  graph.Resize(n);
  for (int i = 1000; i <= 10000; i++) {
    if (i % 1000 != 9 && AddOne(i) < 10000) {
      graph.Push(i, AddOne(i));
    }
    if (i % 1000 != 1 && MinusOne(i) > 999) {
      graph.Push(i, MinusOne(i));
    }
    if (ShiftLeft(i) > 999) {
      graph.Push(i, ShiftLeft(i));
    }
    if (ShiftRight(i) > 999) {
      graph.Push(i, ShiftRight(i));
    }
  }
  std::vector<int> dist;
  dist.resize(n + 1, -1);
  std::vector<int> parent;
  parent.resize(n + 1, -1);
  graph.BFS(start, dist, parent);
  if (dist[end] == -1) {
    std::cout << -1;
  } else {
    std::cout << dist[end] << '\n';
    std::vector<int> path(1, end);
    while (parent[end] != -1) {
      end = parent[end];
      path.push_back(end);
    }
    for (int i = path.size() - 1; i >= 0; i--) {
      std::cout << path[i] << ' ';
    }
    std::cout << '\n';
  }
}
