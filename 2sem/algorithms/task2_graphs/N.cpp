#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct Pair {
  int vertex_;
  int number_;

  Pair() {
    vertex_ = 0;
    number_ = 0;
  }

  Pair(int vertex, int number) : vertex_(vertex), number_(number) {
  }
};

class Graph {
 private:
  std::vector<std::vector<Pair>> adjacency_list_;

 public:
  void Push(int begin, int end, int i) {
    adjacency_list_[begin].emplace_back(Pair(end, i));
  }

  void Resize(int n) {
    adjacency_list_.resize(n + 1);
  }

  bool NotDouble(const std::vector<Pair>& vector, int v, int i) {
    for (size_t j = 0; j < vector.size(); j++) {
      if (vector[j].vertex_ == v && vector[j].number_ != i) {
        return false;
      }
    }
    return true;
  }

  void DFS(std::vector<int>& used, std::vector<int>& time_in, std::vector<int>& time_up, int& timer,
           std::set<int>& our_bridges, int& v, int& p) {
    used[v] = 1;
    time_in[v] = time_up[v] = timer++;
    for (size_t i = 0; i < adjacency_list_[v].size(); i++) {
      int to = adjacency_list_[v][i].vertex_;
      if (to == p) {
        continue;
      }
      if (used[to] == 1) {
        time_up[v] = std::min(time_up[v], time_in[to]);
      }
      if (used[to] == 0) {
        DFS(used, time_in, time_up, timer, our_bridges, to, v);
        time_up[v] = std::min(time_up[v], time_up[to]);
        if (time_up[to] > time_in[v] &&
            NotDouble(adjacency_list_[v], adjacency_list_[v][i].vertex_, adjacency_list_[v][i].number_)) {
          our_bridges.insert(adjacency_list_[v][i].number_);
        }
      }
    }
    used[v] = 2;
  }
};

void FindBridges(Graph& graph, std::vector<int>& used, std::vector<int>& time_in, std::vector<int>& time_up,
                 std::set<int>& our_bridges, int n) {
  int timer = 0;
  int p = -1;
  for (int i = 1; i < n + 1; i++) {
    if (used[i] == 0) {
      graph.DFS(used, time_in, time_up, timer, our_bridges, i, p);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph graph;
  graph.Resize(n + 1);
  std::vector<int> used(n + 1, 0);
  std::vector<int> time_in(n + 1, 0);
  std::vector<int> time_up(n + 1, 0);
  std::set<int> our_bridges;
  for (int i = 1; i < m + 1; i++) {
    int k, l;
    std::cin >> k >> l;
    graph.Push(k, l, i);
    graph.Push(l, k, i);
  }
  FindBridges(graph, used, time_in, time_up, our_bridges, n);
  std::cout << our_bridges.size() << '\n';
  for (auto it = our_bridges.begin(); it != our_bridges.end(); it++) {
    std::cout << *it << '\n';
  }
}
