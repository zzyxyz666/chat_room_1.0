/*

*/

#ifndef __PURE_ZCREATEWIN_H__
#define __PURE_ZCREATEWIN_H__
#include "zbase.h"
#ifndef __ALLWIN__
#include <windows.h>
#endif

typedef struct ZREGISTCLASSMESSAGE
{
	HINSTANCE hInstance;
	UINT Style;
	WNDPROC WndProc;
	const char *ClassName;
} CLASS_PARAM, *PCLASS_PARAM;

typedef struct ZCREATEWINDOWMESSAGE
{
	HINSTANCE hInstance;
	DWORD ExStyle;
	DWORD Style;
	const char *ClassName;
	const char *Title;
	int X;
	int Y;
	int Width;
	int Height;
	HWND hwndParent;
	HMENU hMenu;
} CREATE_PARAM, *PCREATE_PARAM;

int zRegistClass( PCLASS_PARAM pParam);
HWND zCreateWindow( PCREATE_PARAM pParam );
int zMessageLoop(void);

//define function

int zRegistClass( PCLASS_PARAM pParam )
{
	WNDCLASS	wndclass;
	wndclass.style			= pParam->Style;
	wndclass.lpfnWndProc	= pParam->WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= pParam->hInstance;
	wndclass.hIcon			= LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor		= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName	= NULL;
	wndclass.lpszClassName	= pParam->ClassName;
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), TEXT("Main"), MB_ICONERROR);
		return -1;
	}
	return 0;
}

HWND zCreateWindow( PCREATE_PARAM pParam )
{
	HWND hwnd;
	hwnd = CreateWindowEx(
						 pParam->ExStyle,	            // window Exstyle
						 pParam->ClassName,				// window class name
						 pParam->Title,					// window caption
						 pParam->Style,					// window style
						 pParam->X,						// initial x position
						 pParam->Y,						// initial y pozition
						 pParam->Width,					// initial x size
						 pParam->Height,				// initial y size
						 pParam->hwndParent,			// parent window handel
						 pParam->hMenu,					// window menu handle
						 pParam->hInstance,				// program instance handle
						 NULL);							// creation parameters
	return hwnd;
}

int zMessageLoop(void)
{
	MSG	msg;
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
	return msg.wParam;
}

#endif

