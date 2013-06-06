#include <iostream>

#include "cpputil/stream/nullstream.h"

using namespace cpputil;
using namespace std;

void print(ostream& os)
{
	os << "You shouldn't see this." << endl;
}

int main()
{
  onullstream os(cout);

  os << "You shouldn't see this." << endl;
	print(os);

	cout << "If you didn't see it, this works." << endl;

  return 0;
}


