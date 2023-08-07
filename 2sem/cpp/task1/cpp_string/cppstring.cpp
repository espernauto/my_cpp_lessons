#include <stdexcept>
#include "cppstring.h"
#include <iostream>

String::String() {
  str_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

String::String(const char* str1) {  // NOLINT
  Reserve(strlen(str1) + 1);
  std::strncpy(str_, str1, strlen(str1));
  size_ = strlen(str1);
  capacity_ = size_;
}

String::String(size_t size, char symbol) {
  if (size > 0) {
    Reserve(size);
    for (size_t i = 0; i < size; i++) {
      str_[i] = symbol;
    }
    size_ = size;
    capacity_ = size_;
  } else {
    size_ = 0;
    str_ = nullptr;
    capacity_ = 0;
  }
}

String::String(const char* str1, size_t size) {
  if (size > 0) {
    Reserve(size);
    strncpy(str_, str1, size);
    size_ = size;
    capacity_ = size_;
  } else {
    size_ = 0;
    str_ = nullptr;
    capacity_ = 0;
  }
}

String::String(const String& str1) {
  if (str1.Size() > 0) {
    Reserve(str1.Size());
    capacity_ = str1.Capacity();
    size_ = str1.Size();
    strncpy(str_, str1.str_, size_);
  } else {
    size_ = 0;
    str_ = nullptr;
    capacity_ = 0;
  }
}

const char& String::operator[](size_t i) const {
  return *(str_ + i);
}

char& String::operator[](size_t i) {
  return *(str_ + i);
}

const char& String::At(size_t idx) const {
  if (idx >= size_) {
    throw StringOutOfRange();
  }
  return str_[idx];
}

char& String::At(size_t idx) {
  if (idx >= size_) {
    throw StringOutOfRange();
  }
  return str_[idx];
}

const char* String::Data() const {
  return str_;
}

const char* String::CStr() const {
  return str_;
}

char* String::CStr() {
  return str_;
}

const char& String::Front() const {
  return *str_;
}

const char& String::Back() const {
  if (size_ > 0) {
    return *(str_ + size_ - 1);
  }
  return *str_;
}

char& String::Front() {
  return *str_;
}

char& String::Back() {
  if (size_ > 0) {
    return *(str_ + size_ - 1);
  }
  return *str_;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

bool String::Empty() const {
  return (size_ == 0);
}

void String::Swap(String& other) {
  std::swap(str_, other.str_);
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  size_--;
}

void String::Resize(size_t new_size, char symbol) {
  if (new_size > capacity_) {
    Reserve(new_size);
    if (size_ < new_size) {
      for (size_t i = size_; i < new_size; ++i) {
        str_[i] = symbol;
      }
    }
    if (new_size > capacity_) {
      capacity_ = new_size;
    }
    size_ = new_size;
  } else {
    size_ = new_size;
  }
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }
  auto* new_memory = new char[new_capacity];
  for (size_t i = 0; i < size_; ++i) {
    new_memory[i] = str_[i];
  }
  capacity_ = new_capacity;
  delete[] str_;
  str_ = new_memory;
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    auto* new_str = new char[size_];
    for (size_t i = 0; (i < size_ && i < size_); ++i) {
      new_str[i] = this->At(i);
    }
    delete[] str_;
    str_ = new_str;
    capacity_ = size_;
  }
}

void String::PushBack(char l) {
  if (size_ == capacity_) {
    Reserve(std::max<size_t>(capacity_ * 2, 1));
  }
  str_[size_] = l;
  ++size_;
}

void String::Clear() {
  this->size_ = 0;
}

String operator+(const String& a, const String& other) {
  String c;
  c += a;
  c += other;
  return c;
}

String& String::operator+=(const String& other) {
  if (size_ + other.size_ >= capacity_) {
    Reserve(std::max<size_t>((size_ + other.size_) * 2, 1));
  }
  for (size_t i = 0; i < other.size_; i++, size_++) {
    str_[size_] = other.str_[i];
  }
  return *this;
}

bool operator<(const String& a, const String& other) {
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

bool operator<=(const String& a, const String& other) {
  return !(other < a);
}

bool operator>(const String& a, const String& other) {
  return other < a;
}

bool operator>=(const String& a, const String& other) {
  return other <= a;
}

bool operator==(const String& a, const String& other) {
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

bool operator!=(const String& a, const String& other) {
  return !(a == other);
}

std::ostream& operator<<(std::ostream& out, const String& a) {
  for (size_t i = 0; i < a.Size(); i++) {
    out << a[i];
  }
  return out;
}

String& String::operator=(const String& other) {
  if (this == &other) {
    return *this;
  }
  if (other.str_ != nullptr) {
    String tmp = String(other);
    this->Swap(tmp);
    return *this;
  }
  delete[] str_;
  size_ = 0;
  str_ = nullptr;
  capacity_ = 0;
  return *this;
}
