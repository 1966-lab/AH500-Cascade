#if !defined(AFX_INPUTSTRDLG_H__FDBD5769_2B90_482A_BF0A_7F9D67C4B626__INCLUDED_)
#define AFX_INPUTSTRDLG_H__FDBD5769_2B90_482A_BF0A_7F9D67C4B626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Inputstrdlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CInputstrdlg dialog

class CInputstrdlg : public CDialog
{
// Construction
public:
	CInputstrdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputstrdlg)
	enum { IDD = IDD_INPUTSTRDIG };
	CXPButton	m_okbt;
	CXPButton	m_cancelbt;
	CHoverEdit	m_stringedit;
	CString	m_instring;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputstrdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputstrdlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTSTRDLG_H__FDBD5769_2B90_482A_BF0A_7F9D67C4B626__INCLUDED_)
