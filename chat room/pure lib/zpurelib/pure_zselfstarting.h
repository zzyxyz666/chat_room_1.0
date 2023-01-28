/*

*/

#ifndef __PURE_ZSELFSTARTING_H__
#define __PURE_ZSELFSTARTING_H__
#include <windows.h>
#define PATH_MAX_LEN 128
int selfStarting(const char * name);

///////////////////////
//function define

int selfStarting(const char * name)
{
	char path[PATH_MAX_LEN], redegit[PATH_MAX_LEN] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	GetModuleFileName(NULL, path, PATH_MAX_LEN);
	int res;
	HKEY hKey;
	DWORD dwDisposition = REG_OPENED_EXISTING_KEY;
	res = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT(redegit),0, NULL, REG_OPTION_NON_VOLATILE,\
						 KEY_ALL_ACCESS, NULL, &hKey,&dwDisposition);
	if(res != ERROR_SUCCESS)
	{
		return -1;
	}
	res = RegSetValueEx(hKey, TEXT(name), 0, REG_SZ,
						 (BYTE*)path, sizeof(path)*sizeof(TCHAR));
	if(res != ERROR_SUCCESS)
	{
		return -2;
	}
	RegCloseKey(hKey);
	return 0;
}
#undef PATH_MAX_LEN

#endif

