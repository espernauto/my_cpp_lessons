#include <iostream>

bool Check(int i, int j, int k, int* board) {
  if (k == i) {
    return true;
  }
  return board[k] != j && (i - k) != (j - board[k]) && (i - k) != (board[k] - j) && Check(i, j, k + 1, board);
}

int Put(int n, int i, int j, int* board) {
  if (i == n) {
    return 1;
  }
  if (j < n) {
    int r = 0;
    if (Check(i, j, 0, board)) {
      board[i] = j;
      r = Put(n, i + 1, 0, board);
    }
    return r + Put(n, i, j + 1, board);
  }
  return 0;
}

int main() {
  int n;
  std::cin >> n;
  auto* board = new int[n];
  for (int i = 0; i < n; i++) {
    board[i] = 0;
  }
  std::cout << Put(n, 0, 0, board);
  delete[] board;
}
