#ifndef SORT_H
#define SORT_H

#define VECTOR_MEMORY_IMPLEMENTED

#include <iostream>
#include <cstring>
#include <algorithm>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

template <typename T>
class Vector {
 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  T *data_ = nullptr;

  T *Allocate(size_t sz) {
    return static_cast<T *>(operator new(sz * sizeof(T)));
  }

  void Reallocate(size_t new_capacity) {
    T *new_data;
    if (new_capacity > 0) {
      new_data = Allocate(new_capacity);
      for (size_t i = 0; i < size_; ++i) {
        new (new_data + i) T(std::move(data_[i]));
      }
    } else {
      new_data = nullptr;
    }
    for (size_t i = 0; i < size_; ++i) {
      data_[i].~T();
    }
    operator delete(data_);
    data_ = new_data;
    capacity_ = new_capacity;
  }

 public:
  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;

  using Iterator = T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstIterator = const T *;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Iterator begin() noexcept;             //  NOLINT
  ConstIterator begin() const noexcept;  //  NOLINT

  ConstIterator cbegin() const noexcept;  //  NOLINT
  ConstIterator cend() const noexcept;    //  NOLINT

  Iterator end() noexcept;             //  NOLINT
  ConstIterator end() const noexcept;  //  NOLINT

  ReverseIterator rbegin() noexcept;             //  NOLINT
  ConstReverseIterator rbegin() const noexcept;  //  NOLINT

  ConstReverseIterator crbegin() const noexcept;  //  NOLINT
  ConstReverseIterator crend() const noexcept;    //  NOLINT

  ReverseIterator rend() noexcept;             //  NOLINT
  ConstReverseIterator rend() const noexcept;  //  NOLINT

  Vector() = default;

  Vector(std::initializer_list<T> list) : Vector(list.begin(), list.end()) {
  }

  explicit Vector(size_t new_size) {
    size_ = new_size;
    capacity_ = new_size;
    data_ = Allocate(new_size);
    size_t count = 0;
    try {
      for (size_t i = 0; i < size_; ++i) {
        new (data_ + i) T;
        ++count;
      }
    } catch (...) {
      for (size_t j = 0; j < count; ++j) {
        (data_ + j)->~T();
      }
      operator delete(data_);
      throw;
    }
  }

  Vector(size_t size, const T &el) {
    size_ = size;
    capacity_ = size;
    if (size > 0) {
      data_ = Allocate(size);
    } else {
      data_ = nullptr;
    }
    size_t count = 0;
    try {
      for (size_t i = 0; i < size_; ++i) {
        new (data_ + i) T(el);
        ++count;
      }
    } catch (...) {
      for (size_t j = 0; j < count; ++j) {
        (data_ + j)->~T();
      }
      operator delete(data_);
      throw;
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    size_ = std::distance(first, last);
    if (size_ > 0) {
      try {
        data_ = Allocate(size_);
        capacity_ = size_;
        std::uninitialized_copy(first, last, data_);
      } catch (...) {
        operator delete(data_);
        throw;
      }
    } else {
      data_ = nullptr;
      capacity_ = 0;
    }
  }

  Vector(const Vector &other) {
    if (other.size_ > 0) {
      data_ = Allocate(other.size_);
      try {
        std::uninitialized_copy(other.data_, other.data_ + other.size_, data_);
      } catch (...) {
        operator delete(data_);
        throw;
      }
      size_ = capacity_ = other.size_;
    } else {
      size_ = 0;
      data_ = nullptr;
      capacity_ = 0;
    }
  }

  Vector(Vector &&other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(std::move(other.data_)) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~Vector() {
    Reallocate(0);
    size_ = 0;
  }

  Vector &operator=(const Vector &other) {
    if (this == &other) {
      return *this;
    }
    if (other.data_ != nullptr) {
      Vector tmp = Vector(other);
      this->Swap(tmp);
      return *this;
    }
    for (size_t i = 0; i < size_; ++i) {
      (data_ + i)->~T();
    }
    size_ = 0;
    operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    for (size_t i = 0; i < size_; ++i) {
      (data_ + i)->~T();
    }
    operator delete(data_);
    data_ = std::move(other.data_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
    return *this;
  }

  void Reserve(SizeType new_capacity) {
    if (capacity_ < new_capacity) {
      auto new_data = Allocate(new_capacity);
      size_t count = 0;
      try {
        for (size_t i = 0; i < size_; ++i) {
          new (new_data + i) T(std::move_if_noexcept(data_[i]));
          ++count;
        }
      } catch (...) {
        for (size_t i = 0; i < count; ++i) {
          (new_data + i)->~T();
        }
        operator delete(new_data);
        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
      data_ = new_data;
      capacity_ = new_capacity;
    }
  }

  ConstReference operator[](SizeType i) const {
    return *(data_ + i);
  }

  Reference operator[](SizeType i) {
    return *(data_ + i);
  }

  ConstReference At(SizeType idx) const {
    if (idx >= size_) {
      throw StringOutOfRange();
    }
    return data_[idx];
  }

  Reference At(SizeType idx) {
    if (idx >= size_) {
      throw StringOutOfRange();
    }
    return data_[idx];
  }

  Pointer Data() {
    return data_;
  }

  ConstPointer Data() const {
    return data_;
  }

  ConstPointer CStr() const {
    return data_;
  }

  Pointer CStr() {
    return data_;
  }

  ConstReference Front() const {
    return *data_;
  }

  ConstReference Back() const {
    if (size_ > 0) {
      return *(data_ + size_ - 1);
    }
    return *data_;
  }

  Reference Front() {
    return *data_;
  }

  Reference Back() {
    if (size_ > 0) {
      return *(data_ + size_ - 1);
    }
    return *data_;
  }

  SizeType Size() const {
    return size_;
  }

  SizeType Length() const {
    return size_;
  }

  SizeType Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  void Swap(Vector &other) {
    std::swap(data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
  }

  void PopBack() {
    if (size_ == 0) {
      return;
    }
    (data_ + size_ - 1)->~T();
    size_--;
  }

  void PushBack(const T &el) {
    if (size_ == capacity_) {
      auto new_data = Allocate(std::max(static_cast<int>(capacity_) * 2, 1));
      size_t count = 0;
      try {
        for (size_t i = 0; i < size_; ++i) {
          new (new_data + i) T(std::move_if_noexcept(data_[i]));
          ++count;
        }
        new (new_data + size_) T(el);
        ++count;
      } catch (...) {
        for (size_t j = 0; j < count; ++j) {
          (new_data + j)->~T();
        }
        operator delete(new_data);
        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
      data_ = new_data;
      ++size_;
      if (capacity_ != 0) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
    } else {
      ++size_;
      try {
        new (data_ + size_ - 1) T(el);
      } catch (...) {
        (data_ + size_ - 1)->~T();
        --size_;
        throw;
      }
    }
  }

  void PushBack(T &&el) {
    size_t old_capacity = capacity_;
    try {
      if (size_ == capacity_) {
        Reserve(std::max<SizeType>(capacity_ * 2, 1));
      }
      new (data_ + size_) T(std::move_if_noexcept(el));
      ++size_;
    } catch (...) {
      Reallocate(old_capacity);
      --size_;
      throw;
    }
  }

  void Clear() {
    for (size_t i = 0; i < size_; ++i) {
      (data_ + i)->~T();
    }
    size_ = 0;
  }

  void Resize(const size_t &new_size) {
    size_t count = 0;
    if (new_size > capacity_) {
      auto new_data = Allocate(new_size);
      try {
        for (size_t i = 0; i < size_; ++i) {
          new (new_data + i) T(std::move_if_noexcept(data_[i]));
          ++count;
        }
        for (size_t i = size_; i < new_size; ++i) {
          new (new_data + i) T;
          ++count;
        }
      } catch (...) {
        for (size_t j = 0; j < count; ++j) {
          (new_data + j)->~T();
        }
        operator delete(new_data);
        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
      data_ = new_data;
      capacity_ = new_size;
    } else {
      if (size_ < new_size) {
        try {
          for (size_t i = size_; i < new_size; ++i) {
            new (data_ + i) T;
            ++count;
          }
        } catch (...) {
          for (size_t j = size_; j < size_ + count; ++j) {
            (data_ + j)->~T();
          }
          throw;
        }
      } else {
        for (size_t i = new_size; i < size_; ++i) {
          (data_ + i)->~T();
        }
      }
    }
    size_ = new_size;
  }

  void Resize(const size_t &new_size, const T &value) {
    size_t count = 0;
    if (new_size > capacity_) {
      auto new_data = Allocate(new_size);
      try {
        for (size_t i = 0; i < size_; ++i) {
          new (new_data + i) T(std::move_if_noexcept(data_[i]));
          ++count;
        }
        for (size_t i = size_; i < new_size; ++i) {
          new (new_data + i) T(value);
          ++count;
        }
      } catch (...) {
        for (size_t j = 0; j < count; ++j) {
          (new_data + j)->~T();
        }
        operator delete(new_data);
        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
      data_ = new_data;
      capacity_ = new_size;
    } else {
      if (size_ < new_size) {
        try {
          for (size_t i = size_; i < new_size; ++i) {
            new (data_ + i) T(value);
            ++count;
          }
        } catch (...) {
          for (size_t j = size_; j < size_ + count; ++j) {
            (data_ + j)->~T();
          }
          throw;
        }
      } else {
        for (size_t i = new_size; i < size_; ++i) {
          (data_ + i)->~T();
        }
      }
    }
    size_ = new_size;
  }

  void ShrinkToFit() {
    if (capacity_ > size_) {
      Reallocate(size_);
    }
  }

  Vector &operator+=(const Vector &other) {
    if (size_ + other.size_ >= capacity_) {
      Reserve(std::max<size_t>((size_ + other.size_) * 2, 1));
    }
    for (SizeType i = 0; i < other.size_; i++, size_++) {
      data_[size_] = other.data_[i];
    }
    return *this;
  }

  template <class... Args>
  void EmplaceBack(Args &&... args) {
    if (size_ == capacity_) {
      auto new_data = Allocate(std::max(static_cast<int>(capacity_) * 2, 1));
      size_t count = 0;
      try {
        for (size_t i = 0; i < size_; ++i) {
          new (new_data + i) T(std::move_if_noexcept(data_[i]));
          ++count;
        }
        new (new_data + size_) T(std::forward<Args>(args)...);
        ++count;
      } catch (...) {
        for (size_t j = 0; j < count; ++j) {
          (new_data + j)->~T();
        }
        operator delete(new_data);

        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
      data_ = new_data;
      ++size_;
      if (capacity_ != 0) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
    } else {
      ++size_;
      try {
        new (data_ + size_ - 1) T(std::forward<Args>(args)...);
      } catch (...) {
        (data_ + size_ - 1)->~T();
        --size_;
        throw;
      }
    }
  }
};

template <class T>
typename Vector<T>::Iterator Vector<T>::begin() noexcept {  //  NOLINT
  return data_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::begin() const noexcept {  //  NOLINT
  return data_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::cbegin() const noexcept {  //  NOLINT
  return data_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::cend() const noexcept {  //  NOLINT
  return data_ + size_;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::end() noexcept {  //  NOLINT
  return data_ + size_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::end() const noexcept {  //  NOLINT
  return data_ + size_;
}

template <class T>
typename Vector<T>::ReverseIterator Vector<T>::rbegin() noexcept {  //  NOLINT
  return std::reverse_iterator(this->end());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::rbegin() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->end());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::crbegin() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->cend());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::crend() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->cbegin());
}

template <class T>
typename Vector<T>::ReverseIterator Vector<T>::rend() noexcept {  //  NOLINT
  return std::reverse_iterator(this->begin());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::rend() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->begin());
}

template <typename T>
Vector<T> operator+(const Vector<T> &a, const Vector<T> &other) {
  Vector<T> c;
  c += a;
  c += other;
  return c;
}

template <typename T>
bool operator<(const Vector<T> &a, const Vector<T> &other) {
  for (size_t i = 0; i < std::min(a.Size(), other.Size()); i++) {
    if (a[i] < other[i]) {
      return a[i] < other[i];
    }
    if (a[i] > other[i]) {
      return a[i] < other[i];
    }
  }
  if (a.Size() < other.Size()) {
    return a.Size() < other.Size();
  }
  return false;
}

template <typename T>
bool operator<=(const Vector<T> &a, const Vector<T> &other) {
  return !(other < a);
}

template <typename T>
bool operator>(const Vector<T> &a, const Vector<T> &other) {
  return other < a;
}

template <typename T>
bool operator>=(const Vector<T> &a, const Vector<T> &other) {
  return other <= a;
}

template <typename T>
bool operator==(const Vector<T> &a, const Vector<T> &other) {
  for (size_t i = 0; i < std::min(a.Size(), other.Size()); i++) {
    if (a[i] != other[i]) {
      return a[i] == other[i];
    }
  }
  if (a.Size() != other.Size()) {
    return a.Size() == other.Size();
  }
  return true;
}

template <typename T>
bool operator!=(const Vector<T> &a, const Vector<T> &other) {
  return !(a == other);
}

#endif
