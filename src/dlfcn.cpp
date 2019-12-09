#include <uwp_compat/dlfcn.h>
#include <uwp_compat/encoding.h>
#include <uwp_compat/path.h>

#include <cstdlib>

void* dlopen(const char* filename, int flag)
{
  if (!filename)
    return nullptr;

  wchar_t* fname = to_utf16(filename, -1);
  if (!fname)
    return nullptr;

  wchar_t* base_path = uwp_executable_directory_u16();
  if (!base_path)
  {
    std::free(fname);
    return nullptr;
  }

  uwp_fix_slash_u16(fname, -1);
  
  size_t bplength = wcslen(base_path);
  wchar_t* start = fname;
  if (_wcsnicmp(fname, base_path, bplength))
    start = fname + bplength + 1; // Skip over last \

  std::free(base_path);

  HMODULE hmod = LoadPackagedLibrary(start, 0);
  std::free(fname);

  return static_cast<void*>(hmod);
}

char* dlerror()
{
  return "";
}

void* dlsym(void* handle, const char* symbol)
{
  auto h = static_cast<HMODULE>(handle);
  if (!h || !symbol)
    return nullptr;

  return static_cast<void*>(GetProcAddress(h, symbol));
}

int dlclose(void* handle)
{
  auto h = static_cast<HMODULE>(handle);
  if (!h)
    return -1;

  return FreeLibrary(h) == TRUE ? 0 : -1;
}
