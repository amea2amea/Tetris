#ifndef Tetris_Falling_Block_h
#define Tetris_Falling_Block_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Tetris_Block.h"
#include "Array2D.h"

/*--------------*/
/*	�N���X		*/
/*--------------*/

/****************************/
/*	�����u���b�N�̃N���X	*/
/****************************/
class CTetris_Falling_Block
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CTetris_Falling_Block();											/* �����Ȃ��R���X�g���N�^				*/			
	CTetris_Falling_Block(unsigned short, unsigned short);				/* ��������R���X�g���N�^				*/

	/*	�f�X�g���N�^	*/
	~CTetris_Falling_Block();

	/*	�֐�	*/
	void						SetFallingBlockState();					/* �����u���b�N�̈ʒu����ݒ�			*/
	void						CreateFallingBlock(char);				/* �����u���b�N���쐬					*/
	void						Clear();								/* �����u���b�N�̃��������				*/
	void						FallingBlockInit();						/* �����u���b�N�̏�����					*/
	void						SetSize(unsigned short, unsigned short);/* �����u���b�N�̃T�C�Y��ݒ�			*/
	unsigned short				GetFallingBlockLeft() const;			/* �����u���b�N�̍��[					*/
	unsigned short				GetFallingBlockTop() const;				/* �����u���b�N�̏�[					*/
	unsigned short				GetFallingBlockRight() const;			/* �����u���b�N�̉E�[					*/
	unsigned short				GetFallingBlockBottom() const;			/* �����u���b�N�̉��[					*/
	CTetris_Block				GetBlock(long, long) const;				/* �����u���b�N���擾					*/		
	CTetris_Block&				SetBlock(long, long);					/* �����u���b�N��ݒ�					*/
	unsigned short				GetBlockColor(long, long);				/* �����u���b�N�ʒu�̃J���[���擾		*/
	unsigned short&				SetBlockColor(long, long);				/* �����u���b�N�ʒu�̃J���[����ݒ�		*/
	unsigned short				GetBlockState(long, long);				/* �����u���b�N�̏�Ԃ��擾				*/
	unsigned short&				SetBlockState(long, long);				/* �����u���b�N�̏�Ԃ�ݒ�				*/
	unsigned short				GetFallingBlockType() const;			/* �����u���b�N�̃^�C�v���擾			*/
	unsigned short&				SetFallingBlockType();					/* �����u���b�N�̃^�C�v��ݒ�			*/


	/*------------------*/
	/*	�����o�ϐ�		*/
	/*------------------*/
private:
	Array2D< CTetris_Block >	m_FallingBlock;							/*	�����u���b�N�̏��					*/
	unsigned short				m_FallingBlockTop;						/*	�����u���b�N�̏�[�ʒu				*/	
	unsigned short				m_FallingBlockLeft;						/*	�����u���b�N�̍��[�ʒu				*/
	unsigned short				m_FallingBlockBottom;					/*	�����u���b�N�̉��[�ʒu				*/
	unsigned short				m_FallingBlockRight;					/*	�����u���b�N�̉E�[�ʒu				*/
	unsigned short				m_FallingBlockType;						/*	�����u���b�N�̃u���b�N�^�C�v		*/
	unsigned short				m_FallinggBlockX;						/*	�����u���b�N�T�C�Y (��)				*/
	unsigned short				m_FallinggBlockY;						/*	�����u���b�N�T�C�Y (�c)				*/

};
#endif
