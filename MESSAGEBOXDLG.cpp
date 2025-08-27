// MESSAGEBOXDLG.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "MESSAGEBOXDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MESSAGEBOXDLG dialog


MESSAGEBOXDLG::MESSAGEBOXDLG(CWnd* pParent /*=NULL*/)
	: CDialog(MESSAGEBOXDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(MESSAGEBOXDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MESSAGEBOXDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MESSAGEBOXDLG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MESSAGEBOXDLG, CDialog)
	//{{AFX_MSG_MAP(MESSAGEBOXDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MESSAGEBOXDLG message handlers

BOOL MESSAGEBOXDLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_title);
	
	if(m_okvisable)
		GetDlgItem(IDOK)->SetWindowText(m_okcontent);
	else
		GetDlgItem(IDOK)->ShowWindow(SW_HIDE);

	if(m_canvisable)
		GetDlgItem(IDCANCEL)->SetWindowText(m_cancontent);
	else
		GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_COMBOX_DLG)->SetWindowText(m_content);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
