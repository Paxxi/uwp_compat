#include <uwp_compat/encoding.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <cstdlib>
#include <cstring>

#include <winrt/base.h>

wchar_t* to_utf16(const char* str, size_t length)
{
  if (str == nullptr)
    return nullptr;

  if (length <= 0)
    length = strlen(str);

  int result = MultiByteToWideChar(CP_UTF8, 0, str, static_cast<int>(length), NULL, 0);
  if (result == 0)
    return NULL;

  length = static_cast<size_t>(result) + 1;
  wchar_t* strW = reinterpret_cast<wchar_t*>(std::malloc(length * sizeof(wchar_t)));
  if (strW == nullptr)
    return nullptr;

  result = MultiByteToWideChar(CP_UTF8, 0, str, result, strW, static_cast<int>(length));

  if (result == 0)
  {
    free(strW);
    return NULL;
  }

  if (strW[length - 1] != '\0')
    strW[length - 1] = '\0';

  return strW;
}

char* to_utf8(const wchar_t* str, size_t length)
{
  if (str == nullptr)
    return nullptr;

  if (length <= 0)
    length = wcslen(str);

  int result = WideCharToMultiByte(CP_UTF8, 0, str, static_cast<int>(length), NULL, 0, NULL, NULL);
  if (result == 0)
    return NULL;

  int required = result + 1;
  char *newStr = reinterpret_cast<char*>(std::malloc(required));
  if (newStr == nullptr)
    return nullptr;

  result = WideCharToMultiByte(CP_UTF8, 0, str, static_cast<int>(length), newStr, required, NULL, NULL);
  if (result == 0)
  {
    std::free(newStr);
    return NULL;
  }

  if (newStr[required - 1] != '\0')
    newStr[required - 1] = '\0';
  
  return newStr;
}

wchar_t* hstring_to_wstring(const winrt::hstring&& hstr)
{
  uint32_t length_with_null = hstr.size() + 1;
  auto cstr = reinterpret_cast<wchar_t*>(std::malloc(length_with_null * sizeof(wchar_t)));
  if (!cstr)
    return nullptr;

  if (!wcsncpy_s(cstr, length_with_null, hstr.c_str(), hstr.size()))
  {
    std::free(cstr);
    cstr = nullptr;
  }

  return cstr;
}

char* hstring_to_cstring(const winrt::hstring&& hstr)
{
  return to_utf8(hstr.c_str(), hstr.size());
}

char* wstring_to_cstring(wchar_t* wstr)
{
  if (!wstr)
    return nullptr;

  auto cstr = to_utf8(wstr, -1);
  std::free(wstr);

  return cstr;
}
