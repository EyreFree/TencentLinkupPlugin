
// Lianliankan.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLianliankanApp:
// �йش����ʵ�֣������ Lianliankan.cpp
//

class CLianliankanApp : public CWinApp
{
public:
	CLianliankanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLianliankanApp theApp;