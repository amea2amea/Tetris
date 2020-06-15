#ifndef Tetris_Manger_h
#define Tetris_Manger_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "Tetris_Filed.h"
#include "Array2D.h"

/*--------------------------------------*/
/*	マネジャークラス ( シングルトン )	*/ 
/*--------------------------------------*/
class CTetrisManger
{

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	コンストラクタ	*/
	CTetrisManger();
	CTetrisManger(const CTetrisManger&);
	
	/*	コピーコンストラクタ	*/
	void operator=(const CTetrisManger&) {};				/* クラスの代入操作( = 操作)は禁止			*/

public:
	/*	デストラクタ	*/
	virtual	~CTetrisManger();
	
	/*	関数	*/
	CTetris_Filed&				GetTetrisFiled();
	static CTetrisManger*		Instance();
	DWORD						GetTetrisPoint() const;
	DWORD&						SetTetrisPoint();
	DWORD						GetTetrisFallingTime() const;
	DWORD&						SetTetrisFallingTime();
	DWORD						GetTetrisNextBlockWaitTime() const;
	DWORD&						SetTetrisNextBlockWaitTime();

	/*------------------*/
	/*	メンバ変数		*/
	/*------------------*/
private:
	CTetris_Filed				m_Tetris_Filed;				/*	テトリスの情報							*/
	DWORD		 				m_Tetris_Points;			/*	点数									*/
	DWORD		 				m_FallingTime;				/*	落下時間								*/
	DWORD		 				m_NextBlockWaitTime;		/*	次のブロックの待ち時間					*/


};
#endif