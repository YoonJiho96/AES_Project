
// AES_Project.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAES_ProjectApp:
// �� Ŭ������ ������ ���ؼ��� AES_Project.cpp�� �����Ͻʽÿ�.
//

class CAES_ProjectApp : public CWinApp
{
public:
	CAES_ProjectApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAES_ProjectApp theApp;