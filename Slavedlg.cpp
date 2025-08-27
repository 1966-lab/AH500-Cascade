// Slavedlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Slavedlg.h"
#include "MDSDoc.h"
#include "Modsoutdlg.h"
#include "Passworddlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlavedlg dialog

extern CMDSDoc* pdoc;
CSlavedlg::CSlavedlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlavedlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSlavedlg)
	//}}AFX_DATA_INIT
	outairNo=0;
}


void CSlavedlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSlavedlg)
	DDX_Control(pDX, IDOK, m_okbt);
	DDX_Control(pDX, IDC_MODOUTBTN, m_modoutbt);
	DDX_Control(pDX, IDC_ALARMLIST, m_alarmlist);
	DDX_Control(pDX, IDC_ELEVALVE1, m_elevavle1);
	DDX_Control(pDX, IDC_COMP1, m_comp1);
	DDX_Control(pDX, IDC_DNOISEDELAYTIME, m_dnoisedelaytime);
	DDX_Control(pDX, IDC_DFROSTTP, m_dfrosttp);
	DDX_Control(pDX, IDC_FACTSHOT, m_factshot);
	DDX_Control(pDX, IDC_TARGETSHOT, m_targetshot);
	DDX_Control(pDX, IDC_INPAN1, m_inpan1);
	DDX_Control(pDX, IDC_OUTDOORTP, m_outdoortp);
	DDX_Control(pDX, IDC_HICSUPERCOOL, m_hicsupercool);
	DDX_Control(pDX, IDC_DFROSTSTARTTP, m_dfroststarttp);
	DDX_Control(pDX, IDC_LOWPRE, m_lowpre);
	DDX_Control(pDX, IDC_HIGHPRE, m_highpre);
	DDX_Control(pDX, IDC_INGAS, m_ingas);
	DDX_Control(pDX, IDC_OUTGAS, m_outgas);
//	DDX_Control(pDX, IDC_PWMOUT, m_pwmout);
	DDX_Control(pDX, IDC_TOTALNEEDHP, m_totalneedhp);
	DDX_Control(pDX, IDC_ELEVALVE0, m_elevalve0);
//	DDX_Control(pDX, IDC_OILBLANCE, m_oilblance);
//	DDX_Control(pDX, IDC_OILRE, m_oilre);
	DDX_Control(pDX, IDC_RUNMODE, m_runmode);
	DDX_Control(pDX, IDC_HP, m_hp);
	DDX_Control(pDX, IDC_AIRVERSION, m_airversion);
	DDX_Control(pDX, IDC_DFROSTINTERTIME, m_dfrostintertime);
	DDX_Control(pDX, IDC_DFROSTRUNTIME, m_dfrostruntime);
	DDX_Control(pDX, IDC_DFROSTENDTP, m_dfrostendtp);
	DDX_Control(pDX, IDC_AIRTYPE1, m_airtype1);
	DDX_Control(pDX, IDC_MIDPAN3, m_midpan3);
	DDX_Control(pDX, IDC_MIDPAN2, m_midpan2);
	DDX_Control(pDX, IDC_MiDPAN1, m_midpan1);
	DDX_Control(pDX, IDC_OUTPAN3, m_outpan3);
	DDX_Control(pDX, IDC_OUTPAN2, m_outpan2);
	DDX_Control(pDX, IDC_OUTPAN1, m_outpan1);
	DDX_Control(pDX, IDC_INPAN3, m_inpan3);
	DDX_Control(pDX, IDC_INPAN2, m_inpan2);
	DDX_Control(pDX, IDC_FOURVALVE4, m_fourvalve4);
	DDX_Control(pDX, IDC_FOURVALVE3, m_fourvalve3);
	DDX_Control(pDX, IDC_FOURVALVE2, m_fourvalve2);
	DDX_Control(pDX, IDC_FOURVALVE1, m_fourvalve1);
	DDX_Control(pDX, IDC_COMP3, m_comp3);
	DDX_Control(pDX, IDC_COMP2, m_comp2);
	DDX_Control(pDX, IDC_ELEDISTEN4, m_eledisten4);
	DDX_Control(pDX, IDC_ELEDISTEN3, m_eledisten3);
	DDX_Control(pDX, IDC_ELEDISTEN2, m_eledisten2);
	DDX_Control(pDX, IDC_ELEDISTEN1, m_eledisten1);
	DDX_Control(pDX, IDC_FAN3, m_fan3);
	DDX_Control(pDX, IDC_FAN2, m_fan2);
	DDX_Control(pDX, IDC_FAN1, m_fan1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSlavedlg, CDialog)
	//{{AFX_MSG_MAP(CSlavedlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MODOUTBTN, OnModoutbtn)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlavedlg message handlers

//在窗口中输出各个数据
void CSlavedlg::showdata(int No)
{
	CString tempstr,str;
	float f;
	tempstr="MDS";
	//能力
	int AHPstr[2][10]={{3,4,5,6,0,9,0,11,0,0},{3,4,5,6,0,8,0,10,0,0}};
	int BHPstr[2][11]={{8,10,12,15,18,20,22,24,26,28,30},{8,10,12,15,18,20,22,24,26,28,30}};
	if(pdoc->airlist[No].air_hp<0||pdoc->airlist[No].air_type1>10)//检查防止溢出
		pdoc->airlist[No].air_type1=0;
	if(pdoc->airlist[No].air_type1==1)
	{
		str.Format("%.3d%",AHPstr[0][pdoc->airlist[No].air_hp_s0]*10);
	}
	else
	{
		str.Format("%.3d%",BHPstr[0][pdoc->airlist[No].air_hp_s0]*10);
	}
	tempstr+=str;
	//机组类型  0--MDS-B 1--MDS--A
	if(pdoc->airlist[No].air_type1_s0==0)
		str.Format("B");
	else
		str.Format("A");
	tempstr+=str;
	//机组类型  1--单冷  0--热泵
	if(pdoc->airlist[No].air_type2_s0==0)
		tempstr+="R";
	m_airtype1.SetWindowText(tempstr);

	
	//外机程序版本
	tempstr.Format("%.1f",(float)pdoc->airlist[No].out_version_s0/10);
	m_airversion.SetWindowText(tempstr);

	//阀门初始开度
	tempstr.Format("%d",pdoc->airlist[No].air_valve_ini_s0);
	m_hp.SetWindowText(tempstr);

//状态参数
	//运行模式  0--停机 1--制冷 2--制热 3--自动
	//			4--送风 5--除湿 6--除霜 7--调试
	CString runmode[8]={"停机","制冷","制热","自动","送风","除湿","除霜","调试"}; 
	if(pdoc->airlist[No].s_runmode_s0>=0&&pdoc->airlist[No].s_runmode_s0<=7)
	{
		m_runmode.SetWindowText(runmode[pdoc->airlist[No].s_runmode_s0]);
	}

	//0--油回收停止 1--油回收运行
	if(pdoc->airlist[No].s_oil_reclaim_run_s0==0)
		tempstr.Format("停止");
	else
		tempstr.Format("运行");
	m_oilre.SetWindowText(tempstr);
				
	//0--油平衡停止 1--油平衡运行
	if(pdoc->airlist[No].s_oil_blance_run_s0==0)
		tempstr.Format("停止");
	else
		tempstr.Format("运行");
	m_oilblance.SetWindowText(tempstr);
	
	CString wind[4]={"停止","低速","中速","高速"}; 
	//风机1  0--停 1--低速 2--中速 3--高速
	if(pdoc->airlist[No].s_windmotor1_s0>=0&&pdoc->airlist[No].s_windmotor1_s0<=3)//有效性检查
	{
		m_fan1.SetWindowText(wind[pdoc->airlist[No].s_windmotor1_s0]);
	}
	//风机2  0--停 1--低速 2--中速 3--高速
	if(pdoc->airlist[No].s_windmotor2_s0>=0&&pdoc->airlist[No].s_windmotor2_s0<=3)
	{
		m_fan2.SetWindowText(wind[pdoc->airlist[No].s_windmotor2]);
	}
	//风机3  0--停 1--低速 2--中速 3--高速
	if(pdoc->airlist[No].s_windmotor3_s0>=0&&pdoc->airlist[No].s_windmotor3_s0<=3)
	{
		m_fan3.SetWindowText(wind[pdoc->airlist[No].s_windmotor3_s0]);
	}

	//0#电磁阀状态  0--关  1--开
	if(pdoc->airlist[No].s_ele_valve0_s0==0)
		tempstr.Format("停止");
	else
		tempstr.Format("运行");
	m_elevalve0.SetWindowText(tempstr);

	//0#电磁阀状态  0--关  1--开
	if(pdoc->airlist[No].s_ele_valve1_s0==0)
		tempstr.Format("停止");
	else
		tempstr.Format("运行");
	m_elevavle1.SetWindowText(tempstr);

	//压缩机1状态 0--关 1--开
	if(pdoc->airlist[No].s_compre1_s0==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_comp1.SetWindowText(tempstr);

	//压缩机2状态 0--关 1--开
	if(pdoc->airlist[No].s_compre2_s0==0)
	{
		tempstr.Format("关闭");
	}
	else
	{
		tempstr.Format("开");
	}
	m_comp2.SetWindowText(tempstr);
	
	//压缩机3状态 0--关 1--开
	if(pdoc->airlist[No].s_compre3_s0==0)
	{
		tempstr.Format("关闭");
	}
	else
	{
		tempstr.Format("开");
	}
	m_comp3.SetWindowText(tempstr);


	//四通阀1状态 0--关 1--开
	if(pdoc->airlist[No].s_fourvalve1_s0==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_fourvalve1.SetWindowText(tempstr);

	//四通阀2状态 0--关 1--开
	if(pdoc->airlist[No].s_fourvalve2_s0==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_fourvalve2.SetWindowText(tempstr);

	//四通阀3状态 0--关 1--开
	if(pdoc->airlist[No].s_fourvalve3_s0==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_fourvalve3.SetWindowText(tempstr);

	//四通阀4状态 0--关 1--开
	if(pdoc->airlist[No].s_fourvalve4_s0==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_fourvalve4.SetWindowText(tempstr);
	
	//电磁膨胀阀1开度
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve1_s0);
	m_eledisten1.SetWindowText(tempstr);
	//电磁膨胀阀2开度
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve2_s0);
	m_eledisten2.SetWindowText(tempstr);
	//电磁膨胀阀3开度
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve3_s0);
	m_eledisten3.SetWindowText(tempstr);
	//电磁膨胀阀4开度
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve4_s0);
	m_eledisten4.SetWindowText(tempstr);

	//总能力需求(单位HP)
	tempstr.Format("%.1fHP",pdoc->airlist[No].s_total_needed_HP_s0);
	m_totalneedhp.SetWindowText(tempstr);

	//数码压缩机PWM输出百分比
	tempstr.Format("%d%%",pdoc->airlist[No].s_datacompre_PWM_s0);
	m_pwmout.SetWindowText(tempstr);
		
	//排气温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_outgas_tp_s0);
	m_outgas.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outgas_tp_s0>=150)
		m_outgas.SetWindowText("短路");
	if(pdoc->airlist[No].s_outgas_tp_s0<=5)
		m_outgas.SetWindowText("开路");

	//环境温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_environment_tp_s0);
	m_outdoortp.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_environment_tp_s0>=127)
		m_outdoortp.SetWindowText("短路");
	if(pdoc->airlist[No].s_environment_tp_s0<=-127)
		m_outdoortp.SetWindowText("开路");

	//回气温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_ingas_tp_s0);
	m_ingas.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_ingas_tp_s0>=127)
		m_ingas.SetWindowText("短路");
	if(pdoc->airlist[No].s_ingas_tp_s0<=-127)
		m_ingas.SetWindowText("开路");

	//1#进盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_inpan1_tp_s0);
	m_inpan1.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_inpan1_tp_s0>=127)
		m_inpan1.SetWindowText("短路");
	if(pdoc->airlist[No].s_inpan1_tp_s0<=-127)
		m_inpan1.SetWindowText("开路");
	//1#中盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_midpan1_tp_s0);
	m_midpan1.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_midpan1_tp_s0>=127)
		m_midpan1.SetWindowText("短路");
	if(pdoc->airlist[No].s_midpan1_tp_s0<=-127)
		m_midpan1.SetWindowText("开路");
	//1#出盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_outpan1_tp_s0);
	m_outpan1.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outpan1_tp_s0>=127)
		m_outpan1.SetWindowText("短路");
	if(pdoc->airlist[No].s_outpan1_tp_s0<=-127)
		m_outpan1.SetWindowText("开路");

	//2#进盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_inpan2_tp_s0);
	m_inpan2.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_inpan2_tp_s0>=127)
		m_inpan2.SetWindowText("短路");
	if(pdoc->airlist[No].s_inpan2_tp_s0<=-127)
		m_inpan2.SetWindowText("开路");
	//2#中盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_midpan2_tp_s0);
	m_midpan2.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_midpan2_tp_s0>=127)
		m_midpan2.SetWindowText("短路");
	if(pdoc->airlist[No].s_midpan2_tp_s0<=-127)
		m_midpan2.SetWindowText("开路");
	//2#出盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_outpan2_tp_s0);
	m_outpan2.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outpan2_tp_s0>=127)
		m_outpan2.SetWindowText("短路");
	if(pdoc->airlist[No].s_outpan2_tp_s0<=-127)
		m_outpan2.SetWindowText("开路");

	//3#进盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_inpan3_tp_s0);
	m_inpan3.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_inpan3_tp_s0>=127)
		m_inpan3.SetWindowText("短路");
	if(pdoc->airlist[No].s_inpan3_tp_s0<=-127)
		m_inpan3.SetWindowText("开路");
	//3#中盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_midpan3_tp_s0);
	m_midpan3.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_midpan3_tp_s0>=127)
		m_midpan3.SetWindowText("短路");
	if(pdoc->airlist[No].s_midpan3_tp_s0<=-127)
		m_midpan3.SetWindowText("开路");
	//3#出盘温度
	tempstr.Format("%.1f℃",pdoc->airlist[No].s_outpan3_tp_s0);
	m_outpan3.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outpan3_tp_s0>=127)
		m_outpan3.SetWindowText("短路");
	if(pdoc->airlist[No].s_outpan3_tp_s0<=-127)
		m_outpan3.SetWindowText("开路");

	//高压
	tempstr.Format("%.1fBar",pdoc->airlist[No].s_highpre_s0);
	m_highpre.SetWindowText(tempstr);

	//低压
	tempstr.Format("%.1fBar",pdoc->airlist[No].s_lowpre_s0);
	m_lowpre.SetWindowText(tempstr);

	//除霜检测开始温度(-3~3℃),带符号表示
	tempstr.Format("%d℃",pdoc->airlist[No].s_delfrost_check_start_tp_s0);
	m_dfroststarttp.SetWindowText(tempstr);

	//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_set_tp_s0);
	m_dfrosttp.SetWindowText(tempstr);
	
	//除霜结束温度  (10~50℃	默认15℃)
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_exit_tp_s0);
	m_dfrostendtp.SetWindowText(tempstr);
	
	//除霜间隔时间  (0~90min,  默认45min)
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_intertime_s0);
	m_dfrostintertime.SetWindowText(tempstr);
	
	//除霜运行时间  (5~25min,  默认10min)
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_runtime_s0);
	m_dfrostruntime.SetWindowText(tempstr);
		
	//降噪延迟时间(3~9,默认6)
	tempstr.Format("%d",pdoc->airlist[No].s_delnoise_delaytime_s0);
	m_dnoisedelaytime.SetWindowText(tempstr);

	//实际过热度
	tempstr.Format("%.1f",pdoc->airlist[No].s_factsuperhot_s0);
	m_factshot.SetWindowText(tempstr);

	//目标过热度
	f=(float)pdoc->airlist[No].s_targetsuperhot_s0;
	f/=10;
	tempstr.Format("%.1f",f);
	m_targetshot.SetWindowText(tempstr);
	//HIC回路目标过冷度
/*	tempstr.Format("%d",pdoc->airlist[No].s_targetsupercool_s0);
	m_hicsupercool.SetWindowText(tempstr);*/
}

BOOL CSlavedlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString tempstr;
	tempstr.Format("(%d#外机)  0#从机状态",outairNo);
	this->SetWindowText(tempstr);
	if(pdoc->m_connectflag==1)
	{
		SetTimer(0,1000,NULL);
		SetTimer(1,2000,NULL);
	}
	showdata(outairNo);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSlavedlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==0)//更新显示错误
	{
		showdata(outairNo);
	}
	if(nIDEvent==1)//更新显示错误
	{
		showerror(outairNo);
	}
	CDialog::OnTimer(nIDEvent);
}

void CSlavedlg::showerror(int No)
{
	int i=0;
	int temp=0;
//	m_alarmlist.ShowWindow(FALSE);
	for(i=m_alarmlist.GetCount()-1;i>=0;i--)
	{
		m_alarmlist.DeleteString(i);
	}
	CString errorstr[15]={"定速压缩机1过载","定速压缩机2过载","定速压缩机3过载","定速压缩机4过载","高压故障","低压故障","探头故障","系统故障","排气温度过高","内外机通讯故障","四通阀故障","环境温度过高/低","紧急运行","过热度过小","冷媒泄露"};
//	m_alarmlist.AddString("0#从机故障列表");
	for(i=0;i<15;i++)
	{
		if(pdoc->airlist[No].s_error_s0[i]==1)
		{
			if(i!=9)
				m_alarmlist.AddString(errorstr[i]);
		}
	}//故障*/
}

void CSlavedlg::OnModoutbtn() 
{
	// TODO: Add your control notification handler code here
	

	CModsoutdlg dlg;
	CPassworddlg pdlg;

	if(pdlg.DoModal()!=IDOK)
		return;
	dlg.outairNo=outairNo;
	dlg.DoModal();
}

HBRUSH CSlavedlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_LISTBOX&&pWnd->GetDlgCtrlID()==IDC_ALARMLIST) 
	{
		pDC->SetBkColor(RGB(255,255,255));
		pDC->SetTextColor(RGB(255,0,0));
		HBRUSH b=CreateSolidBrush(RGB(255,255,255));
		return b;
	//	pDC->SetBkColor(RGB(255,255,0));
	//	return m_listbkbrush;
 	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
