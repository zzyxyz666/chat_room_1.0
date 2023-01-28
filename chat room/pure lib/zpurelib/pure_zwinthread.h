/*


*/
#ifndef __PURE_ZWINTHREAD_H__
#define __PURE_ZWINTHREAD_H__
#include <windows.h>
HANDLE initThread(LPTHREAD_START_ROUTINE FunProcName, void* Param);

HANDLE initThread(LPTHREAD_START_ROUTINE FunProcName, void* Param)
{
	return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FunProcName,(LPVOID)Param,0,NULL);
}

#endif

