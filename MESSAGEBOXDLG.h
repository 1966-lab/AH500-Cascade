#if !defined(AFX_MESSAGEBOXDLG_H__3AED2E1A_A867_41D8_BAE6_FFE2810B7771__INCLUDED_)
#define AFX_MESSAGEBOXDLG_H__3AED2E1A_A867_41D8_BAE6_FFE2810B7771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MESSAGEBOXDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MESSAGEBOXDLG dialog

class MESSAGEBOXDLG : public CDialog
{
// Construction
public:
	MESSAGEBOXDLG(CWnd* pParent = NULL);   // standard constructor
	CString m_title;
	CString m_content;
	CString m_okcontent;
	CString m_cancontent;
	int     m_okvisable;
	int     m_canvisable;
// Dialog Data
	//{{AFX_DATA(MESSAGEBOXDLG)
	enum { IDD = IDD_MESSAGEBOXDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MESSAGEBOXDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MESSAGEBOXDLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEBOXDLG_H__3AED2E1A_A867_41D8_BAE6_FFE2810B7771__INCLUDED_)
