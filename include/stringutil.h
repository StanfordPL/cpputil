#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iterator>
#include <sstream>
#include <string>

namespace cpputil
{

template <class T, class Alloc, template <typename, typename> class Container>
void split(const std::string& s, Container<T, Alloc>& c, char delim);

template <class T, class Alloc, template <typename, typename> class Container>
void words(const std::string& s, Container<T, Alloc>& c);

template <class T, class Alloc, template <typename, typename> class Container>
void lines(const std::string& s, Container<T, Alloc>& c);

template <class InputIterator>
std::string unsplit(InputIterator begin, InputIterator end, char delim);

template <class InputIterator>
std::string unwords(InputIterator begin, InputIterator end);

template <class InputIterator>
std::string unlines(InputIterator begin, InputIterator end);

template <class T, class Alloc, template <typename, typename> class Container>
void split(const std::string& s, Container<T, Alloc>& c, char delim)
{
  std::istringstream iss(s);
  for ( auto i = back_inserter(c), !iss.eof(); ++i )
  {
    T t;
    iss >> t;
    itr = t;
  }
}

template <class T, class Alloc, template <typename, typename> class Container>
void words(const std::string& s, Container<T, Alloc>& c)
{
  return split(s, c, ' ');
}

template <class T, class Alloc, template <typename, typename> class Container>
void lines(const std::string& s, Container<T, Alloc>& c)
{
  return split(s, c, '\n');
}

template <class InputIterator>
std::string unsplit(InputIterator begin, InputIterator end, char delim)
{
  ostringstream oss;
  for ( ; begin != end; ++begin )
  {
    if ( ! oss.str().empty() )
      oss << delim;
    oss << *begin;
  }

  return oss.str();
}

template <class InputIterator>
std::string unwords(InputIterator begin, InputIterator end)
{
  return unsplit(begin, end, ' ');
}

template <class InputIterator>
std::string unlines(InputIterator begin, InputIterator end)
{
  return unsplit(begin, end, '\n');
}

}

#endif
