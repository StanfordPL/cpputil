#include <iostream>

#include "src/timer.h"

using namespace cpputil;
using namespace std;

int main() {
	Timer t;
	t.start();
	for ( int i = 0; i < 12345678; ++i );
	t.stop();

	cout << t.sec() << " seconds elapsed" << endl;
	cout << t.nsec() << " nanoseconds elapsed" << endl;

  return 0;
}

