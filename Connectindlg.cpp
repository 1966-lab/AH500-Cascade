// Connectindlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Connectindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectindlg

IMPLEMENT_DYNCREATE(CConnectindlg, CFormView)

CConnectindlg::CConnectindlg()
	: CFormView(CConnectindlg::IDD)
{
	//{{AFX_DATA_INIT(CConnectindlg)
	//}}AFX_DATA_INIT
//	m_bkcolor=RGB(108,121,247);//RGB(160,180,220);
	m_bkcolor=RGB(255,255,200);
	m_bkbrush=CreateSolidBrush(m_bkcolor);//63,186,137));
}

CConnectindlg::~CConnectindlg()
{
}

void CConnectindlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectindlg)
	DDX_Control(pDX, IDOK, m_okbt);
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectindlg, CFormView)
	//{{AFX_MSG_MAP(CConnectindlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectindlg diagnostics

#ifdef _DEBUG
void CConnectindlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CConnectindlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CConnectindlg message handlers

HBRUSH CConnectindlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_DLG) 
 	{
 		return m_bkbrush;
 	}
	if (nCtlColor == CTLCOLOR_STATIC)
 	{
 		pDC->SetBkColor(m_bkcolor);
	//	pDC->SetTextColor(RGB(255,255,0));
 		return m_bkbrush;
 	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
