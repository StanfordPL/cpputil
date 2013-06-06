#include <iostream>

#include "src/thread.h"

using namespace cpputil;
using namespace std;

class PrintThread : public Thread {
	public:
		PrintThread() : Thread() { }

	protected:
		virtual void run() {
			for ( int i = 0; i < 10; ++i )
				cout << id() << ": " << i << endl;
		}
};

int main() {
	int N = 2;
	PrintThread ts[N];
	for ( int i = 0; i < N; ++i )
		ts[i].start();
	for ( int i = 0; i < N; ++i )
		ts[i].join();

  return 0;
}

