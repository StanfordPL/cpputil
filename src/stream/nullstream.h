#ifndef CPPUTIL_STREAM_NULLSTREAM_H
#define CPPUTIL_STREAM_NULLSTREAM_H

#include <iostream>
#include <streambuf>

namespace cpputil
{

template <typename Ch, typename Tr>
class basic_nullbuf : public std::basic_streambuf<Ch, Tr>
{
	public:

		typedef typename std::basic_streambuf<Ch, Tr>::char_type   char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type    int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type    off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type    pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

		inline explicit basic_nullbuf() : std::basic_streambuf<Ch, Tr>() { }
		inline virtual ~basic_nullbuf() { }

	protected:

    inline virtual int_type overflow(int_type c = traits_type::eof()) { return c; }
};

template <typename Ch, typename Tr>
class basic_onullstream : public std::basic_ostream<Ch, Tr>
{
	public:

		inline explicit basic_onullstream(std::basic_ostream<Ch, Tr>& is)   : std::basic_ostream<Ch, Tr>(&buf_), buf_() { }	
		inline explicit basic_onullstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(&buf_), buf_() { }
		inline virtual ~basic_onullstream() { }

	private:

		basic_nullbuf<Ch, Tr> buf_;		
};

typedef basic_onullstream<char, std::char_traits<char>>       onullstream;
typedef basic_onullstream<wchar_t, std::char_traits<wchar_t>> wonullstream;

}

#endif
