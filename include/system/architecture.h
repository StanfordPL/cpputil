#ifndef CPPUTIL_SYSTEM_ARCHITECTURE_H
#define CPPUTIL_SYSTEM_ARCHITECTURE_H

/// @file architecture.h
/// @brief Defines macros for testing architecture properties.

/// @def IS_32_BIT
/// @brief Defined iff the architecture is 32-bit.

/// @def IS_64_BIT
/// @brief Defined iff the architecture is 64-bit.

// Windows
#if _WIN32 || _WIN64
  #if _WIN64
    #define IS_64_BIT
  #else
    #define IS_32_BIT
  #endif
#endif

// gcc
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define IS_64_BIT
  #else
    #define IS_32_BIT
  #endif
#endif

#endif
