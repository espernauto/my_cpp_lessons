#ifndef SORT_H
#define SORT_H

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T, size_t Siz>
struct Array {
  T array[Siz];

  T& operator[](int i) {
    return *(array + i);
  };

  const T& operator[](int i) const {
    return *(array + i);
  };

  T& At(size_t idx) {
    if (idx >= Siz || idx < 0) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  const T& At(size_t idx) const {
    if (idx >= Siz || idx < 0) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  T* Data() {
    return array;
  }

  const T* Data() const {
    return array;
  }

  T& Front() {
    return *array;
  }

  const T& Front() const {
    return *array;
  }

  T& Back() {
    if (Siz > 0) {
      return *(array + Siz - 1);
    }
    return *array;
  }

  const T& Back() const {
    if (Siz > 0) {
      return *(array + Siz - 1);
    }
    return *array;
  }

  size_t Size() const {
    return Siz;
  }

  bool Empty() const {
    return (Siz == 0);
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < Siz; i++) {
      array[i] = value;
    }
  }

  void Swap(Array<T, Siz>& other) {
    for (size_t i = 0; i < Siz; i++) {
      T tmp = other[i];
      other[i] = array[i];
      array[i] = tmp;
    }
  }
};
#endif
