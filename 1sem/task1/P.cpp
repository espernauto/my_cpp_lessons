#ifndef MERGE_H
#define MERGE_H

template <typename F, typename S, typename T>
void Merge(const F* first_begin, const F* first_end, const S* second_begin, const S* second_end, T* out) {
  while (first_begin < first_end || second_begin < second_end) {
    if (first_end - 1 < first_begin) {
      *out = *second_begin;
      out++;
      second_begin++;
    } else if (second_end - 1 < second_begin) {
      *out = *first_begin;
      out++;
      first_begin++;
    } else if (*first_begin < *second_begin) {
      *out = *first_begin;
      out++;
      first_begin++;
    } else {
      *out = *second_begin;
      out++;
      second_begin++;
    }
  }
}

#endif
