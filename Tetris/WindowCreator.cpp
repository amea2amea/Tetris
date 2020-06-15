/*------------------*/
/* インクルード		*/
/*------------------*/
#include "WindowCreator.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CWindowCreator		:	コンストラクタ ( 引数なし )				*/
/*																				*/
/*==============================================================================*/
CWindowCreator::CWindowCreator()	:
				m_Clase_Name(_T("WinMain"))
			,	m_Title(_T("Window"))
			,	m_IsFullScreen(WindowCreatorNS::DEFAULT_SCREEN_MODE)
			,	m_WindowWidth(WindowCreatorNS::DEFAULT_WINDOW_WIDTH)
			,	m_WindowHeight(WindowCreatorNS::DEFAULT_WINDOW_HEIGHT)

{
	m_hInstance = NULL;
	m_hWnd		= NULL;
	m_hFont		= NULL;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CWindowCreators	:	コンストラクタ ( 引数あり )					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[引数]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CWindowCreator::CWindowCreator(LPTSTR class_name, LPTSTR title_name, bool displaymode, long window_width, long window_height) :
				m_Clase_Name(class_name)
			,	m_Title(title_name)
			,	m_IsFullScreen(displaymode)
			,	m_WindowWidth(window_width)
			,	m_WindowHeight(window_height)
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		~CControlProcess			:	デストラクタ					*/
/*																				*/
/*==============================================================================*/
CWindowCreator::~CWindowCreator()
{
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
bool CWindowCreator::Create(HINSTANCE hInstance)
{

	/********************************/
	/*	ウィンドウクラスの設定		*/
	/********************************/
	MyRegisterClass(hInstance);

	/****************************/
	/*	ウィンドウの作成		*/
	/****************************/
	if (!MyCreateWindow(hInstance))
	{
		return FALSE;
	}

	/****************************/
	/*	フォントの作成			*/
	/****************************/
	MyCreateFont(TETRIS_FONT, TETRIS_FONT_HIGHT, TETRIS_FONT_STAET_ANGLE);

	/********************************/
	/*	インスタンスハンドルの取得	*/
	/********************************/
	SetInstanceHandle(hInstance);

	return TRUE;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MyRegisterClass				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool						:	ウィンドウの作成				*/
/*												成功 -> 1,	失敗 -> 0			*/
/*	[引数]		HINSTANCE	hInstance		:	インスタンスのハンドル			*/
/*																				*/
/*==============================================================================*/
ATOM CWindowCreator::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW		wcex;														/*	ウィンドウクラス									*/

	/****************************/
	/*	ウィンドウクラスの設定	*/
	/****************************/
	wcex.cbSize			= sizeof(wcex);											/*	構造体のサイズ										*/
	wcex.style			= CS_HREDRAW| CS_VREDRAW;								/*	ウィンドウサイズ変更時の再描画						*/
	wcex.lpfnWndProc	= AppWndProc;											/*	ウィンドウプロシージャの関数名						*/
	wcex.cbClsExtra		= 0;													/*	拡張クラスのメモリ									*/
	wcex.cbWndExtra		= 0;													/*	拡張ウィンドウのメモリ								*/
	wcex.hInstance		= hInstance;											/*	インスタンスへのハンドル							*/
	wcex.hIcon			= NULL;													/*	ウィンドウのアイコン								*/
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);							/*	ウィンドウ上にある場合のカーソル -> 矢印を設定		*/
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);					/*	背景ブラシ											*/
	wcex.lpszMenuName	= NULL;													/*	メニューのリソース名								*/
	wcex.lpszClassName	= m_Clase_Name;											/*	ウィンドウクラス名									*/
	wcex.hIconSm		= NULL;													/*	ウィンドウの小さいアイコン							*/
	
	/****************************/
	/*	ウィンドウクラスの登録	*/
	/****************************/
	if (RegisterClassEx(&wcex) == 0)											/*	ウィンドウクラスの登録がエラーならば				*/
		return 0;


	return RegisterClassExW(&wcex);

}
/*==============================================================================*/
/*																				*/
/*	[関数]		MyCreateWindow				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool						:	ウィンドウの作成				*/
/*												成功 -> 1,	失敗 -> 0			*/
/*	[引数]		HINSTANCE	hInstance		:	インスタンスのハンドル			*/
/*																				*/
/*==============================================================================*/
bool CWindowCreator::MyCreateWindow(HINSTANCE hInstance)
{
	/********************************/
	/*	ウィンドウスタイルの設定	*/
	/********************************/
	ULONG_PTR		style = 0;														/*	ウィンドウスタイルの設定							*/

	if (m_IsFullScreen)																/*	フルスクリーンの設定であれば						*/
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}

	/********************************/
	/*	ウィンドウの作成			*/
	/********************************/
	HWND hwnd = ::CreateWindow(		m_Clase_Name									/*	ウィンドウクラス名									*/
								,	m_Title											/*	ウィンドウタイトル名								*/
								,	static_cast<DWORD>(style)			 			/*	ウィンドウスタイル									*/
								,	CW_USEDEFAULT									/*	ウィンドウの水平位置 ( デフォルト )					*/
								,	CW_USEDEFAULT									/*	ウィンドウの垂直位置 ( デフォルト )					*/
								,	m_WindowWidth									/*	ウィンドウ幅										*/
								,	m_WindowHeight									/*	ウィンドウ高さ										*/
								,	(HWND)NULL										/*	親ウィンドウ										*/
								,	(HMENU)NULL										/*	メニュー											*/
								,	hInstance										/*	インスタンスへのハンドル							*/
								,	(LPVOID)NULL									/*	ウィンドウパラメータ								*/
								);

	if (!hwnd)																		/*	ウィンドウ作成が失敗したらならば					*/
	{
		return FALSE;
	}
	
	/*----------------------------------------------------------------------*/
	/*	ウィンドウの場合、クライアント領域がWINDOW_WIDTH × WINDOW_HEIGHT	*/
	/*	になるようにクライアント領域を再設定								*/
	/*----------------------------------------------------------------------*/
	if ( !m_IsFullScreen )															/*	フルスクリーンの設定でなければ						*/
	{
		RECT ClientRect;
		GetClientRect(hwnd, &ClientRect);											/*	現在のクライアント領域を取得						*/
		
		/****************************/
		/*	ウィンドウの再設定		*/
		/****************************/
		MoveWindow(	hwnd															/*	ウィンドウハンドル									*/
				,	ClientRect.left													/*	左													*/
				,	ClientRect.top													/*	上													*/
				,	m_WindowWidth + (m_WindowWidth - ClientRect.right )				/*	右													*/
				,	m_WindowHeight + (m_WindowHeight - ClientRect.bottom )			/*	下													*/
				,	true															/*	ウィンドウの再描画設定								*/
			);
	}

	/****************************/
	/*	ウィンドウの表示		*/
	/****************************/
	ShowWindow(hwnd, SW_SHOW);														/*	ウィンドウを表示									*/
	UpdateWindow(hwnd);																/*	ウインドウプロシージャを直接呼び、WM_PAINTを処理	*/

	
	/********************************/
	/*	ウィンドウハンドルの取得	*/
	/********************************/
	SetWindowHandle(hwnd);

	return TRUE;

}
/*==============================================================================*/
/*																				*/
/*	[関数]		MyCreateFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool						:	ウィンドウの作成				*/
/*												成功 -> 1,	失敗 -> 0			*/
/*	[引数]		HINSTANCE	hInstance		:	インスタンスのハンドル			*/
/*																				*/
/*==============================================================================*/
void CWindowCreator::MyCreateFont(LPCTSTR font_type, int height, int angle)
{
	m_hFont = CreateFont(	height						/*	フォント高さ					*/
						,	0							/*	文字幅 ( 0の場合は自動調整 )	*/
						,	angle						/*	テキストの角度					*/
						,	0							/*	文字開始位置の水平軸の角度		*/
						,	FW_REGULAR					/*	フォント太さ					*/
						,	FALSE						/*	斜体 ( イタリック体 )			*/
						,	FALSE						/*	アンダーライン					*/
						,	FALSE						/*	打ち消し線						*/
						,	SHIFTJIS_CHARSET			/*	文字セット						*/
						,	OUT_DEFAULT_PRECIS			/*	出力精度						*/
						,	CLIP_DEFAULT_PRECIS			/*	クリッピング精度				*/
						,	PROOF_QUALITY				/*	出力品質						*/
						,	FIXED_PITCH | FF_MODERN		/*	ピッチとフォントファミリ		*/
						,	font_type					/*	書体名							*/
				); 

	return ;

}
/*==============================================================================*/
/*																				*/
/*	[関数]		GetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
HWND CWindowCreator::GetWindowHandle() const
{
	return m_hWnd;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetWindowFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
HFONT CWindowCreator::GetWindowHFont() const
{
	return m_hFont;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetInstanceHandle			:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CWindowCreator::SetInstanceHandle(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CWindowCreator::SetWindowHandle(HWND hwnd)
{
	m_hWnd = hwnd;
	return;
}