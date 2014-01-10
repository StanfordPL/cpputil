/*
Copyright 2013 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CPPUTIL_STREAM_REDACTSTREAM_H
#define CPPUTIL_STREAM_REDACTSTREAM_H

#include <cctype>
#include <iostream>
#include <streambuf>

namespace cpputil
{

inline int redactbuf_i()
{
	static int i = std::ios_base::xalloc();
	return i;
}

template <typename Ch, typename Tr>
class basic_redactbuf : public std::basic_streambuf<Ch, Tr>
{
  public:

		typedef typename std::basic_streambuf<Ch, Tr>::char_type   char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type    off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type    pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

    inline explicit basic_redactbuf(std::basic_streambuf<Ch, Tr>* buf, std::ios_base& ios) : std::basic_streambuf<Ch, Tr>(), buf_(buf), ios_(ios) { }
		inline virtual ~basic_redactbuf() { }

  protected:

    inline virtual int sync() 
		{ 
			return buf_->pubsync(); 
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			const auto ch = traits_type::to_char_type(c);
			return ios_.iword(redactbuf_i()) != 0 && isgraph(ch) ? buf_->sputc('x') : buf_->sputc(ch);
		}

  private:

    std::basic_streambuf<Ch, Tr>* buf_; 
		std::ios_base& ios_;
};

template <typename Ch, typename Tr>
class basic_oredactstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oredactstream(std::basic_ostream<Ch, Tr>& os)   : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf(), *this) 
		{ 
			this->iword(redactbuf_i()) = 0;
		}
		inline explicit basic_oredactstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(&buf_), buf_(sb, *this)
		{
			this->iword(redactbuf_i()) = 0;
		}
		inline virtual ~basic_oredactstream() { }

  private:

    basic_redactbuf<Ch, Tr> buf_; 
};

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& redact(std::basic_ostream<Ch, Tr>& os)
{
	os.iword(redactbuf_i()) = 1;
	return os;
}

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& unredact(std::basic_ostream<Ch, Tr>& os)
{
	os.iword(redactbuf_i()) = 0;
	return os;
}

typedef basic_oredactstream<char, std::char_traits<char>>       oredactstream;        
typedef basic_oredactstream<wchar_t, std::char_traits<wchar_t>> woredactstream; 

}

#endif

