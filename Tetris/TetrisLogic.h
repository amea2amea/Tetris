#ifndef _TETRIS_LOGIC_H
#define _TETRIS_LOGIC_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "GameLogic.h"
#include "Tetris_Filed.h"

/*----------------------------------*/
/*	プロセスのコントロールクラス	*/
/*----------------------------------*/
class CTetrisLogic : public CGameLogic
{
	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CTetrisLogic();

	/*	デストラクタ	*/
	virtual	~CTetrisLogic();

	/*	関数	*/

protected:

	/*	仮想関数	*/
	virtual void	Logic(CInput*);

private:
	void			Init();
	void			Update();
	void			UpdateBlock();
	void			UpdatePoint();
	bool			UpdateTimer();
	bool			Keydown(CInput*);

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/
	static const short				TETRIS_FALL_TIME			= 300;		/*	テトリス落下時間の更新時間				*/
	static const short				TETRIS_NEXTBLOCK_WAIT_TIME	= 300;		/*	テトリス落下時間の更新時間				*/
	static const short				TETRIS_FALL_TIME_SPEED_UP	= 100;		/*	テトリス落下時間の速度更新				*/
	static const short				TETRIS_NEXTBLOCK_WAIT_SLOW	= 100;		/*	テトリス落下時間の速度更新				*/
	static const short				TETRIS_SINGLE_POINTS		= 40;		/*	テトリス得点 ( シングル )				*/
	static const short				TETRIS_DOUBLE_POINTS		= 100;		/*	テトリス得点 ( ダブル )					*/
	static const short				TETRIS_TRIPLE_POINTS		= 300;		/*	テトリス得点 ( トリプル )				*/
	static const short				TETRIS_TETRIS_POINTS		= 1200;		/*	テトリス得点 ( テトリス )				*/
	static const short				TETRIS_KEYDOWN_POINTS		= 1;		/*	テトリス得点 ( キーダウン )				*/

protected:
	CTetris_Filed&					m_Tetris_Filed;							/*	テトリスのブロック情報					*/

private:
	DWORD 							m_TimeStart;							/*	更新開始時間							*/
	DWORD		 					m_TimeEnd;								/*	更新終了時間							*/
	bool							m_Init;									/*	初期化フラグ							*/
																			/*		true	: 初期化済み				*/
																			/*		false	: 初期化してない			*/

	bool							m_Finish;								/*	終了フラグ								*/
																			/*		true	: 終了済み					*/
																			/*		false	: 終了してない				*/

	bool							m_CurrentBlockFallTimeMode;				/*	落下高速モード							*/
	bool							m_CurrentBlockLandingMode;				/*	落下ブロックの着地位置表示モード		*/

};
#endif
