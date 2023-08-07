#include <iostream>
#include <queue>

void Check(std::queue<int>& queue, std::vector<std::vector<int>>& matrix, int y, int x, int n, int m, int first,
           int second) {
  if (0 <= x && x < m && 0 <= y && y < n && matrix[y][x] < 0) {
    matrix[y][x] = matrix[first][second] + 1;
    queue.push(y);
    queue.push(x);
  }
}

void DeWayDoSubuganda(std::queue<int>& queue, std::vector<std::vector<int>>& matrix, int n, int m) {
  int first, second;
  while (!queue.empty()) {
    first = queue.front();
    queue.pop();
    second = queue.front();
    queue.pop();
    Check(queue, matrix, first - 1, second, n, m, first, second);
    Check(queue, matrix, first + 1, second, n, m, first, second);
    Check(queue, matrix, first, second - 1, n, m, first, second);
    Check(queue, matrix, first, second + 1, n, m, first, second);
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::queue<int> queue;
  std::vector<std::vector<int>> matrix;
  matrix.resize(n);
  for (int i = 0; i < n; i++) {
    matrix[i].resize(m);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> matrix[i][j];
      if (matrix[i][j]--) {
        queue.push(i);
        queue.push(j);
      }
    }
  }
  DeWayDoSubuganda(queue, matrix, n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
}
