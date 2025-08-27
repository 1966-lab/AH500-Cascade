#if !defined(AFX_ADDCONFIG_H__8A2A925D_9FF0_4C5C_A824_79DBEF015A76__INCLUDED_)
#define AFX_ADDCONFIG_H__8A2A925D_9FF0_4C5C_A824_79DBEF015A76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddConfig dialog

class CAddConfig : public CDialog
{
// Construction
public:
	CAddConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddConfig)
	enum { IDD = IDD_ADDCONFIG };
	CString	m_configname;
	CString	m_a;
	CString	m_b;
	CString	m_c;
	CString	m_d;
	CString	m_e;
	CString	m_f;
	CString	m_g;
	CString	m_h;
	CString	m_i;
	CString	m_j;
	CString	m_k;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddConfig)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDCONFIG_H__8A2A925D_9FF0_4C5C_A824_79DBEF015A76__INCLUDED_)
