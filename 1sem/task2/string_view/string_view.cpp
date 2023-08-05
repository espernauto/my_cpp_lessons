#include <stdexcept>
#include "string_view.h"

const char& StringView::operator[](int i) const {
  return *(str_ + i);
}

const char& StringView::At(size_t idx) const {
  size_t size = end_ - str_;
  if (idx >= size) {
    throw StringViewOutOfRange();
  }
  return str_[idx];
}

const char* StringView::Data() const {
  return str_;
}

const char& StringView::Front() const {
  return *str_;
}

const char& StringView::Back() const {
  size_t size = end_ - str_;
  if (size > 0) {
    return *(str_ + size - 1);
  }
  return *str_;
}

size_t StringView::Size() const {
  size_t size = end_ - str_;
  return size;
}

size_t StringView::Length() const {
  size_t size = end_ - str_;
  return size;
}

bool StringView::Empty() const {
  size_t size = end_ - str_;
  return (size == 0);
}

void StringView::Swap(StringView& other) {
  std::swap(*this, other);
}

StringView StringView::RemovePrefix(size_t prefix_size) {
  str_ = str_ + prefix_size;
  return str_;
}

StringView StringView::RemoveSuffix(size_t suffix_size) {
  end_ = end_ - suffix_size;
  return str_;
}

StringView StringView::Substr(size_t pos, size_t count) {
  size_t size = end_ - str_;
  if (pos > size) {
    throw StringViewOutOfRange();
  }
  if (count < Size() - pos) {
    return StringView(str_ + pos, count);
  }
  return StringView(str_ + pos, Size() - pos);
}
