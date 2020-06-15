/*------------------*/
/* インクルード		*/
/*------------------*/
#include "ControlProcess.h"

/*------------------*/
/* extern宣言		*/
/*------------------*/
extern CControlProcess*		g_pAppWndProc;				/*	ウィンドウをコントロールするクラスのポインタ		*/

/*==============================================================================*/
/*																				*/
/*	[関数]		CControlProcess		:	コンストラクタ ( 引数なし )				*/
/*																				*/
/*==============================================================================*/
CControlProcess::CControlProcess()
{
	m_pWindowCreator	= new CWindowCreator();
	m_pInput			= new CInput();
	m_pGameLogic		= 0;
	m_pGraphics			= 0;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CControlProcess	:	コンストラクタ ( 引数あり )					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[引数]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CControlProcess::CControlProcess(HINSTANCE hInstance, LPTSTR lpCmdLine) :
			CFameWork(hInstance, lpCmdLine)
		,	m_hMutex(NULL)
		,	m_hMutexCP(NULL)
{
	m_pWindowCreator	= new CWindowCreator();
	m_pInput			= new CInput();
	m_pGameLogic		= 0;
	m_pGraphics			= 0;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		~CControlProcess			:	デストラクタ					*/
/*																				*/
/*==============================================================================*/
CControlProcess::~CControlProcess()
{
	delete m_pWindowCreator;
	delete m_pInput;
	m_pGameLogic = 0;
	m_pGraphics = 0;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Initialize					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
bool CControlProcess::Initialize()
{
	/********************************/
	/*	ウィンドウハンドルの取得	*/
	/********************************/
	SetWindowHandle(m_pWindowCreator->GetWindowHandle());

	if (m_pGraphics != NULL)
	{
		m_pGraphics->SetWindowHandle(m_pWindowCreator->GetWindowHandle());
		m_pGraphics->SetWindowHFont(m_pWindowCreator->GetWindowHFont());
		m_pGraphics->Create();
	}
	else
	{
		return false;
	}

	/********************/
	/*	各種初期設定	*/
	/********************/
	m_pInput->Initialize(GetWindowHandle(), 0);

	/****************************************************************/
	/*	高分解能パフォーマンスカウンタの周波数 ( 更新頻度 )を取得	*/
	/****************************************************************/
	if (QueryPerformanceFrequency(&m_TimerFreq) == false)
	{
		;
	}

	/************************************/
	/*	1ループ処理の開始時間を取得		*/
	/************************************/
	QueryPerformanceCounter(&m_TimeStart);

	return true;
}


/*==============================================================================*/
/*																				*/
/*	[関数]		Create					:										*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool						:	ウィンドウの作成				*/
/*												成功 -> 1,	失敗 -> 0			*/
/*	[引数]		HINSTANCE	hInstance		:	インスタンスのハンドル			*/
/*				UINT_PTR	nCmdShow		:	ウィンドウ表示の指定			*/
/*																				*/
/*==============================================================================*/
bool CControlProcess::Create(HINSTANCE hInstance)
{
	bool ret = false;
	
	if (m_pWindowCreator == NULL)
		return ret;

	if (m_pInput == NULL)
		return ret;

	/************************************/
	/*	ウィンドウのポインタを取得		*/
	/************************************/
	g_pAppWndProc = this;

	/************************************/
	/*	ウィンドウの作成				*/
	/************************************/
	ret = m_pWindowCreator->Create(hInstance);

	return ret;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MessageLoop					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CControlProcess::MessageLoop()
{
	/*	
		Note 1:
			GetMessageとPeekMessageの違い
				処理するメッセージが無い場合、
				GetMessageはメッセージを待ちますが、PeekMessageは待ちません	
				つまり、whileのループ処理が永遠に続くことになります。
	
		Note 2:
			TranslateMessageとは				
				TranslateMessageは、仮想キーメッセージをASCIIコードに変換し、
				WM_CHAR, WM_SYSCHARを新しく作り出してポストするだけで	
				元のメッセージはそのままポストされる		
	*/					
	
	MSG	msg;
	int ret	= 0;

	while (1)
	{
		ret = ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);				/*	メッセージを取得									*/

		if (msg.message == WM_QUIT)										/*	終了メッセージならば								*/
		{
			break;														/*	ループから抜ける									*/
		}
		else if(ret == 0)												/*	何も処理されない ( アイドル時間ならば )				*/
		{
			Update();													/*	更新処理を行う										*/
		}
		else															/*	何か処理されたらならば								*/
		{
			::TranslateMessage(&msg);									/*	仮想キーメッセージを文字メッセージに変換			*/
			::DispatchMessage(&msg);									/*	ウィンドウプロシージャにメッセージを送る			*/
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Update						:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CControlProcess::Update()
{
	/********************************/
	/*	フレームレートの更新		*/
	/********************************/
	if (!FramesTime())
		return;

	/****************/
	/*	更新処理	*/
	/****************/
	if(m_pGameLogic != NULL)
		m_pGameLogic->Logic(m_pInput);

	/****************/
	/*	描画処理	*/
	/****************/
	if (m_pGraphics != NULL)
		m_pGraphics->DrawMain();

	/************************/
	/*	入力のクリア処理	*/
	/************************/
	m_pInput->Clear(inputNS::KEYS_PRESSED);			/*	入力の情報をクリア		*/

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		FramesTime					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
bool CControlProcess::FramesTime()
{
	/************************************/
	/*	1ループ処理の終了時間を取得		*/
	/************************************/
	QueryPerformanceCounter(&m_TimeEnd);

	/********************************************************************/
	/*	1ループに掛かる経過時間を計算									*/
	/*		処理時間 = 1周期の時間 ÷ 周波数 ( 1秒あたりのCPU処理回数 )	*/
	/********************************************************************/
	if(m_TimerFreq.QuadPart != 0)
		m_FrameTime = (double)(m_TimeEnd.QuadPart - m_TimeStart.QuadPart) / (double)m_TimerFreq.QuadPart;

	/************************************/
	/*	1ループに掛かる経過時間を計算	*/
	/************************************/
	if (m_FrameTime < FramesRateNS::MIN_FRAME_TIME)														/*	希望するフレーム時間に対して経過時間が短いならば	*/
	{
		/************************************************/
		/*	CPU処理時間において余った時間がある場合		*/
		/************************************************/
		m_SleepTime = (DWORD)((FramesRateNS::MIN_FRAME_TIME - m_FrameTime) * 1000);						/*	余った時間は待機時間とするため計算する				*/
		Sleep(m_SleepTime);																				/*	メッセージ処理が行われるようにするために待つ		*/

		return false;
	}
	else if (m_FrameTime > 0.0)
	{
		/********************************************/
		/*	ゲーム1秒あたりのフレーム数				*/
		/*		( 1秒間に何回メインループを回るか )	*/
		/********************************************/
		m_fps = (m_fps * 0.99f) + (0.01f / m_FrameTime);												/*	平均 fps ( ゲーム1秒あたりのフレーム数 )			*/
	}

	if (m_FrameTime > FramesRateNS::MAX_FRAME_TIME)														/*	フレーム時間が非常に遅いならば						*/
	{
		m_FrameTime = FramesRateNS::MAX_FRAME_TIME;														/*	フレーム時間を最大値に設定							*/
	}

	/****************************************/
	/*	前回の終了時間を開始時間に設定		*/
	/****************************************/
	m_TimeStart = m_TimeEnd;

	return true;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		DispatchEvent	:	ウィンドウプロシージャ						*/
/*									( ウィンドウコールバック関数 )				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	LRESULT WINAPI 	:	標準のウィンドウプロシージャの処理を行う	*/
/*	[引数]		HWND			:	ウィンドウハンドル							*/
/*				UINT_PTR		:	メッセージ									*/
/*				WPARAM			:												*/
/*				LPARAM			:												*/
/*																				*/
/*==============================================================================*/
LRESULT CALLBACK CControlProcess::DispatchEvent(HWND hwnd, UINT_PTR msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		/****************************/
		/*	終了					*/
		/****************************/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		/****************************/
		/*	ウィンドウが作成された	*/
		/****************************/
	case WM_CREATE:
		m_pWindowCreator->MyCreateFont(NULL, 100, 0);
		return 0;

		/****************************/
		/*	キーの押し下げ			*/
		/****************************/
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		m_pInput->KeyDown(wParam);
		return 0;

		/****************************/
		/*	キーの押し上げ			*/
		/****************************/
	case WM_KEYUP:
	case WM_SYSKEYUP:
		m_pInput->KeyUp(wParam);
		return 0;

		/****************************/
		/*	文字が入力された		*/
		/****************************/
	case WM_CHAR:
		m_pInput->TextIn(wParam);
		return 0;

		/****************************/
		/*	設定キーが押された		*/
		/****************************/
	case WM_INPUT:
		m_pInput->MouseRawIn(lParam);
		return 0;

		/****************************/
		/*	左クリックの押し下げ	*/
		/****************************/
	case WM_LBUTTONDOWN:
		m_pInput->SetMouseLButton(true);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	左クリックの押し上げ	*/
		/****************************/
	case WM_LBUTTONUP:
		m_pInput->SetMouseLButton(false);
		m_pInput->MouseIn(lParam);
		return 0;

		/************************************/
		/*	マウスの中央ボタンの押し下げ	*/
		/************************************/
	case WM_MBUTTONDOWN:
		m_pInput->SetMouseMButton(true);
		m_pInput->MouseIn(lParam);
		return 0;

		/************************************/
		/*	マウスの中央ボタンの押し上げ	*/
		/************************************/
	case WM_MBUTTONUP:
		m_pInput->SetMouseMButton(false);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	右クリックの押し下げ	*/
		/****************************/
	case WM_RBUTTONDOWN:
		m_pInput->SetMouseRButton(true);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	右クリックの押し上げ	*/
		/****************************/
	case WM_RBUTTONUP:
		m_pInput->SetMouseRButton(false);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	マウスの移動された		*/
		/****************************/
	case WM_MOUSEMOVE:
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************************/
		/*	多機能マウスのボタンメッセージ		*/
		/****************************************/
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		m_pInput->SetMouseXButton(wParam);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	描画メッセージ			*/
		/****************************/
	case WM_PAINT:
		if (m_pGraphics != NULL)
			m_pGraphics->DrawMain();
		return 0;

	default:
		break;

	}

	return DefWindowProc(hwnd, static_cast<UINT>(msg), wParam, lParam);

}
