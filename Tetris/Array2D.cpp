
/*------------------*/
/* インクルード		*/
/*------------------*/
#include <algorithm>
#include "Array2D.h"
#include "Tetris_Block.h"
#include "TetrisDraw.h"

/*--------------------------------------*/
/* 明示的テンプレートのインスタンス化	*/
/*--------------------------------------*/
template class Array2D<unsigned long>;
template class Array2D<unsigned short>;
template class Array2D<unsigned int>;
template class Array2D<long>;
template class Array2D<short>;
template class Array2D<int>;
template class Array2D<CTetris_Block>;
template class Array2D<Block_Rect>;

/*------------------*/
/* メンバ関数		*/
/*------------------*/

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[関数]	Array2D()		:	コンストラクタ						*/
/*																	*/
/*------------------------------------------------------------------*/
Array2D<TYPE>::Array2D()
{
	m_Size_X	= 0;
	m_Size_Y	= 0;
	m_Array2D.clear();
}

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[関数]	Array2D()		:	引数ありコンストラクタ				*/
/*																	*/
/*	---------------------------------------------------------------	*/
/*	[引数]		int			:	配列のX座標サイズ					*/
/*				int			:	配列のY座標サイズ					*/
/*																	*/
/*------------------------------------------------------------------*/
Array2D<TYPE>::Array2D(unsigned int x, unsigned int y )
{
	m_Size_X = x;
	m_Size_Y = y;
	m_Array2D.resize( m_Size_X * m_Size_Y );
}

template <typename TYPE>
/*----------------------------------------------------------------------*/
/*																		*/
/*	[関数]	Array2D			:	コピーコンストラクタ(仮引数へのコピー)	*/
/*																		*/
/*	------------------------------------------------------------------	*/
/*	[引数]		Array2D		:	Array2Dクラス							*/
/*																		*/
/*----------------------------------------------------------------------*/
Array2D<TYPE>::Array2D( const Array2D& other )
{
	m_Size_X = other.m_Size_X;
	m_Size_Y = other.m_Size_Y;
	m_Array2D.resize( m_Size_X * m_Size_Y );
	
	std::copy(other.m_Array2D.begin(), other.m_Array2D.end(), m_Array2D.begin());
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	~Array2D		:	デストラクタ				*/
/*															*/
/*	---------------------------------------------------		*/
/*	[引数]		int			:	配列のX座標サイズ			*/
/*				int			:	配列のY座標サイズ			*/
/*															*/
/*----------------------------------------------------------*/
Array2D<TYPE>::~Array2D()
{
	m_Array2D.clear();
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	Clear			:	メモリの消去				*/
/*															*/
/*	---------------------------------------------------		*/
/*	[引数]		void		:	なし						*/
/*				void		:	なし						*/
/*															*/
/*----------------------------------------------------------*/
void Array2D<TYPE>::Clear()
{
	m_Array2D.clear();
}

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[関数]	SetSize			:	配列の作成							*/
/*																	*/
/*	---------------------------------------------------------------	*/
/*	[引数]		int			:	配列のX座標サイズ					*/
/*				int			:	配列のY座標サイズ					*/
/*																	*/
/*------------------------------------------------------------------*/
void Array2D<TYPE>::SetSize( unsigned int  x, unsigned int y )
{
	m_Size_X = x;
	m_Size_Y = y;
	m_Array2D.resize( m_Size_X * m_Size_Y );

	return;
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	operator()		:	指定された配列位置への参照	*/
/*															*/
/*	------------------------------------------------------	*/
/*	[戻り値]	const TYPE&	:	指定された配列の参照		*/
/*	[引数]		int			:	参照する配列のX座標位置		*/
/*				int			:	参照する配列のY座標位置		*/
/*															*/
/*----------------------------------------------------------*/
const TYPE& Array2D<TYPE>::operator()( unsigned int x, unsigned int  y ) const
{
	return m_Array2D[ y * m_Size_X + x ];
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	operator()		:	指定された配列位置への設定	*/
/*															*/
/*	------------------------------------------------------	*/
/*	[戻り値]	TYPE&		:	指定された配列の参照		*/
/*	[引数]		int			:	参照する配列のX座標位置		*/
/*				int			:	参照する配列のY座標位置		*/
/*															*/
/*----------------------------------------------------------*/
TYPE& Array2D<TYPE>::operator()( unsigned int x, unsigned int y )
{
	return m_Array2D[ y * m_Size_X + x ];
}

