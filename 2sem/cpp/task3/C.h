#ifndef UNTITLED3_OPTIONAL_H
#define UNTITLED3_OPTIONAL_H

#include <iostream>

template <class T>
struct IsArray;

template <class T>
inline const bool kIsArrayV = IsArray<T>::value;

template <class T>
struct IsArray : std::integral_constant<bool, false> {};

template <class T>
struct IsArray<T[]> : std::integral_constant<bool, true> {};

template <class T, std::size_t N>
struct IsArray<T[N]> : std::integral_constant<bool, true> {};

template <class T>
struct Rank;

template <class T>
inline const int kRankV = Rank<T>::value;

template <class T>
struct Rank : std::integral_constant<std::size_t, 0> {};

template <class T>
struct Rank<T[]> : std::integral_constant<std::size_t, kRankV<T> + 1> {};

template <class T, std::size_t N>
struct Rank<T[N]> : std::integral_constant<std::size_t, kRankV<T> + 1> {};

template <class T>
struct Size;

template <class T>
inline const int kSizeV = Size<T>::value;

template <class T>
struct Size : std::integral_constant<std::size_t, 1> {};

template <class T>
struct Size<T[]> : std::integral_constant<std::size_t, 0> {};

template <class T, size_t M>
struct Size<T[M]> : std::integral_constant<std::size_t, M> {};

template <class T>
struct TotalSize;

template <class T>
inline const int kTotalSizeV = TotalSize<T>::value;

template <class T>
struct TotalSize : std::integral_constant<std::size_t, 1> {};

template <class T>
struct TotalSize<T[]> : std::integral_constant<std::size_t, 0> {};

template <class T, std::size_t N>
struct TotalSize<T[N]> : std::integral_constant<std::size_t, kTotalSizeV<T> * N> {};

template <class T>
struct RemoveArray;

template <class T>
using RemoveArrayT = typename RemoveArray<T>::Type;

template <class T>
struct RemoveArray {
  using Type = T;
};

template <class T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <class T, std::size_t N>
struct RemoveArray<T[N]> {
  using Type = T;
};

template <class T>
struct RemoveAllArrays;

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;

template <class T>
struct RemoveAllArrays {
  using Type = T;
};

template <class T>
struct RemoveAllArrays<T[]> {
  using Type = typename RemoveAllArrays<T>::Type;
};

template <class T, std::size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = typename RemoveAllArrays<T>::Type;
};

#endif
