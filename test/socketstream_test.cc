#include <unistd.h>

#include <cassert>
#include <cstdlib>

#include <iostream>

#include "socketstream.h"

using namespace std;

int main(int argc, char** argv)
{
  if ( fork() == 0 )
  {
    socketstreamserver server(atoi(argv[0]));
    while ( true )
    {
      socketstream ss;
      string s;

      server.accept(ss);
      ss >> s;
      ss << "ECHO";
    }
  }
  else
    while ( true )
    {
      socketstream ss("localhost", atoi(argv[0]));
      string s;
    
      cout << "Enter: ";
      cin >> s;

      ss << s << endl;
      ss >> s;

      cout << "Received [" << s << "]" << endl;
    }
    
  return 0;
}
