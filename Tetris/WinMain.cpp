/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "FrameWork.h"
#include "ProcessManger.h"
#include "Graphics.h"
#include "GameLogic.h"
#include "TetrisDraw.h"
#include "TetrisLogic.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		WinMain						:	�A�v���P�[�V�����̃��C���֐�	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	int							:									*/
/*	[����]		HINSTANCE	hInstance		:	�C���X�^���X�̃n���h��			*/
/*				HINSTANCE	hPrevInstance	:	���NULL (�p�~���ꂽ�p�����[�^)	*/
/*				LPTSTR		lpCmdLine		:	�R�}���h���C������				*/
/*				int			nCmdShow		:	�E�B���h�E�\���̎w��			*/
/*																				*/
/*==============================================================================*/
int WINAPI _tWinMain(_In_ HINSTANCE	hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	//	MY_RUNNINGTIMER(cRunningTimer, "WinMain");
	//	setlocale(LC_ALL, "Japanese");

	CProcessManger			process_manger;
	CFameWork*				p_framework = 0;
	CGraphics*				p_graphics	= 0;
	CGameLogic*				p_gamelogic	= 0;

	try
	{
		p_framework = process_manger.Create(hInstance, lpCmdLine); 
		p_gamelogic = new CTetrisLogic();
		p_graphics = new CTetrisDraw();

		if (p_framework == NULL)
			return 0;

		if(p_graphics != NULL)
			p_framework->SetGraphicClass(p_graphics);

		if (p_gamelogic != NULL)
			p_framework->SetGameLogicClass(p_gamelogic);

		//	MY_TRACETIME(cRunningTimer, "ProcessObject Created");
	}
	catch (...) {
	}

	if (p_framework != NULL)
	{
		p_framework->Run();
		delete p_graphics;
		delete p_gamelogic;
		delete p_framework;
	}

	return 0;
}