#pragma once

#include <utility> // std::forward

// 定义比较运算符的宏
#define _LIBPENGCXX_DEFINE_COMPARISON(ClassName) \
    friend bool operator==(const ClassName& lhs, const ClassName& rhs) noexcept \
    { \
        return std::equal(lhs.begin(), lhs.end(), rhs.begin()); \
    } \
    \
    friend bool operator!=(const ClassName& lhs, const ClassName& rhs) noexcept \
    { \
        return !(lhs == rhs); \
    } \
    \
    friend bool operator<(const ClassName& lhs, const ClassName& rhs) noexcept \
    { \
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); \
    } \
    \
    friend bool operator<=(const ClassName& lhs, const ClassName& rhs) noexcept \
    { \
        return !(rhs < lhs); \
    } \
    \
    friend bool operator>(const ClassName& lhs, const ClassName& rhs) noexcept \
    { \
        return rhs < lhs; \
    } \
    \
    friend bool operator>=(const ClassName& lhs, const ClassName& rhs) noexcept \
    { \
        return !(lhs < rhs); \
    }

// 定义不可达代码的宏
#define _LIBPENGCXX_UNREACHABLE() \
    do { \
        __builtin_unreachable(); \
    } while (false)
