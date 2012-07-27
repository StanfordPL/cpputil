#ifndef CPPUTIL_STREAM_LOGSTREAM_H
#define CPPUTIL_STREAM_LOGSTREAM_H

#include <ctime>
#include <iostream>

#include "cpputil/stream/indentstream.h"
#include "cpputil/stream/noopstream.h"
#include "cpputil/stream/shuntstream.h"

namespace cpputil
{

inline int logbuf_i()
{
	static int i = std::ios_base::xalloc();
	return i;
}

template <typename Ch, typename Tr>
class basic_ologstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_ologstream(std::basic_ostream<Ch, Tr>& os) : std::basic_ostream<Ch, Tr>(&shunt_), shunt_(&indent_, *this), indent_(os.rdbuf(), *this) 
		{ 
			this->iword(logbuf_i()) = 0;	
		}
		inline explicit basic_ologstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(&shunt_), shunt_(&indent_, *this), indent_(sb, *this) 
		{ 
			this->iword(logbuf_i()) = 0;
		}
		inline virtual ~basic_ologstream() { }

		inline void set_level(long level) 
		{ 
			this->iword(logbuf_i()) = level;
		}

  private:

 		basic_shuntbuf<Ch, Tr> shunt_;		
    basic_indentbuf<Ch, Tr> indent_;
};

class level
{
	public:
		inline explicit level(long l) : l_(l) { }

		template <typename Ch, typename Tr>
	 	inline std::basic_ostream<Ch, Tr>& operator()(std::basic_ostream<Ch, Tr>& os) const
		{
			time_t raw;
			time(&raw);
			auto local = asctime(localtime(&raw));
			local[24] = '\0';

			if ( l_ <= os.iword(logbuf_i()) )
				os << open << unindent(30) << "[" << l_ << "][" << local << "] " << indent(30);
			else
				os << close;

			return os;
		}

	private:
		long l_;
};

template <typename Ch, typename Tr>
inline std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const level& l)
{
	return l(os);
}

#ifndef CPPUTIL_NO_LOG
typedef basic_ologstream<char, std::char_traits<char>>       ologstream;        
typedef basic_ologstream<wchar_t, std::char_traits<wchar_t>> wologstream; 
#else
typedef basic_onoopstream<char, std::char_traits<char>>       ologstream;        
typedef basic_onoopstream<wchar_t, std::char_traits<wchar_t>> wologstream; 
#endif

}

#endif
