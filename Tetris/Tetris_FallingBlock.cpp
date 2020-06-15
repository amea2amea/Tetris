/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "TetrisManger.h"
#include "Tetris_FallingBlock.h"

/*----------------------------------------------------------------------*/
/*																		*/
/*	[関数]	CTetris_Falling_Block	:	引数なしコンストラクタ			*/
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
/*	[関数]	CTetris_Falling_Block	:	引数ありコンストラクタ			*/
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
/*	[関数]	~CTetris_Falling_Block	:	デストラクタ			*/
/*																*/
/*--------------------------------------------------------------*/
CTetris_Falling_Block::~CTetris_Falling_Block()
{
	Clear();													/*	メモリ解放			*/
	m_FallingBlockType		= BlockNS::FALLING_BLOCK_EMPTY;
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockState	:	落下ブロックの状態					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::Clear()
{
	m_FallingBlock.Clear();									/*	メモリ解放			*/
}

/*==============================================================================*/
/*																				*/
/*	[関数]		FallingBlockInit		:	落下ブロックの初期化				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
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
/*	[関数]		SetSize					:	落下ブロックのサイズ				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		unsigned long			:	ブロックサイズ ( 横 )				*/
/*										:	ブロックサイズ ( 縦 )				*/
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
/*	[関数]		GetFallingBlockState	:	落下ブロックの状態					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::SetFallingBlockState()
{
	int x_filed = 0;
	int y_filed = 0;

	/****************************/
	/*	ブロックの状態を初期化	*/
	/****************************/
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;

	/****************************/
	/*	ブロックの位置を取得	*/
	/****************************/
	for (y_filed = 0; y_filed < m_FallinggBlockY; y_filed++)
	{
		for (x_filed = 0; x_filed < m_FallinggBlockX; x_filed++)
		{
			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockLeft >(x_filed + 1) || (m_FallingBlockLeft == 0)))
			{
				/****************************/
				/*	ブロックの左端			*/
				/****************************/
				m_FallingBlockLeft = x_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockRight < (x_filed + 1)))
			{
				/****************************/
				/*	ブロックの右端			*/
				/****************************/
				m_FallingBlockRight = x_filed + 1;
			}

			if ((m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&& (m_FallingBlockTop >(y_filed + 1) || (m_FallingBlockTop == 0)))
			{
				/****************************/
				/*	ブロックの上端			*/
				/****************************/
				m_FallingBlockTop = y_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockBottom < (y_filed + 1)))
			{
				/****************************/
				/*	ブロックの下端			*/
				/****************************/
				m_FallingBlockBottom = y_filed + 1;
			}
		}
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		CreateFallingBlock		:	現在のブロックを作成				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Falling_Block::CreateFallingBlock(char block_type)
{
	CTetris_Block	tetris_block(BlockNS::RED, BlockNS::EXISTENCE);

	switch (block_type)
	{
		/**************/
		/*	□□□□　*/
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
		/*	□□□　*/
		/*	□	　	*/
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
		/*	□□□　*/
		/*		□	*/
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
		/*	  □□　*/
		/*	□□　	*/
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
		/*	□□	*/
		/*	  □□　*/
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
		/*　□□	*/
		/*　□□	*/
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
		/*　□□□	*/
		/*　　□	*/
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
/*	[関数]		GetFallingBlockType		:	現在のブロックのタイプを取得		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockType() const
{
	return m_FallingBlockType;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetFallingBlockType		:	現在のブロックのタイプを設定		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short& CTetris_Falling_Block::SetFallingBlockType()
{
	return m_FallingBlockType;
}
/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockLeft		:	現在のブロックの左端位置を取得		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockLeft() const
{
	return m_FallingBlockLeft;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockTop		:	現在のブロックの最上端位置を取得	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockTop() const
{
	return m_FallingBlockTop;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockRight	:	現在のブロックの右端位置を取得		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockRight() const
{
	return m_FallingBlockRight;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockBottom	:	現在のブロックの最下端位置を取得	*/
/*				unsigned short			:										*/
/*	[引数]																		*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]							:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CTetris_Falling_Block::GetFallingBlockBottom() const
{
	return m_FallingBlockBottom;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockColor		:	ブロックの色を取得						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を取得						*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Falling_Block::GetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlockColor		:	ブロックの色を設定						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を設定						*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CTetris_Falling_Block::SetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockState			:	ブロックがあるかどうかを取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Falling_Block::GetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlock				:	ブロックの状態を設定				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CTetris_Falling_Block::SetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockState			:	ブロックを取得						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを取得						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block CTetris_Falling_Block::GetBlock(long x, long y) const
{
	return m_FallingBlock(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlock				:	ブロックを設定						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを設定						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block& CTetris_Falling_Block::SetBlock(long x, long y)
{
	return m_FallingBlock(x, y);
}