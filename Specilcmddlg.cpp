// Specilcmddlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Specilcmddlg.h"
#include "MDSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecilcmddlg dialog

extern CMDSDoc* pdoc;
CSpecilcmddlg::CSpecilcmddlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecilcmddlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpecilcmddlg)
	//}}AFX_DATA_INIT
	outairNo=0;
}


void CSpecilcmddlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecilcmddlg)
	DDX_Control(pDX, IDC_CLEARBTN, m_clearbtn);
	DDX_Control(pDX, IDC_BUTTON2, m_bt2);
	DDX_Control(pDX, IDC_BUTTON1, m_bt1);
	DDX_Control(pDX, IDC_MASKBTN, m_maskbt);
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	DDX_Control(pDX, IDOK, m_okbt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpecilcmddlg, CDialog)
	//{{AFX_MSG_MAP(CSpecilcmddlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_MASKBTN, OnMaskbtn)
	ON_BN_CLICKED(IDC_CLEARBTN, OnClearbtn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecilcmddlg message handlers

BOOL CSpecilcmddlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString tempstr;
	tempstr.Format("%d#外机,从机数量:%d",outairNo,pdoc->airlist[outairNo].in_num);
	this->SetWindowText(tempstr);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpecilcmddlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox("确实要进行除霜",NULL,MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
		{
			pdoc->queryFunNo1=pdoc->queryFunNo;
			pdoc->queryAirNo1=pdoc->queryAirNo;
			pdoc->sendcmdflag=1;
			pdoc->m_errorcount=0;
			pdoc->queryFunNo=9;
			pdoc->queryAirNo=outairNo;
		}
	}
	
}

void CSpecilcmddlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox("确实要开阀",NULL,MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
		{
			pdoc->queryFunNo1=pdoc->queryFunNo;
			pdoc->queryAirNo1=pdoc->queryAirNo;
			pdoc->sendcmdflag=1;
			pdoc->m_errorcount=0;
			pdoc->queryFunNo=10;
			pdoc->queryAirNo=outairNo;
		}
	}
}

void CSpecilcmddlg::OnMaskbtn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(MessageBox("确定",NULL,MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
		{
			pdoc->queryFunNo1=pdoc->queryFunNo;
			pdoc->queryAirNo1=pdoc->queryAirNo;
			pdoc->sendcmdflag=1;
			pdoc->m_errorcount=0;
			pdoc->queryFunNo=11;
			pdoc->queryAirNo=outairNo;
		}
	}
}

void CSpecilcmddlg::OnClearbtn() 
{
	// TODO: Add your control notification handler code here
	if(MessageBox("确实要清除运行时间",NULL,MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
		{
			pdoc->queryFunNo1=pdoc->queryFunNo;
			pdoc->queryAirNo1=pdoc->queryAirNo;
			pdoc->sendcmdflag=1;
			pdoc->m_errorcount=0;
			pdoc->queryFunNo=14;
			pdoc->queryAirNo=outairNo;
		}
	}
}
