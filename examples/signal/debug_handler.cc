#include <iostream>

#include "include/signal/debug_handler.h"

using namespace cpputil;
using namespace std;

int main() {
	DebugHandler dh;
	dh.install_sigsegv();

	int* v = 0;
	*v = 0;

	return 0;
}
