#ifndef _GRAPHICS_H
#define _GRAPHICS_H 

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "Array1D.h"
#include "Array2D.h"

/*--------------*/
/*	�\����		*/
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
/*	�`��N���X		*/
/*------------------*/
class CGraphics
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CGraphics();

	/*	�f�X�g���N�^	*/
	virtual	~CGraphics();

	/*	�����z�֐�	*/
	virtual void			Draw() = 0;
	virtual void			DrawGradation(long, long, long, long, COLORREF, char);

	/*	�֐�	*/
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
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	��`�p�ϐ� ( const )	*/
	static const short			TEXT_MAX_BYTE = 1024;	/*	�e�L�X�g�̍ő�o�C�g��				*/

private:
	HWND						m_hWnd;
	HDC							m_hdc;
	HFONT						m_hFont;
	HDC							m_Memoryhdc;
	HBITMAP						m_hBitmap;
	TEXTMETRIC					m_textmetric;
	std::vector<GeometryDraw>	m_GeometryDraw;			/*	�`��p�̐}�`�̏��					*/
	std::vector<TextRectDraw>	m_TextRectDraw;			/*	�`��p�̃e�L�X�g(�����`)�̐ݒ���	*/
	std::vector<TextOutDraw>	m_TextOutDraw;			/*	�`��p�̃e�L�X�g�̐ݒ���			*/
	short						m_DrawFlag;				/*	�`�悷�邽�߂̃r�b�g�t���O			*/
														/*	bit0:	�l�p�`�̕`��				*/
														/*	bit1:	�e�L�X�g(�l�p�`)�̕`��		*/
														/*	bit2:	�e�L�X�g�̕`��				*/

};
#endif