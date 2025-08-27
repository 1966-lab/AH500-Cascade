#if !defined(AFX_COMPDLG_H__82170D71_E541_42DE_B71A_2227FA61B372__INCLUDED_)
#define AFX_COMPDLG_H__82170D71_E541_42DE_B71A_2227FA61B372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// compdlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"
#include "ColorListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// Ccompdlg dialog

class Ccompdlg : public CDialog
{
// Construction
public:
	int outairNo;
	Ccompdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Ccompdlg)
	enum { IDD = IDD_COMPDLG };
	CColorListCtrl	m_complist;
	CXPButton	m_cancelbt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Ccompdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Ccompdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void querycomptime(int No);
	CImageList m_imagelist;
	void refreshdata(int No);
	void setrow(int No);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPDLG_H__82170D71_E541_42DE_B71A_2227FA61B372__INCLUDED_)
