/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "ControlProcess.h"


/*------------------*/
/* extern�錾		*/
/*------------------*/
extern CControlProcess*		g_pAppWndProc;				/*	�E�B���h�E���R���g���[������N���X�̃|�C���^		*/

/*==============================================================================*/
/*																				*/
/*	[�֐�]		 AppWndProc		:	�E�B���h�E�v���V�[�W��						*/
/*									( �E�B���h�E�R�[���o�b�N�֐� )				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	LRESULT WINAPI 	:	�W���̃E�B���h�E�v���V�[�W���̏������s��	*/
/*	[����]		HWND			:	�E�B���h�E�n���h��							*/
/*				UINT_PTR		:	���b�Z�[�W									*/
/*				WPARAM			:												*/
/*				LPARAM			:												*/
/*																				*/
/*==============================================================================*/
LRESULT WINAPI AppWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CControlProcess* pApp;

	switch (msg)
	{

	case WM_CREATE:
		pApp = (CControlProcess*)g_pAppWndProc;
		return 	::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pApp);
	default:
		pApp = (CControlProcess*)::GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (NULL != pApp)
		{
			return pApp->DispatchEvent(hwnd, msg, wParam, lParam);
		}
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}
}