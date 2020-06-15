#ifndef _FRAME_WORK_H
#define _FRAME_WORK_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Graphics.h"
#include "GameLogic.h"

/*----------------------------------*/
/*	プロセスの核となるクラス		*/
/*----------------------------------*/
class CFameWork
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CFameWork();
	CFameWork(HINSTANCE, LPTSTR);

	/*	デストラクタ	*/
	virtual	~CFameWork();
	
	/*	関数	*/
	bool		Run();
	HINSTANCE	GetInstanceHandle() const;
	HWND		GetWindowHandle() const;
	void		SetGraphicClass(CGraphics*);
	void		SetGameLogicClass(CGameLogic*);

protected:
	/*	純仮想関数	*/
	virtual void	MessageLoop() = 0;

	/*	仮想関数	*/
	virtual bool	Initialize();

	/*	関数	*/
	void			SetWindowHandle(HWND);

	/*--------------*/
	/*	メンバ変数	*/
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
