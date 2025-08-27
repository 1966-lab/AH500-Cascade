#if !defined(AFX_COLORSTATIC_H__B4019142_1A3D_4A27_A46F_E554724BA118__INCLUDED_)
#define AFX_COLORSTATIC_H__B4019142_1A3D_4A27_A46F_E554724BA118__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Colorstatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorstatic window

class CColorstatic : public CStatic
{
// Construction
public:
	CColorstatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorstatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void setcolortype(int type);
	virtual ~CColorstatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorstatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_type;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__B4019142_1A3D_4A27_A46F_E554724BA118__INCLUDED_)
