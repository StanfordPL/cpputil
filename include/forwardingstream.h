#ifndef FORWARDINGSTREAM_H
#define FORWARDINGSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename _CharT, typename _Traits>
class basic_forwardingbuf : public std::basic_streambuf<_CharT, _Traits>
{
  public:
    typedef _CharT char_type;
    typedef _Traits traits_type;
    typedef typename traits_type::int_type int_type;

    basic_forwardingbuf(std::basic_streambuf<char_type, traits_type>* buf) :
      buf_(buf),
      isActive_(true)
    {
      // Does nothing.
    }

    void setActive(bool active) { isActive_ = active; }

  protected:
    virtual int sync() { return buf_->pubsync(); }

    virtual int_type overflow(int_type c = traits_type::eof())
    {
      const int_type eof = traits_type::eof();

      if ( traits_type::eq_int_type(c, eof) )
        return traits_type::not_eof(c);

      if ( ! isActive_ )
        return c;

      const int_type result = buf_->sputc(traits_type::to_char_type(c));

      return traits_type::eq_int_type(result, eof) ? eof : c;
    }

  private:
    std::basic_streambuf<char_type, traits_type>* buf_;
    bool isActive_;
};

template <typename _CharT, typename _Traits>
class basic_forwardingstream : public std::basic_ostream<_CharT, _Traits>
{
  public:
    basic_forwardingstream(std::ostream& os) :
      std::basic_ostream<_CharT, _Traits>(&fbuf_),
      fbuf_(os.rdbuf())
    {
      // Does nothing.
    }

    void setActive(bool active) { fbuf_.setActive(active); }

  private:
    basic_forwardingbuf<_CharT, _Traits> fbuf_;
};

typedef basic_forwardingstream<char, std::char_traits<char> > forwardingstream;
typedef basic_forwardingstream<wchar_t, std::char_traits<wchar_t> > wforwardingstream;

}

#endif
