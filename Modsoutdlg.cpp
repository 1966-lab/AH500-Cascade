// Modsoutdlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Modsoutdlg.h"
#include "MDSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModsoutdlg dialog

extern CMDSDoc* pdoc;
CModsoutdlg::CModsoutdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModsoutdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModsoutdlg)
	//}}AFX_DATA_INIT
}


void CModsoutdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModsoutdlg)
	DDX_Control(pDX, IDOK, m_okbt);
	DDX_Control(pDX, IDCANCEL, m_cancelbt);
	DDX_Control(pDX, IDC_APPLY, m_applybt);
	DDX_Control(pDX, IDC_P8, m_p8);
	DDX_Control(pDX, IDC_P7, m_p7);
	DDX_Control(pDX, IDC_P6, m_p6);
	DDX_Control(pDX, IDC_P5, m_p5);
	DDX_Control(pDX, IDC_P4, m_p4);
	DDX_Control(pDX, IDC_P3, m_p3);
	DDX_Control(pDX, IDC_P2, m_p2);
	DDX_Control(pDX, IDC_P1, m_p1);
	DDX_Control(pDX, IDC_SPIN13, m_spin13);
	DDX_Control(pDX, IDC_SPIN12, m_spin12);
	DDX_Control(pDX, IDC_SPIN11, m_spin11);
	DDX_Control(pDX, IDC_SPIN10, m_spin10);
	DDX_Control(pDX, IDC_SPIN9, m_spin9);
	DDX_Control(pDX, IDC_SPIN8, m_spin8);
	DDX_Control(pDX, IDC_TARGETSHOT, m_targetshot);
	DDX_Control(pDX, IDC_MOVEFAC2, m_movefac2);
	DDX_Control(pDX, IDC_MOVEFAC1, m_movefac1);
	DDX_Control(pDX, IDC_SPIN6, m_spin6);
	DDX_Control(pDX, IDC_SPIN5, m_spin5);
	DDX_Control(pDX, IDC_SPIN4, m_spin4);
	DDX_Control(pDX, IDC_SPIN3, m_spin3);
	DDX_Control(pDX, IDC_SPIN2, m_spin2);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_VAVLE4, m_vavle4);
	DDX_Control(pDX, IDC_VAVLE3, m_vavle3);
	DDX_Control(pDX, IDC_VAVLE2, m_vavle2);
	DDX_Control(pDX, IDC_VAVLE1, m_vavle1);
	DDX_Control(pDX, IDC_DEFROENDTP, m_defroendtp);
	DDX_Control(pDX, IDC_DEFROINTERTIME, m_defrointertime);
	DDX_Control(pDX, IDC_DEFRORUNTIME, m_defroruntime);
	DDX_Control(pDX, IDC_DENOISEDELAYTIME, m_denoisedelaytime);
	DDX_Control(pDX, IDC_DFROSETTP, m_defrosettp);
	DDX_Control(pDX, IDC_DFROCHECKTP, m_defrochecktp);
	DDX_Text(pDX, IDC_DFROCHECKTP, m_defrochecktp1);
	DDV_MinMaxInt(pDX, m_defrochecktp1, -10, 3);
	DDX_Text(pDX, IDC_DEFROENDTP, m_defroendtp1);
	DDV_MinMaxInt(pDX, m_defroendtp1, 10, 50);
	DDX_Text(pDX, IDC_DFROSETTP, m_defrosettp1);
	DDV_MinMaxInt(pDX, m_defrosettp1, -30, 0);
	DDX_Text(pDX, IDC_DEFROINTERTIME, m_defrointertime1);
	DDV_MinMaxInt(pDX, m_defrointertime1, 20, 90);
	DDX_Text(pDX, IDC_DEFRORUNTIME, m_defroruntime1);
	DDV_MinMaxInt(pDX, m_defroruntime1, 5, 25);
	DDX_Text(pDX, IDC_DENOISEDELAYTIME, m_denoisedelaytime1);
	DDV_MinMaxInt(pDX, m_denoisedelaytime1, 3, 9);
	DDX_Text(pDX, IDC_VAVLE1, m_vavle11);
	DDX_Text(pDX, IDC_VAVLE2, m_vavle21);
	DDX_Text(pDX, IDC_VAVLE3, m_vavle31);
	DDX_Text(pDX, IDC_VAVLE4, m_vavle41);
	DDX_Text(pDX, IDC_MOVEFAC1, m_movefac11);
	DDV_MinMaxFloat(pDX, m_movefac11, 0.f, 5.f);
	DDX_Text(pDX, IDC_MOVEFAC2, m_movefac21);
	DDV_MinMaxFloat(pDX, m_movefac21, 0.f, 5.f);
	DDX_Text(pDX, IDC_TARGETSHOT, m_targetshot1);
	DDV_MinMaxFloat(pDX, m_targetshot1, 0.f, 10.f);
	DDX_Text(pDX, IDC_P8, m_p81);
	DDX_Text(pDX, IDC_P7, m_p71);
	DDX_Text(pDX, IDC_P6, m_p61);
	DDX_Text(pDX, IDC_P5, m_p51);
	DDV_MinMaxInt(pDX, m_p51, 0, 50);
	DDX_Text(pDX, IDC_P4, m_p41);
	DDV_MinMaxInt(pDX, m_p41, 0, 50);
	DDX_Text(pDX, IDC_P3, m_p31);
	DDV_MinMaxInt(pDX, m_p31, 0, 50);
	DDX_Text(pDX, IDC_P2, m_p21);
	DDV_MinMaxInt(pDX, m_p21, 0, 50);
	DDX_Text(pDX, IDC_P1, m_p11);
	DDV_MinMaxInt(pDX, m_p11, 0, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModsoutdlg, CDialog)
	//{{AFX_MSG_MAP(CModsoutdlg)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModsoutdlg message handlers
void CModsoutdlg::showdata()
{
	CString str;
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_check_start_tp_s0);
	m_defrochecktp.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_set_tp_s0);
	m_defrosettp.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_exit_tp_s0);
	m_defroendtp.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_intertime_s0);
	m_defrointertime.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_runtime_s0);
	m_defroruntime.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delnoise_delaytime_s0);
	m_denoisedelaytime.SetWindowText(str);

	//阀门
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve1_s0);
	m_vavle1.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve2_s0);
	m_vavle2.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve3_s0);
	m_vavle3.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve4_s0);
	m_vavle4.SetWindowText(str);

	int t=0;
	//能力需求
//	str.Format("%.1f",pdoc->airlist[outairNo].s_total_needed_HP);
//	m_needhp.SetWindowText(str);

	float f;
	//目标过热度
	f=(float)pdoc->airlist[outairNo].s_targetsuperhot_s0;
	f/=10;
	str.Format("%.1f",f);
	m_targetshot.SetWindowText(str);
	//动作系数1
	f=(float)pdoc->airlist[outairNo].s_movefac1_s0;
	f/=10;
	str.Format("%.1f",f);
	m_movefac1.SetWindowText(str);
	//动作系数2
	f=(float)pdoc->airlist[outairNo].s_movefac2_s0;
	f/=10;
	str.Format("%.1f",f);
	m_movefac2.SetWindowText(str);
	
	t=pdoc->airlist[outairNo].s_p1_s0;
	str.Format("%d",t);
	m_p1.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p2_s0;
	str.Format("%d",t);
	m_p2.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p3_s0;
	str.Format("%d",t);
	m_p3.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p4_s0;	
	str.Format("%d",t);
	m_p4.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p5_s0;
	str.Format("%d",t);
	m_p5.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p6_s0;
	str.Format("%d",t);
	m_p6.SetWindowText(str);
	
	t=pdoc->airlist[outairNo].s_p7_s0;
	str.Format("%d",t);
	m_p7.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p8_s0;
	str.Format("%d",t);
	m_p8.SetWindowText(str);
}
void CModsoutdlg::OnApply() 
{   
	// TODO: Add your control notification handler code here
	CString str;
	UpdateData(TRUE);
	str.Empty();
	//设置数据检查
	if(m_p11>m_p21)
		str="TscA1不能大于TscA2";
	if(m_p21>50)
		str+="\r\nTscA2不能大于50℃";
	if(m_p31>m_p41)
		str+="\r\nTscT1不能大于TscT2";
	if(m_p41>m_p51)
		str+="\r\nTscT2不能大于TscT3";
	if(m_p51>50)
		str+="\r\nTscT3不能大于50℃";
	if(!str.IsEmpty())
	{

		str+="\r\n\r\n请你重新设置,OK?";
		if(MessageBox(str,"错误",MB_OK|MB_ICONERROR)==IDOK)
			return;
	}
	pdoc->airlist[outairNo].s_delfrost_check_start_tp1=m_defrochecktp1;
	pdoc->airlist[outairNo].s_delfrost_set_tp1=m_defrosettp1;
	pdoc->airlist[outairNo].s_delfrost_exit_tp1=m_defroendtp1;
	pdoc->airlist[outairNo].s_delfrost_intertime1=m_defrointertime1;
	pdoc->airlist[outairNo].s_delfrost_runtime1=m_defroruntime1;
	pdoc->airlist[outairNo].s_delnoise_delaytime1=m_denoisedelaytime1;

	pdoc->airlist[outairNo].s_ele_distension_valve11=m_vavle11;
	pdoc->airlist[outairNo].s_ele_distension_valve21=m_vavle21;
	pdoc->airlist[outairNo].s_ele_distension_valve31=m_vavle31;
	pdoc->airlist[outairNo].s_ele_distension_valve41=m_vavle41;

	//pdoc->airlist[outairNo].s_windmotor11=fan1;
	//pdoc->airlist[outairNo].s_windmotor21=fan2;
//	pdoc->airlist[outairNo].s_windmotor31=fan3;

//	pdoc->airlist[outairNo].s_total_needed_HP1=m_needhp1;
	
	pdoc->airlist[outairNo].s_targetsuperhot1=m_targetshot1*10;
	pdoc->airlist[outairNo].s_movefac11=m_movefac11*10;
	pdoc->airlist[outairNo].s_movefac21=m_movefac21*10;

	pdoc->airlist[outairNo].s_p11=m_p11;
	pdoc->airlist[outairNo].s_p21=m_p21;
	pdoc->airlist[outairNo].s_p31=m_p31;
	pdoc->airlist[outairNo].s_p41=m_p41;
	pdoc->airlist[outairNo].s_p51=m_p51;
	pdoc->airlist[outairNo].s_p61=m_p61;
	pdoc->airlist[outairNo].s_p71=m_p71;
	pdoc->airlist[outairNo].s_p81=m_p81;

	if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
	{
		if(MessageBox("确实要修改吗",NULL,MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
		pdoc->queryFunNo1=pdoc->queryFunNo;
		pdoc->queryAirNo1=pdoc->queryAirNo;
		pdoc->sendcmdflag=1;
		pdoc->m_errorcount=0;
		pdoc->queryFunNo=6;
		pdoc->queryAirNo=outairNo;
		pdoc->querySAirNo=1;
	}
}


 
BOOL CModsoutdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spin1.SetRange(-10,0);

	m_spin2.SetRange(-30,0);

	m_spin3.SetRange(10,50);

	m_spin4.SetRange(20,90);

	m_spin5.SetRange(5,25);

	m_spin6.SetRange(3,9);

//	m_spin7.SetRange(0,25); 

	m_spin8.SetRange(0,50); 
	m_spin9.SetRange(0,50); 
	m_spin10.SetRange(0,50); 
	m_spin11.SetRange(0,50); 
	m_spin12.SetRange(0,50); 
//	m_spin13.SetRange(0,50); 

	showdata();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModsoutdlg::OnOK() 
{
	// TODO: Add extra validation here
	OnApply();
	CDialog::OnOK();
}
