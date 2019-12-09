#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

  char* uwp_executable_directory_u8();
  wchar_t* uwp_executable_directory_u16();
  void uwp_fix_slash_u16(wchar_t* str, size_t length);

#ifdef __cplusplus
}
#endif
