#ifndef _WINDOW_CREATOR_H
#define _WINDOW_CREATOR_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"

/*--------------*/
/*	列挙体		*/
/*--------------*/

namespace WindowCreatorNS
{
	enum WINDOW_DEFAULT_SIZE						/*	ウィンドウのデフォルト定義									*/
	{
		DEFAULT_WINDOW_WIDTH		= 450,			/*	ウィンドウ幅												*/
		DEFAULT_WINDOW_HEIGHT		= 520,			/*	ウィンドウ高さ												*/
		DEFAULT_SCREEN_MODE			= 0				/*	ウィンドウの表示モード ( 0:ウィンドウ 1:フルスクリーン )	*/
	};
}

/*----------------------------------*/
/*	ウィンドウの操作クラス			*/
/*----------------------------------*/
class CWindowCreator
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CWindowCreator();
	CWindowCreator(LPTSTR, LPTSTR, bool, long, long);

	/*	デストラクタ	*/
	virtual	~CWindowCreator();

	/*	関数	*/
	bool		Create(HINSTANCE);
	ATOM		MyRegisterClass(HINSTANCE);
	bool		MyCreateWindow(HINSTANCE);
	void		MyCreateFont(LPCTSTR, int, int);
	HWND		GetWindowHandle() const;
	HFONT		GetWindowHFont() const;

private:
	/*	関数	*/
	void			SetInstanceHandle(HINSTANCE);
	void			SetWindowHandle(HWND);

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/
	LPCTSTR							TETRIS_FONT					= NULL;
	static const short				TETRIS_FONT_HIGHT			= 40;
	static const short				TETRIS_FONT_STAET_ANGLE		= 0;

private:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	HFONT		m_hFont;
	LPTSTR		m_Clase_Name;								/*	ウィンドウクラス名									*/
	LPTSTR		m_Title;									/*	ウィンドウ名										*/
	bool		m_IsFullScreen;								/*	スクリーンの表示モードの設定						*/
	long		m_WindowWidth;								/*	ウィンドウ幅										*/
	long		m_WindowHeight;								/*	ウィンドウ高さ										*/

};
#endif