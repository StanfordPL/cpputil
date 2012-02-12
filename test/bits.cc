#include <cassert>
#include <iostream>

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

  for ( uint16_t i = 0; i < 0xffff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "16 bit tests passed!" << endl;

  for ( uint32_t i = 0; i < 0xffffffff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "32 bit tests passed!" << endl;

  for ( uint64_t i = 0xffffffff00000000; i < 0xffffffffffffffff; ++i )
  {
    assert(count_bits_naive(i) == count_bits_kernighan(i) && "Error in count_bits_kernighan()!");
    assert(count_bits_naive(i) == count_bits_best(i)      && "Error in count_bits_best()!");
  }
  cout << "64 bit tests passed!" << endl;

  cout << "I can't believe you ran this program for this long." << endl;

  return 0;
}
