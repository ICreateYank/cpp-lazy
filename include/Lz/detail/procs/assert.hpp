#pragma once

#ifndef LZ_DETAIL_PROCS_ASSERT_HPP
#define LZ_DETAIL_PROCS_ASSERT_HPP

#include <Lz/detail/compiler_config.hpp>

// clang-format off

#if defined(LZ_DEBUG_ASSERTIONS)
  #define LZ_USE_DEBUG_ASSERTIONS
#endif

#if defined(LZ_USE_DEBUG_ASSERTIONS)
  #include <cstdio>
  #include <exception>
#endif

// clang-format on

#if defined(LZ_USE_DEBUG_ASSERTIONS)

namespace lz {
namespace detail {

[[noreturn]] inline void
assertion_fail(const char* file, const int line, const char* func, const char* message, const char* expr) {
    std::fprintf(stderr, "%s:%d assertion \"%s\" failed in function '%s' with message:\n\t%s\n", file, line, expr, func, message);
    std::terminate();
}
} // namespace detail
} // namespace lz

#define LZ_ASSERT(CONDITION, MSG)                                                                                                \
    ((CONDITION) ? (static_cast<void>(0)) : (lz::detail::assertion_fail(__FILE__, __LINE__, __func__, MSG, #CONDITION)))
#define LZ_ASSERT_INCREMENTABLE(CONDITION) LZ_ASSERT(CONDITION, "Cannot increment after end")
#define LZ_ASSERT_DECREMENTABLE(CONDITION) LZ_ASSERT(CONDITION, "Cannot decrement before begin")
#define LZ_ASSERT_DEREFERENCABLE(CONDITION) LZ_ASSERT(CONDITION, "Cannot dereference end")
#define LZ_ASSERT_ADDABLE(CONDITION) LZ_ASSERT(CONDITION, "Cannot add after end")
#define LZ_ASSERT_SUBTRACTABLE(CONDITION) LZ_ASSERT(CONDITION, "Cannot subtract before end")
#define LZ_ASSERT_SUB_ADDABLE(CONDITION) LZ_ASSERT(CONDITION, "Cannot add after end/cannot subtract before begin")
#define LZ_ASSERT_COMPATIBLE(CONDITION) LZ_ASSERT(CONDITION, "Incompatible iterators")

#else // ^^ defined(LZ_USE_DEBUG_ASSERTIONS) vv !defined(LZ_USE_DEBUG_ASSERTIONS)

#define LZ_ASSERT(CONDITION, MSG)                                                                                                \
    static_cast<void>(CONDITION);                                                                                                \
    static_cast<void>(MSG)

#define LZ_ASSERT_INCREMENTABLE(CONDITION) static_cast<void>(CONDITION)
#define LZ_ASSERT_DECREMENTABLE(CONDITION) static_cast<void>(CONDITION)
#define LZ_ASSERT_DEREFERENCABLE(CONDITION) static_cast<void>(CONDITION)
#define LZ_ASSERT_ADDABLE(CONDITION) static_cast<void>(CONDITION)
#define LZ_ASSERT_SUBTRACTABLE(CONDITION) static_cast<void>(CONDITION)
#define LZ_ASSERT_SUB_ADDABLE(CONDITION) static_cast<void>(CONDITION)
#define LZ_ASSERT_COMPATIBLE(CONDITION) static_cast<void>(CONDITION)

#endif // defined(LZ_USE_DEBUG_ASSERTIONS)

#endif
