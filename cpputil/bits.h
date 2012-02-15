#ifndef CPPUTIL_BITS_H
#define CPPUTIL_BITS_H

#include <stdint.h>

namespace cpputil
{

template <typename UInt = unsigned int>
uint8_t count_bits_naive(UInt v)
{
  uint8_t c = 0;
  for ( ; v; v >>= 1 )
    c += v & 1;

  return c;
}

template <typename UInt = unsigned int>
uint8_t count_bits_kernighan(UInt v)
{
  uint8_t c = 0;
  for ( ; v; c++ )
    v &= v - 1;

  return c;
}

template <typename UInt = unsigned int, int CHAR_BIT = 8>
uint8_t count_bits_best(UInt v)
{
  v = v - ((v >> 1) & (UInt)~(UInt)0/3);                         
  v = (v & (UInt)~(UInt)0/15*3) + ((v >> 2) & (UInt)~(UInt)0/15*3);     
  v = (v + (v >> 4)) & (UInt)~(UInt)0/255*15;                      
  return (UInt)(v * ((UInt)~(UInt)0/255)) >> (sizeof(UInt) - 1) * CHAR_BIT; 
}

template <typename Int, uint8_t bit>
inline bool bit(Int x)
{
  return (x >> bit) & 1;
}

template <typename Int, int CHAR_BIT = 8>
inline bool msb(Int x)
{
  return bit<Int, sizeof(Int)*CHAR_BIT-1>(x);
}

template <typename Int>
inline bool lsb(Int x) 
{ 
  return bit<Int, 0>(x);
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
