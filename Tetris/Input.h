
#ifndef _INPUT_H
#define _INPUT_H 

/*------------------*/
/*					*/
/*------------------*/
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC      ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE     ((USHORT) 0x02)
#endif

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include <WindowsX.h>
#include <WinUser.h>
#include <string>

namespace inputNS
{
    const int		KEYS_ARRAY_LEN	= 256;
    const UCHAR		KEYS_DOWN		= 0x01;
    const UCHAR		KEYS_PRESSED	= 0x02;
    const UCHAR		MOUSE			= 0x04;
    const UCHAR		TEXT_IN			= 0x08;
    const UCHAR		KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

const DWORD GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0X7FFF);
const DWORD GAMEPAD_TRIGGER_DEADZONE	= 30;
const DWORD MAX_CONTROLLERS				= 4;
const DWORD GAMEPAD_DPAD_UP				= 0x0001;
const DWORD GAMEPAD_DPAD_DOWN			= 0x0002;
const DWORD GAMEPAD_DPAD_LEFT			= 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT			= 0x0008;
const DWORD GAMEPAD_START_BUTTON		= 0x0010;
const DWORD GAMEPAD_BACK_BUTTON			= 0x0020;
const DWORD GAMEPAD_LEFT_THUMB			= 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB			= 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER		= 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER		= 0x0200;
const DWORD GAMEPAD_A					= 0x1000;
const DWORD GAMEPAD_B					= 0x2000;
const DWORD GAMEPAD_X					= 0x4000;
const DWORD GAMEPAD_Y					= 0x8000;

/*----------------------------------*/
/*	���̓N���X						*/
/*----------------------------------*/
class CInput
{

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
    bool			m_KeysDown[inputNS::KEYS_ARRAY_LEN];      									/*	�w��̃L�[��������Ă�����  ( true : �L��	�@false : ���� )			*/
    bool			m_KeysPressed[inputNS::KEYS_ARRAY_LEN];       								/*	�w��̃L�[�������ꂽ  ( true : �L��	�@false : ���� )					*/
    std::string		m_TextIn;																	/*	���[�U�����͂����������												*/
    char			m_CharIn;																	/*	�Ō�ɓ��͂��ꂽ�������												*/
    bool			m_NewLine;																	/*	�V�����s���J�n���ꂽ�ꍇ ( true : �L���@false : ���� )					*/
	int				m_MouseX;																	/*	�}�E�X�̍��W�ʒu ( �����W )												*/
	int				m_MouseY;																	/*	�}�E�X�̍��W�ʒu ( �c���W )												*/
	int				m_MouseRawX;																/*	�����׃}�E�X�̍��W�ʒu ( �����W )										*/
	int				m_MouseRawY; 																/*	�����׃}�E�X�̍��W�ʒu ( �c���W )										*/
    RAWINPUTDEVICE	m_Rid[1];
    bool			m_MouseCaptured;															/*	�}�E�X���L���v�`������Ă���ꍇ ( true : �L���@false : ���� )			*/
	bool			m_MouseLButton;																/*	�}�E�X�����N���b�N����Ă���ꍇ ( true : �L���@false : ���� )			*/
    bool			m_MouseMButton;																/*	�}�E�X�̒����{�^����������Ă���ꍇ ( true : �L���@false : ���� )		*/
    bool			m_MouseRButton;  															/*	�}�E�X���E�N���b�N����Ă���ꍇ ( true : �L���@false : ���� )			*/
    bool			m_MouseX1Button;  															/*	�}�E�X��X1�{�^����������Ă���ꍇ ( true : �L���@false : ���� )		*/
    bool			m_MouseX2Button;  															/*	�}�E�X��X2�{�^����������Ă���ꍇ ( true : �L���@false : ���� )		*/

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
    CInput();
    
	/*	�f�X�g���N�^	*/
	virtual			~CInput();
	
	/*	�֐�	*/
	
	/*	�������֘A	*/
	void			Initialize(HWND, bool);														/*	���̓N���X�̏���������													*/

	/*	�L�[�֘A	*/
	void			KeyDown(WPARAM);															/*	�L�[�̉�����������														*/
	void			KeyUp(WPARAM);																/*	�L�[�̉����グ����														*/
	bool			isKeyDown(UCHAR vkey) const;												/*	�w�肳�ꂽ�L�[��������Ă��邩�ǂ����m�F ( ���݂̏�� )					*/
	bool			wasKeyPressed(UCHAR vkey) const;											/*	�w�肳�ꂽ�L�[�������ꂽ���ǂ����m�F									*/
	bool			anyKeyPressed() const;														/*	���炩�̃L�[�������ꂽ���ǂ����m�F										*/
	char			GetKeyPressed() const;
	void			ClearKeyPress(UCHAR vkey);

	/*	�����֘A	*/
	void			TextIn(WPARAM);																/*	�������͏���															*/
	std::string		GetTextIn() const;															/*	�������擾 ( Return�R�[�h�������ꂽ )									*/
	char			GetCharIn() const;															/*	�Ō�̕������擾 ( Return�R�[�h�������ꂽ )								*/
	void			ClearTextIn();																/*	�����o�b�t�@�̃N���A													*/

	/*	�}�E�X�֘A	*/
	void			MouseIn(LPARAM);															/*	�}�E�X�̓���															*/
	void			MouseRawIn(LPARAM);															/*	�����׃}�E�X�̓���														*/
	void			SetMouseLButton(bool);														/*	�}�E�X�̍��N���b�N����													*/
	void			SetMouseMButton(bool);														/*	�}�E�X�̒����{�^������													*/
	void			SetMouseRButton(bool);														/*	�}�E�X�̉E�N���b�N����													*/
	void			SetMouseXButton(WPARAM);													/*	�}�E�X��X�{�^������														*/
	int				GetMouseX() const;															/*	�}�E�X�̍��W�ʒu ( �����W )	���擾										*/
	int				GetMouseY() const;															/*	�}�E�X�̍��W�ʒu ( �c���W )	���擾										*/
	int				GetMouseRawX() const;														/*	�����׃}�E�X�̍��W�ʒu ( �����W ) ���擾								*/
	int				GetMouseRawY() const;														/*	�����׃}�E�X�̍��W�ʒu ( �c���W ) ���擾								*/
	bool			GetMouseLButton() const;													/*	�}�E�X�̍��N���b�N�̗L����Ԃ��擾										*/
	bool			GetMouseMButton() const;													/*	�}�E�X�̒����{�^���̗L����Ԃ��擾										*/
	bool			GetMouseRButton() const;													/*	�}�E�X�̉E�N���b�N�̗L����Ԃ��擾										*/
	bool			GetMouseX1Button() const;													/*	�}�E�X��X1�{�^���̗L����Ԃ��擾										*/
	bool			GetMouseX2Button() const;													/*	�}�E�X��X1�{�^���̗L����Ԃ��擾										*/

	/*	�L�[�E�����E�}�E�X�̋��ʊ֘A	*/
	void			Clear(UCHAR);																/*	�w�肳�ꂽ���̓o�b�t�@���N���A											*/
	void			ClearAll();

};

#endif

