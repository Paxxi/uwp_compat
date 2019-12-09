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

// wchar_t* uwp_get_documents_u16()
// {
//   return hstring_to_wstring(KnownFolders::GetFolderForUserAsync(nullptr, KnownFolderId::DocumentsLibrary).get().Path());
//   return hstring_to_wstring(KnownFolders::DocumentsLibrary().Path());
// }

// char* uwp_get_documents_u8()
// {
//   return hstring_to_cstring(KnownFolders::DocumentsLibrary().Path());
// }

// wchar_t* uwp_get_cameraroll_u16()
// {
//   return hstring_to_wstring(KnownFolders::CameraRoll().Path());
// }

// char* uwp_get_cameraroll_u8()
// {
//   return hstring_to_cstring(KnownFolders::CameraRoll().Path());
// }

// wchar_t* uwp_get_playlists_u16()
// {
//   return hstring_to_wstring(KnownFolders::Playlists().Path());
// }

// char* uwp_get_playlists_u8()
// {
//   return hstring_to_cstring(KnownFolders::Playlists().Path());
// }

// wchar_t* uwp_get_savedpictures_u16()
// {
//   return hstring_to_wstring(KnownFolders::SavedPictures().Path());
// }

// char* uwp_get_savedpictures_u8()
// {
//   return hstring_to_cstring(KnownFolders::SavedPictures().Path());
// }

// wchar_t* uwp_get_music_u16()
// {
//   return hstring_to_wstring(KnownFolders::MusicLibrary().Path());
// }

// char* uwp_get_music_u8()
// {
//   return hstring_to_cstring(KnownFolders::MusicLibrary().Path());
// }

// wchar_t* uwp_get_pictures_u16()
// {
//   return hstring_to_wstring(KnownFolders::PicturesLibrary().Path());
// }

// char* uwp_get_pictures_u8()
// {
//   return hstring_to_cstring(KnownFolders::PicturesLibrary().Path());
// }

// wchar_t* uwp_get_videos_u16()
// {
//   return hstring_to_wstring(KnownFolders::VideosLibrary().Path());
// }

// char* uwp_get_videos_u8()
// {
//   return hstring_to_cstring(KnownFolders::VideosLibrary().Path());
// }

// wchar_t* uwp_get_homegroup_u16()
// {
//   return hstring_to_wstring(KnownFolders::HomeGroup().Path());
// }

// char* uwp_get_homegroup_u8()
// {
//   return hstring_to_cstring(KnownFolders::HomeGroup().Path());
// }

// wchar_t* uwp_get_removabledevices_u16()
// {
//   return hstring_to_wstring(KnownFolders::RemovableDevices().Path());
// }

// char* uwp_get_removabledevices_u8()
// {
//   return hstring_to_cstring(KnownFolders::RemovableDevices().Path());
// }

// wchar_t* uwp_get_mediaserverdevices_u16()
// {
//   return hstring_to_wstring(KnownFolders::MediaServerDevices().Path());
// }

// char* uwp_get_mediaserverdevices_u8()
// {
//   return hstring_to_cstring(KnownFolders::MediaServerDevices().Path());
// }

// wchar_t* uwp_get_objects3d_u16()
// {
//   return hstring_to_wstring(KnownFolders::Objects3D().Path());
// }

// char* uwp_get_objects3d_u8()
// {
//   return hstring_to_cstring(KnownFolders::Objects3D().Path());
// }

// wchar_t* uwp_get_appcaptures_u16()
// {
//   return hstring_to_wstring(KnownFolders::AppCaptures().Path());
// }

// char* uwp_get_appcaptures_u8()
// {
//   return hstring_to_cstring(KnownFolders::AppCaptures().Path());
// }

// wchar_t* uwp_get_recordedcalls_u16()
// {
//   return hstring_to_wstring(KnownFolders::RecordedCalls().Path());
// }

// char* uwp_get_recordedcalls_u8()
// {
//   return hstring_to_cstring(KnownFolders::RecordedCalls().Path());
// }

// wchar_t* uwp_get_cookies_u16()
// {
//   return hstring_to_wstring(AppDataPaths::Cookies().Path());
// }

// char* uwp_get_cameraroll_u8()
// {
//   return hstring_to_cstring(KnownFolders::CameraRoll().Path());
// }
