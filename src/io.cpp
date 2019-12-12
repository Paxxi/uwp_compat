#include <uwp_compat/io.h>
#include <uwp_compat/encoding.h>

#include <cstdlib>


HANDLE uwp_create_file_u16(
	_In_ LPCWSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile
)
{
#ifndef MS_APP
	return CreateFileW(lpFileName, dwDesiredAccess,
		dwShareMode, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes,
		hTemplateFile);
#else
	const DWORD attributeMask = FILE_ATTRIBUTE_ARCHIVE |
		FILE_ATTRIBUTE_ENCRYPTED |
		FILE_ATTRIBUTE_HIDDEN |
		FILE_ATTRIBUTE_INTEGRITY_STREAM |
		FILE_ATTRIBUTE_NORMAL |
		FILE_ATTRIBUTE_OFFLINE |
		FILE_ATTRIBUTE_READONLY |
		FILE_ATTRIBUTE_SYSTEM |
		FILE_ATTRIBUTE_TEMPORARY;

	const DWORD flagMask = FILE_FLAG_BACKUP_SEMANTICS |
		FILE_FLAG_DELETE_ON_CLOSE |
		FILE_FLAG_NO_BUFFERING |
		FILE_FLAG_OPEN_NO_RECALL |
		FILE_FLAG_OPEN_REPARSE_POINT |
		FILE_FLAG_OPEN_REQUIRING_OPLOCK |
		FILE_FLAG_OVERLAPPED |
		FILE_FLAG_POSIX_SEMANTICS |
		FILE_FLAG_RANDOM_ACCESS |
		FILE_FLAG_SESSION_AWARE |
		FILE_FLAG_SEQUENTIAL_SCAN |
		FILE_FLAG_WRITE_THROUGH;

	const DWORD securityMask = SECURITY_ANONYMOUS |
		SECURITY_CONTEXT_TRACKING |
		SECURITY_DELEGATION |
		SECURITY_EFFECTIVE_ONLY |
		SECURITY_IDENTIFICATION |
		SECURITY_IMPERSONATION;

	CREATEFILE2_EXTENDED_PARAMETERS ext;
	ext.dwSize = sizeof(ext);
	ext.dwFileAttributes = dwFlagsAndAttributes & attributeMask;
	ext.dwFileFlags = dwFlagsAndAttributes & flagMask;
	ext.dwSecurityQosFlags = dwFlagsAndAttributes & securityMask;
	ext.hTemplateFile = hTemplateFile;
	ext.lpSecurityAttributes = lpSecurityAttributes;

	return CreateFile2(lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, &ext);
#endif
}

HANDLE uwp_create_file_u8(
	_In_ LPCSTR lpFileName,
	_In_ DWORD dwDesiredAccess,
	_In_ DWORD dwShareMode,
	_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	_In_ DWORD dwCreationDisposition,
	_In_ DWORD dwFlagsAndAttributes,
	_In_opt_ HANDLE hTemplateFile)
{
	auto filename = to_utf16(lpFileName, -1);
	if (!filename)
		return INVALID_HANDLE_VALUE;

	HANDLE h = uwp_create_file_u16(filename,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
	std::free(filename);

	return h;
}
