// MDS.h : main header file for the MDS application
//
#define WM_STARTWATCHER WM_USER+2000           //看守进程退出消息；
#if !defined(AFX_MDS_H__0A83143C_FCA5_4D24_94BC_3F6D9C0729D3__INCLUDED_)
#define AFX_MDS_H__0A83143C_FCA5_4D24_94BC_3F6D9C0729D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#define  defEK_AC_MDSVIEW_MESSAGE   (WM_USER+200)
/////////////////////////////////////////////////////////////////////////////
// CMDSApp:
// See MDS.cpp for the implementation of this class
//

class CMDSApp : public CWinApp
{
public:
	CMDSApp();

	_ConnectionPtr m_pConnection;//连接数据库；
//	int  ConnectAccess();
	TCHAR szPath[MAX_PATH];
	BOOL         MYDOGISLIVE;
	BOOL         YourDogIsHere;
	CString      HintStrExit;
		CString      SoftVer;
	int m_bLanguage;
	INT m_bInput;
	int _ReadLangSet(int &uchLanguage);
	int _SaveLangSet(int &uchLanguage);
	int _ReadInputSet(int &uchLanguage);
	int _SaveInputSet(int &uchLanguage);
	void ExcuteSql(_RecordsetPtr &rs,_bstr_t sql);
	_RecordsetPtr  m_pRecordset;
    CString path1;
	bool AreYouHaveTheDog();
	bool QuerySafeNet_EK();
	bool ReleaseSafeNet_EK();
	CWnd *p_MDSView_Message_Wnd;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDSApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMDSApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL UnRegisterOcx(LPCTSTR OcxFileName);
	BOOL RegisterOcx(LPCTSTR OcxFileName);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDS_H__0A83143C_FCA5_4D24_94BC_3F6D9C0729D3__INCLUDED_)
