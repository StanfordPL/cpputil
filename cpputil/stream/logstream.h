#ifndef CPPUTIL_STREAM_LOGSTREAM_H
#define CPPUTIL_STREAM_LOGSTREAM_H

#include <iostream>

#include "cpputil/stream/indentstream.h"
#include "cpputil/stream/noopstream.h"
#include "cpputil/stream/shuntstream.h"

namespace cpputil
{

enum LogLevel { SEVERE, WARNING, INFO, CONFIG, FINE, FINER, FINEST };

template <typename Ch, typename Tr>
class basic_ologstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_ologstream(std::basic_ostream<Ch, Tr>& os, LogLevel level = INFO) : std::basic_ostream<Ch, Tr>(&shunt_), shunt_(&indent_), indent_(os.rdbuf()), level_(level) { }
		inline explicit basic_ologstream(std::basic_streambuf<Ch, Tr>* sb, LogLevel level = INFO) : std::basic_ostream<Ch, Tr>(&shunt_), shunt_(&indent_), indent_(sb), level_(level) { }
		inline virtual ~basic_ologstream() { }

		inline void set_level(LogLevel level) { level_ = level; }

    basic_ologstream& operator<<(LogLevel level)
    {
      if ( level <= level_ )
      {
        shunt_.open();

        indent_.indent(10);
        *this << labels[level];
        indent_.reset();
      }
      else
        shunt_.close();

      return *this;
    }

  private:

    basic_shuntbuf<Ch, Tr> shunt_;   
    basic_indentbuf<Ch, Tr> indent_; 
    LogLevel level_;                    
};


#ifndef CPPUTIL_NO_LOG
typedef basic_ologstream<char, std::char_traits<char>> ologstream;        
typedef basic_ologstream<wchar_t, std::char_traits<wchar_t>> wologstream; 
#else
typedef basic_onoopstream<char, std::char_traits<char>> ologstream;
typedef basic_onoopstream<wchar_t, std::char_traits<wchar_t>> ologstream;
#endif

}
#endif
