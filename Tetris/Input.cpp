/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "input.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CInput			:	�R���X�g���N�^								*/
/*																				*/
/*==============================================================================*/
CInput::CInput()
{
	/********************************/
	/*	������ ( �L�[��� )			*/
	/********************************/
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		m_KeysDown[i] = false;
	}

	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		m_KeysPressed[i] = false;
	}

	/********************************/
	/*	������	( ������� )		*/
	/********************************/
	m_NewLine = true;
	m_TextIn = "";
	m_CharIn = 0;

	/********************************/
	/*	������	( �}�E�X��� )		*/
	/********************************/
    m_MouseX		= 0;
	m_MouseY		= 0;
	m_MouseRawX		= 0;
	m_MouseRawY		= 0;
	m_MouseLButton	= false;
	m_MouseMButton	= false;
	m_MouseRButton	= false;
	m_MouseX1Button = false;
	m_MouseX2Button = false;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~Input			:	�f�X�g���N�^								*/
/*																				*/
/*==============================================================================*/
CInput::~CInput()
{
	if (m_MouseCaptured)				/*	�}�E�X���L���v�`������Ă���Ȃ��		*/
	{
		ReleaseCapture();				/*	�L���v�`���[���̃��\�[�X�����		*/
	}
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Initialize		:	������										*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]					:	�Ȃ�										*/
/*	[����]		HWND			:	�E�B���h�E�n���h��							*/
/*				bool			:	�}�E�X���L���v�`������Ă��邩�ǂ���		*/
/*									( true : �L���@false : ���� )				*/
/*																				*/
/*==============================================================================*/
void CInput::Initialize(HWND hwnd, bool capture)
{
  
	/********************************/
	/*	�����ݒ�					*/
	/********************************/
	m_MouseCaptured = capture;

	/********************************************************************/
	/*	�����̃}�E�X��L�[�{�[�h�̏������o							*/
	/*	 ( �����׃}�E�X�p�̓ǂݎ��BWM_MOUSEMOVE�ł͎擾�ł��Ȃ��̂�	*/
	/*		WM_INPUT�ɗ���悤��RegisterRawInputDevices�Őݒ肵�Ă��� )	*/
	/*		�� �W���}�E�X -> 400dpi										*/
	/*		�� �W���}�E�X -> 800dpi�ȏ�									*/
	/********************************************************************/
	m_Rid[0].usUsagePage	= HID_USAGE_PAGE_GENERIC; 
	m_Rid[0].usUsage		= HID_USAGE_GENERIC_MOUSE;
	m_Rid[0].dwFlags		= RIDEV_INPUTSINK;
	m_Rid[0].hwndTarget		= hwnd;
    RegisterRawInputDevices(m_Rid, 1, sizeof(m_Rid[0]));

	/********************************/
	/*	�}�E�X�L���v�`���[����		*/
	/********************************/
	if (m_MouseCaptured)
	{
		SetCapture(hwnd);
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		KeyDown			:	�L�[�̉�����������							*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		WPARAM			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::KeyDown(WPARAM wParam)
{
	/********************************/
	/*	�L�[�R�[�h����				*/
	/********************************/
    if (wParam < inputNS::KEYS_ARRAY_LEN)
    {
        m_KeysDown[wParam]		= true;					/*	�w��̃L�[��������Ă����� �@( ���݂̏�� ) 			*/
        m_KeysPressed[wParam]	= true;					/*	�w��̃L�[�������ꂽ  									*/
    }

	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		KeyUp			:	�L�[�̉����グ����							*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		WPARAM			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::KeyUp(WPARAM wParam)
{
	/********************************/
	/*	�L�[�R�[�h����				*/
	/********************************/
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		m_KeysDown[wParam] = false;						/*	�w��̃L�[��������Ă��Ȃ���� �@( ���݂̏�� ) 			*/
	}

	return;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		isKeyDown		:	�w�肳�ꂽ�L�[��������Ă��邩�ǂ����m�F	*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	���z�L�[��������Ă��邩�ǂ���				*/
/*									�@( true : �L���@false : ���� )				*/
/*	[����]		UCHAR			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::isKeyDown(UCHAR vkey) const
{

	if (vkey < inputNS::KEYS_ARRAY_LEN)
	{
		return m_KeysDown[vkey];
	}
	else
	{
		return false;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		wasKeyPressed	:	�w�肳�ꂽ�L�[�������ꂽ���ǂ����m�F		*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	���z�L�[�������ꂽ���ǂ���					*/
/*									�@( true : ���z�L�[�R�[�h�@false : ���� ) 	*/
/*	[����]		UCHAR			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::wasKeyPressed(UCHAR vkey) const
{

	if (vkey < inputNS::KEYS_ARRAY_LEN)
	{
		return m_KeysPressed[vkey];
	}
	else
	{
		return false;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		wasKeyPressed	:	���炩�̃L�[�������ꂽ���ǂ����m�F			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	���z�L�[�����������ꂽ���ǂ���				*/
/*									�@( true : �L���@false : ���� )				*/
/*	[����]		UCHAR			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		if (m_KeysPressed[i] == true)
			return true;
	}


    return false;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetKeyPressed	:	���݉����ꂽ���z�L�[���擾					*/
/*									( �����̃L�[�̏ꍇ�A�Ⴂ���z�R�[�h )		*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	���z�L�[									*/
/*									�@( 0 ~ 255�̉��z�L�[�R�[�h )				*/
/*	[����]		void			:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
char CInput::GetKeyPressed() const
{
	for (int i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		if (m_KeysPressed[i] == true)
			return static_cast<char>(i);
	}

	return false;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		ClearKeyPress	:	�w�肳�ꂽ�L�[�̉�������������				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		UCHAR			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::ClearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
	{
		m_KeysPressed[vkey] = false;
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		TextIn			:	�������͏���								*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		WPARAM			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::TextIn(WPARAM wParam)
{
	if (m_NewLine)											/*	�V�����s��I�������Ȃ��							*/
	{
		m_TextIn.clear();									/*	�L�[�����N���A									*/
		m_NewLine = false;									/*	�V�����s�̑I�����I�t								*/
	}

	if (wParam == '\b')										/*	�o�b�N�X�y�[�X�Ȃ��								*/
	{
		if (m_TextIn.length() > 0)							/*	�������ݒ�ς݂Ȃ��								*/
		{
			m_TextIn.erase(m_TextIn.size() - 1);			/*	�Ō�̕���������									*/
		}
	}
	else													/*	�o�b�N�X�y�[�X�ȊO�Ȃ��							*/
	{
		m_TextIn += static_cast<char>(wParam);				/*	������ǉ����Ă���									*/
		m_CharIn = static_cast<char>(wParam);				/*	�Ō�̕����ɐݒ�									*/
	}

	if ((char)wParam == '\r')								/*	���s�R�[�h���ݒ肳�ꂽ�� ( �L�����b�W���^�[�� )		*/
	{
		m_NewLine = true;									 /*	�V�����s��I��										*/
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetTextIn		:	�������擾 ( Return�R�[�h�������ꂽ )		*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
std::string CInput::GetTextIn() const
{
	return m_TextIn;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetTextIn		:	�Ō�̕������擾 ( Return�R�[�h�������ꂽ )	*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
char CInput::GetCharIn() const
{
	return m_CharIn;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		ClearTextIn		:	�����o�b�t�@�̃N���A						*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::ClearTextIn()
{
	m_TextIn.clear();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Clear			:	�w�肳�ꂽ���̓o�b�t�@���N���A				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		UCHAR			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::Clear(UCHAR what)
{
	/****************************/
	/*	�L�[�̉�������			*/
	/****************************/
	if(what & inputNS::KEYS_DOWN)
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            m_KeysDown[i] = false;
    }

	/****************************/
	/*	�L�[�̉����グ			*/
	/****************************/
    if(what & inputNS::KEYS_PRESSED)
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            m_KeysPressed[i] = false;
    }

	/****************************/
	/*	�}�E�X					*/
	/****************************/
    if(what & inputNS::MOUSE)
    {
        m_MouseX	= 0;
        m_MouseY	= 0;
        m_MouseRawX = 0;
        m_MouseRawY = 0;
    }

	/****************************/
	/*	���������͂��ꂽ		*/
	/****************************/
	if (what & inputNS::TEXT_IN)
	{
		ClearTextIn();
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		ClearAll		:												*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::ClearAll()
{
	Clear(inputNS::KEYS_MOUSE_TEXT);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MouseIn			:	�}�E�X���͏���								*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		WPARAM			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::MouseIn(LPARAM lParam)
{
    m_MouseX = GET_X_LPARAM(lParam); 
    m_MouseY = GET_Y_LPARAM(lParam);
	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MouseIn			:	�����׃}�E�X���͏���						*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		WPARAM			:	���z�L�[�R�[�h( 0 �` 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::MouseRawIn(LPARAM lParam)
{
    UINT dwSize = 40;
    static BYTE lpb[40];
    
	/****************************/
	/*	�����׃}�E�X�̓ǂݎ��	*/
	/****************************/
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
                    lpb, &dwSize, sizeof(RAWINPUTHEADER));
    
    RAWINPUT* raw = (RAWINPUT*)lpb;
    
    if (raw->header.dwType == RIM_TYPEMOUSE)			/*	�}�E�X������͂��ꂽ						*/
    {
        m_MouseRawX = raw->data.mouse.lLastX;
        m_MouseRawY = raw->data.mouse.lLastY;
    } 

	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetMouseLButton	:	�}�E�X�̍��N���b�N����						*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		bool			:	���N���b�N�̏��							*/
/*									( true : ����@false : �Ȃ� )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseLButton(bool LButtonOn)
{
	m_MouseLButton = LButtonOn;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetMouseMButton	:	�}�E�X�̒����{�^������						*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		bool			:	�����{�^���̏��							*/
/*									( true : ����@false : �Ȃ� )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseMButton(bool MButtoOn)
{
	m_MouseMButton = MButtoOn;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetMouseLButton	:	�}�E�X�̉E�N���b�N����						*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		bool			:	�E�N���b�N�̏��							*/
/*									( true : ����@false : �Ȃ� )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseRButton(bool RButtonOn)
{
	m_MouseRButton = RButtonOn;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetMouseXButton	:	�}�E�X��X�{�^������							*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	�Ȃ�										*/
/*	[����]		bool			:	X�{�^���̏��								*/
/*									( true : ����@false : �Ȃ� )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseXButton(WPARAM wParam)
{
	m_MouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
	m_MouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseX		:	�}�E�X�̍��W�ʒu ( �����W )	���擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	int 			:	���W�ʒu ( �����W )							*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseX() const
{
	return m_MouseX;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GettMouseY		:	�}�E�X�̍��W�ʒu ( �c���W )	���擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	int 			:	���W�ʒu ( �c���W )							*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseY() const
{
	return m_MouseY;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseRawX	:	�����׃}�E�X�̍��W�ʒu ( �����W ) ���擾	*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	int 			:	���W�ʒu ( �����W )							*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseRawX() const
{
	return m_MouseRawX;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseRawY	:	�����׃}�E�X�̍��W�ʒu ( �c���W ) ���擾	*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void 			:	���W�ʒu ( �c���W )							*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseRawY() const
{
	return m_MouseRawY;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseLButton	:	�}�E�X�̍��N���b�N�̗L����Ԃ��擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	���N���b�N�̏��							*/
/*									( true : ����@false : �Ȃ� )				*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseLButton() const 
{ 
	return m_MouseLButton; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseLButton	:	�}�E�X�̒����{�^���̗L����Ԃ��擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	�����{�^���̏��							*/
/*									( true : �L���@false : ���� )				*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseMButton() const
{ 
	return m_MouseMButton; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseLButton	:	�}�E�X�̉E�N���b�N�̗L����Ԃ��擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	�E�N���b�N�̏��							*/
/*									( true : ����@false : �Ȃ� )				*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseRButton() const
{ 
	return m_MouseRButton; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseLButton	:	�}�E�X��X1�{�^���̗L����Ԃ��擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	X1�{�^���̏��								*/
/*									( true : �L���@false : ���� )				*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseX1Button() const
{ 
	return m_MouseX1Button; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetMouseLButton	:	�}�E�X��X1�{�^���̗L����Ԃ��擾			*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool 			:	X1�{�^���̏��								*/
/*									( true : �L���@false : ���� )				*/
/*	[����]						:	�Ȃ�										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseX2Button() const
{ 
	return m_MouseX2Button; 
}