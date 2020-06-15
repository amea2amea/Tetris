#ifndef Array2D_h
#define Array2D_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include <vector>

/*--------------------------*/
/*	�e���v���[�g�N���X		*/
/*--------------------------*/
template <typename TYPE>

class Array2D															/* 1�����z���2�����̂悤�ɑ��삷�邽�߂̃N���X		*/
{
/*--------------*/
/*	�����o�ϐ�	*/
/*--------------*/
private:
	std::vector<TYPE>	m_Array2D;
	int					m_Size_X;
	int					m_Size_Y;

/*--------------*/
/*	�����o�֐�	*/
/*--------------*/
public:
	void operator=(const Array2D& other) {};							/* �N���X�̑������( = ����)�͋֎~					*/
	Array2D();															/* �R���X�g���N�^									*/
	Array2D( unsigned int, unsigned int );								/* �R���X�g���N�^									*/
	Array2D( const Array2D& );											/* �R�s�[�R���X�g���N�^								*/
	~Array2D();															/* �f�X�g���N�^										*/
	void		Clear();												/* �������̏���										*/
	void		SetSize( unsigned int, unsigned int );					/* �z��̍쐬										*/
	const TYPE&	operator()( unsigned int, unsigned int ) const;			/* 2�����z�񑀍�̎Q��								*/
	TYPE&		operator()( unsigned int, unsigned int );				/* 2�����z�񑀍�̐ݒ�								*/

};

#endif