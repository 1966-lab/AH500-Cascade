
#include "XPButton.h"
#include "HoverEdit.h"

#if !defined(AFX_TESTCODEDLG_H__D3EB88DD_3143_4F2C_A3A9_CCC6952844D4__INCLUDED_)
#define AFX_TESTCODEDLG_H__D3EB88DD_3143_4F2C_A3A9_CCC6952844D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Testcodedlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CTestcodedlg dialog

class CTestcodedlg : public CDialog
{
// Construction
public:
	void set_show();
	CTestcodedlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestcodedlg)
	enum { IDD = IDD_TESTCODEDLG };
	CXPButton	m_cancelbt;
	CHoverEdit	m_th5;
	CHoverEdit	m_th4;
	CHoverEdit	m_th3;
	CHoverEdit	m_th2;
	CHoverEdit	m_th1;
	CStatic	m_datastatic;
	CXPButton	m_testbt;
	CXPButton	m_stoptestbt;
	CXPButton	m_testokbt;
	//}}AFX_DATA
	CStatic	m_feedback[8];
	CStatic	m_code0[8];
	CStatic	m_code1[8];
	CStatic	m_code2[8];
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestcodedlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestcodedlg)
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnStoptestbt();
	afx_msg void OnTestbt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void do_code_data(CByteArray* inbyte);
	CByteArray Inputdata;
	CByteArray cfdata;
	int m_tempbytecount;
	int m_readlenght;
	int queryopen;
	CBitmap codeonbmp;
	CBitmap codeoffbmp;
	CBitmap fbackonbmp;
	CBitmap fbackoffbmp;

	HBITMAP hcodeonbmp;
	HBITMAP hcodeoffbmp;
	HBITMAP hfbackonbmp;
	HBITMAP hfbackoffbmp;

	CString showstr;
	int showcount;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCODEDLG_H__D3EB88DD_3143_4F2C_A3A9_CCC6952844D4__INCLUDED_)
