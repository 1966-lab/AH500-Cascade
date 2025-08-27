#if !defined(AFX_ALARMDLG_H__9374A823_A854_4380_A460_84D4AC3ECD36__INCLUDED_)
#define AFX_ALARMDLG_H__9374A823_A854_4380_A460_84D4AC3ECD36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Alarmdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlarmdlg dialog

class CAlarmdlg : public CDialog
{
// Construction
public:
	CAlarmdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlarmdlg)
	enum { IDD = IDD_ALARMDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlarmdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlarmdlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALARMDLG_H__9374A823_A854_4380_A460_84D4AC3ECD36__INCLUDED_)
