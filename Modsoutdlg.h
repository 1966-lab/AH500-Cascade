#if !defined(AFX_MODSOUTDLG_H__9AF19013_88E5_4F37_96E9_E3D0053334F4__INCLUDED_)
#define AFX_MODSOUTDLG_H__9AF19013_88E5_4F37_96E9_E3D0053334F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modsoutdlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CModsoutdlg dialog

class CModsoutdlg : public CDialog
{
// Construction
public:
	void showdata();
	int outairNo;
	CModsoutdlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CModsoutdlg)
	enum { IDD = IDD_MODSOUTDIG };
	CXPButton	m_okbt;
	CXPButton	m_cancelbt;
	CXPButton	m_applybt;
	CHoverEdit	m_p8;
	CHoverEdit	m_p7;
	CHoverEdit	m_p6;
	CHoverEdit	m_p5;
	CHoverEdit	m_p4;
	CHoverEdit	m_p3;
	CHoverEdit	m_p2;
	CHoverEdit	m_p1;
	CSpinButtonCtrl	m_spin13;
	CSpinButtonCtrl	m_spin12;
	CSpinButtonCtrl	m_spin11;
	CSpinButtonCtrl	m_spin10;
	CSpinButtonCtrl	m_spin9;
	CSpinButtonCtrl	m_spin8;
	CHoverEdit	m_targetshot;
	CHoverEdit	m_movefac2;
	CHoverEdit	m_movefac1;
	CSpinButtonCtrl	m_spin6;
	CSpinButtonCtrl	m_spin5;
	CSpinButtonCtrl	m_spin4;
	CSpinButtonCtrl	m_spin3;
	CSpinButtonCtrl	m_spin2;
	CSpinButtonCtrl	m_spin1;
	CHoverEdit	m_vavle4;
	CHoverEdit	m_vavle3;
	CHoverEdit	m_vavle2;
	CHoverEdit	m_vavle1;
	CHoverEdit	m_defroendtp;
	CHoverEdit	m_defrointertime;
	CHoverEdit	m_defroruntime;
	CHoverEdit	m_denoisedelaytime;
	CHoverEdit	m_defrosettp;
	CHoverEdit	m_defrochecktp;
	int		m_defrochecktp1;
	int		m_defroendtp1;
	int		m_defrosettp1;
	int		m_defrointertime1;
	int		m_defroruntime1;
	int		m_denoisedelaytime1;
	int		m_vavle11;
	int		m_vavle21;
	int		m_vavle31;
	int		m_vavle41;
	float	m_movefac11;
	float	m_movefac21;
	float	m_targetshot1;
	int		m_p81;
	int		m_p71;
	int		m_p61;
	int		m_p51;
	int		m_p41;
	int		m_p31;
	int		m_p21;
	int		m_p11;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModsoutdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModsoutdlg)
	afx_msg void OnApply();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODSOUTDLG_H__9AF19013_88E5_4F37_96E9_E3D0053334F4__INCLUDED_)
