#ifndef SORT_H
#define SORT_H

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

struct StringView {
 private:
  const char* str_;
  const char* end_;

 public:
  StringView() {
    str_ = nullptr;
    end_ = str_;
  }
  StringView(const char* str1) {  // NOLINT
    str_ = str1;
    int i = 0;
    while (str_[i] != '\0') {
      i++;
    }
    end_ = str_ + i;
  }
  StringView(const char* str1, size_t siz) {
    str_ = str1;
    end_ = str_ + siz;
  }
  const char& operator[](int i) const;
  const char& At(size_t idx) const;
  const char* Data() const;
  const char& Front() const;
  const char& Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  void Swap(StringView& other);
  StringView RemovePrefix(size_t prefix_size);
  StringView RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1);
};
#endif
