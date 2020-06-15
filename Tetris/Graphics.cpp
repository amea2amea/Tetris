/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Graphics.h"

/*==============================================================*/
/*																*/
/*	[�֐�]		CGraphics	:	�R���X�g���N�^ ( �����Ȃ� )		*/
/*																*/
/*==============================================================*/
CGraphics::CGraphics()
{
	m_hWnd		= NULL;
	m_hdc		= NULL;
	m_Memoryhdc = NULL;
	m_hBitmap	= NULL;
	m_DrawFlag			= 0;				/*	�s�N�Z�����Ƃ̕`��t���O�𖳌�				*/
	m_GeometryDraw.resize(0);				/*	�`��p�̐}�`����������					*/
	m_TextRectDraw.resize(0);				/*	�`��p�̃e�L�X�g(�����`)�̐ݒ����������	*/
	m_TextOutDraw.resize(0);				/*	�`��p�̃e�L�X�g�̐ݒ����������			*/
}

/*======================================================*/
/*														*/
/*	[�֐�]		~CGraphics	:	�f�X�g���N�^			*/
/*														*/
/*======================================================*/
CGraphics::~CGraphics()
{
	/************************/
	/*	�������̉��		*/
	/************************/
	MemoryClear();

	/************************/
	/*	�I�u�W�F�N�g�̉��	*/
	/************************/
	DeleteDC(m_hdc);
	DeleteDC(m_Memoryhdc);
	DeleteObject(m_hBitmap);

	/************************/
	/*	�|�C���^�̏�����	*/
	/************************/
	m_hWnd		= NULL;
	m_hdc		= NULL;
	m_hFont		= NULL;
	m_Memoryhdc = NULL;
	m_hBitmap	= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MemoryClear			:	�������N���A							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		void				:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CGraphics::MemoryClear()
{
	m_GeometryDraw.clear();					/*	�`��p�̐}�`����������				*/
	m_TextRectDraw.clear();					/*	�`��p�̐}�`����������				*/
	m_TextOutDraw.clear();					/*	�`��p�̐}�`����������				*/
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		DrawMain			:	�`�揈��								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		void				:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CGraphics::DrawMain()
{
	PAINTSTRUCT		ps;												/*	�`����									*/
	RECT			rect;											/*	�E�B���h�E�T�C�Y�̎擾�p					*/

	GetClientRect(m_hWnd, &rect);									/*	�E�B���h�E�T�C�Y�̎擾						*/
	InvalidateRect(m_hWnd, &rect, NULL);

	m_hdc = BeginPaint(m_hWnd, &ps);								/*	�f�o�C�X�R���e�L�X�g�̃n���h�����擾		*/

	if (	(m_hdc != NULL)											/*	�f�o�C�X�R���e�L�X�g���擾�ł��Ă���Ȃ��	*/
		&&	(m_Memoryhdc != NULL))									/*	�E�B���h�E�n���h�����擾�ł��Ă���Ȃ��	*/
	{
		/************************/
		/*	�`�����ݒ�		*/
		/************************/
		DrawClear(m_Memoryhdc);

		/************************/
		/*	�`�����ݒ�		*/
		/************************/
		Draw();

		/****************/
		/*	�`�揈��	*/
		/****************/
		SetMapMode(m_Memoryhdc, MM_TEXT);							/*	�`�惂�[�h���s�N�Z���P�ʂ̐ݒ�				*/

		if (m_DrawFlag & BIT0)										/*	�����`�̕`��t���O��L���Ȃ��				*/
			DrawRectAngle(m_Memoryhdc);								/*	�����`�̕`��								*/

		if (m_DrawFlag & BIT1)										/*	�e�L�X�g(�����`)�̕`��t���O��L���Ȃ��	*/
			DrawTextRect(m_Memoryhdc);								/*	�e�L�X�g(�����`�w��)�̕`��					*/

		if (m_DrawFlag & BIT2)										/*	�e�L�X�g�̕`��t���O��L���Ȃ��			*/
			DrawTextOut(m_Memoryhdc);								/*	�e�L�X�g�̕`��								*/


		/****************************/
		/*	�r�b�g�}�b�v��]��		*/
		/****************************/								/*	�r�b�g�}�b�v��VRAM�ɓ]��					*/
		BitBlt(m_hdc												/*	�R�s�[��̃f�o�C�X�R���e�L�X�g�̃n���h��	*/
			, rect.left												/*	�R�s�[��̃E�B���h�E�̍���[ ( X���W )		*/
			, rect.top												/*	�R�s�[��̃E�B���h�E�̍���[ ( Y���W )		*/
			, rect.right											/*	�R�s�[��̃E�B���h�E�̉E���[ ( X���W )		*/
			, rect.bottom											/*	�R�s�[��̃E�B���h�E�̉E���[ ( Y���W )		*/
			, m_Memoryhdc											/*	�R�s�[���̃f�o�C�X�R���e�L�X�g�̃n���h��	*/
			, rect.left												/*	�R�s�[���̃E�B���h�E�̍���[ ( X���W )		*/
			, rect.top												/*	�R�s�[���̃E�B���h�E�̍���[ ( Y���W )		*/
			, SRCCOPY												/*	�R�s�[������R�s�[��֒����`���R�s�[		*/
			);
	}

	EndPaint(m_hWnd, &ps);											/*	�f�o�C�X�R���e�L�X�g�̃n���h����ԋp		*/
	m_DrawFlag			= 0;										/*	�s�N�Z�����Ƃ̕`��t���O�𖳌�				*/
	m_GeometryDraw.resize(0);										/*	�`��p�̐}�`����������					*/
	m_TextRectDraw.resize(0);										/*	�`��p�̃e�L�X�g(�����`)�̐ݒ����������	*/
	m_TextOutDraw.resize(0);										/*	�`��p�̃e�L�X�g�̐ݒ����������			*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Init				:	������									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CGraphics::Create()
{
	HDC		hdc		= NULL;
	RECT	rect;

	/****************************************/
	/*	�_�u���o�b�t�@�̃r�b�g�}�b�v���쐬	*/
	/****************************************/
	hdc = GetDC(m_hWnd);                      							/*	�f�o�C�X�R���e�L�X�g�̃n���h�����擾	*/
	GetClientRect(m_hWnd, &rect);  										/*	�E�B���h�E�T�C�Y���擾					*/
	m_hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);	/*	�E�B���h�E�T�C�Y�̃r�b�g�}�b�v���쐬	*/
	m_Memoryhdc = CreateCompatibleDC(hdc);								/*	�������f�o�C�X�R���e�L�X�g���쐬		*/
	SelectObject(m_Memoryhdc, m_hBitmap);								/*	�������f�o�C�X�R���e�L�X�g�ɕR�t��		*/

	/****************************/
	/*	�t�H���g�̏����擾	*/
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
/*	[�֐�]		SetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetWindowHandle(HWND hwnd)
{
	m_hWnd = hwnd;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetWindowHFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetWindowHFont(HFONT hFont)
{
	m_hFont = hFont;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetGradation	:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND			:												*/
/*	[����]		long			:												*/
/*				long			:												*/
/*				long			:												*/
/*				long			:												*/
/*				COLORREF		:												*/
/*				char			:	�O���f�[�V�������s���F						*/
/*										BIT0	->	�ԐF ( �P�x�������Ă��� )�@	*/													
/*										BIT1	->	�ԐF ( �P�x�������Ă��� )�@	*/
/*										BIT2	->	�F ( �P�x�������Ă��� )�@	*/	
/*										BIT3	->	�F ( �P�x�������Ă��� )�@	*/	
/*										BIT4	->	�ΐF ( �P�x�������Ă��� )�@	*/
/*										BIT5	->	�ΐF ( �P�x�������Ă��� )�@	*/
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

	width				= EndPosX - StartPosX;												/*	�`�悷��̈���擾							*/
	red_ratio_calc		= static_cast<float> (red) / static_cast<float> (width);			/*	�I��F�̗̈�ƕ`��̈�̔䗦���擾 ( �� )	*/
	green_ratio_calc	= static_cast<float> (green) / static_cast<float> (width);			/*	�I��F�̗̈�ƕ`��̈�̔䗦���擾 ( �� )	*/
	blue_ratio_calc		= static_cast<float> (blue) / static_cast<float> (width);			/*	�I��F�̗̈�ƕ`��̈�̔䗦���擾 ( �� )	*/

	for (int y = StartPosY; y <= EndPosY; y++)
	{
		for (int x = StartPosX; x <= EndPosX; x++)
		{		
			BYTE red_ratio		= 0;
			BYTE green_ratio	= 0;
			BYTE blue_ratio		= 0;

			/****************************/
			/*	�`��䗦�̌v�Z			*/
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
			/*	���݂̕`��F�̐ݒ�		*/
			/****************************/
			if ((red) && (red != red_ratio))
				red_ratio	= (red_ratio) % red;
			if ((green) && (green != green_ratio))
				green_ratio = (green_ratio) % green;
			if ((blue) && (blue != blue_ratio))
				blue_ratio	= (blue_ratio) % blue;

			/****************************/
			/*	�s�N�Z�����Ƃɕ`��		*/
			/****************************/
			color = RGB(red_ratio, green_ratio, blue_ratio);								/*	�s�N�Z���ʒu�ɐݒ肷��F���擾			*/
			SetPixel(m_Memoryhdc, x, y, color);												/*	�s�N�Z���ʒu�ɐF��ݒ�					*/
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
HWND CGraphics::GetWindowHandle() const
{
	return m_hWnd;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetInstanceHandle			:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HINSTANCE					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
HDC CGraphics::GetDeviceContext() const
{
	return m_hdc;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetRectAngle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
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
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag	|= BIT0;									/*	�`��t���O�̐ݒ�				*/

	/****************************/
	/*	�`�����ݒ�			*/
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
/*	[�֐�]		SetTextRect					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
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
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag |= BIT1;										/*	�`��t���O�̐ݒ�							*/

	/****************************/
	/*	�`�����ݒ�			*/
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
/*	[�֐�]		SetTextOut					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
/*				UINT						:									*/
/*				LPCTSTR						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetTextOut(UINT x_start, UINT y_start, std::string str, UINT textpitch, COLORREF color)
{
	/****************************/
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag |= BIT2;										/*	�`��t���O�̐ݒ�							*/

	/****************************/
	/*	�`�����ݒ�			*/
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
/*	[�֐�]		DrawRectAngle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
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
		/*	�����`�̕`��			*/
		/****************************/
		if (line_width == 0)
		{
			oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));					/*	�y���̐ݒ� ( �u���V�Ȃ� )		*/
		}
		else
		{
			hpen = CreatePen(style, line_width, pen_color);									/*	�y���̍쐬						*/
			oldhpen = (HPEN)SelectObject(hdc, hpen);										/*	�y���̐ݒ�						*/
		}

		hbrush = CreateSolidBrush(brush_color);												/*	�u���V�̍쐬					*/
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush);										/*	�u���V�̐ݒ� 					*/
		SetBkMode(hdc, OPAQUE);																/*	�w�i��h��Ԃ��ɐݒ�			*/
		Rectangle(hdc, left, top, right, bottom);											/*	�����`��ݒ�					*/

		/****************************/
		/*	�I�u�W�F�N�g�̏���		*/
		/****************************/
		SetBkMode(hdc, TRANSPARENT);														/*	�w�i�𓧖��ɐݒ肵�Ă���		*/
		SelectObject(hdc, oldhpen);															/*	�y���̐ݒ�����ɖ߂�			*/
		SelectObject(hdc, oldhbrush);														/*	�u���V�̐ݒ�����ɖ߂�			*/

		if (hpen != NULL)
			DeleteObject(hpen);																/*	�쐬�����y�����폜				*/

		if (hbrush != NULL)
			DeleteObject(hbrush);															/*	�쐬�����u���V���폜			*/

		if (oldhpen != NULL)
			DeleteObject(oldhpen);															/*	�쐬�����y�����폜				*/

		if (oldhbrush != NULL)
			DeleteObject(oldhbrush);														/*	�쐬�����u���V���폜			*/
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawTextRect				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
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
		/*	�����̕`��		*/
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
/*	[�֐�]		DrawTextOut					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
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
		/*	�����̕`��		*/
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
/*	[�֐�]		DrawClear					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawClear(HDC hdc)
{
	HPEN		hpen		= NULL;
	HPEN		oldhpen		= NULL;
	HBRUSH		oldhbrush	= NULL;
	RECT		rect;																	/*	�E�B���h�E�T�C�Y�̎擾�p		*/

	GetClientRect(m_hWnd, &rect);  														/*	�E�B���h�E�T�C�Y���擾			*/

	/****************************/
	/*	�w�i�̃N���A			*/
	/****************************/
	oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));						/*	�y���̐ݒ�						*/
	oldhbrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));					/*	�u���V�̐ݒ� ( �u���V�Ȃ� )		*/
	SetBkMode(hdc, OPAQUE);																/*	�w�i�͓h��Ԃ�				*/
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);						/*	�����`��ݒ�					*/

	/****************************/
	/*	�I�u�W�F�N�g�̏���		*/
	/****************************/
	SetBkMode(hdc, TRANSPARENT);														/*	�w�i�𓧖��ɐݒ肵�Ă���		*/
	SelectObject(hdc, oldhpen);															/*	�y���̐ݒ�����ɖ߂�			*/
	SelectObject(hdc, oldhbrush);														/*	�u���V�̐ݒ�����ɖ߂�			*/

	if (hpen != NULL)
		DeleteObject(hpen);																/*	�쐬�����y�����폜				*/

	if (oldhpen != NULL)
		DeleteObject(oldhpen);															/*	�쐬�����y�����폜				*/

	if (oldhbrush != NULL)
		DeleteObject(oldhbrush);														/*	�쐬�����u���V���폜			*/

	return;
}