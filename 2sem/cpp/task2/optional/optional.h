#ifndef UNTITLED3_OPTIONAL_H
#define UNTITLED3_OPTIONAL_H

#include <stdexcept>

class BadOptionalAccess : public std::runtime_error {
 public:
  BadOptionalAccess() : std::runtime_error("BadOptionalAccess") {
  }
};

template <typename T>
class Optional {
  bool has_value_ = false;
  alignas(T) char data_[sizeof(T)];

 public:
  Optional() noexcept = default;

  ~Optional() {
    if (has_value_) {
      Value().~T();
      has_value_ = false;
    }
  }

  Optional(const Optional &other) {
    if (other.has_value_) {
      new (data_) T(other.Value());
      has_value_ = true;
    } else {
      *this = Optional();
    }
  }

  Optional(Optional &&other) noexcept {
    if (other.has_value_) {
      new (data_) T(std::move(other.Value()));
      has_value_ = true;
    } else {
      *this = Optional();
    }
  }

  Optional(const T &value) {  // NOLINT
    new (data_) T(value);
    has_value_ = true;
  }

  Optional(T &&value) noexcept {  // NOLINT
    new (data_) T(std::move(value));
    has_value_ = true;
  }

  Optional &operator=(const Optional &other) {
    if (this == &other) {
      return *this;
    }
    if (!other.has_value_) {
      if (!has_value_) {
        return *this;
      }
      Value().~T();
      has_value_ = false;
    }
    Optional tmp(other);
    Swap(tmp);
    return *this;
  }

  Optional &operator=(Optional &&other) noexcept {
    if (this == &other) {
      return *this;
    }
    if (!other.has_value_) {
      if (!has_value_) {
        return *this;
      }
    }
    if (has_value_) {
      Value().~T();
      has_value_ = false;
    }
    Optional tmp(std::move(other));
    Swap(tmp);
    return *this;
  }

  Optional &operator=(const T &other) {
    if (has_value_) {
      Value().~T();
      has_value_ = false;
    }
    *this = Optional(other);
    return *this;
  }

  Optional &operator=(T &&other) noexcept {
    if (has_value_) {
      Value().~T();
      has_value_ = false;
    }
    *this = Optional(std::move(other));
    return *this;
  }

  void Swap(Optional &other) {
    if (has_value_ && other.has_value_) {
      std::swap(Value(), other.Value());
      return;
    }
    if (!has_value_ && !other.has_value_) {
      return;
    }
    if (has_value_ && !other.has_value_) {
      new (other.data_) T(std::move(Value()));
      Value().~T();
      std::swap(has_value_, other.has_value_);
      return;
    }
    other.Swap(*this);
  }

  T &Value() {
    if (!has_value_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<T *>(data_);
  }

  const T &Value() const {
    if (!has_value_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<const T *>(data_);
  }

  bool HasValue() const {
    return has_value_;
  }

  void Reset() {
    if (has_value_) {
      Value().~T();
      has_value_ = false;
    }
  }

  const T &operator*() const {
    return *reinterpret_cast<const T *>(data_);
  }

  T &operator*() {
    return *reinterpret_cast<T *>(data_);
  }

  explicit operator bool() const {
    return has_value_;
  }

  template <typename... Args>
  void Emplace(Args &&... args) {
    if (has_value_) {
      Value().~T();
    }
    ::new (&data_) T(std::forward<Args>(args)...);
    has_value_ = true;
  }
};

#endif
