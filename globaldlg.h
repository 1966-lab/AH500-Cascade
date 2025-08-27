#if !defined(AFX_GLOBALDLG_H__14030AD2_B8B0_472C_9F72_B95A1A3EFF74__INCLUDED_)
#define AFX_GLOBALDLG_H__14030AD2_B8B0_472C_9F72_B95A1A3EFF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// globaldlg.h : header file
//

#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// globaldlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class globaldlg : public CFormView
{
public:
	globaldlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(globaldlg)

// Form Data
public:
	//{{AFX_DATA(globaldlg)
	enum { IDD = IDD_GLOBALDLG };
	CXPButton	m_cancelbt;
	CXPButton	m_okbt;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(globaldlg)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~globaldlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(globaldlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Drawview(CDC* pDC); 
	void Drawgroup(int* x, int* y,int airno,CDC* pDC);
	void drawnetview(CBitmap* bmp,int airmac_x, int airmac_y,CDC* pDC);
	HBRUSH m_bkbrush;
	COLORREF m_bkcolor;
	CBitmap m_outdoor;

/*	CBitmap m_MCCSTOP;
	CBitmap m_MCCCOOL;
	CBitmap m_MCCHOT;

	CBitmap m_MCKSTOP;
	CBitmap m_MCKCOOL;
	CBitmap m_MCKHOT;

	CBitmap m_MCMSTOP;
	CBitmap m_MCMCOOL;
	CBitmap m_MCMHOT;

	CBitmap m_MWMSTOP;
	CBitmap m_MWMCOOL;
	CBitmap m_MWMHOT;

	CBitmap m_MDBSTOP;
	CBitmap m_MDBCOOL;
	CBitmap m_MDBHOT;*/

	CBitmap m_inairbmp[5][3];

	int outwidth;
	int outhight;
	int inusedwidth;
	int inusedhight;
	int m_updataflag;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLOBALDLG_H__14030AD2_B8B0_472C_9F72_B95A1A3EFF74__INCLUDED_)
