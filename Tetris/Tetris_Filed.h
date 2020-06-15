#ifndef Tetris_Filed_h
#define Tetris_Filed_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Tetris_Block.h"
#include "Tetris_FallingBlock.h"
#include "Array2D.h"

/*--------------*/
/*	構造体		*/
/*--------------*/
struct Block_Point												/*	ボート位置の構造体							*/
{
	/*----------------------*/
	/*	座標位置			*/
	/*----------------------*/
	unsigned int x;												/*	座標位置 ( 横 )								*/
	unsigned int y;												/*	座標位置 ( 縦 )								*/

	/*----------------------*/
	/*	コンストラクタ		*/
	/*----------------------*/
	Block_Point()												/*	引数なしコンストラクタ						*/
	{
		Block_Point(0, 0);
	}

	Block_Point(int x, int y)									/*	引数ありコンストラクタ						*/
	{
		this->x = x;
		this->y = y;
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		演算子オーバーロード	*/
	/*------------------------------*/

	const Block_Point& operator()(int x, int y) const			/*	位置を指定したときの操作　( 代入用 )		*/
	{
		return Block_Point(x, y);
	}

	Block_Point& operator()(int x, int y)						/*	位置を指定したときの操作　( 操作用 )		*/
	{
		return Block_Point(x, y);
	}
};

/*--------------*/
/*	クラス		*/
/*--------------*/

/************************/
/*	ボードのクラス		*/
/************************/
class CTetris_Filed 
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CTetris_Filed();										/* 引数なしコンストラクタ				*/

	/*	デストラクタ	*/
	~CTetris_Filed();

	/*	関数	*/
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
	unsigned short			GetBlockColor(long,long, char);		/* ブロック位置のカラーを取得			*/
	unsigned short&			SetBlockColor(long, long, char);	/* ブロック位置のカラーをを設定			*/
	unsigned short			GetBlockState(long, long, char);	/* ブロックの状態を取得					*/
	unsigned short&			SetBlockState(long, long, char);	/* ブロックの状態を設定					*/
	unsigned short			GetBlockTopPosX(char) const;
	unsigned short			GetBlockTopPosY(char) const;
	unsigned short			GetFiledSizeX() const;
	unsigned short			GetFiledSizeY() const;

private:
	/*	関数	*/
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
	/*	メンバ変数		*/
	/*------------------*/
public:
	/*	定義用変数 ( const )	*/
	static const short						TETRIS_FILED_SIZE_X = 10;											/*	テトリスのの横サイズ							*/
	static const short						TETRIS_FILED_SIZE_Y = 20;											/*	テトリスの縦サイズ								*/
	static const short						TETRIS_FILED_SIZE = TETRIS_FILED_SIZE_X * TETRIS_FILED_SIZE_Y;		/*	テトリスのフィールドサイズ						*/
	static const short						TETRIS_FILED_START_X = 3;											/*	テトリスの開始位置 (横)							*/
	static const short						TETRIS_FILED_START_Y = 4;											/*	テトリスの開始位置 (縦)							*/
	static const short						COLOR_NUM = 3;														/*	色の種類										*/
	static const short						COLOR_START_POINT = -1;												/*	色の開始データ									*/
	static const short						CURRENT_BLOCK_X = 5;												/*	落下ブロックサイズ (横)							*/
	static const short						CURRENT_BLOCK_Y = 5;												/*	落下ブロックサイズ (縦)							*/
	static const short						CURRENT_BLOCK_START_X = 5;											/*	落下ブロックの開始位置 (横)						*/
	static const short						CURRENT_BLOCK_START_Y = 0;											/*	落下ブロックの開始位置 (縦)						*/

protected:
	Array2D< CTetris_Block >				m_Block;															/*	ブロックの情報									*/
	CTetris_Falling_Block					m_CurrentBlock;														/*	落下ブロックの情報 ( 落下ブロック )				*/
	CTetris_Falling_Block					m_WaitBlock;														/*	待機のブロックの情報 ( 次の落下ブロック )		*/
	CTetris_Falling_Block					m_WaitNextBlock;													/*	待機の次のブロックの情報 ( 次の待機ブロック )	*/
	CTetris_Falling_Block					m_LandingBlock;														/*	落下ブロックの着地位置							*/
	unsigned short							m_CurrentBlockTopPosX;												/*	落下ブロックのフィールド位置 ( 横 )				*/
	unsigned short							m_CurrentBlockTopPosY;												/*	落下ブロックのフィールド位置 ( 縦 )				*/
	unsigned short							m_LandingBlockTopPosX;												/*	落下ブロックの着地位置  ( 横 )					*/
	unsigned short							m_LandingBlockTopPosY;												/*	落下ブロックの着地位置 ( 縦 )					*/
	short									m_CurrentBlockRotatinAngle;											/*	落下ブロック回転角度							*/
	
	unsigned char							m_BlockDeleteInfo;													/*	ブロックの消去情報								*/	
																												/*	Bit0 : 1段消去									*/
																												/*	Bit1 : 2段消去									*/
																												/*	Bit2 : 3段消去									*/
																												/*	Bit3 : 4段消去									*/
																												/*	Bit4 : 1段消去 ( 2つ目 )						*/

};
#endif