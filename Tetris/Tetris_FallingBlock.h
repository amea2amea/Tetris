#ifndef Tetris_Falling_Block_h
#define Tetris_Falling_Block_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Tetris_Block.h"
#include "Array2D.h"

/*--------------*/
/*	クラス		*/
/*--------------*/

/****************************/
/*	落下ブロックのクラス	*/
/****************************/
class CTetris_Falling_Block
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CTetris_Falling_Block();											/* 引数なしコンストラクタ				*/			
	CTetris_Falling_Block(unsigned short, unsigned short);				/* 引数ありコンストラクタ				*/

	/*	デストラクタ	*/
	~CTetris_Falling_Block();

	/*	関数	*/
	void						SetFallingBlockState();					/* 落下ブロックの位置情報を設定			*/
	void						CreateFallingBlock(char);				/* 落下ブロックを作成					*/
	void						Clear();								/* 落下ブロックのメモリ解放				*/
	void						FallingBlockInit();						/* 落下ブロックの初期化					*/
	void						SetSize(unsigned short, unsigned short);/* 落下ブロックのサイズを設定			*/
	unsigned short				GetFallingBlockLeft() const;			/* 落下ブロックの左端					*/
	unsigned short				GetFallingBlockTop() const;				/* 落下ブロックの上端					*/
	unsigned short				GetFallingBlockRight() const;			/* 落下ブロックの右端					*/
	unsigned short				GetFallingBlockBottom() const;			/* 落下ブロックの下端					*/
	CTetris_Block				GetBlock(long, long) const;				/* 落下ブロックを取得					*/		
	CTetris_Block&				SetBlock(long, long);					/* 落下ブロックを設定					*/
	unsigned short				GetBlockColor(long, long);				/* 落下ブロック位置のカラーを取得		*/
	unsigned short&				SetBlockColor(long, long);				/* 落下ブロック位置のカラーをを設定		*/
	unsigned short				GetBlockState(long, long);				/* 落下ブロックの状態を取得				*/
	unsigned short&				SetBlockState(long, long);				/* 落下ブロックの状態を設定				*/
	unsigned short				GetFallingBlockType() const;			/* 落下ブロックのタイプを取得			*/
	unsigned short&				SetFallingBlockType();					/* 落下ブロックのタイプを設定			*/


	/*------------------*/
	/*	メンバ変数		*/
	/*------------------*/
private:
	Array2D< CTetris_Block >	m_FallingBlock;							/*	落下ブロックの情報					*/
	unsigned short				m_FallingBlockTop;						/*	落下ブロックの上端位置				*/	
	unsigned short				m_FallingBlockLeft;						/*	落下ブロックの左端位置				*/
	unsigned short				m_FallingBlockBottom;					/*	落下ブロックの下端位置				*/
	unsigned short				m_FallingBlockRight;					/*	落下ブロックの右端位置				*/
	unsigned short				m_FallingBlockType;						/*	落下ブロックのブロックタイプ		*/
	unsigned short				m_FallinggBlockX;						/*	落下ブロックサイズ (横)				*/
	unsigned short				m_FallinggBlockY;						/*	落下ブロックサイズ (縦)				*/

};
#endif
