/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "WindowCreator.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CWindowCreator		:	�R���X�g���N�^ ( �����Ȃ� )				*/
/*																				*/
/*==============================================================================*/
CWindowCreator::CWindowCreator()	:
				m_Clase_Name(_T("WinMain"))
			,	m_Title(_T("Window"))
			,	m_IsFullScreen(WindowCreatorNS::DEFAULT_SCREEN_MODE)
			,	m_WindowWidth(WindowCreatorNS::DEFAULT_WINDOW_WIDTH)
			,	m_WindowHeight(WindowCreatorNS::DEFAULT_WINDOW_HEIGHT)

{
	m_hInstance = NULL;
	m_hWnd		= NULL;
	m_hFont		= NULL;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CWindowCreators	:	�R���X�g���N�^ ( �������� )					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[����]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CWindowCreator::CWindowCreator(LPTSTR class_name, LPTSTR title_name, bool displaymode, long window_width, long window_height) :
				m_Clase_Name(class_name)
			,	m_Title(title_name)
			,	m_IsFullScreen(displaymode)
			,	m_WindowWidth(window_width)
			,	m_WindowHeight(window_height)
{
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CControlProcess			:	�f�X�g���N�^					*/
/*																				*/
/*==============================================================================*/
CWindowCreator::~CWindowCreator()
{
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
bool CWindowCreator::Create(HINSTANCE hInstance)
{

	/********************************/
	/*	�E�B���h�E�N���X�̐ݒ�		*/
	/********************************/
	MyRegisterClass(hInstance);

	/****************************/
	/*	�E�B���h�E�̍쐬		*/
	/****************************/
	if (!MyCreateWindow(hInstance))
	{
		return FALSE;
	}

	/****************************/
	/*	�t�H���g�̍쐬			*/
	/****************************/
	MyCreateFont(TETRIS_FONT, TETRIS_FONT_HIGHT, TETRIS_FONT_STAET_ANGLE);

	/********************************/
	/*	�C���X�^���X�n���h���̎擾	*/
	/********************************/
	SetInstanceHandle(hInstance);

	return TRUE;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		MyRegisterClass				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool						:	�E�B���h�E�̍쐬				*/
/*												���� -> 1,	���s -> 0			*/
/*	[����]		HINSTANCE	hInstance		:	�C���X�^���X�̃n���h��			*/
/*																				*/
/*==============================================================================*/
ATOM CWindowCreator::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW		wcex;														/*	�E�B���h�E�N���X									*/

	/****************************/
	/*	�E�B���h�E�N���X�̐ݒ�	*/
	/****************************/
	wcex.cbSize			= sizeof(wcex);											/*	�\���̂̃T�C�Y										*/
	wcex.style			= CS_HREDRAW| CS_VREDRAW;								/*	�E�B���h�E�T�C�Y�ύX���̍ĕ`��						*/
	wcex.lpfnWndProc	= AppWndProc;											/*	�E�B���h�E�v���V�[�W���̊֐���						*/
	wcex.cbClsExtra		= 0;													/*	�g���N���X�̃�����									*/
	wcex.cbWndExtra		= 0;													/*	�g���E�B���h�E�̃�����								*/
	wcex.hInstance		= hInstance;											/*	�C���X�^���X�ւ̃n���h��							*/
	wcex.hIcon			= NULL;													/*	�E�B���h�E�̃A�C�R��								*/
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);							/*	�E�B���h�E��ɂ���ꍇ�̃J�[�\�� -> ����ݒ�		*/
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);					/*	�w�i�u���V											*/
	wcex.lpszMenuName	= NULL;													/*	���j���[�̃��\�[�X��								*/
	wcex.lpszClassName	= m_Clase_Name;											/*	�E�B���h�E�N���X��									*/
	wcex.hIconSm		= NULL;													/*	�E�B���h�E�̏������A�C�R��							*/
	
	/****************************/
	/*	�E�B���h�E�N���X�̓o�^	*/
	/****************************/
	if (RegisterClassEx(&wcex) == 0)											/*	�E�B���h�E�N���X�̓o�^���G���[�Ȃ��				*/
		return 0;


	return RegisterClassExW(&wcex);

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		MyCreateWindow				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool						:	�E�B���h�E�̍쐬				*/
/*												���� -> 1,	���s -> 0			*/
/*	[����]		HINSTANCE	hInstance		:	�C���X�^���X�̃n���h��			*/
/*																				*/
/*==============================================================================*/
bool CWindowCreator::MyCreateWindow(HINSTANCE hInstance)
{
	/********************************/
	/*	�E�B���h�E�X�^�C���̐ݒ�	*/
	/********************************/
	ULONG_PTR		style = 0;														/*	�E�B���h�E�X�^�C���̐ݒ�							*/

	if (m_IsFullScreen)																/*	�t���X�N���[���̐ݒ�ł����						*/
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPEDWINDOW;
	}

	/********************************/
	/*	�E�B���h�E�̍쐬			*/
	/********************************/
	HWND hwnd = ::CreateWindow(		m_Clase_Name									/*	�E�B���h�E�N���X��									*/
								,	m_Title											/*	�E�B���h�E�^�C�g����								*/
								,	static_cast<DWORD>(style)			 			/*	�E�B���h�E�X�^�C��									*/
								,	CW_USEDEFAULT									/*	�E�B���h�E�̐����ʒu ( �f�t�H���g )					*/
								,	CW_USEDEFAULT									/*	�E�B���h�E�̐����ʒu ( �f�t�H���g )					*/
								,	m_WindowWidth									/*	�E�B���h�E��										*/
								,	m_WindowHeight									/*	�E�B���h�E����										*/
								,	(HWND)NULL										/*	�e�E�B���h�E										*/
								,	(HMENU)NULL										/*	���j���[											*/
								,	hInstance										/*	�C���X�^���X�ւ̃n���h��							*/
								,	(LPVOID)NULL									/*	�E�B���h�E�p�����[�^								*/
								);

	if (!hwnd)																		/*	�E�B���h�E�쐬�����s������Ȃ��					*/
	{
		return FALSE;
	}
	
	/*----------------------------------------------------------------------*/
	/*	�E�B���h�E�̏ꍇ�A�N���C�A���g�̈悪WINDOW_WIDTH �~ WINDOW_HEIGHT	*/
	/*	�ɂȂ�悤�ɃN���C�A���g�̈���Đݒ�								*/
	/*----------------------------------------------------------------------*/
	if ( !m_IsFullScreen )															/*	�t���X�N���[���̐ݒ�łȂ����						*/
	{
		RECT ClientRect;
		GetClientRect(hwnd, &ClientRect);											/*	���݂̃N���C�A���g�̈���擾						*/
		
		/****************************/
		/*	�E�B���h�E�̍Đݒ�		*/
		/****************************/
		MoveWindow(	hwnd															/*	�E�B���h�E�n���h��									*/
				,	ClientRect.left													/*	��													*/
				,	ClientRect.top													/*	��													*/
				,	m_WindowWidth + (m_WindowWidth - ClientRect.right )				/*	�E													*/
				,	m_WindowHeight + (m_WindowHeight - ClientRect.bottom )			/*	��													*/
				,	true															/*	�E�B���h�E�̍ĕ`��ݒ�								*/
			);
	}

	/****************************/
	/*	�E�B���h�E�̕\��		*/
	/****************************/
	ShowWindow(hwnd, SW_SHOW);														/*	�E�B���h�E��\��									*/
	UpdateWindow(hwnd);																/*	�E�C���h�E�v���V�[�W���𒼐ڌĂсAWM_PAINT������	*/

	
	/********************************/
	/*	�E�B���h�E�n���h���̎擾	*/
	/********************************/
	SetWindowHandle(hwnd);

	return TRUE;

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		MyCreateFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool						:	�E�B���h�E�̍쐬				*/
/*												���� -> 1,	���s -> 0			*/
/*	[����]		HINSTANCE	hInstance		:	�C���X�^���X�̃n���h��			*/
/*																				*/
/*==============================================================================*/
void CWindowCreator::MyCreateFont(LPCTSTR font_type, int height, int angle)
{
	m_hFont = CreateFont(	height						/*	�t�H���g����					*/
						,	0							/*	������ ( 0�̏ꍇ�͎������� )	*/
						,	angle						/*	�e�L�X�g�̊p�x					*/
						,	0							/*	�����J�n�ʒu�̐������̊p�x		*/
						,	FW_REGULAR					/*	�t�H���g����					*/
						,	FALSE						/*	�Α� ( �C�^���b�N�� )			*/
						,	FALSE						/*	�A���_�[���C��					*/
						,	FALSE						/*	�ł�������						*/
						,	SHIFTJIS_CHARSET			/*	�����Z�b�g						*/
						,	OUT_DEFAULT_PRECIS			/*	�o�͐��x						*/
						,	CLIP_DEFAULT_PRECIS			/*	�N���b�s���O���x				*/
						,	PROOF_QUALITY				/*	�o�͕i��						*/
						,	FIXED_PITCH | FF_MODERN		/*	�s�b�`�ƃt�H���g�t�@�~��		*/
						,	font_type					/*	���̖�							*/
				); 

	return ;

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
HWND CWindowCreator::GetWindowHandle() const
{
	return m_hWnd;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetWindowFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
HFONT CWindowCreator::GetWindowHFont() const
{
	return m_hFont;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetInstanceHandle			:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CWindowCreator::SetInstanceHandle(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CWindowCreator::SetWindowHandle(HWND hwnd)
{
	m_hWnd = hwnd;
	return;
}