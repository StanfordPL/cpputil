#include <iostream>

#include "cpputil/stream/noopstream.h"
#include "cpputil/timer.h"

using namespace cpputil;
using namespace std;

struct C
{
	int x_, y_, z_;
};
istream& operator>>(istream& is, C& c) { is >> c.x_ >> c.y_ >> c.z_; return is; }
ostream& operator<<(ostream& os, const C& c) { os << c.x_ << c.y_ << c.z_ << endl; return os; }

int main()
{
	inoopstream ins(cin.rdbuf());
	Timer t1, t2;
	
	t1.start();
	for ( int itr = 0; itr < 1e9; ++itr )
	{
		bool b;
		ins >> b;
		short s;
		ins >> s;
		unsigned short us;
		ins >> us;
		int i;
		ins >> i;
		unsigned int ui;
		ins >> ui;
		long l;
		ins >> l;
		unsigned long ul;
		ins >> ul;
		float f;
		ins >> f;
		double d;
		ins >> d;
		long double ld;
		ins >> ld;
		void* v;
		ins >> v;
		ins >> cin.rdbuf();
		ins >> cin;

		char c;
		ins >> c;
		signed char sc;
		ins >> sc;
		unsigned char uc;
		ins >> uc;
		char* ch;
		ins >> ch;
		signed char* scp;
		ins >> scp;
		unsigned char* ucp;
		ins >> ucp;

		C udt;
		ins >> udt;
	}
	t1.stop();

	t2.start();
	for ( int itr = 0; itr < 1e9; ++itr );
	t2.stop();

	onoopstream ons(cout.rdbuf());
	Timer t3, t4;
	
	t3.start();
	for ( int itr = 0; itr < 1e9; ++itr )
	{
		bool b;
		ons << b;
		short s;
		ons << s;
		unsigned short us;
		ons << us;
		int i;
		ons << i;
		unsigned int ui;
		ons << ui;
		long l;
		ons << l;
		unsigned long ul;
		ons << ul;
		float f;
		ons << f;
		double d;
		ons << d;
		long double ld;
		ons << ld;
		void* v;
		ons << v;
		ons << cout.rdbuf();
		ons << cout;

		char c;
		ons << c;
		signed char sc;
		ons << sc;
		unsigned char uc;
		ons << uc;
		char* ch;
		ons << ch;
		signed char* scp;
		ons << scp;
		unsigned char* ucp;
		ons << ucp;

		C udt;
		ons << udt;
	}
	t3.stop();

	t4.start();
	for ( int itr = 0; itr < 1e9; ++itr );
	t4.stop();

	cout << "-> If you didn't have to type anything, input works in principle." << endl;
	cout << "-> If you didn't see any crazy values printed, output works in principle." << endl;
	cout << "-> If these times look about the same, the compiler is eliminating basically everything." << endl;
	cout << endl;
	cout << "Input Runtime: " << t1.nsec() << " ns" << endl;
	cout << "Input Control: " << t2.nsec() << " ns" << endl;
	cout << endl;
	cout << "Output Runtime: " << t3.nsec() << " ns" << endl;
	cout << "Output Control: " << t4.nsec() << " ns" << endl;

	return 0;
}

