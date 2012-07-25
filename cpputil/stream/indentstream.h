#ifndef CPPUTIL_STREAM_INDENT_STREAM_H
#define CPPUTIL_STREAM_INDENT_STREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename Ch, typename Tr>
class basic_indentbuf : public std::basic_streambuf<Ch, Tr>
{
  public:

    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef unsigned int                                       indent_type;

    inline explicit basic_indentbuf(std::basic_streambuf<Ch, Tr>* buf, indent_type indent = 0) : std::basic_streambuf<Ch, Tr>(), buf_(buf), indent_(indent) { }
		inline virtual ~basic_indentbuf() { }

  protected:

    inline virtual int sync() 
		{ 
			return buf_->pubsync(); 
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			return open_ ? buf_->sputc(traits_type::to_char_type(c)) : c;
		}

		inline void indent(indent_type indent) 
		{ 
			indent_ += indent 
		};
		inline void unindent(indent_type indent) 
		{
			if ( indent > indent_ )
				indent_ = 0;
			else
				indent_ -= indent;
		}
		inline void reset()
		{
			indent_ = 0;
		}

  private:

    std::basic_streambuf<Ch, Tr>* buf_; 
		indent_type indent_;
};

template <typename Ch, typename Tr>
class basic_oindentstream : public std::basic_ostream<Ch, Tr>
{
  public:

		typedef typename basic_indentbuf<Ch, Tr>::indent_type indent_type;

		inline explicit basic_oindentstream(std::basic_ostream<Ch, Tr>& os, indent_type indent = 0) : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf(), indent) { }
		inline explicit basic_oindentstream(std::basic_streambuf<Ch, Tr>* sb, indent_type indent = 0) : std::basic_ostream<Ch, Tr>(sb), buf_(sb, indent) { }
		inline virtual ~basic_oindentstream() { }

		inline void indent(indent_type indent) { buf_->indent(indent); }
		inline void unindent(indent_type indent) { buf_->unindent(indent); }
		inline void reset() { buf_->reset(); }

  private:

    basic_indentbuf<Ch, Tr> buf_; 
};

typedef basic_oindentstream<char, std::char_traits<char>> oindentstream;        
typedef basic_oindentstream<wchar_t, std::char_traits<wchar_t>> woindentstream; 

}

#endif
