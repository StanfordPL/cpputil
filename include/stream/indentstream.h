#ifndef CPPUTIL_STREAM_INDENT_STREAM_H
#define CPPUTIL_STREAM_INDENT_STREAM_H

/// @file indentstream.h
/// @brief Templated basic_delegatebuf's and basic_iostream's that implement indent on carriage return.

#include <stddef.h>
#include <stdexcept>

#include "stream/delegatestream.h"

namespace cpputil
{

/// @brief A basic_delegatebuf that implements indentation on carriage return.
template <typename Char, typename Traits>
class basic_indentbuf : public basic_delegatebuf<Char, Traits>
{
  public:

    typedef typename basic_delegatebuf<Char, Traits>::char_type   char_type;   ///< Redefinition of the underlying char_type.
    typedef typename basic_delegatebuf<Char, Traits>::traits_type traits_type; ///< Redefinition of the underlying traits_type.
    typedef typename basic_delegatebuf<Char, Traits>::int_type    int_type;    ///< Redefinition of the underlying int_type.
    typedef typename basic_delegatebuf<Char, Traits>::pos_type    pos_type;    ///< Redefinition of the underlying indent_type.
    typedef typename basic_delegatebuf<Char, Traits>::off_type    off_type;    ///< Redefinition of the underlying off_type.

    typedef          size_t                                       size_type;   ///< Tabstop and indent counting type.

    /// @cond DELETED_METHODS
    basic_indentbuf() = delete;
    /// @endcond

    /// @brief The default copy constructor provided by the compiler.
    basic_indentbuf(const basic_indentbuf& rhs) = default;
    /// @brief The default move constructor provided by the compiler.
    basic_indentbuf(basic_indentbuf&& rhs) = default;
    /// @brief The default assignment operator provided by the compiler.
    basic_indentbuf& operator=(const basic_indentbuf& rhs) = default;

    /// @brief Constructs a basic_delegatebuf from a basic_streambuf, with an optional tab stop.
    basic_indentbuf(std::basic_streambuf<Char, Traits>* buf, /**< [in,out] The streambuf to which methods are delegated; must outlast the lifetime of this object. */
                    size_type tabstop = 2                    /**< [in]     The width of a tab stop. */
                   ) : 
      basic_delegatebuf<Char, Traits>(buf),
      tabstop_(tabstop),
      pending_(true),
      indent_(0)
    {
      // Does nothing.
    }

    /// @brief Resets the tab stop width.
    void tabstop(size_type n /**< [in] The new tabstop width. */
                )
    {
      tabstop_ = n;
    }

    /// @brief Increments the current indent.
    void indent(size_type n = 1 /**< [in] The number of tab stops to increment by. */
               )
    {
      indent_ += n;
    } 

    /// @brief Decrements the current indent.
    /// 
    /// Throws an underflow_error if n is greater than the current indent.
    void unindent(size_type n = 1 /**< [in] The number of tab stops to decrement by. */
                 )
    {
      if ( n > indent_ )
        throw std::underflow_error("Cannot untab beyond the beginning of a line!");
      indent_ -= n;
    }

    /// @brief Resets the current indent to zero.
    void reset()
    {
      indent_ = 0;
    }

  protected:

    /// @brief Inserts spaces prior to the first character of a new line.
    ///
    /// The responsibility of inserting those spaces, along with the input character, is delegated to the underlying basic_streambuf.
    /// Control aborts on the first unsuccessful delegated call to overflow.
    ///
    /// @return the result of the final invocation of overflow, or eof on error.
    virtual int_type overflow(int_type c = traits_type::eof())
    {
      const auto eof = Traits::eof();

      if ( pending_ )
      {
        pending_ = false;
        for ( size_type i = 0, ie = tabstop_ * indent_; i < ie; ++i )
        {
          const auto result = basic_delegatebuf<Char, Traits>::overflow(' ');
          if ( traits_type::eq_int_type(result, eof) )
            return eof;
        }
      }

      if ( c == '\n' )
        pending_ = true;

      return basic_delegatebuf<Char, Traits>::overflow(c);
    }

  private:

    size_t tabstop_; /**< The width of a tab stop */
    bool pending_;   /**< Is a tab insertion pending? */
    size_t indent_;  /**< The current tab indent */
};

/// @brief A basic_ostream backed by a basic_indentbuf.
/// @sa http://www.cplusplus.com/reference/ostream
template <typename Char, typename Traits>
class basic_oindentstream : public std::basic_ostream<Char, Traits>
{
  public:

    /// @cond DELETED_METHODS
    basic_oindentstream() = delete;
    basic_oindentstream(basic_oindentstream&& rhs) = delete;
    basic_oindentstream& operator=(const basic_oindentstream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_oindentstream from a basic_ostream.
    basic_oindentstream(std::basic_ostream<Char, Traits>& os /**< A basic_ostream from which to co-opt a basic_streambuf to delegate to. */
                    ) :
      std::basic_ostream<Char, Traits>(&buf_),
      buf_(os.rdbuf()) 
      {
        // Does nothing.
      }

    /// @brief Returns a pointer to the underlying basic_indentbuf.
    /// @return the underlying basic_indentbuf
    basic_indentbuf<Char, Traits>* buf() 
    {
      return &buf_;
    }

  private:

    basic_indentbuf<Char, Traits> buf_; /**< The default implementation of ostream will redirect all write methods to this object. */
};

typedef basic_oindentstream<char, std::char_traits<char>> oindentstream;        ///< Convenience typedef for chars.
typedef basic_oindentstream<wchar_t, std::char_traits<wchar_t>> woindentstream; ///< Convenience typedef for wide chars.

/// @brief A basic_iostream backed by a basic_indentbuf.
/// @sa http://www.cplusplus.com/reference/iostream
template <typename Char, typename Traits>
class basic_indentstream : public std::basic_iostream<Char, Traits>
{
  public:

    /// @cond DELETED_METHODS
    basic_indentstream() = delete;
    basic_indentstream(basic_indentstream&& rhs) = delete;
    basic_indentstream& operator=(const basic_indentstream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_indentstream from a basic_iostream.
    basic_indentstream(std::basic_iostream<Char, Traits>& ios /**< A basic_iostream from which to co-opt a basic_streambuf to delegate to. */
                      ) :
      std::basic_iostream<Char, Traits>(&buf_),
      buf_(ios.rdbuf()) 
      {
        // Does nothing.
      }

    /// @brief Returns a pointer to the underlying basic_indentbuf.
    /// @return the underlying basic_indentbuf
    basic_indentbuf<Char, Traits>* buf() const
    {
      return &buf_;
    }

  private:

    basic_indentbuf<Char, Traits> buf_; /**< The default implementation of iostream will redirect all read/write methods to this object. */
};

typedef basic_indentstream<char, std::char_traits<char>> indentstream;        ///< Convenience typedef for chars.
typedef basic_indentstream<wchar_t, std::char_traits<wchar_t>> windentstream; ///< Convenience typedef for wide chars.

}

#endif
