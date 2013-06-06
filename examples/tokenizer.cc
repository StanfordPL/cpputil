#include <iostream>
#include <string>

#include "src/tokenizer.h"

using namespace cpputil;
using namespace std;

int main() {
  Tokenizer<string> t;
	t.tokenize("Hello");
	t.tokenize("world");

	cout << "Should print \"Hello world\": ";
	cout << *t.untokenize(0) << " " << *t.untokenize(1) << endl;

	for ( int n = 0; n < 2; ++n ) {
		cout << "Tokenized strings: (" << t.size() << ") [";
			for ( const auto& itr : t )
				cout << itr << " ";
		cout << "]" << endl;

		t.clear();
	}

  return 0;
}

