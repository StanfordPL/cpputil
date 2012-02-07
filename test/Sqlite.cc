#include <iostream>

#include "cpputil/Sqlite.h"

using namespace cpputil;
using namespace std;

int main()
{
  Sqlite s("foo.db");

  s.query("DROP TABLE R;");
  s.query("CREATE TABLE R(x INTEGER, y INTEGER);");
  
  s.query("INSERT INTO R VALUES(1, 2);");
  s.query("INSERT INTO R VALUES(2, 3);");
  s.query("INSERT INTO R VALUES(3, 4);");

  // Should print 1 2, 2 3, 3 4
  s.query("SELECT * FROM R;");
  for ( auto i = s.begin(), ie = s.end(); i != ie; ++i )
  {
    for ( auto j = (*i).begin(), je = (*i).end(); j != je; ++j )
      cout << (*j) << " ";
    cout << endl;
  }

  return 0;
}
