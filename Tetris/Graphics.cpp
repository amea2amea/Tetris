/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Graphics.h"

/*==============================================================*/
/*																*/
/*	[関数]		CGraphics	:	コンストラクタ ( 引数なし )		*/
/*																*/
/*==============================================================*/
CGraphics::CGraphics()
{
	m_hWnd		= NULL;
	m_hdc		= NULL;
	m_Memoryhdc = NULL;
	m_hBitmap	= NULL;
	m_DrawFlag			= 0;				/*	ピクセルごとの描画フラグを無効				*/
	m_GeometryDraw.resize(0);				/*	描画用の図形情報を初期化					*/
	m_TextRectDraw.resize(0);				/*	描画用のテキスト(長方形)の設定情報を初期化	*/
	m_TextOutDraw.resize(0);				/*	描画用のテキストの設定情報を初期化			*/
}

/*======================================================*/
/*														*/
/*	[関数]		~CGraphics	:	デストラクタ			*/
/*														*/
/*======================================================*/
CGraphics::~CGraphics()
{
	/************************/
	/*	メモリの解放		*/
	/************************/
	MemoryClear();

	/************************/
	/*	オブジェクトの解放	*/
	/************************/
	DeleteDC(m_hdc);
	DeleteDC(m_Memoryhdc);
	DeleteObject(m_hBitmap);

	/************************/
	/*	ポインタの初期化	*/
	/************************/
	m_hWnd		= NULL;
	m_hdc		= NULL;
	m_hFont		= NULL;
	m_Memoryhdc = NULL;
	m_hBitmap	= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		MemoryClear			:	メモリクリア							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CGraphics::MemoryClear()
{
	m_GeometryDraw.clear();					/*	描画用の図形情報を初期化				*/
	m_TextRectDraw.clear();					/*	描画用の図形情報を初期化				*/
	m_TextOutDraw.clear();					/*	描画用の図形情報を初期化				*/
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DrawMain			:	描画処理								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CGraphics::DrawMain()
{
	PAINTSTRUCT		ps;												/*	描画情報									*/
	RECT			rect;											/*	ウィンドウサイズの取得用					*/

	GetClientRect(m_hWnd, &rect);									/*	ウィンドウサイズの取得						*/
	InvalidateRect(m_hWnd, &rect, NULL);

	m_hdc = BeginPaint(m_hWnd, &ps);								/*	デバイスコンテキストのハンドルを取得		*/

	if (	(m_hdc != NULL)											/*	デバイスコンテキストが取得できているならば	*/
		&&	(m_Memoryhdc != NULL))									/*	ウィンドウハンドルが取得できているならば	*/
	{
		/************************/
		/*	描画情報を設定		*/
		/************************/
		DrawClear(m_Memoryhdc);

		/************************/
		/*	描画情報を設定		*/
		/************************/
		Draw();

		/****************/
		/*	描画処理	*/
		/****************/
		SetMapMode(m_Memoryhdc, MM_TEXT);							/*	描画モードをピクセル単位の設定				*/

		if (m_DrawFlag & BIT0)										/*	長方形の描画フラグを有効ならば				*/
			DrawRectAngle(m_Memoryhdc);								/*	長方形の描画								*/

		if (m_DrawFlag & BIT1)										/*	テキスト(長方形)の描画フラグを有効ならば	*/
			DrawTextRect(m_Memoryhdc);								/*	テキスト(長方形指定)の描画					*/

		if (m_DrawFlag & BIT2)										/*	テキストの描画フラグを有効ならば			*/
			DrawTextOut(m_Memoryhdc);								/*	テキストの描画								*/


		/****************************/
		/*	ビットマップを転送		*/
		/****************************/								/*	ビットマップをVRAMに転送					*/
		BitBlt(m_hdc												/*	コピー先のデバイスコンテキストのハンドル	*/
			, rect.left												/*	コピー先のウィンドウの左上端 ( X座標 )		*/
			, rect.top												/*	コピー先のウィンドウの左上端 ( Y座標 )		*/
			, rect.right											/*	コピー先のウィンドウの右下端 ( X座標 )		*/
			, rect.bottom											/*	コピー先のウィンドウの右下端 ( Y座標 )		*/
			, m_Memoryhdc											/*	コピー元のデバイスコンテキストのハンドル	*/
			, rect.left												/*	コピー元のウィンドウの左上端 ( X座標 )		*/
			, rect.top												/*	コピー元のウィンドウの左上端 ( Y座標 )		*/
			, SRCCOPY												/*	コピー元からコピー先へ長方形をコピー		*/
			);
	}

	EndPaint(m_hWnd, &ps);											/*	デバイスコンテキストのハンドルを返却		*/
	m_DrawFlag			= 0;										/*	ピクセルごとの描画フラグを無効				*/
	m_GeometryDraw.resize(0);										/*	描画用の図形情報を初期化					*/
	m_TextRectDraw.resize(0);										/*	描画用のテキスト(長方形)の設定情報を初期化	*/
	m_TextOutDraw.resize(0);										/*	描画用のテキストの設定情報を初期化			*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Init				:	初期化									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CGraphics::Create()
{
	HDC		hdc		= NULL;
	RECT	rect;

	/****************************************/
	/*	ダブルバッファのビットマップを作成	*/
	/****************************************/
	hdc = GetDC(m_hWnd);                      							/*	デバイスコンテキストのハンドルを取得	*/
	GetClientRect(m_hWnd, &rect);  										/*	ウィンドウサイズを取得					*/
	m_hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);	/*	ウィンドウサイズのビットマップを作成	*/
	m_Memoryhdc = CreateCompatibleDC(hdc);								/*	メモリデバイスコンテキストを作成		*/
	SelectObject(m_Memoryhdc, m_hBitmap);								/*	メモリデバイスコンテキストに紐付け		*/

	/****************************/
	/*	フォントの情報を取得	*/
	/****************************/
	if (m_hFont != NULL)
	{
		SelectObject(hdc, m_hFont);
		GetTextMetrics(hdc, &m_textmetric);
	}

	ReleaseDC(m_hWnd, hdc);

	return TRUE;
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
void CGraphics::SetWindowHandle(HWND hwnd)
{
	m_hWnd = hwnd;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetWindowHFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetWindowHFont(HFONT hFont)
{
	m_hFont = hFont;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetGradation	:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND			:												*/
/*	[引数]		long			:												*/
/*				long			:												*/
/*				long			:												*/
/*				long			:												*/
/*				COLORREF		:												*/
/*				char			:	グラデーションを行う色						*/
/*										BIT0	->	赤色 ( 輝度をあげていく )　	*/													
/*										BIT1	->	赤色 ( 輝度をさげていく )　	*/
/*										BIT2	->	青色 ( 輝度をあげていく )　	*/	
/*										BIT3	->	青色 ( 輝度をさげていく )　	*/	
/*										BIT4	->	緑色 ( 輝度をあげていく )　	*/
/*										BIT5	->	緑色 ( 輝度をさげていく )　	*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawGradation(long StartPosX, long StartPosY, long EndPosX, long EndPosY, COLORREF rgb, char type)
{
	COLORREF	color;
	BYTE		red					= GetRValue(rgb);
	BYTE		green				= GetGValue(rgb);
	BYTE		blue				= GetBValue(rgb);
	FLOAT		red_ratio_calc		= 0;
	FLOAT		green_ratio_calc	= 0;
	FLOAT		blue_ratio_calc		= 0;
	LONG		width				= 0;

	if (m_Memoryhdc == NULL)
		return;

	if (	(StartPosX >= EndPosX) 
		||	(StartPosY >= EndPosY)
		||	(EndPosX == 0 ) 
		||	(EndPosY == 0))
		return;

	width				= EndPosX - StartPosX;												/*	描画する領域を取得							*/
	red_ratio_calc		= static_cast<float> (red) / static_cast<float> (width);			/*	選択色の領域と描画領域の比率を取得 ( 赤 )	*/
	green_ratio_calc	= static_cast<float> (green) / static_cast<float> (width);			/*	選択色の領域と描画領域の比率を取得 ( 緑 )	*/
	blue_ratio_calc		= static_cast<float> (blue) / static_cast<float> (width);			/*	選択色の領域と描画領域の比率を取得 ( 青 )	*/

	for (int y = StartPosY; y <= EndPosY; y++)
	{
		for (int x = StartPosX; x <= EndPosX; x++)
		{		
			BYTE red_ratio		= 0;
			BYTE green_ratio	= 0;
			BYTE blue_ratio		= 0;

			/****************************/
			/*	描画比率の計算			*/
			/****************************/
			if (type & 0x01)
				red_ratio = static_cast<BYTE>(abs(x - StartPosX) * red_ratio_calc);
			else if (type & 0x02)
				red_ratio = static_cast<BYTE>(red - (abs(x - StartPosX) * red_ratio_calc));

			if (type & 0x04)
				green_ratio = static_cast<BYTE>(abs(x - StartPosX) * green_ratio_calc);
			else if (type & 0x08)
				green_ratio = static_cast<BYTE>(green - (abs(x - StartPosX) * green_ratio_calc));
			
			if (type & 0x10)
				blue_ratio = static_cast<BYTE>(abs(x - StartPosX) * blue_ratio_calc);
			else if (type & 0x20)
				blue_ratio = static_cast<BYTE>(blue - (abs(x - StartPosX) * blue_ratio_calc));
			
			/****************************/
			/*	現在の描画色の設定		*/
			/****************************/
			if ((red) && (red != red_ratio))
				red_ratio	= (red_ratio) % red;
			if ((green) && (green != green_ratio))
				green_ratio = (green_ratio) % green;
			if ((blue) && (blue != blue_ratio))
				blue_ratio	= (blue_ratio) % blue;

			/****************************/
			/*	ピクセルごとに描画		*/
			/****************************/
			color = RGB(red_ratio, green_ratio, blue_ratio);								/*	ピクセル位置に設定する色を取得			*/
			SetPixel(m_Memoryhdc, x, y, color);												/*	ピクセル位置に色を設定					*/
		}
	}

	return;
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
HWND CGraphics::GetWindowHandle() const
{
	return m_hWnd;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetInstanceHandle			:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HINSTANCE					:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
HDC CGraphics::GetDeviceContext() const
{
	return m_hdc;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetRectAngle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		UINT 						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetRectAngle(UINT left, UINT top, UINT right, UINT bottom, UINT style, UINT line_width, COLORREF pen_color, COLORREF brush_color)
{
	/****************************/
	/*	描画用の設定			*/
	/****************************/
	m_DrawFlag	|= BIT0;									/*	描画フラグの設定				*/

	/****************************/
	/*	描画情報を設定			*/
	/****************************/
	GeometryDraw gemetrydraw;
	gemetrydraw.left		= left;
	gemetrydraw.top			= top;
	gemetrydraw.right		= right;
	gemetrydraw.left		= left;
	gemetrydraw.bottom		= bottom;
	gemetrydraw.style		= style;
	gemetrydraw.line_width	= line_width;
	gemetrydraw.pen_color	= pen_color;
	gemetrydraw.brush_color = brush_color;
	m_GeometryDraw.push_back(gemetrydraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetTextRect					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		UINT 						:									*/
/*				UINT						:									*/
/*				LPCTSTR						:									*/
/*				UINT						:									*/
/*				LPRECT						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetTextRect(UINT left, UINT top, UINT right, UINT bottom, std::string str, UINT textpitch, UINT format, COLORREF color)
{
	/****************************/
	/*	描画用の設定			*/
	/****************************/
	m_DrawFlag |= BIT1;										/*	描画フラグの設定							*/

	/****************************/
	/*	描画情報を設定			*/
	/****************************/
	TextRectDraw textrectdraw;
	textrectdraw.left		= left;
	textrectdraw.top		= top;
	textrectdraw.right		= right;
	textrectdraw.bottom		= bottom;
	textrectdraw.string		= str;
	textrectdraw.format		= format;
	textrectdraw.textpitch	= textpitch;
	textrectdraw.color		= color;
	m_TextRectDraw.push_back(textrectdraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetTextOut					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		UINT 						:									*/
/*				UINT						:									*/
/*				LPCTSTR						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetTextOut(UINT x_start, UINT y_start, std::string str, UINT textpitch, COLORREF color)
{
	/****************************/
	/*	描画用の設定			*/
	/****************************/
	m_DrawFlag |= BIT2;										/*	描画フラグの設定							*/

	/****************************/
	/*	描画情報を設定			*/
	/****************************/
	TextOutDraw textoutdraw;
	textoutdraw.x_start		= x_start;
	textoutdraw.y_start		= y_start;
	textoutdraw.string		= str;
	textoutdraw.textpitch	= textpitch;
	textoutdraw.color		= color;
	m_TextOutDraw.push_back(textoutdraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		DrawRectAngle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned					:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawRectAngle(HDC hdc)
{
	for (unsigned int count = 0; count < m_GeometryDraw.size(); count++)
	{
		HPEN		hpen		= NULL;
		HBRUSH		hbrush		= NULL;
		HPEN		oldhpen		= NULL;
		HBRUSH		oldhbrush	= NULL;
		long		left		= m_GeometryDraw[count].left;
		long		top			= m_GeometryDraw[count].top;
		long		right		= m_GeometryDraw[count].right;
		long		bottom		= m_GeometryDraw[count].bottom;
		long		style		= m_GeometryDraw[count].style;
		long		line_width	= m_GeometryDraw[count].line_width;
		COLORREF	pen_color	= m_GeometryDraw[count].pen_color;
		COLORREF	brush_color = m_GeometryDraw[count].brush_color;

		if ((style < 0) || (style > PS_DASHDOTDOT))
		{
			style = PS_SOLID;
		}

		/****************************/
		/*	長方形の描画			*/
		/****************************/
		if (line_width == 0)
		{
			oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));					/*	ペンの設定 ( ブラシなし )		*/
		}
		else
		{
			hpen = CreatePen(style, line_width, pen_color);									/*	ペンの作成						*/
			oldhpen = (HPEN)SelectObject(hdc, hpen);										/*	ペンの設定						*/
		}

		hbrush = CreateSolidBrush(brush_color);												/*	ブラシの作成					*/
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush);										/*	ブラシの設定 					*/
		SetBkMode(hdc, OPAQUE);																/*	背景を塗りつぶしに設定			*/
		Rectangle(hdc, left, top, right, bottom);											/*	長方形を設定					*/

		/****************************/
		/*	オブジェクトの消去		*/
		/****************************/
		SetBkMode(hdc, TRANSPARENT);														/*	背景を透明に設定しておく		*/
		SelectObject(hdc, oldhpen);															/*	ペンの設定を元に戻す			*/
		SelectObject(hdc, oldhbrush);														/*	ブラシの設定を元に戻す			*/

		if (hpen != NULL)
			DeleteObject(hpen);																/*	作成したペンを削除				*/

		if (hbrush != NULL)
			DeleteObject(hbrush);															/*	作成したブラシを削除			*/

		if (oldhpen != NULL)
			DeleteObject(oldhpen);															/*	作成したペンを削除				*/

		if (oldhbrush != NULL)
			DeleteObject(oldhbrush);														/*	作成したブラシを削除			*/
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		DrawTextRect				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned					:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawTextRect(HDC hdc)
{
	for (unsigned int count = 0; count < m_TextRectDraw.size(); count++)
	{
		RECT		rect;
		COLORREF	old_color;
		const char*	cs							= m_TextRectDraw[count].string.c_str();
		UINT		format						= m_TextRectDraw[count].format;
		UINT		textpitch					= m_TextRectDraw[count].textpitch;
		COLORREF	color						= m_TextRectDraw[count].color;
		TCHAR		strBuffer[TEXT_MAX_BYTE]	= {};
		size_t		size;

		rect.left	= m_TextRectDraw[count].left;
		rect.top	= m_TextRectDraw[count].top;
		rect.right	= m_TextRectDraw[count].right;
		rect.bottom = m_TextRectDraw[count].bottom;



#ifdef UNICODE
		mbstowcs_s(&size, strBuffer, TEXT_MAX_BYTE, cs, _TRUNCATE);
#else
		strcpy(strBuffer, cs);
#endif

		if (format == 0)
		{
			format = DT_WORDBREAK | DT_CENTER;
		}

		/********************/
		/*	文字の描画		*/
		/********************/
		SetBkMode(hdc, TRANSPARENT);
		old_color = SetTextColor(hdc, color);

		if (textpitch != NULL)
			SetTextCharacterExtra(hdc, textpitch);
			
		DrawText(	hdc
				,	strBuffer
				,	lstrlen(strBuffer)
				,	&rect
				,	format
			);

		SetTextColor(hdc, old_color);
	
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		DrawTextOut					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned					:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawTextOut(HDC hdc)
{
	for (unsigned int count = 0; count < m_TextOutDraw.size(); count++)
	{
		COLORREF	old_color;
		UINT		x_start						= m_TextOutDraw[count].x_start;
		UINT		y_start						= m_TextOutDraw[count].y_start;
		const char*	cs							= m_TextOutDraw[count].string.c_str();
		UINT		textpitch					= m_TextOutDraw[count].textpitch;
		COLORREF	color						= m_TextOutDraw[count].color;
		TCHAR		strBuffer[TEXT_MAX_BYTE]	= {};
		size_t		size;

#ifdef UNICODE
		mbstowcs_s(&size, strBuffer, TEXT_MAX_BYTE, cs, _TRUNCATE);
#else
		strcpy(strBuffer, cs);
#endif

		/********************/
		/*	文字の描画		*/
		/********************/
		SetBkMode(hdc, TRANSPARENT);
		old_color = SetTextColor(hdc, color);

		if (textpitch != NULL)
			SetTextCharacterExtra(hdc, textpitch);
		
		TextOut(	hdc
				,	x_start
				,	y_start * m_textmetric.tmHeight
				,	strBuffer
				,	lstrlen(strBuffer)
			);

		SetTextColor(hdc, old_color);

	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		DrawClear					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned					:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawClear(HDC hdc)
{
	HPEN		hpen		= NULL;
	HPEN		oldhpen		= NULL;
	HBRUSH		oldhbrush	= NULL;
	RECT		rect;																	/*	ウィンドウサイズの取得用		*/

	GetClientRect(m_hWnd, &rect);  														/*	ウィンドウサイズを取得			*/

	/****************************/
	/*	背景のクリア			*/
	/****************************/
	oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));						/*	ペンの設定						*/
	oldhbrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));					/*	ブラシの設定 ( ブラシなし )		*/
	SetBkMode(hdc, OPAQUE);																/*	背景は塗りつぶし				*/
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);						/*	長方形を設定					*/

	/****************************/
	/*	オブジェクトの消去		*/
	/****************************/
	SetBkMode(hdc, TRANSPARENT);														/*	背景を透明に設定しておく		*/
	SelectObject(hdc, oldhpen);															/*	ペンの設定を元に戻す			*/
	SelectObject(hdc, oldhbrush);														/*	ブラシの設定を元に戻す			*/

	if (hpen != NULL)
		DeleteObject(hpen);																/*	作成したペンを削除				*/

	if (oldhpen != NULL)
		DeleteObject(oldhpen);															/*	作成したペンを削除				*/

	if (oldhbrush != NULL)
		DeleteObject(oldhbrush);														/*	作成したブラシを削除			*/

	return;
}