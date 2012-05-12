#ifndef CPPUTIL_BITS_H
#define CPPUTIL_BITS_H

#include <array>
#include <climits>
#include <type_traits>

#include <stdint.h>

namespace 
{

// Static arrays with the lower n bits set to true

std::array<const int64_t, 64> lower_
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

// Static arrays with the upper n bits set to true

std::array<const int64_t, 64> upper_
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

// TODO: These should move out to traits.h

// Is this an signed type?

template <typename T> 
struct is_signed : public std::false_type {};

template <> struct is_signed<int8_t>     : public std::true_type {};
template <> struct is_signed<int16_t>    : public std::true_type {};
template <> struct is_signed<int32_t>    : public std::true_type {};
template <> struct is_signed<int64_t>    : public std::true_type {};
template <> struct is_signed<__int128_t> : public std::true_type {};

// Is this an unsigned type?

template <typename T>
struct is_unsigned : public std::false_type {};

template <> struct is_unsigned<uint8_t>     : public std::true_type {};
template <> struct is_unsigned<uint16_t>    : public std::true_type {};
template <> struct is_unsigned<uint32_t>    : public std::true_type {};
template <> struct is_unsigned<uint64_t>    : public std::true_type {};
template <> struct is_unsigned<__uint128_t> : public std::true_type {};

// Structs holding the basic signed/unsigned integer types

struct i8   { typedef int8_t     type; };
struct i16  { typedef int16_t    type; };
struct i32  { typedef int32_t    type; };
struct i64  { typedef int64_t    type; };
struct i128 { typedef __int128_t type; };

struct u8   { typedef uint8_t     type; };
struct u16  { typedef uint16_t    type; };
struct u32  { typedef uint32_t    type; };
struct u64  { typedef uint64_t    type; };
struct u128 { typedef __uint128_t type; };

// Twice the width of a type (preserves signedness)

template <typename T> struct double_width {};

template <>           struct double_width<int8_t>   : public i16  {};
template <>           struct double_width<int16_t>  : public i32  {};
template <>           struct double_width<int32_t>  : public i64  {};
template <>           struct double_width<int64_t>  : public i128 {};

template <>           struct double_width<uint8_t>  : public u16  {};
template <>           struct double_width<uint16_t> : public u32  {};
template <>           struct double_width<uint32_t> : public u64  {};
template <>           struct double_width<uint64_t> : public u128 {};

// Half the width of a type (preserves signedness)

template <typename T> struct half_width {};

template <>           struct half_width<int16_t>     : public i8  {};
template <>           struct half_width<int32_t>     : public i16 {};
template <>           struct half_width<int64_t>     : public i32 {};
template <>           struct half_width<__int128_t>  : public i64 {};

template <>           struct half_width<uint16_t>    : public u8  {};
template <>           struct half_width<uint32_t>    : public u16 {};
template <>           struct half_width<uint64_t>    : public u32 {};
template <>           struct half_width<__uint128_t> : public u64 {};

// The signed equivalent of a type

template <typename T> struct to_signed {};

template <>           struct to_signed<int8_t>      : public i8    {};
template <>           struct to_signed<int16_t>     : public i16   {};
template <>           struct to_signed<int32_t>     : public i32   {};
template <>           struct to_signed<int64_t>     : public i64   {};
template <>           struct to_signed<__int128_t>  : public i128  {};

template <>           struct to_signed<uint8_t>      : public i8   {};
template <>           struct to_signed<uint16_t>     : public i16  {};
template <>           struct to_signed<uint32_t>     : public i32  {};
template <>           struct to_signed<uint64_t>     : public i64  {};
template <>           struct to_signed<__uint128_t>  : public i128 {};

// The unsigned equivalent of a type

template <typename T> struct to_unsigned {};

template <>           struct to_unsigned<int8_t>      : public u8    {};
template <>           struct to_unsigned<int16_t>     : public u16   {};
template <>           struct to_unsigned<int32_t>     : public u32   {};
template <>           struct to_unsigned<int64_t>     : public u64   {};
template <>           struct to_unsigned<__int128_t>  : public u128  {};

template <>           struct to_unsigned<uint8_t>      : public u8   {};
template <>           struct to_unsigned<uint16_t>     : public u16  {};
template <>           struct to_unsigned<uint32_t>     : public u32  {};
template <>           struct to_unsigned<uint64_t>     : public u64  {};
template <>           struct to_unsigned<__uint128_t>  : public u128 {};

// Sign extend from one type to another
// TODO: Add checks for To being wider than From

template <typename To, typename From>
inline typename std::enable_if<is_signed<To>::value && is_signed<From>::value, To>::type sign_extend(From from)
{
  return (To) from;
}

template <typename To, typename From>
inline typename std::enable_if<is_signed<To>::value && is_unsigned<From>::value, To>::type sign_extend(From from)
{
  return (To) ((typename to_signed<From>::type) from);
}

template <typename To, typename From>
inline typename std::enable_if<is_unsigned<To>::value && is_signed<From>::value, To>::type sign_extend(From from)
{
  return (To) ((typename to_signed<To>::type) from);
}

template <typename To, typename From>
inline typename std::enable_if<is_unsigned<To>::value && is_unsigned<From>::value, To>::type sign_extend(From from)
{
  return (To) ((typename to_signed<To>::type) ((typename to_signed<From>::type) from));
}

// Zero extend from one type to another
// TODO: Add checks for To being wider than From

template <typename To, typename From>
inline typename std::enable_if<is_signed<From>::value, To>::type zero_extend(From from)
{
  return (To) ((typename to_unsigned<From>::type) from);
}

template <typename To, typename From>
inline typename std::enable_if<is_unsigned<From>::value, To>::type zero_extend(From from)
{
  return (To) from;
}

// Access the nth bit (static and dynamic versions)

template <typename Int, uint8_t n>
inline bool get_bit(Int x)
{
  return (x >> n) & 1;
}

template <typename Int>
inline bool get_bit(Int x, uint8_t n)
{
  return (x >> n) & 1;
}

// Set the nth bit (static and dynamic versions)

template <typename Int, uint8_t n>
inline void set_bit(Int& x)
{
  x = x | (1 << n);
}

template <typename Int>
inline void set_bit(Int& x, uint8_t n)
{
  x = x | (1 << n);
}

// Clears the nth bit (static and dynamic versions)

template <typename Int, uint8_t n>
inline void flip_bit(Int& x)
{
  x = x & ~(1 << n);
}

template <typename Int>
inline void flip_bit(Int& x, uint8_t n)
{
  x = x & ~(1 << n);
}

// Flip the nth bit (static and dynamic versions)

template <typename Int, uint8_t n>
inline void flip_bit(Int& x)
{
  x = x ^ (1 << n);
}

template <typename Int>
inline void flip_bit(Int& x, uint8_t n)
{
  x = x ^ (1 << n);
}

// Most/least signficant bits

template <typename Int>
inline bool msb(Int x)
{
  return get_bit<Int, sizeof(Int) * CHAR_BIT - 1>(x);
}

template <typename Int>
inline bool lsb(Int x) 
{ 
  return get_bit<Int, 0>(x);
}

// Upper / lower halves

template <typename Int>
inline typename half_width<Int>::type get_upper_half(Int x)
{
  return x >> (sizeof(typename half_width<Int>::type) * CHAR_BIT); 
}

template <typename Int>
inline typename half_width<Int>::type get_lower_half(Int x)
{
  return (typename half_width<Int>::type) x;
}

// Bit masking

inline void set_upper_n(int8_t&  x, uint8_t  n) { x |= (int8_t)  upper_[n-1+56]; }
inline void set_upper_n(int16_t& x, uint16_t n) { x |= (int16_t) upper_[n-1+48]; }
inline void set_upper_n(int32_t& x, uint32_t n) { x |= (int32_t) upper_[n-1+32]; }
inline void set_upper_n(int64_t& x, uint64_t n) { x |= (int64_t) upper_[n-1];    }

inline void set_upper_n(uint8_t&  x, uint8_t  n) { x |= (uint8_t)  upper_[n-1+56]; }
inline void set_upper_n(uint16_t& x, uint16_t n) { x |= (uint16_t) upper_[n-1+48]; }
inline void set_upper_n(uint32_t& x, uint32_t n) { x |= (uint32_t) upper_[n-1+32]; }
inline void set_upper_n(uint64_t& x, uint64_t n) { x |= (uint64_t) upper_[n-1];    }

inline void set_lower_n(int8_t&  x, uint8_t  n) { x |= (int8_t)  lower_[n-1]; }
inline void set_lower_n(int16_t& x, uint16_t n) { x |= (int16_t) lower_[n-1]; }
inline void set_lower_n(int32_t& x, uint32_t n) { x |= (int32_t) lower_[n-1]; }
inline void set_lower_n(int64_t& x, uint64_t n) { x |= (int64_t) lower_[n-1]; }

inline void set_lower_n(uint8_t&  x, uint8_t  n) { x |= (uint8_t)  lower_[n-1]; }
inline void set_lower_n(uint16_t& x, uint16_t n) { x |= (uint16_t) lower_[n-1]; }
inline void set_lower_n(uint32_t& x, uint32_t n) { x |= (uint32_t) lower_[n-1]; }
inline void set_lower_n(uint64_t& x, uint64_t n) { x |= (uint64_t) lower_[n-1]; }

// Bit counting

template <typename UInt = uint64_t>
uint8_t count_bits_naive(UInt v)
{
  uint8_t c = 0;
  for ( ; v; v >>= 1 )
    c += v & 1;

  return c;
}

template <typename UInt = uint64_t>
uint8_t count_bits_kernighan(UInt v)
{
  uint8_t c = 0;
  for ( ; v; c++ )
    v &= v - 1;

  return c;
}

template <typename UInt = uint64_t>
uint8_t count_bits_best(UInt v)
{
  v = v - ((v >> 1) & (UInt)~(UInt)0/3);                         
  v = (v & (UInt)~(UInt)0/15*3) + ((v >> 2) & (UInt)~(UInt)0/15*3);     
  v = (v + (v >> 4)) & (UInt)~(UInt)0/255*15;                      
  return (UInt)(v * ((UInt)~(UInt)0/255)) >> (sizeof(UInt) - 1) * CHAR_BIT; 
}

// NOTE: Below this point begins the structure of what I'd like this header to ultimate look like.
//       First a reference implementation, and then successive refinements.
//       A test harness can verify that all implementations produce identical values.
//
//       Where possible, I'd like to include references to the hacker's delight book in the documentation.

// pop -- Population count (number of one bits)
// Hacker's Delight chapter 5

// Reference implementation 

template <typename T>
uint8_t pop_ref(T x)
{
  uint8_t c = 0;
  for ( ; x; x >>= 1 )
    c += x & 1;

  return c;
}

// parity 
// Hacker's Delight chapter 5

// Reference implementation

template <typename T>
uint8_t parity_ref(T x)
{
  return pop_ref(x) % 2;
}

// nlz -- number of leading zeros
// Hacker's Delight chapter 5

// Reference implementation

template <typename T>
uint8_t nlz_ref(T x)
{
  uint8_t c = 0;
  for ( ; x && (x & 1) == 0; x >>= 1 )
    c++;

  return c;
}

// ntz -- number of trailing zeros
// Hacker's Delight chapter 5

// Reference implementation

template <typename T>
uint8_t ntz_ref(T x)
{
  return pop_ref(~x & (x-1));  
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
