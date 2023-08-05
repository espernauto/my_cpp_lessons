#ifndef SORT_H
#define SORT_H

template <typename T>
void Heapify(T* begin, T* end, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int n = end - begin;
  if (l < n && (*(begin + largest) < *(begin + l))) {
    largest = l;
  }
  if (r < n && (*(begin + largest) < *(begin + r))) {
    largest = r;
  }
  if (largest != i) {
    T tmp = *(begin + i);
    *(begin + i) = *(begin + largest);
    *(begin + largest) = tmp;
    Heapify(begin, end, largest);
  }
}

template <typename T>
void MakeHeap(T* begin, T* end) {
  int n = end - begin;
  for (int i = n / 2 - 1; i >= 0; i--) {
    Heapify(begin, end, i);
  }
}

template <typename T>
void SortHeap(T* begin, T* end) {
  MakeHeap(begin, end);
  int n = end - begin;
  for (int i = n - 1; i >= 0; i--) {
    T tmp = *(begin + i);
    *(begin + i) = *begin;
    *begin = tmp;
    Heapify(begin, begin + i, 0);
  }
}
#endif
