#ifndef CPPUTIL_BITS_H
#define CPPUTIL_BITS_H

#include <array>

#include <stdint.h>

namespace 
{

std::array<const int64_t, 64> lower_64_
{{
  0x0000000000000001, 0x0000000000000003, 0x0000000000000007, 0x000000000000000f,
  0x000000000000001f, 0x000000000000003f, 0x000000000000007f, 0x00000000000000ff,
  0x00000000000001ff, 0x00000000000003ff, 0x00000000000007ff, 0x0000000000000fff,
  0x0000000000001fff, 0x0000000000003fff, 0x0000000000007fff, 0x000000000000ffff,
  0x000000000001ffff, 0x000000000003ffff, 0x000000000007ffff, 0x00000000000fffff,
  0x00000000001fffff, 0x00000000003fffff, 0x00000000007fffff, 0x0000000000ffffff,
  0x0000000001ffffff, 0x0000000003ffffff, 0x0000000007ffffff, 0x000000000fffffff,
  0x000000001fffffff, 0x000000003fffffff, 0x000000007fffffff, 0x00000000ffffffff,
  0x00000001ffffffff, 0x00000003ffffffff, 0x00000007ffffffff, 0x0000000fffffffff,
  0x0000001fffffffff, 0x0000003fffffffff, 0x0000007fffffffff, 0x000000ffffffffff,
  0x000001ffffffffff, 0x000003ffffffffff, 0x000007ffffffffff, 0x00000fffffffffff,
  0x00001fffffffffff, 0x00003fffffffffff, 0x00007fffffffffff, 0x0000ffffffffffff,
  0x0001ffffffffffff, 0x0003ffffffffffff, 0x0007ffffffffffff, 0x000fffffffffffff,
  0x001fffffffffffff, 0x003fffffffffffff, 0x007fffffffffffff, 0x00ffffffffffffff,
  0x01ffffffffffffff, 0x03ffffffffffffff, 0x07ffffffffffffff, 0x0fffffffffffffff,
  0x1fffffffffffffff, 0x3fffffffffffffff, 0x7fffffffffffffff, 0xffffffffffffffff
}};

std::array<const int64_t, 64> upper_64_
{{
  0x8000000000000000, 0xc000000000000000, 0xe000000000000000, 0xf000000000000000, 
  0xf800000000000000, 0xfc00000000000000, 0xfe00000000000000, 0xff00000000000000, 
  0xff80000000000000, 0xffc0000000000000, 0xffe0000000000000, 0xfff0000000000000, 
  0xfff8000000000000, 0xfffc000000000000, 0xfffe000000000000, 0xffff000000000000, 
  0xffff800000000000, 0xffffc00000000000, 0xffffe00000000000, 0xfffff00000000000, 
  0xfffff80000000000, 0xfffffc0000000000, 0xfffffe0000000000, 0xffffff0000000000, 
  0xffffff8000000000, 0xffffffc000000000, 0xffffffe000000000, 0xfffffff000000000, 
  0xfffffff800000000, 0xfffffffc00000000, 0xfffffffe00000000, 0xffffffff00000000, 
  0xffffffff80000000, 0xffffffffc0000000, 0xffffffffe0000000, 0xfffffffff0000000, 
  0xfffffffff8000000, 0xfffffffffc000000, 0xfffffffffe000000, 0xffffffffff000000, 
  0xffffffffff800000, 0xffffffffffc00000, 0xffffffffffe00000, 0xfffffffffff00000, 
  0xfffffffffff80000, 0xfffffffffffc0000, 0xfffffffffffe0000, 0xffffffffffff0000, 
  0xffffffffffff8000, 0xffffffffffffc000, 0xffffffffffffe000, 0xfffffffffffff000, 
  0xfffffffffffff800, 0xfffffffffffffc00, 0xfffffffffffffe00, 0xffffffffffffff00, 
  0xffffffffffffff80, 0xffffffffffffffc0, 0xffffffffffffffe0, 0xfffffffffffffff0, 
  0xfffffffffffffff8, 0xfffffffffffffffc, 0xfffffffffffffffe, 0xffffffffffffffff 
}};

}

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
inline bool get_bit(Int x)
{
  return (x >> n) & 1;
}

template <typename Int, unsigned int CHAR_BIT = 8>
inline bool msb(Int x)
{
  return get_bit<Int, sizeof(Int)*CHAR_BIT-1>(x);
}

template <typename Int>
inline bool lsb(Int x) 
{ 
  return get_bit<Int, 0>(x);
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

inline int64_t lower_64(int n) { return           lower_64_[n-1];    }
inline int32_t lower_32(int n) { return (int32_t) lower_64_[n-1];    }
inline int16_t lower_16(int n) { return (int16_t) lower_64_[n-1];    }
inline int8_t  lower_8 (int n) { return (int8_t)  lower_64_[n-1];    }

inline int64_t upper_64(int n) { return           upper_64_[n-1];    }
inline int32_t upper_32(int n) { return (int32_t) upper_64_[n-1+32]; }
inline int16_t upper_16(int n) { return (int16_t) upper_64_[n-1+48]; }
inline int8_t  upper_8 (int n) { return (int8_t)  upper_64_[n-1+56]; }

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
