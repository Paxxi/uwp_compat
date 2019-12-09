#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif
  void* dlopen(const char* filename, int flag);
  char* dlerror(void);
  void* dlsym(void* handle, const char* symbol);
  int dlclose(void* handle);
#ifdef __cplusplus
}
#endif
