/*

*/

#ifndef __PURE_ZCONTROL_H__
#define __PURE_ZCONTROL_H__
#include "pure_zwindows.h"
#include "pure_ztextfont.h"
extern PG_WINDOWS pg_zzywindows;
#define STYLE_BUTTON (WS_CHILD|WS_VISIBLE|WS_BORDER)
#define STYLE_INPUT_EDIT (WS_CHILD|WS_VISIBLE|WS_BORDER|ES_LEFT|ES_MULTILINE|ES_WANTRETURN|WS_VSCROLL)
#define STYLE_OUTPUT_EDIT (WS_CHILD|WS_VISIBLE|WS_BORDER|ES_READONLY|ES_MULTILINE|WS_VSCROLL)

HWND GetEditText(HWND hwnd, char *Buffer, int BufferLen);
HWND CleanEditText(HWND hwnd);
HWND SetEditText(HWND hwnd, char *Buffer);

HWND CreateButton(int X, int Y, int width, int height, char * title, long long ID, HWND parent);
HWND CreateInEdit(int X, int Y, int width, int height, char * title, long long ID, HWND parent);
HWND CreateOutEdit(int X, int Y, int width, int height, char * title, long long ID, HWND parent);

HWND GetEditText(HWND hwnd, char *Buffer, int BufferLen)
{
	SendMessage(hwnd,WM_GETTEXT,BufferLen,(LPARAM)Buffer);
	return hwnd;
}
HWND CleanEditText(HWND hwnd)
{
	SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)NULL);
	return hwnd;
}
HWND SetEditText(HWND hwnd, char *Buffer)
{
	SendMessage(hwnd,EM_SETSEL,0,(LPARAM)-1);
	SendMessage(hwnd,EM_SETSEL,-1,(LPARAM)-1);
	SendMessage(hwnd,EM_REPLACESEL,FALSE,(LPARAM)Buffer);
	return hwnd;
}

HWND CreateButton(int X, int Y, int width, int height, char * title, long long ID, HWND parent)
{
	HWND hwnd = CreateWindow( TEXT("Button"), TEXT(title),STYLE_BUTTON,
	X,Y,width,height,parent,(HMENU)ID,NULL,NULL);
	SendMessage(hwnd,WM_SETFONT,(WPARAM)pg_zzywindows->hFont,(LPARAM)LOWORD(TRUE));
	return hwnd;
}

HWND CreateInEdit(int X, int Y, int width, int height, char * title, long long ID, HWND parent)
{
	HWND hwnd = CreateWindow( TEXT("Edit"), TEXT(title),STYLE_INPUT_EDIT,
	X,Y,width,height,parent,(HMENU)ID,NULL,NULL);
	SendMessage(hwnd,WM_SETFONT,(WPARAM)pg_zzywindows->hFont,(LPARAM)LOWORD(TRUE));
	return hwnd;
}

HWND CreateOutEdit(int X, int Y, int width, int height, char * title, long long ID, HWND parent)
{
	HWND hwnd = CreateWindow( TEXT("Edit"), TEXT(title),STYLE_OUTPUT_EDIT,
	X,Y,width,height,parent,(HMENU)ID,NULL,NULL);
	SendMessage(hwnd,WM_SETFONT,(WPARAM)pg_zzywindows->hFont,(LPARAM)LOWORD(TRUE));
	return hwnd;
}

#endif

