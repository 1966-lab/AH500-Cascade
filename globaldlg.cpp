// globaldlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "MDSDoc.h"
#include "MainFrm.h"
#include "globaldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// globaldlg
extern CMDSDoc* pdoc;

IMPLEMENT_DYNCREATE(globaldlg, CFormView)

globaldlg::globaldlg()
	: CFormView(globaldlg::IDD)
{
	//{{AFX_DATA_INIT(globaldlg)
	//}}AFX_DATA_INIT
	m_bkcolor=RGB(255,255,255);//RGB(108,121,247);//RGB(160,180,220);
	m_bkbrush=CreateSolidBrush(m_bkcolor);//63,186,137));
}

globaldlg::~globaldlg()
{
}

void globaldlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(globaldlg)
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	DDX_Control(pDX, IDOK, m_okbt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(globaldlg, CFormView)
	//{{AFX_MSG_MAP(globaldlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// globaldlg diagnostics

#ifdef _DEBUG
void globaldlg::AssertValid() const
{
	CFormView::AssertValid();
}

void globaldlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// globaldlg message handlers

HBRUSH globaldlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_DLG) 
 	{
 		return m_bkbrush;
 	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void globaldlg::OnOK() 
{
	// TODO: Add your control notification handler code here
	
}

void globaldlg::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
;
}

void globaldlg::drawnetview(CBitmap* bmp, int airmac_x, int airmac_y, CDC* pDC)
{
;
}

void globaldlg::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class

	;
}

void globaldlg::Drawgroup(int* x, int* y,int airno,CDC* pDC) 
{
;
}

void globaldlg::Drawview(CDC* pDC) 
{
	int x,y,x1,y1;//
	x=30;
	y=50;
	x1=15;
	y1=10;

	for(int i=0;i<pdoc->airnum;i++)
	{
		pDC->MoveTo(x1,y1-5);
		pDC->LineTo(x1,y-5);
		pDC->LineTo(x+outwidth/2,y-5);
		pDC->LineTo(x+outwidth/2,y);
		y1=y;
		Drawgroup(&x,&y,i,pDC);
	}
	SetScrollSizes(MM_TEXT, CSize(0,y));
}

