#include <uwp_compat/uwp_compat.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

int getpid()
{
  return GetCurrentProcessId();
}
