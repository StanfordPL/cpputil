#ifndef CPPUTIL_NOOPSTREAM_H
#define CPPUTIL_NOOPSTREAM_H

#include <iostream>

namespace cpputil
{

template <typename Ch, typename Tr>
struct basic_inoopstream : std::basic_istream<Ch, Tr>
{
	// Convenience Constructor
	inline explicit basic_inoopstream(std::basic_istream<Ch, Tr>& is) : std::basic_istream<Ch, Tr>(is.rdbuf()) { }

	// Constructor
	inline explicit basic_inoopstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_istream<Ch, Tr>(sb) { }
	// Destructor
	virtual inline ~basic_inoopstream() { }

	// Basic Template Member Declarations
	inline basic_inoopstream& operator>>(bool& val) { return *this; }
	inline basic_inoopstream& operator>>(short& val) { return *this; }
	inline basic_inoopstream& operator>>(unsigned short& val) { return *this; }
	inline basic_inoopstream& operator>>(int& val) { return *this; }
	inline basic_inoopstream& operator>>(unsigned int& val) { return *this; }
	inline basic_inoopstream& operator>>(long& val) { return *this; }
	inline basic_inoopstream& operator>>(unsigned long& val) { return *this; }
	inline basic_inoopstream& operator>>(float& val) { return *this; }
	inline basic_inoopstream& operator>>(double& val) { return *this; }
	inline basic_inoopstream& operator>>(long double& val) { return *this; }
	inline basic_inoopstream& operator>>(void*& val) { return *this; }
	inline basic_inoopstream& operator>>(std::basic_streambuf<Ch, Tr>* sb) { return *this; }
	inline basic_inoopstream& operator>>(std::basic_istream<Ch, Tr>& (*pf)(std::basic_istream<Ch, Tr>&)) { return *this; }
	inline basic_inoopstream& operator>>(std::basic_ios<Ch, Tr>& (*pf)(std::basic_ios<Ch, Tr>&)) { return *this; }
	inline basic_inoopstream& operator>>(std::ios_base& (*pf)(std::ios_base&)) { return *this; }
};

// Basic Template Global Functions
template <typename Ch, typename Tr>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, Ch& ch) { return is; }
template <typename Ch, typename Tr>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, signed char& ch) { return is; }
template <typename Ch, typename Tr>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, unsigned char& ch) { return is; }
template <typename Ch, typename Tr>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, Ch* str) { return is; }
template <typename Ch, typename Tr>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, signed char* str) { return is; }
template <typename Ch, typename Tr>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, unsigned char* str) { return is; }

// Catch-all for user-defined types
template <typename Ch, typename Tr, typename T>
inline basic_inoopstream<Ch, Tr>& operator>>(basic_inoopstream<Ch, Tr>& is, T& t) { return is; }

// Convenience typedefs
typedef basic_inoopstream<char, std::char_traits<char>> inoopstream;
typedef basic_inoopstream<wchar_t, std::char_traits<wchar_t>> winoopstream;

template <typename Ch, typename Tr>
struct basic_onoopstream : std::basic_ostream<Ch, Tr>
{
	// Convenience Constructor
	inline explicit basic_onoopstream(std::basic_ostream<Ch, Tr>& os) : std::basic_ostream<Ch, Tr>(os.rdbuf()) { }

	// Constructor
	inline explicit basic_onoopstream(std::basic_streambuf<Ch, Tr>* sb) : std::basic_ostream<Ch, Tr>(sb) { }
	// Destructor
	virtual inline ~basic_onoopstream() { }

	// Basic Template Member Declarations
	inline basic_onoopstream& operator<<(bool val) { return *this; }
	inline basic_onoopstream& operator<<(short val) { return *this; }
	inline basic_onoopstream& operator<<(unsigned short val) { return *this; }
	inline basic_onoopstream& operator<<(int val) { return *this; }
	inline basic_onoopstream& operator<<(unsigned int val) { return *this; }
	inline basic_onoopstream& operator<<(long val) { return *this; }
	inline basic_onoopstream& operator<<(unsigned long val) { return *this; }
	inline basic_onoopstream& operator<<(float val) { return *this; }
	inline basic_onoopstream& operator<<(double val) { return *this; }
	inline basic_onoopstream& operator<<(long double val) { return *this; }
	inline basic_onoopstream& operator<<(const void* val) { return *this; }
	inline basic_onoopstream& operator<<(std::basic_streambuf<Ch, Tr>* sb) { return *this; }
	inline basic_onoopstream& operator<<(std::basic_ostream<Ch, Tr>& (*pf)(std::basic_ostream<Ch, Tr>&)) { return *this; }
	inline basic_onoopstream& operator<<(std::basic_ios<Ch, Tr>& (*pf)(std::basic_ios<Ch, Tr>&)) { return *this; }
	inline basic_onoopstream& operator<<(std::ios_base& (*pf)(std::ios_base&)) { return *this; }
};

// Basic Template Global Functions
template <typename Ch, typename Tr>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, char c) { return os; }
template <typename Ch, typename Tr>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, signed char c) { return os; }
template <typename Ch, typename Tr>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, unsigned char c) { return os; }
template <typename Ch, typename Tr>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, const char* s) { return os; }
template <typename Ch, typename Tr>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, const signed char* s) { return os; }
template <typename Ch, typename Tr>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, const unsigned char* s) { return os; }

// Catch-all for user-defined types
template <typename Ch, typename Tr, typename T>
inline basic_onoopstream<Ch, Tr>& operator<<(basic_onoopstream<Ch, Tr>& os, const T& t) { return os; }

// Convenience typedefs
typedef basic_onoopstream<char, std::char_traits<char>> onoopstream;
typedef basic_onoopstream<wchar_t, std::char_traits<wchar_t>> wonoopstream;

template <typename Ch, typename Tr>
struct basic_ionoopstream : public basic_inoopstream<Ch, Tr>, public basic_onoopstream<Ch, Tr> 
{
	// Convenience Constructor
	explicit inline basic_ionoopstream(std::basic_iostream<Ch, Tr>& ios) : basic_inoopstream<Ch, Tr>(ios), basic_onoopstream<Ch, Tr>(ios) { }

	// Constructor
	explicit inline basic_ionoopstream(std::basic_streambuf<Ch, Tr>* sb) : basic_inoopstream<Ch, Tr>(sb), basic_onoopstream<Ch, Tr>(sb) { }
	// Destructor
	virtual inline ~basic_ionoopstream() { }
};

// Convenience typedefs
typedef basic_ionoopstream<char, std::char_traits<char>> ionoopstream;
typedef basic_ionoopstream<wchar_t, std::char_traits<wchar_t>> wionoopstream;

}

#endif
