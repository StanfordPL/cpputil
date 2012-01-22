#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include <cassert>
#include <iomanip>
#include <ostream>

#include "forwardingstream.h"

namespace cpputil
{

template <typename _Char, typename _Traits>
class basic_logstream : public std::basic_ostream<_Char, _Traits>
{
  public:
    enum Level
    {
      OFF     = 0,
      SEVERE  = 1,
      WARNING = 2,
      INFO    = 3,
      CONFIG  = 4,
      FINE    = 5,
      FINER   = 6,
      FINEST  = 7
    };

    basic_logstream(std::ostream& os) :
      std::basic_ostream<_Char, _Traits>(&fbuf_),
      fbuf_(os.rdbuf()),
      level_(FINEST)
    {
      // Does nothing.
    }  

    void setLevel(Level level) { level_ = level; }

    basic_logstream& operator<<(Level level)
    {
      if ( level <= level_ && level != OFF)
      {
        fbuf_.setActive(true);

        *this << "[";
        switch ( level )
        {
          case SEVERE: 
            *this << "SEVERE ";
            break;
          case WARNING: 
            *this << "WARNING";
            break;
          case INFO: 
            *this << "INFO   ";
            break;
          case CONFIG: 
            *this << "CONFIG ";
            break;
          case FINE: 
            *this << "FINE   ";
            break;
          case FINER: 
            *this << "FINER  ";
            break;
          case FINEST:
            *this << "FINEST ";
            break;
         
          default:
            assert(false && "Control should never reach here!");
            break;
        }
        *this << "] ";
      }
      else
        fbuf_.setActive(false);

      return *this;
    }

  private:
    basic_forwardingbuf<_Char, _Traits> fbuf_;
    Level level_;
};

typedef basic_logstream<char, std::char_traits<char> > logstream;
typedef basic_logstream<wchar_t, std::char_traits<wchar_t> > wlogstream;

}

#endif
