/*

*/

#ifndef __PURE_ZWINDOWS_H__
#define __PURE_ZWINDOWS_H__

#include "zbase.h"
#ifndef __ALLWIN__
#include <windows.h>
#endif
#include <stdio.h>
#include "pure_zinitwin.h"

typedef struct GLOBAL_WINDOWS_VARIABLE
{
	HINSTANCE hInstance;
	HWND hwnd;
	HDC hdc;
	HBITMAP hBitMap;
	HFONT hFont;
}G_WINDOWS, *PG_WINDOWS;

int winmain(void);
void initConsole(void);
HWND zInitWindow(PINITWIN pWin);
int zInitGlobalHandle(PG_WINDOWS pg_windows);

#include "pure_zcallback.h"
#include "pure_zcreatewin.h"
#include "pure_zcontrol.h"
#include "pure_ztextfont.h"

//function define

G_WINDOWS g_zzywindows;
PG_WINDOWS pg_zzywindows = &g_zzywindows;

int zInitGlobalHandle(PG_WINDOWS pg_windows)
{
	pg_windows->hwnd = NULL;
	pg_windows->hInstance = NULL;
	pg_windows->hdc = NULL;
	pg_windows->hFont = NULL;
	pg_windows->hBitMap = NULL;
}

extern PG_CALLBACK_PARAM pg_zzycallback;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	initCallBackParam(pg_zzycallback);
	zInitGlobalHandle(pg_zzywindows);
	g_zzywindows.hInstance = hInstance;
	winmain();
	//need initWindow() see pure_initwin.h
	ShowWindow (g_zzywindows.hwnd, iCmdShow);
	UpdateWindow (g_zzywindows.hwnd);
	zMessageLoop();
}

HWND zInitWindow(PINITWIN pWin)
{
	CLASS_PARAM regist;
	PCLASS_PARAM pregist = &regist;
	CREATE_PARAM create;
	PCREATE_PARAM pcreate = &create;
	pregist->hInstance = g_zzywindows.hInstance;
	pcreate->hInstance = g_zzywindows.hInstance;
	//
	pregist->ClassName = pWin->className;
	pregist->WndProc = pWin->WndProc;
	pregist->Style = pWin->classStyle;
	//
	pcreate->ExStyle = pWin->createExStyle;
	pcreate->Style = pWin->createStyle;
	pcreate->Title = pWin->Title;
	pcreate->X = pWin->X;
	pcreate->Y = pWin->Y;
	pcreate->Width = pWin->Width;
	pcreate->Height = pWin->Height;
	pcreate->ClassName = pregist->ClassName;
	pcreate->hwndParent = pWin->hwndParent;
	pcreate->hMenu = pWin->hMenu;
	int r = zRegistClass(pregist);
	g_zzywindows.hwnd = zCreateWindow(pcreate);
	UnregisterClass(pWin->className, g_zzywindows.hInstance);
	if(r == -1 || g_zzywindows.hwnd == NULL)
	{
		return NULL;
	}
 	return g_zzywindows.hwnd;
}

void initConsole(void)
{
    AllocConsole();
    freopen("CONIN$", "r+t", stdin);
    freopen("CONOUT$", "w+t", stdout);
}

#endif

