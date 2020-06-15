
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
/* インクルード		*/
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
/*	入力クラス						*/
/*----------------------------------*/
class CInput
{

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
    bool			m_KeysDown[inputNS::KEYS_ARRAY_LEN];      									/*	指定のキーが押されている状態  ( true : 有効	　false : 無効 )			*/
    bool			m_KeysPressed[inputNS::KEYS_ARRAY_LEN];       								/*	指定のキーが押された  ( true : 有効	　false : 無効 )					*/
    std::string		m_TextIn;																	/*	ユーザが入力した文字情報												*/
    char			m_CharIn;																	/*	最後に入力された文字情報												*/
    bool			m_NewLine;																	/*	新しい行が開始された場合 ( true : 有効　false : 無効 )					*/
	int				m_MouseX;																	/*	マウスの座標位置 ( 横座標 )												*/
	int				m_MouseY;																	/*	マウスの座標位置 ( 縦座標 )												*/
	int				m_MouseRawX;																/*	高精細マウスの座標位置 ( 横座標 )										*/
	int				m_MouseRawY; 																/*	高精細マウスの座標位置 ( 縦座標 )										*/
    RAWINPUTDEVICE	m_Rid[1];
    bool			m_MouseCaptured;															/*	マウスがキャプチャされている場合 ( true : 有効　false : 無効 )			*/
	bool			m_MouseLButton;																/*	マウスが左クリックされている場合 ( true : 有効　false : 無効 )			*/
    bool			m_MouseMButton;																/*	マウスの中央ボタンが押されている場合 ( true : 有効　false : 無効 )		*/
    bool			m_MouseRButton;  															/*	マウスが右クリックされている場合 ( true : 有効　false : 無効 )			*/
    bool			m_MouseX1Button;  															/*	マウスのX1ボタンが押されている場合 ( true : 有効　false : 無効 )		*/
    bool			m_MouseX2Button;  															/*	マウスのX2ボタンが押されている場合 ( true : 有効　false : 無効 )		*/

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
    CInput();
    
	/*	デストラクタ	*/
	virtual			~CInput();
	
	/*	関数	*/
	
	/*	初期化関連	*/
	void			Initialize(HWND, bool);														/*	入力クラスの初期化処理													*/

	/*	キー関連	*/
	void			KeyDown(WPARAM);															/*	キーの押し下げ処理														*/
	void			KeyUp(WPARAM);																/*	キーの押し上げ処理														*/
	bool			isKeyDown(UCHAR vkey) const;												/*	指定されたキーが押されているかどうか確認 ( 現在の状態 )					*/
	bool			wasKeyPressed(UCHAR vkey) const;											/*	指定されたキーが押されたかどうか確認									*/
	bool			anyKeyPressed() const;														/*	何らかのキーが押されたかどうか確認										*/
	char			GetKeyPressed() const;
	void			ClearKeyPress(UCHAR vkey);

	/*	文字関連	*/
	void			TextIn(WPARAM);																/*	文字入力処理															*/
	std::string		GetTextIn() const;															/*	文字を取得 ( Returnコードが押された )									*/
	char			GetCharIn() const;															/*	最後の文字を取得 ( Returnコードが押された )								*/
	void			ClearTextIn();																/*	文字バッファのクリア													*/

	/*	マウス関連	*/
	void			MouseIn(LPARAM);															/*	マウスの入力															*/
	void			MouseRawIn(LPARAM);															/*	高精細マウスの入力														*/
	void			SetMouseLButton(bool);														/*	マウスの左クリック入力													*/
	void			SetMouseMButton(bool);														/*	マウスの中央ボタン入力													*/
	void			SetMouseRButton(bool);														/*	マウスの右クリック入力													*/
	void			SetMouseXButton(WPARAM);													/*	マウスのXボタン入力														*/
	int				GetMouseX() const;															/*	マウスの座標位置 ( 横座標 )	を取得										*/
	int				GetMouseY() const;															/*	マウスの座標位置 ( 縦座標 )	を取得										*/
	int				GetMouseRawX() const;														/*	高精細マウスの座標位置 ( 横座標 ) を取得								*/
	int				GetMouseRawY() const;														/*	高精細マウスの座標位置 ( 縦座標 ) を取得								*/
	bool			GetMouseLButton() const;													/*	マウスの左クリックの有効状態を取得										*/
	bool			GetMouseMButton() const;													/*	マウスの中央ボタンの有効状態を取得										*/
	bool			GetMouseRButton() const;													/*	マウスの右クリックの有効状態を取得										*/
	bool			GetMouseX1Button() const;													/*	マウスのX1ボタンの有効状態を取得										*/
	bool			GetMouseX2Button() const;													/*	マウスのX1ボタンの有効状態を取得										*/

	/*	キー・文字・マウスの共通関連	*/
	void			Clear(UCHAR);																/*	指定された入力バッファをクリア											*/
	void			ClearAll();

};

#endif

