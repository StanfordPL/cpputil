#ifndef FORWARDINGSTREAM_H
#define FORWARDINGSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename _Char, typename _Traits>
class basic_forwardingbuf : public std::basic_streambuf<_Char, _Traits>
{
  public:
    typedef typename _Traits::int_type int_type;

    basic_forwardingbuf(std::basic_streambuf<_Char, _Traits>* buf) :
      buf_(buf),
      isActive_(true)
    {
      // Does nothing.
    }

    void setActive(bool active) { isActive_ = active; }

  protected:
    virtual int sync() { return buf_->pubsync(); }

    virtual int_type overflow(int_type c = _Traits::eof())
    {
      const int_type eof = _Traits::eof();

      if ( _Traits::eq_int_type(c, eof) )
        return _Traits::not_eof(c);

      if ( ! isActive_ )
        return c;

      const _Char ch = _Traits::to_char_type(c);
      const int_type result = buf_->sputc(ch);

      return _Traits::eq_int_type(result, eof) ? eof : c;
    }

  private:
    std::basic_streambuf<_Char, _Traits>* buf_;
    bool isActive_;
};

template <typename _Char, typename _Traits>
class basic_forwardingstream : public std::basic_ostream<_Char, _Traits>
{
  public:
    basic_forwardingstream(std::ostream& os) :
      std::basic_ostream<_Char, _Traits>(&fbuf_),
      fbuf_(os.rdbuf())
    {
      // Does nothing.
    }

    void setActive(bool active) { fbuf_.setActive(active); }

  private:
    basic_forwardingbuf<_Char, _Traits> fbuf_;
};

typedef basic_forwardingstream<char, std::char_traits<char> > forwardingstream;
typedef basic_forwardingstream<wchar_t, std::char_traits<wchar_t> > wforwardingstream;

}

#endif
