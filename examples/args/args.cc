#include <iostream>
#include <set>
#include <vector>
#include "include/args.h"

using namespace cpputil;
using namespace std;

auto& help_flag = FlagArg::create("h")
	.alternate("help");

auto& i = ValueArg<int>::create("i")
	.alternate("int")
	.usage("<int>")
	.default_val(10);

auto& d = FileArg<double>::create("d")
	.alternate("double")
	.usage("<double>")
	.default_val(1.0);

auto& is = ValueArg<vector<int>,SequenceArgReader<vector<int>>, 
      SequenceArgWriter<vector<int>>>::create("is")
    .default_val(vector<int>());

auto& cs = ValueArg<set<char>,AssociativeArgRangeReader<set<char>,'a','z'>,
      AssociativeArgWriter<set<char>>>::create("cs")
    .default_val(set<char>()); 

int main(int argc, char** argv) {
	Args::read(argc, argv);

	cout << "Usage:" << endl;
	cout << Args::usage(2) << endl;
	cout << endl;

	cout << "Values:" << endl;
	cout << endl;
	cout << Args::debug() << endl;
	cout << endl;

	cout << "Errors:" << endl;
	for ( auto i = Args::error_begin(), ie = Args::error_end(); i != ie; ++i )
		cout << (*i)->reason() << endl;
	cout << endl;

	cout << "Unrecognized options:" << endl;
	for ( auto i = Args::unrecognized_begin(), ie = Args::unrecognized_end(); i != ie; ++i )
		cout << *i << endl;
	cout << endl;

	cout << "Anonymous options:" << endl;
	for ( auto i = Args::anonymous_begin(), ie = Args::anonymous_end(); i != ie; ++i )
		cout << *i << endl;
	cout << endl;

	return 0;
}
