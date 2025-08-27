#if !defined(AFX_JUDGEDLG_H__DB707376_470D_4ACA_9CD4_4C3B2FDE5B34__INCLUDED_)
#define AFX_JUDGEDLG_H__DB707376_470D_4ACA_9CD4_4C3B2FDE5B34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Judgedlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJudgedlg dialog

class CJudgedlg : public CDialog
{
// Construction
public:
	CJudgedlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJudgedlg)
	enum { IDD = IDD_JUDGEDIG };
	CEdit	m_data4;
	CButton	m_selchk2;
	CEdit	m_capdata2;
	CButton	m_selchk1;
	CEdit	m_capdata1;
	CButton	m_testbt;
	CButton	m_stoptestbt;
	CEdit	m_data3;
	CEdit	m_data1;
	CString	m_capstring;
	CString	m_capstring2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJudgedlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CJudgedlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStart();
	afx_msg void OnClearbtn();
	afx_msg void OnClearbtn1();
	afx_msg void OnSelchk();
	afx_msg void OnSelchk2();
	afx_msg void OnClearbtn4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void do_code_data(CByteArray* inbyte);
	void show_error_data(CByteArray* inbyte);
	void getcmpdata(CByteArray* inbyte,CString str,int* flag);
	void chk1show();
	void chk2show();
	CByteArray Inputdata;
	CByteArray cfdata;
	CByteArray cfdata1;
	int m_tempbytecount;
	int m_readlenght;
	int queryopen;
	CString showstr;
	CString errorstr;
	CString cmpstr;
	CString showreslutstr;
	
	int selflag[6];
	int showcount;
	int starflag[6][20];//标记为*的字节
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUDGEDLG_H__DB707376_470D_4ACA_9CD4_4C3B2FDE5B34__INCLUDED_)
