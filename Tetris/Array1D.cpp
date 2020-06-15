/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include <algorithm>
#include "Array1D.h"
#include "TetrisDraw.h"

/*--------------------------------------*/
/* �����I�e���v���[�g�̃C���X�^���X��	*/
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
/* �����o�֐�		*/
/*------------------*/

template <typename TYPE>
/*------------------------------------------------------------------*/
/*																	*/
/*	[�֐�]	Array1D()		:	�R���X�g���N�^						*/
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
/*	[�֐�]	Array1D()		:	��������R���X�g���N�^				*/
/*	---------------------------------------------------------------	*/
/*	[����]		int			:	�z��̃T�C�Y						*/
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
/*	[�֐�]	Array1D		:	�R�s�[�R���X�g���N�^(�������ւ̃R�s�[)			*/
/*	------------------------------------------------------------------		*/
/*	[����]		Array1D	:	Array1D�N���X									*/
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
/*	[�֐�]	~Array1D		:	�f�X�g���N�^				*/
/*	---------------------------------------------------		*/
/*	[����]		int			:	�z��̃T�C�Y				*/
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
/*	[�֐�]	Clear			:	�������̏���				*/
/*	---------------------------------------------------		*/
/*	[�߂�l]	void		:	�Ȃ�						*/
/*	[����]		void		:	�Ȃ�						*/
/*															*/
/*----------------------------------------------------------*/
void Array1D<TYPE>::Clear()
{
	m_Array1D.clear();
}

template <typename TYPE>
/*----------------------------------------------------------*/
/*															*/
/*	[�֐�]	SetSize				:	�z��̍쐬				*/
/*	--------------------------------------------------------*/
/*	[�߂�l]	void			:	�Ȃ�					*/
/*	[����]		unsigned int	:	�z��̃T�C�Y			*/
/*				int				:	�J�n�ʒu				*/
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
/*	[�֐�]	operator()		:	�w�肳�ꂽ�z��ʒu�ւ̎Q��	*/
/*	---------------------------------------------------		*/
/*	[�߂�l]	const int&	:	�w�肳�ꂽ�z��̎Q��		*/
/*	[����]		int			:	�Q�Ƃ���z��ʒu			*/
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
/*	[�֐�]	operator()		:	�w�肳�ꂽ�z��ʒu�ւ̐ݒ�	*/
/*	-------------------------------------------------------	*/
/*	[�߂�l]	const int&	:	�w�肳�ꂽ�z��̎Q��		*/
/*	[����]		int			:	�Q�Ƃ���z��ʒu			*/
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
/*	[�֐�]	operator()		:	�w�肳�ꂽ�z��ʒu�ւ̎Q��	*/
/*	---------------------------------------------------		*/
/*	[�߂�l]	const int&	:	�w�肳�ꂽ�z��̎Q��		*/
/*	[����]		int			:	�Q�Ƃ���z��ʒu			*/
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
/*	[�֐�]	operator()		:	�w�肳�ꂽ�z��ʒu�ւ̐ݒ�	*/
/*	-------------------------------------------------------	*/
/*	[�߂�l]	const int&	:	�w�肳�ꂽ�z��̎Q��		*/
/*	[����]		int			:	�Q�Ƃ���z��ʒu			*/
/*															*/
/*----------------------------------------------------------*/
TYPE& Array1D<TYPE>::operator[]( int pos )
{
	if (pos >= m_StartPoint)
		return m_Array1D[pos - m_StartPoint];
	else
		return m_Array1D[0];
}