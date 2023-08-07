#ifndef UNIQUEPTR_UNIQUE_PTR_H
#define UNIQUEPTR_UNIQUE_PTR_H

#include <type_traits>

template <typename T, typename = void>
struct IsDereferenceable : std::false_type {};

template <typename T>
struct IsDereferenceable<T, std::void_t<decltype(*std::declval<T>())>> : std::true_type {};

template <typename T>
constexpr bool kIsDereferenceableV = IsDereferenceable<T>::value;

template <typename T, typename = void>
struct IsIncrementable : std::false_type {};

template <typename T>
struct IsIncrementable<T, std::void_t<decltype(std::declval<T&>()++)>> : std::true_type {};

template <typename T>
constexpr bool kIsIncrementableV = IsIncrementable<T>::value;

template <typename T, typename = void>
struct IsDecrementable : std::false_type {};

template <typename T>
struct IsDecrementable<T, std::void_t<decltype(std::declval<T&>()--)>> : std::true_type {};

template <typename T>
constexpr bool kIsDecrementableV = IsDecrementable<T&>::value;

template <typename T, typename = void>
struct IsArrowDereferenceable : std::false_type {};

template <typename T>
struct IsArrowDereferenceable<T, std::void_t<decltype(std::declval<T>().operator->())>> : std::true_type {};

template <typename T>
constexpr bool kIsArrowDereferenceableV = IsArrowDereferenceable<T>::value || std::is_pointer_v<T>;

template <typename T, typename = void>
struct IsEqualityComparable : std::false_type {};

template <typename T>
struct IsEqualityComparable<T, std::void_t<decltype(std::declval<const T&>() == std::declval<const T&>())>>
    : std::bool_constant<std::is_convertible_v<decltype(std::declval<const T&>() == std::declval<const T&>()), bool>> {
};

template <typename T>
constexpr bool kIsEqualityComparableV = IsEqualityComparable<T>::value;

template <typename T, typename = void>
struct IsOrdered : std::false_type {};

template <typename T>
struct IsOrdered<T, std::void_t<decltype(std::declval<const T&>() < std::declval<const T&>())>>
    : std::bool_constant<std::is_convertible_v<decltype(std::declval<const T&>() < std::declval<const T&>()), bool>> {};

template <typename T>
constexpr bool kIsOrderedV = IsOrdered<T>::value;

template <typename T, typename = void>
struct IsSubtractable : std::false_type {};

template <typename T>
struct IsSubtractable<T, std::void_t<decltype(std::declval<const T&>() - std::declval<const T&>())>> : std::true_type {
};

template <typename T>
constexpr bool kIsSubtractableV = IsSubtractable<T>::value;

template <typename T>
using DifferenceType = decltype(std::declval<T>() - std::declval<T>());

template <typename T, typename = void>
struct HasIntegralArithmetic : std::false_type {};

template <typename T>
struct HasIntegralArithmetic<
    T, std::void_t<DifferenceType<T>, decltype(std::declval<T&>() += std::declval<DifferenceType<T>>()),
                   decltype(std::declval<T&>() -= std::declval<DifferenceType<T>>())>>
    : std::bool_constant<std::is_integral_v<DifferenceType<T>>> {};

template <typename T>
constexpr bool kHasIntegralArithmeticV = (HasIntegralArithmetic<T>::value);

template <typename T, typename = void>
struct IsSubscriptable : std::false_type {};

template <typename T>
struct IsSubscriptable<T, std::void_t<decltype(std::declval<T>()[std::declval<DifferenceType<T>>()])>>
    : std::bool_constant<std::is_integral_v<DifferenceType<T>>> {};

template <typename T>
constexpr bool kIsSubscriptableV = (IsSubscriptable<T>::value);

template <typename T>
constexpr bool kIsIteratorV = std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T> &&
                              std::is_destructible_v<T> && kIsDereferenceableV<T> && kIsIncrementableV<T>;

template <typename T>
constexpr bool kIsInputIteratorV = kIsIteratorV<T> && kIsEqualityComparableV<T> && kIsArrowDereferenceableV<T>;

template <typename T>
constexpr bool kIsForwardIteratorV = kIsInputIteratorV<T> && std::is_default_constructible_v<T>;

template <typename T>
constexpr bool kIsBidirectionalIteratorV = kIsForwardIteratorV<T> && kIsDecrementableV<T>;

template <typename T>
constexpr bool kIsRandomAccessIteratorV = kIsBidirectionalIteratorV<T> && kIsSubscriptableV<T> &&
                                          kHasIntegralArithmeticV<T> && kIsSubscriptableV<T> && kIsOrderedV<T>;

#endif  //  UNIQUEPTR_UNIQUE_PTR_H
