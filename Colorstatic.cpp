// Colorstatic.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Colorstatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CColorstatic

CColorstatic::CColorstatic()
{

}

CColorstatic::~CColorstatic()
{

}


BEGIN_MESSAGE_MAP(CColorstatic, CStatic)
	//{{AFX_MSG_MAP(CColorstatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorstatic message handlers
void CColorstatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rcClient;
	GetClientRect(&rcClient);

	CBrush Brush;
	switch(m_type)//0--停止 1--运行 2--报警  3--禁用  4---离线
	{
		
	case 0:
		Brush.CreateSolidBrush(RGB(0,0,0));
		break;
	case 1:
		Brush.CreateSolidBrush(RGB(0,255,0));
		break;
	case 2:
		Brush.CreateSolidBrush(RGB(255,255,0));
		break;
	case 3:
		Brush.CreateSolidBrush(RGB(0,0,0));
		break;
	case 4:
		Brush.CreateSolidBrush(RGB(0,0,0));
		break;
	}
	dc.SelectObject(&Brush);
	dc.Rectangle(rcClient);
//	dc.SetBkColor(RGB(0,255,0));
//	SetWindowText("开");
	// Do not call CStatic::OnPaint() for painting messages
}

void CColorstatic::setcolortype(int type)
{
	m_type=type;
	Invalidate();
}
