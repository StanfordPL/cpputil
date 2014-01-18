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

#include <array>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

namespace cpputil {

template <typename F>
class ofilterstreambuf : public std::streambuf {
  public:
    ofilterstreambuf(std::streambuf* buf) 
      : buf_(buf) { }

    virtual ~ofilterstreambuf() { }

    F& filter() {
      return filter_;
    }

  protected:
    virtual int sync() {
      return buf_->pubsync() == 0 ? 0 : -1;
    }

    virtual int overflow(int c = EOF) {
      if ( c == EOF )
        return EOF;
      
      filter_(buf_, c);
      return 1;
    }

  private:
    std::streambuf* buf_;
    F filter_;
};

template <typename F>
class ofilterstream : public std::ostream {
  public:
    explicit ofilterstream(std::ostream& os) 
      : std::ostream(&buf_), buf_(os.rdbuf()) { }

    explicit ofilterstream(std::streambuf& sb) 
      : std::ostream(&buf_), buf_(sb) { }

    virtual ~ofilterstream() { }

    F& filter() {
      return buf_.filter();
    }

  private:
    ofilterstreambuf<F> buf_;
};






template <typename InF, typename OutF, size_t Size>
class filterstreambuf;

template <typename InF, typename OutF>
class filterstreambuf<InF, OutF, 0> : public std::streambuf {
  public:
    filterstreambuf(std::streambuf* buf) : buf_(buf) { }

    virtual ~filterstreambuf() { }

    virtual int underflow() { 
      if ( gptr() == egptr() ) {
        next_ = buf_->sbumpc();
        setg(&next_, &next_, &next_+1);
      }
      return *gptr();
    }

    virtual int overflow(int c = EOF) { 
      return buf_->sputc(c);
    }

    virtual int sync() { 
      if ( gptr() != egptr() ) {
        buf_->sputbackc(next_);
        setg(0,0,0);
      }
      return buf_->pubsync();
    }

  private:
    std::streambuf* buf_;
    char next_;
};

template <typename InF, typename OutF>
class filterstreambuf<InF, OutF, 1> : public std::streambuf {
  public:
    filterstreambuf(std::streambuf* buf) : buf_(buf) { }

    virtual ~filterstreambuf() { }

    virtual int underflow() { 
      if ( gptr() == egptr() ) {
        in_buf_.resize(1);
        if ( (in_buf_.front() = buf_->sbumpc()) == EOF ) {
          return EOF;
        }
        in_(in_buf_);
        setg(in_buf_.data(), in_buf_.data(), in_buf_.data()+in_buf_.size());
      }

      return *gptr();
    }

    virtual int overflow(int c = EOF) { 
      if ( c == EOF ) {
        return EOF;
      } 

      out_buf_.resize(1);
      out_buf_.front() = c;
      out_(out_buf_);
      for ( const auto val : out_buf_ ) {
        buf_->sputc(val);
      }

      return out_buf_.empty() ? EOF : out_buf_.back();
    }

    virtual int sync() { 
      return buf_->pubsync();
    }

  private:
    std::streambuf* buf_;

    InF in_;
    std::vector<char> in_buf_;
    OutF out_;
    std::vector<char> out_buf_;
};

template <typename InF, size_t Size>
class ifilterstream : public std::istream {
  public:
    ifilterstream(std::istream& is) : std::istream(&buf_), buf_(is.rdbuf()) { }
    virtual ~ifilterstream() { }

  private:
    filterstreambuf<InF, void*, Size> buf_;
};

} // namespace cpputil

#endif

