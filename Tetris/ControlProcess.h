#ifndef _CONTROL_PROCESS_H
#define _CONTROL_PROCESS_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "FrameWork.h"
#include "WindowCreator.h"
#include "input.h"
#include "GameLogic.h"

/*	�t���[���̍X�V	*/
namespace FramesRateNS
{
	const float		FRAME_RATE = 30.0f;										/*	�t���[�����[�g   ( �^�[�Q�b�g )						*/
	const float		MIN_FRAME_RATE = 10.0f;									/*	�t���[�����[�g   ( �ŏ� )							*/
	const float		MIN_FRAME_TIME = 1.0f / FRAME_RATE;  					/*	�t���[���������� ( �ŏ� )							*/
	const float		MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;  				/*	�t���[���������� ( �ő� )							*/
}

/*----------------------------------*/
/*	�v���Z�X�̃R���g���[���N���X	*/
/*----------------------------------*/
class CControlProcess : public CFameWork
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CControlProcess();
	CControlProcess(HINSTANCE, LPTSTR);

	/*	�f�X�g���N�^	*/
	virtual	~CControlProcess();

	/*	�֐�	*/
	LRESULT CALLBACK	DispatchEvent(HWND, UINT_PTR, WPARAM, LPARAM);			/*	���b�Z�[�W����	*/
	bool				Create(HINSTANCE);
	bool				Initialize();

protected:
	/*	���z�֐�	*/
	virtual void	MessageLoop();
	virtual void	Update();
	virtual bool	FramesTime();

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	�n���h��	*/
	HANDLE			m_hMutex;
	HANDLE			m_hMutexCP;
	
	/*	�N���X�̃|�C���^	*/
	CWindowCreator*	m_pWindowCreator;
	CInput*			m_pInput;
	
	/*	����	*/
	LARGE_INTEGER 	m_TimeStart;											/*	1���[�v�����̊J�n����											*/
	LARGE_INTEGER 	m_TimeEnd;												/*	1���[�v�����̏I������											*/
	LARGE_INTEGER	m_TimerFreq;											/*	1�b�������CPU�����̉� ( �N���b�N�� : ���g�� )				*/
	double			m_FrameTime;											/*	1���[�v�����̏�������											*/
	double			m_fps;													/*	�Q�[��1�b������̃t���[���� ( 1�b�Ԃɉ��񃁃C�����[�v����邩 ) */
	DWORD			m_SleepTime;											/*																	*/

};
#endif
