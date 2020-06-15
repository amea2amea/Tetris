#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H 

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Global.h"
#include "Input.h"

/*------------------*/
/*	�`��N���X		*/
/*------------------*/
class CGameLogic
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CGameLogic();

	/*	�f�X�g���N�^	*/
	virtual	~CGameLogic();

	/*	�����z�֐�	*/
	virtual void	Logic(CInput*) = 0;


};
#endif
