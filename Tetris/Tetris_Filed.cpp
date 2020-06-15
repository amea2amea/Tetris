/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "TetrisManger.h"
#include "Tetris_Filed.h"

/*--------------------------------------------------------------*/
/*																*/
/*	[�֐�]	CTetris_Filed	:	const�����Ȃ��R���X�g���N�^		*/
/*																*/
/*--------------------------------------------------------------*/
CTetris_Filed::CTetris_Filed()
{
	m_Block.SetSize(TETRIS_FILED_SIZE_X + TETRIS_FILED_START_X + 2, TETRIS_FILED_SIZE_Y + TETRIS_FILED_START_Y + 2);
	m_CurrentBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_WaitBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_WaitNextBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_LandingBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_CurrentBlockTopPosX		= 0;
	m_CurrentBlockTopPosY		= 0;
	m_LandingBlockTopPosX		= 0;
	m_LandingBlockTopPosY		= 0;
	m_CurrentBlockRotatinAngle	= 0;
	Init();
}

/*--------------------------------------------------------------*/
/*																*/
/*	[�֐�]	~CTetris_Filed	:	�f�X�g���N�^					*/
/*																*/
/*--------------------------------------------------------------*/
CTetris_Filed::~CTetris_Filed()
{
	m_Block.Clear();						/*				*/
	m_CurrentBlock.Clear();					/*				*/
	m_WaitBlock.Clear();					/*				*/
	m_WaitNextBlock.Clear();				/*				*/
	m_LandingBlock.Clear();					/*				*/
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Init				:	������									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetris_Filed::Init()
{
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);
	CTetris_Block	tetris_wall(BlockNS::GRAY, BlockNS::WALL);

	/********************************/
	/*	�t�B�[���h�ʒu�̏�����		*/
	/********************************/
	for (int x = TETRIS_FILED_START_X; x < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
	{
		for (int y = TETRIS_FILED_START_Y; y < TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y++)
		{
			m_Block(x, y) = tetris_block;																/*	�t�B�[���h�ʒu�̏���������					*/
		}
	}

	/************************/
	/*	�ǂ̐ݒ�			*/
	/************************/
	for (int x = TETRIS_FILED_START_X - 1; x <= TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
	{
		m_Block(x, TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y) = tetris_wall;							/*	�ǂ̐ݒ� ( 1�ԉ� )								*/
	}

	for (int y = TETRIS_FILED_START_Y; y <= TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y++)
	{
		m_Block(TETRIS_FILED_START_X - 1, y) = tetris_wall;												/*	�ǂ̐ݒ� ( ���[ )								*/
		m_Block(TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X, y) = tetris_wall;							/*	�ǂ̐ݒ� ( �E�[ )								*/
	}

	/************************/
	/*	�����̏�����		*/
	/************************/
	srand((unsigned int)time(NULL));

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		isGameOver			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Q�[���I��( 0:���Ȃ�	1:���� )		*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CTetris_Filed::isGameOver()
{
	bool			GameOver		= false;
	char			block_count		= 0;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/********************************/
	/*	1��u���b�N�̑��ݔ���		*/
	/********************************/
	for (int x_filed = TETRIS_FILED_START_X; x_filed < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x_filed++)
	{
		if (m_Block(x_filed, TETRIS_FILED_START_Y - 1).GetBlockState() == BlockNS::EXISTENCE)						/*	�t�B�[���h�O�Ƀu���b�N������Ȃ��				*/
		{
			GameOver = true;
			break;
		}
	}

	/********************************/
	/*	�Q�[���I�[�o�[����			*/
	/********************************/
	if (GameOver)																									/*	�Q�[���I�[�o�[�Ȃ��							*/
	{
		/********************************/
		/*	�u���b�N���O���C�F�ɐݒ�	*/
		/********************************/
		for (int x = TETRIS_FILED_START_X; x < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
		{
			for (int y = 0; y < TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y++)
			{
				if (m_Block(x, y).GetBlockState() == BlockNS::EXISTENCE)
				{
					m_Block(x, y).SetBlockColor() = BlockNS::DIMGRAY;												/*	�t�B�[���h�ʒu�̏���������					*/
				}
			}
		}
	}

	return GameOver;
}

/*======================================================================================*/
/*																						*/
/*	[�֐�]		FallingBlockToBoard		:	�����u���b�N���t�B�[���h�ɃR�s�[			*/
/*																						*/
/*	------------------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�										*/
/*	[����]		CTetris_Falling_Block&	:	�����u���b�N�̃N���X						*/
/*				char					:	�t�B�[���h��ւ̃R�s�[���[�h				*/
/*												0	-> �����@ 							*/
/*												1	-> ���݂̃u���b�N���R�s�[			*/
/*												2	-> ���̃u���b�N���J�n�ʒu�ɃR�s�[	*/
/*				unsigned short			:	�����u���b�N�̊J�n�ʒu ( �����W )			*/
/*				unsigned short			:	�����u���b�N�̊J�n�ʒu ( �c���W )			*/
/*																						*/
/*======================================================================================*/
void CTetris_Filed::FallingBlockToBoard(CTetris_Falling_Block& Tetris_Falling_Block, char mode, unsigned short x_filed, unsigned short y_filed)
{
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/************************************/
	/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
	/************************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		int startblockY = 0;

		if (y_filed + y < CURRENT_BLOCK_START_Y)
			break;

		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (x_filed + x > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X)
				break;

			if (Tetris_Falling_Block.GetBlockState(x, y) == BlockNS::EXISTENCE)
			{
				if (mode == 1)
				{
					m_Block(x_filed + x, y_filed + y) = tetris_block;
				}
				else if (mode == 2)
				{
					m_Block(x_filed + x, y_filed + startblockY) = tetris_block;
					startblockY++;
				}
				else
				{
 					m_Block(x_filed + x, y_filed + y) = Tetris_Falling_Block.GetBlock(x, y);
				}
			}
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		NextWaitBlockInit		:	���̃u���b�N�̏���������			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::NextWaitBlockInit()
{
	char			block_type = 0;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/****************************/
	/*	�u���b�N����������	*/
	/****************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_WaitBlock.SetBlock(x, y)		= tetris_block;
			m_WaitNextBlock.SetBlock(x, y)	= tetris_block;
		}
	}

	/************************************/
	/*	�u���b�N�̎�ނ𗐐��Őݒ�		*/
	/************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * 7);

	/****************************/
	/*	�ҋ@�u���b�N���쐬		*/
	/****************************/
	CreateCurrentBlock(block_type);

	/****************************/
	/*	�u���b�N����������	*/
	/****************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_WaitBlock.SetBlock(x, y)		= m_WaitNextBlock.SetBlock(x, y);
			m_WaitNextBlock.SetBlock(x, y)	= tetris_block;
		}
	}

	m_WaitBlock.SetFallingBlockType() = m_WaitNextBlock.GetFallingBlockType();

	/************************************/
	/*	�u���b�N�̎�ނ𗐐��Őݒ�		*/
	/************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * 7);

	/****************************/
	/*	���̑ҋ@�u���b�N���쐬	*/
	/****************************/
	CreateCurrentBlock(block_type);

	/****************************/
	/*	���̃u���b�N���쐬		*/
	/****************************/
	NextCurrentBlock();

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		NextWaitBlock			:	���̃u���b�N���쐬 ( �ҋ@�p )		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::NextWaitBlock()
{
	char			block_type = 0;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/****************************/
	/*	�u���b�N����������	*/
	/****************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_WaitBlock.SetBlock(x, y)		= m_WaitNextBlock.SetBlock(x, y);
			m_WaitNextBlock.SetBlock(x, y)	= tetris_block;
			m_LandingBlock.SetBlock(x, y)	= tetris_block;
		}
	}

	m_WaitBlock.SetFallingBlockType() = m_WaitNextBlock.GetFallingBlockType();

	/************************************/
	/*	�u���b�N�̎�ނ𗐐��Őݒ�		*/
	/************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * 7);

	/****************************/
	/*	�u���b�N���쐬			*/
	/****************************/
	CreateCurrentBlock(block_type);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		NextCurrentBlock		:	���̃u���b�N���쐬					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]		void					:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::NextCurrentBlock()
{
	/********************************/
	/*	���݂̃u���b�N���̐ݒ�	*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_CurrentBlock.SetBlock(x, y) = m_WaitBlock.SetBlock(x, y);
			m_LandingBlock.SetBlock(x, y) = m_WaitBlock.SetBlock(x, y);
		}
	}

	m_CurrentBlock.SetFallingBlockType() = m_WaitBlock.GetFallingBlockType();
	m_LandingBlock.SetFallingBlockType() = m_WaitBlock.GetFallingBlockType();

	/****************************/
	/*	�u���b�N�̊J�n�ʒu		*/
	/****************************/
	m_CurrentBlockTopPosX = CURRENT_BLOCK_START_X;
	
	if (m_CurrentBlock.GetFallingBlockType() == BlockNS::FALLING_BLOCK_ROD_TYPE)
	{
		m_CurrentBlockTopPosY = CURRENT_BLOCK_START_Y + 1;
	}
	else
	{
		m_CurrentBlockTopPosY = CURRENT_BLOCK_START_Y;
	}

	/********************************/
	/*	�u���b�N�̉�]�p�x���N���A	*/
	/********************************/
	m_CurrentBlockRotatinAngle = 0;

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CreateCurrentBlock		:	���݂̃u���b�N���쐬				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::CreateCurrentBlock(char block_type)
{
	/****************************/
	/*	�u���b�N�̍쐬			*/
	/****************************/
	m_WaitNextBlock.CreateFallingBlock(block_type);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MoveBlock				:	�u���b�N�̈ړ�����					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool					:	true	->	�ړ��\				*/
/*											false	->	�ړ��s��				*/
/*	[����]		CTetris_Falling_Block&	:	�����u���b�N�̃N���X				*/
/*				char					:	�u���b�N�̏������@					*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlock(CTetris_Falling_Block& Tetris_Falling_Block, char next_block_direction)
{
	bool			block_move	= false;
	unsigned short	x_filed		= m_CurrentBlockTopPosX;
	unsigned short	y_filed		= m_CurrentBlockTopPosY;

	switch (next_block_direction)
	{
		/************************************/
		/*	�u���b�N�̈ړ�������������		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_LEFT:
		block_move = MoveBlockLeft(Tetris_Falling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	�u���b�N�̈ړ��������E����		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_RIGHT:
		block_move = MoveBlockRight(Tetris_Falling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	�u���b�N�̈ړ�������������		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_DOWN:
		block_move = MoveBlockDown(Tetris_Falling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	�u���b�N�̈ړ�������CCW��]		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_ROTATE_CW:
 		block_move = RotateBlock(Tetris_Falling_Block, BlockNS::BLOCK_CCW_ROTATION);
		break;

		/************************************/
		/*	�u���b�N�̈ړ�������CW��]		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_ROTATE_CCW:
		block_move = RotateBlock(Tetris_Falling_Block, BlockNS::BLOCK_CW_ROTATION);
		break;

		/************************************/
		/*	�u���b�N�̗������[�h			*/
		/************************************/
	case BlockNS::BLOCK_MOVE_FALL_MODE:
		MoveBlockFallMode(Tetris_Falling_Block);
		break;

	}

	/************************************/
	/*	�u���b�N�ړ��̍X�V����			*/
	/************************************/
	if (block_move)
	{
		MoveBlockUpdate(Tetris_Falling_Block, next_block_direction);
	}

	return block_move;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MoveBlockUpdate			:	�u���b�N�ړ��̍X�V����				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]		CTetris_Falling_Block&	:	�����u���b�N�̃N���X				*/
/*				char					:	�u���b�N�̏������@					*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::MoveBlockUpdate(CTetris_Falling_Block& Tetris_Falling_Block, char next_block_direction)
{

	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	/************************************/
	/*	�t�B�[���h��̃u���b�N���N���A	*/
	/************************************/
	FallingBlockToBoard(Tetris_Falling_Block, 1, x_filed, y_filed);

	/************************************/
	/*	�t�B�[���h��̃u���b�N��i�߂�	*/
	/************************************/
	switch (next_block_direction)
	{
		/************************************/
		/*	�u���b�N�̈ړ�������������		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_LEFT:
		m_CurrentBlockTopPosX--;
		break;

		/************************************/
		/*	�u���b�N�̈ړ��������E����		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_RIGHT:
		m_CurrentBlockTopPosX++;
		break;

		/************************************/
		/*	�u���b�N�̈ړ�������������		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_DOWN:
		m_CurrentBlockTopPosY++;
		break;
	
	default:
		break;

	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CurrentMoveBlock		:	���݂̃u���b�N�̈ړ�����			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool					:	true	->	�ړ��\				*/
/*											false	->	�ړ��s��				*/
/*	[����]		char					:	�u���b�N�������@					*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::CurrentMoveBlock(char next_block_direction)
{
	bool block_move = false;
	block_move		= MoveBlock(m_CurrentBlock, next_block_direction);
	return block_move;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MoveBlockLeft			:	�u���b�N�̈ړ����� ( �� )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool					:	true	->	�ړ��\				*/
/*											false	->	�ړ��s��				*/
/*	[����]		CTetris_Falling_Block&	:	�����u���b�N�̃N���X				*/
/*				unsigned short			:	�����u���b�N�̈ʒu ( �����W )		*/
/*				unsigned short			:	�����u���b�N�̈ʒu ( �c���W )		*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlockLeft(CTetris_Falling_Block& Tetris_Falling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
		�u���b�N���������Ɉړ��ł��邩����
			�t�B�[���h��ɂ��錻�݂̃u���b�N�̈��1���ɂ����ău���b�N��
			���݂��Ȃ��Ȃ�΁A�E�ɐi�߂�
	*/

	char			left_block	= 0;
	unsigned short	block_top	= Tetris_Falling_Block.GetFallingBlockTop() - 1;
	unsigned short	block_left	= Tetris_Falling_Block.GetFallingBlockLeft() - 1;

	if ((x_filed + block_left) > TETRIS_FILED_START_X)
	{
		/************************************/
		/*	�u���b�N�����[�ɐi�߂�ꍇ		*/
		/************************************/
		for (int y = block_top; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = TETRIS_FILED_START_X - 1; x >= 0; x--)
			{
				if (	(Tetris_Falling_Block.GetBlockState(x, y))						/*	���݂̃u���b�N���Ƀu���b�N������				*/
					&&	(m_Block(x_filed + x - 1, y_filed + y).GetBlockState()))		/*	�t�B�[���h��̈���ɂ��u���b�N������Ȃ��	*/
				{
					if (x == 0)															/*	��ԍ��̃u���b�N���ł���Ȃ��				*/
					{
						left_block++;													/*	���Ƀu���b�N�����݂���							*/
					}
					else if (!Tetris_Falling_Block.GetBlockState(x - 1, y))				/*	���݂̃u���b�N���̍��Ƀu���b�N���Ȃ��Ȃ��	*/
					{
						left_block++;													/*	���Ƀu���b�N�����݂���							*/
					}
				}
			}

			if (y_filed + y > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	�u���b�N�̈ړ�����		*/
		/****************************/
		if (	(!left_block)															/*	���Ƀu���b�N�����݂��Ȃ��Ȃ��					*/
			&&	(m_CurrentBlockTopPosX > 0))
		{
			return true;
		}
	}

	return false;
}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		MoveBlockRight			:	�u���b�N�̈ړ����� ( �E )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool					:	true	->	�ړ��\				*/
/*											false	->	�ړ��s��				*/
/*	[����]		CTetris_Falling_Block&	:	�����u���b�N�̃N���X				*/
/*				unsigned short			:	�����u���b�N�̈ʒu ( �����W )		*/
/*				unsigned short			:	�����u���b�N�̈ʒu ( �c���W )		*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlockRight(CTetris_Falling_Block& Tetris_Falling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
			�u���b�N���E�����Ɉړ��ł��邩����
				�t�B�[���h��ɂ��錻�݂̃u���b�N�̈��1�E�ɂ����ău���b�N��
				���݂��Ȃ��Ȃ�΁A�E�ɐi�߂�
	*/

	char			right_block = 0;
	unsigned short	block_top	= Tetris_Falling_Block.GetFallingBlockTop() - 1;
	unsigned short	block_right	= Tetris_Falling_Block.GetFallingBlockRight() - 1;

	if ((m_CurrentBlockTopPosX < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X))
	{
		/************************************/
		/*	�u���b�N���E�[�ɐi�߂�ꍇ		*/
		/************************************/
		for (int y = block_top; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = 0; x < CURRENT_BLOCK_X; x++)
			{
				if (x_filed + x > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X)
					break;

				if (	(Tetris_Falling_Block.GetBlockState(x, y))						/*	���݂̃u���b�N���Ƀu���b�N������				*/
					&&	(m_Block(x_filed + x + 1, y_filed + y).GetBlockState()))		/*	�t�B�[���h��̈�E�ɂ��u���b�N������Ȃ��	*/
				{	
					if (x == CURRENT_BLOCK_X - 1)										/*	��ԉE�̃u���b�N���ł���Ȃ��				*/
					{
						right_block++;													/*	�E�Ƀu���b�N�����݂���							*/
					}
					else if (!Tetris_Falling_Block.GetBlockState(x + 1, y))				/*	���݂̃u���b�N���̉E�Ƀu���b�N���Ȃ��Ȃ��	*/
					{
						right_block++;													/*	�E�Ƀu���b�N�����݂���							*/
					}
				}
			}

			if (y_filed + y > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	�u���b�N�̈ړ�����		*/
		/****************************/
		if (!right_block)																/*	�E�Ƀu���b�N�����݂��Ȃ��Ȃ��					*/
		{
			return true;
		}
	}

	return false;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MoveBlockDown			:	�u���b�N�̈ړ����� ( �� )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool					:	true	->	�ړ��\				*/
/*											false	->	�ړ��s��				*/
/*	[����]		CTetris_Falling_Block&	:	�����u���b�N�̃N���X				*/
/*				unsigned short			:	�����u���b�N�̈ʒu ( �����W )		*/
/*				unsigned short			:	�����u���b�N�̈ʒu ( �c���W )		*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlockDown(CTetris_Falling_Block& Tetris_Falling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
			�u���b�N�̍ŉ��[�̔���	
				���݂̃u���b�N�̈�̐擪����u���b�N�̍ŉ��[�ʒu�����Z�����l��
				�t�B�[���h��菬�����Ȃ�΁A���ɐi�߂�

		Note 2:
			�u���b�N���������Ɉړ��ł��邩����
				�t�B�[���h��ɂ��錻�݂̃u���b�N�̈��1���ɂ����ău���b�N��
				���݂��Ȃ��Ȃ�΁A���ɐi�߂�
	*/

	char			below_block		= 0;
	unsigned short	block_bottom	= Tetris_Falling_Block.GetFallingBlockBottom() - 1;
	unsigned short	block_left		= Tetris_Falling_Block.GetFallingBlockLeft() - 1;

	if((y_filed + block_bottom + 1) < TETRIS_FILED_SIZE_Y + TETRIS_FILED_START_Y)		/*	���݂̃u���b�N���̈�O�łȂ��Ȃ��				*/
	{
		/************************************/
		/*	�u���b�N�����[�ɐi�߂�ꍇ		*/
		/************************************/
		for (int y = 0; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = block_left; x < CURRENT_BLOCK_X; x++)
			{
				if (x_filed + x > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X)
					break;

				if (	(Tetris_Falling_Block.GetBlockState(x, y))						/*	���݂̃u���b�N���Ƀu���b�N������				*/
					&&	(m_Block(x_filed + x, y_filed + y + 1).GetBlockState()))		/*	�t�B�[���h��̈���ɂ��u���b�N������Ȃ��	*/
				{
					if(y == CURRENT_BLOCK_Y - 1)										/*	��ԉ��̃u���b�N���ł���Ȃ��				*/
					{
						below_block++;													/*	���Ƀu���b�N�����݂���							*/
					}
					else if (!Tetris_Falling_Block.GetBlockState(x, y + 1))				/*	���݂̃u���b�N���̉��Ƀu���b�N���Ȃ��Ȃ��	*/
					{
						below_block++;													/*	���Ƀu���b�N�����݂���							*/
					}
				}
			}

			if (y_filed + y > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	�u���b�N�̈ړ�����		*/
		/****************************/
		if (!below_block)																/*	���Ƀu���b�N�����݂��Ȃ��Ȃ��					*/
		{
			return true;																/*	�ړ��\										*/
		}

	}

	return false;																		/*	�ړ��s��										*/
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		RotateBlock				:	�u���b�N�̉�]����					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	long					:	�Ȃ�								*/
/*	[����]								:	�����u���b�N���					*/
/*										:	��]���� ( 0:CW 1:CCW )				*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::RotateBlock(CTetris_Falling_Block& Tetris_Falling_Block, char type)
{
	unsigned short				x_filed = m_CurrentBlockTopPosX;
	unsigned short				y_filed = m_CurrentBlockTopPosY;
	short						shift_x = 0;
	short						shift_y = 0;
	Array2D< CTetris_Block >	tetris_block(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);

	/************************/
	/*	��]���Ȃ��u���b�N	*/
	/************************/
	if (	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_EMPTY)
		|| 	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_SQUARE_TYPE))
	{
		return false;
	}

	/************************************/
	/*	-90�x����������]���Ȃ��u���b�N	*/
	/************************************/
	if (	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_Z_TYPE)
		|| 	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_REVERSE_Z_TYPE)
		|| 	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_ROD_TYPE))
	{
		if (m_CurrentBlockRotatinAngle != 0)
		{
			type = BlockNS::BLOCK_CW_ROTATION;
		}
		else if (type == BlockNS::BLOCK_CW_ROTATION)
		{
			type = BlockNS::BLOCK_CCW_ROTATION;
		}
	}

	/********************************/
	/*	���݂̃u���b�N������]	*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (type == BlockNS::BLOCK_CW_ROTATION)
			{
				tetris_block((CURRENT_BLOCK_Y - 1) - y, x) = Tetris_Falling_Block.GetBlock(x, y);
			}
			else if (type == BlockNS::BLOCK_CCW_ROTATION)
			{
				tetris_block(y, (CURRENT_BLOCK_X - 1) - x) = Tetris_Falling_Block.GetBlock(x, y);
			}
		}
	}

	/********************************/
	/*	��]�\������				*/
	/*		�t�B�[���h���̔���		*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (tetris_block(x, y).GetBlockState() == BlockNS::EXISTENCE)
			{
				unsigned int x_rotate = x + x_filed;
				unsigned int y_rotate = y + y_filed;

				if (x_rotate < TETRIS_FILED_START_X)											/*	���[�̃t�B�[���h�𒴂���Ȃ��	*/
				{
					shift_x = TETRIS_FILED_START_X - x_rotate;
				}
				else if (x_rotate > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X - 1)				/*	�E�[�̃t�B�[���h�𒴂���Ȃ��	*/
				{
					shift_x = (TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X - 1) - x_rotate;
				}
				else if (y_rotate > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y - 1)				/*	���[�̃t�B�[���h�𒴂���Ȃ��	*/
				{
					shift_y = (TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y - 1) - y_rotate;
				}
			}
		}
	}

	/************************************/
	/*	�t�B�[���h��̃u���b�N���V�t�g	*/
	/************************************/
	if ((shift_x != 0) || (shift_y != 0))		/*	���̂܂܉�]�ł��Ȃ��Ȃ��		*/
	{	
		m_CurrentBlockTopPosX += shift_x;
		m_CurrentBlockTopPosY += shift_y;
	}

	/************************************/
	/*	�t�B�[���h��̃u���b�N���N���A	*/
	/************************************/
	FallingBlockToBoard(Tetris_Falling_Block, 1, x_filed, y_filed);

	/****************************************/
	/*	��]�\������						*/
	/*		�t�B�[���h��̃u���b�N�̔���	*/
	/****************************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if(		(tetris_block(x, y).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_Block(x_filed + x, y_filed + y).GetBlockState() == BlockNS::EXISTENCE))
			{
				FallingBlockToBoard(Tetris_Falling_Block, 0, x_filed, y_filed);
   				return false;
			}
		}
	}

	/********************************/
	/*	��]�����u���b�N���R�s�[	*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			Tetris_Falling_Block.SetBlock(x, y) = tetris_block(x, y);
		}
	}

	if (type == BlockNS::BLOCK_CW_ROTATION)
	{
		m_CurrentBlockRotatinAngle += -90;
	}
	else if (type == BlockNS::BLOCK_CCW_ROTATION)
	{
		m_CurrentBlockRotatinAngle += 90;
	}

	return true;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MoveBlockFallMode		:	�u���b�N�̗������[�h				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	long					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::MoveBlockFallMode(CTetris_Falling_Block& Tetris_Falling_Block)
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	while (MoveBlockDown(Tetris_Falling_Block, x_filed, y_filed))
	{
		/********************************/
		/*	���݃u���b�N�̈ʒu���X�V	*/
		/********************************/
		MoveBlockUpdate(Tetris_Falling_Block, BlockNS::BLOCK_MOVE_DOWN);
		x_filed = m_CurrentBlockTopPosX;
		y_filed = m_CurrentBlockTopPosY;

		/****************************/
		/*	�u���b�N��Ԃ�ݒ�		*/
		/****************************/
		SetCurrentBlockState();

		/************************************/
		/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
		/************************************/
		FallingBlockToBoard(Tetris_Falling_Block, 0, x_filed, y_filed);

	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		LandingBlockPos			:	�����u���b�N�̒��n�ʒu				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	long					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::LandingBlockPos()
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	/********************************/
	/*	���n�u���b�N�̐F�̐ݒ�		*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_LandingBlock.SetBlock(x, y) = m_CurrentBlock.SetBlock(x, y);
			m_LandingBlock.SetBlockColor(x, y) = BlockNS::LIGHTGRAY;
		}
	}

	m_LandingBlock.SetFallingBlockType() = m_CurrentBlock.GetFallingBlockType();

	/********************************/
	/*	���n�u���b�N��Ԃ�ݒ�		*/
	/********************************/
	m_LandingBlock.SetFallingBlockState();

	/************************/
	/*	�����n�_�܂ŏ���	*/
	/************************/
	while (MoveBlockDown(m_LandingBlock, x_filed, y_filed))
	{
		/********************************/
		/*	���݃u���b�N�̈ʒu���X�V	*/
		/********************************/
		y_filed++;
	}

	/************************************/
	/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
	/************************************/
	m_LandingBlockTopPosX = x_filed;
	m_LandingBlockTopPosY = y_filed;
	
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		LandingBlockClear		:	�����u���b�N�̒��n�ʒu�̃N���A		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	long					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::LandingBlockClear()
{
	m_LandingBlock.FallingBlockInit();
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CheckBlockLine			:	�s���u���b�N�Ŗ��܂��Ă��钲�ׂ�	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	long					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::CheckBlockLine()
{
	bool			no_line_block = false;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);
	char			continuity_flag = 0;

	/********************************/
	/*	�����u���b�N�̏����N���A	*/
	/********************************/
	m_BlockDeleteInfo = 0;

	/********************************/
	/*	�t�B�[���h�ʒu�̏��		*/
	/********************************/
	for (int y_filed = TETRIS_FILED_START_Y; y_filed < TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y_filed++)
	{	
		no_line_block = false;

		/********************************/
		/*	1�s�u���b�N�̑��ݔ���		*/
		/********************************/
		for (int x_filed = TETRIS_FILED_START_X; x_filed < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x_filed++)
		{
			if ((m_Block(x_filed, y_filed).GetBlockState() != BlockNS::EXISTENCE))									/*	1�s�Ƀu���b�N���Ȃ��Ƃ��낪����Ȃ��	*/
			{
				no_line_block = true;
				break;
			}
		}

		/********************************/
		/*	�����u���b�N�̃J�E���g		*/
		/********************************/
		if (no_line_block)
		{
			continue;
		}
		else if (y_filed == continuity_flag + 1)
		{
			continuity_flag = y_filed;
			m_BlockDeleteInfo = m_BlockDeleteInfo << BIT0;
		}
		else if (continuity_flag)
		{
			m_BlockDeleteInfo += BIT4;
		}
		else
		{
			continuity_flag = y_filed;
		 	m_BlockDeleteInfo = BIT0;
		}

		/********************************/
		/*	1�s�̃u���b�N���X�V			*/
		/********************************/
		for (int y = y_filed; y >= TETRIS_FILED_START_Y; y--)
		{
			for (int x = TETRIS_FILED_START_X; x < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
			{
				if (y == y_filed)
				{
					m_Block(x, y) = tetris_block;
				}

				if (y != TETRIS_FILED_START_Y)
				{
					m_Block(x, y) = m_Block(x, y - 1);																/*	1�s��̃u���b�N�����ɗ��Ƃ�				*/
				}
			}
		}

	}

	return;
}

/*======================================================================================*/
/*																						*/
/*	[�֐�]		CurrentBlockToBoard		:	���݂̃u���b�N���t�B�[���h�ɃR�s�[			*/
/*																						*/
/*	------------------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�										*/
/*				char					:	�t�B�[���h��ւ̃R�s�[���[�h				*/
/*												0	-> �����@ 							*/
/*												1	-> ���݂̃u���b�N���R�s�[			*/
/*												2	-> ���̃u���b�N���J�n�ʒu�ɃR�s�[	*/
/*																						*/
/*======================================================================================*/
void CTetris_Filed::CurrentBlockToBoard(char mode)
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;
	FallingBlockToBoard(m_CurrentBlock, mode, x_filed, y_filed);
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetCurrentBlockState	:	���݃u���b�N�̈ʒu����ݒ�		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void  CTetris_Filed::SetCurrentBlockState()
{
	m_CurrentBlock.SetFallingBlockState();
	return;
}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetBlockDeleteInfo		:	�u���b�N�������					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned char			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned char CTetris_Filed::GetBlockDeleteInfo() const
{
	return m_BlockDeleteInfo;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockColor		:	�u���b�N�̐F���擾						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�u���b�N�̐F���擾						*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetBlockColor(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).GetBlockColor();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.GetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.GetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.GetBlockColor(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.GetBlockColor(x, y);
	}
	else
	{
		return m_Block(x, y).GetBlockColor();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlockColor		:	�u���b�N�̐F��ݒ�						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�u���b�N�̐F��ݒ�						*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CTetris_Filed::SetBlockColor(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).SetBlockColor();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.SetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.SetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.SetBlockColor(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.SetBlockColor(x, y);
	}
	else
	{
		return m_Block(x, y).SetBlockColor();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockState			:	�u���b�N�����邩�ǂ������擾		*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetBlockState(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).GetBlockState();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.GetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.GetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.GetBlockState(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.GetBlockState(x, y);
	}
	else
	{
		return 0;
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlock				:	�u���b�N�̏�Ԃ�ݒ�				*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CTetris_Filed::SetBlockState(long x, long y, char type)
{

	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).SetBlockState();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.SetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.SetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.SetBlockState(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.SetBlockState(x, y);;
	}
	else
	{
		return m_Block(x, y).SetBlockState();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockState			:	�u���b�N���擾						*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N���擾						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block CTetris_Filed::GetBlock(long x, long y) const
{
	return m_Block(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlock				:	�u���b�N��ݒ�						*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N��ݒ�						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block& CTetris_Filed::SetBlock(long x, long y)
{
	return m_Block(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockTopPosX(		:	�����u���b�N�̈ʒu�����擾		*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetBlockTopPosX(char type) const
{
	if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlockTopPosX;
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlockTopPosX;
	}
	else
	{
		return 0;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockTopPosY			:	�����u���b�N�̈ʒu�����擾		*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetBlockTopPosY(char type) const
{
	if(type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlockTopPosY;
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlockTopPosY;
	}
	else
	{
		return 0;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetFiledSizeX			:	�t�B�[���h�T�C�Y���擾				*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetFiledSizeX() const
{
	return TETRIS_FILED_SIZE_X;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetFiledSizeY			:	�t�B�[���h�T�C�Y���擾				*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetFiledSizeY() const
{
	return TETRIS_FILED_SIZE_Y;
}