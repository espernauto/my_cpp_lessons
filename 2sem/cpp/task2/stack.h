#ifndef SORT_H
#define SORT_H

#include <stdexcept>
#include <deque>

template <class T, typename Container = std::deque<T>>
class Stack {
 private:
  Container container_;

 public:
  Stack() {
    container_ = Container();
  }

  explicit Stack(const Container& container) : container_(container) {
  }

  template <typename InputIt>
  Stack(InputIt begin, InputIt end) {
    std::copy(begin, end, std::back_inserter(container_));
  }

  const T& Top() const {
    return container_.back();
  }

  T& Top() {
    return container_.back();
  }

  bool Empty() const {
    return container_.empty();
  }

  size_t Size() const {
    return container_.size();
  }

  void Push(T v) {
    container_.push_back(std::move(v));
  }

  template <typename... Args>
  void Emplace(Args&&... args) {
    container_.emplace_back(std::forward<Args>(args)...);
  }

  void Pop() {
    container_.pop_back();
  }

  void Swap(Stack& other) {
    container_.swap(other.container_);
  }
};

#endif
