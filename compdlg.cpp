// compdlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "compdlg.h"
#include "MDSDoc.h"
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Ccompdlg dialog

extern CMDSDoc* pdoc;
Ccompdlg::Ccompdlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ccompdlg::IDD, pParent),m_complist(9)
{
	//{{AFX_DATA_INIT(Ccompdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Ccompdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Ccompdlg)
	DDX_Control(pDX, IDC_COMPLIST, m_complist);
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Ccompdlg, CDialog)
	//{{AFX_MSG_MAP(Ccompdlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Ccompdlg message handlers


BOOL Ccompdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CStringArray Head;
    CByteArray   Cols;
    Head.Add("机组");
    Cols.Add(9);       
    Head.Add("能力");
    Cols.Add(9);      
    Head.Add("平均");
    Cols.Add(10);      
	Head.Add("COMP1");
    Cols.Add(12);     
	Head.Add("COMP2");
    Cols.Add(12);     
	Head.Add("COMP3");
    Cols.Add(12);     
	Head.Add("COMP4");
    Cols.Add(12);     
	Head.Add("COMP5");
    Cols.Add(12);     
	Head.Add("COMP6");
    Cols.Add(12);      
    m_complist.InitCtrl(&Head, &Cols); 
	m_complist.SetExtendedStyle(LVS_EX_GRIDLINES);

	setrow(outairNo);
	refreshdata(outairNo);
	SetTimer(0,1000,NULL);
//	m_complist.SetItemBackgndColor(RGB(100,100,100),2,1);
//	m_complist.SetItemTextColor(RGB(255,0,0),0,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Ccompdlg::setrow(int No)
{
	int i,j,count; 
	int compc[4]={2,2,2,2};
	CString str,tempstr;
//	m_complist.InsertItem(0,"主机");
//	for(i=0;i<pdoc->airlist[No].in_num;i++)
//	{
//		str.Format("从%d#",i);
//		m_complist.InsertItem(0,str);
//	}
	int pos=0;
	CStringArray Head;
	for(i=0;i<17;i++)
	{
		Head.RemoveAll();
		for(j=0;j<9;j++)
		{
			str.Format("");
			Head.Add(str);
		}
		pos=m_complist.AddItem(&Head);
		if (pos!=LISTCTRL_ERROR) ;
	}
	
	//主机
	count=compc[pdoc->airlist[No].air_hp];	//压缩机个数
	for(i=8;i>count;i--)
	{
		m_complist.SetItemBackgndColor(RGB(128,128,128),0,i);
	}
	//从机
	for(j=0;j<pdoc->airlist[No].in_num;j++)
	{
		count=compc[pdoc->airlist[No].indoor_air[No].air_hp];	//压缩机个数
		for(i=8;i>count;i--)
		{
			m_complist.SetItemBackgndColor(RGB(128,128,128),j+1,i);
		}
	}
}

void Ccompdlg::refreshdata(int No)
{
	int i,t,j,k,count;
	
	int compnum[4]={2,2,2,2};
	CString str,tempstr;
	m_complist.SetItemText(0,0,"主机");
	str.Format("%.0fHP",pdoc->airlist[No].s_total_needed_HP);
	m_complist.SetItemText(0,1,str);				//显示出当前需求能力
	m_complist.SetItemText(0,3,"数码");				

	j=0;
	count=compnum[pdoc->airlist[No].air_hp];	//压缩机个数
	for(i=0;i<count;i++)
	{
		if(pdoc->airlist[No].s_compre[i]==0)		//关闭
			m_complist.SetItemBackgndColor(RGB(255,255,0),0,3+i);
		else
			m_complist.SetItemBackgndColor(RGB(0,255,0),0,3+i);
		t=pdoc->airlist[No].data_13[i*3];
		t<<=8;
		t+=pdoc->airlist[No].data_13[i*3+1];
		str.Format("%d.%d",t,pdoc->airlist[No].data_13[i*3+2]);
		//	if(i>0)
	//	{
			m_complist.SetItemText(0,3+i,str);
			j+=t;
	//	}
	}
	j/=(count);
	str.Format("%d",j);
	m_complist.SetItemText(0,2,str);

	for(k=0;k<pdoc->airlist[No].in_num;k++)
	{
		str.Format("从%d#",k);
		m_complist.SetItemText(k+1,0,str);

		str.Format("%.0fHP",pdoc->airlist[No].indoor_air[k].s_total_needed_HP);
		m_complist.SetItemText(k+1,1,str);					//显示出当前需求能力

		j=0;
		count=compnum[pdoc->airlist[No].indoor_air[k].air_hp];//压缩机个数
		for(i=0;i<count;i++)
		{
			if(pdoc->airlist[No].indoor_air[k].s_compre[i]==0)		//关闭
				m_complist.SetItemBackgndColor(RGB(255,255,0),k+1,3+i);
			else
				m_complist.SetItemBackgndColor(RGB(0,255,0),k+1,3+i);
			t=pdoc->airlist[No].indoor_air[k].data_13[i*3];
			t<<=8;
			t+=pdoc->airlist[No].indoor_air[k].data_13[i*3+1];
			str.Format("%d.%d",t,pdoc->airlist[No].indoor_air[k].data_13[i*3+2]);
			m_complist.SetItemText(k+1,3+i,str);
			j+=t;
		}
		j/=count;
		str.Format("%d",j);
		m_complist.SetItemText(k+1,2,str);
	}
}

void Ccompdlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	refreshdata(outairNo);
	querycomptime(outairNo);
	CDialog::OnTimer(nIDEvent);
}

void Ccompdlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(0);
	CDialog::OnCancel();
}

void Ccompdlg::querycomptime(int No)
{
	if(pdoc->m_connectflag==1&&pdoc->m_startflag==1&&pdoc->sendcmdflag==0)//如果串口打开
	{
		pdoc->queryFunNo1=pdoc->queryFunNo;
		pdoc->queryAirNo1=pdoc->queryAirNo;
		pdoc->sendcmdflag=1;
		pdoc->m_errorcount=0;
		pdoc->queryFunNo=13;
		pdoc->queryAirNo=outairNo;
		pdoc->querySAirNo=0;
	}
}
