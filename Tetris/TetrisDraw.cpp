/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "TetrisManger.h"
#include "TetrisDraw.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CTetrisDraw			:	�R���X�g���N�^ ( �����Ȃ� )				*/
/*																				*/
/*==============================================================================*/
CTetrisDraw::CTetrisDraw() :m_Tetris_Filed(CTetrisManger::Instance()->GetTetrisFiled())
{
	m_BlockRect.SetSize(m_Tetris_Filed.TETRIS_FILED_SIZE_X + m_Tetris_Filed.TETRIS_FILED_START_X + 2, m_Tetris_Filed.TETRIS_FILED_SIZE_Y + m_Tetris_Filed.TETRIS_FILED_START_Y + 2);
	m_WaitBlockRect.SetSize(m_Tetris_Filed.CURRENT_BLOCK_X, m_Tetris_Filed.CURRENT_BLOCK_Y);
	m_WaitNextBlockRect.SetSize(m_Tetris_Filed.CURRENT_BLOCK_X, m_Tetris_Filed.CURRENT_BLOCK_Y);
	m_LandingBlockRect.SetSize(m_Tetris_Filed.CURRENT_BLOCK_X, m_Tetris_Filed.CURRENT_BLOCK_Y);
	InitBlockRect();
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CTetrisDraw		:	�f�X�g���N�^							*/
/*																				*/
/*==============================================================================*/
CTetrisDraw::~CTetrisDraw()
{
	m_BlockRect.Clear();
	m_WaitBlockRect.Clear();
	m_WaitNextBlockRect.Clear();
	m_LandingBlockRect.Clear();
}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		Draw				:	�`��									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetrisDraw::Draw()
{	
	/****************************/
	/*	�e�L�X�g�̕`��			*/
	/****************************/
	SetTetrisText();

	/****************************/
	/*	�`��̐ݒ�				*/
	/****************************/
	SetTetrisColor();

	return;

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetTetrisText		:	�e�g���X�̃e�L�X�g�ݒ�					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetrisDraw::SetTetrisText()
{
	unsigned long	x_start					= (m_Tetris_Filed.TETRIS_FILED_SIZE_X + m_Tetris_Filed.TETRIS_FILED_START_X + 2) * TETRIS_BLOCK_PIXEL_SIZE_X;
	unsigned long	y_start					= 2;
	unsigned long	color					= RGB(255, 255, 255);
	unsigned long	points					= CTetrisManger::Instance()->GetTetrisPoint();
	unsigned long	falling_time			= CTetrisManger::Instance()->GetTetrisFallingTime();
	int const		arraysize				= 8;
	char			tetris_disp[arraysize] = {};
	size_t			cbDest					= arraysize * sizeof(char);
	std::string		str_score("[ SCORE ] ");
	std::string		str_falling_time("[ Falling Time ] ");
	std::string		str_next_block("[ Next Block1 ] ");
	std::string		str_next_wait_block("[ Next Block2 ] ");

	/********************/
	/*	�^�C�g���\��	*/
	/********************/
	SetTextOut(x_start, TetrisDrawNS::SCORE_TITLE, str_score, 0, color);
	SetTextOut(x_start, TetrisDrawNS::FALL_TIME_TITLE, str_falling_time, 0, color);
	SetTextOut(x_start, TetrisDrawNS::NEXT_BLOCK_TITLE, str_next_block, 0, color);
	SetTextOut(x_start, TetrisDrawNS::NEXT_WAIT_BLOCK_TITLE, str_next_wait_block, 0, color);

	/****************/
	/*	���_�\��	*/
	/****************/
	sprintf_s(tetris_disp, cbDest, "%lu", points);
	SetTextOut(x_start, TetrisDrawNS::SCORE, tetris_disp, 0, color);

	/********************/
	/*	�������ԕ\��	*/
	/********************/
	sprintf_s(tetris_disp, cbDest, "%lu ms",falling_time);
	SetTextOut(x_start, TetrisDrawNS::FALL_TIME, tetris_disp, 0, color);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetTetrisColor		:	�e�g���X�̕`��ݒ�						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetrisDraw::SetTetrisColor()
{
	unsigned long	line_color	= RGB(255, 255, 255);

	/************************************/
	/*	�`��̐ݒ� ( ���n�ʒu�u���b�N )	*/
	/************************************/
	for (int y_filed = 0; y_filed < m_Tetris_Filed.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_Tetris_Filed.CURRENT_BLOCK_X; x_filed++)
		{
			if (m_Tetris_Filed.GetBlockState(x_filed, y_filed, BlockNS::LANDING_BLOCK) != BlockNS::EMPTY)
			{

				m_LandingBlockRect(x_filed, y_filed).left	= (x_filed + m_Tetris_Filed.GetBlockTopPosX(BlockNS::LANDING_BLOCK)) * TETRIS_BLOCK_PIXEL_SIZE_X;
				m_LandingBlockRect(x_filed, y_filed).right	= m_LandingBlockRect(x_filed, y_filed).left + TETRIS_BLOCK_PIXEL_SIZE_X;
				m_LandingBlockRect(x_filed, y_filed).top	= (y_filed + m_Tetris_Filed.GetBlockTopPosY(BlockNS::LANDING_BLOCK)) * TETRIS_BLOCK_PIXEL_SIZE_Y;
				m_LandingBlockRect(x_filed, y_filed).bottom = m_LandingBlockRect(x_filed, y_filed).top + TETRIS_BLOCK_PIXEL_SIZE_Y;

				SetRectAngle(	m_LandingBlockRect(x_filed, y_filed).left + TETRIS_BLOCK_MARGIN_LEFT
							,	m_LandingBlockRect(x_filed, y_filed).top + TETRIS_BLOCK_MARGIN_TOP
							,	m_LandingBlockRect(x_filed, y_filed).right - TETRIS_BLOCK_MARGIN_RIGHT
							,	m_LandingBlockRect(x_filed, y_filed).bottom - TETRIS_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::LANDING_BLOCK)
					);
			}
		}
	}

	/********************************/
	/*	�`��̐ݒ� ( �t�B�[���h )	*/
	/********************************/
	for (int y_filed = 0; y_filed < (m_Tetris_Filed.TETRIS_FILED_SIZE_Y + m_Tetris_Filed.TETRIS_FILED_START_Y + 2); y_filed++)
	{
		for (int x_filed = 0; x_filed < (m_Tetris_Filed.TETRIS_FILED_SIZE_X + m_Tetris_Filed.TETRIS_FILED_START_X + 2); x_filed++)
		{
			if(m_Tetris_Filed.GetBlockState(x_filed, y_filed, BlockNS::FILED_BLOCK) != BlockNS::EMPTY)
			{ 
				SetRectAngle(	m_BlockRect(x_filed, y_filed).left + TETRIS_BLOCK_MARGIN_LEFT
							,	m_BlockRect(x_filed, y_filed).top + TETRIS_BLOCK_MARGIN_TOP
							,	m_BlockRect(x_filed, y_filed).right	- TETRIS_BLOCK_MARGIN_RIGHT
							,	m_BlockRect(x_filed, y_filed).bottom - TETRIS_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::FILED_BLOCK)
						);
			}
		}
	}

	/************************************/
	/*	�`��̐ݒ� ( �ҋ@�u���b�N )		*/
	/************************************/
	for (int y_filed = 0; y_filed < m_Tetris_Filed.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_Tetris_Filed.CURRENT_BLOCK_X; x_filed++)
		{
			if (m_Tetris_Filed.GetBlockState(x_filed, y_filed, BlockNS::WAIT_BLOCK) != BlockNS::EMPTY)
			{
				SetRectAngle(	m_WaitBlockRect(x_filed, y_filed).left + TETRIS_BLOCK_MARGIN_LEFT
							,	m_WaitBlockRect(x_filed, y_filed).top + TETRIS_BLOCK_MARGIN_TOP
							,	m_WaitBlockRect(x_filed, y_filed).right - TETRIS_BLOCK_MARGIN_RIGHT
							,	m_WaitBlockRect(x_filed, y_filed).bottom - TETRIS_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::WAIT_BLOCK)
					);
			}
		}
	}

	/****************************************/
	/*	�`��̐ݒ� ( ���̑ҋ@�u���b�N )	*/
	/****************************************/
	for (int y_filed = 0; y_filed < m_Tetris_Filed.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_Tetris_Filed.CURRENT_BLOCK_X; x_filed++)
		{
			if (m_Tetris_Filed.GetBlockState(x_filed, y_filed, BlockNS::WAIT_NEXT_BLOCK) != BlockNS::EMPTY)
			{
				SetRectAngle(	m_WaitNextBlockRect(x_filed, y_filed).left + TETRIS_BLOCK_MARGIN_LEFT
							,	m_WaitNextBlockRect(x_filed, y_filed).top + TETRIS_BLOCK_MARGIN_TOP
							,	m_WaitNextBlockRect(x_filed, y_filed).right - TETRIS_BLOCK_MARGIN_RIGHT
							,	m_WaitNextBlockRect(x_filed, y_filed).bottom - TETRIS_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::WAIT_NEXT_BLOCK)
					);
			}
		}
	}

	return;

}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetColor			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�u���b�N�̐F���擾						*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
COLORREF CTetrisDraw::GetColor(long x, long y, char type)
{
	unsigned long block_color		= 0;
	unsigned long color				= 0;

	/****************************/
	/*	�e��u���b�N�̐F���擾	*/
	/****************************/
	block_color = m_Tetris_Filed.GetBlockColor(x, y, type);

	switch (block_color)
	{
		case BlockNS::BLACK:					/*	��							*/
			color = RGB(0, 0, 0);
			break;

		case BlockNS::WHITE:					/*	��							*/
			color = RGB(255, 255, 255);
			break;

		case BlockNS::LIGHTGRAY:				/*	���C�g�O���C ( �W���O���C )	*/
			color = RGB(200, 200, 200);
			break;

		case BlockNS::DIMGRAY:					/*	�f�B���O���C ( �Â��O���C )	*/
			color = RGB(105, 105, 105);
			break;

		case BlockNS::GRAY:						/*	�O���C						*/
			color = RGB(128, 128, 128);
			break;

		case BlockNS::RED:						/*	��							*/
			color = RGB(255, 0, 0);
			break;

		case BlockNS::YELLOW:					/*	��							*/
			color = RGB(255, 255, 0);
			break;

		case BlockNS::PINK:						/*	�s���N						*/
			color = RGB(255, 20, 147);
			break;
			
		case BlockNS::GREEN:					/*	��							*/
			color = RGB(0, 255, 0);
			break;

		case BlockNS::BLUE:						/*	��							*/
			color = RGB(0, 0, 255);
			break;

		case BlockNS::CYAN:						/*	�V�A��						*/
			color = RGB(0, 255, 255);
			break;

		case BlockNS::ORANGE:					/*	�I�����W					*/
			color = RGB(255, 165, 0);
			break;

		default:
			break;
	}

	return color;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		InitBlockRect		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		void				:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetrisDraw::InitBlockRect()
{
	unsigned long	x_start = (m_Tetris_Filed.TETRIS_FILED_SIZE_X + m_Tetris_Filed.TETRIS_FILED_START_X + 2) * TETRIS_BLOCK_PIXEL_SIZE_X;
	unsigned long	y_start = TetrisDrawNS::NEXT_BLOCK;

	for (int y_filed = 0; y_filed < m_Tetris_Filed.TETRIS_FILED_SIZE_Y + m_Tetris_Filed.TETRIS_FILED_START_Y + 2; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_Tetris_Filed.TETRIS_FILED_SIZE_X + m_Tetris_Filed.TETRIS_FILED_START_X + 2; x_filed++)
		{
			m_BlockRect(x_filed, y_filed).left		= x_filed * TETRIS_BLOCK_PIXEL_SIZE_X;
			m_BlockRect(x_filed, y_filed).right		= m_BlockRect(x_filed, y_filed).left + TETRIS_BLOCK_PIXEL_SIZE_X;
			m_BlockRect(x_filed, y_filed).top		= y_filed * TETRIS_BLOCK_PIXEL_SIZE_Y;
			m_BlockRect(x_filed, y_filed).bottom	= m_BlockRect(x_filed, y_filed).top + TETRIS_BLOCK_PIXEL_SIZE_Y;
		}
	}

	for (int y_filed = 0; y_filed < m_Tetris_Filed.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_Tetris_Filed.CURRENT_BLOCK_X; x_filed++)
		{
			m_WaitBlockRect(x_filed, y_filed).left		= x_filed * TETRIS_BLOCK_PIXEL_SIZE_X + x_start;
			m_WaitBlockRect(x_filed, y_filed).right		= m_WaitBlockRect(x_filed, y_filed).left + TETRIS_BLOCK_PIXEL_SIZE_X;
			m_WaitBlockRect(x_filed, y_filed).top		= ( y_filed + TetrisDrawNS::NEXT_BLOCK) * TETRIS_BLOCK_PIXEL_SIZE_Y;
			m_WaitBlockRect(x_filed, y_filed).bottom	= m_WaitBlockRect(x_filed, y_filed).top + TETRIS_BLOCK_PIXEL_SIZE_Y;
		}
	}
	
	for (int y_filed = 0; y_filed < m_Tetris_Filed.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_Tetris_Filed.CURRENT_BLOCK_X; x_filed++)
		{
			m_WaitNextBlockRect(x_filed, y_filed).left		= x_filed * TETRIS_BLOCK_PIXEL_SIZE_X + x_start;
			m_WaitNextBlockRect(x_filed, y_filed).right		= m_WaitNextBlockRect(x_filed, y_filed).left + TETRIS_BLOCK_PIXEL_SIZE_X;
			m_WaitNextBlockRect(x_filed, y_filed).top		= (y_filed + TetrisDrawNS::NEXT_WAIT_BLOCK) * TETRIS_BLOCK_PIXEL_SIZE_Y;
			m_WaitNextBlockRect(x_filed, y_filed).bottom	= m_WaitNextBlockRect(x_filed, y_filed).top + TETRIS_BLOCK_PIXEL_SIZE_Y;
		}
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetRectAngle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	Block_Rect			:											*/
/*	[����]		long 				:											*/
/*				long 				:											*/
/*																				*/
/*------------------------------------------------------------------------------*/
Block_Rect CTetrisDraw::GetBlockRect(long x_index, long y_index)
{
	Block_Rect block_rect;

	block_rect.left		= m_BlockRect(x_index, y_index).left;
	block_rect.right	= m_BlockRect(x_index, y_index).right;
	block_rect.top		= m_BlockRect(x_index, y_index).top;
	block_rect.bottom	= m_BlockRect(x_index, y_index).bottom;
	
	return block_rect;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetRectAngle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		long 				:											*/
/*				long 				:											*/
/*				Block_Rect			:											*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetrisDraw::SetBlockRect(long x_index, long y_index, Block_Rect block_rect)
{
	m_BlockRect(x_index, y_index).left		= block_rect.left;
	m_BlockRect(x_index, y_index).right		= block_rect.right;
	m_BlockRect(x_index, y_index).top		= block_rect.top;
	m_BlockRect(x_index, y_index).bottom	= block_rect.bottom;

	return;
}