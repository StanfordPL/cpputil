#include <iostream>

#include "include/sig_handler.h"

using namespace cpputil;
using namespace std;

int main() {
	VerboseSegvHandler::install();
	int* v = 0;
	*v = 0;

	return 0;
}
