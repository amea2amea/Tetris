#ifndef Array1D_h
#define Array1D_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include <vector>

/*--------------------------*/
/*	�e���v���[�g�N���X		*/
/*--------------------------*/
template <typename TYPE>															

class Array1D														/* 1�����z��𑀍삷�邽�߂̃N���X		*/
{
/*--------------*/
/*	�����o�ϐ�	*/
/*--------------*/
private:
	std::vector<TYPE>		m_Array1D;								/* �z��f�[�^							*/
	int						m_Size;									/* �z��T�C�Y							*/
	int						m_StartPoint;							/* �z��J�n�ʒu							*/

/*--------------*/
/*	�����o�֐�	*/
/*--------------*/	
public:
	void operator=(const Array1D& other) {};						/* �N���X�̑������( = ����)�͋֎~		*/
	Array1D();														/* �R���X�g���N�^						*/
	Array1D( unsigned int, int);									/* �R���X�g���N�^						*/
	Array1D( const Array1D& );										/* �R�s�[�R���X�g���N�^					*/
	~Array1D();														/* �f�X�g���N�^							*/
	void		Clear();											/* �������̏���							*/
	void		SetSize( unsigned int, int );						/* �z��̍쐬							*/
	const TYPE&	operator()( int ) const;							/* ()�ɂ��w�肳�ꂽ�z��ʒu�ւ̎Q��	*/
	TYPE&		operator()( int );									/* ()�ɂ��w�肳�ꂽ�z��ʒu�ւ̐ݒ�	*/
	const TYPE&	operator[]( int ) const;							/* []�ɂ��w�肳�ꂽ�z��ʒu�ւ̎Q��	*/
	TYPE&		operator[]( int );									/* []�ɂ��w�肳�ꂽ�z��ʒu�ւ̐ݒ�	*/

};

#endif
