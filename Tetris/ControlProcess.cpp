/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "ControlProcess.h"

/*------------------*/
/* extern�錾		*/
/*------------------*/
extern CControlProcess*		g_pAppWndProc;				/*	�E�B���h�E���R���g���[������N���X�̃|�C���^		*/

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CControlProcess		:	�R���X�g���N�^ ( �����Ȃ� )				*/
/*																				*/
/*==============================================================================*/
CControlProcess::CControlProcess()
{
	m_pWindowCreator	= new CWindowCreator();
	m_pInput			= new CInput();
	m_pGameLogic		= 0;
	m_pGraphics			= 0;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CControlProcess	:	�R���X�g���N�^ ( �������� )					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[����]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CControlProcess::CControlProcess(HINSTANCE hInstance, LPTSTR lpCmdLine) :
			CFameWork(hInstance, lpCmdLine)
		,	m_hMutex(NULL)
		,	m_hMutexCP(NULL)
{
	m_pWindowCreator	= new CWindowCreator();
	m_pInput			= new CInput();
	m_pGameLogic		= 0;
	m_pGraphics			= 0;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CControlProcess			:	�f�X�g���N�^					*/
/*																				*/
/*==============================================================================*/
CControlProcess::~CControlProcess()
{
	delete m_pWindowCreator;
	delete m_pInput;
	m_pGameLogic = 0;
	m_pGraphics = 0;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Initialize					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
bool CControlProcess::Initialize()
{
	/********************************/
	/*	�E�B���h�E�n���h���̎擾	*/
	/********************************/
	SetWindowHandle(m_pWindowCreator->GetWindowHandle());

	if (m_pGraphics != NULL)
	{
		m_pGraphics->SetWindowHandle(m_pWindowCreator->GetWindowHandle());
		m_pGraphics->SetWindowHFont(m_pWindowCreator->GetWindowHFont());
		m_pGraphics->Create();
	}
	else
	{
		return false;
	}

	/********************/
	/*	�e�평���ݒ�	*/
	/********************/
	m_pInput->Initialize(GetWindowHandle(), 0);

	/****************************************************************/
	/*	������\�p�t�H�[�}���X�J�E���^�̎��g�� ( �X�V�p�x )���擾	*/
	/****************************************************************/
	if (QueryPerformanceFrequency(&m_TimerFreq) == false)
	{
		;
	}

	/************************************/
	/*	1���[�v�����̊J�n���Ԃ��擾		*/
	/************************************/
	QueryPerformanceCounter(&m_TimeStart);

	return true;
}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		Create					:										*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool						:	�E�B���h�E�̍쐬				*/
/*												���� -> 1,	���s -> 0			*/
/*	[����]		HINSTANCE	hInstance		:	�C���X�^���X�̃n���h��			*/
/*				UINT_PTR	nCmdShow		:	�E�B���h�E�\���̎w��			*/
/*																				*/
/*==============================================================================*/
bool CControlProcess::Create(HINSTANCE hInstance)
{
	bool ret = false;
	
	if (m_pWindowCreator == NULL)
		return ret;

	if (m_pInput == NULL)
		return ret;

	/************************************/
	/*	�E�B���h�E�̃|�C���^���擾		*/
	/************************************/
	g_pAppWndProc = this;

	/************************************/
	/*	�E�B���h�E�̍쐬				*/
	/************************************/
	ret = m_pWindowCreator->Create(hInstance);

	return ret;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MessageLoop					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CControlProcess::MessageLoop()
{
	/*	
		Note 1:
			GetMessage��PeekMessage�̈Ⴂ
				�������郁�b�Z�[�W�������ꍇ�A
				GetMessage�̓��b�Z�[�W��҂��܂����APeekMessage�͑҂��܂���	
				�܂�Awhile�̃��[�v�������i���ɑ������ƂɂȂ�܂��B
	
		Note 2:
			TranslateMessage�Ƃ�				
				TranslateMessage�́A���z�L�[���b�Z�[�W��ASCII�R�[�h�ɕϊ����A
				WM_CHAR, WM_SYSCHAR��V�������o���ă|�X�g���邾����	
				���̃��b�Z�[�W�͂��̂܂܃|�X�g�����		
	*/					
	
	MSG	msg;
	int ret	= 0;

	while (1)
	{
		ret = ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);				/*	���b�Z�[�W���擾									*/

		if (msg.message == WM_QUIT)										/*	�I�����b�Z�[�W�Ȃ��								*/
		{
			break;														/*	���[�v���甲����									*/
		}
		else if(ret == 0)												/*	������������Ȃ� ( �A�C�h�����ԂȂ�� )				*/
		{
			Update();													/*	�X�V�������s��										*/
		}
		else															/*	�����������ꂽ��Ȃ��								*/
		{
			::TranslateMessage(&msg);									/*	���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�			*/
			::DispatchMessage(&msg);									/*	�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�			*/
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Update						:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CControlProcess::Update()
{
	/********************************/
	/*	�t���[�����[�g�̍X�V		*/
	/********************************/
	if (!FramesTime())
		return;

	/****************/
	/*	�X�V����	*/
	/****************/
	if(m_pGameLogic != NULL)
		m_pGameLogic->Logic(m_pInput);

	/****************/
	/*	�`�揈��	*/
	/****************/
	if (m_pGraphics != NULL)
		m_pGraphics->DrawMain();

	/************************/
	/*	���͂̃N���A����	*/
	/************************/
	m_pInput->Clear(inputNS::KEYS_PRESSED);			/*	���͂̏����N���A		*/

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		FramesTime					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
bool CControlProcess::FramesTime()
{
	/************************************/
	/*	1���[�v�����̏I�����Ԃ��擾		*/
	/************************************/
	QueryPerformanceCounter(&m_TimeEnd);

	/********************************************************************/
	/*	1���[�v�Ɋ|����o�ߎ��Ԃ��v�Z									*/
	/*		�������� = 1�����̎��� �� ���g�� ( 1�b�������CPU������ )	*/
	/********************************************************************/
	if(m_TimerFreq.QuadPart != 0)
		m_FrameTime = (double)(m_TimeEnd.QuadPart - m_TimeStart.QuadPart) / (double)m_TimerFreq.QuadPart;

	/************************************/
	/*	1���[�v�Ɋ|����o�ߎ��Ԃ��v�Z	*/
	/************************************/
	if (m_FrameTime < FramesRateNS::MIN_FRAME_TIME)														/*	��]����t���[�����Ԃɑ΂��Čo�ߎ��Ԃ��Z���Ȃ��	*/
	{
		/************************************************/
		/*	CPU�������Ԃɂ����ė]�������Ԃ�����ꍇ		*/
		/************************************************/
		m_SleepTime = (DWORD)((FramesRateNS::MIN_FRAME_TIME - m_FrameTime) * 1000);						/*	�]�������Ԃ͑ҋ@���ԂƂ��邽�ߌv�Z����				*/
		Sleep(m_SleepTime);																				/*	���b�Z�[�W�������s����悤�ɂ��邽�߂ɑ҂�		*/

		return false;
	}
	else if (m_FrameTime > 0.0)
	{
		/********************************************/
		/*	�Q�[��1�b������̃t���[����				*/
		/*		( 1�b�Ԃɉ��񃁃C�����[�v����邩 )	*/
		/********************************************/
		m_fps = (m_fps * 0.99f) + (0.01f / m_FrameTime);												/*	���� fps ( �Q�[��1�b������̃t���[���� )			*/
	}

	if (m_FrameTime > FramesRateNS::MAX_FRAME_TIME)														/*	�t���[�����Ԃ����ɒx���Ȃ��						*/
	{
		m_FrameTime = FramesRateNS::MAX_FRAME_TIME;														/*	�t���[�����Ԃ��ő�l�ɐݒ�							*/
	}

	/****************************************/
	/*	�O��̏I�����Ԃ��J�n���Ԃɐݒ�		*/
	/****************************************/
	m_TimeStart = m_TimeEnd;

	return true;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DispatchEvent	:	�E�B���h�E�v���V�[�W��						*/
/*									( �E�B���h�E�R�[���o�b�N�֐� )				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	LRESULT WINAPI 	:	�W���̃E�B���h�E�v���V�[�W���̏������s��	*/
/*	[����]		HWND			:	�E�B���h�E�n���h��							*/
/*				UINT_PTR		:	���b�Z�[�W									*/
/*				WPARAM			:												*/
/*				LPARAM			:												*/
/*																				*/
/*==============================================================================*/
LRESULT CALLBACK CControlProcess::DispatchEvent(HWND hwnd, UINT_PTR msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		/****************************/
		/*	�I��					*/
		/****************************/
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		/****************************/
		/*	�E�B���h�E���쐬���ꂽ	*/
		/****************************/
	case WM_CREATE:
		m_pWindowCreator->MyCreateFont(NULL, 100, 0);
		return 0;

		/****************************/
		/*	�L�[�̉�������			*/
		/****************************/
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		m_pInput->KeyDown(wParam);
		return 0;

		/****************************/
		/*	�L�[�̉����グ			*/
		/****************************/
	case WM_KEYUP:
	case WM_SYSKEYUP:
		m_pInput->KeyUp(wParam);
		return 0;

		/****************************/
		/*	���������͂��ꂽ		*/
		/****************************/
	case WM_CHAR:
		m_pInput->TextIn(wParam);
		return 0;

		/****************************/
		/*	�ݒ�L�[�������ꂽ		*/
		/****************************/
	case WM_INPUT:
		m_pInput->MouseRawIn(lParam);
		return 0;

		/****************************/
		/*	���N���b�N�̉�������	*/
		/****************************/
	case WM_LBUTTONDOWN:
		m_pInput->SetMouseLButton(true);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	���N���b�N�̉����グ	*/
		/****************************/
	case WM_LBUTTONUP:
		m_pInput->SetMouseLButton(false);
		m_pInput->MouseIn(lParam);
		return 0;

		/************************************/
		/*	�}�E�X�̒����{�^���̉�������	*/
		/************************************/
	case WM_MBUTTONDOWN:
		m_pInput->SetMouseMButton(true);
		m_pInput->MouseIn(lParam);
		return 0;

		/************************************/
		/*	�}�E�X�̒����{�^���̉����グ	*/
		/************************************/
	case WM_MBUTTONUP:
		m_pInput->SetMouseMButton(false);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	�E�N���b�N�̉�������	*/
		/****************************/
	case WM_RBUTTONDOWN:
		m_pInput->SetMouseRButton(true);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	�E�N���b�N�̉����グ	*/
		/****************************/
	case WM_RBUTTONUP:
		m_pInput->SetMouseRButton(false);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	�}�E�X�̈ړ����ꂽ		*/
		/****************************/
	case WM_MOUSEMOVE:
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************************/
		/*	���@�\�}�E�X�̃{�^�����b�Z�[�W		*/
		/****************************************/
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		m_pInput->SetMouseXButton(wParam);
		m_pInput->MouseIn(lParam);
		return 0;

		/****************************/
		/*	�`�惁�b�Z�[�W			*/
		/****************************/
	case WM_PAINT:
		if (m_pGraphics != NULL)
			m_pGraphics->DrawMain();
		return 0;

	default:
		break;

	}

	return DefWindowProc(hwnd, static_cast<UINT>(msg), wParam, lParam);

}
