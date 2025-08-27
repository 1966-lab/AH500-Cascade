// ColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "ColorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorEdit

CColorEdit::CColorEdit()
{
}

CColorEdit::~CColorEdit()
{
}


BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers

void CColorEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//dc.SetBkColor(RGB(255,255,0));
	// Do not call CEdit::OnPaint() for painting messages
}

HBRUSH CColorEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(colorflag==0)
	pDC->SetBkColor(RGB(255,255,0));
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CColorEdit::setbcolor(int c)
{
	colorflag=c;
	Invalidate();
}
