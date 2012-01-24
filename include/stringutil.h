#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <fstream>
#include <iterator>
#include <sstream>
#include <string>

namespace 
{

template <typename _T>
inline std::string ttoa(const _T& t)
{
  std::ostringstream oss;
  oss << t;
  return oss.str();
}

}

namespace cpputil
{

template <typename _Alloc, template <typename, typename> class _Container>
void split(const std::string& s, _Container<std::string, _Alloc>& c, char delim)
{
  std::istringstream iss(s);
  std::string ss;

  for ( auto i = back_inserter(c); !iss.eof(); ++i )
  {
    getline(iss, ss, delim);
    i = ss;
  }
}

template <class _Alloc, template <typename, typename> class _Container>
inline void words(const std::string& s, _Container<std::string, _Alloc>& c)
{
  return split(s, c, ' ');
}

template <typename _Alloc, template <typename, typename> class _Container>
inline void lines(const std::string& s, _Container<std::string, _Alloc>& c)
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

inline std::string readfile(const char* file)
{
  std::ifstream ifs(file);
  if ( ! ifs.is_open() )
    return "";

  std::stringstream ss;
  ss << ifs.rdbuf();
  return ss.str();
}

}

#endif
