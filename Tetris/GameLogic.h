#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H 

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Global.h"
#include "Input.h"

/*------------------*/
/*	描画クラス		*/
/*------------------*/
class CGameLogic
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CGameLogic();

	/*	デストラクタ	*/
	virtual	~CGameLogic();

	/*	純仮想関数	*/
	virtual void	Logic(CInput*) = 0;


};
#endif
