#ifndef UNIQUEPTR_UNIQUE_PTR_H
#define UNIQUEPTR_UNIQUE_PTR_H

#include <algorithm>

template <class T>
class UniquePtr {
 private:
  T* ptr_ = nullptr;

 public:
  UniquePtr() = default;

  explicit UniquePtr(T* ptr) {
    if (ptr) {
      delete ptr_;
      ptr_ = ptr;
    }
  }

  UniquePtr(const UniquePtr& ptr) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (ptr_ != other.ptr_) {
      UniquePtr temp(std::move(other));
      Swap(temp);
    }
    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
    ptr_ = nullptr;
  }

  T* Release() {
    T* tmp;
    if (ptr_) {
      tmp = ptr_;
    } else {
      tmp = nullptr;
    }
    ptr_ = nullptr;
    return tmp;
  }

  void Reset(T* ptr = nullptr) {
    if (!ptr) {
      delete ptr_;
      ptr_ = nullptr;
    } else {
      delete ptr_;
      ptr_ = ptr;
    }
  }

  void Swap(UniquePtr& other) {
    std::swap(ptr_, other.ptr_);
  }

  T* Get() {
    return ptr_;
  }

  T* Get() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }
};

#endif  // UNIQUEPTR_UNIQUE_PTR_H
