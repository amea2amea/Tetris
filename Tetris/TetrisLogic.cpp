/*------------------*/
/* インクルード		*/
/*------------------*/
#include "TetrisManger.h"
#include "TetrisLogic.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CTetrisLogic		:	コンストラクタ ( 引数なし )				*/
/*																				*/
/*==============================================================================*/
CTetrisLogic::CTetrisLogic():m_Tetris_Filed(CTetrisManger::Instance()->GetTetrisFiled())
{
	CTetrisManger::Instance()->SetTetrisFallingTime()		= TETRIS_FALL_TIME;
	CTetrisManger::Instance()->SetTetrisNextBlockWaitTime() = TETRIS_NEXTBLOCK_WAIT_TIME;
	m_TimeStart	= timeGetTime();
	m_CurrentBlockFallTimeMode	= false;
	m_CurrentBlockLandingMode	= false;
	m_Init						= false;
	m_Finish					= false;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		~CTetrisLogic		:	デストラクタ							*/
/*																				*/
/*==============================================================================*/
CTetrisLogic::~CTetrisLogic()
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Logic				:	ロジック								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::Logic(CInput* input)
{
	/************************/
	/*	終了処理			*/
	/************************/
	if (m_Finish == true)
		return;
	
	/************************/
	/*	初期化処理			*/
	/************************/
	if (m_Init == false)
	{
		Init();					/*	初期化処理			*/
	}

	/************************/
	/*	キー処理			*/
	/************************/
	if (Keydown(input))
	{
		UpdateBlock();
	}

	/************************/
	/*	更新処理			*/
	/************************/
	Update();

	return;

}
/*==============================================================================*/
/*																				*/
/*	[関数]		Init				:	初期設定								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::Init()
{
	/********************/
	/*	テトリスを作成	*/
	/********************/
	m_Tetris_Filed.Init();

	/****************************/
	/*	次のブロックの初期設定	*/
	/****************************/
	m_Tetris_Filed.NextWaitBlockInit();

	/********************************/
	/*	現在のブロック状態を設定	*/
	/********************************/
	m_Tetris_Filed.SetCurrentBlockState();

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	m_Tetris_Filed.CurrentBlockToBoard(2);

	/************************/
	/*	待機ブロックを作成	*/
	/************************/
	m_Tetris_Filed.NextWaitBlock();

	/****************/
	/*	初期化完了	*/
	/****************/
	m_Init = true;

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		Keydown				:	キーダウン処理							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
bool CTetrisLogic::Keydown(CInput* input)
{
	char keycord		= input->GetKeyPressed();
	char ctrl_keydown	= input->isKeyDown(VK_CONTROL);
	bool block_move = false;

	/********************************/
	/*	落下モードの状態チェック	*/
	/********************************/
	if (!ctrl_keydown)
	{
		m_CurrentBlockFallTimeMode = false;
	}

	switch (keycord)
	{
	case VK_LEFT:
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_LEFT);
		break;

	case VK_RIGHT:
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_RIGHT);
		break;

	case VK_DOWN:
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_KEYDOWN_POINTS;
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN);
		break;

	case VK_SPACE:
   		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_ROTATE_CW);
		break;

	case VK_B:	/* B	*/
	case VK_C:	/* C	*/
	case VK_V:	/* V	*/
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_ROTATE_CCW);
		break;
		
	case VK_CONTROL:
		if (!m_CurrentBlockFallTimeMode)
		{
			unsigned short FiledY = m_Tetris_Filed.GetFiledSizeY();
			unsigned short PosY = m_Tetris_Filed.GetBlockTopPosY(BlockNS::CURRENT_BLOCK);
			CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_KEYDOWN_POINTS * (FiledY - PosY);
			block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_FALL_MODE);
			m_CurrentBlockFallTimeMode = true;
		}
		break;

	case VK_RETURN:
		if (m_CurrentBlockLandingMode)
		{
			m_CurrentBlockLandingMode = false;
			m_Tetris_Filed.LandingBlockClear();
		}
		else
		{
			m_CurrentBlockLandingMode = true;
		}
		break;

	default:
		break;
	}

	return block_move;
}
/*==============================================================================*/
/*																				*/
/*	[関数]		Update				:	更新処理								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::Update()
{
	/************************/
	/*	更新タイマー処理	*/
	/************************/
	if (!UpdateTimer())
		return;

	/************************/
	/*	ブロック更新処理	*/
	/************************/
	if (m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN))						/*	ブロックの移動が可能					*/
	{
		UpdateBlock();

		if (m_CurrentBlockLandingMode)
		{
			m_Tetris_Filed.LandingBlockPos();
		}
	}
	else																				/*	ブロックの移動が不可 ( 着地済 )			*/
	{
		/****************************/
		/*	ゲーム終了の判定		*/
		/****************************/
		if (m_Tetris_Filed.isGameOver())												/*	ゲームオーバーならば					*/
		{
			m_Finish = true;
		}
		else																			/*	次のブロックへ進むならば				*/
		{
			/********************************/
			/*	ブロック行のチェック処理	*/
			/********************************/
			m_Tetris_Filed.CheckBlockLine();

			/************************/
			/*	得点の更新処理		*/
			/************************/
			UpdatePoint();

			/****************************/
			/*	次のブロックを作成		*/
			/****************************/
			m_Tetris_Filed.NextCurrentBlock();											/*	次のブロックの作成						*/
			m_Tetris_Filed.NextWaitBlock();												/*	待機ブロックの作成						*/

			/****************************************/
			/*	次のブロックをフィールドにコピー	*/
			/****************************************/
			m_Tetris_Filed.CurrentBlockToBoard(2);

			/****************************/
			/*	次のブロックの待ち時間	*/
			/****************************/
			Sleep(CTetrisManger::Instance()->GetTetrisNextBlockWaitTime());
		}
	}

	/********************/
	/*	時間の更新		*/
	/********************/
	m_TimeStart = m_TimeEnd;

	return;

}
/*==============================================================================*/
/*																				*/
/*	[関数]		UpdateBlock			:	ブロック更新処理						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::UpdateBlock()
{
	/********************************/
	/*	現在のブロック状態を設定	*/
	/********************************/
	m_Tetris_Filed.SetCurrentBlockState();

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	m_Tetris_Filed.CurrentBlockToBoard(0);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		UpdateTimer			:	更新タイマー処理						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
bool CTetrisLogic::UpdateTimer()
{
	/************************************/
	/*	更新タイマーのスピードアップ	*/
	/************************************/
	unsigned long	points			= CTetrisManger::Instance()->GetTetrisPoint();
	unsigned long	falling_time	= CTetrisManger::Instance()->GetTetrisFallingTime();
	
	if (	(falling_time == TETRIS_FALL_TIME)
		&&	(points > TETRIS_TETRIS_POINTS))
	{
		CTetrisManger::Instance()->SetTetrisFallingTime()		-= TETRIS_FALL_TIME_SPEED_UP;
		CTetrisManger::Instance()->SetTetrisNextBlockWaitTime() += TETRIS_NEXTBLOCK_WAIT_SLOW;
	}
	else if (	(falling_time == TETRIS_FALL_TIME - TETRIS_FALL_TIME_SPEED_UP)
			&&	(points > TETRIS_TETRIS_POINTS * 2))
	{
		CTetrisManger::Instance()->SetTetrisFallingTime()		-= TETRIS_FALL_TIME_SPEED_UP;
		CTetrisManger::Instance()->SetTetrisNextBlockWaitTime() += TETRIS_NEXTBLOCK_WAIT_SLOW;
	}

	/************************/
	/*	更新タイマー処理	*/
	/************************/
	DWORD UpDateTimer = 0;
	m_TimeEnd = timeGetTime();
	UpDateTimer = m_TimeEnd - m_TimeStart;

	if (UpDateTimer < falling_time)
	{
		return false;
	}
	else
	{
		return true;
	}

}

/*==============================================================================*/
/*																				*/
/*	[関数]		UpdatePoint			:	得点の更新処理							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::UpdatePoint()
{
	unsigned char block_delete = m_Tetris_Filed.GetBlockDeleteInfo();

	/************************/
	/*	得点処理 ( 連段 )	*/
	/************************/
	if (block_delete & BIT0)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_SINGLE_POINTS;
	}	
	else if (block_delete & BIT1)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_DOUBLE_POINTS;
	}
	else if (block_delete & BIT2)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_TRIPLE_POINTS;
	}
	else if (block_delete & BIT3)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_TETRIS_POINTS;
	}

	/************************/
	/*	シングル ( 複数 )	*/
	/************************/
	if (block_delete & BIT4)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_SINGLE_POINTS * 2;
	}

	return;

}
