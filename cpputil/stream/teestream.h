#ifndef CPPUTIL_STREAM_TEESTREAM_H
#define CPPUTIL_STREAM_TEESTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename Ch, typename Tr>
class basic_teebuf : public basic_streambuf<Ch, Tr>
{
  public:

		typedef typename std::basic_streambuf<Ch, Tr>::char_type   char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type    off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type    pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

		inline explicit basic_teebuf(std::basic_streambuf<Ch, Tr>* buf1, std::basic_streambuf<Ch, Tr>* buf2) : std::basic_streambuf<Ch, Tr>(), buf1_(buf1), buf2_(buf2) { }
		inline virtual ~basic_teebuf() { }

  protected:

		inline virtual int_type sync()
		{
			const auto res1 = buf1_->sync();
			const auto res2 = buf2_->sync();

			return ( res1 == 0 && res2 == 0 ) ? 0 : -1;
		}
    inline virtual int_type overflow(int_type c = traits_type::eof())
    {
      const auto res1 = buf1_->overflow(c); 
      const auto res2 = buf2_->overflow(c);
      const auto eof  = traits_type::eof();

      return traits_type::eq_int_type(res1, eof) || traits_type::eq_int_type(res2, eof) ? eof : c;
    }

  private:

    basic_streambuf<Ch, Tr> buf1_;
    basic_streambuf<Ch, Tr> buf2_;
};

template <typename Ch, typename Tr>
class basic_oteestream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oteestream(std::basic_ostream<Ch, Tr> os1, std::basic_ostream<Ch, Tr> os2)       : std::basic_ostream<Ch, Tr>(buf_), buf_(os1.rdbuf(), os2.rdbuf()) { }
		inline explicit basic_oteestream(std::basic_streambuf<Ch, Tr> buf1, std::basic_streambuf<Ch, Tr> buf2) : std::basic_ostream<Ch, Tr>(buf_), buf_(buf1, buf2) { }
		inline virtual ~basic_oteestream() { }

  private:

    basic_teebuf<Ch, Tr> buf_; 
};

typedef basic_oteestream<char, std::char_traits<char>>       oteestream;        
typedef basic_oteestream<wchar_t, std::char_traits<wchar_t>> woteestream; 

}

#endif
