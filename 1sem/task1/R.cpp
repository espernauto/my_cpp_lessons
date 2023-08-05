#ifndef SORT_H
#define SORT_H

template <typename F>
F *Partition(F *i, F *j) {
  F *m = i + (j - 1 - i) / 2;
  if (j < i + 2) {
    m = i;
  }
  F mid = *m;
  while (i - 1 < j) {
    while (*i < mid) {
      i++;
    }
    while (mid < *j) {
      j--;
    }
    if (j - 1 < i) {
      break;
    }
    if (i - 1 < j) {
      F tmp = *i;
      *i = *j;
      *j = tmp;
      i++;
      j--;
    }
  }
  return j;
}

template <typename F>
void KthElement(F *begin, F *k, F *end) {
  F *left = begin;
  F *right = end - 1;
  while (true) {
    F *mid = Partition(left, right);
    if (mid == k) {
      F tmp = *mid;
      *mid = *k;
      *k = tmp;
      return;
    } else if (k < mid) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
}

#endif
