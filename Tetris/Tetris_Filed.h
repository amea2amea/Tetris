#ifndef Tetris_Filed_h
#define Tetris_Filed_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Tetris_Block.h"
#include "Tetris_FallingBlock.h"
#include "Array2D.h"

/*--------------*/
/*	�\����		*/
/*--------------*/
struct Block_Point												/*	�{�[�g�ʒu�̍\����							*/
{
	/*----------------------*/
	/*	���W�ʒu			*/
	/*----------------------*/
	unsigned int x;												/*	���W�ʒu ( �� )								*/
	unsigned int y;												/*	���W�ʒu ( �c )								*/

	/*----------------------*/
	/*	�R���X�g���N�^		*/
	/*----------------------*/
	Block_Point()												/*	�����Ȃ��R���X�g���N�^						*/
	{
		Block_Point(0, 0);
	}

	Block_Point(int x, int y)									/*	��������R���X�g���N�^						*/
	{
		this->x = x;
		this->y = y;
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		���Z�q�I�[�o�[���[�h	*/
	/*------------------------------*/

	const Block_Point& operator()(int x, int y) const			/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Block_Point(x, y);
	}

	Block_Point& operator()(int x, int y)						/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Block_Point(x, y);
	}
};

/*--------------*/
/*	�N���X		*/
/*--------------*/

/************************/
/*	�{�[�h�̃N���X		*/
/************************/
class CTetris_Filed 
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CTetris_Filed();										/* �����Ȃ��R���X�g���N�^				*/

	/*	�f�X�g���N�^	*/
	~CTetris_Filed();

	/*	�֐�	*/
	void					Init();
	bool					isGameOver();
	void					CurrentBlockToBoard(char);
	void					SetCurrentBlockState();
	void					NextWaitBlockInit();
	void					NextCurrentBlock();
	void					NextWaitBlock();
	void					LandingBlockPos();
	void					LandingBlockClear();
	bool					CurrentMoveBlock(char);
	void					CheckBlockLine();
	unsigned char			GetBlockDeleteInfo() const;
	CTetris_Block			GetBlock(long, long) const;
	CTetris_Block&			SetBlock(long, long);
	unsigned short			GetBlockColor(long,long, char);		/* �u���b�N�ʒu�̃J���[���擾			*/
	unsigned short&			SetBlockColor(long, long, char);	/* �u���b�N�ʒu�̃J���[����ݒ�			*/
	unsigned short			GetBlockState(long, long, char);	/* �u���b�N�̏�Ԃ��擾					*/
	unsigned short&			SetBlockState(long, long, char);	/* �u���b�N�̏�Ԃ�ݒ�					*/
	unsigned short			GetBlockTopPosX(char) const;
	unsigned short			GetBlockTopPosY(char) const;
	unsigned short			GetFiledSizeX() const;
	unsigned short			GetFiledSizeY() const;

private:
	/*	�֐�	*/
	void			CreateCurrentBlock(char);
	void			FallingBlockToBoard(CTetris_Falling_Block&, char, unsigned short, unsigned short);
	void			MoveBlockUpdate(CTetris_Falling_Block&, char);
	bool			MoveBlock(CTetris_Falling_Block&, char);
	bool			MoveBlockLeft(CTetris_Falling_Block&, unsigned short, unsigned short);
	bool			MoveBlockRight(CTetris_Falling_Block&, unsigned short, unsigned short);
	bool			MoveBlockDown(CTetris_Falling_Block&, unsigned short, unsigned short);
	bool			RotateBlock(CTetris_Falling_Block&, char);
	void			MoveBlockFallMode(CTetris_Falling_Block&);

	/*------------------*/
	/*	�����o�ϐ�		*/
	/*------------------*/
public:
	/*	��`�p�ϐ� ( const )	*/
	static const short						TETRIS_FILED_SIZE_X = 10;											/*	�e�g���X�̂̉��T�C�Y							*/
	static const short						TETRIS_FILED_SIZE_Y = 20;											/*	�e�g���X�̏c�T�C�Y								*/
	static const short						TETRIS_FILED_SIZE = TETRIS_FILED_SIZE_X * TETRIS_FILED_SIZE_Y;		/*	�e�g���X�̃t�B�[���h�T�C�Y						*/
	static const short						TETRIS_FILED_START_X = 3;											/*	�e�g���X�̊J�n�ʒu (��)							*/
	static const short						TETRIS_FILED_START_Y = 4;											/*	�e�g���X�̊J�n�ʒu (�c)							*/
	static const short						COLOR_NUM = 3;														/*	�F�̎��										*/
	static const short						COLOR_START_POINT = -1;												/*	�F�̊J�n�f�[�^									*/
	static const short						CURRENT_BLOCK_X = 5;												/*	�����u���b�N�T�C�Y (��)							*/
	static const short						CURRENT_BLOCK_Y = 5;												/*	�����u���b�N�T�C�Y (�c)							*/
	static const short						CURRENT_BLOCK_START_X = 5;											/*	�����u���b�N�̊J�n�ʒu (��)						*/
	static const short						CURRENT_BLOCK_START_Y = 0;											/*	�����u���b�N�̊J�n�ʒu (�c)						*/

protected:
	Array2D< CTetris_Block >				m_Block;															/*	�u���b�N�̏��									*/
	CTetris_Falling_Block					m_CurrentBlock;														/*	�����u���b�N�̏�� ( �����u���b�N )				*/
	CTetris_Falling_Block					m_WaitBlock;														/*	�ҋ@�̃u���b�N�̏�� ( ���̗����u���b�N )		*/
	CTetris_Falling_Block					m_WaitNextBlock;													/*	�ҋ@�̎��̃u���b�N�̏�� ( ���̑ҋ@�u���b�N )	*/
	CTetris_Falling_Block					m_LandingBlock;														/*	�����u���b�N�̒��n�ʒu							*/
	unsigned short							m_CurrentBlockTopPosX;												/*	�����u���b�N�̃t�B�[���h�ʒu ( �� )				*/
	unsigned short							m_CurrentBlockTopPosY;												/*	�����u���b�N�̃t�B�[���h�ʒu ( �c )				*/
	unsigned short							m_LandingBlockTopPosX;												/*	�����u���b�N�̒��n�ʒu  ( �� )					*/
	unsigned short							m_LandingBlockTopPosY;												/*	�����u���b�N�̒��n�ʒu ( �c )					*/
	short									m_CurrentBlockRotatinAngle;											/*	�����u���b�N��]�p�x							*/
	
	unsigned char							m_BlockDeleteInfo;													/*	�u���b�N�̏������								*/	
																												/*	Bit0 : 1�i����									*/
																												/*	Bit1 : 2�i����									*/
																												/*	Bit2 : 3�i����									*/
																												/*	Bit3 : 4�i����									*/
																												/*	Bit4 : 1�i���� ( 2�� )						*/

};
#endif