#ifndef CPPUTIL_SYSTEM_ARCHITECTURE_H
#define CPPUTIL_SYSTEM_ARCHITECTURE_H

/// @file architecture.h
/// @brief Macros for testing architecture properties.
///
/// Defines IS_32_BIT iff this is a 32-bit architecture.
/// Defines IS_64_BIT otherwise.

// Windows
#if _WIN32 || _WIN64
  #if _WIN64
    #define IS_64_BIT()
  #else
    #define IS_32_BIT()
  #endif
#endif

// gcc
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define IS_64_BIT()
  #else
    #define IS_32_BIT()
  #endif
#endif

#endif
