#ifndef DAEMON_H
#define DAEMON_H

#include <cunistd>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>

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

  freopen("/dev/null", "r", stdin);
  freopen("/dev/null", "w", stdout);
  freopen("/dev/null", "w", stderr);
} 

}

#endif
