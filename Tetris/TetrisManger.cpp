/*------------------*/
/* インクルード		*/
/*------------------*/
#include "TetrisManger.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CTetrisManger		:	コンストラクタ ( 引数なし )				*/
/*																				*/
/*==============================================================================*/
CTetrisManger::CTetrisManger()
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		~CTetrisManger		:	デストラクタ							*/
/*																				*/
/*==============================================================================*/
CTetrisManger::~CTetrisManger()
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Instance					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
CTetrisManger* CTetrisManger::Instance()
{
	static CTetrisManger instance;
	return &instance;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetTetrisFiled				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
CTetris_Filed& CTetrisManger::GetTetrisFiled()
{
	return m_Tetris_Filed;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetTetrisPoint			:	テトリスの得点						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	DWORD 			:												*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
DWORD CTetrisManger::GetTetrisPoint() const
{
	return m_Tetris_Points;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetTetrisPoint			:	テトリスの得点						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	DWORD 			:												*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
DWORD& CTetrisManger::SetTetrisPoint()
{
	return m_Tetris_Points;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetTetrisPoint			:	テトリスの落下時間					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	DWORD 					:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
DWORD CTetrisManger::GetTetrisFallingTime() const
{
	return m_FallingTime;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetTetrisPoint			:	テトリスの落下時間					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	DWORD 					:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
DWORD& CTetrisManger::SetTetrisFallingTime()
{
	return m_FallingTime;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetTetrisNextBlockWaitTime	:	テトリスの次ブロック待ち時間	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	DWORD 						:									*/
/*	[引数]									:	なし							*/
/*																				*/
/*==============================================================================*/
DWORD CTetrisManger::GetTetrisNextBlockWaitTime() const
{
	return m_NextBlockWaitTime;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetTetrisNextBlockWaitTime	:	テトリスの次ブロック待ち時間	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	DWORD 						:									*/
/*	[引数]									:	なし							*/
/*																				*/
/*==============================================================================*/
DWORD& CTetrisManger::SetTetrisNextBlockWaitTime()
{
	return m_NextBlockWaitTime;
}