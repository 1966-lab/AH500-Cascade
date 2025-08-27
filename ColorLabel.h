#if !defined(AFX_COLORLABEL_H__9108820F_E3DF_4038_A36A_25DB1B3421BB__INCLUDED_)
#define AFX_COLORLABEL_H__9108820F_E3DF_4038_A36A_25DB1B3421BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorLabel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorLabel window

class CColorLabel : public CStatic
{
// Construction
public:
	CColorLabel();
	int colorIndex;
	int Value;
	int fontH;
	int fontW;
	int ColorR;
	int ColorG;
	int ColorB;
	CString Caption;
	void SetFontSize(int h,int w);
	void SetFontColor(int r,int g,int b);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorLabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorLabel)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLABEL_H__9108820F_E3DF_4038_A36A_25DB1B3421BB__INCLUDED_)
