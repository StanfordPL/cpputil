#include <iostream>

#include "cpputil/stream/shuntstream.h"

using namespace cpputil;
using namespace std;

void print_nonsense(ostream& os)
{
	os << "Are you jaking me sideways while pumping my gas!?" << endl;
}

int main()
{
  oshuntstream os(cout);

  os << "You should see this" << endl;
  os << close << open << close;

  os << "You shouldn't see this" << endl;
	print_nonsense(os);

  os << open;
  os << "You should see this" << endl;

	os << close;
	cout << "You should see this" << endl;

  return 0;
}
