/*------------------*/
/* ifdef用の定義	*/
/*------------------*/
#define WIN32_LEAN_AND_MEAN

#ifndef _GROBAL_H
#define _GROBAL_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include <windows.h>
#include <tchar.h>
#include <basetsd.h>
#include <math.h> 
#include <time.h>
#include <crtdbg.h>
#include <mmsystem.h>
#include <Strsafe.h>
#include <String.h>

/*--------------*/
/*	定義		*/
/*--------------*/

/*	キーマップ	*/
#define VK_B 0x42
#define VK_C 0x43
#define VK_V 0x56

/*--------------*/
/*	列挙体		*/
/*--------------*/

enum WINDOW_MEASSAGE												/*	ウィンドウのメッセージ定義							*/
{
	WINDOW_MEASSAGE_START	= 0,									/*	ウィンドウの開始処理								*/
	WINDOW_MEASSAGE_QUIT	= 1,									/*	ウィンドウの終了処理								*/
};

enum BIT_FLAG														/*	ビットフラグ										*/
{
	BIT0 = 0x01,
	BIT1 = 0x02,
	BIT2 = 0x04,
	BIT3 = 0x08,
	BIT4 = 0x10,
	BIT5 = 0x20,
	BIT6 = 0x40,
	BIT7 = 0x80,
};

/*----------------------*/
/* プロトタイプ宣言		*/
/*----------------------*/
LRESULT WINAPI	AppWndProc(HWND, UINT, WPARAM, LPARAM);

#endif