#ifndef _WINDOW_CREATOR_H
#define _WINDOW_CREATOR_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"

/*--------------*/
/*	�񋓑�		*/
/*--------------*/

namespace WindowCreatorNS
{
	enum WINDOW_DEFAULT_SIZE						/*	�E�B���h�E�̃f�t�H���g��`									*/
	{
		DEFAULT_WINDOW_WIDTH		= 450,			/*	�E�B���h�E��												*/
		DEFAULT_WINDOW_HEIGHT		= 520,			/*	�E�B���h�E����												*/
		DEFAULT_SCREEN_MODE			= 0				/*	�E�B���h�E�̕\�����[�h ( 0:�E�B���h�E 1:�t���X�N���[�� )	*/
	};
}

/*----------------------------------*/
/*	�E�B���h�E�̑���N���X			*/
/*----------------------------------*/
class CWindowCreator
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CWindowCreator();
	CWindowCreator(LPTSTR, LPTSTR, bool, long, long);

	/*	�f�X�g���N�^	*/
	virtual	~CWindowCreator();

	/*	�֐�	*/
	bool		Create(HINSTANCE);
	ATOM		MyRegisterClass(HINSTANCE);
	bool		MyCreateWindow(HINSTANCE);
	void		MyCreateFont(LPCTSTR, int, int);
	HWND		GetWindowHandle() const;
	HFONT		GetWindowHFont() const;

private:
	/*	�֐�	*/
	void			SetInstanceHandle(HINSTANCE);
	void			SetWindowHandle(HWND);

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	��`�p�ϐ� ( const )	*/
	LPCTSTR							TETRIS_FONT					= NULL;
	static const short				TETRIS_FONT_HIGHT			= 40;
	static const short				TETRIS_FONT_STAET_ANGLE		= 0;

private:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	HFONT		m_hFont;
	LPTSTR		m_Clase_Name;								/*	�E�B���h�E�N���X��									*/
	LPTSTR		m_Title;									/*	�E�B���h�E��										*/
	bool		m_IsFullScreen;								/*	�X�N���[���̕\�����[�h�̐ݒ�						*/
	long		m_WindowWidth;								/*	�E�B���h�E��										*/
	long		m_WindowHeight;								/*	�E�B���h�E����										*/

};
#endif