#ifndef SORT_H
#define SORT_H

template <typename F>
void Sort(F *a, F *b) {
  if (a < b - 1) {
    F *i = a;
    F *j = b - 1;
    F *m = a + (b - a) / 2;
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
    if (a < j) {
      Sort(a, j + 1);
    }
    if (j < b) {
      Sort(j + 1, b);
    }
  }
}

#endif
