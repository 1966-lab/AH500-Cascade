#if !defined(AFX_SPECILCMDDLG_H__340D71AC_A714_40AA_B20E_0ED0D0693281__INCLUDED_)
#define AFX_SPECILCMDDLG_H__340D71AC_A714_40AA_B20E_0ED0D0693281__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Specilcmddlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CSpecilcmddlg dialog

class CSpecilcmddlg : public CDialog
{
// Construction
public:
	int outairNo;
	CSpecilcmddlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpecilcmddlg)
	enum { IDD = IDD_SPECILCMDDLG };
	CXPButton	m_clearbtn;
	CXPButton	m_bt2;
	CXPButton	m_bt1;
	CXPButton	m_maskbt;
	CXPButton	m_cancelbt;
	CXPButton	m_okbt;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecilcmddlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpecilcmddlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnMaskbtn();
	afx_msg void OnClearbtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECILCMDDLG_H__340D71AC_A714_40AA_B20E_0ED0D0693281__INCLUDED_)
