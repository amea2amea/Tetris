#ifndef _PROCESS_MANGER_H
#define _PROCESS_MANGER_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"

/*------------------*/
/* �O���錾			*/
/*------------------*/
class CFameWork;

/*----------------------------------*/
/*	�v���Z�X���Ǘ�����N���X		*/
/*----------------------------------*/
class CProcessManger
{
	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CProcessManger();

	/*	�f�X�g���N�^	*/
	virtual	~CProcessManger();
	
	/*	�֐�	*/
	CFameWork*	Create(HINSTANCE, LPTSTR);

private:
	/*	�֐�	*/
	bool	IsAnotherInstance();

};
#endif
