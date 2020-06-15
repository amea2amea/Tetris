#ifndef Tetris_Block_h
#define Tetris_Block_h

namespace BlockNS
{
	enum Block_Color									/*	�u���b�N�J���[�̏��						*/
	{
		RED,											/*	��											*/
		YELLOW,											/*	��											*/
		PINK,											/*	�s���N										*/
		GREEN,											/*	��											*/
		BLUE,											/*	��											*/
		CYAN,											/*	�V�A��										*/
		ORANGE,											/*	�I�����W									*/
		BLACK,											/*	��											*/
		WHITE,											/*	��											*/
		DIMGRAY,										/*	�f�B���O���C ( �Â��O���C )					*/
		LIGHTGRAY,										/*	���C�g�O���C ( �W���O���C )					*/
		GRAY											/*	�O���C										*/
	};

	enum Block_State									/*	�u���b�N�̏��								*/
	{
		EXISTENCE	= 1,								/*	�u���b�N����								*/
		EMPTY		= 0,								/*	�u���b�N�Ȃ�								*/
		WALL		= 2									/*	��											*/
	};

	enum Block_Move										/*	�u���b�N�̈ړ�����							*/
	{
		BLOCK_MOVE_LEFT,								/*	�u���b�N�̈ړ�������������					*/
		BLOCK_MOVE_RIGHT,								/*	�u���b�N�̈ړ��������E����					*/
		BLOCK_MOVE_DOWN,								/*	�u���b�N�̈ړ�������������					*/
		BLOCK_MOVE_ROTATE_CW,							/*	�u���b�N�̈ړ�������CW��]					*/
		BLOCK_MOVE_ROTATE_CCW,							/*	�u���b�N�̈ړ�������CCW��]					*/
		BLOCK_MOVE_FALL_MODE,							/*	�u���b�N�̗������[�h						*/
		BLOCK_MOVE_LANDING_MODE							/*	�u���b�N�̒��n�ʒu�\�����[�h				*/
	};

	enum Block_Rotation									/*	�u���b�N�̉�]����							*/
	{
		BLOCK_CW_ROTATION,								/*	�u���b�N�̉�]������CW��]					*/
		BLOCK_CCW_ROTATION								/*	�u���b�N�̉�]������CCW��]					*/
	};

	enum Block_Type										/*	�u���b�N									*/
	{
		FILED_BLOCK,									/*	�t�B�[���h��̃u���b�N						*/
		CURRENT_BLOCK,									/*	���݂̃u���b�N								*/
		WAIT_BLOCK,										/*	�ҋ@�u���b�N ( ���̃u���b�N )				*/
		WAIT_NEXT_BLOCK,								/*	�ҋ@�u���b�N ( ���̑ҋ@�u���b�N )			*/
		LANDING_BLOCK									/*	���n�_�\���u���b�N							*/
	};

	enum Falling_Block_Type								/*	�����u���b�N�̎��							*/
	{
		FALLING_BLOCK_EMPTY,							/*	���݃u���b�N�Ȃ�							*/
		FALLING_BLOCK_ROD_TYPE,							/*	�c�_										*/
		FALLING_BLOCK_L_TYPE,							/*	L �^										*/
		FALLING_BLOCK_REVERSE_L_TYPE,					/*	�t L �^										*/
		FALLING_BLOCK_Z_TYPE,							/*	Z �^										*/
		FALLING_BLOCK_REVERSE_Z_TYPE,					/*	�t Z �^										*/
		FALLING_BLOCK_CONVEX_TYPE,						/*	�� �^										*/
		FALLING_BLOCK_SQUARE_TYPE,						/*	�����` �^									*/
	};
}

/*--------------*/
/*	�N���X		*/
/*--------------*/
class CTetris_Block										/*	�e�g���X�̃u���b�N�N���X			*/
{

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CTetris_Block();									/* �����Ȃ��R���X�g���N�^				*/
	CTetris_Block( short, unsigned short );				/* ��������R���X�g���N�^				*/

	/*	�f�X�g���N�^	*/
	~CTetris_Block();

	/*	�֐�	*/
	unsigned short				GetBlockColor() const;	/* �u���b�N�ʒu�̃J���[���擾			*/
	unsigned short&				SetBlockColor();		/* �u���b�N�ʒu�̃J���[����ݒ�			*/
	unsigned short				GetBlockState() const;	/* �u���b�N�̏�Ԃ��擾					*/
	unsigned short&				SetBlockState();		/* �u���b�N�̏�Ԃ�ݒ�					*/

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	unsigned short				m_Color;				/* �u���b�N�̐F							*/
	unsigned short				m_BlockState;			/* �u���b�N�̏��						*/


};
#endif