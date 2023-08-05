#ifndef SORT_H
#define SORT_H

template <typename T>
void SiftUp(T* begin, int i) {
  while (*(begin + (i - 1) / 2) < *(begin + i)) {
    T tmp = *(begin + i);
    *(begin + i) = *(begin + (i - 1) / 2);
    *(begin + (i - 1) / 2) = tmp;
    i = (i - 1) / 2;
  }
}

template <typename T>
void SiftDown(T* begin, T* end, int i) {
  while (2 * i + 1 < end - begin) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int j = left;
    if ((right < end - begin)) {
      if (*(begin + left) < *(begin + right)) {
        j = right;
      }
    }
    if (*(begin + j) < *(begin + i)) {
      return;
    }
    T tmp = *(begin + i);
    *(begin + i) = *(begin + j);
    *(begin + j) = tmp;
    i = j;
  }
}

template <typename T>
void PushHeap(T* begin, T* end) {
  int size = end - begin;
  if (size > 0) {
    SiftUp(begin, size - 1);
  }
}

template <typename T>
void PopHeap(T* begin, T* end) {
  T c = *(begin);
  *(begin) = *(end - 1);
  *(end - 1) = c;
  SiftDown(begin, end - 1, 0);
}

#endif
