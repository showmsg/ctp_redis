/*----------------------------------------------
File: printfc.hh -- printf with color
Date: 2014/2/24 16:52:35
Author: js2854@gmail.com
----------------------------------------------*/

#ifndef __PRINTFC_H__
#define __PRINTFC_H__


#ifdef __cplusplus
extern "C"
{
	
#endif

#pragma once

#ifdef WINDOWS
#define WIN32
#define _CONSOLE
#define _MBCS
#endif

#include <stdio.h>

#define MAX_STR_LEN		2048

#ifndef WIN32
#include <stdarg.h> //vsnprintf,va_start,va_end
#include <string.h> //strok
const typedef enum _ForeColor
{
	FG_BLACK		= 30, //黑色
	FG_RED			= 31, //红色
	FG_GREEN		= 32, //绿色
	FG_YELLOW		= 33, //黄色
	FG_BLUE			= 34, //蓝色
	FG_PURPLE		= 35, //紫色
	FG_DARKGREEN	= 36, //深绿色
	FG_WHITE		= 37, //白色
}ForeColor;

const typedef enum _BackColor
{
	BG_BLACK		= 40, //黑色
	BG_DARKRED		= 41, //深红色
	BG_GREEN		= 42, //绿色
	BG_YELLOW		= 43, //黄色
	BG_BLUE			= 44, //蓝色
	BG_PURPLE		= 45, //紫色
	BG_DARKGREEN	= 46, //深绿色
	BG_WHITE		= 47, //白色
}BackColor;

#else
#include <windows.h>
const typedef enum _ForeColor
{
	FG_BLACK		= 0, //黑色
	FG_RED			= FOREGROUND_INTENSITY | FOREGROUND_RED, //红色
	FG_GREEN		= FOREGROUND_INTENSITY | FOREGROUND_GREEN, //绿色
	FG_YELLOW		= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, //黄色
	FG_BLUE			= FOREGROUND_INTENSITY | FOREGROUND_BLUE, //蓝色
	FG_PURPLE		= FOREGROUND_RED | FOREGROUND_BLUE, //紫色
	FG_DARKGREEN	= FOREGROUND_GREEN, //深绿色
	FG_WHITE		= FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, //白色
}ForeColor;

const typedef enum _BackColor
{
	BG_BLACK		= 0, //黑色
	BG_DARKRED		= BACKGROUND_RED, //深红色
	BG_GREEN		= BACKGROUND_INTENSITY | BACKGROUND_GREEN, //绿色
	BG_YELLOW		= BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN, //黄色
	BG_BLUE			= BACKGROUND_INTENSITY | BACKGROUND_BLUE, //蓝色
	BG_PURPLE		= BACKGROUND_RED | BACKGROUND_BLUE, //紫色
	BG_DARKGREEN	= BACKGROUND_GREEN, //深绿色
	BG_WHITE		= BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE, //白色
}BackColor;

#endif

int printfc(ForeColor fc, const char* format_str, ...);

int printfbc(ForeColor fc, BackColor bc, const char* format_str, ...);

#ifdef __cplusplus
}; //end of extern "C" {
#endif

#endif //__PRINTFC_H__
