#include <iostream>

#include "cpputil/stream/redactstream.h"

using namespace cpputil;
using namespace std;

void print_secret(ostream& os)
{
	os << "Are you jaking me sideways while pumping my gas!?" << endl;
}

int main()
{
  oredactstream os(cout);

  os << "You should see this" << endl;
  os << redact << unredact << redact;

  os << "You shouldn't see this" << endl;
	print_secret(os);

  os << unredact;
  os << "You should see this" << endl;

	os << redact;
	cout << "You should see this" << endl;

  return 0;
}
