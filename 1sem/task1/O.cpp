#ifndef SORT_H
#define SORT_H

template <typename F>
bool BinarySearch(const F *l, const F *r, const F &x) {
  if (l + 1 < r && r + 1 < l) {
    return 0;
  }
  if (x < *l) {
    return 0;
  }
  while (l + 1 < r) {
    const F *m = l + (r - l) / 2;
    if (x < *m) {
      r = m;
    } else {
      l = m;
    }
  }
  if (*l < x) {
    return 0;
  }
  return 1;
}

template <typename F>
const F *LowerBound(const F *l, const F *r, const F &x) {
  if (*(r - 1) < x) {
    return r;
  }
  if (x < *l) {
    return l;
  }
  if (l + 1 < r && r + 1 < l) {
    return r;
  }
  while (l + 1 < r) {
    const F *m = l + (r - l) / 2;
    if (x < *m) {
      r = m;
    } else {
      l = m;
    }
  }
  if (*l < x) {
    return r;
  }
  return l;
}

template <typename F>
const F *UpperBound(const F *l, const F *r, const F &x) {
  if (*(r - 1) < x) {
    return r;
  }
  if (x < *l) {
    return l;
  }
  if (l + 1 < r && r + 1 < l) {
    return r;
  }
  while (l + 1 < r) {
    const F *m = l + (r - l) / 2;
    if (x < *m) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

#endif
