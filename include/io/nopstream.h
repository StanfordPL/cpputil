// Copyright 2014 eric schkufza
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPPUTIL_INCLUDE_IO_NOPSTREAM_H
#define CPPUTIL_INCLUDE_IO_NOPSTREAM_H

#include <iostream>

namespace cpputil {

template <typename Ch, typename Tr>
struct basic_inopstream : std::basic_istream<Ch, Tr> {
	explicit basic_inopstream(std::basic_istream<Ch, Tr>& is) { }

	explicit basic_inopstream(std::basic_streambuf<Ch, Tr>* sb) { }

	virtual ~basic_inopstream() { }

	basic_inopstream& operator>>(bool& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(short& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(unsigned short& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(int& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(unsigned int& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(long& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(unsigned long& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(float& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(double& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(long double& val) { 
    return *this; 
  }
	
  basic_inopstream& operator>>(void*& val) { 
    return *this; 
  }

	basic_inopstream& operator>>(std::basic_streambuf<Ch, Tr>* sb) { 
    return *this; 
  }

	basic_inopstream& operator>>(std::basic_istream<Ch, Tr>& (*pf)(std::basic_istream<Ch, Tr>&)) { 
    return *this; 
  }

	basic_inopstream& operator>>(std::basic_ios<Ch, Tr>& (*pf)(std::basic_ios<Ch, Tr>&)) { 
    return *this; 
  }

	basic_inopstream& operator>>(std::ios_base& (*pf)(std::ios_base&)) { 
    return *this; 
  }
};

template <typename Ch, typename Tr>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, Ch& ch) { 
  return is; 
}

template <typename Ch, typename Tr>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, signed char& ch) { 
  return is; 
}

template <typename Ch, typename Tr>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, unsigned char& ch) { 
  return is; 
}

template <typename Ch, typename Tr>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, Ch* str) { 
  return is; 
}

template <typename Ch, typename Tr>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, signed char* str) { 
  return is; 
}

template <typename Ch, typename Tr>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, unsigned char* str) { 
  return is; 
}

template <typename Ch, typename Tr, typename T>
basic_inopstream<Ch, Tr>& operator>>(basic_inopstream<Ch, Tr>& is, T& t) { 
  return is; 
}

typedef basic_inopstream<char, std::char_traits<char>> inopstream;
typedef basic_inopstream<wchar_t, std::char_traits<wchar_t>> winopstream;

template <typename Ch, typename Tr>
struct basic_onopstream : std::basic_ostream<Ch, Tr> {
	explicit basic_onopstream(std::basic_ostream<Ch, Tr>& os) { }

	explicit basic_onopstream(std::basic_streambuf<Ch, Tr>* sb) { }

	virtual ~basic_onopstream() { }

	basic_onopstream& operator<<(bool val) { 
    return *this; 
  }

	basic_onopstream& operator<<(short val) { 
    return *this; 
  }

	basic_onopstream& operator<<(unsigned short val) { 
    return *this; 
  }

	basic_onopstream& operator<<(int val) { 
    return *this; 
  }

	basic_onopstream& operator<<(unsigned int val) { 
    return *this; 
  }

	basic_onopstream& operator<<(long val) { 
    return *this; 
  }

	basic_onopstream& operator<<(unsigned long val) { 
    return *this; 
  }

	basic_onopstream& operator<<(float val) { 
    return *this; 
  }

	basic_onopstream& operator<<(double val) { 
    return *this; 
  }

	basic_onopstream& operator<<(long double val) { 
    return *this; 
  }

	basic_onopstream& operator<<(const void* val) { 
    return *this; 
  }

	basic_onopstream& operator<<(std::basic_streambuf<Ch, Tr>* sb) { 
    return *this; 
  }

	basic_onopstream& operator<<(std::basic_ostream<Ch, Tr>& (*pf)(std::basic_ostream<Ch, Tr>&)) { 
    return *this; 
  }

	basic_onopstream& operator<<(std::basic_ios<Ch, Tr>& (*pf)(std::basic_ios<Ch, Tr>&)) { 
    return *this; 
  }

	basic_onopstream& operator<<(std::ios_base& (*pf)(std::ios_base&)) { 
    return *this; 
  }
};

template <typename Ch, typename Tr>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, char c) { 
  return os; 
}

template <typename Ch, typename Tr>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, signed char c) { 
  return os; 
}

template <typename Ch, typename Tr>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, unsigned char c) { 
  return os; 
}

template <typename Ch, typename Tr>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, const char* s) { 
  return os; 
}

template <typename Ch, typename Tr>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, const signed char* s) { 
  return os; 
}

template <typename Ch, typename Tr>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, const unsigned char* s) { 
  return os; 
}

template <typename Ch, typename Tr, typename T>
basic_onopstream<Ch, Tr>& operator<<(basic_onopstream<Ch, Tr>& os, const T& t) { 
  return os; 
}

typedef basic_onopstream<char, std::char_traits<char>> onopstream;
typedef basic_onopstream<wchar_t, std::char_traits<wchar_t>> wonopstream;

template <typename Ch, typename Tr>
struct basic_nopstream : public basic_inopstream<Ch, Tr>, public basic_onopstream<Ch, Tr> {
	explicit basic_nopstream(std::basic_iostream<Ch, Tr>& ios) { }

	explicit basic_nopstream(std::basic_streambuf<Ch, Tr>* sb) { }

	virtual ~basic_nopstream() { }
};

typedef basic_nopstream<char, std::char_traits<char>> nopstream;
typedef basic_nopstream<wchar_t, std::char_traits<wchar_t>> wnopstream;

} // namespace cpputil

#endif
