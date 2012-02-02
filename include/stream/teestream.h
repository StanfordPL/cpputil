#ifndef CPPUTIL_STREAM_TEESTREAM_H
#define CPPUTIL_STREAM_TEESTREAM_H

/// @file teestream.h
/// @brief Templated basic_delegatebuf's and basic_ostream's that copy their inputs to a second basic_delegatebuf.

#include "stream/delegatestream.h"

namespace cpputil
{

/// @brief A basic_delegatebuf that copies its input to a second basic_delegatebuf.
template <typename Ch, typename Tr>
class basic_teebuf : public basic_delegatebuf<Ch, Tr>
{
  public:

    typedef typename basic_delegatebuf<Ch, Tr>::char_type   char_type;   ///< Redefinition of the underlying char_type.
    typedef typename basic_delegatebuf<Ch, Tr>::traits_type traits_type; ///< Redefinition of the underlying traits_type.
    typedef typename basic_delegatebuf<Ch, Tr>::int_type    int_type;    ///< Redefinition of the underlying int_type.
    typedef typename basic_delegatebuf<Ch, Tr>::pos_type    pos_type;    ///< Redefinition of the underlying pos_type.
    typedef typename basic_delegatebuf<Ch, Tr>::off_type    off_type;    ///< Redefinition of the underlying off_type.

    /// @cond DELETED_METHODS
    basic_teebuf() = delete;
    /// @endcond

    /// @brief The default copy constructor provided by the compiler.
    basic_teebuf(const basic_teebuf& rhs) = default;
    /// @brief The default move constructor provided by the compiler.
    basic_teebuf(basic_teebuf&& rhs) = default;
    /// @brief The default assignment operator provided by the compiler.
    basic_teebuf& operator=(const basic_teebuf& rhs) = default;

    /// @brief Constructs a basic_delegatebuf from two basic_streambuf's.
    basic_teebuf(std::basic_streambuf<Ch, Tr>* buf1, /**< [in,out] The first streambuf to which methods are delegated; must outlast the lifetime of this object. */
                 std::basic_streambuf<Ch, Tr>* buf2  /**< [in,out] The second streambuf to which methods are delegated; must outlast the lifetime of this object. */
                ) : 
      basic_delegatebuf<Ch, Tr>(buf1),
      buf2_(buf2)
    {
      // Does nothing.
    }

  protected:

    /// @brief Passes the input character to both underlying basic_delegatebufs.
    ///
    /// @return the input character on success, or eof if either underlying basic_delegatebuf returns eof.
    virtual int_type overflow(int_type c = traits_type::eof())
    {
      const int_type eof = traits_type::eof();

      auto res1 = basic_delegatebuf<Ch, Tr>::overflow(c);
      auto res2 = buf2_.sputc(c);

      return traits_type::eq_int_type(res1, eof) || traits_type::eq_int_type(res2, eof) ? eof : c;
    }

  private:

    basic_delegatebuf<Ch, Tr> buf2_; ///< The second underlying basic_delegatebuf.
};

/// @brief A basic_ostream backed by a basic_teebuf.
/// @sa http://www.cplusplus.com/reference/ostream
template <typename Ch, typename Tr>
class basic_oteestream : public std::basic_ostream<Ch, Tr>
{
  public:

    /// @cond DELETED_METHODS
    basic_oteestream() = delete;
    basic_oteestream(basic_oteestream&& rhs) = delete;
    basic_oteestream& operator=(const basic_oteestream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_oteestream from two basic_ostreams.
    basic_oteestream(std::basic_ostream<Ch, Tr>& os1, /**< The first basic_ostream from which to co-opt a basic_streambuf to delegate to. */
                     std::basic_ostream<Ch, Tr>& os2  /**< The second basic_ostream from which to co-opt a basic_streambuf to delegate to. */
                    ) :
      std::basic_ostream<Ch, Tr>(&buf_),
      buf_(os1.rdbuf(), os2.rdbuf()) 
    {
      // Does nothing.
    }

  private:

    basic_teebuf<Ch, Tr> buf_; /**< The default implementation of ostream will redirect all write methods to this object. */
};

typedef basic_oteestream<char, std::char_traits<char>> oteestream;        ///< Convenience typedef for chars.
typedef basic_oteestream<wchar_t, std::char_traits<wchar_t>> woteestream; ///< Convenience typedef for wide chars.

}

#endif
