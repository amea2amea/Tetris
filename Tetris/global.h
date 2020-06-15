/*------------------*/
/* ifdef�p�̒�`	*/
/*------------------*/
#define WIN32_LEAN_AND_MEAN

#ifndef _GROBAL_H
#define _GROBAL_H

/*------------------*/
/* �C���N���[�h		*/
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
/*	��`		*/
/*--------------*/

/*	�L�[�}�b�v	*/
#define VK_B 0x42
#define VK_C 0x43
#define VK_V 0x56

/*--------------*/
/*	�񋓑�		*/
/*--------------*/

enum WINDOW_MEASSAGE												/*	�E�B���h�E�̃��b�Z�[�W��`							*/
{
	WINDOW_MEASSAGE_START	= 0,									/*	�E�B���h�E�̊J�n����								*/
	WINDOW_MEASSAGE_QUIT	= 1,									/*	�E�B���h�E�̏I������								*/
};

enum BIT_FLAG														/*	�r�b�g�t���O										*/
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
/* �v���g�^�C�v�錾		*/
/*----------------------*/
LRESULT WINAPI	AppWndProc(HWND, UINT, WPARAM, LPARAM);

#endif