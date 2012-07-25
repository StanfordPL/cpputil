#ifndef CPPUTIL_STREAM_SHUNTSTREAM_H
#define CPPUTIL_STREAM_SHUNTSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename Ch, typename Tr>
class basic_shuntbuf : public std::basic_streambuf<Ch, Tr>
{
  public:

    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   

    inline explicit basic_shuntbuf(std::basic_streambuf<Ch, Tr>* buf, bool open = true) : std::basic_streambuf<Ch, Tr>(), buf_(buf), open_(open) { }
		inline virtual ~basic_shuntbuf() { }

  protected:

    inline virtual int sync() 
		{ 
			return buf_->pubsync(); 
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			return open_ ? buf_->sputc(traits_type::to_char_type(c)) : c;
		}

		inline void open() { open_ = true; }
		inline void close() { open_ = false; }

  private:

    std::basic_streambuf<Ch, Tr>* buf_; 
		bool open_;
};

template <typename Ch, typename Tr>
class basic_oshuntstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oshuntstream(std::basic_ostream<Ch, Tr>& os, bool open = true) : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf(), open) { }
		inline explicit basic_oshuntstream(std::basic_streambuf<Ch, Tr>* sb, bool open = true) : std::basic_ostream<Ch, Tr>(sb), buf_(sb, open) { }
		inline virtual ~basic_oshuntstream() { }

		inline void open() { buf_->open(); }
		inline void close() { buf_->close(); }

  private:

    basic_shuntbuf<Ch, Tr> buf_; 
};

typedef basic_oshuntstream<char, std::char_traits<char>> oshuntstream;        
typedef basic_oshuntstream<wchar_t, std::char_traits<wchar_t>> woshuntstream; 

}

#endif
