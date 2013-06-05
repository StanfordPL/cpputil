#ifndef CPPUTIL_STREAM_REDIRECTSTREAM_H
#define CPPUTIL_STREAM_REDIRECTSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename Ch, typename Tr>
class basic_redirectbuf : public std::basic_streambuf<Ch, Tr>
{
  public:

		typedef typename std::basic_streambuf<Ch, Tr>::char_type   char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type    off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type    pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

    inline explicit basic_redirectbuf(std::basic_streambuf<Ch, Tr>* buf) : std::basic_streambuf<Ch, Tr>(), buf_(buf) { }
		inline virtual ~basic_redirectbuf() { }

  protected:

    inline virtual void imbue(const std::locale& loc) 
		{ 
			buf_->pubimbue(loc); 
		}
    inline virtual std::basic_streambuf<Ch, Tr>* setbuf(char_type* s, std::streamsize n) 
		{ 
			return buf_->pubsetbuf(s, n); 
		}
    inline virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) 
		{ 
			return buf_->pubseekoff(off, dir, which); 
		}
    inline virtual pos_type seekpos(pos_type pos, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) 
		{ 
			return buf_->pubseekpos(pos, which); 
		}
    inline virtual int sync() 
		{ 
			return buf_->pubsync(); 
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			return buf_->sputc(traits_type::to_char_type(c)); 
		}
    inline virtual int_type underflow() 
		{ 
			return buf_->sgetc(); 
		}
    inline virtual int_type uflow() 
		{ 
			return buf_->sbumpc(); 
		}

  private:

    std::basic_streambuf<Ch, Tr>* buf_; 
};

template <typename Ch, typename Tr>
class basic_iredirectstream : public std::basic_istream<Ch, Tr>
{
  public:

		inline explicit basic_iredirectstream(std::basic_istream<Ch, Tr>& is)   : std::basic_istream<Ch, Tr>(&buf_), buf_(is.rdbuf()) { }
		inline explicit basic_iredirectstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_istream<Ch, Tr>(&buf_), buf_(sb) { }
		inline virtual ~basic_iredirectstream() { }

  private:

    basic_redirectbuf<Ch, Tr> buf_; 
};

typedef basic_iredirectstream<char, std::char_traits<char>>       iredirectstream;        
typedef basic_iredirectstream<wchar_t, std::char_traits<wchar_t>> wiredirectstream; 

template <typename Ch, typename Tr>
class basic_oredirectstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oredirectstream(std::basic_ostream<Ch, Tr>& os)   : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf()) { }
		inline explicit basic_oredirectstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(&buf_), buf_(sb) { }
		inline virtual ~basic_oredirectstream() { }

  private:

    basic_redirectbuf<Ch, Tr> buf_; 
};

typedef basic_oredirectstream<char, std::char_traits<char>>       oredirectstream;        
typedef basic_oredirectstream<wchar_t, std::char_traits<wchar_t>> woredirectstream; 

template <typename Ch, typename Tr>
class basic_redirectstream : public std::basic_iostream<Ch, Tr>
{
  public:

		inline explicit basic_redirectstream(std::basic_iostream<Ch, Tr>& ios) : std::basic_iostream<Ch, Tr>(&buf_), buf_(ios.rdbuf()) { }
		inline explicit basic_redirectstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_iostream<Ch, Tr>(&buf_), buf_(sb) { }
		inline virtual ~basic_redirectstream() { }

  private:

    basic_redirectbuf<Ch, Tr> buf_; 
};

typedef basic_redirectstream<char, std::char_traits<char>>       redirectstream;        
typedef basic_redirectstream<wchar_t, std::char_traits<wchar_t>> wredirectstream; 

}

#endif
