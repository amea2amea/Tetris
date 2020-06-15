/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "TetrisManger.h"
#include "TetrisLogic.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CTetrisLogic		:	�R���X�g���N�^ ( �����Ȃ� )				*/
/*																				*/
/*==============================================================================*/
CTetrisLogic::CTetrisLogic():m_Tetris_Filed(CTetrisManger::Instance()->GetTetrisFiled())
{
	CTetrisManger::Instance()->SetTetrisFallingTime()		= TETRIS_FALL_TIME;
	CTetrisManger::Instance()->SetTetrisNextBlockWaitTime() = TETRIS_NEXTBLOCK_WAIT_TIME;
	m_TimeStart	= timeGetTime();
	m_CurrentBlockFallTimeMode	= false;
	m_CurrentBlockLandingMode	= false;
	m_Init						= false;
	m_Finish					= false;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CTetrisLogic		:	�f�X�g���N�^							*/
/*																				*/
/*==============================================================================*/
CTetrisLogic::~CTetrisLogic()
{
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Logic				:	���W�b�N								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::Logic(CInput* input)
{
	/************************/
	/*	�I������			*/
	/************************/
	if (m_Finish == true)
		return;
	
	/************************/
	/*	����������			*/
	/************************/
	if (m_Init == false)
	{
		Init();					/*	����������			*/
	}

	/************************/
	/*	�L�[����			*/
	/************************/
	if (Keydown(input))
	{
		UpdateBlock();
	}

	/************************/
	/*	�X�V����			*/
	/************************/
	Update();

	return;

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		Init				:	�����ݒ�								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::Init()
{
	/********************/
	/*	�e�g���X���쐬	*/
	/********************/
	m_Tetris_Filed.Init();

	/****************************/
	/*	���̃u���b�N�̏����ݒ�	*/
	/****************************/
	m_Tetris_Filed.NextWaitBlockInit();

	/********************************/
	/*	���݂̃u���b�N��Ԃ�ݒ�	*/
	/********************************/
	m_Tetris_Filed.SetCurrentBlockState();

	/************************************/
	/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
	/************************************/
	m_Tetris_Filed.CurrentBlockToBoard(2);

	/************************/
	/*	�ҋ@�u���b�N���쐬	*/
	/************************/
	m_Tetris_Filed.NextWaitBlock();

	/****************/
	/*	����������	*/
	/****************/
	m_Init = true;

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Keydown				:	�L�[�_�E������							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
bool CTetrisLogic::Keydown(CInput* input)
{
	char keycord		= input->GetKeyPressed();
	char ctrl_keydown	= input->isKeyDown(VK_CONTROL);
	bool block_move = false;

	/********************************/
	/*	�������[�h�̏�ԃ`�F�b�N	*/
	/********************************/
	if (!ctrl_keydown)
	{
		m_CurrentBlockFallTimeMode = false;
	}

	switch (keycord)
	{
	case VK_LEFT:
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_LEFT);
		break;

	case VK_RIGHT:
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_RIGHT);
		break;

	case VK_DOWN:
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_KEYDOWN_POINTS;
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN);
		break;

	case VK_SPACE:
   		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_ROTATE_CW);
		break;

	case VK_B:	/* B	*/
	case VK_C:	/* C	*/
	case VK_V:	/* V	*/
		block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_ROTATE_CCW);
		break;
		
	case VK_CONTROL:
		if (!m_CurrentBlockFallTimeMode)
		{
			unsigned short FiledY = m_Tetris_Filed.GetFiledSizeY();
			unsigned short PosY = m_Tetris_Filed.GetBlockTopPosY(BlockNS::CURRENT_BLOCK);
			CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_KEYDOWN_POINTS * (FiledY - PosY);
			block_move = m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_FALL_MODE);
			m_CurrentBlockFallTimeMode = true;
		}
		break;

	case VK_RETURN:
		if (m_CurrentBlockLandingMode)
		{
			m_CurrentBlockLandingMode = false;
			m_Tetris_Filed.LandingBlockClear();
		}
		else
		{
			m_CurrentBlockLandingMode = true;
		}
		break;

	default:
		break;
	}

	return block_move;
}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		Update				:	�X�V����								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::Update()
{
	/************************/
	/*	�X�V�^�C�}�[����	*/
	/************************/
	if (!UpdateTimer())
		return;

	/************************/
	/*	�u���b�N�X�V����	*/
	/************************/
	if (m_Tetris_Filed.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN))						/*	�u���b�N�̈ړ����\					*/
	{
		UpdateBlock();

		if (m_CurrentBlockLandingMode)
		{
			m_Tetris_Filed.LandingBlockPos();
		}
	}
	else																				/*	�u���b�N�̈ړ����s�� ( ���n�� )			*/
	{
		/****************************/
		/*	�Q�[���I���̔���		*/
		/****************************/
		if (m_Tetris_Filed.isGameOver())												/*	�Q�[���I�[�o�[�Ȃ��					*/
		{
			m_Finish = true;
		}
		else																			/*	���̃u���b�N�֐i�ނȂ��				*/
		{
			/********************************/
			/*	�u���b�N�s�̃`�F�b�N����	*/
			/********************************/
			m_Tetris_Filed.CheckBlockLine();

			/************************/
			/*	���_�̍X�V����		*/
			/************************/
			UpdatePoint();

			/****************************/
			/*	���̃u���b�N���쐬		*/
			/****************************/
			m_Tetris_Filed.NextCurrentBlock();											/*	���̃u���b�N�̍쐬						*/
			m_Tetris_Filed.NextWaitBlock();												/*	�ҋ@�u���b�N�̍쐬						*/

			/****************************************/
			/*	���̃u���b�N���t�B�[���h�ɃR�s�[	*/
			/****************************************/
			m_Tetris_Filed.CurrentBlockToBoard(2);

			/****************************/
			/*	���̃u���b�N�̑҂�����	*/
			/****************************/
			Sleep(CTetrisManger::Instance()->GetTetrisNextBlockWaitTime());
		}
	}

	/********************/
	/*	���Ԃ̍X�V		*/
	/********************/
	m_TimeStart = m_TimeEnd;

	return;

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		UpdateBlock			:	�u���b�N�X�V����						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::UpdateBlock()
{
	/********************************/
	/*	���݂̃u���b�N��Ԃ�ݒ�	*/
	/********************************/
	m_Tetris_Filed.SetCurrentBlockState();

	/************************************/
	/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
	/************************************/
	m_Tetris_Filed.CurrentBlockToBoard(0);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		UpdateTimer			:	�X�V�^�C�}�[����						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
bool CTetrisLogic::UpdateTimer()
{
	/************************************/
	/*	�X�V�^�C�}�[�̃X�s�[�h�A�b�v	*/
	/************************************/
	unsigned long	points			= CTetrisManger::Instance()->GetTetrisPoint();
	unsigned long	falling_time	= CTetrisManger::Instance()->GetTetrisFallingTime();
	
	if (	(falling_time == TETRIS_FALL_TIME)
		&&	(points > TETRIS_TETRIS_POINTS))
	{
		CTetrisManger::Instance()->SetTetrisFallingTime()		-= TETRIS_FALL_TIME_SPEED_UP;
		CTetrisManger::Instance()->SetTetrisNextBlockWaitTime() += TETRIS_NEXTBLOCK_WAIT_SLOW;
	}
	else if (	(falling_time == TETRIS_FALL_TIME - TETRIS_FALL_TIME_SPEED_UP)
			&&	(points > TETRIS_TETRIS_POINTS * 2))
	{
		CTetrisManger::Instance()->SetTetrisFallingTime()		-= TETRIS_FALL_TIME_SPEED_UP;
		CTetrisManger::Instance()->SetTetrisNextBlockWaitTime() += TETRIS_NEXTBLOCK_WAIT_SLOW;
	}

	/************************/
	/*	�X�V�^�C�}�[����	*/
	/************************/
	DWORD UpDateTimer = 0;
	m_TimeEnd = timeGetTime();
	UpDateTimer = m_TimeEnd - m_TimeStart;

	if (UpDateTimer < falling_time)
	{
		return false;
	}
	else
	{
		return true;
	}

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		UpdatePoint			:	���_�̍X�V����							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CTetrisLogic::UpdatePoint()
{
	unsigned char block_delete = m_Tetris_Filed.GetBlockDeleteInfo();

	/************************/
	/*	���_���� ( �A�i )	*/
	/************************/
	if (block_delete & BIT0)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_SINGLE_POINTS;
	}	
	else if (block_delete & BIT1)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_DOUBLE_POINTS;
	}
	else if (block_delete & BIT2)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_TRIPLE_POINTS;
	}
	else if (block_delete & BIT3)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_TETRIS_POINTS;
	}

	/************************/
	/*	�V���O�� ( ���� )	*/
	/************************/
	if (block_delete & BIT4)
	{
		CTetrisManger::Instance()->SetTetrisPoint() += TETRIS_SINGLE_POINTS * 2;
	}

	return;

}
