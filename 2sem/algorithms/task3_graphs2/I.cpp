#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  std::vector<std::vector<std::pair<int64_t, int64_t>>> adjacency_list_;

 public:
  void Push(int64_t begin, int64_t end, int64_t value) {
    adjacency_list_[begin].emplace_back(std::make_pair(end, value));
  }

  void Resize(int n) {
    adjacency_list_.resize(n);
  }

  void Dijkstra(std::vector<int64_t>& dist, std::vector<int64_t>& prev, int start) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.push(std::make_pair(0, start));
    while (!q.empty()) {
      int v = q.top().second;
      int cur_d = q.top().first;
      q.pop();
      if (cur_d > dist[v]) {
        continue;
      }
      for (auto i = adjacency_list_[v].begin(); i != adjacency_list_[v].end(); i++) {
        int64_t to = (*i).first;
        int64_t cost = (*i).second;
        if (dist[v] + cost < dist[to]) {
          dist[to] = dist[v] + cost;
          prev[to] = v;
          q.push(std::make_pair(dist[to], to));
        }
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int rooms_number = 0;
  std::cin >> rooms_number;
  for (int i = 0; i < rooms_number; i++) {
    int n = 0;
    std::cin >> n;
    int m = 0;
    std::cin >> m;
    Graph graph;
    graph.Resize(n);
    int start = 0;
    for (int k = 0; k < m; k++) {
      int begin = 0;
      int end = 0;
      int value = 0;
      std::cin >> begin >> end >> value;
      graph.Push(begin, end, value);
      graph.Push(end, begin, value);
    }
    std::cin >> start;
    int64_t inf = 2009000999;
    std::vector<int64_t> used(n, -1);
    std::vector<int64_t> dist(n, inf);
    dist[start] = 0;
    graph.Dijkstra(dist, used, start);
    for (int j = 0; j < n; j++) {
      if (dist[j] == inf) {
        std::cout << inf << ' ';
      } else {
        std::cout << dist[j] << ' ';
      }
    }
    std::cout << '\n';
  }
}
