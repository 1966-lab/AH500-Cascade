#if !defined(AFX_MOD_SLAVE_CFG_H__D7F78608_EFFB_4FF1_82D1_4BA71D31F414__INCLUDED_)
#define AFX_MOD_SLAVE_CFG_H__D7F78608_EFFB_4FF1_82D1_4BA71D31F414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// mod_slave_cfg.h : header file
//
#include "XPButton.h"
#include "HoverEdit.h"
/////////////////////////////////////////////////////////////////////////////
// Cmod_slave_cfg dialog

class Cmod_slave_cfg : public CDialog
{
// Construction
public:
	int slave_air_no;
	void show_data(int out_air, int out_air_s);
	Cmod_slave_cfg(CWnd* pParent = NULL);   // standard constructor
	int outairNo;
// Dialog Data
	//{{AFX_DATA(Cmod_slave_cfg)
	enum { IDD = IDD_SLAVE_CFG };
	CHoverEdit	m_s_valve4;
	CHoverEdit	m_s_valve3;
	CHoverEdit	m_s_valve2;
	CHoverEdit	m_s_valve1;
	CXPButton	m_bt_ok;
	CXPButton	m_bt_cancle;
	CXPButton	m_bt_apply;
	CComboBox	m_slavesel;
	CSpinButtonCtrl	m_spwinant_set;
	CSpinButtonCtrl	m_spsup_set;
	CSpinButtonCtrl	m_spdeftime_set;
	CSpinButtonCtrl	m_spdefint_set;
	CSpinButtonCtrl	m_spdefeixt_set;
	CSpinButtonCtrl	m_spdefb_set;
	CSpinButtonCtrl	m_spdefa_set;
	CSpinButtonCtrl	m_spcoolant_set;
	CHoverEdit	m_edit_obsup;
	CHoverEdit	m_edit_coolant;	
	CHoverEdit	m_edit_coolint;
	CHoverEdit	m_edit_winant;
	CHoverEdit	m_edit_defint;
	CHoverEdit	m_edit_time;
	CHoverEdit	m_edit_defexit;
	CHoverEdit	m_edit_defb;
	CHoverEdit	m_edit_defa;
	int		m_int_defa;
	int		m_int_defb;
	int		m_int_defexit;
	int		m_int_defint;
	int		m_int_deftime;
	int		m_int_winant;
	int		m_int_coolant;
	int		m_int_obsup;
	int		m_s_valve11;
	int		m_s_valve21;
	int		m_s_valve31;
	int		m_s_valve41;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cmod_slave_cfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cmod_slave_cfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeSlaveSel();
	afx_msg void OnSelchangeSlaveSel();
	afx_msg void OnApply();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOD_SLAVE_CFG_H__D7F78608_EFFB_4FF1_82D1_4BA71D31F414__INCLUDED_)
