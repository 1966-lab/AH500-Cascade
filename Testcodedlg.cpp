// Testcodedlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Testcodedlg.h"
#include "MDSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestcodedlg dialog

extern CMDSDoc* pdoc;
extern  CMSComm	m_comm1;
CTestcodedlg::CTestcodedlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestcodedlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestcodedlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestcodedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestcodedlg)
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	DDX_Control(pDX, IDC_TH5, m_th5);
	DDX_Control(pDX, IDC_TH4, m_th4);
	DDX_Control(pDX, IDC_TH3, m_th3);
	DDX_Control(pDX, IDC_TH2, m_th2);
	DDX_Control(pDX, IDC_TH1, m_th1);
	DDX_Control(pDX, IDC_DATASTATIC, m_datastatic);
	DDX_Control(pDX, IDC_TESTBT, m_testbt);
	DDX_Control(pDX, IDC_STOPTESTBT, m_stoptestbt);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CODE00, m_code0[0]);
	DDX_Control(pDX, IDC_CODE01, m_code0[1]);
	DDX_Control(pDX, IDC_CODE02, m_code0[2]);
	DDX_Control(pDX, IDC_CODE03, m_code0[3]);
	DDX_Control(pDX, IDC_CODE04, m_code0[4]);
	DDX_Control(pDX, IDC_CODE05, m_code0[5]);
	DDX_Control(pDX, IDC_CODE06, m_code0[6]);
	DDX_Control(pDX, IDC_CODE07, m_code0[7]);

	DDX_Control(pDX, IDC_CODE10, m_code1[0]);
	DDX_Control(pDX, IDC_CODE11, m_code1[1]);
	DDX_Control(pDX, IDC_CODE12, m_code1[2]);
	DDX_Control(pDX, IDC_CODE13, m_code1[3]);
	DDX_Control(pDX, IDC_CODE14, m_code1[4]);
	DDX_Control(pDX, IDC_CODE15, m_code1[5]);
	DDX_Control(pDX, IDC_CODE16, m_code1[6]);
	DDX_Control(pDX, IDC_CODE17, m_code1[7]);

	DDX_Control(pDX, IDC_CODE20, m_code2[0]);
	DDX_Control(pDX, IDC_CODE21, m_code2[1]);
	DDX_Control(pDX, IDC_CODE22, m_code2[2]);
	DDX_Control(pDX, IDC_CODE23, m_code2[3]);
	DDX_Control(pDX, IDC_CODE24, m_code2[4]);
	DDX_Control(pDX, IDC_CODE25, m_code2[5]);
	DDX_Control(pDX, IDC_CODE26, m_code2[6]);
	DDX_Control(pDX, IDC_CODE27, m_code2[7]);

	DDX_Control(pDX, IDC_FEEDBACK0, m_feedback[0]);
	DDX_Control(pDX, IDC_FEEDBACK1, m_feedback[1]);
	DDX_Control(pDX, IDC_FEEDBACK2, m_feedback[2]);
	DDX_Control(pDX, IDC_FEEDBACK3, m_feedback[3]);
	DDX_Control(pDX, IDC_FEEDBACK4, m_feedback[4]);
	DDX_Control(pDX, IDC_FEEDBACK5, m_feedback[5]);
	DDX_Control(pDX, IDC_FEEDBACK6, m_feedback[6]);
	DDX_Control(pDX, IDC_FEEDBACK7, m_feedback[7]);


}


BEGIN_MESSAGE_MAP(CTestcodedlg, CDialog)
	//{{AFX_MSG_MAP(CTestcodedlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOPTESTBT, OnStoptestbt)
	ON_BN_CLICKED(IDC_TESTBT, OnTestbt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestcodedlg message handlers

void CTestcodedlg::OnTestbt() 
{
	// TODO: Add your control notification handler code here
	if(m_comm1.GetPortOpen())
		return;
	pdoc->set_comm();
	SetTimer(4,25,NULL);
	m_testbt.EnableWindow(FALSE);
	m_stoptestbt.EnableWindow(TRUE);
}
void CTestcodedlg::OnStoptestbt() 
{
	// TODO: Add your control notification handler code here
	if(m_comm1.GetPortOpen())
		m_comm1.SetPortOpen(0);
	KillTimer(4);
	m_testbt.EnableWindow(TRUE);
	m_stoptestbt.EnableWindow(FALSE);

}

void CTestcodedlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_comm1.GetPortOpen())
		m_comm1.SetPortOpen(0);
	KillTimer(4);
	CDialog::OnCancel();
}

void CTestcodedlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==4)
	{
		CString str;
		if(queryopen==1)//发送
		{
			pdoc->query_code_set();
			showstr.Empty();
			queryopen=0;
		}
		else//响应
		{
			int reply=0;		//功能代码
			if(m_readlenght==0)//第一次读串口长度
			{
				m_tempbytecount=m_comm1.GetInBufferCount();
				m_readlenght=1;
				return;
			}
			else
			{
				if(m_tempbytecount!=m_comm1.GetInBufferCount())
				{
					m_tempbytecount=m_comm1.GetInBufferCount();
					return;
				}
				else
				{
					reply=pdoc->getcommdata(&Inputdata);//从串口得到数据，为0表示得到数据不正确
					m_tempbytecount=0;
					m_readlenght=0;
				}
			}		
			if(reply==0x20)
			{
				do_code_data(&Inputdata);
			}
			else
			{
				m_datastatic.SetWindowText(showstr);
			}
			queryopen=1;
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CTestcodedlg::do_code_data(CByteArray* inbyte)
{
	CString tempstr,str;
	int i;
	tempstr.Empty();
	if(inbyte->GetSize()==9)
	{
		for(i=0;i<4;i++)
			cfdata.SetAt(i,inbyte->GetAt(i+3));	
		set_show();
		for(i=0;i<9;i++)
		{
			str.Format("%x  ",inbyte->GetAt(i));
			showstr+=str;
		}
		m_datastatic.SetWindowText(showstr);
	}
	else if(inbyte->GetSize()==17)
	{
		for(i=0;i<12;i++)
			cfdata.SetAt(i,inbyte->GetAt(i+3));	
		set_show();
		for(i=0;i<17;i++)
		{
			str.Format("%x  ",inbyte->GetAt(i));
			showstr+=str;
		}
		m_datastatic.SetWindowText(showstr);
	}
//	showstr.Empty();
	
}

void CTestcodedlg::set_show()
{
	int i,temp0,temp1,temp2,temp3;
	float t;
	CString tempstr;
	temp0=cfdata.GetAt(0);
	temp1=cfdata.GetAt(1);
	temp2=cfdata.GetAt(2);  
	temp3=cfdata.GetAt(3);
	for(i=0;i<8;i++)
	{
		if((temp0>>i)&0x1)
			m_code0[7-i].SetBitmap(hcodeonbmp);	
		else
			m_code0[7-i].SetBitmap(hcodeoffbmp);
		if((temp1>>i)&0x1)
			m_code1[7-i].SetBitmap(hcodeonbmp);	
		else
			m_code1[7-i].SetBitmap(hcodeoffbmp);
		if((temp2>>i)&0x1)
			m_code2[7-i].SetBitmap(hcodeonbmp);
		else
			m_code2[7-i].SetBitmap(hcodeoffbmp);
		if((temp3>>i)&0x1)
			m_feedback[i].SetBitmap(hfbackoffbmp);	
		else
			m_feedback[i].SetBitmap(hfbackonbmp);
	}

	temp0=cfdata.GetAt(4);
	temp1=cfdata.GetAt(9);
	t=caldec(temp0,temp1,1);	
	tempstr.Format("%.1f℃",t);
	m_th1.SetWindowText(tempstr);

	temp0=cfdata.GetAt(5);
	t=caldec(temp0,temp1,0);	
	tempstr.Format("%.1f℃",t);
	m_th2.SetWindowText(tempstr);
	
	temp0=cfdata.GetAt(6);
	temp1=cfdata.GetAt(10);
	t=caldec(temp0,temp1,1);	
	tempstr.Format("%.1f℃",t);
	m_th3.SetWindowText(tempstr);

	temp0=cfdata.GetAt(7);
	t=caldec(temp0,temp1,0);	
	tempstr.Format("%.1f℃",t);
	m_th4.SetWindowText(tempstr);

	temp0=cfdata.GetAt(8);
	temp1=cfdata.GetAt(11);
	t=caldec(temp0,temp1,1);	
	tempstr.Format("%.1f℃",t);
	m_th5.SetWindowText(tempstr);
}

BOOL CTestcodedlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	queryopen=1;
	codeonbmp.LoadBitmap(IDB_CODEONBMP);
	codeoffbmp.LoadBitmap(IDB_CODEOFFBMP);
	fbackonbmp.LoadBitmap(IDB_FBACKON);
	fbackoffbmp.LoadBitmap(IDB_FBACKOFF);

	hcodeonbmp=(HBITMAP)codeonbmp.Detach();
	hcodeoffbmp=(HBITMAP)codeoffbmp.Detach();
	hfbackonbmp=(HBITMAP)fbackonbmp.Detach();
	hfbackoffbmp=(HBITMAP)fbackoffbmp.Detach();
	cfdata.SetSize(12);
	for(int i=0;i<12;i++)
	{
		cfdata.SetAt(i,0);
	}
	set_show();
	m_testbt.EnableWindow(TRUE);
	m_stoptestbt.EnableWindow(FALSE);
	showstr.Empty();
	showcount=0;

	if(!m_comm1.GetPortOpen())
	{
		pdoc->set_comm();
		SetTimer(4,25,NULL);
		m_testbt.EnableWindow(FALSE);
		m_stoptestbt.EnableWindow(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

