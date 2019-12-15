#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
  void uwp_fix_slash_u16(wchar_t* str, size_t length);

  char* uwp_executable_directory_u8();
  wchar_t* uwp_executable_directory_u16();

#ifdef MS_APP
  wchar_t* uwp_get_fonts_u16();
  char* uwp_get_fonts_u8();

  wchar_t* uwp_get_programdata_u16();
  char* uwp_get_programdata_u8();

  wchar_t* uwp_get_public_u16();
  char* uwp_get_public_u8();

  wchar_t* uwp_get_publicdesktop_u16();
  char* uwp_get_publicdesktop_u8();

  wchar_t* uwp_get_publicdocuments_u16();
  char* uwp_get_publicdocuments_u8();

  wchar_t* uwp_get_publicdownloads_u16();
  char* uwp_get_publicdownloads_u8();

  wchar_t* uwp_get_publicmusic_u16();
  char* uwp_get_publicmusic_u8();

  wchar_t* uwp_get_publicpictures_u16();
  char* uwp_get_publicpictures_u8();

  wchar_t* uwp_get_publicvideos_u16();
  char* uwp_get_publicvideos_u8();

  wchar_t* uwp_get_system_u16();
  char* uwp_get_system_u8();

  wchar_t* uwp_get_systemarm_u16();
  char* uwp_get_systemarm_u8();

  wchar_t* uwp_get_systemhost_u16();
  char* uwp_get_systemhost_u8();

  wchar_t* uwp_get_systemx64_u16();
  char* uwp_get_systemx64_u8();

  wchar_t* uwp_get_systemx86_u16();
  char* uwp_get_systemx86_u8();

  wchar_t* uwp_get_userprofiles_u16();
  char* uwp_get_userprofiles_u8();

  wchar_t* uwp_get_windows_u16();
  char* uwp_get_windows_u8();

  wchar_t* uwp_get_cameraroll_u16();
  char* uwp_get_cameraroll_u8();

  wchar_t* uwp_get_cookies_u16();
  char* uwp_get_cookies_u8();

  wchar_t* uwp_get_desktop_u16();
  char* uwp_get_desktop_u8();

  wchar_t* uwp_get_documents_u16();
  char* uwp_get_documents_u8();

  wchar_t* uwp_get_favorites_u16();
  char* uwp_get_favorites_u8();

  wchar_t* uwp_get_history_u16();
  char* uwp_get_history_u8();

  wchar_t* uwp_get_internetcache_u16();
  char* uwp_get_internetcache_u8();

  wchar_t* uwp_get_localappdata_u16();
  char* uwp_get_localappdata_u8();

  wchar_t* uwp_get_localappdatalow_u16();
  char* uwp_get_localappdatalow_u8();

  wchar_t* uwp_get_music_u16();
  char* uwp_get_music_u8();

  wchar_t* uwp_get_pictures_u16();
  char* uwp_get_pictures_u8();

  wchar_t* uwp_get_profile_u16();
  char* uwp_get_profile_u8();

  wchar_t* uwp_get_recent_u16();
  char* uwp_get_recent_u8();

  wchar_t* uwp_get_roamingappdata_u16();
  char* uwp_get_roamingappdata_u8();

  wchar_t* uwp_get_savedpictures_u16();
  char* uwp_get_savedpictures_u8();

  wchar_t* uwp_get_screenshots_u16();
  char* uwp_get_screenshots_u8();

  wchar_t* uwp_get_templates_u16();
  char* uwp_get_templates_u8();

  wchar_t* uwp_get_videos_u16();
  char* uwp_get_videos_u8();
#endif

#ifdef __cplusplus
}
#endif
