// mod_slave_cfg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "mod_slave_cfg.h"
#include "MDSDoc.h"
#include "MESSAGEBOXDLG.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cmod_slave_cfg dialog
extern CMDSApp theApp;
extern CMDSDoc* pdoc;
Cmod_slave_cfg::Cmod_slave_cfg(CWnd* pParent /*=NULL*/)
	: CDialog(Cmod_slave_cfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cmod_slave_cfg)
	m_int_defa = -4;
	m_int_defb = -20;
	m_int_defexit = 28;
	m_int_defint = 45;
	m_int_deftime = 10;
	m_int_winant = 5;
	m_int_coolant = 5;
	m_int_obsup = 4;
	outairNo=0;
	m_s_valve11 = 0;
	m_s_valve21 = 0;
	m_s_valve31 = 0;
	m_s_valve41 = 0;
	//}}AFX_DATA_INIT
}


void Cmod_slave_cfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cmod_slave_cfg)
	DDX_Control(pDX, IDC_S_VALVE4, m_s_valve4);
	DDX_Control(pDX, IDC_S_VALVE3, m_s_valve3);
	DDX_Control(pDX, IDC_S_VALVE2, m_s_valve2);
	DDX_Control(pDX, IDC_S_VALVE1, m_s_valve1);
	DDX_Control(pDX, IDOK, m_bt_ok);
	DDX_Control(pDX, IDCANCEL, m_bt_cancle);
	DDX_Control(pDX, ID_APPLY, m_bt_apply);
	DDX_Control(pDX, IDC_SLAVE_SEL, m_slavesel);
	DDX_Control(pDX, IDC_SPWNTANT_SET, m_spwinant_set);
	DDX_Control(pDX, IDC_SPSUP_SET, m_spsup_set);
	DDX_Control(pDX, IDC_SPDEFTIME_SET, m_spdeftime_set);
	DDX_Control(pDX, IDC_SPDEFINT_SET, m_spdefint_set);
	DDX_Control(pDX, IDC_SPDEFEXIT_SET, m_spdefeixt_set);
	DDX_Control(pDX, IDC_SPDEFB_SET, m_spdefb_set);
	DDX_Control(pDX, IDC_SPDEFA_SET, m_spdefa_set);
	DDX_Control(pDX, IDC_SPCOOLANT_SET, m_spcoolant_set);
	DDX_Control(pDX, IDC_OBSUP, m_edit_obsup);
	DDX_Control(pDX, IDC_COOLANT, m_edit_coolant);
	DDX_Control(pDX, IDC_WININT, m_edit_winant);
	DDX_Control(pDX, IDC_DEFINT, m_edit_defint);
	DDX_Control(pDX, IDC_DEFTIME, m_edit_time);
	DDX_Control(pDX, IDC_DEFEXIT, m_edit_defexit);
	DDX_Control(pDX, IDC_DEFB, m_edit_defb);
	DDX_Control(pDX, IDC_DEFA, m_edit_defa);
	DDX_Text(pDX, IDC_DEFA, m_int_defa);
	DDV_MinMaxInt(pDX, m_int_defa, -10, 0);
	DDX_Text(pDX, IDC_DEFB, m_int_defb);
	DDV_MinMaxInt(pDX, m_int_defb, -30, 0);
	DDX_Text(pDX, IDC_DEFEXIT, m_int_defexit);
	DDV_MinMaxInt(pDX, m_int_defexit, 10, 50);
	DDX_Text(pDX, IDC_DEFINT, m_int_defint);
	DDV_MinMaxInt(pDX, m_int_defint, 20, 90);
	DDX_Text(pDX, IDC_DEFTIME, m_int_deftime);
	DDX_Text(pDX, IDC_WININT, m_int_winant);
	DDV_MinMaxInt(pDX, m_int_winant, 2, 5);
	DDX_Text(pDX, IDC_COOLANT, m_int_coolant);
	DDV_MinMaxInt(pDX, m_int_coolant, 2, 5);
	DDX_Text(pDX, IDC_OBSUP, m_int_obsup);
	DDV_MinMaxInt(pDX, m_int_obsup, 0, 10);
	DDX_Text(pDX, IDC_S_VALVE1, m_s_valve11);
	DDX_Text(pDX, IDC_S_VALVE2, m_s_valve21);
	DDX_Text(pDX, IDC_S_VALVE3, m_s_valve31);
	DDX_Text(pDX, IDC_S_VALVE4, m_s_valve41);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cmod_slave_cfg, CDialog)
	//{{AFX_MSG_MAP(Cmod_slave_cfg)
	ON_CBN_EDITCHANGE(IDC_SLAVE_SEL, OnEditchangeSlaveSel)
	ON_CBN_SELCHANGE(IDC_SLAVE_SEL, OnSelchangeSlaveSel)
	ON_BN_CLICKED(ID_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cmod_slave_cfg message handlers

BOOL Cmod_slave_cfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	if(pdoc->m_connectflag==1)
		//m_airnumctl.EnableWindow(FALSE);
	// TODO: Add extra initialization here
	int i;
	CString tempstr,str;
	for(i=m_slavesel.GetCount()-1;i>=0;i--)
		m_slavesel.DeleteString(i);
	for(i=0;i<pdoc->airlist[outairNo].in_num;i++)
	{		
		tempstr.Format("%d#",i);
		m_slavesel.InsertString(-1,tempstr);
	}
	m_slavesel.SetCurSel(0);
	m_spdefa_set.SetRange(-10,0);
	m_spdefb_set.SetRange(-30,0);
    m_spdefeixt_set.SetRange(10,50);
	m_spdeftime_set.SetRange(5,25);
	m_spdefint_set.SetRange(20,90);
	m_spcoolant_set.SetRange(2,5);
	m_spwinant_set.SetRange(2,5);
	m_spsup_set.SetRange(0,10);
	show_data(0,0);
	if(theApp.m_bLanguage==0)
	{
		this->SetWindowText("修改从机配置参数");
		GetDlgItem(IDC_STATIC_SELECT_SLAVEUNIT)->SetWindowText("选择从机");

		GetDlgItem(IDC_STATIC_FROSTA)->SetWindowText("除霜曲线A点:");//(-10~3)
		GetDlgItem(IDC_STATIC_FROST_B)->SetWindowText("除霜曲线B点:");//(-30~0)
		GetDlgItem(IDC_STATIC_FROST_END)->SetWindowText("除霜结束温度:");//(10~50)
		GetDlgItem(IDC_STATIC_FROST_TIME)->SetWindowText("除霜间隔时间:");//(20~90)
		GetDlgItem(IDC_STATIC_FROST_RUNTIME)->SetWindowText("除霜运行时间:");//(5~25)
		GetDlgItem(IDC_STATIC_FEETEMP)->SetWindowText("制冷防冻温度:");//(-10~5)
		GetDlgItem(IDC_STATIC_WINDTEMP)->SetWindowText("冬季防冻温度:");//(5~10)
		GetDlgItem(IDC_STATIC_OBJECTHEAT)->SetWindowText("目标过热度:");//(0.0~10.0)

		GetDlgItem(ID_APPLY)->SetWindowText("应用");
		GetDlgItem(IDOK)->SetWindowText("确定");
		GetDlgItem(IDCANCEL)->SetWindowText("关闭");

		
	}
	else if(theApp.m_bLanguage==1)
	{
		this->SetWindowText("Modify the configured parameters of slave unit");
		GetDlgItem(IDC_STATIC_SELECT_SLAVEUNIT)->SetWindowText("select slave unit");
		GetDlgItem(IDC_STATIC_FROSTA)->SetWindowText("A on defrosting curve:");//(-10~3)
		GetDlgItem(IDC_STATIC_FROST_B)->SetWindowText("B on defrosting curve:");//(-30~0)
		GetDlgItem(IDC_STATIC_FROST_END)->SetWindowText("Defrosting end time:");//(10~50)
		GetDlgItem(IDC_STATIC_FROST_TIME)->SetWindowText("Defrosting interval:");//(20~90)
		GetDlgItem(IDC_STATIC_FROST_RUNTIME)->SetWindowText("Defrosting time:");//(5~25)
		GetDlgItem(IDC_STATIC_FEETEMP)->SetWindowText("Anti-freeze temperature for cooling:");//(-10~5)
		GetDlgItem(IDC_STATIC_WINDTEMP)->SetWindowText("Winter Anti-freezing Temperature:");//需要翻译(5~10)
		GetDlgItem(IDC_STATIC_OBJECTHEAT)->SetWindowText("Target superheat degree:");//(0.0~10.0)

		GetDlgItem(ID_APPLY)->SetWindowText("Apply");
		GetDlgItem(IDOK)->SetWindowText("OK");
		GetDlgItem(IDCANCEL)->SetWindowText("Close");

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cmod_slave_cfg::show_data(int out_air, int out_air_s)
{
	CString tempstr;
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_delfrost_check_start_tp);
	m_edit_defa.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_delfrost_set_tp);
	m_edit_defb.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_delfrost_exit_tp);
	m_edit_defexit.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_delfrost_intertime);	
	m_edit_defint.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_delfrost_runtime);
	m_edit_time.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_cool_ant);
	m_edit_coolant.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_winter_ant);
	m_edit_winant.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_targetsuperhot/10);
	m_edit_obsup.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_ele_distension_valve1);
	m_s_valve1.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_ele_distension_valve2);
	m_s_valve2.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_ele_distension_valve3);
	m_s_valve3.SetWindowText(tempstr);
	tempstr.Format("%d",pdoc->airlist[out_air].indoor_air[out_air_s].s_ele_distension_valve4);
	m_s_valve4.SetWindowText(tempstr);
}

void Cmod_slave_cfg::OnEditchangeSlaveSel() 
{
	// TODO: Add your control notification handler code here
	slave_air_no=m_slavesel.GetCurSel();
	show_data(outairNo,slave_air_no); 
}

void Cmod_slave_cfg::OnSelchangeSlaveSel() 
{
	slave_air_no=m_slavesel.GetCurSel();
	show_data(outairNo,slave_air_no); 
	// TODO: Add your control notification handler code here
	
}

void Cmod_slave_cfg::OnApply() 
{
	// TODO: Add your control notification handler code here
	CString str;
	UpdateData(TRUE);
	slave_air_no=m_slavesel.GetCurSel();
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_delfrost_check_start_tp=m_int_defa;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_delfrost_set_tp=m_int_defb;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_delfrost_exit_tp=m_int_defexit;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_delfrost_intertime=m_int_defint;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_delfrost_runtime=m_int_deftime;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_cool_ant=m_int_coolant;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_winter_ant=m_int_winant;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_targetsuperhot1=m_int_obsup*10;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_ele_distension_valve11=m_s_valve11;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_ele_distension_valve21=m_s_valve21;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_ele_distension_valve31=m_s_valve31;
	pdoc->airlist[outairNo].indoor_air[slave_air_no].s_ele_distension_valve41=m_s_valve41;
	if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)
	{
//		if(MessageBox("确实要修改吗",NULL,MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
//			return;
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
		pdoc->airlist[outairNo].unit_no=slave_air_no;    //6号命令的地址号
	}
}

void Cmod_slave_cfg::OnOK() 
{
	// TODO: Add extra validation here
	OnApply();
	CDialog::OnOK();
}
