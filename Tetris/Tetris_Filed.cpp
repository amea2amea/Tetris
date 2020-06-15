/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "TetrisManger.h"
#include "Tetris_Filed.h"

/*--------------------------------------------------------------*/
/*																*/
/*	[関数]	CTetris_Filed	:	const引数なしコンストラクタ		*/
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
/*	[関数]	~CTetris_Filed	:	デストラクタ					*/
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
/*	[関数]		Init				:	初期化									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CTetris_Filed::Init()
{
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);
	CTetris_Block	tetris_wall(BlockNS::GRAY, BlockNS::WALL);

	/********************************/
	/*	フィールド位置の初期化		*/
	/********************************/
	for (int x = TETRIS_FILED_START_X; x < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
	{
		for (int y = TETRIS_FILED_START_Y; y < TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y++)
		{
			m_Block(x, y) = tetris_block;																/*	フィールド位置の情報を初期化					*/
		}
	}

	/************************/
	/*	壁の設定			*/
	/************************/
	for (int x = TETRIS_FILED_START_X - 1; x <= TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
	{
		m_Block(x, TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y) = tetris_wall;							/*	壁の設定 ( 1番下 )								*/
	}

	for (int y = TETRIS_FILED_START_Y; y <= TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y++)
	{
		m_Block(TETRIS_FILED_START_X - 1, y) = tetris_wall;												/*	壁の設定 ( 左端 )								*/
		m_Block(TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X, y) = tetris_wall;							/*	壁の設定 ( 右端 )								*/
	}

	/************************/
	/*	乱数の初期化		*/
	/************************/
	srand((unsigned int)time(NULL));

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		isGameOver			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	ゲーム終了( 0:しない	1:する )		*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CTetris_Filed::isGameOver()
{
	bool			GameOver		= false;
	char			block_count		= 0;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/********************************/
	/*	1列ブロックの存在判定		*/
	/********************************/
	for (int x_filed = TETRIS_FILED_START_X; x_filed < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x_filed++)
	{
		if (m_Block(x_filed, TETRIS_FILED_START_Y - 1).GetBlockState() == BlockNS::EXISTENCE)						/*	フィールド外にブロックがあるならば				*/
		{
			GameOver = true;
			break;
		}
	}

	/********************************/
	/*	ゲームオーバー処理			*/
	/********************************/
	if (GameOver)																									/*	ゲームオーバーならば							*/
	{
		/********************************/
		/*	ブロックをグレイ色に設定	*/
		/********************************/
		for (int x = TETRIS_FILED_START_X; x < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x++)
		{
			for (int y = 0; y < TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y++)
			{
				if (m_Block(x, y).GetBlockState() == BlockNS::EXISTENCE)
				{
					m_Block(x, y).SetBlockColor() = BlockNS::DIMGRAY;												/*	フィールド位置の情報を初期化					*/
				}
			}
		}
	}

	return GameOver;
}

/*======================================================================================*/
/*																						*/
/*	[関数]		FallingBlockToBoard		:	落下ブロックをフィールドにコピー			*/
/*																						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし										*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス						*/
/*				char					:	フィールド上へのコピーモード				*/
/*												0	-> 消去　 							*/
/*												1	-> 現在のブロックをコピー			*/
/*												2	-> 次のブロックを開始位置にコピー	*/
/*				unsigned short			:	落下ブロックの開始位置 ( 横座標 )			*/
/*				unsigned short			:	落下ブロックの開始位置 ( 縦座標 )			*/
/*																						*/
/*======================================================================================*/
void CTetris_Filed::FallingBlockToBoard(CTetris_Falling_Block& Tetris_Falling_Block, char mode, unsigned short x_filed, unsigned short y_filed)
{
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/************************************/
	/*	ブロックをフィールドにコピー	*/
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
/*	[関数]		NextWaitBlockInit		:	次のブロックの初期化処理			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::NextWaitBlockInit()
{
	char			block_type = 0;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/****************************/
	/*	ブロック情報を初期化	*/
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
	/*	ブロックの種類を乱数で設定		*/
	/************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * 7);

	/****************************/
	/*	待機ブロックを作成		*/
	/****************************/
	CreateCurrentBlock(block_type);

	/****************************/
	/*	ブロック情報を初期化	*/
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
	/*	ブロックの種類を乱数で設定		*/
	/************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * 7);

	/****************************/
	/*	次の待機ブロックを作成	*/
	/****************************/
	CreateCurrentBlock(block_type);

	/****************************/
	/*	次のブロックを作成		*/
	/****************************/
	NextCurrentBlock();

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		NextWaitBlock			:	次のブロックを作成 ( 待機用 )		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::NextWaitBlock()
{
	char			block_type = 0;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);

	/****************************/
	/*	ブロック情報を初期化	*/
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
	/*	ブロックの種類を乱数で設定		*/
	/************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * 7);

	/****************************/
	/*	ブロックを作成			*/
	/****************************/
	CreateCurrentBlock(block_type);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		NextCurrentBlock		:	次のブロックを作成					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::NextCurrentBlock()
{
	/********************************/
	/*	現在のブロック情報の設定	*/
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
	/*	ブロックの開始位置		*/
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
	/*	ブロックの回転角度をクリア	*/
	/********************************/
	m_CurrentBlockRotatinAngle = 0;

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CreateCurrentBlock		:	現在のブロックを作成				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::CreateCurrentBlock(char block_type)
{
	/****************************/
	/*	ブロックの作成			*/
	/****************************/
	m_WaitNextBlock.CreateFallingBlock(block_type);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlock				:	ブロックの移動処理					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				char					:	ブロックの処理方法					*/
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
		/*	ブロックの移動方向が左方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_LEFT:
		block_move = MoveBlockLeft(Tetris_Falling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	ブロックの移動方向が右方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_RIGHT:
		block_move = MoveBlockRight(Tetris_Falling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	ブロックの移動方向が下方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_DOWN:
		block_move = MoveBlockDown(Tetris_Falling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	ブロックの移動方向がCCW回転		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_ROTATE_CW:
 		block_move = RotateBlock(Tetris_Falling_Block, BlockNS::BLOCK_CCW_ROTATION);
		break;

		/************************************/
		/*	ブロックの移動方向がCW回転		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_ROTATE_CCW:
		block_move = RotateBlock(Tetris_Falling_Block, BlockNS::BLOCK_CW_ROTATION);
		break;

		/************************************/
		/*	ブロックの落下モード			*/
		/************************************/
	case BlockNS::BLOCK_MOVE_FALL_MODE:
		MoveBlockFallMode(Tetris_Falling_Block);
		break;

	}

	/************************************/
	/*	ブロック移動の更新処理			*/
	/************************************/
	if (block_move)
	{
		MoveBlockUpdate(Tetris_Falling_Block, next_block_direction);
	}

	return block_move;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockUpdate			:	ブロック移動の更新処理				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				char					:	ブロックの処理方法					*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::MoveBlockUpdate(CTetris_Falling_Block& Tetris_Falling_Block, char next_block_direction)
{

	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	/************************************/
	/*	フィールド上のブロックをクリア	*/
	/************************************/
	FallingBlockToBoard(Tetris_Falling_Block, 1, x_filed, y_filed);

	/************************************/
	/*	フィールド上のブロックを進める	*/
	/************************************/
	switch (next_block_direction)
	{
		/************************************/
		/*	ブロックの移動方向が左方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_LEFT:
		m_CurrentBlockTopPosX--;
		break;

		/************************************/
		/*	ブロックの移動方向が右方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_RIGHT:
		m_CurrentBlockTopPosX++;
		break;

		/************************************/
		/*	ブロックの移動方向が下方向		*/
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
/*	[関数]		CurrentMoveBlock		:	現在のブロックの移動処理			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		char					:	ブロック処理方法					*/
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
/*	[関数]		MoveBlockLeft			:	ブロックの移動処理 ( 左 )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				unsigned short			:	落下ブロックの位置 ( 横座標 )		*/
/*				unsigned short			:	落下ブロックの位置 ( 縦座標 )		*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlockLeft(CTetris_Falling_Block& Tetris_Falling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
		ブロックが左方向に移動できるか判定
			フィールド上にある現在のブロック領域の1つ左においてブロックが
			存在しないならば、右に進める
	*/

	char			left_block	= 0;
	unsigned short	block_top	= Tetris_Falling_Block.GetFallingBlockTop() - 1;
	unsigned short	block_left	= Tetris_Falling_Block.GetFallingBlockLeft() - 1;

	if ((x_filed + block_left) > TETRIS_FILED_START_X)
	{
		/************************************/
		/*	ブロックが左端に進める場合		*/
		/************************************/
		for (int y = block_top; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = TETRIS_FILED_START_X - 1; x >= 0; x--)
			{
				if (	(Tetris_Falling_Block.GetBlockState(x, y))						/*	現在のブロック情報にブロックがあり				*/
					&&	(m_Block(x_filed + x - 1, y_filed + y).GetBlockState()))		/*	フィールド上の一つ左にもブロックがあるならば	*/
				{
					if (x == 0)															/*	一番左のブロック情報であるならば				*/
					{
						left_block++;													/*	左にブロックが存在する							*/
					}
					else if (!Tetris_Falling_Block.GetBlockState(x - 1, y))				/*	現在のブロック情報の左にブロックがないならば	*/
					{
						left_block++;													/*	左にブロックが存在する							*/
					}
				}
			}

			if (y_filed + y > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	ブロックの移動判定		*/
		/****************************/
		if (	(!left_block)															/*	左にブロックが存在しないならば					*/
			&&	(m_CurrentBlockTopPosX > 0))
		{
			return true;
		}
	}

	return false;
}


/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockRight			:	ブロックの移動処理 ( 右 )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				unsigned short			:	落下ブロックの位置 ( 横座標 )		*/
/*				unsigned short			:	落下ブロックの位置 ( 縦座標 )		*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlockRight(CTetris_Falling_Block& Tetris_Falling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
			ブロックが右方向に移動できるか判定
				フィールド上にある現在のブロック領域の1つ右においてブロックが
				存在しないならば、右に進める
	*/

	char			right_block = 0;
	unsigned short	block_top	= Tetris_Falling_Block.GetFallingBlockTop() - 1;
	unsigned short	block_right	= Tetris_Falling_Block.GetFallingBlockRight() - 1;

	if ((m_CurrentBlockTopPosX < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X))
	{
		/************************************/
		/*	ブロックが右端に進める場合		*/
		/************************************/
		for (int y = block_top; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = 0; x < CURRENT_BLOCK_X; x++)
			{
				if (x_filed + x > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X)
					break;

				if (	(Tetris_Falling_Block.GetBlockState(x, y))						/*	現在のブロック情報にブロックがあり				*/
					&&	(m_Block(x_filed + x + 1, y_filed + y).GetBlockState()))		/*	フィールド上の一つ右にもブロックがあるならば	*/
				{	
					if (x == CURRENT_BLOCK_X - 1)										/*	一番右のブロック情報であるならば				*/
					{
						right_block++;													/*	右にブロックが存在する							*/
					}
					else if (!Tetris_Falling_Block.GetBlockState(x + 1, y))				/*	現在のブロック情報の右にブロックがないならば	*/
					{
						right_block++;													/*	右にブロックが存在する							*/
					}
				}
			}

			if (y_filed + y > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	ブロックの移動判定		*/
		/****************************/
		if (!right_block)																/*	右にブロックが存在しないならば					*/
		{
			return true;
		}
	}

	return false;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockDown			:	ブロックの移動処理 ( 下 )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				unsigned short			:	落下ブロックの位置 ( 横座標 )		*/
/*				unsigned short			:	落下ブロックの位置 ( 縦座標 )		*/
/*																				*/
/*==============================================================================*/
bool CTetris_Filed::MoveBlockDown(CTetris_Falling_Block& Tetris_Falling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
			ブロックの最下端の判定	
				現在のブロック領域の先頭からブロックの最下端位置を加算した値が
				フィールドより小さいならば、下に進める

		Note 2:
			ブロックが下方向に移動できるか判定
				フィールド上にある現在のブロック領域の1つ下においてブロックが
				存在しないならば、下に進める
	*/

	char			below_block		= 0;
	unsigned short	block_bottom	= Tetris_Falling_Block.GetFallingBlockBottom() - 1;
	unsigned short	block_left		= Tetris_Falling_Block.GetFallingBlockLeft() - 1;

	if((y_filed + block_bottom + 1) < TETRIS_FILED_SIZE_Y + TETRIS_FILED_START_Y)		/*	現在のブロックが領域外でないならば				*/
	{
		/************************************/
		/*	ブロックが下端に進める場合		*/
		/************************************/
		for (int y = 0; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = block_left; x < CURRENT_BLOCK_X; x++)
			{
				if (x_filed + x > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X)
					break;

				if (	(Tetris_Falling_Block.GetBlockState(x, y))						/*	現在のブロック情報にブロックがあり				*/
					&&	(m_Block(x_filed + x, y_filed + y + 1).GetBlockState()))		/*	フィールド上の一つ下にもブロックがあるならば	*/
				{
					if(y == CURRENT_BLOCK_Y - 1)										/*	一番下のブロック情報であるならば				*/
					{
						below_block++;													/*	下にブロックが存在する							*/
					}
					else if (!Tetris_Falling_Block.GetBlockState(x, y + 1))				/*	現在のブロック情報の下にブロックがないならば	*/
					{
						below_block++;													/*	下にブロックが存在する							*/
					}
				}
			}

			if (y_filed + y > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	ブロックの移動判定		*/
		/****************************/
		if (!below_block)																/*	下にブロックが存在しないならば					*/
		{
			return true;																/*	移動可能										*/
		}

	}

	return false;																		/*	移動不可										*/
}

/*==============================================================================*/
/*																				*/
/*	[関数]		RotateBlock				:	ブロックの回転処理					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	落下ブロック情報					*/
/*										:	回転方向 ( 0:CW 1:CCW )				*/
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
	/*	回転しないブロック	*/
	/************************/
	if (	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_EMPTY)
		|| 	(Tetris_Falling_Block.GetFallingBlockType() == BlockNS::FALLING_BLOCK_SQUARE_TYPE))
	{
		return false;
	}

	/************************************/
	/*	-90度方向しか回転しないブロック	*/
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
	/*	現在のブロック情報を回転	*/
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
	/*	回転可能か判定				*/
	/*		フィールド幅の判定		*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (tetris_block(x, y).GetBlockState() == BlockNS::EXISTENCE)
			{
				unsigned int x_rotate = x + x_filed;
				unsigned int y_rotate = y + y_filed;

				if (x_rotate < TETRIS_FILED_START_X)											/*	左端のフィールドを超えるならば	*/
				{
					shift_x = TETRIS_FILED_START_X - x_rotate;
				}
				else if (x_rotate > TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X - 1)				/*	右端のフィールドを超えるならば	*/
				{
					shift_x = (TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X - 1) - x_rotate;
				}
				else if (y_rotate > TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y - 1)				/*	下端のフィールドを超えるならば	*/
				{
					shift_y = (TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y - 1) - y_rotate;
				}
			}
		}
	}

	/************************************/
	/*	フィールド上のブロックをシフト	*/
	/************************************/
	if ((shift_x != 0) || (shift_y != 0))		/*	そのまま回転できないならば		*/
	{	
		m_CurrentBlockTopPosX += shift_x;
		m_CurrentBlockTopPosY += shift_y;
	}

	/************************************/
	/*	フィールド上のブロックをクリア	*/
	/************************************/
	FallingBlockToBoard(Tetris_Falling_Block, 1, x_filed, y_filed);

	/****************************************/
	/*	回転可能か判定						*/
	/*		フィールド上のブロックの判定	*/
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
	/*	回転したブロックをコピー	*/
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
/*	[関数]		MoveBlockFallMode		:	ブロックの落下モード				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::MoveBlockFallMode(CTetris_Falling_Block& Tetris_Falling_Block)
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	while (MoveBlockDown(Tetris_Falling_Block, x_filed, y_filed))
	{
		/********************************/
		/*	現在ブロックの位置を更新	*/
		/********************************/
		MoveBlockUpdate(Tetris_Falling_Block, BlockNS::BLOCK_MOVE_DOWN);
		x_filed = m_CurrentBlockTopPosX;
		y_filed = m_CurrentBlockTopPosY;

		/****************************/
		/*	ブロック状態を設定		*/
		/****************************/
		SetCurrentBlockState();

		/************************************/
		/*	ブロックをフィールドにコピー	*/
		/************************************/
		FallingBlockToBoard(Tetris_Falling_Block, 0, x_filed, y_filed);

	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		LandingBlockPos			:	落下ブロックの着地位置				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::LandingBlockPos()
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	/********************************/
	/*	着地ブロックの色の設定		*/
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
	/*	着地ブロック状態を設定		*/
	/********************************/
	m_LandingBlock.SetFallingBlockState();

	/************************/
	/*	落下地点まで処理	*/
	/************************/
	while (MoveBlockDown(m_LandingBlock, x_filed, y_filed))
	{
		/********************************/
		/*	現在ブロックの位置を更新	*/
		/********************************/
		y_filed++;
	}

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	m_LandingBlockTopPosX = x_filed;
	m_LandingBlockTopPosY = y_filed;
	
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		LandingBlockClear		:	落下ブロックの着地位置のクリア		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::LandingBlockClear()
{
	m_LandingBlock.FallingBlockInit();
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CheckBlockLine			:	行がブロックで埋まっている調べる	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CTetris_Filed::CheckBlockLine()
{
	bool			no_line_block = false;
	CTetris_Block	tetris_block(BlockNS::BLACK, BlockNS::EMPTY);
	char			continuity_flag = 0;

	/********************************/
	/*	消去ブロックの情報をクリア	*/
	/********************************/
	m_BlockDeleteInfo = 0;

	/********************************/
	/*	フィールド位置の情報		*/
	/********************************/
	for (int y_filed = TETRIS_FILED_START_Y; y_filed < TETRIS_FILED_START_Y + TETRIS_FILED_SIZE_Y; y_filed++)
	{	
		no_line_block = false;

		/********************************/
		/*	1行ブロックの存在判定		*/
		/********************************/
		for (int x_filed = TETRIS_FILED_START_X; x_filed < TETRIS_FILED_START_X + TETRIS_FILED_SIZE_X; x_filed++)
		{
			if ((m_Block(x_filed, y_filed).GetBlockState() != BlockNS::EXISTENCE))									/*	1行にブロックがないところがあるならば	*/
			{
				no_line_block = true;
				break;
			}
		}

		/********************************/
		/*	消去ブロックのカウント		*/
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
		/*	1行のブロックを更新			*/
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
					m_Block(x, y) = m_Block(x, y - 1);																/*	1行上のブロックを下に落とす				*/
				}
			}
		}

	}

	return;
}

/*======================================================================================*/
/*																						*/
/*	[関数]		CurrentBlockToBoard		:	現在のブロックをフィールドにコピー			*/
/*																						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし										*/
/*				char					:	フィールド上へのコピーモード				*/
/*												0	-> 消去　 							*/
/*												1	-> 現在のブロックをコピー			*/
/*												2	-> 次のブロックを開始位置にコピー	*/
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
/*	[関数]		GetCurrentBlockState	:	現在ブロックの位置情報を設定		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void  CTetris_Filed::SetCurrentBlockState()
{
	m_CurrentBlock.SetFallingBlockState();
	return;
}
/*==============================================================================*/
/*																				*/
/*	[関数]		GetBlockDeleteInfo		:	ブロック消去情報					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned char			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned char CTetris_Filed::GetBlockDeleteInfo() const
{
	return m_BlockDeleteInfo;
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
/*	[関数]		SetBlockColor		:	ブロックの色を設定						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を設定						*/
/*	[引数]							:	なし									*/
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
/*	[関数]		GetBlockState			:	ブロックがあるかどうかを取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
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
/*	[関数]		SetBlock				:	ブロックの状態を設定				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
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
/*	[関数]		GetBlockState			:	ブロックを取得						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを取得						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block CTetris_Filed::GetBlock(long x, long y) const
{
	return m_Block(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlock				:	ブロックを設定						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを設定						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
CTetris_Block& CTetris_Filed::SetBlock(long x, long y)
{
	return m_Block(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockTopPosX(		:	落下ブロックの位置情報を取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
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
/*	[関数]		GetBlockTopPosY			:	落下ブロックの位置情報を取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
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
/*	[関数]		GetFiledSizeX			:	フィールドサイズを取得				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetFiledSizeX() const
{
	return TETRIS_FILED_SIZE_X;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetFiledSizeY			:	フィールドサイズを取得				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]									なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CTetris_Filed::GetFiledSizeY() const
{
	return TETRIS_FILED_SIZE_Y;
}