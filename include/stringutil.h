#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iterator>
#include <sstream>
#include <string>

namespace 
{

template <typename T>
inline std::string ttoa(const T& t)
{
  std::ostringstream oss;
  oss << t;
  return oss.str();
}

}

namespace cpputil
{

template <typename T, typename Alloc, template <typename, typename> class Container>
void split(const std::string& s, Container<T, Alloc>& c, char delim)
{
  std::istringstream iss(s);
  for ( auto i = back_inserter(c); !iss.eof(); ++i )
  {
    T t;
    iss >> t;
    i = t;
  }
}

template <class T, class Alloc, template <typename, typename> class Container>
inline void words(const std::string& s, Container<T, Alloc>& c)
{
  return split(s, c, ' ');
}

template <typename T, typename Alloc, template <typename, typename> class Container>
inline void lines(const std::string& s, Container<T, Alloc>& c)
{
  return split(s, c, '\n');
}

template <typename InputIterator>
std::string unsplit(InputIterator begin, InputIterator end, char delim)
{
  std::ostringstream oss;
  for ( ; begin != end; ++begin )
  {
    if ( ! oss.str().empty() )
      oss << delim;
    oss << *begin;
  }

  return oss.str();
}

template <typename InputIterator>
inline std::string unwords(InputIterator begin, InputIterator end)
{
  return unsplit(begin, end, ' ');
}

template <typename InputIterator>
inline std::string unlines(InputIterator begin, InputIterator end)
{
  return unsplit(begin, end, '\n');
}

inline std::string itoa(int x) 
{
  return ttoa(x);
}

inline std::string utoa(unsigned int x)
{
  return ttoa(x);
}

}

#endif
