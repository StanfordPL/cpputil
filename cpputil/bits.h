#ifndef CPPUTIL_BITS_H
#define CPPUTIL_BITS_H

#include <stdint.h>

namespace cpputil
{

struct w8   { typedef int8_t   type; };
struct w16  { typedef int16_t  type; };
struct w32  { typedef int32_t  type; };
struct w64  { typedef int64_t  type; };
struct w128 { typedef __int128 type; };

template <typename T> struct double_width {};
template <>           struct double_width<int8_t>  : public w16 {};
template <>           struct double_width<int16_t> : public w32 {};
template <>           struct double_width<int32_t> : public w64 {};
template <>           struct double_width<int64_t> : public w128 {};

template <typename T> struct half_width {};
template <>           struct half_width<int16_t>  : public w8  {};
template <>           struct half_width<int32_t>  : public w16 {};
template <>           struct half_width<int64_t>  : public w32 {};
template <>           struct half_width<__int128> : public w64 {};

template <typename Int, uint8_t n>
inline bool bit(Int x)
{
  return (x >> n) & 1;
}

template <typename Int, unsigned int CHAR_BIT = 8>
inline bool msb(Int x)
{
  return bit<Int, sizeof(Int)*CHAR_BIT-1>(x);
}

template <typename Int>
inline bool lsb(Int x) 
{ 
  return bit<Int, 0>(x);
}

template <typename Int, unsigned int CHAR_BIT = 8>
inline typename half_width<Int>::type upper(Int x)
{
  return x >> (sizeof(typename half_width<Int>::type) * CHAR_BIT); 
}

template <typename Int>
inline typename half_width<Int>::type lower(Int x)
{
  return (typename half_width<Int>::type) x;
}

template <typename Int>
uint8_t count_bits_naive(Int v)
{
  uint8_t c = 0;
  for ( ; v; v >>= 1 )
    c += v & 1;

  return c;
}

template <typename Int>
uint8_t count_bits_kernighan(Int v)
{
  uint8_t c = 0;
  for ( ; v; c++ )
    v &= v - 1;

  return c;
}

template <typename Int, unsigned int CHAR_BIT = 8>
uint8_t count_bits_best(Int v)
{
  v = v - ((v >> 1) & (Int)~(Int)0/3);                         
  v = (v & (Int)~(Int)0/15*3) + ((v >> 2) & (Int)~(Int)0/15*3);     
  v = (v + (v >> 4)) & (Int)~(Int)0/255*15;                      
  return (Int)(v * ((Int)~(Int)0/255)) >> (sizeof(Int) - 1) * CHAR_BIT; 
}

}

/*
namespace cpputil
{

// sign (portability issue)

template <typename _Int = int>
bool opposite_signs(_Int x, _Int y)
{
  return (x ^ y) < 0;
}

// abs (portability issue)

// min (portability issue)

// max (portability issue)

template <typename _Int = int>
bool is_power_of_2(_Int v)
{
  return (v & (v - 1)) == 0;
}

template <typename _Int = int>
bool is_power_of_2_ignore_0(_Int v)
{
  return v && !(v & (v - 1));
}

template <typename UInt = unsigned int>
void conditional_set(bool f, UInt m, UInt& w)
{
  w ^= (-f ^ w) & m;
}

template <typename UInt = unsigned int>
void conditional_set_superscalar(bool f, UInt m, UInt& w)
{
  w = (w & ~m) | (-f & m);
}

template <typename _Int = int>
_Int negate_if_false(bool f, _Int v)
{
  return (f ^ (f -1)) * v;
}

template <typename _Int = int>
_Int negate_if_true(bool f, _Int v)
{
  return (v ^ -f) + f;
}

template <typename UInt = unsigned int>
UInt merge_bits(UInt a, UInt b, UInt mask)
{
  return a ^ ((a ^ b) & mask);
} 

template <typename UInt = unsigned int>
bool parity_naive(UInt v)
{
  bool parity = false;
  while ( v )
  {
    parity = !parity;
    v = v & (v - 1); 
  }

  return parity;
}

template <typename _Int = int>
void swap_with_addition(_Int& a, _Int& b)
{
  (&(a) == &(b)) || (((a) -= (b)), ((b) += (a)), ((a) = (b) - (a)));
}

template <typename _Int>
void swap_with_xor(_Int& a, _Int& b)
{
  ((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b));
}

template <typename UInt = unsigned int>
void swap_bits_with_xor(UInt i, UInt j, UInt n, UInt b)
{
  UInt x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); 
  return b ^ ((x << i) | (x << j));
}

}
*/

#endif
