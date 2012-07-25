#ifndef CPPUTIL_STREAM_SHUNTSTREAM_H
#define CPPUTIL_STREAM_SHUNTSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

inline static int shuntbuf_i()
{
	static int i = std::ios_base::xalloc();
	return i;
}

template <typename Ch, typename Tr>
class basic_shuntbuf : public std::basic_streambuf<Ch, Tr>
{
  public:

		typedef typename std::basic_streambuf<Ch, Tr>::char_type   char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type    off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type    pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

    inline explicit basic_shuntbuf(std::basic_streambuf<Ch, Tr>* buf, std::ios_base& ios) : std::basic_streambuf<Ch, Tr>(), buf_(buf), ios_(ios) { }
		inline virtual ~basic_shuntbuf() { }

  protected:

    inline virtual int sync() 
		{ 
			return buf_->pubsync(); 
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			return ios_.iword(shuntbuf_i()) != 0 ? buf_->sputc(traits_type::to_char_type(c)) : c;
		}

  private:

    std::basic_streambuf<Ch, Tr>* buf_; 
		std::ios_base& ios_;
};

template <typename Ch, typename Tr>
class basic_oshuntstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oshuntstream(std::basic_ostream<Ch, Tr>& os)   : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf(), *this) 
		{ 
			this->iword(shuntbuf_i()) = 1;
		}
		inline explicit basic_oshuntstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(sb), buf_(sb, *this)
		{
			this->iword(shuntbuf_i()) = 1;
		}
		inline virtual ~basic_oshuntstream() { }

  private:

    basic_shuntbuf<Ch, Tr> buf_; 
};

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& open(std::basic_ostream<Ch, Tr>& os)
{
	os.iword(shuntbuf_i()) = 1;
	return os;
}

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& close(std::basic_ostream<Ch, Tr>& os)
{
	os.iword(shuntbuf_i()) = 0;
	return os;
}

typedef basic_oshuntstream<char, std::char_traits<char>>       oshuntstream;        
typedef basic_oshuntstream<wchar_t, std::char_traits<wchar_t>> woshuntstream; 

}

#endif
