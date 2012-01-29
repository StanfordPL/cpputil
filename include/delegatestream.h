#ifndef DELEGATE_STREAM_H
#define DELEGATE_STREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename _Char, typename _Traits>
class basic_delegatebuf : public std::basic_streambuf<_Char, _Traits>
{
  public:
    typedef typename std::basic_streambuf<_Char, _Traits>::char_type   char_type;
    typedef typename std::basic_streambuf<_Char, _Traits>::traits_type traits_type;
    typedef typename std::basic_streambuf<_Char, _Traits>::int_type    int_type;
    typedef typename std::basic_streambuf<_Char, _Traits>::pos_type    pos_type;
    typedef typename std::basic_streambuf<_Char, _Traits>::off_type    off_type;

    basic_delegatebuf(std::basic_streambuf<_Char, _Traits>* buf) : buf_(buf) {}

  protected:
    virtual void imbue(const std::locale& loc) { buf_->pubimbue(loc); }
    virtual std::basic_streambuf<_Char, _Traits>* setbuf(char_type* s, std::streamsize n) { return buf_->pubsetbuf(s, n); }
    virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) { return buf_->pubseekoff(off, dir, which); }
    virtual pos_type seekpos(pos_type pos, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) { return buf_->pubseekpos(pos, which); }
    virtual int sync() { return buf_->pubsync(); }

    virtual int_type overflow(int_type c = traits_type::eof())
    {
      const int_type eof = _Traits::eof();

      if ( _Traits::eq_int_type(c, eof) )
        return _Traits::not_eof(c);

      const char_type ch = traits_type::to_char_type(c);
      const int_type result = buf_->sputc(ch);

      return traits_type::eq_int_type(result, eof) ? eof : c;
    }
    virtual int_type underflow() { return buf_->sgetc(); }
    virtual int_type uflow() { return buf_->sbumpc(); }

  private:
    std::basic_streambuf<_Char, _Traits>* buf_;
};

template <typename _Char, typename _Traits>
class basic_idelegatestream : public std::basic_istream<_Char, _Traits>
{
  public:
    basic_idelegatestream(std::istream& is) :
      std::basic_istream<_Char, _Traits>(&buf_),
      buf_(is.rdbuf())
    {
      // Does nothing.
    }

  private:
    basic_delegatebuf<_Char, _Traits> buf_;
};

typedef basic_idelegatestream<char, std::char_traits<char>> idelegatestream;
typedef basic_idelegatestream<wchar_t, std::char_traits<wchar_t>> widelegatestream;

template <typename _Char, typename _Traits>
class basic_odelegatestream : public std::basic_ostream<_Char, _Traits>
{
  public:
    basic_odelegatestream(std::ostream& os) :
      std::basic_ostream<_Char, _Traits>(&buf_),
      buf_(os.rdbuf())
    {
      // Does nothing.
    }

  private:
    basic_delegatebuf<_Char, _Traits> buf_;
};

typedef basic_odelegatestream<char, std::char_traits<char>> odelegatestream;
typedef basic_odelegatestream<wchar_t, std::char_traits<wchar_t>> wodelegatestream;

template <typename _Char, typename _Traits>
class basic_delegatestream : public std::basic_iostream<_Char, _Traits>
{
  public:
    basic_delegatestream(std::ostream& os) :
      std::basic_iostream<_Char, _Traits>(&buf_),
      buf_(os.rdbuf())
    {
      // Does nothing.
    }

  private:
    basic_delegatebuf<_Char, _Traits> buf_;
};

typedef basic_delegatestream<char, std::char_traits<char>> delegatestream;
typedef basic_delegatestream<wchar_t, std::char_traits<wchar_t>> wdelegatestream;

}

#endif
