
// TestFrame_Opencv.h : TestFrame_Opencv Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTestFrame_OpencvApp:
// �йش����ʵ�֣������ TestFrame_Opencv.cpp
//

class CTestFrame_OpencvApp : public CWinAppEx
{
public:
	CTestFrame_OpencvApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTestFrame_OpencvApp theApp;
