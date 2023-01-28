/*
LRESULT CALLBACK DefWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int winmain(void);

HWND initWindow(int flag, INITWIN *pInitWin);
	WINFLAG_DEFAULT,
	WINFLAG_STYLE,
#define SY_POSITION     _32b01_
#define SY_WINSIZE      _32b02_
#define SY_COORDINATE (SY_POSITION | SY_WINSIZE)
#define SY_NAME         _32b03_
#define SY_DEFAULT      _32b10_
#define SY_INVISIABLE   _32b11_
#define SY_FIXEDSIZE    _32b12_
	WINFLAG_MASK,
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

void initConsole(void)

typedef void(*KeyCallBack) (int key, int event);
typedef void(*CharCallBack) (char c);
typedef void(*TimerCallBack) (int timerID);
typedef void(*MouseCallBack) (int x, int y, int button_event, int add_event);
typedef void(*CommandCallBack) (int ID);
typedef void(*CreateCallBack) ();
typedef int(*DestroyCallBack) ();
typedef void(*PaintCallBack) ();
typedef void(*OtherCallback) (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void RegistKey(KeyCallBack callback);
void RegistChar(CharCallBack callback);
void RegistTimer(TimerCallBack callback);
void RegistMouse(MouseCallBack callback);
void RegistCommand(CommandCallBack callback);
void RegistCreate(CreateCallBack callback);
void RegistDestroy(DestroyCallBack callback);
void RegistPaint(PaintCallBack callback);
void RegistOther(OtherCallback callback);

HWND CreateButton(int X, int Y, int width, int height, const char * title, HMENU ID, HWND parent);
HWND CreateInEdit(int X, int Y, int width, int height, const char * title, HMENU ID, HWND parent);
HWND CreateOutEdit(int X, int Y, int width, int height, const char * title, HMENU ID, HWND parent);
*/

#ifndef __ZWINDOWS_H__
#define __ZWINDOWS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zpurelib/pure_zwindows.h"

#ifdef __cplusplus
}
#endif

#endif

