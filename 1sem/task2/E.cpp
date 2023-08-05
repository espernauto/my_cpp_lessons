#include <iostream>
#include <algorithm>

template <typename T>
T SiftUp(T* begin, int i) {
  while (*(begin + i) > *(begin + (i - 1) / 2)) {
    T tmp = *(begin + i);
    *(begin + i) = *(begin + (i - 1) / 2);
    *(begin + (i - 1) / 2) = tmp;
    i = (i - 1) / 2;
  }
  return i + 1;
}

template <typename T>
T SiftDown(T* begin, T* end, int i) {
  while (2 * i + 1 < end - begin) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int j = left;
    if ((right < end - begin)) {
      if (*(begin + right) > *(begin + left)) {
        j = right;
      }
    }
    if (*(begin + i) >= *(begin + j)) {
      return i + 1;
    }
    T tmp = *(begin + i);
    *(begin + i) = *(begin + j);
    *(begin + j) = tmp;
    i = j;
  }
  return i + 1;
}

template <typename T>
void Insert(T* begin, T* end, T value) {
  int size = end - begin;
  *end = value;
  if (size > 0) {
    std::cout << SiftUp(begin, size) << '\n';
  } else {
    std::cout << 1 << '\n';
  }
}

template <typename T>
T Delete(T* begin, T* end, int64_t num) {
  T size = end - begin;
  T c = *(begin + num);
  *(begin + num) = *(begin + size - 1);
  *(begin + size - 1) = c;
  if (size == 1) {
    return 0;
  }
  if ((num - 1) / 2 > 0) {
    int k = SiftUp(begin, num) - 1;
    return SiftDown(begin, end - 1, k);
  }
  return SiftDown(begin, end - 1, num);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  auto* queue = new int64_t[n];
  int type;
  int64_t value;
  int64_t size = 0;
  for (int i = 0; i < m; i++) {
    std::cin >> type;
    if (type == 1) {
      if (size == 0) {
        std::cout << -1 << '\n';
      } else {
        int64_t max = queue[0];
        std::cout << Delete(queue, queue + size, 0) << " ";
        std::cout << max << '\n';
        size--;
      }
    }
    if (type == 2) {
      std::cin >> value;
      if (size == n) {
        std::cout << -1 << '\n';
      } else {
        Insert(queue, queue + size, value);
        size++;
      }
    }
    if (type == 3) {
      std::cin >> value;
      if (value > size || value < 1) {
        std::cout << -1 << '\n';
      } else {
        std::cout << queue[value - 1] << '\n';
        Delete(queue, queue + size, value - 1);
        size--;
      }
    }
  }
  for (int i = 0; i < size; i++) {
    std::cout << queue[i] << " ";
  }
  delete[] queue;
}
