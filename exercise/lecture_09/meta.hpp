#ifndef STATIC_VISITOR_META_HPP
#define STATIC_VISITOR_META_HPP

#include <cstddef>
#include <concepts>
#include <functional>
#include <string>

template <typename T>
struct is_bool : std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, bool> {};

template <typename T, typename = void>
struct is_number : std::false_type {};

template <typename T>
struct is_number<T, std::void_t<
        std::enable_if_t<std::is_arithmetic_v<std::remove_reference_t<std::remove_cv_t<T>>>>,
        std::enable_if_t<!std::is_same_v<std::remove_reference_t<std::remove_cv_t<T>>, bool>>
>> : std::true_type {};

template <typename T>
struct is_char : std::is_same<std::remove_cv_t<std::remove_reference_t<T>>, char> {};

template <typename T, typename = void>
struct is_string : std::false_type {};

//if it has a c_str as member it should be a string
template <typename T>
struct is_string<T, std::void_t<decltype(std::declval<std::decay_t<T>>().c_str())>> : std::true_type {};

//accessing element in list must be a char
template <typename T, std::size_t N>
struct is_string<T[N]> : std::is_same<std::decay_t<std::remove_const_t<T>>, char> {};

//handle the const and pointer stuff
template <typename T>
struct is_string<T*, std::enable_if_t<std::is_same_v<std::decay_t<std::remove_cv_t<T>>, char>>> : std::true_type {};


template <typename T, typename = void>
struct is_container : std::false_type {};

template <typename T>
struct is_container<T, std::void_t<
        decltype(std::declval<std::decay_t<T>>().begin())
        ,decltype(std::declval<std::decay_t<T>>().end())
        ,std::enable_if_t<!std::is_same_v<std::decay_t<T>, std::string>> //strings dont count
>> : std::true_type {};

//accessing element in list must be a possible
template <typename T, std::size_t N>
struct is_container<T[N]> : std::true_type {};


/**
 * TODO: implement meta-predicates
 * (template classes/variables taking type and returning bool)
 * is_container_v
 * accepts_v
 *
 * Tips:
 * - read documentation about std::is_same, std::is_integral, std::is_floating_point, std::is_arithmetic.
 * - make your meta-predicates robust against const/volatile/reference combinations (see meta_test.cpp):
 *   see std::remove_reference, std::remove_const, std::remove_cvref, std::decay
 */

template <typename T>
constexpr auto is_bool_v = is_bool<T>::value;

template <typename T>
constexpr auto is_number_v = is_number<T>::value;
template <typename T>

constexpr auto is_character_v = is_char<T>::value;

template <typename T>
constexpr auto is_string_v = is_string<T>::value;

template <typename T>
constexpr auto is_container_v = is_container<T>::value;  // FIXME: use concepts, require std::begin, std::end, and not is_string_v

template <typename Data, typename Visitor>
constexpr auto accepts_v = true;  // FIXME: check for Data::accept(Visitor) by using concepts or detection toolkit

#endif  // STATIC_VISITOR_META_HPP