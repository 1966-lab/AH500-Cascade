// Inputstrdlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Inputstrdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputstrdlg dialog


CInputstrdlg::CInputstrdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputstrdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputstrdlg)
	m_instring = _T("");
	//}}AFX_DATA_INIT
}


void CInputstrdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputstrdlg)
	DDX_Control(pDX, IDOK, m_okbt);
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	DDX_Control(pDX, IDC_INSTRING, m_stringedit);
	DDX_Text(pDX, IDC_INSTRING, m_instring);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputstrdlg, CDialog)
	//{{AFX_MSG_MAP(CInputstrdlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputstrdlg message handlers

BOOL CInputstrdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_stringedit.SetLimitText(16);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
