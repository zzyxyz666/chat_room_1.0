/*

*/
#ifndef __PURE_ZCALLBACK_H__
#define __PURE_ZCALLBACK_H__
#include "zbase.h"
#ifndef __ALLWIN__
#include <windows.h>
#endif

enum KEY_BUTTON_EVENT
{
	KEYDOWN,
	KEYUP,
};

enum MOUSE_BUTTON_EVENT
{
	LBUTTONDOWN,
	LBUTTONUP,
	LBUTTONDBLCLK,
	MBUTTONDOWN,
	MBUTTONUP,
	MBUTTONDBLCLK,
	RBUTTONDOWN,
	RBUTTONUP,
	RBUTTONDBLCLK,
	MOUSEMOVE,
	MOUSEWHEEL,
};

typedef void(*KeyCallBack) (int key, int event);
typedef void(*CharCallBack) (char c);
typedef void(*TimerCallBack) (int timerID);
typedef void(*MouseCallBack) (int x, int y, int button_event, int add_event);
typedef void(*CommandCallBack) (int ID);
typedef void(*CreateCallBack) ();
typedef int(*DestroyCallBack) ();
typedef void(*PaintCallBack) ();
typedef void(*OtherCallback) (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

typedef struct GLOBAL_CALLBACK_FUNCTION
{
	KeyCallBack m_key;
	CharCallBack m_char;
	TimerCallBack m_timer;
	MouseCallBack m_mouse;
	CommandCallBack m_command;
	CreateCallBack m_create;
	DestroyCallBack m_destroy;
	PaintCallBack m_paint;
	OtherCallback m_other;
}G_CALLBACK_PARAM, *PG_CALLBACK_PARAM;

G_CALLBACK_PARAM g_zzycallback;
PG_CALLBACK_PARAM pg_zzycallback = &g_zzycallback;
//function declare
LRESULT CALLBACK DefWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void initCallBackParam(PG_CALLBACK_PARAM pg_callback);
void RegistKey(KeyCallBack callback);
void RegistChar(CharCallBack callback);
void RegistTimer(TimerCallBack callback);
void RegistMouse(MouseCallBack callback);
void RegistCommand(CommandCallBack callback);
void RegistCreate(CreateCallBack callback);
void RegistDestroy(DestroyCallBack callback);
void RegistPaint(PaintCallBack callback);
void RegistOther(OtherCallback callback);
//message
int zzy_in_other_message(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam);
void zzy_in_create(WPARAM wParam, LPARAM lParam);
void zzy_in_paint(WPARAM wParam, LPARAM lParam);
void zzy_in_char(WPARAM wParam, LPARAM lParam);
void zzy_in_keydown(WPARAM wParam, LPARAM lParam);
void zzy_in_keyup(WPARAM wParam, LPARAM lParam);
void zzy_in_lbuttondown(WPARAM wParam, LPARAM lParam);
void zzy_in_lbuttonup(WPARAM wParam, LPARAM lParam);
void zzy_in_lbuttondblclk(WPARAM wParam, LPARAM lParam);
void zzy_in_mbuttondown(WPARAM wParam, LPARAM lParam);
void zzy_in_mbuttonup(WPARAM wParam, LPARAM lParam);
void zzy_in_mbuttondblclk(WPARAM wParam, LPARAM lParam);
void zzy_in_rbuttondown(WPARAM wParam, LPARAM lParam);
void zzy_in_rbuttonup(WPARAM wParam, LPARAM lParam);
void zzy_in_rbuttondblclk(WPARAM wParam, LPARAM lParam);
void zzy_in_mousemove(WPARAM wParam, LPARAM lParam);
void zzy_in_mousewheel(WPARAM wParam, LPARAM lParam);
void zzy_in_timer(WPARAM wParam, LPARAM lParam);
void zzy_in_destroy(WPARAM wParam, LPARAM lParam);
void zzy_in_command(WPARAM wParam, LPARAM lParam);


//
void initCallBackParam(PG_CALLBACK_PARAM pg_callback)
{
	pg_callback->m_char = NULL;
	pg_callback->m_key = NULL;
	pg_callback->m_timer = NULL;
	pg_callback->m_mouse = NULL;
	pg_callback->m_command = NULL;
	pg_callback->m_create = NULL;
	pg_callback->m_destroy = NULL;
	pg_callback->m_paint = NULL;
	pg_callback->m_other = NULL;
}

void RegistKey(KeyCallBack callback)
{
	pg_zzycallback->m_key = callback;
}
void RegistChar(CharCallBack callback)
{
	pg_zzycallback->m_char = callback;
}
void RegistTimer(TimerCallBack callback)
{
	pg_zzycallback->m_timer = callback;
}
void RegistMouse(MouseCallBack callback)
{
	pg_zzycallback->m_mouse = callback;
}
void RegistCommand(CommandCallBack callback)
{
	pg_zzycallback->m_command = callback;
}
void RegistCreate(CreateCallBack callback)
{
	pg_zzycallback->m_create = callback;
}
void RegistDestroy(DestroyCallBack callback)
{
	pg_zzycallback->m_destroy = callback;
}
void RegistPaint(PaintCallBack callback)
{
	pg_zzycallback->m_paint = callback;
}
void RegistOther(OtherCallback callback)
{
	pg_zzycallback->m_other = callback;
}
//customize function
int zzy_in_other_message(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	if(pg_zzycallback->m_other != NULL)
		pg_zzycallback->m_other(hwnd, message, wParam, lParam);
}
//funcion define
void zzy_in_create(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_create != NULL)
		pg_zzycallback->m_create();
}

void zzy_in_destroy(WPARAM wParam, LPARAM lParam)
{
	int r = 0;
	if(pg_zzycallback->m_destroy != NULL)
		r = pg_zzycallback->m_destroy();
	if(!r)
	{
		PostQuitMessage(0);
	}	
}

//other define

void zzy_in_paint(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_paint != NULL)
		pg_zzycallback->m_paint();
}

//timer
void zzy_in_timer(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_timer != NULL)
		pg_zzycallback->m_timer((int)wParam);
}
//char
void zzy_in_char(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_char != NULL)
		pg_zzycallback->m_char((char)wParam);
}
//keyboard
void zzy_in_keydown(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_key != NULL)
		pg_zzycallback->m_key((int)wParam , KEYDOWN);
}

void zzy_in_keyup(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_key != NULL)
		pg_zzycallback->m_key((int)wParam , KEYUP);
}
//mouse message
void zzy_in_lbuttondown(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), LBUTTONDOWN,LOWORD(wParam));
}
void zzy_in_lbuttonup(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), LBUTTONUP,LOWORD(wParam));
}
void zzy_in_lbuttondblclk(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), LBUTTONDBLCLK,LOWORD(wParam));
}
void zzy_in_mbuttondown(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), MBUTTONDOWN,LOWORD(wParam));
}
void zzy_in_mbuttonup(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), MBUTTONUP,LOWORD(wParam));
}
void zzy_in_mbuttondblclk(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), MBUTTONDBLCLK,LOWORD(wParam));
}
void zzy_in_rbuttondown(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), RBUTTONDOWN,LOWORD(wParam));
}
void zzy_in_rbuttonup(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), RBUTTONUP,LOWORD(wParam));
}
void zzy_in_rbuttondblclk(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), RBUTTONDBLCLK,LOWORD(wParam));
}
void zzy_in_mousemove(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int)LOWORD(lParam),(int) HIWORD(lParam), MOUSEMOVE,LOWORD(wParam));
}
void zzy_in_mousewheel(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_mouse != NULL)
		pg_zzycallback->m_mouse((int) LOWORD(lParam),(int) HIWORD(lParam), MOUSEWHEEL,wParam);
}
//command
void zzy_in_command(WPARAM wParam, LPARAM lParam)
{
	if(pg_zzycallback->m_command != NULL)
	{
		pg_zzycallback->m_command((int)(LOWORD(wParam)));
	}
}

LRESULT CALLBACK DefWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
			zzy_in_create(wParam, lParam);
			break;
		case WM_PAINT:
			zzy_in_paint(wParam, lParam);
			break;
		case WM_CHAR:
			zzy_in_char(wParam, lParam);
			break;
		case WM_KEYDOWN:
			zzy_in_keydown(wParam, lParam);
			break;
		case WM_KEYUP:
			zzy_in_keyup(wParam, lParam);
			break;
		case WM_LBUTTONDOWN:
			zzy_in_lbuttondown(wParam, lParam);
			break;
		case WM_LBUTTONUP:
			zzy_in_lbuttonup(wParam, lParam);
			break;
		case WM_LBUTTONDBLCLK:
			zzy_in_lbuttondblclk(wParam, lParam);
			break;
		case WM_MBUTTONDOWN:
			zzy_in_mbuttondown(wParam, lParam);
			break;
		case WM_MBUTTONUP:
			zzy_in_mbuttonup(wParam, lParam);
			break;
		case WM_MBUTTONDBLCLK:
			zzy_in_mbuttondblclk(wParam, lParam);
			break;
		case WM_RBUTTONDOWN:
			zzy_in_rbuttondown(wParam, lParam);
			break;
		case WM_RBUTTONUP:
			zzy_in_rbuttonup(wParam, lParam);
			break;
		case WM_RBUTTONDBLCLK:
			zzy_in_rbuttondblclk(wParam, lParam);
			break;
		case WM_MOUSEMOVE:
			zzy_in_mousemove(wParam, lParam);
			break;
		case WM_MOUSEWHEEL:
			zzy_in_mousewheel(wParam, lParam);
			break;
		case WM_TIMER:
			zzy_in_timer(wParam, lParam);
			break;
		case WM_DESTROY:
			zzy_in_destroy(wParam, lParam);
			break;
		case WM_COMMAND:
			zzy_in_command(wParam, lParam);
			break;
		default:
			zzy_in_other_message(hwnd, message, wParam, lParam);
            break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif

