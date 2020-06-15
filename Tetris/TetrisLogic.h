#ifndef _TETRIS_LOGIC_H
#define _TETRIS_LOGIC_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "GameLogic.h"
#include "Tetris_Filed.h"

/*----------------------------------*/
/*	�v���Z�X�̃R���g���[���N���X	*/
/*----------------------------------*/
class CTetrisLogic : public CGameLogic
{
	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CTetrisLogic();

	/*	�f�X�g���N�^	*/
	virtual	~CTetrisLogic();

	/*	�֐�	*/

protected:

	/*	���z�֐�	*/
	virtual void	Logic(CInput*);

private:
	void			Init();
	void			Update();
	void			UpdateBlock();
	void			UpdatePoint();
	bool			UpdateTimer();
	bool			Keydown(CInput*);

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	��`�p�ϐ� ( const )	*/
	static const short				TETRIS_FALL_TIME			= 300;		/*	�e�g���X�������Ԃ̍X�V����				*/
	static const short				TETRIS_NEXTBLOCK_WAIT_TIME	= 300;		/*	�e�g���X�������Ԃ̍X�V����				*/
	static const short				TETRIS_FALL_TIME_SPEED_UP	= 100;		/*	�e�g���X�������Ԃ̑��x�X�V				*/
	static const short				TETRIS_NEXTBLOCK_WAIT_SLOW	= 100;		/*	�e�g���X�������Ԃ̑��x�X�V				*/
	static const short				TETRIS_SINGLE_POINTS		= 40;		/*	�e�g���X���_ ( �V���O�� )				*/
	static const short				TETRIS_DOUBLE_POINTS		= 100;		/*	�e�g���X���_ ( �_�u�� )					*/
	static const short				TETRIS_TRIPLE_POINTS		= 300;		/*	�e�g���X���_ ( �g���v�� )				*/
	static const short				TETRIS_TETRIS_POINTS		= 1200;		/*	�e�g���X���_ ( �e�g���X )				*/
	static const short				TETRIS_KEYDOWN_POINTS		= 1;		/*	�e�g���X���_ ( �L�[�_�E�� )				*/

protected:
	CTetris_Filed&					m_Tetris_Filed;							/*	�e�g���X�̃u���b�N���					*/

private:
	DWORD 							m_TimeStart;							/*	�X�V�J�n����							*/
	DWORD		 					m_TimeEnd;								/*	�X�V�I������							*/
	bool							m_Init;									/*	�������t���O							*/
																			/*		true	: �������ς�				*/
																			/*		false	: ���������ĂȂ�			*/

	bool							m_Finish;								/*	�I���t���O								*/
																			/*		true	: �I���ς�					*/
																			/*		false	: �I�����ĂȂ�				*/

	bool							m_CurrentBlockFallTimeMode;				/*	�����������[�h							*/
	bool							m_CurrentBlockLandingMode;				/*	�����u���b�N�̒��n�ʒu�\�����[�h		*/

};
#endif
