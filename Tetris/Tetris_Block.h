#ifndef Tetris_Block_h
#define Tetris_Block_h

namespace BlockNS
{
	enum Block_Color									/*	ブロックカラーの状態						*/
	{
		RED,											/*	赤											*/
		YELLOW,											/*	黄											*/
		PINK,											/*	ピンク										*/
		GREEN,											/*	緑											*/
		BLUE,											/*	青											*/
		CYAN,											/*	シアン										*/
		ORANGE,											/*	オレンジ									*/
		BLACK,											/*	黒											*/
		WHITE,											/*	白											*/
		DIMGRAY,										/*	ディムグレイ ( 暗いグレイ )					*/
		LIGHTGRAY,										/*	ライトグレイ ( 淡いグレイ )					*/
		GRAY											/*	グレイ										*/
	};

	enum Block_State									/*	ブロックの状態								*/
	{
		EXISTENCE	= 1,								/*	ブロックあり								*/
		EMPTY		= 0,								/*	ブロックなし								*/
		WALL		= 2									/*	壁											*/
	};

	enum Block_Move										/*	ブロックの移動方向							*/
	{
		BLOCK_MOVE_LEFT,								/*	ブロックの移動方向が左方向					*/
		BLOCK_MOVE_RIGHT,								/*	ブロックの移動方向が右方向					*/
		BLOCK_MOVE_DOWN,								/*	ブロックの移動方向が下方向					*/
		BLOCK_MOVE_ROTATE_CW,							/*	ブロックの移動方向がCW回転					*/
		BLOCK_MOVE_ROTATE_CCW,							/*	ブロックの移動方向がCCW回転					*/
		BLOCK_MOVE_FALL_MODE,							/*	ブロックの落下モード						*/
		BLOCK_MOVE_LANDING_MODE							/*	ブロックの着地位置表示モード				*/
	};

	enum Block_Rotation									/*	ブロックの回転方向							*/
	{
		BLOCK_CW_ROTATION,								/*	ブロックの回転方向がCW回転					*/
		BLOCK_CCW_ROTATION								/*	ブロックの回転方向がCCW回転					*/
	};

	enum Block_Type										/*	ブロック									*/
	{
		FILED_BLOCK,									/*	フィールド上のブロック						*/
		CURRENT_BLOCK,									/*	現在のブロック								*/
		WAIT_BLOCK,										/*	待機ブロック ( 次のブロック )				*/
		WAIT_NEXT_BLOCK,								/*	待機ブロック ( 次の待機ブロック )			*/
		LANDING_BLOCK									/*	着地点表示ブロック							*/
	};

	enum Falling_Block_Type								/*	落下ブロックの種類							*/
	{
		FALLING_BLOCK_EMPTY,							/*	現在ブロックなし							*/
		FALLING_BLOCK_ROD_TYPE,							/*	縦棒										*/
		FALLING_BLOCK_L_TYPE,							/*	L 型										*/
		FALLING_BLOCK_REVERSE_L_TYPE,					/*	逆 L 型										*/
		FALLING_BLOCK_Z_TYPE,							/*	Z 型										*/
		FALLING_BLOCK_REVERSE_Z_TYPE,					/*	逆 Z 型										*/
		FALLING_BLOCK_CONVEX_TYPE,						/*	凸 型										*/
		FALLING_BLOCK_SQUARE_TYPE,						/*	正方形 型									*/
	};
}

/*--------------*/
/*	クラス		*/
/*--------------*/
class CTetris_Block										/*	テトリスのブロッククラス			*/
{

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CTetris_Block();									/* 引数なしコンストラクタ				*/
	CTetris_Block( short, unsigned short );				/* 引数ありコンストラクタ				*/

	/*	デストラクタ	*/
	~CTetris_Block();

	/*	関数	*/
	unsigned short				GetBlockColor() const;	/* ブロック位置のカラーを取得			*/
	unsigned short&				SetBlockColor();		/* ブロック位置のカラーをを設定			*/
	unsigned short				GetBlockState() const;	/* ブロックの状態を取得					*/
	unsigned short&				SetBlockState();		/* ブロックの状態を設定					*/

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	unsigned short				m_Color;				/* ブロックの色							*/
	unsigned short				m_BlockState;			/* ブロックの状態						*/


};
#endif