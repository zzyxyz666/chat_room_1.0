/*

*/
#ifndef __PURE_ZINITWIN_H__
#define __PURE_ZINITWIN_H__

#include "zbase.h"
#ifndef __ALLWIN__
#include <windows.h>
#endif
#include "zbite.h"
#include "pure_zwindows.h"
#include "pure_zcreatewin.h"
#include "pure_zcallback.h"

enum INIT_WINDOW_VARIABLE_FLAG
{
	WINFLAG_DEFAULT,
	WINFLAG_STYLE,
	WINFLAG_MASK,
};

typedef struct INIT_WINDOWS_VARIABLE
{
	bit_32 mask;
 	bit_32 style;
	//CLASS_PARAM
	UINT classStyle;
	WNDPROC WndProc;
	const char *className;
	//CREATE_PARAM
	DWORD createExStyle;
	DWORD createStyle;
	const char *Title;
	int X;
	int Y;
	int Width;
	int Height;
	HWND hwndParent;
	HMENU hMenu;
}WIN_PARAM, *PWIN_PARAM, INITWIN, *PINITWIN;
//
HWND zInitWindow(PINITWIN pWin);
//
//HWND initWindow(int flag, INITWIN *pInitWin);
int zWinFillingBlank(bit_32 mask, PINITWIN pWin);
int zInMyWinStyle(bit_32 style, bit_32 *mask, PINITWIN pWin);
//individualization
#ifndef INITWINDOW_STYLE
#define INITWINDOW_STYLE
#define WS_DEFAULT (CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS)
#define WS_DRAW (CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS)
#define  WS_EX_INVISIBLE (WS_EX_TOOLWINDOW | \
WS_EX_NOACTIVATE | WS_EX_TRANSPARENT | \
WS_EX_LAYOUTRTL | WS_EX_TOPMOST)
#endif

#define nullbit 		_32b00_
#define WP_C_STYLE      _32b01_
#define WP_C_WNDPROC    _32b02_
#define WP_C_NAME       _32b03_
#define WP_W_EXSTYLE    _32b04_
#define WP_W_STYLE      _32b05_
#define WP_W_TITLE      _32b06_
#define WP_W_X          _32b07_
#define WP_W_Y          _32b08_
#define WP_W_WIDTH      _32b09_
#define WP_W_HEIGHT     _32b10_
#define WP_W_HPARENT    _32b11_
#define WP_W_HMENU      _32b12_

#define SY_POSITION     _32b01_
#define SY_WINSIZE      _32b02_
#define SY_COORDINATE (SY_POSITION | SY_WINSIZE)
#define SY_NAME         _32b03_

#define SY_DEFAULT      _32b10_
#define SY_INVISIABLE   _32b11_
#define SY_FIXEDSIZE    _32b12_

#define SY_CHILD        _32b30_
#define SY_DIALOGBOX    _32b31_

//
int zInMyWinStyle(bit_32 style, bit_32 *mask, PINITWIN pWin)
{
	if(style & SY_POSITION)//1
	{
		*mask ^= WP_W_X;
		*mask ^= WP_W_Y;
	}
	if(style & SY_WINSIZE)//2
	{
		*mask ^= WP_W_WIDTH;
		*mask ^= WP_W_HEIGHT;
	}
	if(style & SY_NAME)//3
	{
		*mask ^= WP_W_TITLE;
	}
	if(style & SY_DEFAULT)//4
	{
		return 0;
	}
	if(style & SY_CHILD)
	{
		*mask ^= WP_W_HPARENT;
		*mask ^= WP_C_NAME;
		*mask ^= WP_C_WNDPROC;
	}
	else if(style & SY_INVISIABLE)
	{
		*mask ^= WP_W_EXSTYLE;
		*mask ^= WP_W_STYLE;
		pWin->createExStyle = WS_EX_INVISIBLE;
		pWin->createStyle = WS_POPUP;
	}
	else if(style & SY_FIXEDSIZE)
	{
		*mask ^= WP_W_STYLE;
		pWin->createStyle = WS_OVERLAPPED |WS_CAPTION |WS_SYSMENU |WS_MINIMIZEBOX ;
	}
	else if(style & SY_DIALOGBOX)
	{
//		*mask ^= WP_W_HPARENT;
		*mask ^= WP_W_STYLE;
		*mask ^= WP_C_NAME;
		*mask ^= WP_C_WNDPROC;
		pWin->createStyle = WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE;
		//WS_CHILD | WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_BORDER
	}
	return 0;
}

HWND initWindow(int flag, INITWIN *pInitWin)
{
	CLASS_PARAM registParam;
	CREATE_PARAM createParam;
	bit_32 mask = ~pInitWin->mask;
	switch(flag)
	{
		case WINFLAG_DEFAULT:
			{
				mask = ~nullbit;
				break;
			}
		case WINFLAG_STYLE:
			{
				mask = ~nullbit;
				zInMyWinStyle(pInitWin->style, &mask, pInitWin);
				break;
			}
		case WINFLAG_MASK:
			{
				break;
			}
		default:
			{
				MessageBox(NULL, "The flag is none define value", "WARNING", MB_ICONERROR);
				mask = ~nullbit;
				break;
			}
	}
	zWinFillingBlank(mask, pInitWin);
	return zInitWindow(pInitWin);
}

int zWinFillingBlank(bit_32 mask, PINITWIN pWin)
{
	if(mask & WP_C_STYLE)//1
		pWin->classStyle = WS_DEFAULT;
	if(mask & WP_C_WNDPROC)//2
		pWin->WndProc = DefWndProc;
	if(mask & WP_C_NAME)//3
		pWin->className = TEXT ("ZZY_MAIN_CLASS_WINDOWS");
	if(mask & WP_W_EXSTYLE)//4
		pWin->createExStyle = WS_EX_LEFT;
	if(mask & WP_W_STYLE)//5
		pWin->createStyle = WS_OVERLAPPEDWINDOW;
	if(mask & WP_W_TITLE)//6
		pWin->Title = TEXT("WinMain");
	if(mask & WP_W_X)//7
		pWin->X = CW_USEDEFAULT;
	if(mask & WP_W_Y)//8
		pWin->Y = CW_USEDEFAULT;
	if(mask & WP_W_WIDTH)//9
		pWin->Width = CW_USEDEFAULT;
	if(mask & WP_W_HEIGHT)//10
		pWin->Height = CW_USEDEFAULT;
	if(mask & WP_W_HPARENT)//11
		pWin->hwndParent = NULL;
	if(mask & WP_W_HMENU)//12
		pWin->hMenu = NULL;
	return 0;
}

#endif
