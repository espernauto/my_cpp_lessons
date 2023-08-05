#include <iostream>
#include <algorithm>

struct Count {
  uint64_t card;
  uint64_t number;
};

Count* Extra(uint64_t* a, int len) {
  uint64_t save = a[0];
  auto* new_a = new Count[len + 1];
  new_a[1].card = save;
  uint64_t j = 2;
  uint64_t count = 1;
  for (int i = 1; i < len; i++) {
    if (a[i] != save) {
      new_a[j - 1].number = count;
      new_a[j].card = a[i];
      count = 1;
      save = a[i];
      j++;
    } else {
      count += 1;
    }
  }
  new_a[j - 1].number = count;
  new_a[0].number = j;
  return new_a;
}

bool Cmp(uint64_t value, Count& a) {
  return (value < a.card);
}

bool Cmp2(Count& a, uint64_t value) {
  return (a.card < value);
}

int main() {
  uint64_t n;
  uint64_t k;
  std::cin >> n >> k;
  auto* list = new uint64_t[n];
  Count* weighted_list;
  uint64_t count = 0;
  for (uint64_t i = 0; i < n; i++) {
    std::cin >> list[i];
  }
  std::sort(list, list + n);
  weighted_list = Extra(list, n);
  uint64_t len = weighted_list[0].number;
  for (uint64_t i = 1; i < len; i++) {
    if (weighted_list[i].number >= 3) {
      count += 1;
    }
  }
  for (uint64_t i = 1; i < len; i++) {
    Count* end;
    end = std::upper_bound(weighted_list + i, weighted_list + len, k * weighted_list[i].card, Cmp);
    uint64_t j = end - i - weighted_list;
    uint64_t num = (j - 2) * (j - 1) * 3;
    count += num;
  }
  for (uint64_t i = 1; i < len; i++) {
    if (weighted_list[i].number >= 2) {
      Count* end;
      end = std::upper_bound(weighted_list + i, weighted_list + len, k * weighted_list[i].card, Cmp);
      uint64_t j = end - i - weighted_list;
      if (k == 1) {
        j = 1;
      }
      count += 3 * (j - 1);
    }
  }
  for (uint64_t i = 1; i < len; i++) {
    weighted_list[i].card = weighted_list[i].card * k;
  }
  for (uint64_t i = len - 1; i > 0; i--) {
    if (weighted_list[i].number >= 2) {
      Count* end;
      end = std::lower_bound(weighted_list + 1, weighted_list + i, weighted_list[i].card / k, Cmp2);
      uint64_t j = weighted_list + i - end;
      count += 3 * j;
    }
  }
  std::cout << count;
  delete[] list;
  delete[] weighted_list;
}
