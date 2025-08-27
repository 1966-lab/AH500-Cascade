// Judgedlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Judgedlg.h"
#include "MDSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJudgedlg dialog

extern CMDSDoc* pdoc;
extern  CMSComm	m_comm1;
CJudgedlg::CJudgedlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJudgedlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJudgedlg)
	m_capstring = _T("");
	m_capstring2 = _T("");
	//}}AFX_DATA_INIT
}


void CJudgedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJudgedlg)
	DDX_Control(pDX, IDC_DATA4, m_data4);
	DDX_Control(pDX, IDC_SELCHK2, m_selchk2);
	DDX_Control(pDX, IDC_CAPDATA2, m_capdata2);
	DDX_Control(pDX, IDC_SELCHK, m_selchk1);
	DDX_Control(pDX, IDC_CAPDATA1, m_capdata1);
	DDX_Control(pDX, IDC_START, m_testbt);
	DDX_Control(pDX, IDOK, m_stoptestbt);
	DDX_Control(pDX, IDC_DATA3, m_data3);
	DDX_Control(pDX, IDC_DATA1, m_data1);
	DDX_Text(pDX, IDC_CAPDATA1, m_capstring);
	DDX_Text(pDX, IDC_CAPDATA2, m_capstring2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJudgedlg, CDialog)
	//{{AFX_MSG_MAP(CJudgedlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_CLEARBTN, OnClearbtn)
	ON_BN_CLICKED(IDC_CLEARBTN1, OnClearbtn1)
	ON_BN_CLICKED(IDC_SELCHK, OnSelchk)
	ON_BN_CLICKED(IDC_SELCHK2, OnSelchk2)
	ON_BN_CLICKED(IDC_CLEARBTN4, OnClearbtn4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJudgedlg message handlers
BOOL CJudgedlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i,j;
	// TODO: Add extra initialization here
	if(!m_comm1.GetPortOpen())
	{
		pdoc->set_comm();
		SetTimer(0,5,NULL);
	}
	m_testbt.EnableWindow(FALSE);
	m_stoptestbt.EnableWindow(TRUE);
	showstr.Empty();
	errorstr.Empty();
	m_capdata1.SetLimitText(40);
	m_capdata2.SetLimitText(40);
	for(i=0;i<6;i++)
	{
		selflag[i]=0;
		for(j=0;j<20;j++)
			starflag[i][j]=0;//标记为*的字节
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CJudgedlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==0)
	{
		CString str;
	//	if(queryopen==1)//发送
	//	{
		//	pdoc->query_code_set();
		//	showstr.Empty();
		//	queryopen=0;
			;
//		}
//		else//响应
//		{
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
			if(reply!=0)
			{
				do_code_data(&Inputdata);
			}
			else
			{
				if(m_comm1.GetInBufferCount()!=0)
				{
					show_error_data(&Inputdata);//显示错误的数据包
				}
			}
//		}
	}
	CDialog::OnTimer(nIDEvent);
}
void CJudgedlg::getcmpdata(CByteArray* inbyte,CString str,int* flag)
{
	int i,l,c,startc;
	char temp,temp1,temp2;
	CString tempstr;
	CByteArray tempbyte,tempbyte1;	
	str.MakeUpper();
	str.TrimLeft(" ");
	l=str.GetLength();
	tempbyte.SetSize(40);
	c=0;
	startc=0;
	for(i=0;i<l;i++)
	{
		temp=str.GetAt(i);
		if(((temp>=48)&&(temp<=57))||((temp>=65)&&(temp<=70))||(temp==42))
		{
			tempbyte.SetAt(c,temp);
			c++;
		}
	}
	if(c%2!=0)
	{
		c--;
		inbyte->SetSize(c/2+1);
		temp2=tempbyte.GetAt(c);
		if(temp2==42)
		{
			*(flag+c/2)=1;
			inbyte->SetAt(c/2,42);
		}
		else
		{
			if((temp2>=48)&&(temp2<=57))
				temp2-=48;
			if((temp2>=65)&&(temp2<=70))
				temp2-=55;
			*(flag+c/2)=0;
			inbyte->SetAt(c/2,temp2);
		}
	}
	else
		inbyte->SetSize(c/2);
	for(i=0;i<c;i+=2)
	{
		temp1=tempbyte.GetAt(i);
		temp2=tempbyte.GetAt(i+1);
		if((temp1>=48)&&(temp1<=57))
			temp1-=48;
		if((temp1>=65)&&(temp1<=70))
			temp1-=55;
		if((temp2>=48)&&(temp2<=57))
			temp2-=48;
		if((temp2>=65)&&(temp2<=70))
			temp2-=55;
		if((temp1==42)||temp2==42)
		{
			inbyte->SetAt(i/2,42);
			*(flag+i/2)=1;
		}
		else
		{
			inbyte->SetAt(i/2,temp1*16+temp2);
			*(flag+i/2)=0;
		}
	}
}
void CJudgedlg::show_error_data(CByteArray* inbyte)
{
	CString tempstr,str,gstr;
	int i,r;
	r=0;
	UpdateData(TRUE);
	tempstr.Empty();
	for(i=0;i<inbyte->GetSize();i++)
	{
		str.Format("%2.2x ",inbyte->GetAt(i));
		tempstr+=str;
		if((i!=0)&&((i+1)%10==0)&&(i!=inbyte->GetSize()))
			tempstr+="\r\n";
	}
	errorstr+=tempstr;
	errorstr+="\r\n";
	m_data4.SetWindowText(errorstr);//显示收到的数据包
	if(errorstr.GetLength()>=5000)
		errorstr.Empty();
}
void CJudgedlg::do_code_data(CByteArray* inbyte)
{
	CString tempstr,str,gstr,tempstr1;;
	int i,r;
	r=0;
	UpdateData(TRUE);
	tempstr.Empty();
	for(i=0;i<inbyte->GetSize();i++)
	{
		str.Format("%2.2x ",inbyte->GetAt(i));
		tempstr+=str;
		if((i!=0)&&((i+1)%10==0)&&(i!=inbyte->GetSize()))
			tempstr+="\r\n";
	}
	
	if(strsortflag1==1)
	{
		tempstr1=showstr;
		showstr.Empty();
		showstr+=tempstr;
		showstr+="\r\n";
		showstr+=tempstr1;
	}
	else
	{
		showstr+=tempstr;
		showstr+="\r\n";
	}
	m_data1.SetWindowText(showstr);//显示收到的数据包
	if(showstr.GetLength()>=5000)
		showstr.Empty();
	if(selflag[0]==1)//比较要捕获的饿数据1
	{
		cfdata.SetSize(0);
		//得到要捕获的第一个数据包
		getcmpdata(&cfdata,m_capstring,starflag[0]);

		for(i=0;i<cfdata.GetSize();i++)
		{
			if(starflag[0][i]==0)
			{
				if(inbyte->GetAt(i)!=cfdata.GetAt(i))
					r=1;
			}
		}
		if(r!=1)
		{
			showreslutstr+=tempstr;
			showreslutstr+="\r\n";
			m_data3.SetWindowText(showreslutstr);
			if(showreslutstr.GetLength()>5000)
				showreslutstr.Empty();
		}
	}
	r=0;
	if(selflag[1]==1)//比较要捕获的数据2
	{
		cfdata1.SetSize(0);
		//得到要捕获的第一个数据包
		getcmpdata(&cfdata1,m_capstring2,starflag[1]);

		for(i=0;i<cfdata1.GetSize();i++)
		{
			if(starflag[1][i]==0)
			{
				if(inbyte->GetAt(i)!=cfdata1.GetAt(i))
					r=1;
			}
		}
		if(r!=1)
		{
			showreslutstr+=tempstr;
			showreslutstr+="\r\n";
			m_data3.SetWindowText(showreslutstr);
			if(showreslutstr.GetLength()>5000)
				showreslutstr.Empty();
		}
	}
}

void CJudgedlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_comm1.GetPortOpen())
		m_comm1.SetPortOpen(0);
	KillTimer(0);
	m_testbt.EnableWindow(TRUE);
	m_stoptestbt.EnableWindow(FALSE);
}

void CJudgedlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_comm1.GetPortOpen())
		m_comm1.SetPortOpen(0);
	KillTimer(0);
	CDialog::OnCancel();
}

void CJudgedlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	if(m_comm1.GetPortOpen())
		return;
	pdoc->set_comm();
	SetTimer(0,25,NULL);
	m_testbt.EnableWindow(FALSE);
	m_stoptestbt.EnableWindow(TRUE);
}


void CJudgedlg::OnClearbtn() 
{
	// TODO: Add your control notification handler code here
	showreslutstr.Empty();
	m_data3.SetWindowText(showreslutstr);
}

void CJudgedlg::OnClearbtn1() 
{
	// TODO: Add your control notification handler code here
	showstr.Empty();
	m_data1.SetWindowText(showstr);
}
void CJudgedlg::chk1show()
{
	int i;
	CString str,tempstr;
	cfdata.SetSize(0);
	//得到要捕获的第一个数据包
	getcmpdata(&cfdata,m_capstring,starflag[0]);
	//调整后输出
	for(i=0;i<cfdata.GetSize();i++)
	{
		if(starflag[0][i]==1)
			str="** ";
		else
			str.Format("%2.2x ",cfdata.GetAt(i));
		tempstr+=str;
		if((i!=0)&&((i+1)%10==0)&&(i!=cfdata.GetSize()))
			tempstr+="\r\n";
	}
	m_capdata1.SetWindowText(tempstr);
}
void CJudgedlg::OnSelchk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	selflag[0]=m_selchk1.GetCheck();
	if(selflag[0]==1)
	{
		chk1show();
	}
}
void CJudgedlg::chk2show()
{
	int i;
	CString str,tempstr;
	cfdata1.SetSize(0);
	//得到要捕获的第一个数据包
	getcmpdata(&cfdata1,m_capstring2,starflag[1]);
	//调整后输出
	for(i=0;i<cfdata1.GetSize();i++)
	{
		if(starflag[1][i]==1)
			str="** ";
		else
			str.Format("%2.2x ",cfdata1.GetAt(i));
		tempstr+=str;
		if((i!=0)&&((i+1)%10==0)&&(i!=cfdata1.GetSize()))
			tempstr+="\r\n";
	}
	m_capdata2.SetWindowText(tempstr);
}
void CJudgedlg::OnSelchk2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	selflag[1]=m_selchk2.GetCheck();
	if(selflag[1]==1)
	{
		chk2show();
	}
}

void CJudgedlg::OnClearbtn4() 
{
	// TODO: Add your control notification handler code here
	errorstr.Empty();
	m_data4.SetWindowText(errorstr);
}
