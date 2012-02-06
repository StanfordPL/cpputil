#ifndef CPPUTIL_SYSTEM_DAEMON_H
#define CPPUTIL_SYSTEM_DAEMON_H

#include <cstdio>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace cpputil
{

inline void daemonize(const char* dir, int success, int failure)
{
  pid_t pid = fork();
  if ( pid < 0 )
    exit(failure);
  else if ( pid > 0 )
    exit(success);

  umask(0);
  
  if ( setsid() < 0 )
    exit(failure);

  if ( chdir(dir) < 0 )
    exit(failure);

  auto r1 = freopen("/dev/null", "r", stdin);  (void) r1;
  auto r2 = freopen("/dev/null", "w", stdout); (void) r2;
  auto r3 = freopen("/dev/null", "w", stderr); (void) r3;
} 

}

#endif
