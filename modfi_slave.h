#if !defined(AFX_MODFI_SLAVE_H__572413B3_46E3_4262_A6F4_68D95BF891DD__INCLUDED_)
#define AFX_MODFI_SLAVE_H__572413B3_46E3_4262_A6F4_68D95BF891DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// modfi_slave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cmodfi_slave dialog

class Cmodfi_slave : public CDialog
{
// Construction
public:
	Cmodfi_slave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cmodfi_slave)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cmodfi_slave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cmodfi_slave)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODFI_SLAVE_H__572413B3_46E3_4262_A6F4_68D95BF891DD__INCLUDED_)
