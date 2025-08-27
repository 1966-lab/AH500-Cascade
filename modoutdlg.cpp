// modoutdlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "modoutdlg.h"
#include "MDSDoc.h"
#include "MESSAGEBOXDLG.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cmodoutdlg dialog
extern CMDSApp theApp;
extern CMDSDoc* pdoc;
Cmodoutdlg::Cmodoutdlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cmodoutdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cmodoutdlg)
	m_airnum = 0;
	m_defrochecktp1 = 0;
	m_defroendtp1 = 0;
	m_defrosettp1 = 0;
	m_defrointertime1 = 0;
	m_defroruntime1 = 0;
	m_denoisedelaytime1 = 0;
	m_vavle11 = 0;
	m_vavle21 = 0;
	m_vavle31 = 0;
	m_vavle41 = 0;
	m_movefac11 = 0.0f;
	m_movefac21 = 0.0f;
	m_targetshot1 = 0.0f;
	m_p81 = 0;
	m_p71 = 0;
	m_p61 = 0;
	m_p51 = 0;
	m_p41 = 0;
	m_p31 = 0;
	m_p21 = 0;
	m_p11 = 0;
	m_sethp1 = 0;
	m_antifreeze1 = 0;
	m_winterantif1 = 0;
	outairNo=0;
	m_ev1time1 = 0;
	//}}AFX_DATA_INIT

}


void Cmodoutdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cmodoutdlg)
	DDX_Control(pDX, IDC_SPIN15, m_spin15);
	DDX_Control(pDX, IDC_SPIN18, m_spin18);
	DDX_Control(pDX, IDC_EV1TIME, m_ev1time);
	DDX_Control(pDX, IDC_VALVE2, m_valve2);
	DDX_Control(pDX, IDC_RLY9, m_rly9);
	DDX_Control(pDX, IDC_RLY8, m_rly8);
	DDX_Control(pDX, IDC_RLY7, m_rly7);
	DDX_Control(pDX, IDC_RLY6, m_rly6);
	DDX_Control(pDX, IDC_RLY3, m_rly3);
	DDX_Control(pDX, IDC_RLY2, m_rly2);
	DDX_Control(pDX, IDC_SPIN17, m_spin17);
	DDX_Control(pDX, IDC_SPIN16, m_spin16);
	DDX_Control(pDX, IDC_WINTERANTIF, m_winterantif);
	DDX_Control(pDX, IDC_ANTIFREEZE, m_antifreeze);
	DDX_Control(pDX, IDC_VALVE, m_valve);
	DDX_Control(pDX, IDC_FAN2, m_fan2);
	DDX_Control(pDX, IDC_FAN1, m_fan1);
	DDX_Control(pDX, IDC_SETHP, m_sethp);
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
	DDX_Control(pDX, IDC_AIRNUM, m_airnumctl);
	DDX_Text(pDX, IDC_AIRNUM, m_airnum);
	DDV_MinMaxInt(pDX, m_airnum, 1, 32);
//	DDX_Text(pDX, IDC_DFROCHECKTP, m_defrochecktp1);
//	DDV_MinMaxInt(pDX, m_defrochecktp1, -10, 3);
//	DDX_Text(pDX, IDC_DEFROENDTP, m_defroendtp1);
//	DDV_MinMaxInt(pDX, m_defroendtp1, 10, 50);
//	DDX_Text(pDX, IDC_DFROSETTP, m_defrosettp1);
//	DDV_MinMaxInt(pDX, m_defrosettp1, -30, 0);
//	DDX_Text(pDX, IDC_DEFROINTERTIME, m_defrointertime1);
//	DDV_MinMaxInt(pDX, m_defrointertime1, 20, 90);
//	DDX_Text(pDX, IDC_DEFRORUNTIME, m_defroruntime1);
//	DDV_MinMaxInt(pDX, m_defroruntime1, 5, 25);
//	DDX_Text(pDX, IDC_DENOISEDELAYTIME, m_denoisedelaytime1);
//	DDV_MinMaxInt(pDX, m_denoisedelaytime1, 10, 50);
	DDX_Text(pDX, IDC_VAVLE1, m_vavle11);
	DDX_Text(pDX, IDC_VAVLE2, m_vavle21);
	DDX_Text(pDX, IDC_VAVLE3, m_vavle31);
	DDX_Text(pDX, IDC_VAVLE4, m_vavle41);
//	DDX_Text(pDX, IDC_MOVEFAC1, m_movefac11);
//	DDV_MinMaxFloat(pDX, m_movefac11, 0.f, 7.f);
//	DDX_Text(pDX, IDC_MOVEFAC2, m_movefac21);
//	DDV_MinMaxFloat(pDX, m_movefac21, 0.f, 5.f);
//	DDX_Text(pDX, IDC_TARGETSHOT, m_targetshot1);
//	DDV_MinMaxFloat(pDX, m_targetshot1, 0.f, 10.f);
	DDX_Text(pDX, IDC_P8, m_p81);
	DDX_Text(pDX, IDC_P7, m_p71);
	DDX_Text(pDX, IDC_P6, m_p61);
//	DDX_Text(pDX, IDC_P5, m_p51);
//	DDV_MinMaxInt(pDX, m_p51, 0, 50);
//	DDX_Text(pDX, IDC_P4, m_p41);
//	DDV_MinMaxInt(pDX, m_p41, 0, 50);
//	DDX_Text(pDX, IDC_P3, m_p31);
//	DDV_MinMaxInt(pDX, m_p31, 0, 50);
//	DDX_Text(pDX, IDC_P2, m_p21);
//	DDV_MinMaxInt(pDX, m_p21, 0, 50);
//	DDX_Text(pDX, IDC_P1, m_p11);
//	DDV_MinMaxInt(pDX, m_p11, 0, 50);
	DDX_Text(pDX, IDC_SETHP, m_sethp1);
//	DDX_Text(pDX, IDC_ANTIFREEZE, m_antifreeze1);
//	DDV_MinMaxInt(pDX, m_antifreeze1, -10, 5);
//	DDX_Text(pDX, IDC_WINTERANTIF, m_winterantif1);
//	DDV_MinMaxInt(pDX, m_winterantif1, 0, 5);
//	DDX_Text(pDX, IDC_EV1TIME, m_ev1time1);
//	DDV_MinMaxInt(pDX, m_ev1time1, 0, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cmodoutdlg, CDialog)
	//{{AFX_MSG_MAP(Cmodoutdlg)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cmodoutdlg message handlers
 
BOOL Cmodoutdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(theApp.m_bLanguage==0)
	{
		m_fan1.AddString("停止");
		m_fan1.AddString("低速");
		m_fan1.AddString("中速");
		m_fan1.AddString("高速");
		m_fan2.AddString("停止");
		m_fan2.AddString("低速");
		m_fan2.AddString("中速");
		m_fan2.AddString("高速");

		m_rly2.AddString("关");
		m_rly2.AddString("开");
		m_rly3.AddString("关");
		m_rly3.AddString("开");
		m_rly6.AddString("关");
		m_rly6.AddString("开");
		m_rly7.AddString("关");
		m_rly7.AddString("开");
		m_rly8.AddString("关");
		m_rly8.AddString("开");
		m_rly9.AddString("关");
		m_rly9.AddString("开");

		m_valve.AddString("关");
		m_valve.AddString("开");
		m_valve2.AddString("关");
		m_valve2.AddString("开");
	}
	else if(theApp.m_bLanguage==1)
	{
		m_fan1.AddString("Stop");
		m_fan1.AddString("Low");
		m_fan1.AddString("Medium");
		m_fan1.AddString("High");
		m_fan2.AddString("Stop");
		m_fan2.AddString("Low");
		m_fan2.AddString("Medium");
		m_fan2.AddString("High");
		m_rly2.AddString("OFF");
		m_rly2.AddString("ON");
		m_rly3.AddString("OFF");
		m_rly3.AddString("ON");
		m_rly6.AddString("OFF");
		m_rly6.AddString("ON");
		m_rly7.AddString("OFF");
		m_rly7.AddString("ON");
		m_rly8.AddString("OFF");
		m_rly8.AddString("ON");
		m_rly9.AddString("OFF");
		m_rly9.AddString("ON");

		m_valve.AddString("OFF");
		m_valve.AddString("ON");
		m_valve2.AddString("OFF");
		m_valve2.AddString("ON");
	}
	
	// TODO: Add extra initialization here
	if(pdoc->m_connectflag==1)
		m_airnumctl.EnableWindow(FALSE);
	m_spin1.SetRange(-10,3);

	m_spin2.SetRange(-30,0);

	m_spin3.SetRange(10,50);

	m_spin4.SetRange(20,90);

	m_spin5.SetRange(5,25);

	m_spin6.SetRange(10,50);

//	m_spin7.SetRange(0,25); 

	m_spin8.SetRange(0,50); 
	m_spin9.SetRange(0,50); 
	m_spin10.SetRange(0,50); 
	m_spin11.SetRange(0,50); 
	m_spin12.SetRange(0,50); 
//	m_spin13.SetRange(0,50); 
	m_spin15.SetRange(0,500); 
	m_spin16.SetRange(-10,5); 
	m_spin17.SetRange(5,10); 
	m_spin18.SetRange(0,30); 
	showdata();
	if(theApp.m_bLanguage==0)
	{
		this->SetWindowText("修改外机配置参数");
		GetDlgItem(IDC_STATIC_FROSTA)->SetWindowText("除霜曲线A点(-10~3):");
		GetDlgItem(IDC_STATIC_FROST_B)->SetWindowText("除霜曲线B点(-30~0):");
		GetDlgItem(IDC_STATIC_FROST_END)->SetWindowText("除霜结束温度(10~50):");
		GetDlgItem(IDC_STATIC_FROST_TIME)->SetWindowText("除霜间隔时间(20~90):");
		GetDlgItem(IDC_STATIC_FROST_RUNTIME)->SetWindowText("除霜运行时间(5~25):");
		GetDlgItem(IDC_STATIC_ABLETIME)->SetWindowText("能力计算周期(10~50):");
		GetDlgItem(IDC_STATIC_FEETEMP)->SetWindowText("制冷防冻温度(-10~5):");
		GetDlgItem(IDC_STATIC_WINDTEMP)->SetWindowText("冬季防冻温度(5~10):");
		GetDlgItem(IDC_STATIC_HEATWATER)->SetWindowText("热气旁通时间(0~30):");
		
		GetDlgItem(IDC_STATIC_START)->SetWindowText("启动抽空退出压力(0.0~7.0):");
		GetDlgItem(IDC_STATIC_STOP)->SetWindowText("停机抽空退出压力(0~50):");
		GetDlgItem(IDC_STATIC_BALANCE)->SetWindowText("热交器平衡系数(0.0~5.0):");
		GetDlgItem(IDC_STATIC_PUMPRUNTIME)->SetWindowText("水泵预运行时间:");
		GetDlgItem(IDC_STATIC_OBJECTHEAT)->SetWindowText("目标过热度(0.0~10.0):");

		GetDlgItem(IDC_STATIC_WATERFORCOOL)->SetWindowText("制冷出水设置:");
		GetDlgItem(IDC_STATIC_WATERFORHEAT)->SetWindowText("制热出水设置:");

        GetDlgItem(IDC_STATIC_HANDABLE)->SetWindowText("手动设置能力");

		GetDlgItem(IDC_STATIC_UNIT_NUM)->SetWindowText("机组数量:");

		GetDlgItem(IDC_STATIC_HAND_EXV)->SetWindowText("手动调节阀门开度");

		GetDlgItem(IDC_STATIC_ELEEXV)->SetWindowText("电磁阀");

		GetDlgItem(IDC_APPLY)->SetWindowText("应用");
		GetDlgItem(IDOK)->SetWindowText("确定");
		GetDlgItem(IDCANCEL)->SetWindowText("关闭");

		GetDlgItem(IDC_STATIC_COMPCTRL)->SetWindowText("压缩机控制(调试模式下有效)");
		
		GetDlgItem(IDC_STATIC_COMPRESS0)->SetWindowText("压缩机0:");
		GetDlgItem(IDC_STATIC_COMPRESS1)->SetWindowText("压缩机1:");
		GetDlgItem(IDC_STATIC_COMPRESS2)->SetWindowText("压缩机2:");
		GetDlgItem(IDC_STATIC_COMPRESS3)->SetWindowText("压缩机3:");

		GetDlgItem(IDC_STATIC_FOUR)->SetWindowText("四通阀(调试模式):");
		GetDlgItem(IDC_STATIC_FOURA)->SetWindowText("四通阀a:");
		GetDlgItem(IDC_STATIC_FOURB)->SetWindowText("四通阀b:");

		GetDlgItem(IDC_STATIC_ALARMMESSAGE)->SetWindowText("提醒:  若对系统不熟悉请不要随便使用调试模式,否则会损坏机器");
		
	}
	else if(theApp.m_bLanguage==1)
	{
		this->SetWindowText("Modify the configured parameters of outdoor unit");
		GetDlgItem(IDC_STATIC_FROSTA)->SetWindowText("A on defrosting curve(-10~3):");
		GetDlgItem(IDC_STATIC_FROST_B)->SetWindowText("B on defrosting curve(-30~0):");
		GetDlgItem(IDC_STATIC_FROST_END)->SetWindowText("Defrosting end time(10~50):");
		GetDlgItem(IDC_STATIC_FROST_TIME)->SetWindowText("Defrosting interval(20~90):");
		GetDlgItem(IDC_STATIC_FROST_RUNTIME)->SetWindowText("Defrosting time(5~25):");
		GetDlgItem(IDC_STATIC_ABLETIME)->SetWindowText("Capacity calculation cycle(10~50):");
		GetDlgItem(IDC_STATIC_FEETEMP)->SetWindowText("Anti-freeze temperature for cooling(-10~5):");
		GetDlgItem(IDC_STATIC_WINDTEMP)->SetWindowText("Winter Anti-freezing Temperature(5~10):");//需要翻译
		GetDlgItem(IDC_STATIC_HEATWATER)->SetWindowText("bypass time(0~30):");

		GetDlgItem(IDC_STATIC_START)->SetWindowText("Vacuum pressure for start exit(0.0~7.0):");
		GetDlgItem(IDC_STATIC_STOP)->SetWindowText("Vacuum pressure for stop exit(0~50):");
		GetDlgItem(IDC_STATIC_BALANCE)->SetWindowText("Heat exchanger balance coefficient(0.0~5.0):");
		GetDlgItem(IDC_STATIC_PUMPRUNTIME)->SetWindowText("Pump pre-operation time:");
		GetDlgItem(IDC_STATIC_OBJECTHEAT)->SetWindowText("Target superheat degree(0.0~10.0):");

		GetDlgItem(IDC_STATIC_WATERFORCOOL)->SetWindowText("Cooling outlet water temp.:");
		GetDlgItem(IDC_STATIC_WATERFORHEAT)->SetWindowText("Heating outlet water temp.:");

		GetDlgItem(IDC_STATIC_HANDABLE)->SetWindowText("Manual setting capability");

		GetDlgItem(IDC_STATIC_UNIT_NUM)->SetWindowText("Unit Qty.:");

		GetDlgItem(IDC_STATIC_HAND_EXV)->SetWindowText("Adjust valve openness manually");

		GetDlgItem(IDC_STATIC_ELEEXV)->SetWindowText("Solenoid");

		GetDlgItem(IDC_APPLY)->SetWindowText("Apply");
		GetDlgItem(IDOK)->SetWindowText("OK");
		GetDlgItem(IDCANCEL)->SetWindowText("Close");

		GetDlgItem(IDC_STATIC_COMPCTRL)->SetWindowText("Compressor control (commissioning mode)");

		GetDlgItem(IDC_STATIC_COMPRESS0)->SetWindowText("Compressor 0:");
		GetDlgItem(IDC_STATIC_COMPRESS1)->SetWindowText("Compressor 1:");
		GetDlgItem(IDC_STATIC_COMPRESS2)->SetWindowText("Compressor 2:");
		GetDlgItem(IDC_STATIC_COMPRESS3)->SetWindowText("Compressor 3:");

		GetDlgItem(IDC_STATIC_FOUR)->SetWindowText("4-way valve (commissioning mode):");
		GetDlgItem(IDC_STATIC_FOURA)->SetWindowText("4-way valve a:");
		GetDlgItem(IDC_STATIC_FOURB)->SetWindowText("4-way valve b:");

		GetDlgItem(IDC_STATIC_ALARMMESSAGE)->SetWindowText("Note: Use commissioning mode only when you are familial with the system; otherwise the unit may be damaged.");
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cmodoutdlg::showdata()
{
	CString str;
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_check_start_tp);
	m_defrochecktp.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_set_tp);
	m_defrosettp.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_exit_tp);
	m_defroendtp.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_intertime);
	m_defrointertime.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delfrost_runtime);
	m_defroruntime.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_delnoise_delaytime);
	m_denoisedelaytime.SetWindowText(str);

	//阀门
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve1);
	m_vavle1.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve2);
	m_vavle2.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve3);
	m_vavle3.SetWindowText(str);
	str.Format("%d",pdoc->airlist[outairNo].s_ele_distension_valve4);
	m_vavle4.SetWindowText(str);

	int t=0;
	//能力需求
	pdoc->airlist[outairNo].s_sethp=pdoc->airlist[outairNo].s_total_needed_HP;
	str.Format("%d",pdoc->airlist[outairNo].s_sethp);
	m_sethp.SetWindowText(str);

	float f;
	//目标过热度
	//f=(float)pdoc->airlist[outairNo].s_targetsuperhot_change;
	/*f/=10;
	str.Format("%.1f",f);
	m_targetshot.SetWindowText(str);*/
	//动作系数1
	f=(float)pdoc->airlist[outairNo].s_movefac1;
	f/=10;
	str.Format("%.1f",f);
	m_movefac1.SetWindowText(str);
	//动作系数2
	f=(float)pdoc->airlist[outairNo].s_movefac2;
	f/=10;
	str.Format("%.1f",f);
	m_movefac2.SetWindowText(str);
	
	t=pdoc->airlist[outairNo].s_p1;
	str.Format("%d",t);
	m_p1.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p2;
	str.Format("%d",t);
	m_p2.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p3;
	str.Format("%d",t);
	m_p3.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p4;	
	str.Format("%d",t);
	m_p4.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p5;
	str.Format("%d",t);
	m_p5.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p6;
	str.Format("%d",t);
	m_p6.SetWindowText(str);
	
	t=pdoc->airlist[outairNo].s_p7;
	str.Format("%d",t);
	m_p7.SetWindowText(str);

	t=pdoc->airlist[outairNo].s_p8;
	t*=2;
	str.Format("%d",t);
	m_p8.SetWindowText(str);

	//风速
	m_fan1.SetCurSel(pdoc->airlist[outairNo].s_windmotor1);
	m_fan2.SetCurSel(pdoc->airlist[outairNo].s_windmotor2);

	//电磁阀
	m_valve.SetCurSel(pdoc->airlist[outairNo].s_ele_valve0);
	//电磁阀2
	m_valve2.SetCurSel(pdoc->airlist[outairNo].s_ele_valve1);

	//制冷防冻温度
	str.Format("%d",pdoc->airlist[outairNo].s_antifreeze);
	m_antifreeze.SetWindowText(str);

	//冬季防冻温度
	str.Format("%d",pdoc->airlist[outairNo].s_winterantif);
	m_winterantif.SetWindowText(str);
	//压缩机0
	m_rly9.SetCurSel(pdoc->airlist[outairNo].s_compre[0]);
	//压缩机1
	m_rly8.SetCurSel(pdoc->airlist[outairNo].s_compre[1]);
	//压缩机2
	m_rly7.SetCurSel(pdoc->airlist[outairNo].s_compre[2]);
	//压缩机3
	m_rly6.SetCurSel(pdoc->airlist[outairNo].s_compre[3]);
	//四通阀A
	m_rly3.SetCurSel(pdoc->airlist[outairNo].s_fourvalve1);
	//四通阀B
	m_rly2.SetCurSel(pdoc->airlist[outairNo].s_fourvalve2);
}

void Cmodoutdlg::OnApply() 
{
	// TODO: Add your control notification handler code here
//	CString str;
	UpdateData(TRUE);
	if(!CheckData())
	{
		return;
	}
//	str.Empty();
	//设置数据检查
//	if(m_p11>m_p21)
//		str="TscA1不能大于TscA2";
//	if(m_p21>50)
//		str+="\r\nTscA2不能大于50℃";
//	if(m_p31>m_p41)
//		str+="\r\nTscT1不能大于TscT2";
//	if(m_p41>m_p51)
//		str+="\r\nTscT2不能大于TscT3";
//	if(m_p51>50)
//		str+="\r\nTscT3不能大于50℃";
//	if(!str.IsEmpty())
//	{
//
///		str+="\r\n\r\n请你重新设置,OK?";
//		if(MessageBox(str,"错误",MB_OK|MB_ICONERROR)==IDOK)
//			return;
//	}
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

	pdoc->airlist[outairNo].s_windmotor11=m_fan1.GetCurSel();
	pdoc->airlist[outairNo].s_windmotor21=m_fan2.GetCurSel();
	//pdoc->airlist[outairNo].s_windmotor31=fan3;
	pdoc->airlist[outairNo].s_ele_valve01=m_valve.GetCurSel();
	pdoc->airlist[outairNo].s_ele_valve11=m_valve2.GetCurSel();

	//压缩机0
	pdoc->airlist[outairNo].s_compre1[0]=m_rly9.GetCurSel();
	//压缩机1
	pdoc->airlist[outairNo].s_compre1[1]=m_rly8.GetCurSel();
	//压缩机2
	pdoc->airlist[outairNo].s_compre1[2]=m_rly7.GetCurSel();
	//压缩机3
	pdoc->airlist[outairNo].s_compre1[3]=m_rly6.GetCurSel();
	//四通阀
	pdoc->airlist[outairNo].s_fourvalve11=m_rly3.GetCurSel();
	pdoc->airlist[outairNo].s_fourvalve21=m_rly2.GetCurSel();

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
	pdoc->airlist[outairNo].s_p81=m_p81/2;
	pdoc->airlist[outairNo].s_sethp1=m_sethp1;

	pdoc->airlist[outairNo].s_antifreeze1=m_antifreeze1;
	pdoc->airlist[outairNo].s_winterantif1=m_winterantif1;

	if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
	{
//		if(MessageBox("确实要修改吗",NULL,MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
//		return;
		CString tempstr,tempstr1,tempstrok,tempstrcan;

		if(theApp.m_bLanguage==0)
		{
			tempstr="确实要修改吗?";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="are you sure to modify?";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=1;
		INT_PTR nResponse =dlg.DoModal();
		if(nResponse!=IDOK)
			return;
		pdoc->queryFunNo1=pdoc->queryFunNo;
		pdoc->queryAirNo1=pdoc->queryAirNo;
		pdoc->sendcmdflag=1;
		pdoc->m_errorcount=0;
		pdoc->queryFunNo=6;
		pdoc->queryAirNo=outairNo;
		pdoc->querySAirNo=0;
		pdoc->airlist[outairNo].unit_no=0xff;
	}
}

void Cmodoutdlg::OnOK() 
{
	// TODO: Add extra validation here
	OnApply();
	CDialog::OnOK();
}


int Cmodoutdlg::CheckData()
{
	CString strtemp = "";
	double db = 0;
	CString tempstr,tempstr1,tempstrok,tempstrcan;
	m_defrochecktp.GetWindowText(strtemp);
	m_defrochecktp1 = atoi(strtemp.GetBuffer(0));
	if (m_defrochecktp1 > 3 || m_defrochecktp1 < -10)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认除霜曲线A点(-10~3)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm A on defrosting curve(-10~3)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}


	m_defrosettp.GetWindowText(strtemp);
	m_defrosettp1 = atoi(strtemp.GetBuffer(0));
	if (m_defrosettp1 > 0 || m_defrosettp1 < -30)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认除霜曲线B点(-30~0)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm B on defrosting curve(-30~0)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}	
	
	m_defroendtp.GetWindowText(strtemp);
	m_defroendtp1 = atoi(strtemp.GetBuffer(0));
	if (m_defroendtp1 > 50 || m_defroendtp1 < 10)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认除霜结束温度(10~50)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Defrosting end time(10~50)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}

	m_defrointertime.GetWindowText(strtemp);
	m_defrointertime1 = atoi(strtemp.GetBuffer(0));
	if (m_defrointertime1 > 90 || m_defrointertime1 < 20)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认除霜间隔时间(20~90)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Defrosting interval(20~90)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}
	
	m_defroruntime.GetWindowText(strtemp);
	m_defroruntime1 = atoi(strtemp.GetBuffer(0));
	if (m_defroruntime1 > 25 || m_defroruntime1 < 5)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认除霜运行时间(5~25)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Defrosting time(5~25)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}
	m_denoisedelaytime.GetWindowText(strtemp);
	m_denoisedelaytime1 = atoi(strtemp.GetBuffer(0));
	if (m_denoisedelaytime1 > 50 || m_denoisedelaytime1 < 10)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认能力计算周期(10~50)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Capacity calculation cycle(10~50)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}


	m_movefac1.GetWindowText(strtemp);
	m_movefac11 = atof(strtemp.GetBuffer(0));
	if (m_movefac11 > 7.0 || m_movefac11 < 0.0)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认启动抽空退出压力(0.0~7.0)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Vacuum pressure for start exit(0.0~7.0)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}

	m_movefac2.GetWindowText(strtemp);
	m_movefac21 = atof(strtemp.GetBuffer(0));
	if (m_movefac21 > 5.0 || m_movefac21 < 0.0)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认热交器平衡系数(0.0~5.0)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Heat exchanger balance coefficient(0.0~5.0)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}	

	m_targetshot.GetWindowText(strtemp);
	m_targetshot1 = atof(strtemp.GetBuffer(0));
	if (m_targetshot1 > 10.0 || m_targetshot1 < 0.0)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认目标过热度(0.0~10.0)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Target superheat degree(0.0~10.0)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}


	m_p1.GetWindowText(strtemp);
	m_p11 = atoi(strtemp.GetBuffer(0));
	if (m_p11 > 50|| m_p11 < 0)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认停机抽空退出压力(0~50):";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Vacuum pressure for stop exit(0~50)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}

	m_antifreeze.GetWindowText(strtemp);
	m_antifreeze1 = atoi(strtemp.GetBuffer(0));
	if (m_antifreeze1 > 5|| m_antifreeze1 < -10)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认制冷防冻温度(-10~5)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Anti-freeze temperature for cooling(-10~5)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}

	m_winterantif.GetWindowText(strtemp);
	m_winterantif1 = atoi(strtemp.GetBuffer(0));
	if (m_winterantif1 > 10|| m_winterantif1 < 5)
	{
		if(theApp.m_bLanguage==0)
		{
			tempstr="请确认冬季防冻温度(5~10)";
			tempstr1=L"欧科空调";
			tempstrok=L"确定";
			tempstrcan=L"取消";
		}
		else
		{
			tempstr="Please confirm Winter Anti-freezing Temperature(5~10)";
			tempstr1=L"EUROKLIMAT Air Conditioning";
			tempstrok=L"OK";
			tempstrcan=L"CANCEL";
		}
		MESSAGEBOXDLG dlg;
		dlg.m_title=tempstr1;
		dlg.m_content=tempstr;
		dlg.m_okcontent=tempstrok;
		dlg.m_cancontent=tempstrcan;
		dlg.m_okvisable=1;
		dlg.m_canvisable=0;
		INT_PTR nResponse =dlg.DoModal();
		return FALSE;
	}


	return TRUE;
}


