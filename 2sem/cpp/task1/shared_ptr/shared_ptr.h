#ifndef UNIQUEPTR_UNIQUE_PTR_H
#define UNIQUEPTR_UNIQUE_PTR_H

#define WEAK_PTR_IMPLEMENTED

#include <algorithm>
#include <stdexcept>

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class WeakPtr;

struct Counter {
  size_t strong_counter;
  size_t weak_counter;
};

template <class T>
class SharedPtr {
 public:
  T *ptr_ = nullptr;
  Counter *counter_;

  SharedPtr() {
    ptr_ = nullptr;
    counter_ = nullptr;
  }

  explicit SharedPtr(T *ptr) {
    ptr_ = ptr;
    if (ptr_) {
      counter_ = new Counter;
      counter_->strong_counter = 1;
      counter_->weak_counter = 0;
    } else {
      counter_ = nullptr;
    }
  }

  SharedPtr(std::nullptr_t ptr) {  // NOLINT
    ptr_ = ptr;
    counter_ = nullptr;
  }

  SharedPtr(const SharedPtr &ptr) {
    if (ptr) {
      ptr_ = ptr.ptr_;
      counter_ = ptr.counter_;
      counter_->strong_counter++;
    } else {
      counter_ = nullptr;
    }
  }

  SharedPtr(const WeakPtr<T> &ptr) {  // NOLINT
    if (ptr.Expired()) {
      throw BadWeakPtr();
    }
    ptr_ = ptr.ptr_;
    if (ptr.counter_) {
      counter_ = ptr.counter_;
      counter_->strong_counter += 1;
    } else {
      counter_ = nullptr;
    }
  }

  SharedPtr &operator=(const SharedPtr &other) {
    SharedPtr tmp(other);
    Swap(tmp);
    return *this;
  }

  SharedPtr(SharedPtr &&other) noexcept : ptr_(nullptr), counter_(nullptr) {
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (ptr_ != other.ptr_) {
      SharedPtr temp(std::move(other));
      Swap(temp);
    }
    return *this;
  }

  void Delete() {
    if (ptr_) {
      --(counter_->strong_counter);
      if ((counter_->strong_counter == 0) && (counter_->weak_counter == 0)) {
        delete ptr_;
        delete counter_;
      } else if (counter_->strong_counter == 0) {
        delete ptr_;
      }
    }
  }

  ~SharedPtr() {
    Delete();
    ptr_ = nullptr;
    counter_ = nullptr;
  }

  void Reset(T *other_ptr = nullptr) {
    Delete();
    ptr_ = other_ptr;
    if (ptr_) {
      counter_ = new Counter{1, 0};
    } else {
      counter_ = nullptr;
    }
  }

  void Swap(SharedPtr &other) {
    if (ptr_ != other.ptr_) {
      std::swap(ptr_, other.ptr_);
      std::swap(counter_, other.counter_);
    }
  }

  T *Get() {
    return ptr_;
  }

  T *Get() const {
    return ptr_;
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  size_t UseCount() const {
    if (this->counter_) {
      return counter_->strong_counter;
    }
    return 0;
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }
};

template <class T>
class WeakPtr {
 public:
  T *ptr_ = nullptr;
  Counter *counter_;

  WeakPtr() {
    ptr_ = nullptr;
    counter_ = nullptr;
  }

  explicit WeakPtr(T *ptr) {
    ptr_ = ptr;
    if (ptr) {
      counter_ = new Counter;
      counter_->weak_counter = 1;
      counter_->strong_counter = 0;
    } else {
      counter_ = nullptr;
    }
  }

  WeakPtr(std::nullptr_t ptr) {  // NOLINT
    ptr_ = ptr;
    counter_ = nullptr;
  }

  WeakPtr(const WeakPtr &ptr) {
    if (ptr) {
      ptr_ = ptr.ptr_;
      counter_ = ptr.counter_;
      counter_->weak_counter++;
    } else {
      counter_ = nullptr;
    }
  }

  WeakPtr(const SharedPtr<T> &ptr) {  // NOLINT
    if (ptr) {
      ptr_ = ptr.ptr_;
      counter_ = ptr.counter_;
      counter_->weak_counter++;
    } else {
      counter_ = nullptr;
    }
  }

  WeakPtr &operator=(const WeakPtr &other) {
    WeakPtr tmp(other);
    Swap(tmp);
    return *this;
  }

  WeakPtr(WeakPtr &&other) noexcept : ptr_(nullptr), counter_(nullptr) {
    ptr_ = other.ptr_;
    counter_ = other.counter_;
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  WeakPtr &operator=(WeakPtr &&other) noexcept {
    if (ptr_ != other.ptr_) {
      WeakPtr temp(std::move(other));
      Swap(temp);
    }
    return *this;
  }

  ~WeakPtr() {
    if (counter_) {
      --(counter_->weak_counter);
      if ((counter_->strong_counter == 0) && (counter_->weak_counter == 0)) {
        delete counter_;
      }
    }
    ptr_ = nullptr;
    counter_ = nullptr;
  }

  void Reset() {
    if (counter_) {
      --(counter_->weak_counter);
    }
    ptr_ = nullptr;
    counter_ = nullptr;
  }

  void Swap(WeakPtr &other) {
    if (ptr_ != other.ptr_) {
      std::swap(ptr_, other.ptr_);
      std::swap(counter_, other.counter_);
    }
  }

  size_t UseCount() const {
    if (this->counter_) {
      return counter_->strong_counter;
    }
    return 0;
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }

  bool Expired() const {
    return UseCount() == 0;
  }

  SharedPtr<T> Lock() const {
    if (this->Expired()) {
      return nullptr;
    }
    return SharedPtr<T>(*this);
  }
};

#endif  //  UNIQUEPTR_UNIQUE_PTR_H
