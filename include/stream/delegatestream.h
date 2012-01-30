#ifndef CPPUTIL_STREAM_DELEGATESTREAM_H
#define CPPUTIL_STREAM_DELEGATESTREAM_H

/// @file delegatestream.h
/// @brief Templated basic_streambuf's and basic_iostream's that delegate read/write requests to existing basic_streambuf's.
///
/// The following references were extremely helpful in writing this header:
///  - @link http://wordaligned.org/articles/cpp-streambufs

#include <iostream>
#include <streambuf>

namespace cpputil
{

/// @brief A basic_streambuf that delegates all public methods to an existing basic_streambuf.
///
/// This is, to the best of my knowledge, a minimal complete implementation.
/// This class does not maintain an internal buffer.
/// Consequently, the default implementation of basic_streambuf redirects all read/write methods to calls to u(nder)flow/overflow.
/// For completeness, protected methods invocations for which corresponding public methods exist are delegated to those methods.
///
/// @sa http://www.cplusplus.com/reference/iostream/streambuf

template <typename Char, typename Traits>
class basic_delegatebuf : public std::basic_streambuf<Char, Traits>
{
  public:

    typedef typename std::basic_streambuf<Char, Traits>::char_type   char_type;   ///< Redefinition of the underlying char_type.
    typedef typename std::basic_streambuf<Char, Traits>::traits_type traits_type; ///< Redefinition of the underlying traits_type.
    typedef typename std::basic_streambuf<Char, Traits>::int_type    int_type;    ///< Redefinition of the underlying int_type.
    typedef typename std::basic_streambuf<Char, Traits>::pos_type    pos_type;    ///< Redefinition of the underlying pos_type.
    typedef typename std::basic_streambuf<Char, Traits>::off_type    off_type;    ///< Redefinition of the underlying off_type.

    /// @cond DELETED_METHODS
    basic_delegatebuf() = delete;
    /// @endcond

    /// @brief The default copy constructor provided by the compiler.
    basic_delegatebuf(const basic_delegatebuf& rhs) = default;
    /// @brief The default move constructor provided by the compiler.
    basic_delegatebuf(basic_delegatebuf&& rhs) = default;
    /// @brief The default assignment operator provided by the compiler.
    basic_delegatebuf& operator=(const basic_delegatebuf& rhs) = default;

    /// @brief Constructs a basic_delegatebuf from a basic_streambuf.
    basic_delegatebuf(std::basic_streambuf<Char, Traits>* buf /**< [in,out] The streambuf to which methods are delegated; must outlast the lifetime of this object. */
                     ) : 
      buf_(buf) 
    {
      // Does nothing.
    }

  protected:

    /// @brief Invokes pubimbue on the delegate basic_streambuf.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/imbue/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/pubimbue/
    virtual void imbue(const std::locale& loc) 
    { 
      buf_->pubimbue(loc); 
    }
    /// @brief Invokes pubsetbuf the delegate basic_streambuf.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/setbuf/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/pubsetbuf/
    virtual std::basic_streambuf<Char, Traits>* setbuf(char_type* s, std::streamsize n) 
    { 
      return buf_->pubsetbuf(s, n); 
    }
    /// @brief Invokes pubseekoff on the delegate basic_streambuf.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/seekoff/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/pubseekoff/
    virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) 
    { 
      return buf_->pubseekoff(off, dir, which); 
    }
    /// @brief Invokes pubseekpos on the delegate basic_streambuf.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/seekpos/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/pubseekpos/
    virtual pos_type seekpos(pos_type pos, std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) 
    { 
      return buf_->pubseekpos(pos, which); 
    }
    /// @brief Invokes pubsync on the delegate basic_streambuf.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/sync/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/pubsync/
    virtual int sync() 
    { 
      return buf_->pubsync(); 
    }

    /// @brief Invokes sputc on the delegate basic_streambuf.
    /// @return the result of the invocation on success, or eof on failure or eof as input.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/overflow/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/sputc/
    virtual int_type overflow(int_type c = traits_type::eof())
    {
      const auto eof = Traits::eof();

      if ( traits_type::eq_int_type(c, eof) )
        return Traits::not_eof(c);

      const auto ch = traits_type::to_char_type(c);
      const auto result = buf_->sputc(ch);

      return traits_type::eq_int_type(result, eof) ? eof : c;
    }
    /// @brief Invokes sgetc on the delegate basic_streambuf.
    /// @return the result of the invocation.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/underflow/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/sgetc/
    virtual int_type underflow() 
    { 
      return buf_->sgetc(); 
    }
    /// @brief Invokes sbumpc on the delegate basic_streambuf.
    /// @return the result of the invocation.
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/uflow/
    /// @sa http://www.cplusplus.com/reference/iostream/streambuf/sbumpc/
    virtual int_type uflow() 
    { 
      return buf_->sbumpc(); 
    }

  private:

    std::basic_streambuf<Char, Traits>* buf_; /**< The basic_streambuf to which methods are delegated. */
};

/// @brief A basic_istream backed by a basic_delegatebuf.
/// @sa http://www.cplusplus.com/reference/istream
template <typename Char, typename Traits>
class basic_idelegatestream : public std::basic_istream<Char, Traits>
{
  public:

    /// @cond DELETED_METHODS
    basic_idelegatestream() = delete;
    basic_idelegatestream(const basic_idelegatestream& rhs) = delete;
    basic_idelegatestream(basic_idelegatestream&& rhs) = delete;
    basic_idelegatestream& operator=(const basic_idelegatestream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_idelegatestream from a basic_istream.
    basic_idelegatestream(std::basic_istream<Char, Traits>& is /**< A basic_istream from which to co-opt a basic_streambuf to delegate to. */
                         ) :
      std::basic_istream<Char, Traits>(&buf_),
      buf_(is.rdbuf()) 
    {
      // Does nothing.
    }

  private:

    basic_delegatebuf<Char, Traits> buf_; /**< The default implementation of istream will redirect all read methods to this object. */
};

typedef basic_idelegatestream<char, std::char_traits<char>> idelegatestream;        ///< Convenience typedef for chars.
typedef basic_idelegatestream<wchar_t, std::char_traits<wchar_t>> widelegatestream; ///< Convenience typedef for wide chars.

/// @brief A basic_ostream backed by a basic_delegatebuf.
/// @sa http://www.cplusplus.com/reference/ostream
template <typename Char, typename Traits>
class basic_odelegatestream : public std::basic_ostream<Char, Traits>
{
  public:

    /// @cond DELETED_METHODS
    basic_odelegatestream() = delete;
    basic_odelegatestream(const basic_odelegatestream& rhs) = delete;
    basic_odelegatestream(basic_odelegatestream&& rhs) = delete;
    basic_odelegatestream& operator=(const basic_odelegatestream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_odelegatestream from a basic_ostream.
    basic_odelegatestream(std::basic_ostream<Char, Traits>& os /**< A basic_ostream from which to co-opt a basic_streambuf to delegate to. */
                         ) :
      std::basic_ostream<Char, Traits>(&buf_),
      buf_(os.rdbuf()) 
    {
      // Does nothing.
    }

  private:

    basic_delegatebuf<Char, Traits> buf_; /**< The default implementation of ostream will redirect all write methods to this object. */
};

typedef basic_odelegatestream<char, std::char_traits<char>> odelegatestream;        ///< Convenience typedef for chars.
typedef basic_odelegatestream<wchar_t, std::char_traits<wchar_t>> wodelegatestream; ///< Convenience typedef for wide chars.

/// @brief A basic_iostream backed by a basic_delegatebuf.
/// @sa http://www.cplusplus.com/reference/iostream
template <typename Char, typename Traits>
class basic_delegatestream : public std::basic_iostream<Char, Traits>
{
  public:

    /// @cond DELETED_METHODS
    basic_delegatestream() = delete;
    basic_delegatestream(const basic_delegatestream& rhs) = delete;
    basic_delegatestream(basic_delegatestream&& rhs) = delete;
    basic_delegatestream& operator=(const basic_delegatestream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_delegatestream from a basic_iostream.
    basic_delegatestream(std::basic_iostream<Char, Traits>& ios /**< A basic_iostream from which to co-opt a basic_streambuf to delegate to. */
                        ) :
      std::basic_iostream<Char, Traits>(&buf_),
      buf_(ios.rdbuf()) 
    {
      // Does nothing.
    }

  private:

    basic_delegatebuf<Char, Traits> buf_; /**< The default implementation of iostream will redirect all read/write methods to this object. */
};

typedef basic_delegatestream<char, std::char_traits<char>> delegatestream;        ///< Convenience typedef for chars.
typedef basic_delegatestream<wchar_t, std::char_traits<wchar_t>> wdelegatestream; ///< Convenience typedef for wide chars.

}

#endif
