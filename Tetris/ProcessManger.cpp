/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "ControlProcess.h"
#include "ProcessManger.h"


/*==============================================================================*/
/*																				*/
/*	[�֐�]		Process			:	�R���X�g���N�^								*/
/*																				*/
/*==============================================================================*/
CProcessManger::CProcessManger()
{
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CProcessManger	:	�f�X�g���N�^								*/
/*																				*/
/*==============================================================================*/
CProcessManger::~CProcessManger()
{
}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		Create			:												*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	ProcessCore*	:												*/
/*	[����]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CFameWork* CProcessManger::Create(HINSTANCE hInstance, LPTSTR lpCmdLine)
{
	CFameWork*			pframewoke		= 0;
	CControlProcess*	pcontrolprocess = 0;
	
	if (!IsAnotherInstance())
	{
		pframewoke = new CControlProcess(hInstance, lpCmdLine);

		if (pframewoke != NULL)
		{
			pcontrolprocess = (CControlProcess*)pframewoke;
			pcontrolprocess->Create(hInstance);
			pcontrolprocess->Initialize();
		}
	}

	return pframewoke;
}

/*==================================================================================*/
/*																					*/
/*	[�֐�]		IsAnotherInstance	:	�E�B���h�E��2�d�N���֎~						*/
/*										( �~���[�e�b�N�X���� )						*/
/*	--------------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	ture  -> �C���X�^���X�����݂��Ă�			*/
/*										false -> �������B��̃C���X�^���X�ł���		*/
/*	[����]		void				:	�Ȃ�										*/
/*																					*/
/*==================================================================================*/
bool CProcessManger::IsAnotherInstance()
{
	HANDLE hMutex;

	hMutex = ::OpenMutex(MUTEX_ALL_ACCESS				/*	�Z�L�����e�B�L�q�q				*/
						, FALSE							/*	�ŏ��̏��L�҂ɂȂ邩�ǂ���		*/
						, _T("MYMUTEX")					/*	�I�u�W�F�N�g��					*/
			);

	/********************************************/
	/*	�C���X�^���X�����݂��Ă��邩�`�F�b�N	*/
	/********************************************/
	if ((hMutex != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
	{
		::CloseHandle(hMutex);
		return true;
	}

	return false;
}

