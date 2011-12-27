#ifndef TEESTREAM_H
#define TEESTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename _CharT, typename _Traits>
class basic_teebuf : public std::basic_streambuf<_CharT, _Traits>
{
  public:
    typedef          _CharT            char_type;
    typedef          _Traits           traits_type;
    typedef typename _Traits::int_type int_type;

    basic_teebuf(std::basic_streambuf<char_type, traits_type>* buf1, std::basic_streambuf<char_type, traits_type>* buf2) :
      buf1_(buf1),
      buf2_(buf2)
    {
      // Does nothing.
    }

  protected:
    virtual int sync()
    {
      const int result1 = buf1_->pubsync();
      const int result2 = buf2_->pubsync();

      return result1 == 0 && result2 == 0 ? 0 : -1;
    }

    virtual int_type overflow(int_type c = traits_type::eof())
    {
      const int_type eof = traits_type::eof();
      
      if ( traits_type::eq_int_type(c, eof) )
        return traits_type::not_eof(c);

      const char_type ch = traits_type::to_char_type(c);
      const int_type result1 = buf1_->sputc(ch);
      const int_type result2 = buf2_->sputc(ch);

      return traits_type::eq_int_type(result1, eof) || traits_type::eq_int_type(result2, eof) ? eof : c;
    }

  private:
    std::basic_streambuf<char_type, traits_type>* buf1_;
    std::basic_streambuf<char_type, traits_type>* buf2_;
};

template <typename _CharT, typename _Traits>
class basic_teestream : public std::basic_ostream<_CharT, _Traits>
{
  public:
    basic_teestream(std::ostream& os1, std::ostream& os2) :
      std::basic_ostream<_CharT, _Traits>(&tbuf_),
      tbuf_(os1.rdbuf(), os2.rdbuf())
    {
      // Does nothing.
    }

  private:
    basic_teebuf<_CharT, _Traits> tbuf_;
};

typedef basic_teestream<char, std::char_traits<char> > teestream;
typedef basic_teestream<wchar_t, std::char_traits<wchar_t> > wteestream;

}

#endif
