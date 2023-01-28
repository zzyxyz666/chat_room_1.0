/*
*/

#ifndef __PURE_ZTEXTFONT_H__
#define __PURE_ZTEXTFONT_H__

#include "pure_zwindows.h"
extern PG_WINDOWS pg_zzywindows;

void zUpdateFont(int size, char* fontName);
void SetFont(int size, char* fontName);
//400 normal / 700
//size value is 0 ~ 1000
void SetFont(int size, char* fontName)
{
	zUpdateFont(size,fontName);
}

void zUpdateFont(int size, char* fontName)
{
	if(pg_zzywindows->hFont)DeleteObject(pg_zzywindows->hFont);
	pg_zzywindows->hFont = CreateFont(0,0,0,0,size,FALSE,FALSE,FALSE,
	ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,
	fontName);
}



#endif

