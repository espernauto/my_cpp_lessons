#include <iostream>

template <typename F>
int64_t Merge(F* array, F* end, F* l, F* r, F* l_end, F* r_end, int64_t count) {
  int64_t size = end - array;
  int64_t l_size = l_end - l;
  int64_t r_size = r_end - r;
  int64_t l_index = 0;
  int64_t r_index = 0;
  int64_t i = 0;
  auto* temp_array = new F[size];
  while (l_index < l_size && r_index < r_size) {
    if (l[l_index] <= r[r_index]) {
      temp_array[i++] = l[l_index++];
    } else {
      temp_array[i++] = r[r_index++];
      count += l_size - l_index;
    }
  }
  while (l_index < l_size) {
    temp_array[i++] = l[l_index++];
  }
  while (r_index < r_size) {
    temp_array[i++] = r[r_index++];
  }
  for (int64_t i = 0; i < size; i++) {
    array[i] = temp_array[i];
  }
  delete[] temp_array;
  return count;
}

template <typename F>
int64_t MergeSort(F* array, F* end, int64_t count) {
  int64_t size = end - array;
  if (size <= 1) {
    return count;
  }
  int64_t m = size / 2;
  int64_t l_size = m;
  int64_t r_size = size - m;
  F* l = array;
  F* r = array + l_size;
  count = MergeSort(l, array + l_size, count);
  count = MergeSort(r, r + r_size, count);
  count += Merge(array, array + size, l, r, l + l_size, r + r_size, 0);
  return count;
}

int main() {
  int64_t n;
  std::cin >> n;
  int64_t count = 0;
  auto* a = new uint64_t[n];
  for (int64_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cout << MergeSort(a, a + n, count) << '\n';
  delete[] a;
}
