/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "TetrisManger.h"
#include "Tetris_FallingBlock.h"

/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]	CTetris_Falling_Block	:	�����Ȃ��R���X�g���N�^			*/
/*																		*/
/*----------------------------------------------------------------------*/
CTetris_Falling_Block::CTetris_Falling_Block()
{
	m_FallingBlock.SetSize(5, 5);
	m_FallingBlockType		= BlockNS::FALLING_BLOCK_EMPTY;
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;
}

/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]	CTetris_Falling_Block	:	��������R���X�g���N�^			*/
/*																		*/
/*----------------------------------------------------------------------*/
CTetris_Falling_Block::CTetris_Falling_Block(unsigned short x, unsigned short y)
{
	m_FallingBlock.SetSize(x, y);
	m_FallinggBlockX		= x;
	m_FallinggBlockY		= y;
	m_FallingBlockType		= BlockNS::FALLING_BLOCK_EMPTY;
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0; 

}

/*--------------------------------------------------------------*/
/*																*/
/*	[�֐�]	~CTetris_Falling_Block	:	�f�X�g���N�^			*/
/*																*/
/*--------------------------------------------------------------*/
CTetris_Falling_Block::~CTetris_Falling_Block()
{
	Clear();													/*	���������			*/
	m_FallingBlockType		= BlockNS::FALLING_BLOCK_EMPTY;
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockState	:	�����u���b�N�̏��					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::Clear()
{
	m_FallingBlock.Clear();									/*	���������			*/
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		FallingBlockInit		:	�����u���b�N�̏�����				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::FallingBlockInit()
{
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	for (int y = 0; y < m_FallinggBlockY; y++)
	{
		for (int x = 0; x < m_FallinggBlockX; x++)
		{
			SetBlock(x, y) = tetris_block;
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetSize					:	�����u���b�N�̃T�C�Y				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]		unsigned long			:	�u���b�N�T�C�Y ( �� )				*/
/*										:	�u���b�N�T�C�Y ( �c )				*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::SetSize(unsigned short x, unsigned short y)
{
	m_FallingBlock.SetSize(x, y);
	m_FallinggBlockX = x;
	m_FallinggBlockY = y;
	
	return;
}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockState	:	�����u���b�N�̏��					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::SetFallingBlockState()
{
	int x_filed = 0;
	int y_filed = 0;

	/****************************/
	/*	�u���b�N�̏�Ԃ�������	*/
	/****************************/
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;

	/****************************/
	/*	�u���b�N�̈ʒu���擾	*/
	/****************************/
	for (y_filed = 0; y_filed < m_FallinggBlockY; y_filed++)
	{
		for (x_filed = 0; x_filed < m_FallinggBlockX; x_filed++)
		{
			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockLeft >(x_filed + 1) || (m_FallingBlockLeft == 0)))
			{
				/****************************/
				/*	�u���b�N�̍��[			*/
				/****************************/
				m_FallingBlockLeft = x_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockRight < (x_filed + 1)))
			{
				/****************************/
				/*	�u���b�N�̉E�[			*/
				/****************************/
				m_FallingBlockRight = x_filed + 1;
			}

			if ((m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&& (m_FallingBlockTop >(y_filed + 1) || (m_FallingBlockTop == 0)))
			{
				/****************************/
				/*	�u���b�N�̏�[			*/
				/****************************/
				m_FallingBlockTop = y_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockBottom < (y_filed + 1)))
			{
				/****************************/
				/*	�u���b�N�̉��[			*/
				/****************************/
				m_FallingBlockBottom = y_filed + 1;
			}
		}
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CreateFallingBlock		:	���݂̃u���b�N���쐬				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::CreateFallingBlock(char block_type)
{
	CTetris_Block	tetris_block(BlockNS::RED, BlockNS::EXISTENCE);

	switch (block_type)
	{
		/**************/
		/*	���������@*/
		/**************/
	case 0:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_ROD_TYPE;
		tetris_block.SetBlockColor() = BlockNS::RED;
		m_FallingBlock(1, 1) = tetris_block;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(3, 1) = tetris_block;
		m_FallingBlock(4, 1) = tetris_block;
		break;

		/************/
		/*	�������@*/
		/*	��	�@	*/
		/************/
	case 1:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_REVERSE_L_TYPE;
		tetris_block.SetBlockColor() = BlockNS::BLUE;
		m_FallingBlock(1, 1) = tetris_block;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(3, 1) = tetris_block;
		m_FallingBlock(1, 2) = tetris_block;
		break;

		/************/
		/*	�������@*/
		/*		��	*/
		/************/
	case 2:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_L_TYPE;
		tetris_block.SetBlockColor() = BlockNS::ORANGE;
		m_FallingBlock(1, 1) = tetris_block;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(3, 1) = tetris_block;
		m_FallingBlock(3, 2) = tetris_block;
		break;

		/************/
		/*	  �����@*/
		/*	�����@	*/
		/************/
	case 3:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_REVERSE_Z_TYPE;
		tetris_block.SetBlockColor() = BlockNS::PINK;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(3, 1) = tetris_block;
		m_FallingBlock(1, 2) = tetris_block;
		m_FallingBlock(2, 2) = tetris_block;
		break;

		/************/
		/*	����	*/
		/*	  �����@*/
		/************/
	case 4:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_Z_TYPE;
		tetris_block.SetBlockColor() = BlockNS::GREEN;
		m_FallingBlock(1, 1) = tetris_block;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(2, 2) = tetris_block;
		m_FallingBlock(3, 2) = tetris_block;
		break;

		/************/
		/*�@����	*/
		/*�@����	*/
		/************/
	case 5:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_SQUARE_TYPE;
		tetris_block.SetBlockColor() = BlockNS::YELLOW;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(3, 1) = tetris_block;
		m_FallingBlock(2, 2) = tetris_block;
		m_FallingBlock(3, 2) = tetris_block;
		break;

		/************/
		/*�@������	*/
		/*�@�@��	*/
		/************/
	case 6:
		m_FallingBlockType = BlockNS::FALLING_BLOCK_CONVEX_TYPE;
		tetris_block.SetBlockColor() = BlockNS::CYAN;
		m_FallingBlock(1, 1) = tetris_block;
		m_FallingBlock(2, 1) = tetris_block;
		m_FallingBlock(3, 1) = tetris_block;
		m_FallingBlock(2, 2) = tetris_block;
		break;
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockType		:	���݂̃u���b�N�̃^�C�v���擾		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockType() const
{
	return m_FallingBlockType;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetFallingBlockType		:	���݂̃u���b�N�̃^�C�v��ݒ�		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short& CTetris_Falling_Block::SetFallingBlockType()
{
	return m_FallingBlockType;
}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockLeft		:	���݂̃u���b�N�̍��[�ʒu���擾		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockLeft() const
{
	return m_FallingBlockLeft;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockTop		:	���݂̃u���b�N�̍ŏ�[�ʒu���擾	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockTop() const
{
	return m_FallingBlockTop;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockRight	:	���݂̃u���b�N�̉E�[�ʒu���擾		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockRight() const
{
	return m_FallingBlockRight;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockBottom	:	���݂̃u���b�N�̍ŉ��[�ʒu���擾	*/
/*				unsigned short			:										*/
/*	[����]																		*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]							:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockBottom() const
{
	return m_FallingBlockBottom;
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
unsigned short CTetris_Falling_Block::GetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockColor();
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
unsigned short& CTetris_Falling_Block::SetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockState			:	�u���b�N�����邩�ǂ������擾		*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Falling_Block::GetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlock				:	�u���b�N�̏�Ԃ�ݒ�				*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CTetris_Falling_Block::SetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockState			:	�u���b�N���擾						*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N���擾						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block CTetris_Falling_Block::GetBlock(long x, long y) const
{
	return m_FallingBlock(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlock				:	�u���b�N��ݒ�						*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N��ݒ�						*/
/*	[����]									�Ȃ�								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block& CTetris_Falling_Block::SetBlock(long x, long y)
{
	return m_FallingBlock(x, y);
}