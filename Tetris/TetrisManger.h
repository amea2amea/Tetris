#ifndef Tetris_Manger_h
#define Tetris_Manger_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "Tetris_Filed.h"
#include "Array2D.h"

/*--------------------------------------*/
/*	�}�l�W���[�N���X ( �V���O���g�� )	*/ 
/*--------------------------------------*/
class CTetrisManger
{

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	�R���X�g���N�^	*/
	CTetrisManger();
	CTetrisManger(const CTetrisManger&);
	
	/*	�R�s�[�R���X�g���N�^	*/
	void operator=(const CTetrisManger&) {};				/* �N���X�̑������( = ����)�͋֎~			*/

public:
	/*	�f�X�g���N�^	*/
	virtual	~CTetrisManger();
	
	/*	�֐�	*/
	CTetris_Filed&				GetTetrisFiled();
	static CTetrisManger*		Instance();
	DWORD						GetTetrisPoint() const;
	DWORD&						SetTetrisPoint();
	DWORD						GetTetrisFallingTime() const;
	DWORD&						SetTetrisFallingTime();
	DWORD						GetTetrisNextBlockWaitTime() const;
	DWORD&						SetTetrisNextBlockWaitTime();

	/*------------------*/
	/*	�����o�ϐ�		*/
	/*------------------*/
private:
	CTetris_Filed				m_Tetris_Filed;				/*	�e�g���X�̏��							*/
	DWORD		 				m_Tetris_Points;			/*	�_��									*/
	DWORD		 				m_FallingTime;				/*	��������								*/
	DWORD		 				m_NextBlockWaitTime;		/*	���̃u���b�N�̑҂�����					*/


};
#endif