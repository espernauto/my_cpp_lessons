#include <iostream>

int main() {
  int counter_lines = 0;
  int counter_columns = 0;
  int lines = 0;
  int columns = 0;
  int line_gap = 0;
  int column_gap = 0;
  int first_line = 0;
  int first_column = 0;
  int n, m;
  std::cin >> n >> m;
  auto** a = new char*[n];
  for (int i = 0; i < n; i++) {
    a[i] = new char[m];
  }
  for (int i = 0; i < n; ++i) {
    char l[1000] = "";
    if (m > 0) {
      std::cin >> l;
    }
    for (int j = 0; j < m; j++) {
      a[i][j] = l[j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int s = a[i][j];
      if (s == 49) {
        counter_lines += 1;
      }
    }
    if (m > 1) {
      if (counter_lines == m) {
        if (lines == 0) {
          first_line = i;
        }
        if (lines == 1) {
          line_gap = i - first_line;
        }
        lines += 1;
      }
    }
    counter_lines = 0;
  }

  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      int s = a[i][j];
      if (s == 49) {
        counter_columns += 1;
      }
    }
    if (n > 1) {
      if (counter_columns == n) {
        if (columns == 0) {
          first_column = j;
        }
        if (columns == 1) {
          column_gap = j - first_column;
        }
        columns += 1;
      }
    }
    counter_columns = 0;
  }
  if (lines > 0 && columns > 0) {
    std::cout << "Square";
  } else if (lines > 1 && (line_gap) <= m) {
    std::cout << "Line";
  } else if (columns > 1 && (column_gap) <= n) {
    std::cout << "Vertical line";
  } else {
    std::cout << "?";
  }
  for (int i = 0; i < n; ++i) {
    delete[] a[i];
  }
  delete[] a;
}
