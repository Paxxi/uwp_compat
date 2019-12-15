#pragma once

#ifdef MS_APP
#include <winrt/base.h>

wchar_t* hstring_to_wstring(const winrt::hstring&& hstr);
char* hstring_to_cstring(const winrt::hstring&& hstr);
char* wstring_to_cstring(wchar_t* wstr);

#endif
