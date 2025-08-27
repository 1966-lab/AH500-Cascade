#if !defined(AFX_COLOREDIT_H__E068EE99_CA65_405A_B458_AF965BB5DBCE__INCLUDED_)
#define AFX_COLOREDIT_H__E068EE99_CA65_405A_B458_AF965BB5DBCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorEdit window

class CColorEdit : public CEdit
{
// Construction
public:
	CColorEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	void setbcolor(int c);
	virtual ~CColorEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorEdit)
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int colorflag;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDIT_H__E068EE99_CA65_405A_B458_AF965BB5DBCE__INCLUDED_)
