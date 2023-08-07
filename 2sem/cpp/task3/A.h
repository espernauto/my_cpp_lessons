#ifndef UNTITLED3_OPTIONAL_H
#define UNTITLED3_OPTIONAL_H

#include <iostream>

template <typename It>
constexpr void Advance(It &it, typename std::iterator_traits<It>::difference_type n) {
  using Category = typename std::iterator_traits<It>::iterator_category;
  static_assert(std::is_base_of_v<std::input_iterator_tag, Category>);
  auto dist = static_cast<typename std::iterator_traits<It>::difference_type>(n);
  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, Category>) {
    it += dist;
  } else {
    while (dist > 0) {
      --dist;
      ++it;
    }
    if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, Category>) {
      while (dist < 0) {
        ++dist;
        --it;
      }
    }
  }
}

template <class It>
constexpr It Next(It it, typename std::iterator_traits<It>::difference_type n = 1) {
  Advance(it, n);
  return it;
}

template <class It>
constexpr It Prev(It it, typename std::iterator_traits<It>::difference_type n = 1) {
  Advance(it, -n);
  return it;
}

template <typename It>
typename std::iterator_traits<It>::difference_type Distance(It begin, It end) {
  using Type = typename std::iterator_traits<It>::iterator_category;
  if constexpr (std::is_base_of_v<std::random_access_iterator_tag, Type>) {
    return (end - begin);
  } else {
    typename std::iterator_traits<It>::difference_type res = 0;
    while (begin != end) {
      ++begin;
      ++res;
    }
    return res;
  }
}

#endif
