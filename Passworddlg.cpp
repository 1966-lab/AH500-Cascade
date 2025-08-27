// Passworddlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Passworddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassworddlg dialog
extern CMDSApp theApp;

CPassworddlg::CPassworddlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPassworddlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassworddlg)
	m_password = _T("");
	//}}AFX_DATA_INIT
}


void CPassworddlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassworddlg)
	DDX_Control(pDX, IDC_PASSEDIT, m_passedit);
	DDX_Control(pDX, IDOK, m_okbt);
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	DDX_Text(pDX, IDC_PASSEDIT, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassworddlg, CDialog)
	//{{AFX_MSG_MAP(CPassworddlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassworddlg message handlers

void CPassworddlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(m_password.GetLength()==0)
	{
		return;
	}
//	pdoc->convertpassword(m_password);
//	CString p("98239763");
//	pdoc->convertpassword(p);
//	CString tempstr;
//	tempstr.Format("%s",pdoc->m_password);
	if(m_password=="1963")
		CDialog::OnOK();
	else
	{
		if(theApp.m_bLanguage==0)
			MessageBox("√‹¬Î¥ÌŒÛ!",NULL,NULL);
		else if(theApp.m_bLanguage==1)
			MessageBox("Password error!",NULL,NULL);
	}
}

BOOL CPassworddlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
