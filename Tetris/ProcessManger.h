#ifndef _PROCESS_MANGER_H
#define _PROCESS_MANGER_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"

/*------------------*/
/* 前方宣言			*/
/*------------------*/
class CFameWork;

/*----------------------------------*/
/*	プロセスを管理するクラス		*/
/*----------------------------------*/
class CProcessManger
{
	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CProcessManger();

	/*	デストラクタ	*/
	virtual	~CProcessManger();
	
	/*	関数	*/
	CFameWork*	Create(HINSTANCE, LPTSTR);

private:
	/*	関数	*/
	bool	IsAnotherInstance();

};
#endif
