#ifndef WORD_STREAM_H
#define WORD_STREAM_H

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

class IWordStream
{
  public:
    IWordStream(std::istream& is, char delim = ' ');

    template <class T>
    friend IWordStream& operator>>(IWordStream& iws, T& t);

  private:
    std::istream& is_;
    char delim_;
};

template <class T>
IWordStream& operator>>(IWordStream& iws, T& t);

class OWordStream
{
  public:
    OWordStream(std::ostream& os, char delim = ' '); 

    template <class T>
    friend OWordStream& operator<<(OWordStream& ows, T& t);

  private:
    std::ostream& os_;
    char delim_;
    bool empty_;
};

template <class T>
OWordStream& operator<<(OWordStream& ows, T& t);

template <class T, class Alloc, template <typename, typename> class Container>
void words(const std::string& s, Container<T, Alloc>& c, char delim = ' ');

template <class InputIterator>
std::string unwords(InputIterator begin, InputIterator end, char delim = ' ');

IWordStream::IWordStream(std::istream& is, char delim) :
  is_(is),
  delim_(delim)
{
  // Does nothing.
}

template <class T>
IWordStream& operator>>(IWordStream& iws, T& t)
{
  std::string s;
  std::getline(iws.is_, s, iws.delim_);

  std::istringstream iss(s);
  iss >> t;

  return iws;
}

template <>
IWordStream& operator>>(IWordStream& iws, std::string& s)
{
  std::getline(iws.is_, s, iws.delim_);
  return iws;
}

OWordStream::OWordStream(std::ostream& os, char delim) :
  os_(os),
  delim_(delim),
  empty_(true)
{
  // Does nothing.
}

template <class T>
OWordStream& operator<<(OWordStream& ows, T& t)
{
  if ( !ows.empty_ )
    ows.os_ << ows.delim_;
  ows.os_ << t;

  ows.empty_ = false;
  return ows;
}

template <class T, class Alloc, template <typename, typename> class Container>
void words(const std::string& s, Container<T, Alloc>& c, char delim)
{
  std::istringstream iss(s);
  IWordStream iws(iss, delim);

  T t;
  for ( auto itr = back_inserter(c); !iss.eof(); ++itr )
  {
    iws >> t;
    itr = t;
  }
}

template <class InputIterator>
std::string unwords(InputIterator begin, InputIterator end, char delim)
{
  std::ostringstream oss;
  OWordStream ows(oss, delim);

  for ( ; begin != end; ++begin )
    ows << *begin;

  return oss.str();
}

#endif
