#ifndef WORD_STREAM_H
#define WORD_STREAM_H

#include <iostream>
#include <sstream>
#include <string>

class IWordStream
{
  public:
    IWordStream(const std::string& s, char delim);

    bool eof() const;

    IWordStream& operator>>(std::string& s);  

  private:
    std::istringstream iss_;
    char delim_;
};

class OWordStream
{
  public:
    OWordStream(char delim = ' '); 

    std::string str() const;

    OWordStream& operator<<(const std::string& s);

  private:
    std::ostringstream oss_;
    char delim_;
};

IWordStream::IWordStream(const std::string& s, char delim = ' ') :
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

OWordStream::OWordStream(char delim) :
  delim_(delim)
{
  // Does nothing.
}

inline std::string OWordStream::str() const
{
  return oss_.str();
}

inline OWordStream& OWordStream::operator<<(const std::string& s)
{
  if ( str().length() > 0 )
    oss_ << delim_;
  oss_ << s;

  return *this;
}

#endif
