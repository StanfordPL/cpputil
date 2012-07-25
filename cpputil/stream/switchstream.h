#ifndef CPPUTIL_STREAM_SWITCHSTREAM_H
#define CPPUTIL_STREAM_SWITCHSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename Ch, typename Tr>
class basic_switchbuf : public basic_streambuf<Ch, Tr>
{
  public:

    typedef typename basic_streambuf<Ch, Tr>::traits_type traits_type; 
    typedef typename basic_streambuf<Ch, Tr>::int_type    int_type;   

		inline explicit basic_switchbuf(std::basic_streambuf<Ch, Tr>* buf1, std::basic_streambuf<Ch, Tr>* buf2, bool use_first = true) : std::basic_streambuf<Ch, Tr>(), buf1_(buf1), buf2_(buf2), use_first_(use_first) { }
		inline virtual ~basic_switchbuf() { }

		inline void use_first() { use_first_ = true; }
		inline void use_second() { use_first = false; }

  protected:

		inline virtual int_type sync()
		{
			const auto res1 = buf1_->sync();
			const auto res2 = buf2_->sync();

			return ( res1 == 0 && res2 == 0 ) ? 0 : -1;
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			return use_first_ ? buf1_->overflow(c) : buf2_->overflow(c); 
		}

  private:

    basic_streambuf<Ch, Tr> buf1_;
    basic_streambuf<Ch, Tr> buf2_;

		bool use_first_;
};

template <typename Ch, typename Tr>
class basic_oswitchstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oswitchstream(std::basic_ostream<Ch, Tr> os1, std::basic_ostream<Ch, Tr> os2, bool use_first = true) : std::basic_ostream<Ch, Tr>(buf_), buf_(os1.rdbuf(), os2.rdbuf(), use_first) { }
		inline explicit basic_oswitchstream(std::basic_streambuf<Ch, Tr> buf1, std::basic_streambuf<Ch, Tr> buf2, bool use_first = true) : std::basic_ostream<Ch, Tr>(buf_), buf_(buf1, buf2, use_first) { }
		inline virtual ~basic_oswitchstream() { }

		inline void use_first() { buf_->use_first(); }
		inline void use_second() { buf_->use_second(); }

  private:

    basic_switchbuf<Ch, Tr> buf_; 
};

typedef basic_oswitchstream<char, std::char_traits<char>> oswitchstream;        
typedef basic_oswitchstream<wchar_t, std::char_traits<wchar_t>> woswitchstream; 

}

#endif

