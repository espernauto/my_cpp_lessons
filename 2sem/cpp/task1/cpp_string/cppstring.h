#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <cstring>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* str_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

 public:
  String();

  String(const char* str1);  // NOLINT

  String(size_t size, char symbol);

  String(const char* str1, size_t size);

  String(const String& str1);

  ~String() {
    delete[] str_;
  }

  String& operator=(const String& other);
  void Reserve(size_t);
  const char& operator[](size_t i) const;
  char& operator[](size_t i);
  const char& At(size_t idx) const;
  char& At(size_t idx);
  const char* Data() const;
  const char* CStr() const;
  char* CStr();
  const char& Front() const;
  const char& Back() const;
  char& Front();
  char& Back();
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  bool Empty() const;
  void Swap(String& other);
  void PopBack();
  void PushBack(char);
  void Clear();
  String Substr(size_t pos, size_t count = -1);
  void Resize(size_t, char);
  void ShrinkToFit();
  String& operator+=(const String& other);
  friend std::istream& operator>>(std::istream& in, String&);
};

String operator+(const String& a, const String& other);
bool operator>(const String& a, const String& other);
bool operator>=(const String& a, const String& other);
bool operator<(const String& a, const String& other);
bool operator<=(const String& a, const String& other);
bool operator==(const String& a, const String& other);
bool operator!=(const String& a, const String& other);
std::ostream& operator<<(std::ostream& out, const String& a);
#endif
