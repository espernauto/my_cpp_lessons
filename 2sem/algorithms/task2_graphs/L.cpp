#include <iostream>
#include <vector>
#include <algorithm>

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

  void DFS1(std::vector<int>& used, std::vector<int>& order, int v) {
    used[v] = 1;
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      if (!used[adjacency_list_[v][i]]) {
        DFS1(used, order, adjacency_list_[v][i]);
      }
    }
    order.emplace_back(v);
  }

  void DFS2(std::vector<int>& used, std::vector<std::pair<int, int>>& component, int v, int count) {
    used[v] = 1;
    component.emplace_back(std::make_pair(v, count));
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      if (!used[adjacency_list_[v][i]]) {
        DFS2(used, component, adjacency_list_[v][i], count);
      }
    }
  }
};

void TopSort(Graph& graph, std::vector<int>& used, std::vector<int>& order, int n) {
  for (int i = 1; i < n + 1; i++) {
    if (!used[i]) {
      graph.DFS1(used, order, i);
    }
  }
  used.clear();
  used.resize(n + 1, 0);
}

void Condensation(Graph& graph_transposed, std::vector<int>& used, std::vector<std::pair<int, int>>& component,
                  std::vector<int>& order, int n, int& count) {
  for (int i = 0; i < n; i++) {
    int v = order[n - i - 1];
    if (!used[v]) {
      count++;
      graph_transposed.DFS2(used, component, v, count);
    }
  }
  std::sort(component.begin(), component.end());
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  Graph graph_transposed;
  graph.Resize(n + 1);
  graph_transposed.Resize(n + 1);
  std::vector<int> used(n + 1, 0);
  std::vector<int> order;
  std::vector<std::pair<int, int>> component;
  int count = 0;
  for (int i = 0; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    graph.Push(a, b);
    graph_transposed.Push(b, a);
  }
  TopSort(graph, used, order, n);
  Condensation(graph_transposed, used, component, order, n, count);
  std::cout << count << '\n';
  for (size_t i = 0; i < component.size(); i++) {
    std::cout << component[i].second << ' ';
  }
}
