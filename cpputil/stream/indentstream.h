#ifndef CPPUTIL_STREAM_INDENT_STREAM_H
#define CPPUTIL_STREAM_INDENT_STREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

inline static int indentbuf_i()
{
	static int i = std::ios_base::xalloc();
	return i;
}

template <typename Ch, typename Tr>
class basic_indentbuf : public std::basic_streambuf<Ch, Tr>
{
  public:

		typedef typename std::basic_streambuf<Ch, Tr>::char_type   char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type    off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type    pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

    inline explicit basic_indentbuf(std::basic_streambuf<Ch, Tr>* buf, std::ios_base& ios) : std::basic_streambuf<Ch, Tr>(), buf_(buf), ios_(ios), pending_(false) { }
		inline virtual ~basic_indentbuf() { }

  protected:

    inline virtual int sync() 
		{ 
			return buf_->pubsync(); 
		}
    inline virtual int_type overflow(int_type c = traits_type::eof()) 
		{ 
			const auto ch = traits_type::to_char_type(c);

			if ( pending_ == true && ch != '\r' )
			{
				const auto eof = traits_type::eof();
				for ( long i = 0, ie = ios_.iword(indentbuf_i()); i < ie; ++i )
					if ( traits_type::eq_int_type(buf_->sputc(' '), eof) )
						return eof;

				pending_ = false;
			}

			if ( ch == '\n' )
				pending_ = true;

			return buf_->sputc(ch);
		}

  private:

    std::basic_streambuf<Ch, Tr>* buf_; 
		std::ios_base& ios_;
		bool pending_;
};

template <typename Ch, typename Tr>
class basic_oindentstream : public std::basic_ostream<Ch, Tr>
{
  public:

		inline explicit basic_oindentstream(std::basic_ostream<Ch, Tr>& os) : std::basic_ostream<Ch, Tr>(&buf_), buf_(os.rdbuf(), *this) 
		{ 
			this->iword(indentbuf_i()) = 0;	
		}
		inline explicit basic_oindentstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(sb), buf_(sb, *this) 
		{ 
			this->iword(indentbuf_i()) = 0;	
		}
		inline virtual ~basic_oindentstream() { }

  private:

    basic_indentbuf<Ch, Tr> buf_; 
};

class indent
{
	public:
		inline explicit indent(long i) : i_(i) { }
		
		template <typename Ch, typename Tr>
		inline std::basic_ostream<Ch, Tr>& operator()(std::basic_ostream<Ch, Tr>& os) const
		{
			os.iword(indentbuf_i()) += i_;
			return os;	
		}

	private:
		long i_;
};

class unindent
{
	public:
		inline explicit unindent(long ui) : ui_(ui) { }
		
		template <typename Ch, typename Tr>
		inline std::basic_ostream<Ch, Tr>& operator()(std::basic_ostream<Ch, Tr>& os) const
		{
			auto& l = os.iword(indentbuf_i());
			l -= ui_;
			if ( l < 0 )
				l = 0;

			return os;	
		}

	private:
		long ui_;
};

template <typename Ch, typename Tr>
inline std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const indent& i)
{
	return i(os);
}

template <typename Ch, typename Tr>
inline std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const unindent& ui)
{
	return ui(os);
}

typedef basic_oindentstream<char, std::char_traits<char>>       oindentstream;        
typedef basic_oindentstream<wchar_t, std::char_traits<wchar_t>> woindentstream; 

}

#endif
