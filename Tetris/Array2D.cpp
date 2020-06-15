
/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include <algorithm>
#include "Array2D.h"
#include "Tetris_Block.h"
#include "TetrisDraw.h"

/*--------------------------------------*/
/* �����I�e���v���[�g�̃C���X�^���X��	*/
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
/* �����o�֐�		*/
/*------------------*/

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[�֐�]	Array2D()		:	�R���X�g���N�^						*/
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
/*	[�֐�]	Array2D()		:	��������R���X�g���N�^				*/
/*																	*/
/*	---------------------------------------------------------------	*/
/*	[����]		int			:	�z���X���W�T�C�Y					*/
/*				int			:	�z���Y���W�T�C�Y					*/
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
/*	[�֐�]	Array2D			:	�R�s�[�R���X�g���N�^(�������ւ̃R�s�[)	*/
/*																		*/
/*	------------------------------------------------------------------	*/
/*	[����]		Array2D		:	Array2D�N���X							*/
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
/*	[�֐�]	~Array2D		:	�f�X�g���N�^				*/
/*															*/
/*	---------------------------------------------------		*/
/*	[����]		int			:	�z���X���W�T�C�Y			*/
/*				int			:	�z���Y���W�T�C�Y			*/
/*															*/
/*----------------------------------------------------------*/
Array2D<TYPE>::~Array2D()
{
	m_Array2D.clear();
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[�֐�]	Clear			:	�������̏���				*/
/*															*/
/*	---------------------------------------------------		*/
/*	[����]		void		:	�Ȃ�						*/
/*				void		:	�Ȃ�						*/
/*															*/
/*----------------------------------------------------------*/
void Array2D<TYPE>::Clear()
{
	m_Array2D.clear();
}

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[�֐�]	SetSize			:	�z��̍쐬							*/
/*																	*/
/*	---------------------------------------------------------------	*/
/*	[����]		int			:	�z���X���W�T�C�Y					*/
/*				int			:	�z���Y���W�T�C�Y					*/
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
/*	[�֐�]	operator()		:	�w�肳�ꂽ�z��ʒu�ւ̎Q��	*/
/*															*/
/*	------------------------------------------------------	*/
/*	[�߂�l]	const TYPE&	:	�w�肳�ꂽ�z��̎Q��		*/
/*	[����]		int			:	�Q�Ƃ���z���X���W�ʒu		*/
/*				int			:	�Q�Ƃ���z���Y���W�ʒu		*/
/*															*/
/*----------------------------------------------------------*/
const TYPE& Array2D<TYPE>::operator()( unsigned int x, unsigned int  y ) const
{
	return m_Array2D[ y * m_Size_X + x ];
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[�֐�]	operator()		:	�w�肳�ꂽ�z��ʒu�ւ̐ݒ�	*/
/*															*/
/*	------------------------------------------------------	*/
/*	[�߂�l]	TYPE&		:	�w�肳�ꂽ�z��̎Q��		*/
/*	[����]		int			:	�Q�Ƃ���z���X���W�ʒu		*/
/*				int			:	�Q�Ƃ���z���Y���W�ʒu		*/
/*															*/
/*----------------------------------------------------------*/
TYPE& Array2D<TYPE>::operator()( unsigned int x, unsigned int y )
{
	return m_Array2D[ y * m_Size_X + x ];
}

