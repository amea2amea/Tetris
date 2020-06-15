#ifndef _CONTROL_PROCESS_H
#define _CONTROL_PROCESS_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "FrameWork.h"
#include "WindowCreator.h"
#include "input.h"
#include "GameLogic.h"

/*	フレームの更新	*/
namespace FramesRateNS
{
	const float		FRAME_RATE = 30.0f;										/*	フレームレート   ( ターゲット )						*/
	const float		MIN_FRAME_RATE = 10.0f;									/*	フレームレート   ( 最小 )							*/
	const float		MIN_FRAME_TIME = 1.0f / FRAME_RATE;  					/*	フレーム処理時間 ( 最小 )							*/
	const float		MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;  				/*	フレーム処理時間 ( 最大 )							*/
}

/*----------------------------------*/
/*	プロセスのコントロールクラス	*/
/*----------------------------------*/
class CControlProcess : public CFameWork
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CControlProcess();
	CControlProcess(HINSTANCE, LPTSTR);

	/*	デストラクタ	*/
	virtual	~CControlProcess();

	/*	関数	*/
	LRESULT CALLBACK	DispatchEvent(HWND, UINT_PTR, WPARAM, LPARAM);			/*	メッセージ処理	*/
	bool				Create(HINSTANCE);
	bool				Initialize();

protected:
	/*	仮想関数	*/
	virtual void	MessageLoop();
	virtual void	Update();
	virtual bool	FramesTime();

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	ハンドル	*/
	HANDLE			m_hMutex;
	HANDLE			m_hMutexCP;
	
	/*	クラスのポインタ	*/
	CWindowCreator*	m_pWindowCreator;
	CInput*			m_pInput;
	
	/*	時間	*/
	LARGE_INTEGER 	m_TimeStart;											/*	1ループ処理の開始時間											*/
	LARGE_INTEGER 	m_TimeEnd;												/*	1ループ処理の終了時間											*/
	LARGE_INTEGER	m_TimerFreq;											/*	1秒あたりのCPU処理の回数 ( クロック数 : 周波数 )				*/
	double			m_FrameTime;											/*	1ループ処理の処理時間											*/
	double			m_fps;													/*	ゲーム1秒あたりのフレーム数 ( 1秒間に何回メインループを回るか ) */
	DWORD			m_SleepTime;											/*																	*/

};
#endif
