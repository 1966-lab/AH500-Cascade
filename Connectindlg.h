#if !defined(AFX_CONNECTINDLG_H__276E01F8_690D_4585_914B_4436839EA863__INCLUDED_)
#define AFX_CONNECTINDLG_H__276E01F8_690D_4585_914B_4436839EA863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Connectindlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CConnectindlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
class CConnectindlg : public CFormView
{
public:
	CConnectindlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CConnectindlg)

// Form Data
public:
	//{{AFX_DATA(CConnectindlg)
	enum { IDD = IDD_CONNECTINDOORDLG };
	CXPButton	m_okbt;
	CXPButton	m_cancelbt;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectindlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CConnectindlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CConnectindlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	HBRUSH m_bkbrush;
	COLORREF m_bkcolor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTINDLG_H__276E01F8_690D_4585_914B_4436839EA863__INCLUDED_)
