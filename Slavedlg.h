#if !defined(AFX_SLAVEDLG_H__19D9E499_CCF2_4D7B_846B_CF50DD4C1EFF__INCLUDED_)
#define AFX_SLAVEDLG_H__19D9E499_CCF2_4D7B_846B_CF50DD4C1EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Slavedlg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CSlavedlg dialog

class CSlavedlg : public CDialog
{
// Construction
public:
	void showerror(int No);
	int outairNo;
	void showdata(int No);
	CSlavedlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSlavedlg)
	enum { IDD = IDD_SLAVEOUTDLG };
	CXPButton	m_okbt;
	CXPButton	m_modoutbt;
	CListBox	m_alarmlist;
	CHoverEdit	m_elevavle1;
	CHoverEdit	m_comp1; 
	CHoverEdit	m_dnoisedelaytime;
	CHoverEdit	m_dfrosttp;
	CHoverEdit	m_factshot;
	CHoverEdit	m_targetshot;
	CHoverEdit	m_inpan1;
	CHoverEdit	m_outdoortp;
	CHoverEdit	m_hicsupercool;
	CHoverEdit	m_dfroststarttp;
	CHoverEdit	m_lowpre;
	CHoverEdit	m_highpre;
	CHoverEdit	m_ingas;
	CHoverEdit	m_outgas;
	CHoverEdit	m_pwmout;
	CHoverEdit	m_totalneedhp;
	CHoverEdit	m_elevalve0;
	CHoverEdit	m_oilblance;
	CHoverEdit	m_oilre;
	CHoverEdit	m_runmode;
	CHoverEdit	m_hp;
	CHoverEdit	m_airversion;
	CHoverEdit	m_dfrostintertime;
	CHoverEdit	m_dfrostruntime;
	CHoverEdit	m_dfrostendtp;
	CHoverEdit	m_airtype1;
	CHoverEdit	m_midpan3;
	CHoverEdit	m_midpan2;
	CHoverEdit	m_midpan1;
	CHoverEdit	m_outpan3;
	CHoverEdit	m_outpan2;
	CHoverEdit	m_outpan1;
	CHoverEdit	m_inpan3;
	CHoverEdit	m_inpan2;
	CHoverEdit	m_fourvalve4;
	CHoverEdit	m_fourvalve3;
	CHoverEdit	m_fourvalve2;
	CHoverEdit	m_fourvalve1;
	CHoverEdit	m_comp3;
	CHoverEdit	m_comp2;
	CHoverEdit	m_eledisten4;
	CHoverEdit	m_eledisten3;
	CHoverEdit	m_eledisten2;
	CHoverEdit	m_eledisten1;
	CHoverEdit	m_fan3;
	CHoverEdit	m_fan2;
	CHoverEdit	m_fan1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlavedlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSlavedlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnModoutbtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLAVEDLG_H__19D9E499_CCF2_4D7B_846B_CF50DD4C1EFF__INCLUDED_)
