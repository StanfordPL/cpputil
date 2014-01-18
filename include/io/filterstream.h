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

#ifndef CPPUTIL_INCLUDE_IO_FILTER_STREAM_H
#define CPPUTIL_INCLUDE_IO_FILTER_STREAM_H

#include <iostream>
#include <streambuf>
#include <vector>

namespace cpputil {

template <typename F, typename Ch, typename Tr>
class basic_ifilterstreambuf : public std::basic_streambuf<Ch,Tr> {
  public:
		typedef typename std::basic_streambuf<Ch, Tr>::char_type char_type;
    typedef typename std::basic_streambuf<Ch, Tr>::int_type int_type;   
		typedef typename std::basic_streambuf<Ch, Tr>::off_type off_type;
		typedef typename std::basic_streambuf<Ch, Tr>::pos_type pos_type;
    typedef typename std::basic_streambuf<Ch, Tr>::traits_type traits_type; 

    basic_ifilterstreambuf(std::basic_streambuf<Ch,Tr>* buf) 
      : buf_(buf), next_(16) { }

    virtual ~basic_ifilterstreambuf() { }

    F& filter() {
      return filter_;
    }

    void reserve(size_t bytes) {
      next_.reserve(bytes);
    }

  protected:
    virtual int_type underflow() { 
      if ( std::basic_streambuf<Ch,Tr>::gptr() == std::basic_streambuf<Ch,Tr>::egptr() ) {
        const auto c = buf_->sbumpc();
        const auto count = filter_(c, next_.data());
        setg(next_.data(), next_.data(), next_.data()+count);
      }
      return *std::basic_streambuf<Ch,Tr>::gptr();
    }

    virtual int_type sync() { 
      return buf_->pubsync();
    }

  private:
    std::basic_streambuf<Ch,Tr>* buf_;
    std::vector<Ch> next_;
    F filter_;
};

template <typename F, typename Ch, typename Tr>
class basic_ofilterstreambuf : public std::basic_streambuf<Ch,Tr> {
  public:
    basic_ofilterstreambuf(std::basic_streambuf<Ch,Tr>* buf) 
      : buf_(buf) { }

    virtual ~basic_ofilterstreambuf() { }

    F& filter() {
      return filter_;
    }

  protected:
    virtual int sync() {
      return buf_->pubsync();
    }

    virtual int overflow(int c = EOF) {
      if ( c == EOF )
        return EOF;
      
      filter_(buf_, c);
      return 1;
    }

  private:
    std::basic_streambuf<Ch,Tr>* buf_;
    F filter_;
};

template <typename F, typename Ch, typename Tr>
class basic_ifilterstream : public std::basic_istream<Ch,Tr> {
  public:
    explicit basic_ifilterstream(std::basic_istream<Ch,Tr>& is) 
      : std::basic_istream<Ch,Tr>(&buf_), buf_(is.rdbuf()) { }

    explicit basic_ifilterstream(std::basic_streambuf<Ch,Tr>& sb) 
      : std::basic_istream<Ch,Tr>(&buf_), buf_(sb) { }

    virtual ~basic_ifilterstream() { }

    F& filter() {
      return buf_.filter();
    }

    void reserve(size_t bytes) {
      buf_.reserve(bytes);
    }

  private:
    basic_ifilterstreambuf<F,Ch,Tr> buf_;
};

template <typename F>
using ifilterstream = public basic_ifilterstream<F,char,std::char_traits<char>>;
template <typename F>
using wifilterstream = public basic_ifilterstream<F,wchar_t,std::char_traits<wchar_t>>;

template <typename F, typename Ch, typename Tr>
class basic_ofilterstream : public std::basic_ostream<Ch,Tr> {
  public:
    explicit basic_ofilterstream(std::basic_ostream<Ch,Tr>& os) 
      : std::basic_ostream<Ch,Tr>(&buf_), buf_(os.rdbuf()) { }

    explicit basic_ofilterstream(std::basic_streambuf<Ch,Tr>& sb) 
      : std::basic_ostream<Ch,Tr>(&buf_), buf_(sb) { }

    virtual ~basic_ofilterstream() { }

    F& filter() {
      return buf_.filter();
    }

  private:
    basic_ofilterstreambuf<F,Ch,Tr> buf_;
};

template <typename F>
using ofilterstream = public basic_ofilterstream<F,char,std::char_traits<char>>;
template <typename F>
using wofilterstream = public basic_ofilterstream<F,wchar_t,std::char_traits<wchar_t>>;

} // namespace cpputil

#endif

