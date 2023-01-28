/*

*/
#ifndef __SERVER__
#define __SERVER__

#define __ALLWIN__
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pure lib/winsock.h"
#include "../pure lib/winthread.h"
#include "message.h"
#include "list.h"

#define GROUP_MAX 5

//#include "../purelib/zwindows.h"
void initConsole(void)
{
    AllocConsole();
    freopen("CONIN$", "r+t", stdin);
    freopen("CONOUT$", "w+t", stdout);
}

#endif
