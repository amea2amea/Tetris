#ifndef _TETRIS_DRAW_H
#define _TETRIS_DRAW_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Graphics.h"
#include "TetrisLogic.h"

namespace TetrisDrawNS
{
	enum TITLE_POS								/*	�^�C�g���̕\���ʒu				*/
	{
		SCORE_TITLE				= 2,			/*	�X�R�A�̃^�C�g��				*/
		FALL_TIME_TITLE			= 4,			/*	�������Ԃ̃^�C�g��				*/
		NEXT_BLOCK_TITLE		= 6,			/*	���̃u���b�N�̃^�C�g��			*/
		NEXT_WAIT_BLOCK_TITLE	= 9				/*	���̑ҋ@�u���b�N�̃^�C�g��		*/
	};

	enum CONTENT_POS							/*	���e�̕\���ʒu					*/
	{
		SCORE				= 3,				/*	�X�R�A							*/
		FALL_TIME			= 5,				/*	��������						*/
		NEXT_BLOCK			= 12,				/*	���̃u���b�N					*/
		NEXT_WAIT_BLOCK		= 18				/*	���̑ҋ@�u���b�N				*/
	};
}

/*--------------*/
/*	�\����		*/
/*--------------*/
struct Block_Rect
{
	/*----------------------*/
	/*	���W�ʒu			*/
	/*----------------------*/
	long	left;												/*	���W�ʒu ( ���[ )							*/
	long	top;												/*	���W�ʒu ( ��[ )							*/
	long	right;												/*	���W�ʒu ( �E�[ )							*/
	long	bottom;												/*	���W�ʒu ( ���[ )							*/

	/*----------------------*/
	/*	�R���X�g���N�^		*/
	/*----------------------*/
	Block_Rect()												/*	�����Ȃ��R���X�g���N�^						*/
	{
		Block_Rect(0, 0, 0, 0);
	}

	Block_Rect(long left, long top, long right, long bottom)	/*	��������R���X�g���N�^						*/
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		���Z�q�I�[�o�[���[�h	*/
	/*------------------------------*/

	const Block_Rect& operator()(long left, long top, long right, long bottom) const	/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Block_Rect(left, top, right, bottom);
	}

	Block_Rect& operator()(long left, long top, long right, long bottom)				/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Block_Rect(left, top, right, bottom);
	}
};

/*----------------------------------*/
/*	�e�g���X�̕`��N���X			*/
/*----------------------------------*/
class CTetrisDraw : public CGraphics
//					public CTetrisLogic
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CTetrisDraw();

	/*	�f�X�g���N�^	*/
	virtual	~CTetrisDraw();

	/*	�֐�	*/

protected:
	/*	���z�֐�	*/
	virtual void	Draw();

private:
	void			SetTetrisColor();
	void			SetTetrisText();
	COLORREF		GetColor(long, long, char);
	Block_Rect		GetBlockRect(long x_index, long y_index);
	void			SetBlockRect(long x_index, long y_index, Block_Rect);
	void			InitBlockRect();

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	��`�p�ϐ� ( const )	*/
	static const short				TETRIS_BLOCK_PIXEL_SIZE_X	= 20;			/*	�e�g���X�u���b�N�̃s�N�Z���T�C�Y (��)		*/
	static const short				TETRIS_BLOCK_PIXEL_SIZE_Y	= 20;			/*	�e�g���X�u���b�N�̃s�N�Z���T�C�Y (�c)		*/
	static const short				TETRIS_BLOCK_PIXEL_START_X	= 5;			/*	�e�g���X�u���b�N�̃s�N�Z���̊J�n�ʒu (��)	*/
	static const short				TETRIS_BLOCK_PIXEL_START_Y	= 5;			/*	�e�g���X�u���b�N�̃s�N�Z���̊J�n�ʒu (�c)	*/
	static const short				TETRIS_BLOCK_PIXEL_END_X	= 25;			/*	�e�g���X�u���b�N�̃s�N�Z���̏I���ʒu (��)	*/
	static const short				TETRIS_BLOCK_PIXEL_END_Y	= 25;			/*	�e�g���X�u���b�N�̃s�N�Z���̏I���ʒu (�c)	*/
	static const short				TETRIS_BLOCK_MARGIN_LEFT	= 2;			/*	�e�g���X�u���b�N�̃s�N�Z���̃}�[�W�� (��)	*/
	static const short				TETRIS_BLOCK_MARGIN_TOP		= 2;			/*	�e�g���X�u���b�N�̃s�N�Z���̃}�[�W�� (��)	*/
	static const short				TETRIS_BLOCK_MARGIN_RIGHT	= 2;			/*	�e�g���X�u���b�N�̃s�N�Z���̃}�[�W�� (�E)	*/
	static const short				TETRIS_BLOCK_MARGIN_BOTTOM	= 2;			/*	�e�g���X�u���b�N�̃s�N�Z���̃}�[�W�� (��)	*/

private:
	CTetris_Filed&					m_Tetris_Filed;								/*	�e�g���X�̃u���b�N���						*/
	Array2D< Block_Rect >			m_BlockRect;								/*	�u���b�N�̏��								*/
	Array2D< Block_Rect >			m_WaitBlockRect;							/*	�ҋ@�u���b�N�̏��							*/
	Array2D< Block_Rect >			m_WaitNextBlockRect;						/*	���̑ҋ@�u���b�N�̏��						*/
	Array2D< Block_Rect >			m_LandingBlockRect;							/*	���n�\���u���b�N�̏��						*/

};
#endif
