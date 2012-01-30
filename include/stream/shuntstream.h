#ifndef CPPUTIL_STREAM_SHUNTSTREAM
#define CPPUTIL_STREAM_SHUNTSTREAM

/// @file shuntstream.h
/// @brief Templated basic_delegatebuf's and basic_iostream's that can selectively ignore output characters.

#include "stream/delegatestream.h"

namespace cpputil
{

/// @brief A basic_delegatebuf that can selectively ignore output characters.
template <typename Char, typename Traits>
class basic_shuntbuf : public basic_delegatebuf<Char, Traits>
{
  public:

    typedef typename basic_delegatebuf<Char, Traits>::char_type   char_type;   ///< Redefinition of the underlying char_type.
    typedef typename basic_delegatebuf<Char, Traits>::traits_type traits_type; ///< Redefinition of the underlying traits_type.
    typedef typename basic_delegatebuf<Char, Traits>::int_type    int_type;    ///< Redefinition of the underlying int_type.
    typedef typename basic_delegatebuf<Char, Traits>::pos_type    pos_type;    ///< Redefinition of the underlying pos_type.
    typedef typename basic_delegatebuf<Char, Traits>::off_type    off_type;    ///< Redefinition of the underlying off_type.

    /// @cond DELETED_METHODS
    basic_shuntbuf() = delete;
    /// @endcond

    /// @brief The default copy constructor provided by the compiler.
    basic_shuntbuf(const basic_shuntbuf& rhs) = default;
    /// @brief The default move constructor provided by the compiler.
    basic_shuntbuf(basic_shuntbuf&& rhs) = default;
    /// @brief The default assignment operator provided by the compiler.
    basic_shuntbuf& operator=(const basic_shuntbuf& rhs) = default;

    /// @brief Constructs a basic_delegatebuf from a basic_streambuf.
    basic_shuntbuf(std::basic_streambuf<Char, Traits>* buf /**< [in,out] The streambuf to which methods are delegated; must outlast the lifetime of this object. */
                  ) : 
      basic_delegatebuf<Char, Traits>(buf),
      open_(true)
    {
      // Does nothing.
    }

    /// @brief Opens the shunt to output characters
    void open()
    {
      open_ = true;
    }

    /// @brief Closes the shunt to output characters
    void close()
    {
      open_ = false;
    }

  protected:

    /// @brief Passes the input character to the underlying basic_streambuf iff the shunt is open.
    ///
    /// @return the input character if the shunt is closed, or the result of the delegated invocation of overflow.
    virtual int_type overflow(int_type c = traits_type::eof())
    {
      return open_ ? basic_delegatebuf<Char, Traits>::overflow(c) : c;
    }

  private:

    bool open_; /**< Is the shunt open? */
};

/// @brief A basic_ostream backed by a basic_shuntbuf.
/// @sa http://www.cplusplus.com/reference/ostream
template <typename Char, typename Traits>
class basic_oshuntstream : public std::basic_ostream<Char, Traits>
{
  public:

    /// @cond DELETED_METHODS
    basic_oshuntstream() = delete;
    basic_oshuntstream(basic_oshuntstream&& rhs) = delete;
    basic_oshuntstream& operator=(const basic_oshuntstream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_oshuntstream from a basic_ostream.
    basic_oshuntstream(std::basic_ostream<Char, Traits>& os /**< A basic_ostream from which to co-opt a basic_streambuf to delegate to. */
                      ) :
      std::basic_ostream<Char, Traits>(&buf_),
      buf_(os.rdbuf()) 
    {
      // Does nothing.
    }

    /// @brief Returns a pointer to the underlying basic_shuntbuf.
    /// @return the underlying basic_shuntbuf
    basic_shuntbuf<Char, Traits>* buf() 
    {
      return &buf_;
    }

  private:

    basic_shuntbuf<Char, Traits> buf_; /**< The default implementation of ostream will redirect all write methods to this object. */
};

typedef basic_oshuntstream<char, std::char_traits<char>> oshuntstream;        ///< Convenience typedef for chars.
typedef basic_oshuntstream<wchar_t, std::char_traits<wchar_t>> woshuntstream; ///< Convenience typedef for wide chars.

}

#endif
