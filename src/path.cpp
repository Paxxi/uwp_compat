#include <uwp_compat/path.h>
#include <uwp_compat/encoding.h>
#include "internal.hpp"

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <winrt/Windows.Storage.h>

#include <limits>
#include <cstdlib>
#include <cstdint>

using winrt::Windows::Storage::AppDataPaths;
using winrt::Windows::Storage::KnownFolders;
using winrt::Windows::Storage::KnownFolderId;
using winrt::Windows::Storage::SystemDataPaths;
using winrt::Windows::Storage::UserDataPaths;

wchar_t* uwp_executable_directory_u16()
{
  size_t bufLength = 128;
  wchar_t* path = nullptr;
  do
  {
    bufLength *= 2;
    path = reinterpret_cast<wchar_t*>(std::malloc(bufLength * sizeof(wchar_t)));
    if (!path)
      return nullptr;

    DWORD result = GetModuleFileNameW(nullptr, path, static_cast<DWORD>(bufLength));
    if (result > 0 && GetLastError() == ERROR_SUCCESS)
    {
      break;
    }
    else if (result > 0)
    {
      std::free(path);
      path = nullptr;
    }
    else if (result == 0)
    {
      std::free(path);
      return nullptr;
    }
  } while (bufLength < std::numeric_limits<int16_t>::max());

  if (path == nullptr)
    return nullptr;

  wchar_t* result = wcsrchr(path, L'\\');
  if (result)
  {
    result++;
    result = L'\0';
  }

  return path;
}

char* uwp_executable_directory_u8()
{
  wchar_t* pathW = uwp_executable_directory_u16();
  if (!pathW)
    return nullptr;

  char* path = to_utf8(pathW, -1);
  std::free(pathW);
  
  return path;
}

void uwp_fix_slash_u16(wchar_t* str, size_t length)
{
  if (!str)
    return;

  if (length <= 0)
    length = wcslen(str);

  for (int i = 0; i < length; ++i)
  {
    if (str[i] == L'/')
      str[i] = L'\\';
  }
}

wchar_t* uwp_get_fonts_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().Fonts());
}

char* uwp_get_fonts_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().Fonts());
}

wchar_t* uwp_get_programdata_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().ProgramData());
}

char* uwp_get_programdata_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().ProgramData());
}

wchar_t* uwp_get_public_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().Public());
}

char* uwp_get_public_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().Public());
}

wchar_t* uwp_get_publicdesktop_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().PublicDesktop());
}

char* uwp_get_publicdesktop_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().PublicDesktop());
}

wchar_t* uwp_get_publicdocuments_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().PublicDocuments());
}

char* uwp_get_publicdocuments_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().PublicDocuments());
}

wchar_t* uwp_get_publicdownloads_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().PublicDownloads());
}

char* uwp_get_publicdownloads_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().PublicDownloads());
}

wchar_t* uwp_get_publicmusic_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().PublicMusic());
}

char* uwp_get_publicmusic_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().PublicMusic());
}

wchar_t* uwp_get_publicpictures_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().PublicPictures());
}

char* uwp_get_publicpictures_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().PublicPictures());
}

wchar_t* uwp_get_publicvideos_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().PublicVideos());
}

char* uwp_get_publicvideos_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().PublicVideos());
}

wchar_t* uwp_get_system_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().System());
}

char* uwp_get_system_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().System());
}

wchar_t* uwp_get_systemarm_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().SystemArm());
}

char* uwp_get_systemarm_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().SystemArm());
}

wchar_t* uwp_get_systemhost_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().SystemHost());
}

char* uwp_get_systemhost_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().SystemHost());
}

wchar_t* uwp_get_systemx64_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().SystemX64());
}

char* uwp_get_systemx64_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().SystemX64());
}

wchar_t* uwp_get_systemx86_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().SystemX86());
}

char* uwp_get_systemx86_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().SystemX86());
}

wchar_t* uwp_get_userprofiles_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().UserProfiles());
}

char* uwp_get_userprofiles_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().UserProfiles());
}

wchar_t* uwp_get_windows_u16()
{
  return hstring_to_wstring(SystemDataPaths::GetDefault().Windows());
}

char* uwp_get_windows_u8()
{
  return hstring_to_cstring(SystemDataPaths::GetDefault().Windows());
}

 wchar_t* uwp_get_cameraroll_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().CameraRoll());
 }

 char* uwp_get_cameraroll_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().CameraRoll());
 }

 wchar_t* uwp_get_cookies_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Cookies());
 }

 char* uwp_get_cookies_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Cookies());
 }

 wchar_t* uwp_get_desktop_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Desktop());
 }

 char* uwp_get_desktop_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Desktop());
 }

 wchar_t* uwp_get_documents_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Documents());
 }

 char* uwp_get_documents_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Documents());
 }

 wchar_t* uwp_get_favorites_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Favorites());
 }

 char* uwp_get_favorites_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Favorites());
 }

 wchar_t* uwp_get_history_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().History());
 }

 char* uwp_get_history_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().History());
 }

 wchar_t* uwp_get_internetcache_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().InternetCache());
 }

 char* uwp_get_internetcache_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().InternetCache());
 }

 wchar_t* uwp_get_localappdata_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().LocalAppData());
 }

 char* uwp_get_localappdata_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().LocalAppData());
 }

 wchar_t* uwp_get_localappdatalow_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().LocalAppDataLow());
 }

 char* uwp_get_localappdatalow_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().LocalAppDataLow());
 }

 wchar_t* uwp_get_music_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Music());
 }

 char* uwp_get_music_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Music());
 }

 wchar_t* uwp_get_pictures_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Pictures());
 }

 char* uwp_get_pictures_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Pictures());
 }

 wchar_t* uwp_get_profile_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Profile());
 }

 char* uwp_get_profile_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Profile());
 }

 wchar_t* uwp_get_recent_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Recent());
 }

 char* uwp_get_recent_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Recent());
 }

 wchar_t* uwp_get_roamingappdata_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().RoamingAppData());
 }

 char* uwp_get_roamingappdata_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().RoamingAppData());
 }

 wchar_t* uwp_get_savedpictures_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().SavedPictures());
 }

 char* uwp_get_savedpictures_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().SavedPictures());
 }

 wchar_t* uwp_get_screenshots_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Screenshots());
 }

 char* uwp_get_screenshots_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Screenshots());
 }

 wchar_t* uwp_get_templates_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Templates());
 }

 char* uwp_get_templates_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Templates());
 }

 wchar_t* uwp_get_videos_u16()
 {
   return hstring_to_wstring(UserDataPaths::GetDefault().Videos());
 }

 char* uwp_get_videos_u8()
 {
   return hstring_to_cstring(UserDataPaths::GetDefault().Videos());
 }
