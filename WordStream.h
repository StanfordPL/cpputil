#ifndef WORD_STREAM_H
#define WORD_STREAM_H

#include <iterator>
#include <sstream>
#include <string>

class IWordStream
{
  public:
    IWordStream(const std::string& s, char delim = ' ');

    bool eof() const;
    IWordStream& operator>>(std::string& s);  

  private:
    std::istringstream iss_;
    char delim_;
};

template <class Container>
void words(const std::string& s, Container& c, char delim = ' ');

class OWordStream
{
  public:
    OWordStream(char delim = ' '); 

    std::string str() const;
    OWordStream& operator<<(const std::string& s);

  private:
    std::ostringstream oss_;
    char delim_;
    bool empty_;
};

template <class InputIterator>
std::string unwords(InputIterator begin, InputIterator end, char delim = ' ');

IWordStream::IWordStream(const std::string& s, char delim) :
  iss_(s),
  delim_(delim)
{
  // Does nothing.
}

inline bool IWordStream::eof() const
{
  return iss_.eof();
}

inline IWordStream& IWordStream::operator>>(std::string& s)
{
  std::getline(iss_, s, delim_);
  return *this;
}

template <class Container>
void words(const std::string& s, Container& c, char delim)
{
  IWordStream iws(s, delim);
  std::string word; 

  for ( auto itr = back_inserter(c); !iws.eof(); ++itr )
  {
    iws >> word;
    itr = word;
  }
}

OWordStream::OWordStream(char delim) :
  delim_(delim),
  empty_(true)
{
  // Does nothing.
}

inline std::string OWordStream::str() const
{
  return oss_.str();
}

inline OWordStream& OWordStream::operator<<(const std::string& s)
{
  if ( empty_ )
    empty_ = false;
  else
    oss_ << delim_;
  oss_ << s;

  return *this;
}

template <class InputIterator>
std::string unwords(InputIterator begin, InputIterator end, char delim)
{
  OWordStream ows(delim);
  for ( ; begin != end; ++begin )
    ows << *begin;

  return ows.str();
}

#endif
