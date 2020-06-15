#ifndef _GRAPHICS_H
#define _GRAPHICS_H 

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "Array1D.h"
#include "Array2D.h"

/*--------------*/
/*	構造体		*/
/*--------------*/
struct GeometryDraw
{
	UINT		left;
	UINT		top;
	UINT		right;
	UINT		bottom;
	UINT		style;
	UINT		line_width;
	COLORREF	pen_color;
	COLORREF	brush_color;
};

struct TextOutDraw
{
	UINT		x_start;
	UINT		y_start;
	std::string string;
	UINT		textpitch;
	COLORREF	color;
};

struct TextRectDraw
{
	UINT		left;
	UINT		top;
	UINT		right;
	UINT		bottom;
	std::string	string;
	UINT		textpitch;
	UINT		format;
	COLORREF	color;
};




/*------------------*/
/*	描画クラス		*/
/*------------------*/
class CGraphics
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CGraphics();

	/*	デストラクタ	*/
	virtual	~CGraphics();

	/*	純仮想関数	*/
	virtual void			Draw() = 0;
	virtual void			DrawGradation(long, long, long, long, COLORREF, char);

	/*	関数	*/
	bool					Create();
	void					DrawMain();
	void					SetWindowHandle(HWND);
	void					SetWindowHFont(HFONT);
	HWND					GetWindowHandle() const;
	HDC						GetDeviceContext() const;
	void					SetRectAngle(UINT, UINT, UINT, UINT, UINT, UINT, COLORREF, COLORREF);
	void					SetTextRect(UINT, UINT, UINT, UINT, std::string, UINT, UINT, COLORREF);
	void					SetTextOut(UINT, UINT, std::string, UINT, COLORREF);

private:
	void					DrawRectAngle(HDC);
	void					DrawTextRect(HDC);
	void					DrawTextOut(HDC);
	void					DrawClear(HDC);
	void					MemoryClear();

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/
	static const short			TEXT_MAX_BYTE = 1024;	/*	テキストの最大バイト数				*/

private:
	HWND						m_hWnd;
	HDC							m_hdc;
	HFONT						m_hFont;
	HDC							m_Memoryhdc;
	HBITMAP						m_hBitmap;
	TEXTMETRIC					m_textmetric;
	std::vector<GeometryDraw>	m_GeometryDraw;			/*	描画用の図形の情報					*/
	std::vector<TextRectDraw>	m_TextRectDraw;			/*	描画用のテキスト(長方形)の設定情報	*/
	std::vector<TextOutDraw>	m_TextOutDraw;			/*	描画用のテキストの設定情報			*/
	short						m_DrawFlag;				/*	描画するためのビットフラグ			*/
														/*	bit0:	四角形の描画				*/
														/*	bit1:	テキスト(四角形)の描画		*/
														/*	bit2:	テキストの描画				*/

};
#endif