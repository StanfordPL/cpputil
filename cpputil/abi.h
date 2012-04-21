#ifndef CPPUTIL_ABI_H
#define CPPUTIL_ABI_H

#include <string>

#include <cxxabi.h>

namespace cpputil
{

inline std::string unmangle(const char* mangled)
{
  int status;
  char* original = abi::__cxa_demangle(mangled, 0, 0, &status);
  
  std::string unmangled = original != 0 ? original : mangled;
  if ( original ) 
    free(original);

  return unmangled;
}

}

#endif
