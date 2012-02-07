#ifndef BITS_H
#define BITS_H

#include <stdint.h>

namespace 
{

const unsigned char BitsSetTable256[256] =
{
  #define B2(n) n,     n+1,     n+1,     N+2
  #define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
  #define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
                B6(0), B6(1),   B6(1),   B6(2) 
  #undef B6
  #undef B4
  #undef B2
};

}

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

template <typename _UInt = unsigned int>
void conditional_set(bool f, _UInt m, _UInt& w)
{
  w ^= (-f ^ w) & m;
}

template <typename _UInt = unsigned int>
void conditional_set_superscalar(bool f, _UInt m, _UInt& w)
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

template <typename _UInt = unsigned int>
_UInt merge_bits(_UInt a, _UInt b, _UInt mask)
{
  return a ^ ((a ^ b) & mask);
} 

template <typename _UInt = unsigned int>
_UInt count_bits_naive(_UInt v)
{
  _UInt c = 0;
  for ( ; v; v >>= 1 )
    c += v & 1;

  return c;
}

template <typename _UInt = unsigned int>
_UInt count_bits_lookup_v1(uint32_t v)
{
  return BitsSetTable256[v & 0xff] +
         BitsSetTable256[(v >> 8) & 0xff] +
         BitsSetTable256[(v >> 16) & 0xff] +
         BitsSetTable256[v >> 24];
}

template <typename _UInt = unsigned int>
_UInt count_bits_lookup_v2(uint32_t v)
{
  unsigned char* p = (unsigned char*) &v;
  return BitsSetTable256[p[0]] +
         BitsSetTable256[p[1]] +
         BitsSetTable256[p[2]] +
         BitsSetTable256[p[3]];
}

template <typename _UInt = unsigned int>
_UInt count_bits_kernighan(_UInt v)
{
  _UInt c = 0;
  for ( ; v; c++ )
    v &= v - 1;

  return c;
}

template <typename _UInt = unsigned int, int CHAR_BIT = 8>
_UInt count_bits_best(_UInt v)
{
  v = v - ((v >> 1) & (_UInt)~(_UInt)0/3);                         
  v = (v & (_UInt)~(_UInt)0/15*3) + ((v >> 2) & (_UInt)~(_UInt)0/15*3);     
  v = (v + (v >> 4)) & (_UInt)~(_UInt)0/255*15;                      
  return (_UInt)(v * ((_UInt)~(_UInt)0/255)) >> (sizeof(_UInt) - 1) * CHAR_BIT; 
}

template <typename _UInt = unsigned int>
bool parity_naive(_UInt v)
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

template <typename _UInt = unsigned int>
void swap_bits_with_xor(_UInt i, _UInt j, _UInt n, _UInt b)
{
  _UInt x = ((b >> i) ^ (b >> j)) & ((1U << n) - 1); 
  return b ^ ((x << i) | (x << j));
}
























}

#endif
