#ifndef SOCKETSTREAM_H
#define SOCKETSTREAM_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <cassert>
#include <cstring>

#include <iostream>
#include <streambuf>

template <class Char, class Traits>
class basic_socketbuf : public std::basic_streambuf<Char, Traits>
{
  public:
    basic_socketbuf();
    basic_socketbuf(int socket);
    basic_socketbuf(const char* host, unsigned int port);
    virtual ~basic_socketbuf();

    void open(int socket);
    void open(const char* host, unsigned int port);
    void close();

    bool okay() const;

  protected:  
    virtual void imbue(const std::locale& loc);

    virtual std::basic_streambuf<Char, Traits>* setbuf(Char* s, std::streamsize n);
    virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);
    virtual std::streampos seekpos(std::streampos sp, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);
    virtual int sync();

    virtual std::streamsize showmanyc();
    virtual std::streamsize xsgetn(Char* s, std::streamsize n);
    virtual int underflow();
    virtual int uflow();
    virtual int pbackfail(int c = EOF);

    virtual std::streamsize xsputn(const Char* s, std::streamsize n);
    virtual int overflow(int c = EOF);

  private:
    int socket_;
    Char getArea_[512];
    Char putArea_[512];

    bool okay_;
};

template <class Char, class Traits>
class basic_socketstream : public std::basic_iostream<Char, Traits>
{
  public:
    basic_socketstream();
    basic_socketstream(int socket);
    basic_socketstream(const char* host, unsigned int port); 
    virtual ~basic_socketstream();

    void open(int socket);
    void open(const char* host, unsigned int port);
    void close();

  private:
    basic_socketbuf<Char, Traits> sbuf_;  
};

template <class Char, class Traits>
class basic_socketstreamserver
{
  public:
    basic_socketstreamserver(unsigned int port, unsigned int maxConnections = 8);
    ~basic_socketstreamserver();

    void accept(basic_socketstream<Char, Traits>& ss);

    bool okay() const;

  private:
    int socket_;
    sockaddr_in addr_;
    
    bool okay_;
};

typedef basic_socketstream<char, std::char_traits<char> > socketstream;
typedef basic_socketstream<wchar_t, std::char_traits<wchar_t> > wsocketstream;

typedef basic_socketstreamserver<char, std::char_traits<char> > socketstreamserver;
typedef basic_socketstreamserver<wchar_t, std::char_traits<wchar_t> > wsocketstreamserver;



template <class Char, class Traits>
basic_socketbuf<Char, Traits>::basic_socketbuf()
{
  okay_ = false;
}

template <class Char, class Traits>
basic_socketbuf<Char, Traits>::basic_socketbuf(int socket)
{
  open(socket);
}

template <class Char, class Traits>
basic_socketbuf<Char, Traits>::basic_socketbuf(const char* host, unsigned int port)
{
  open(host, port);
}

template <class Char, class Traits>
basic_socketbuf<Char, Traits>::~basic_socketbuf()
{
  close();
}

template <class Char, class Traits>
void basic_socketbuf<Char, Traits>::open(int socket)
{
  socket_ = socket;
  okay_ = true;
  
  setg(&getArea_[0], 0, &getArea_[0]);
  setp(&putArea_[0], &putArea_[512]);
}

template <class Char, class Traits>
void basic_socketbuf<Char, Traits>::open(const char* host, unsigned int port) 
{
  sockaddr_in addr;  
  memset(&addr, 0, sizeof(addr));  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  okay_ = (inet_pton(AF_INET, host, &addr.sin_addr) != -1) &&
          (errno != EAFNOSUPPORT) &&
          (socket_ = socket(AF_INET, SOCK_STREAM, 0)) != -1 &&
          (::connect(socket_, (sockaddr*) &addr, sizeof(addr)) != -1);

  setg(&getArea_[0], 0, &getArea_[0]);
  setp(&putArea_[0], &putArea_[512]);
}

template <class Char, class Traits>
void basic_socketbuf<Char, Traits>::close()
{
  if ( okay_ )
    ::close(socket_);

  okay_ = false;
}

template <class Char, class Traits>
bool basic_socketbuf<Char, Traits>::okay() const
{
  return okay_;
}

template <class Char, class Traits>
void basic_socketbuf<Char, Traits>::imbue(const std::locale& loc)
{
  assert(false && "No definition for imbue()!");
}

template <class Char, class Traits>
std::basic_streambuf<Char, Traits>* basic_socketbuf<Char, Traits>::setbuf(Char* s, std::streamsize n)
{
  assert(false && "No definition for setbuf()!");
  return 0;
}

template <class Char, class Traits>
std::streampos basic_socketbuf<Char, Traits>::seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which)
{
  assert(false && "No definition for seekoff()!");
  return 0;
}

template <class Char, class Traits>
std::streampos basic_socketbuf<Char, Traits>::seekpos(std::streampos sp, std::ios_base::openmode which)
{
  assert(false && "No definition for seekpos()!");
  return 0;
}

template <class Char, class Traits>
int basic_socketbuf<Char, Traits>::sync()
{
  if ( okay_ )
    return -1;

  int sent = 0;
  unsigned int total = 0;        
  unsigned int remaining = std::basic_streambuf<Char, Traits>::pptr() - std::basic_streambuf<Char, Traits>::pbase();

  okay_ = send(socket_, &remaining, 1, 0) == 1;
  while ( okay_ && remaining > 0 )
  {
    okay_ = (sent = send(socket_, std::basic_streambuf<Char, Traits>::pbase() + total, remaining, 0)) > 0;
    total += sent;
    remaining -= sent;
  }

  if ( !okay_ )
    return -1;

  setp(&putArea_[0], &putArea_[512]);
  return 0;
}

template <class Char, class Traits>
std::streamsize basic_socketbuf<Char, Traits>::showmanyc()
{
  assert(false && "No definition for showmanyc()!");
  return 0;
}

template <class Char, class Traits>
std::streamsize basic_socketbuf<Char, Traits>::xsgetn(Char* s, std::streamsize n)
{
  return std::basic_streambuf<Char, Traits>::xsgetn(s, n);
}

template <class Char, class Traits>
int basic_socketbuf<Char, Traits>::underflow()
{
  if ( !okay_ )
    return -1;

  int got = 0;
  unsigned int total = 0;
  unsigned int remaining = 0;

  okay_ = recv(socket_, &remaining, 1, 0) == 1;
  while ( okay_ && remaining > 0 )
  {
    okay_ = (got = recv(socket_, &getArea_[total], remaining, 0)) > 0;
    total += got;
    remaining -= got;
  }

  if ( !okay_ )
    return -1;

  setg(&getArea_[0], &getArea_[0], &getArea_[total]);
  return getArea_[0];
}

template <class Char, class Traits>
int basic_socketbuf<Char, Traits>::uflow()
{
  return std::basic_streambuf<Char, Traits>::uflow();
}

template <class Char, class Traits>
int basic_socketbuf<Char, Traits>::pbackfail(int c)
{
  assert(false && "No definition for pbackfail()!");
  return 0;
}

template <class Char, class Traits>
std::streamsize basic_socketbuf<Char, Traits>::xsputn(const Char* s, std::streamsize n)
{
  return std::basic_streambuf<Char, Traits>::xsputn(s, n);
}

template <class Char, class Traits>
int basic_socketbuf<Char, Traits>::overflow(int c)
{
  if ( sync() == -1 )
    return -1;

  if ( c != EOF )
    putArea_[0] = c;

  return 0;
}

template <class Char, class Traits>
basic_socketstream<Char, Traits>::basic_socketstream() :
  std::iostream(&sbuf_),
  sbuf_()
{
  // Does nothing.
}

template <class Char, class Traits>
basic_socketstream<Char, Traits>::basic_socketstream(int socket) :
  std::iostream(&sbuf_),
  sbuf_(socket)
{
  // Does nothing.
}

template <class Char, class Traits>
basic_socketstream<Char, Traits>::basic_socketstream(const char* host, unsigned int port) :
  std::iostream(&sbuf_),
  sbuf_(host, port)
{
  // Does nothing.
}

template <class Char, class Traits>
basic_socketstream<Char, Traits>::~basic_socketstream()
{
  // Does nothing.
}

template <class Char, class Traits>
void basic_socketstream<Char, Traits>::open(int socket)
{
  sbuf_.open(socket);
}

template <class Char, class Traits>
void basic_socketstream<Char, Traits>::open(const char* host, unsigned int port)
{
  sbuf_.open(host, port);
}

template <class Char, class Traits>
void basic_socketstream<Char, Traits>::close()
{
  sbuf_.close();
}

template <class Char, class Traits>
basic_socketstreamserver<Char, Traits>::basic_socketstreamserver(unsigned int port, unsigned int maxConnections)
{
  memset(&addr_, 0, sizeof(addr_));  

  int on = 1;
  
  addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = INADDR_ANY;
  addr_.sin_port = htons(port);

  okay_ = (socket_ = socket(AF_INET, SOCK_STREAM, 0)) != -1;
  okay_ = okay_ && setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) != -1;
  okay_ = okay_ && bind(socket_, (sockaddr*) &addr_, sizeof(addr_)) != -1;
  okay_ = okay_ && listen(socket_, maxConnections) != -1;
}

template <class Char, class Traits>
basic_socketstreamserver<Char, Traits>::~basic_socketstreamserver()
{
  if ( okay_ )
    close(socket_);
}

template <class Char, class Traits>
void basic_socketstreamserver<Char, Traits>::accept(basic_socketstream<Char, Traits>& ss)
{
  if ( okay_ )
  {
    int sizeofaddr = sizeof(addr_);
    int sock = -1;

    okay_ = (sock = ::accept(socket_, (sockaddr*) &addr_, (socklen_t*) &sizeofaddr)) != -1;
    if ( okay_ )
      ss.open(sock);
  }
}

template <class Char, class Traits>
bool basic_socketstreamserver<Char, Traits>::okay() const
{
  return okay_;
}

#endif
