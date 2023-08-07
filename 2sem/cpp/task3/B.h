#ifndef UNTITLED3_OPTIONAL_H
#define UNTITLED3_OPTIONAL_H

#include <iostream>

template <bool B, class T, class F>
struct Conditional {
  using Type = T;
};

template <class T, class F>
struct Conditional<false, T, F> {
  using Type = F;
};

template <bool B, class T, class F>
using ConditionalT = typename Conditional<B, T, F>::Type;

template <class...>
struct Disjunction : std::false_type {};

template <class B1>
struct Disjunction<B1> : B1 {};

template <class B1, class... Bn>
struct Disjunction<B1, Bn...> : ConditionalT<static_cast<bool>(B1::value), B1, Disjunction<Bn...>> {};

template <int64_t N, int64_t L, int64_t R, bool B>
struct Sqrt;

template <int64_t N, int64_t L = 0, int64_t R = N>
inline const int64_t kSqrtV = Sqrt<N, L, R, (((L + R + 2) / 2) > N / ((L + R + 2) / 2))>::value;

template <int64_t N, int64_t L, int64_t R, bool B>
struct Sqrt : std::integral_constant<int64_t, kSqrtV<N, L, ((L + R + 2) / 2) - 1>> {};

template <int64_t N, int64_t L, int64_t R>
struct Sqrt<N, L, R, false> : std::integral_constant<int64_t, kSqrtV<N, ((L + R + 2) / 2), R>> {};

template <int64_t N, int64_t L, bool B>
struct Sqrt<N, L, L, B> : std::integral_constant<int64_t, L> {};

template <int64_t N, int64_t L>
struct Sqrt<N, L, L, false> : std::integral_constant<int64_t, L> {};

template <int N, int L, int R>
struct HasDivisorOn;

template <int N, int L, int R>
inline const bool kHasDivisorOnV = HasDivisorOn<N, L, R>::value;

template <int N, int L, int R>
struct HasDivisorOn
    : std::integral_constant<bool,
                             Disjunction<HasDivisorOn<N, L, (L + R) / 2>, HasDivisorOn<N, (L + R) / 2 + 1, R>>::value> {
};

template <int N, int L>
struct HasDivisorOn<N, L, L> : std::integral_constant<bool, N % L == 0> {};

template <int N>
struct IsPrime;

template <int N>
inline const bool kIsPrimeV = IsPrime<N>::value;

template <int N>
struct IsPrime : std::integral_constant<bool, !kHasDivisorOnV<N, 2, kSqrtV<N> + 1>> {};

template <>
struct IsPrime<1> : std::integral_constant<bool, false> {};

template <>
struct IsPrime<2> : std::integral_constant<bool, true> {};

#endif
