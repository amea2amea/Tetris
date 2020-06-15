#ifndef _FRAME_WORK_H
#define _FRAME_WORK_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Graphics.h"
#include "GameLogic.h"

/*----------------------------------*/
/*	�v���Z�X�̊j�ƂȂ�N���X		*/
/*----------------------------------*/
class CFameWork
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CFameWork();
	CFameWork(HINSTANCE, LPTSTR);

	/*	�f�X�g���N�^	*/
	virtual	~CFameWork();
	
	/*	�֐�	*/
	bool		Run();
	HINSTANCE	GetInstanceHandle() const;
	HWND		GetWindowHandle() const;
	void		SetGraphicClass(CGraphics*);
	void		SetGameLogicClass(CGameLogic*);

protected:
	/*	�����z�֐�	*/
	virtual void	MessageLoop() = 0;

	/*	���z�֐�	*/
	virtual bool	Initialize();

	/*	�֐�	*/
	void			SetWindowHandle(HWND);

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	LPTSTR		m_CommandLine;

protected:
	CGraphics*		m_pGraphics;
	CGameLogic*		m_pGameLogic;

};
#endif
