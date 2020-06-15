/*------------------*/
/* インクルード		*/
/*------------------*/
#include "ControlProcess.h"
#include "ProcessManger.h"


/*==============================================================================*/
/*																				*/
/*	[関数]		Process			:	コンストラクタ								*/
/*																				*/
/*==============================================================================*/
CProcessManger::CProcessManger()
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		~CProcessManger	:	デストラクタ								*/
/*																				*/
/*==============================================================================*/
CProcessManger::~CProcessManger()
{
}


/*==============================================================================*/
/*																				*/
/*	[関数]		Create			:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	ProcessCore*	:												*/
/*	[引数]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CFameWork* CProcessManger::Create(HINSTANCE hInstance, LPTSTR lpCmdLine)
{
	CFameWork*			pframewoke		= 0;
	CControlProcess*	pcontrolprocess = 0;
	
	if (!IsAnotherInstance())
	{
		pframewoke = new CControlProcess(hInstance, lpCmdLine);

		if (pframewoke != NULL)
		{
			pcontrolprocess = (CControlProcess*)pframewoke;
			pcontrolprocess->Create(hInstance);
			pcontrolprocess->Initialize();
		}
	}

	return pframewoke;
}

/*==================================================================================*/
/*																					*/
/*	[関数]		IsAnotherInstance	:	ウィンドウの2重起動禁止						*/
/*										( ミューテックス処理 )						*/
/*	--------------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	ture  -> インスタンスが存在してる			*/
/*										false -> 自分が唯一のインスタンスである		*/
/*	[引数]		void				:	なし										*/
/*																					*/
/*==================================================================================*/
bool CProcessManger::IsAnotherInstance()
{
	HANDLE hMutex;

	hMutex = ::OpenMutex(MUTEX_ALL_ACCESS				/*	セキュリティ記述子				*/
						, FALSE							/*	最初の所有者になるかどうか		*/
						, _T("MYMUTEX")					/*	オブジェクト名					*/
			);

	/********************************************/
	/*	インスタンスが存在しているかチェック	*/
	/********************************************/
	if ((hMutex != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
	{
		::CloseHandle(hMutex);
		return true;
	}

	return false;
}

