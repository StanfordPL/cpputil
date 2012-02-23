#include <cassert>
#include <iostream>

#include <stdint.h>

#include "cpputil/bits.h"

using namespace cpputil;
using namespace std;

int main()
{
  for ( uint8_t i = 0; i < 0xff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "8 bit tests passed!" << endl;

  for ( uint16_t i = 0x0100; i < 0x01ff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "16 bit tests passed!" << endl;

  for ( uint32_t i = 0x00010000; i < 0x000100ff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "32 bit tests passed!" << endl;

  for ( uint64_t i = 0x0000000100000000; i < 0x00000001000000ff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "64 bit tests passed!" << endl;

  int8_t i8 = 0xff;
  cout << hex << sign_extend<int16_t, int8_t>(i8) << endl;
  cout << hex << zero_extend<int16_t, int8_t>(i8) << endl;

  uint8_t u8 = 0xff;
  cout << hex << sign_extend<int16_t, uint8_t>(u8) << endl;
  cout << hex << zero_extend<int16_t, uint8_t>(u8) << endl;

  int64_t i64 = 0xffffffffffffffff;
  
  __int128_t i128_1 = zero_extend<__int128_t, int64_t>(i64);
  cout << hex << get_upper_half(i128_1) << " " << get_lower_half(i128_1) << endl;
  __int128_t i128_2 = zero_extend<__int128_t, int8_t>(i8);
  cout << hex << get_upper_half(i128_2) << " " << get_lower_half(i128_2) << endl;

  __int128_t i128_3 = i128_1 + i128_2;
  cout << hex << get_upper_half(i128_3) << " " << get_lower_half(i128_3) << endl;

  return 0;
}
