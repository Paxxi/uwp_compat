#pragma once

#ifdef __cplusplus
extern "C" {
#endif

  wchar_t* to_utf16(const char* str, size_t length);

  char* to_utf8(const wchar_t* str, size_t length);

#ifdef __cplusplus
}
#endif
