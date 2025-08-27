#if !defined(AFX_PASSWORDDLG_H__E4E53EE5_DF75_426D_8EEA_BBCD877168BD__INCLUDED_)
#define AFX_PASSWORDDLG_H__E4E53EE5_DF75_426D_8EEA_BBCD877168BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Passworddlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CPassworddlg dialog

class CPassworddlg : public CDialog
{
// Construction
public:
	CPassworddlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassworddlg)
	enum { IDD = IDD_PASSWORD };
	CHoverEdit	m_passedit;
	CXPButton	m_okbt;
	CXPButton	m_cancelbt;
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassworddlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPassworddlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDDLG_H__E4E53EE5_DF75_426D_8EEA_BBCD877168BD__INCLUDED_)
