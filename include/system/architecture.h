#ifndef ARCHITECTURE_H
#define ARCHITECTURE_H

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
