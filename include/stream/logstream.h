#ifndef CPPUTIL_STREAM_LOGSTREAM
#define CPPUTIL_STREAM_LOGSTREAM

/// @file log.h
/// @brief Templated basic_delegatebuf's and basic_iostream's that can selectively ignore output characters.

#include <array>
#include <stdexcept>
#include <string>

#include "stream/indentstream.h"
#include "stream/shuntstream.h"

namespace 
{

/// @brief Logger filtering level labels
std::array<std::string, 8> labels  
{{
  "    [OFF] ",
  " [SEVERE] ",
  "[WARNING] ",
  "   [INFO] ",
  " [CONFIG] ",
  "   [FINE] ",
  "  [FINER] ",
  " [FINEST] "
}};

}

namespace cpputil
{

/// @brief A basic_ostream backed by a basic_shuntbuf.
/// @sa http://www.cplusplus.com/reference/ostream
template <typename Char, typename Traits>
class basic_ologstream : public std::basic_ostream<Char, Traits>
{
  public:

    /// @brief Log filtering levels.
    enum Level
    {
      OFF     = 0,
      SEVERE  = 1,
      WARNING = 2,
      INFO    = 3,
      CONFIG  = 4,
      FINE    = 5,
      FINER   = 6,
      FINEST  = 7
    };

    /// @cond DELETED_METHODS
    basic_ologstream() = delete;
    basic_ologstream(basic_ologstream&& rhs) = delete;
    basic_ologstream& operator=(const basic_ologstream& rhs) = delete;
    /// @endcond

    /// @brief Constructs a basic_ologstream from a basic_ostream, and an optional default filtering level.
    basic_ologstream(std::basic_ostream<Char, Traits>& os, /**< A basic_ostream to which log messages should be directed. */
                     Level level = INFO                    /**< The initial filtering level. */
                    ) :
      std::basic_ostream<Char, Traits>(&shunt_),
      shunt_(&indent_),
      indent_(os.rdbuf(), 10),
      level_(level)
    {
      // Does nothing.
    }

    /// @briefs Resets the logger's filtering level.
    void setLevel(Level level /**< The new filtering level. */
                 )
    {
      level_ = level;
    }

    /// @brief Sets the filtering level of all subsequent stream insertions.
    ///
    /// Log messages above the current filtering level will be ignored.
    /// Throws invalid_argument if level is OFF.
    basic_ologstream& operator<<(Level level)
    {
      if ( level == OFF )
        throw std::invalid_argument("Cannot emit messages with filtering level OFF!");

      if ( level <= level_ )
      {
        shunt_.open();

        indent_.reset();
        *this << labels[level];
        indent_.indent();
      }
      else
        shunt_.close();

      return *this;
    }

  private:

    basic_shuntbuf<Char, Traits> shunt_;   ///< Controls whether log messages are emitted.
    basic_indentbuf<Char, Traits> indent_; ///< Controls log message indenting.
    Level level_;                          ///< The current filtering level.
};

typedef basic_ologstream<char, std::char_traits<char>> ologstream;        ///< Convenience typedef for chars.
typedef basic_ologstream<wchar_t, std::char_traits<wchar_t>> wologstream; ///< Convenience typedef for wide chars.

}
#endif
