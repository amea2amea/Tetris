/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "ControlProcess.h"


/*------------------*/
/* extern宣言		*/
/*------------------*/
extern CControlProcess*		g_pAppWndProc;				/*	ウィンドウをコントロールするクラスのポインタ		*/

/*==============================================================================*/
/*																				*/
/*	[関数]		 AppWndProc		:	ウィンドウプロシージャ						*/
/*									( ウィンドウコールバック関数 )				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	LRESULT WINAPI 	:	標準のウィンドウプロシージャの処理を行う	*/
/*	[引数]		HWND			:	ウィンドウハンドル							*/
/*				UINT_PTR		:	メッセージ									*/
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