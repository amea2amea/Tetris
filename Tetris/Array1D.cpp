/*------------------*/
/* インクルード		*/
/*------------------*/
#include <algorithm>
#include "Array1D.h"
#include "TetrisDraw.h"

/*--------------------------------------*/
/* 明示的テンプレートのインスタンス化	*/
/*--------------------------------------*/
template class Array1D<unsigned long>;
template class Array1D<unsigned short>;
template class Array1D<unsigned int>;
template class Array1D<long>;
template class Array1D<short>;
template class Array1D<int>;
template class Array1D<GeometryDraw>;
template class Array1D<TextRectDraw>;
template class Array1D<TextOutDraw>;

/*------------------*/
/* メンバ関数		*/
/*------------------*/

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[関数]	Array1D()		:	コンストラクタ						*/
/*------------------------------------------------------------------*/
Array1D<TYPE>::Array1D()
{
	m_Size	= 0;
	m_StartPoint = 0;
	m_Array1D.clear();
}

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[関数]	Array1D()		:	引数ありコンストラクタ				*/
/*	---------------------------------------------------------------	*/
/*	[引数]		int			:	配列のサイズ						*/
/*------------------------------------------------------------------*/
Array1D<TYPE>::Array1D( unsigned int size, int start_point)
{
	m_Size			= size;
	m_StartPoint	= start_point;
	m_Array1D.resize( m_Size );
}

template <typename TYPE>
/*--------------------------------------------------------------------------*/
/*																			*/
/*	[関数]	Array1D		:	コピーコンストラクタ(仮引数へのコピー)			*/
/*	------------------------------------------------------------------		*/
/*	[引数]		Array1D	:	Array1Dクラス									*/
/*--------------------------------------------------------------------------*/
Array1D<TYPE>::Array1D( const Array1D& other )
{
	m_Size = other.m_Size;
	m_Array1D.resize( m_Size );

	std::copy(other.m_Array1D.begin(), other.m_Array1D.end(), m_Array1D.begin());
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	~Array1D		:	デストラクタ				*/
/*	---------------------------------------------------		*/
/*	[引数]		int			:	配列のサイズ				*/
/*															*/
/*															*/
/*----------------------------------------------------------*/
Array1D<TYPE>::~Array1D()
{
	m_Array1D.clear();
}


template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	Clear			:	メモリの消去				*/
/*	---------------------------------------------------		*/
/*	[戻り値]	void		:	なし						*/
/*	[引数]		void		:	なし						*/
/*															*/
/*----------------------------------------------------------*/
void Array1D<TYPE>::Clear()
{
	m_Array1D.clear();
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	SetSize				:	配列の作成				*/
/*	--------------------------------------------------------*/
/*	[戻り値]	void			:	なし					*/
/*	[引数]		unsigned int	:	配列のサイズ			*/
/*				int				:	開始位置				*/
/*															*/
/*----------------------------------------------------------*/
void Array1D<TYPE>::SetSize( unsigned int size, int start_point)
{
	m_Size			= size;
	m_StartPoint	= start_point;
	m_Array1D.resize( m_Size );

	return;
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	operator()		:	指定された配列位置への参照	*/
/*	---------------------------------------------------		*/
/*	[戻り値]	const int&	:	指定された配列の参照		*/
/*	[引数]		int			:	参照する配列位置			*/
/*															*/
/*----------------------------------------------------------*/
const TYPE& Array1D<TYPE>::operator()( int pos ) const
{
	if (pos >= m_StartPoint)
		return m_Array1D[pos - m_StartPoint];
	else
		return m_Array1D[0];
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	operator()		:	指定された配列位置への設定	*/
/*	-------------------------------------------------------	*/
/*	[戻り値]	const int&	:	指定された配列の参照		*/
/*	[引数]		int			:	参照する配列位置			*/
/*															*/
/*----------------------------------------------------------*/
TYPE& Array1D<TYPE>::operator()( int pos )
{
	if (pos >= m_StartPoint)
		return m_Array1D[pos - m_StartPoint];
	else
		return m_Array1D[0];
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	operator()		:	指定された配列位置への参照	*/
/*	---------------------------------------------------		*/
/*	[戻り値]	const int&	:	指定された配列の参照		*/
/*	[引数]		int			:	参照する配列位置			*/
/*															*/
/*----------------------------------------------------------*/
const TYPE& Array1D<TYPE>::operator[]( int pos ) const
{
	if (pos >= m_StartPoint)
		return m_Array1D[pos - m_StartPoint];
	else
		return m_Array1D[0];
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[関数]	operator()		:	指定された配列位置への設定	*/
/*	-------------------------------------------------------	*/
/*	[戻り値]	const int&	:	指定された配列の参照		*/
/*	[引数]		int			:	参照する配列位置			*/
/*															*/
/*----------------------------------------------------------*/
TYPE& Array1D<TYPE>::operator[]( int pos )
{
	if (pos >= m_StartPoint)
		return m_Array1D[pos - m_StartPoint];
	else
		return m_Array1D[0];
}