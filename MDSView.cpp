// MDSView.cpp : implementation of the CMDSView class
//

#include "stdafx.h"
#include "MDS.h"
#include "iostream"
#include "MDSDoc.h"
#include "MDSView.h"
#include "MainFrm.h"
#include "MESSAGEBOXDLG.h"
#include "modoutdlg.h"
#include "Specilcmddlg.h"
#include "Passworddlg.h"
#include "Alarmdlg.h"
#include "Testcodedlg.h"
#include "Inputstrdlg.h"
#include "compdlg.h"
#include "mod_slave_cfg.h"
#include <vector>
#include <fstream>   // 输出测试过程log
using namespace std;
#include <math.h>
#include "AddConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma comment( lib, "sentinelkeyw.lib" )
/////////////////////////////////////////////////////////////////////////////
// CMDSView
extern  CMSComm	m_comm1;
CMDSDoc* pdoc = NULL;
IMPLEMENT_DYNCREATE(CMDSView, CFormView)
extern CMDSApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMDSView construction/destruction

LPCTSTR lpRootPathName = "c:\\"; //取C盘
LPTSTR lpVolumeNameBuffer = new char[12];//磁盘卷标
DWORD nVolumeNameSize = 12;// 卷标的字符串长度
DWORD VolumeSerialNumber;//硬盘序列号
DWORD MaximumComponentLength;// 最大的文件长度
LPTSTR lpFileSystemNameBuffer = new char[10];// 存储所在盘符的分区类型的长指针变量
DWORD nFileSystemNameSize = 10;// 分区类型的长指针变量所指向的字符串长度
DWORD FileSystemFlags;// 文件系统的一此标志

/////////////////////////////////////////xu161226
float fTH1 = 0.0f, fTH2 = 0.0f, fTH3 = 0.0f, fTH4 = 0.0f, fTH6 = 0.0f, fTH7 = 0.0f, fTH8 = 0.0f, fTH9 = 0.0f, fTH10 = 0.0f, fTH11 = 0.0f, fTH12 = 0.0f, fTH13 = 0.0f, fTH14 = 0.0f, fELE1 = 0.0f, fELE2 = 0.0f;  //记录临时数据
float FTH1 = 0.0f, FTH2 = 0.0f, FTH3 = 0.0f, FTH4 = 0.0f, FTH6 = 0.0f, FTH7 = 0.0f, FTH8 = 0.0f, FTH9 = 0.0f, FTH10 = 0.0f, FTH11 = 0.0f, FTH12 = 0.0f, FTH13 = 0.0f, FTH14 = 0.0f, FELE1 = 0.0f, FELE2 = 0.0f;  //记录上电前数据
float FFTH1 = 0.0f, FFTH2 = 0.0f, FFTH3 = 0.0f, FFTH4 = 0.0f, FFTH6 = 0.0f, FFTH7 = 0.0f, FFTH8 = 0.0f, FFTH9 = 0.0f, FFTH10 = 0.0f, FFTH11 = 0.0f, FFTH12 = 0.0f, FFTH13 = 0.0f, FFTH14 = 0.0f, FFELE1 = 0.0f, FFELE2 = 0.0f;  //记录上电前数据
float fLP1 = 0.0f, fLP2 = 0.0f, fLP21 = 0.0f, fLP22 = 0.0f; // 系统1,2低压,对应s_lowpre, s_highpre;
float FLP1 = 0.0f, FLP2 = 0.0f, FLP21 = 0.0f, FLP22 = 0.0f; //记录上电前数据 
float FFLP1 = 0.0f, FFLP2 = 0.0f, FFLP21 = 0.0f, FFLP22 = 0.0f; //记录上电前数据 
float LP1_1 = 0.0f, LP1_2 = 0.0f, LP2_1 = 0.0f, LP2_2 = 0.0f;
float F_FTH2 = 0.0f, F_FTH10 = 0.0f, F_FTH4 = 0.0f, F_FTH14 = 0.0f, F_FTH12 = 0.0f, F_FFTH1 = 0.0f, F_FFTH9 = 0.0f, F_FFTH3 = 0.0f, F_FFTH13 = 0.0f, F_FFTH11 = 0.0f, F_FLP2 = 0.0f, F_FLP1 = 0.0f, F_FFLP1 = 0.0f, ZF_FFLP1 = 0.0f;
float F_FFTH2 = 0.0f, F_FFTH10 = 0.0f, F_FFTH4 = 0.0f, F_FFTH14 = 0.0f, F_FFTH12 = 0.0f, F_FFLP2 = 0.0f;
CString models_tag;
CString ordersum_text;
int iStep = 10;//步骤
int iEndStep = 811;//关闭所有动作
int ordersum = 0;
static int outputCount = 0;
int moshi = 0;
int timing = 0, timing1 = 0, timing2 = 0, timing3 = 0, timing4 = 0, timing5 = 0, timing6 = 0, timing7 = 0;
int timing8 = 0, timing9 = 0, timing10 = 0, timing11 = 0, timing12 = 0, timing13 = 0, timing14 = 0, timing15 = 0;
int iSpantime = 0;
int iCot = 0;
int cycle;
int stop = 0;
int errflag;
int exv1errflag;
int exv2errflag;
int exv3errflag;
int m_exv_button_ok = 0;
int m_button1 = 0;
int m_button2 = 0;
const int NUM_SENDCMD = 1000;
BOOL bSendCmd[NUM_SENDCMD] = { FALSE };
int iTime = 0;//距离时间
int iLastTime = 0, iFirstTime = 0;//上次记录时间
int iLastTime2 = 0;//记录持续发送exv命令的上次时间
CString strErr[31] = { "SYS1排温TH1","SYS1盘管出口温度TH9","SYS1吸气温度TH11","SYS1吸气压力","SYS1制热","制热模式TH6 TH7,检查接线","SYS1电子膨胀阀","SYS1进出水探头2","制热膨胀阀1接线","SYS2膨胀阀检查接线",
	"SYS1排温TH1","SYS1中盘温度TH3","SYS1盘管出口温度TH9","SYS1吸气温度TH11","SYS1吸气压力","SYS2排温TH2","SYS2中盘温度TH4","SYS2盘管出口温度TH10","SYS2吸气温度TH12","SYS2吸气压力",
	"制冷模式TH6/TH7,检查接线","1/2系统压力不平衡超过预期","制冷膨胀阀1接线","制冷膨胀阀2接线","制冷膨胀阀2关闭","制热膨胀阀2关闭","SYS2温度,请检查接线","SYS2存在压力","SYS1膨胀阀关闭,检查接线","SYS1电流异常","系统电流异常" };
void RecordTempData(int airNo);//记录n秒前的临时数据
vector<CString> vecErr; //错误记录
CString GetCurTime();
CFile logFile;//(CFile)NULL;

int GetSections(CStringArray& arrSection, CString iniFullPath);
CString getExeDir();



//////////////////////////////////////////


CMDSView::CMDSView()
	: CFormView(CMDSView::IDD)
{
	//{{AFX_DATA_INIT(CMDSView)
	m_inifalg = FALSE;
	m_outnumber = 0;
	m_recordtime = 5;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_tempbytecount = 0;
	m_readlenght = 0;
	m_showNo = 0;
	m_showNo_s = 0;
	m_listbkbrush = CreateSolidBrush((0, 255, 0));
	//	m_bkcolor=RGB(128,180,208);
	//	m_bkcolor=RGB(160,180,220);
	m_bkcolor = RGB(220, 160, 220);
	m_bkbrush = CreateSolidBrush(m_bkcolor);//63,186,137));
	m_bkbrush1 = CreateSolidBrush((0, 255, 0));
	m_bkbrush2 = CreateSolidBrush((255, 255, 0));
	m_bkbrush3 = CreateSolidBrush((0, 0, 255));
	m_bkbrush4 = CreateSolidBrush((255, 0, 0));
	timer1flag = 0;
	timer2flag = 0;
	timer3flag = 0;
	timer4flag = 0;
	timer5flag = 0;
	timer6flag = 0;
	timecount = 0;
	m_iUnitType = 0; //xu170106
	errflag = 0;
	s_funhavelow = _T("");
}

CMDSView::~CMDSView()
{
}

void CMDSView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMDSView)
	DDX_Control(pDX, IDC_EDIT_CFAN, m_edit_cfan);
	DDX_Control(pDX, IDC_EDIT_CHVALVE, m_edit_chvalve);
	DDX_Control(pDX, IDC_EDIT_RCVALVE, m_edit_revalve);
	DDX_Control(pDX, IDC_COMB_HOTSET, m_hotset);
	DDX_Control(pDX, IDC_EDIT_PUMP3, m_deit_pump3);
	DDX_Control(pDX, IDC_EDIT_PUMP2, m_edit_pump2);
	DDX_Control(pDX, IDC_MEDIA_S, m_edit_media_s);
	DDX_Control(pDX, IDC_MEDIA_M, m_edit_media_m);
	DDX_Control(pDX, IDC_CLR_RECORD, m_clr_record);
	DDX_Control(pDX, IDC_HP_S, m_hp_s1);
	DDX_Control(pDX, IDC_CODE1, m_ctrl1);
	DDX_Control(pDX, IDC_CODE2, m_ctrl2);
	//  DDX_Control(pDX, IDC_ELEVAVLE2_S, m_elevavle2_s);
	DDX_Control(pDX, IDC_ELEVAVLE_S, m_elevavle_s);
	DDX_Control(pDX, IDC_AIRVERSION_S, m_airversion_s);
	DDX_Control(pDX, IDC_AIRTYPE1_S, m_airtype1_s);
	DDX_Control(pDX, IDC_AHOT_S, m_ahot_s);
	DDX_Control(pDX, IDC_VIEWSPARA, m_viewspara);
	DDX_Control(pDX, IDC_VIEWMPARA, m_viewmpara);
	DDX_Control(pDX, IDC_AHOT, m_ahot);
	DDX_Control(pDX, IDC_EHOT, m_ehot);
	DDX_Control(pDX, IDC_4WV4, m_4wv4);
	DDX_Control(pDX, IDC_PUMP, m_pumpedit);
	DDX_Control(pDX, IDC_HEATSETIN, m_heatsetin);
	DDX_Control(pDX, IDC_COOLSETIN, m_coolsetin);
	DDX_Control(pDX, IDC_4WV3, m_4wv3);
	DDX_Control(pDX, IDC_OPAPPLY, m_opapplybt);
	DDX_Control(pDX, IDC_OPONOFF, m_oponoff);
	DDX_Control(pDX, IDC_OPMODE, m_opmode);
	DDX_Control(pDX, IDC_AIRNO_S, m_airno_s);
	DDX_Control(pDX, IDC_HICSUPERCOOL_S, m_hicsupercool_s);
	DDX_Control(pDX, IDC_TARGETSHOT_S, m_targetshot_s);
	DDX_Control(pDX, IDC_FACTSHOT_S, m_factshot_s);
	DDX_Control(pDX, IDC_TOTALNEEDHP_S, m_totalneedhp_s);
	DDX_Control(pDX, IDC_RUNMODE_S, m_runmode_s);
	DDX_Control(pDX, IDC_TP1_S, m_tp1_s);
	DDX_Control(pDX, IDC_TP2_S, m_tp2_s);
	DDX_Control(pDX, IDC_TP3_S, m_tp3_s);
	DDX_Control(pDX, IDC_TP4_S, m_tp4_s);
	DDX_Control(pDX, IDC_TP5_S, m_tp5_s);
	DDX_Control(pDX, IDC_TP6_S, m_tp6_s);
	DDX_Control(pDX, IDC_TP7_S, m_tp7_s);
	DDX_Control(pDX, IDC_TP8_S, m_tp8_s);
	DDX_Control(pDX, IDC_TP9_S, m_tp9_s);
	DDX_Control(pDX, IDC_TP10_S, m_tp10_s);
	DDX_Control(pDX, IDC_TP11_S, m_tp11_s);
	DDX_Control(pDX, IDC_TP12_S, m_tp12_s);
	DDX_Control(pDX, IDC_LOWPRE_S, m_lowpre_s);
	DDX_Control(pDX, IDC_HIGHPRE_S, m_highpre_s);
	DDX_Control(pDX, IDC_FOURVALVE2_S, m_fourvalve2_s);
	DDX_Control(pDX, IDC_FOURVALVE1_S, m_fourvalve1_s);
	//DDX_Control(pDX, IDC_FAN2_S, m_fan2_s);
	//DDX_Control(pDX, IDC_FAN1_S, m_fan1_s);
	DDX_Control(pDX, IDC_ELEDISTEN4_S, m_eledisten4_s);
	DDX_Control(pDX, IDC_ELEDISTEN3_S, m_eledisten3_s);
	DDX_Control(pDX, IDC_ELEDISTEN2_S, m_eledisten2_s);
	DDX_Control(pDX, IDC_ELEDISTEN1_S, m_eledisten1_s);
	//  DDX_Control(pDX, IDC_COMP6_S, m_comp6_s);
	//  DDX_Control(pDX, IDC_COMP5_S, m_comp5_s);
	//  DDX_Control(pDX, IDC_COMP4_S, m_comp4_s);
	//  DDX_Control(pDX, IDC_COMP3_S, m_comp3_s);
	DDX_Control(pDX, IDC_COMP2_S, m_comp2_s);
	DDX_Control(pDX, IDC_COMP1_S, m_comp1_s);
	DDX_Control(pDX, IDC_READCOMPTIME, m_readcomptimer);
	DDX_Control(pDX, IDC_MODOUTBTN, m_modoutbt);
	DDX_Control(pDX, IDC_APECILEBTN, m_apecilbt);
	DDX_Control(pDX, IDC_RECORDTIME, m_recordtimeedit);
	DDX_Control(pDX, IDC_OUTNUMBER, m_outnumberedit);
	DDX_Control(pDX, IDC_BAND, m_bandno);
	DDX_Control(pDX, IDC_RUNTIME, m_runtime);
	DDX_Control(pDX, IDC_TESTCODE, m_testcodebt);
	DDX_Control(pDX, IDC_HICSUPERCOOL, m_hicsupercool);
	DDX_Control(pDX, IDC_TARGETSHOT, m_targetshot);
	DDX_Control(pDX, IDC_FACTSHOT, m_factshot);
	DDX_Control(pDX, IDC_INICHECK, m_iniflagchk);
	DDX_Control(pDX, IDC_ALARMLIST, m_alarmlist);
	DDX_Control(pDX, IDC_ALARMLIST2, m_alarmlist2);
	DDX_Control(pDX, IDC_ALARMLIST3, m_alarmlist3);
	DDX_Control(pDX, IDC_COMNO, m_comNo);
	DDX_Control(pDX, IDC_AIRNO, m_airno);
	DDX_Control(pDX, IDC_TOTALNEEDHP, m_totalneedhp);
	DDX_Control(pDX, IDC_RUNMODE, m_runmode);
	DDX_Control(pDX, IDC_TP1, m_tp1);
	DDX_Control(pDX, IDC_TP2, m_tp2);
	DDX_Control(pDX, IDC_TP3, m_tp3);
	DDX_Control(pDX, IDC_TP4, m_tp4);
	DDX_Control(pDX, IDC_TP5, m_tp5);
	DDX_Control(pDX, IDC_TP6, m_tp6);
	DDX_Control(pDX, IDC_TP7, m_tp7);
	DDX_Control(pDX, IDC_TP8, m_tp8);
	DDX_Control(pDX, IDC_TP9, m_tp9);
	DDX_Control(pDX, IDC_TP10, m_tp10);
	DDX_Control(pDX, IDC_TP11, m_tp11);
	DDX_Control(pDX, IDC_TP12, m_tp12);
	DDX_Control(pDX, IDC_LOWPRE, m_lowpre);
	DDX_Control(pDX, IDC_INNUMBER, m_innuber);
	DDX_Control(pDX, IDC_HP, m_hp);
	DDX_Control(pDX, IDC_HIGHPRE, m_highpre);
	DDX_Control(pDX, IDC_FOURVALVE2, m_fourvalve2);
	DDX_Control(pDX, IDC_FOURVALVE1, m_fourvalve1);
	DDX_Control(pDX, IDC_BLDC_SPEED, m_edbldc_speed1);
	DDX_Control(pDX, IDC_BLDC_SPEED2, m_edbldc_speed2);
	DDX_Control(pDX, IDC_ELEDISTEN4, m_eledisten4);
	DDX_Control(pDX, IDC_ELEDISTEN3, m_eledisten3);
	DDX_Control(pDX, IDC_ELEDISTEN2, m_eledisten2);
	DDX_Control(pDX, IDC_ELEDISTEN1, m_eledisten1);
	DDX_Control(pDX, IDC_ESV1, m_esv1);
	DDX_Control(pDX, IDC_ESV2, m_esv2);
	DDX_Control(pDX, IDC_ESV3, m_esv3);
	DDX_Control(pDX, IDC_ESV4, m_esv4);
	DDX_Control(pDX, IDC_COMP2, m_comp2);
	DDX_Control(pDX, IDC_COMP1, m_comp1);
	DDX_Control(pDX, IDC_AIRVERSION, m_airversion);
	DDX_Control(pDX, IDC_AIRTYPE1, m_airtype1);
	DDX_Control(pDX, IDC_CONNECTBTN, m_connectbtn);
	DDX_Check(pDX, IDC_INICHECK, m_inifalg);
	DDX_Text(pDX, IDC_OUTNUMBER, m_outnumber);
	DDV_MinMaxInt(pDX, m_outnumber, 1, 32);
	DDX_Text(pDX, IDC_RECORDTIME, m_recordtime);
	DDV_MinMaxInt(pDX, m_recordtime, 0, 600);
	DDX_Control(pDX, IDC_MSCOMM1, m_comm1);
	DDX_Radio(pDX, IDC_RADIO1, m_iUnitType); //xu170106
	DDX_Control(pDX, IDC_EDIT_A, m_edit_a);
	DDX_Control(pDX, IDC_EDIT_B, m_edit_b);
	DDX_Control(pDX, IDC_EDIT_C, m_edit_c);
	DDX_Control(pDX, IDC_EDIT_D, m_edit_d);
	DDX_Control(pDX, IDC_EDIT_E, m_edit_e);
	DDX_Control(pDX, IDC_EDIT_F, m_edit_f);
	DDX_Control(pDX, IDC_EDIT_G, m_edit_g);
	DDX_Control(pDX, IDC_EDIT_H, m_edit_h);
	DDX_Control(pDX, IDC_EDIT_I, m_edit_i);
	DDX_Control(pDX, IDC_EDIT_J, m_edit_j);
	DDX_Control(pDX, IDC_EDIT_K, m_edit_k);
	DDX_Control(pDX, IDC_COMBO_CONFIGNAME, m_cmb_configname); //xu170214
	DDX_Control(pDX, IDC_BUTTON_SAVECONFIG, m_saveconfig);
	DDX_Control(pDX, IDC_BUTTON_DELCONFIG, m_delconfig);
	DDX_Control(pDX, IDC_BUTTON_ADDCONFIG, m_addconfig);
	DDX_Control(pDX, IDC_EDIT_USERINFO1, m_userinfo1);
	DDX_Control(pDX, IDC_EDIT_USERINFO2, m_userinfo2);
	DDX_Control(pDX, IDC_EDIT_USERINFO3, m_userinfo3);
	DDX_Control(pDX, IDC_EDIT_USERINFO4, m_userinfo4);
	DDX_Control(pDX, IDC_EDIT_USERINFO5, m_userinfo5);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_FUNHAVELOW, m_funhavelow);
	DDX_CBString(pDX, IDC_FUNHAVELOW, s_funhavelow);
	//  DDX_Control(pDX, IDC_EDIT_ELE1, m_ele1);
	//  DDX_Control(pDX, IDC_EDIT_ELE2, m_ele2);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_static_title);
	DDX_Control(pDX, IDC_EDIT_USERINFO7, m_userinfo7);
	DDX_Control(pDX, IDC_COMBO_YUN, m_cmb_yun);
	DDX_Control(pDX, IDC_EDIT_ELE1, m_ele1);
	DDX_Control(pDX, IDC_EDIT_ELE2, m_ele2);
	DDX_Control(pDX, IDC_HPRES1, m_highpre1);
	DDX_Control(pDX, IDC_HPRES2, m_highpre2);
	DDX_Control(pDX, IDC_EDIT_TH13, m_tph13);
	DDX_Control(pDX, IDC_EDIT_TH14, m_tph14);
	DDX_Control(pDX, IDC_EXV1_216, m_exv1_216);
	DDX_Control(pDX, IDC_EXV4_216, m_exv4_216);
	DDX_Control(pDX, IDC_HOT_EHEAT, m_edithot_eheat);
	DDX_Control(pDX, IDC_EXV2_216, m_exv2_216);
	DDX_Control(pDX, IDC_EXV5_216, m_exv5_216);
	DDX_Control(pDX, IDC_EXV3_216, m_exv3_216);
	DDX_Control(pDX, IDC_EXV6_216, m_exv6_216);
	DDX_Control(pDX, IDC_EDIT_X, m_edit_x);
	DDX_Control(pDX, IDC_BUTTON, m_button);
	DDX_Control(pDX, IDC_BUTTON1, m_button11);
	DDX_Control(pDX, IDC_BUTTON2, m_button21);
	//DDX_Control(pDX, IDC_CHECK3, m_check);
	DDX_Control(pDX, IDC_FAN_3, m_fan3);
	DDX_Control(pDX, IDC_FAN_4, m_fan4);

	DDX_Control(pDX, IDC_FTH1, m_ftp1);
	DDX_Control(pDX, IDC_FTH2, m_ftp2);
	DDX_Control(pDX, IDC_FTH3, m_ftp3);
	DDX_Control(pDX, IDC_FTH4, m_ftp4);
	DDX_Control(pDX, IDC_FTH5, m_ftp5);
	DDX_Control(pDX, IDC_FTH6, m_ftp6);
	DDX_Control(pDX, IDC_FTH7, m_ftp7);
	DDX_Control(pDX, IDC_FTH8, m_ftp8);
	DDX_Control(pDX, IDC_FTH9, m_ftp9);
	DDX_Control(pDX, IDC_FTH10, m_ftp10);
	DDX_Control(pDX, IDC_FTH11, m_ftp11);
	DDX_Control(pDX, IDC_FTH12, m_ftp12);

	DDX_Control(pDX, IDC_FLP, m_flp1);
	DDX_Control(pDX, IDC_FFAN1, m_ffan1);
	DDX_Control(pDX, IDC_FFAN2, m_ffan2);
	DDX_Control(pDX, IDC_4WV, m_f4wv1);
	DDX_Control(pDX, IDC_ELE3, m_fele1);
	DDX_Control(pDX, IDC_FCOMP3, m_fcomp3);
	DDX_Control(pDX, IDC_EDIT_M, m_edit_m);
	DDX_Control(pDX, IDC_EDIT_N, m_edit_n);
	//	DDX_Control(pDX, IDC_MODEL_CHANGE, m_mchange);
	DDX_Control(pDX, IDC_FTH13, m_ftp13);
	DDX_Control(pDX, IDC_FTH14, m_ftp14);
	DDX_Control(pDX, IDC_ELEDISTEN5, m_eledisten5);
	DDX_Control(pDX, IDC_ELEDISTEN6, m_eledisten6);
	DDX_Control(pDX, IDC_ELEDISTEN7, m_eledisten7);
	DDX_Control(pDX, IDC_ELEDISTEN8, m_eledisten8);
	DDX_Control(pDX, IDC_EDIT_O, m_edit_o);
	DDX_Control(pDX, IDC_COMBO_TEST, m_test_mode);
	DDX_Control(pDX, IDC_EDIT_GAOYA1, m_edit_gaoya1);
	DDX_Control(pDX, IDC_EDIT_GAOYA2, m_edit_gaoya2);
	DDX_Control(pDX, IDC_EDIT_GAOYAF1, m_edit_gaoyaf1);
	DDX_Control(pDX, IDC_EDIT_GAOYAF2, m_edit_gaoyaf2);
}

BEGIN_MESSAGE_MAP(CMDSView, CFormView)
	//{{AFX_MSG_MAP(CMDSView)
	ON_BN_CLICKED(IDC_INDOORBTN, OnIndoorbtn)
	ON_BN_CLICKED(IDC_MODOUTBTN, OnModoutbtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONNECTBTN, OnConnectbtn)
	ON_CBN_SELCHANGE(IDC_AIRNO, OnSelchangeAirno)
	ON_BN_CLICKED(IDC_APECILEBTN, OnApecilebtn)
	ON_CBN_SELCHANGE(IDC_COMNO, OnSelchangeComno)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_TESTCODE, OnTestcode)
	ON_BN_CLICKED(IDC_SLAVEOUTBTN, OnSlaveoutbtn)
	ON_CBN_SELCHANGE(IDC_BAND, OnSelchangeBand)
	ON_BN_CLICKED(IDC_READCOMPTIME, OnReadcomptime)
	ON_CBN_SELCHANGE(IDC_AIRNO_S, OnSelchangeAirnoS)
	ON_BN_CLICKED(IDC_OPAPPLY, OnOpapply)
	ON_BN_CLICKED(IDC_VIEWMPARA, OnViewmpara)
	ON_BN_CLICKED(IDC_VIEWSPARA, OnViewspara)
	ON_BN_CLICKED(IDC_CLR_RECORD, OnClrRecord)
	ON_MESSAGE(defEK_AC_MDSVIEW_MESSAGE, OnMdsViewMessage)
	ON_CBN_SELCHANGE(IDC_COMBO_CONFIGNAME, OnSelchangeComboConfigname)
	ON_BN_CLICKED(IDC_BUTTON_SAVECONFIG, OnButtonSaveconfig)
	ON_BN_CLICKED(IDC_BUTTON_ADDCONFIG, OnButtonAddconfig)
	ON_BN_CLICKED(IDC_BUTTON_DELCONFIG, OnButtonDelonfig)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_SAOMA, &CMDSView::OnBnClickedRadioSaoma)
	ON_BN_CLICKED(IDC_RADIO_HANDINPUT, &CMDSView::OnBnClickedRadioHandinput)
	ON_EN_CHANGE(IDC_EDIT_USERINFO5, &CMDSView::OnChangeEditUserinfo5)
	ON_CBN_SELCHANGE(IDC_FUNHAVELOW, &CMDSView::OnSelchangeFunhavelow)
	ON_BN_CLICKED(IDC_AUTOTEST, &CMDSView::OnBnClickedAutotest)
	ON_EN_SETFOCUS(IDC_EDIT_USERINFO5, &CMDSView::OnSetfocusEditUserinfo5)
	ON_BN_CLICKED(IDC_RADIO_GPS_SAOMA, &CMDSView::OnBnClickedRadioGpsSaoma)
	ON_BN_CLICKED(IDC_RADIO_GPS_HANDINPUT, &CMDSView::OnBnClickedRadioGpsHandinput)
	ON_BN_CLICKED(IDC_BUTTON, &CMDSView::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON1, &CMDSView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMDSView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMDSView::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO_TEST, &CMDSView::OnCbnSelchangeComboTest)
END_MESSAGE_MAP()

BOOL CMDSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}
LRESULT CMDSView::OnMdsViewMessage(WPARAM wParam, LPARAM lParam)
{
	SetMDSViewMessage();
	return TRUE;
}
void CMDSView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	pdoc = GetDocument();
	int i;

	CString tempstr;
	for (i = 0; i < pdoc->airnum; i++)
	{
		tempstr.Format("%d#", i);
		m_airno.InsertString(-1, tempstr);
	}
	m_outnumber = pdoc->airnum;
	tempstr.Format("%d", pdoc->airnum);
	m_outnumberedit.SetWindowText(tempstr);
	m_airno.SetCurSel(0);
	m_cmb_yun.SetCurSel(0);
	m_comNo.SetCurSel(pdoc->m_commNo - 1);
	m_bandno.SetCurSel(pdoc->m_commband);
	SetTimer(4, 1000, NULL);
	if (theApp.MYDOGISLIVE == 1)//MYDog	
	{
		SetTimer(5, 3000, NULL);//加密狗心跳定时;
	}
	HBITMAP hbmp1 = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), (LPCTSTR)IDB_BITMAP2, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_logobmp.Attach(hbmp1);
	if (theApp.m_bLanguage == 0)//2处要改
	{
		m_oponoff.AddString("关机");
		m_oponoff.AddString("开机");
		m_opmode.AddString("制冷");
		m_opmode.AddString("制热");
		m_opmode.AddString("热水");
		m_opmode.AddString("制冷+热水");
		m_opmode.AddString("制热+热水");
	}
	else if (theApp.m_bLanguage == 1)
	{
		m_oponoff.AddString("OFF");
		m_oponoff.AddString("ON");
		m_opmode.AddString("Cooling");
		m_opmode.AddString("Heating");
		m_opmode.AddString("Hot Water");
		m_opmode.AddString("Cooling+Hot Water");
		m_opmode.AddString("Heating+Hot Water");
	}
	m_opmode.SetCurSel(0);
	m_oponoff.SetCurSel(0);
	m_coolsetin.SetCurSel(9);
	m_heatsetin.SetCurSel(15);
	m_hotset.SetCurSel(20);

	//xu170215
	CStringArray arrSection;
	iniFullPath = getExeDir() + _T("\\Setting.config");
	GetSections(arrSection, iniFullPath);
	if (arrSection.GetSize() < 2)
	{
		WritePrivateProfileString("LANGSET", "CURRENT", "1", iniFullPath);
		CString strSection = "通用";
		WritePrivateProfileString(strSection, "A", "20", iniFullPath);
		WritePrivateProfileString(strSection, "B", "5", iniFullPath);
		WritePrivateProfileString(strSection, "C", "5", iniFullPath);
		WritePrivateProfileString(strSection, "D", "5", iniFullPath);
		WritePrivateProfileString(strSection, "E", "2", iniFullPath);
		WritePrivateProfileString(strSection, "F", "20", iniFullPath);
		WritePrivateProfileString(strSection, "G", "10", iniFullPath);
		WritePrivateProfileString(strSection, "H", "5", iniFullPath);
		WritePrivateProfileString(strSection, "I", "3", iniFullPath);
		WritePrivateProfileString(strSection, "J", "2", iniFullPath);
		WritePrivateProfileString(strSection, "K", "3", iniFullPath);
	}

	GetSections(arrSection, iniFullPath);
	CString strTemp;
	int iNo = 1;
	GetPrivateProfileString("LANGSET", "CURRENT", "1", strTemp.GetBuffer(20), 20, iniFullPath);
	iNo = atoi(strTemp);
	if (iNo<1 || iNo>arrSection.GetSize() - 1)
	{
		iNo = 1;
		WritePrivateProfileString("LANGSET", "CURRENT", "1", iniFullPath);
	}
	for (int j = 1; j != arrSection.GetSize(); j++)  //第2个段名开始
	{
		m_cmb_configname.AddString(arrSection.GetAt(j));
	}
	m_cmb_configname.SetCurSel(iNo - 1);
	CString curSection = arrSection.GetAt(iNo);
	GetPrivateProfileString(curSection, "A", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_a.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "B", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_b.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "C", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_c.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "D", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_d.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "E", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_e.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "F", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_f.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "G", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_g.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "H", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_x.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "I", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_m.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "J", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_n.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "K", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_h.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "L", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_j.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "M", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_i.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "N", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_o.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "V", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	yun_password = strTemp;
	//xu170213
	/*m_edit_a.SetWindowText("20");
	m_edit_b.SetWindowText("5");
	m_edit_c.SetWindowText("5");
	m_edit_d.SetWindowText("5");
	m_edit_e.SetWindowText("2");
	m_edit_f.SetWindowText("20");
	m_edit_g.SetWindowText("10");
	m_edit_h.SetWindowText("5");
	m_edit_i.SetWindowText("3");
	m_edit_j.SetWindowText("2");
	m_edit_k.SetWindowText("3");*/
	_ReadInputSet(m_bInput);
	_ReadTestmodeSet(m_bFunhavelow);
	m_test_mode.SetCurSel(m_bFunhavelow);
	if (m_bInput == 0)   //按钮选择
	{
		((CButton*)GetDlgItem(IDC_RADIO_SAOMA))->SetCheck(1);
		GetDlgItem(IDC_EDIT_USERINFO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERINFO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_USERINFO3)->EnableWindow(FALSE);
		//选择扫码输入(扫码命令)，INFO1,2,3禁止输入
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_HANDINPUT))->SetCheck(1);
		GetDlgItem(IDC_EDIT_USERINFO5)->EnableWindow(FALSE);
		//读取手动输入，INFO5禁止输入
	}
	_ReadInputGPSSet(m_bGPSInput);
	if (m_bGPSInput == 0)   //按钮选择
	{
		((CButton*)GetDlgItem(IDC_RADIO_GPS_SAOMA))->SetCheck(1);
		// GetDlgItem(IDC_EDIT_USERINFO7)->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_GPS_HANDINPUT))->SetCheck(1);
		// GetDlgItem(IDC_EDIT_USERINFO6)->EnableWindow(FALSE);
		 //读取手动输入，INFO5禁止输入
	}
	m_edit_a.EnableWindow(FALSE);
	m_edit_b.EnableWindow(FALSE);
	m_edit_c.EnableWindow(FALSE);
	m_edit_d.EnableWindow(FALSE);
	m_edit_e.EnableWindow(FALSE);
	m_edit_f.EnableWindow(FALSE);
	m_edit_g.EnableWindow(FALSE);
	m_edit_x.EnableWindow(FALSE);
	m_edit_m.EnableWindow(FALSE);
	m_edit_n.EnableWindow(FALSE);
	m_edit_h.EnableWindow(FALSE);
	m_edit_j.EnableWindow(FALSE);
	m_edit_i.EnableWindow(FALSE);
	m_edit_o.EnableWindow(FALSE);
	_ReadInputNAMESet(testname);
	m_userinfo4.SetWindowText(testname);
	theApp.p_MDSView_Message_Wnd = this;
	SetMDSViewMessage();
	GetBitmapHandle(IDB_CODEONBMP, m_open);
	GetBitmapHandle(IDB_CODEOFFBMP, m_off);
	//m_vt = &m_ctrl1;
}

/////////////////////////////////////////////////////////////////////////////
// CMDSView diagnostics

void CMDSView::SetMDSViewMessage()
{
	int onoff = m_oponoff.GetCurSel();
	int mode = m_opmode.GetCurSel();
	m_oponoff.DeleteString(1);
	m_oponoff.DeleteString(0);
	m_opmode.DeleteString(4);
	m_opmode.DeleteString(3);
	m_opmode.DeleteString(2);
	m_opmode.DeleteString(1);
	m_opmode.DeleteString(0);
	if (theApp.m_bLanguage == 0)
	{


		m_oponoff.AddString("关机");
		m_oponoff.AddString("开机");
		m_opmode.AddString("制冷");
		m_opmode.AddString("制热");
		m_opmode.AddString("热水");
		m_opmode.AddString("制冷+热水");
		m_opmode.AddString("制热+热水");

	}
	else if (theApp.m_bLanguage == 1)
	{


		m_oponoff.AddString("OFF");
		m_oponoff.AddString("ON");
		m_opmode.AddString("Cooling");
		m_opmode.AddString("Heating");
		m_opmode.AddString("Hot Water");
		m_opmode.AddString("Cooling+Hot Water");
		m_opmode.AddString("Heating+Hot Water");
	}
	m_oponoff.SetCurSel(onoff);
	m_opmode.SetCurSel(mode);
}


#ifdef _DEBUG
void CMDSView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMDSView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMDSDoc* CMDSView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDSDoc)));
	return (CMDSDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDSView message handlers

void CMDSView::OnIndoorbtn()
{
	// TODO: Add your control notification handler code here
	;
}

void CMDSView::MessAddString(CString valstring)
{
	m_alarmlist2.AddString(valstring);
	int nCount = m_alarmlist2.GetCount();
	if (nCount > 0)
		m_alarmlist2.SetCurSel(nCount - 1);
}
void CMDSView::OnModoutbtn()
{
	// TODO: Add your control notification handler code here
	Cmodoutdlg dlg;
	CPassworddlg pdlg;

	//	if(pdlg.DoModal()!=IDOK)
	//		return;

	dlg.m_airnum = pdoc->airnum;
	dlg.outairNo = m_showNo;
	if (dlg.DoModal() == IDOK)
	{
		//		pdoc->airnum=dlg.m_airnum;
		//		m_outnumber=pdoc->airnum;
		//		CString tempstr;
		//		for(int i=m_airno.GetCount()-1;i>=0;i--)
		//			m_airno.DeleteString(i);
		//		for(i=0;i<pdoc->airnum;i++)
		//		{
		//			tempstr.Format("%d#",i);
		//			m_airno.InsertString(-1,tempstr);
		//		}

		//		tempstr.Format("%d",pdoc->airnum);
		//		m_outnumberedit.SetWindowText(tempstr);

		//	m_airno.SetCurSel(0);
		;
	}
}
void CMDSView::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* frame;
	CString statusstr, tempstr;
	int i;
	frame = (CMainFrame*)AfxGetApp()->GetMainWnd();

	if (pdoc->m_connectflag == 1)//如果串口打开
	{
		if (nIDEvent == 1)
		{
			if (pdoc->queryopen == 1)//发送
			{
				int No = pdoc->queryAirNo;
				if ((pdoc->queryFunNo == 1) || (pdoc->queryFunNo == 3))
				{

					if (theApp.m_bLanguage == 0)
						statusstr.Format("与%d#机组通讯(%d)....", pdoc->queryAirNo, pdoc->queryFunNo);
					else if (theApp.m_bLanguage == 1)
						statusstr.Format("Communicating with unit %d# (%d)....", pdoc->queryAirNo, pdoc->queryFunNo);
				}
				else
				{
					if (theApp.m_bLanguage == 0)
						statusstr.Format("与%d#机组通讯(%d.%d)....", pdoc->queryAirNo, pdoc->queryFunNo, pdoc->airlist[No].in_groupquery);
					else if (theApp.m_bLanguage == 1)
						statusstr.Format("Communicating with unit %d# (%d)....", pdoc->queryAirNo, pdoc->queryFunNo, pdoc->airlist[No].in_groupquery);
				}				frame->m_wndStatusBar.SetPaneText(0, statusstr, TRUE);
				switch (pdoc->queryFunNo)
				{
				case 1:					//查询外机配置	
				//    if(theApp.m_bLanguage==0) //查询外机配置	
				//		frame->m_wndStatusBar.SetPaneText(2,"正在初始化....",TRUE);
				 // 	else if(theApp.m_bLanguage==1) 
				//		frame->m_wndStatusBar.SetPaneText(2,"Initializing....",TRUE);
					pdoc->query_out_set(No);
					break;
				case 2:					//查询内机配置
					if (theApp.m_bLanguage == 0)
						frame->m_wndStatusBar.SetPaneText(2, "正在初始化....", TRUE);
					else if (theApp.m_bLanguage == 1)
						frame->m_wndStatusBar.SetPaneText(2, "Initializing....", TRUE);
					pdoc->query_in_set(No);
					break;
				case 3:					//查询机组状态
					pdoc->query_air_status(No);
					break;
				case 4:					//查询外机运行参数
					pdoc->query_out_para(No);
					break;
				case 5:					//查询内机运行参数
					//SetFan1High(0, 1);
					pdoc->query_in_para(No);
					break;
				case 6:					//修改外机配置参数
					///pdoc->modify_out_para(No);
					break;
				case 7:					//开关部分内机
					pdoc->send_oc_inair(No);
					break;
				case 8:					//开关全部
					pdoc->send_oc_allinair(No);
					break;
				case 9:	//手动除霜特殊运行控制命令	
					pdoc->send_defro_spe(No);
					break;
				case 10://调试时开阀控制命令
					pdoc->seng_openvalve_spe(No);
					break;
				case 11://屏蔽内机通讯控制命令
					pdoc->seng_maskin_spe(No);
					break;
				case 23://进入测试模式
					pdoc->query_comp_time(No);
					break;
				case 24://手动设置开关量
					pdoc->clear_eePROM(No);
					break;
				case 25:					//查询测试模式的输出状态
					pdoc->query_test_status(No);
					break;
				case 26://退出测试模式
					pdoc->query_exit_mode(No);
					pdoc->sendcmdflag = 0;//20191010
					break;
				default:
					break;
				}
				pdoc->queryopen = 0;
			}
			else//响应
			{
				int reply = 0;		//功能代码
				if (m_readlenght == 0)//第一次读串口长度
				{
					m_tempbytecount = m_comm1.GetInBufferCount();
					m_readlenght = 1;
					return;
				}
				else
				{
					if (m_tempbytecount != m_comm1.GetInBufferCount())
					{
						m_tempbytecount = m_comm1.GetInBufferCount();
						return;
					}
					else
					{
						reply = pdoc->getcommdata(&Inputdata);//从串口得到数据，为0表示得到数据不正确
						m_tempbytecount = 0;
						m_readlenght = 0;
					}
				}
				if (reply != 0)
				{
					pdoc->m_errorcount = 0;
					if ((pdoc->queryFunNo == 1) || (pdoc->queryFunNo == 3))
					{
						if (theApp.m_bLanguage == 0)
							statusstr.Format("%d#机组正确应答(%d)", pdoc->queryAirNo, reply);
						else if (theApp.m_bLanguage == 1)
							statusstr.Format("%d# responds correctly (%d)", pdoc->queryAirNo, reply);
					}
					else
					{
						if (theApp.m_bLanguage == 0)
							statusstr.Format("%d#机组正确应答(%d.%d)", pdoc->queryAirNo, reply, pdoc->airlist[pdoc->queryAirNo].in_groupquery);
						else if (theApp.m_bLanguage == 1)
							statusstr.Format("%d# responds correctly (%d.%d)", pdoc->queryAirNo, reply, pdoc->airlist[pdoc->queryAirNo].in_groupquery);
					}
					frame->m_wndStatusBar.SetPaneText(1, statusstr, TRUE);
				}
				else
				{
					if ((pdoc->queryFunNo == 1) || (pdoc->queryFunNo == 3))
					{
						if (theApp.m_bLanguage == 0)
							statusstr.Format("%d#机组没有应答(%d)(%d次)", pdoc->queryAirNo, pdoc->queryFunNo, pdoc->m_errorcount);
						else if (theApp.m_bLanguage == 1)
							statusstr.Format("%d# failed to respond for(%d)(%d times)", pdoc->queryAirNo, pdoc->queryFunNo, pdoc->m_errorcount);
					}
					else
					{
						if (theApp.m_bLanguage == 0)
							statusstr.Format("%d#机组没有应答(%d.%d)(%d次)", pdoc->queryAirNo, pdoc->queryFunNo, pdoc->airlist[pdoc->queryAirNo].in_groupquery, pdoc->m_errorcount);
						else if (theApp.m_bLanguage == 1)
							statusstr.Format("%d# failed to respond for(%d.%d)(%d times)", pdoc->queryAirNo, pdoc->queryFunNo, pdoc->airlist[pdoc->queryAirNo].in_groupquery, pdoc->m_errorcount);
					}
					frame->m_wndStatusBar.SetPaneText(1, statusstr, TRUE);
				}
				int do_ok = 0;		//处理是否正确1--正确
				switch (reply)
				{
					/****************************************************/
					/*功能1、2为初始化查询  							*/
					/*													*/
					/****************************************************/
				case 1:
					do_ok = pdoc->reply_out_set(&Inputdata);
					if (do_ok == 1)
					{
						if (pdoc->sendcmdflag != 1)
						{
							//if(pdoc->airlist[pdoc->queryAirNo].slave_ini==1)
							//{
								//if(pdoc->airlist[pdoc->queryAirNo].in_num>0)
								//{
								//	CTime t = CTime::GetCurrentTime();
								//	pdoc->queryFunNo=2;//查询从机
								///*	for(i=0;i<pdoc->airlist[pdoc->queryAirNo].in_num;i++)
								//	{
								//		tempstr.Format("%2.2d%.2d%.2d_%.2d\.txt",t.GetYear(),t.GetMonth(),t.GetDay(),i+1);
								//		if(pdoc->m_file[i+1].Open(tempstr,CFile::modeReadWrite|CFile::shareDenyNone,NULL))
								//		{
								//			pdoc->m_file[i+1].SeekToEnd();
								//		}
								//		else
								//		{
								//			pdoc->m_file[i+1].Open(tempstr,CFile::modeReadWrite|CFile::modeCreate |CFile::shareDenyNone,NULL);
								//			pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\n机组型号:%s\r\n机组编号:%s\r\n软件版本%s\r\nF1~3---风机1~3  S1~2---电磁阀1~2  C0~3---定压机0~3 Wa~d---四通阀a~d  E1~4---电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n",t.GetYear(),t.GetMonth(),t.GetDay(),i,valstr1,valstr2,theApp.SoftVer);
								//		//	pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\nF1~3---风机1~3  S1~2---电磁阀1~2  C0~3---定压机0~3 Wa~d---四通阀a~d  E1~4---电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n",t.GetYear(),t.GetMonth(),t.GetDay(),i);
								//			pdoc->m_recordstr+="\r\n时间    模式 F1 F2 C1 C2 C3 Wa Wb   E1   E2   E3   E4   Needhp  TSH   lowP1   过热度1  LowP2  过热度2   TH1    TH2    TH3    TH4    TH5    TH6   TH7    TH8    TH9   TH10   TH11   TH12    电流1   电流2 \r\n";
								//			CArchive ar(&pdoc->m_file[i+1],CArchive::store);
								//			ar.WriteString(pdoc->m_recordstr);
								//			ar.Close();										
								//		}
								//	}*/
								//}
								//else
								//{
							pdoc->queryFunNo = 1;
							pdoc->queryAirNo++;
							if (pdoc->queryAirNo >= pdoc->airnum)
							{
								pdoc->queryAirNo = 0;
								pdoc->queryFunNo = 3;
								pdoc->m_startflag = 1;	//初始化完成
								if (theApp.m_bLanguage == 0)
									frame->m_wndStatusBar.SetPaneText(2, "初始化完成", TRUE);
								else if (theApp.m_bLanguage == 1)
									frame->m_wndStatusBar.SetPaneText(2, "Initialization completed", TRUE);
							}
							//}
						//}
						}
					}
					break;
				case 2:
					do_ok = pdoc->reply_in_set(&Inputdata);
					if (do_ok == 1)
					{
						if (pdoc->sendcmdflag != 1)
						{
							pdoc->queryFunNo = 1;
							pdoc->queryAirNo++;
							if (pdoc->queryAirNo >= pdoc->airnum)
							{
								pdoc->queryAirNo = 0;
								pdoc->queryFunNo = 3;
								pdoc->m_startflag = 1;	//初始化完成
								if (theApp.m_bLanguage == 0)
									frame->m_wndStatusBar.SetPaneText(2, "初始化完成", TRUE);
								else if (theApp.m_bLanguage == 1)
									frame->m_wndStatusBar.SetPaneText(2, "Initialization completed", TRUE);

								refreshslave_sel(m_showNo);	//初始化完成后，设置从机的选择框
							}
						}
					}
					break;
					/****************************************************/
					/*功能3、4、5为常规循环查询							*/
					/*													*/
					/****************************************************/
				case 3:
					do_ok = pdoc->reply_air_status(&Inputdata);
					if (do_ok == 1)
					{
						if (pdoc->sendcmdflag != 1)//如果改为发送控制命令，不在改变功能号
						{
							//if(pdoc->airlist[pdoc->queryAirNo].in_num>0)
							//	pdoc->queryFunNo=4;
							//else
							//{
							pdoc->queryFunNo = 1;
							pdoc->queryAirNo++;
							if (pdoc->queryAirNo >= pdoc->airnum)
							{
								pdoc->queryAirNo = 0;
								pdoc->queryFunNo = 25;
							}
							//}
						}
					}
					break;
				case 4:
					do_ok = pdoc->reply_out_para(&Inputdata);
					if (do_ok == 1)
					{
						if (pdoc->sendcmdflag != 1)
						{
							pdoc->queryFunNo = 25;
							pdoc->queryAirNo++;
							if (pdoc->queryAirNo >= pdoc->airnum)//循环查询
							{
								pdoc->queryAirNo = 0;
							}
						}
					}
					break;
				case 5:
					//do_ok=pdoc->reply_in_para(&Inputdata);
					//if(do_ok==1)
					//{
					if (pdoc->sendcmdflag != 1)
					{
						pdoc->queryFunNo = 25;
						pdoc->queryAirNo++;
						if (pdoc->queryAirNo >= pdoc->airnum)//循环查询
						{
							pdoc->queryAirNo = 0;
						}
					}
					//}
					break;
					/****************************************************/
					/*功能6---N为控制命令   							*/
					/*													*/
					/****************************************************/
				case 6:				//正确应答后，恢复常规查询号
					do_ok = pdoc->reply_mofify_out_para(&Inputdata);
					pdoc->sendcmdflag = 0;
					if (pdoc->queryFunNo1 == 6)//为了避免一直发7号命令。
						pdoc->queryFunNo1 = 1;
					pdoc->queryFunNo = pdoc->queryFunNo1;
					pdoc->queryAirNo = pdoc->queryAirNo1;
					break;
				case 23://进入测试模式
					//if(reply==23)
					//	do_ok=pdoc->reply_comp_time(&Inputdata);
					//if(do_ok==1)
					//if(pdoc->sendcmdflag!=1)//如果改为发送控制命令，不在改变功能号
					//{
					pdoc->queryFunNo = 1;
					pdoc->queryAirNo = 0;
					//}
					break;
				case 7:
					;
				case 8:
					;
				case 9:
					;
				case 10:
					;
				case 25:
					do_ok = pdoc->reply_test_status(&Inputdata);
					if (do_ok == 1)
					{
						if (pdoc->sendcmdflag != 1)
						{
							pdoc->queryFunNo = 1;
							pdoc->queryAirNo = 0;
						}
					}
					break;
				case 24:
					pdoc->sendcmdflag = 0;
					if (pdoc->queryFunNo1 == 24)//为了避免一直发7号命令。
						pdoc->queryFunNo1 = 1;
					pdoc->queryFunNo = pdoc->queryFunNo1;
					pdoc->queryAirNo = pdoc->queryAirNo1;
					break;
				case 0:					//通讯错误处理
					pdoc->m_errorcount++;
					if (pdoc->m_errorcount >= 15)//如果连续15次没有正确应答，跳过当前机组查询下一台
					{					//但若是正在初始化时，则复位从头开始查询
						pdoc->m_errorcount = 0;
						if (pdoc->m_startflag == 1)//完成初始化后
						{
							if (pdoc->sendcmdflag == 1)//为6、7、8查询错误时，恢复常规查询号
							{
								pdoc->queryFunNo = pdoc->queryFunNo1;
								pdoc->queryAirNo = pdoc->queryAirNo1;
								pdoc->sendcmdflag = 0;
							}
							else
							{
								if (pdoc->queryFunNo == 3)//3号命令错误处理
								{
									if (pdoc->airlist[pdoc->queryAirNo].in_num == 0)  //没有接从机
									{
										pdoc->queryAirNo++;
										if (pdoc->queryAirNo >= pdoc->airnum)
										{
											pdoc->queryAirNo = 0;
										}
									}
									else
									{
										pdoc->queryFunNo = 4;
									}
								}
								else//4号命令
								{
									pdoc->airlist[pdoc->queryAirNo].in_groupquery++;
									if (pdoc->airlist[pdoc->queryAirNo].in_groupquery >= pdoc->airlist[pdoc->queryAirNo].in_num)
									{
										pdoc->airlist[pdoc->queryAirNo].in_groupquery = 0;
										pdoc->queryAirNo++;
										if (pdoc->queryAirNo >= pdoc->airnum)
										{
											pdoc->queryAirNo = 0;
										}
										pdoc->queryFunNo = 3;
									}

								}
							}
						}
						else//正在初始化时
						{
							pdoc->airlist[pdoc->queryAirNo].in_groupquery = 0;
							pdoc->queryAirNo = 0;
							pdoc->queryFunNo = 1;
						}
					}
					break;
				default:
					break;
				}
				pdoc->queryopen = 1;
			}
		}
		if (nIDEvent == 2)//更新显示数据
		{
			int i;
			showdata(m_showNo);
			//运行时间
			CTime t = CTime::GetCurrentTime();
			CTimeSpan runtime = t - pdoc->m_starttime;
			int ih, im, is;
			ih = runtime.GetTotalHours();
			im = runtime.GetMinutes();
			is = runtime.GetSeconds();
			tempstr.Format("%d小时%d分%d秒", ih, im, is);
			m_runtime.SetWindowText(tempstr);

			if (pdoc->m_startflag == 1)
			{
				timecount++;
				UpdateData(TRUE);
				if ((m_recordtime > 600) || (m_recordtime < 0))
				{
					m_recordtimeedit.SetWindowText("5");
					m_recordtime = 5;
				}
				else if ((timecount >= m_recordtime) && (m_recordtime >= 5))
				{

					timecount = 0;
					for (i = 0; i < pdoc->airnum; i++)
					{
						/*tempstr.Format("%2.2d%.2d%.2d_%.2d\.txt",t.GetYear(),t.GetMonth(),t.GetDay(),i);
						if(strcmp(pdoc->m_file[i].GetFileName(),tempstr))//比较文件名，如果到了第二天，就关闭今天的文件，重新创建记录文件
						{
							pdoc->m_file[i].Close();
							pdoc->m_file[i].Open(tempstr,CFile::modeReadWrite|CFile::modeCreate |CFile::shareDenyNone,NULL);
							pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\n软件版本%s\r\nF1~3---风机1~3  S1~2---电磁阀1~2  C0~3---定压机0~3 Wa~d---四通阀a~d  E1~4---电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n",t.GetYear(),t.GetMonth(),t.GetDay(),i,theApp.SoftVer);
							//pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\n F1~3---风机1~3  S1~2---电磁阀1~2  C0~3---定压机0~3 Wa~d---四通阀a~d  E1~4---电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n",t.GetYear(),t.GetMonth(),t.GetDay(),i);
							pdoc->m_recordstr+="\r\n时间    模式 F1 F2 C1 C2 C3 Wa Wb    E1   E2   E3   E4   Needhp  TSH  lowP1  过热度1  LowP2  过热度2   TH1    TH2    TH3    TH4    TH5    TH6   TH7    TH8    TH9   TH10    TH11   TH12    电流1   电流2   机组型号     机组编号\r\n";
							CArchive ar(&pdoc->m_file[i],CArchive::store);
							ar.WriteString(pdoc->m_recordstr);
							ar.Close();
						}*/
						recorddata(i);
						//    int	m_showNo_s=m_airno_s.GetCurSel();
							/*if(pdoc->airlist[0].in_num>0)
							{
								for(i=0;i<pdoc->airlist[0].in_num;i++)
									showdata_slave(m_showNo,i);
							}*/

					}
					/*	if(pdoc->airlist[pdoc->queryAirNo].in_num>0)
						{
							for(i=0;i<pdoc->airlist[pdoc->queryAirNo].in_num;i++)
							{
								tempstr.Format("%2.2d%.2d%.2d_%.2d\.txt",t.GetYear(),t.GetMonth(),t.GetDay(),i+1);
								if(strcmp(pdoc->m_file[i+1].GetFileName(),tempstr))
								{
									pdoc->m_file[i+1].Close();
									pdoc->m_file[i+1].Open(tempstr,CFile::modeReadWrite|CFile::modeCreate |CFile::shareDenyNone,NULL);
									pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\n软件版本%s\r\nF1~3---风机1~3  S1~2---电磁阀1~2  C0~3---定压机0~3 Wa~d---四通阀a~d  E1~4---电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n",t.GetYear(),t.GetMonth(),t.GetDay(),i,theApp.SoftVer);
								//	pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\n F1~3---风机1~3  S1~2---电磁阀1~2  C0~3---定压机0~3 Wa~d---四通阀a~d  E1~4---电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n",t.GetYear(),t.GetMonth(),t.GetDay(),i);
									pdoc->m_recordstr+="\r\n时间    模式 F1 F2 C1 C2 C3 Wa Wb   E1   E2   E3   E4   Needhp  TSH   lowP1   过热度1  LowP2  过热度2   TH1    TH2    TH3    TH4    TH5    TH6   TH7    TH8    TH9   TH10   TH11   TH12    机组型号     机组编号\r\n";
									CArchive ar(&pdoc->m_file[i+1],CArchive::store);
									ar.WriteString(pdoc->m_recordstr);
									ar.Close();
								}
								recorddata_slave(i);
							}
						}*/
				}
			}
		}
		if (nIDEvent == 3)//更新显示错误
		{
			if (pdoc->m_startflag != 1)	//初始化未完成
				goto End0;
			showerror(m_showNo);
			showcomptime(m_showNo);
		}
		if (nIDEvent == 6)//xu161223 命令执行顺序
		{
			if (pdoc->m_startflag != 1)	//初始化未完成
				goto End0;
			int airNo = 0; //默认为0号外机
//TEST END*/
			int temparr[134] =
			{
			-65,
			-64,
			-63,
			-62,
			-61,
			-60,
			-59,
			-58,
			-57,
			-56,
			-55,
			-54,
			-53,
			-52,
			-51,
			-50,
			-49,
			-48,
			-47,
			-46,
			-45,
			-44,
			-43,
			-42,
			-41,
			-40,
			-39,
			-38,
			-37,
			-36,
			-35,
			-34,
			-33,
			-32,
			-31,
			-30,
			-29,
			-28,
			-27,
			-26,
			-25,
			-24,
			-23,
			-22,
			-21,
			-20,
			-19,
			-18,
			-17,
			-16,
			-15,
			-14,
			-13,
			-12,
			-11,
			-10,
			-9,
			-8,
			-7,
			-6,
			-5,
			-4,
			-3,
			-2,
			-1,
			0,
			1,
			2,
			3,
			4,
			5,
			6,
			7,
			8,
			9,
			10,
			11,
			12,
			13,
			14,
			15,
			16,
			17,
			18,
			19,
			20,
			21,
			22,
			23,
			24,
			25,
			26,
			27,
			28,
			29,
			30,
			31,
			32,
			33,
			34,
			35,
			36,
			37,
			38,
			39,
			40,
			41,
			42,
			43,
			44,
			45,
			46,
			47,
			48,
			49,
			50,
			51,
			52,
			53,
			54,
			55,
			56,
			57,
			58,
			59,
			60,
			61,
			62,
			63,
			64,
			65,
			66,
			67,
			68 };
			float pararr[134] =
			{
			-0.49,
			-0.46,
			-0.42,
			-0.39,
			-0.36,
			-0.32,
			-0.28,
			-0.25,
			-0.2,
			-0.16,
			-0.12,
			-0.07,
			-0.02,
			0.03,
			0.08,
			0.13,
			0.19,
			0.25,
			0.31,
			0.37,
			0.44,
			0.51,
			0.58,
			0.65,
			0.73,
			0.8,
			0.88,
			0.97,
			1.05,
			1.14,
			1.24,
			1.33,
			1.43,
			1.53,
			1.64,
			1.75,
			1.86,
			1.98,
			2.1,
			2.22,
			2.35,
			2.48,
			2.61,
			2.75,
			2.89,
			3.04,
			3.19,
			3.35,
			3.51,
			3.67,
			3.84,
			4.02,
			4.19,
			4.38,
			4.57,
			4.76,
			4.96,
			5.16,
			5.37,
			5.58,
			5.8,
			6.03,
			6.26,
			6.5,
			6.74,
			6.99,
			7.24,
			7.5,
			7.77,
			8.04,
			8.32,
			8.61,
			8.9,
			9.2,
			9.5,
			9.82,
			10.14,
			10.46,
			10.8,
			11.14,
			11.49,
			11.85,
			12.21,
			12.58,
			12.96,
			13.35,
			13.75,
			14.15,
			14.56,
			14.99,
			15.42,
			15.85,
			16.3,
			16.76,
			17.22,
			17.7,
			18.18,
			18.68,
			19.18,
			19.69,
			20.21,
			20.75,
			21.29,
			21.84,
			22.41,
			22.98,
			23.57,
			24.16,
			24.77,
			25.39,
			26.01,
			26.65,
			27.31,
			27.97,
			28.65,
			29.33,
			30.03,
			30.75,
			31.47,
			32.21,
			32.96,
			33.72,
			34.5,
			35.29,
			36.09,
			36.91,
			37.74,
			38.59,
			39.45,
			40.32,
			41.21,
			42.11,
			43.04,
			43.97 };
			CString strRight = _T("√ "), strWrong = _T("× ");
			if (iStep == 10)
			{
				//制冷启动
				if (/*pdoc->airlist[airNo].s_runmode!=1 &&*/ !bSendCmd[iStep - 1])
				{
					iFirstTime = GetTickCount();
					iLastTime = GetTickCount();

					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 测试开始\r\n");

					outfile.Close();
					bSendCmd[iStep - 1] = TRUE;
					//  if(pdoc->airlist[airNo].s_waterswitch==1)//0闭合1断开
					   //{
					   //	MessAddString("水流开关断开");
					   //	errflag=1;
					   //	iStep=620;
					   //}
				}
				else //if(pdoc->airlist[airNo].s_runmode==1 || pdoc->airlist[airNo].s_runmode==2)//启动成功
				{
					iStep += 10;
					///iStep = 580;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime());
					if (m_iUnitType == 4) //xu170511 add 热泵
						outfile.WriteString(" 上电前数据:\r\n");
					else
						outfile.WriteString(" 上电前数据:\r\n");

					//记录上电前数据 xu170215
					FTH1 = pdoc->airlist[airNo].s_tp1;
					FTH2 = pdoc->airlist[airNo].s_tp2;
					FTH3 = pdoc->airlist[airNo].s_tp3;
					FTH4 = pdoc->airlist[airNo].s_tp4;
					FTH6 = pdoc->airlist[airNo].s_tp6;
					FTH7 = pdoc->airlist[airNo].s_tp7;
					FTH8 = pdoc->airlist[airNo].s_tp8;
					FTH9 = pdoc->airlist[airNo].s_tp9;
					FTH10 = pdoc->airlist[airNo].s_tp10;
					FTH11 = pdoc->airlist[airNo].s_tp11;
					FTH12 = pdoc->airlist[airNo].s_tp12;
					FTH13 = pdoc->airlist[airNo].s_tp13;
					FTH14 = pdoc->airlist[airNo].s_tp14;
					FLP1 = pdoc->airlist[airNo].s_lowpre;
					FLP22 = pdoc->airlist[airNo].s_lowpre2;
					FLP2 = pdoc->airlist[airNo].s_highpre;
					FLP21 = pdoc->airlist[airNo].s_highpre2;
					FELE1 = pdoc->airlist[airNo].s_ele;
					FELE2 = pdoc->airlist[airNo].s_ele2;

					FFTH1 = pdoc->airlist[airNo].f_s_tp1;
					FFTH2 = pdoc->airlist[airNo].f_s_tp2;
					FFTH3 = pdoc->airlist[airNo].f_s_tp3;
					FFTH4 = pdoc->airlist[airNo].f_s_tp4;
					FFTH6 = pdoc->airlist[airNo].f_s_tp6;
					FFTH7 = pdoc->airlist[airNo].f_s_tp7;
					FFTH8 = pdoc->airlist[airNo].f_s_tp8;
					FFTH9 = pdoc->airlist[airNo].f_s_tp9;
					FFTH10 = pdoc->airlist[airNo].f_s_tp10;
					FFTH11 = pdoc->airlist[airNo].f_s_tp11;
					FFTH12 = pdoc->airlist[airNo].f_s_tp12;
					FFLP2 = pdoc->airlist[airNo].f_s_highpre;
					FFLP1 = pdoc->airlist[airNo].f_s_lowpre;
					FFELE1 = pdoc->airlist[airNo].f_s_ele1;
					FFELE2 = pdoc->airlist[airNo].f_s_ele2;
					tempstr.Format("TH1=%.1f,TH2=%.1f,TH3=%.1f,TH4=%.1f,TH6=%.1f,TH7=%.1f,TH8=%.1f,TH9=%.1f,\r\nTH10=%.1f,TH11=%.1f,TH12=%.1f,TH13=%.1f,TH14=%.1f,LP1=%.1f,LP2=%.1f,LP21=%.1f,LP22=%.1f,ELE1=%.1f,ELE2=%.1f\r\n,FTH1=%.1f,FTH2=%.1f,FTH3=%.1f,FTH4=%.1f,FTH6=%.1f,FTH7=%.1f,FTH8=%.1f,FTH9=%.1f,\r\nFTH10=%.1f,FTH11=%.1f,FTH12=%.1f,FLP1=%.1f,FLP2=%.1f,FELE1=%.1f,FELE2=%.1f,\r\n",
						pdoc->airlist[airNo].s_tp1, pdoc->airlist[airNo].s_tp2, pdoc->airlist[airNo].s_tp3, pdoc->airlist[airNo].s_tp4, pdoc->airlist[airNo].s_tp6, pdoc->airlist[airNo].s_tp7,
						pdoc->airlist[airNo].s_tp8, pdoc->airlist[airNo].s_tp9, pdoc->airlist[airNo].s_tp10, pdoc->airlist[airNo].s_tp11, pdoc->airlist[airNo].s_tp12, pdoc->airlist[airNo].s_tp13, pdoc->airlist[airNo].s_tp14,
						pdoc->airlist[airNo].s_lowpre, pdoc->airlist[airNo].s_highpre, pdoc->airlist[airNo].s_lowpre2, pdoc->airlist[airNo].s_highpre2, pdoc->airlist[airNo].s_ele, pdoc->airlist[airNo].s_ele2,
						pdoc->airlist[airNo].f_s_tp1, pdoc->airlist[airNo].f_s_tp2, pdoc->airlist[airNo].f_s_tp3, pdoc->airlist[airNo].f_s_tp4, pdoc->airlist[airNo].f_s_tp6, pdoc->airlist[airNo].f_s_tp7,
						pdoc->airlist[airNo].f_s_tp8, pdoc->airlist[airNo].f_s_tp9, pdoc->airlist[airNo].f_s_tp10, pdoc->airlist[airNo].f_s_tp11, pdoc->airlist[airNo].f_s_tp12, pdoc->airlist[airNo].f_s_lowpre, pdoc->airlist[airNo].f_s_highpre, pdoc->airlist[airNo].f_s_ele1, pdoc->airlist[airNo].f_s_ele2);
					outfile.WriteString(tempstr);
					outfile.Close();
				}
			}
			if (iStep == 20 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 10;
				iLastTime = GetTickCount();
				MessAddString("检测程序版本");
				//tempstr.Format("%.1f", (float)pdoc->airlist[airNo].out_version / 10);
				int v1, v2, v3;
				v3 = pdoc->airlist[airNo].out_version / 10;
				v2 = pdoc->airlist[airNo].out_version % 10;
				v1 = pdoc->airlist[airNo].out_version_end;
				tempstr.Format("%.1d.%.1d.%.1d", v3, v2, v1);
				CString strTemp;
				m_edit_g.GetWindowText(strTemp);
				if (tempstr != strTemp)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 程序版本错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "程序版本");
					vecErr.push_back(strWrong + "程序版本");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 程序版本正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "程序版本");
					vecErr.push_back(strRight + "程序版本");
				}
			}
			if (iStep == 30 && (GetTickCount() - iLastTime) >= 50) //系统电加热过载是否闭合
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 10;
				iLastTime = GetTickCount();
				MessAddString("检测拨码是否与机组型号一致");
				if (pdoc->airlist[airNo].sw11 == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.1拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.1拨码");
					vecErr.push_back(strWrong + "SW1.1拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.1拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.1拨码");
					vecErr.push_back(strRight + "SW1.1拨码");
				}
				if (pdoc->airlist[airNo].sw12 == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.2拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.2拨码");
					vecErr.push_back(strWrong + "SW1.2拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.2拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.2拨码");
					vecErr.push_back(strRight + "SW1.2拨码");
				}
				if (pdoc->airlist[airNo].sw13 == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.3拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.3拨码");
					vecErr.push_back(strWrong + "SW1.3拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.3拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.3拨码");
					vecErr.push_back(strRight + "SW1.3拨码");
				}
				if (pdoc->airlist[airNo].sw14 == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.4拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.4拨码");
					vecErr.push_back(strWrong + "SW1.4拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.4拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.4拨码");
					vecErr.push_back(strRight + "SW1.4拨码");
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					if (pdoc->airlist[airNo].sw15 == 0)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.5拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "SW1.5拨码");
						vecErr.push_back(strWrong + "SW1.5拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.5拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "SW1.5拨码");
						vecErr.push_back(strRight + "SW1.5拨码");
					}
				}
				else
				{
					if (pdoc->airlist[airNo].sw15 == 1)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.5拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "SW1.5拨码");
						vecErr.push_back(strWrong + "SW1.5拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.5拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "SW1.5拨码");
						vecErr.push_back(strRight + "SW1.5拨码");
					}
				}
				if (pdoc->airlist[airNo].sw16 == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.6拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.6拨码");
					vecErr.push_back(strWrong + "SW1.6拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.6拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.6拨码");
					vecErr.push_back(strRight + "SW1.6拨码");
				}
				if (pdoc->airlist[airNo].sw17 == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.7拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.7拨码");
					vecErr.push_back(strWrong + "SW1.7拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.7拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.7拨码");
					vecErr.push_back(strRight + "SW1.7拨码");
				}
				if (pdoc->airlist[airNo].sw18 == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.8拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "SW1.8拨码");
					vecErr.push_back(strWrong + "SW1.8拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" SW1.8拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "SW1.8拨码");
					vecErr.push_back(strRight + "SW1.8拨码");
				}
				MessAddString("检测副板拨码是否与机组型号一致");
				if (pdoc->airlist[airNo].sw11_f == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.1拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "副板SW1.1拨码");
					vecErr.push_back(strWrong + "副板SW1.1拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.1拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "副板SW1.1拨码");
					vecErr.push_back(strRight + "副板SW1.1拨码");
				}
				if (pdoc->airlist[airNo].sw12_f == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.2拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "副板SW1.2拨码");
					vecErr.push_back(strWrong + "副板SW1.2拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.2拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "副板SW1.2拨码");
					vecErr.push_back(strRight + "副板SW1.2拨码");
				}
				if (pdoc->airlist[airNo].sw13_f == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.3拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "副板SW1.3拨码");
					vecErr.push_back(strWrong + "副板SW1.3拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.3拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "副板SW1.3拨码");
					vecErr.push_back(strRight + "副板SW1.3拨码");
				}
				if (pdoc->airlist[airNo].sw14_f == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.4拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "副板SW1.4拨码");
					vecErr.push_back(strWrong + "副板SW1.4拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.4拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "副板SW1.4拨码");
					vecErr.push_back(strRight + "副板SW1.4拨码");
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					if (pdoc->airlist[airNo].sw15_f == 0)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.5拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "副板SW1.5拨码");
						vecErr.push_back(strWrong + "副板SW1.5拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.5拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "副板SW1.5拨码");
						vecErr.push_back(strRight + "副板SW1.5拨码");
					}
				}
				else
				{
					if (pdoc->airlist[airNo].sw15_f == 1)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.5拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "副板SW1.5拨码");
						vecErr.push_back(strWrong + "副板SW1.5拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.5拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "副板SW1.5拨码");
						vecErr.push_back(strRight + "副板SW1.5拨码");
					}
				}
				if (pdoc->airlist[airNo].sw16_f == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.6拨码错误\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "副板SW1.6拨码");
					vecErr.push_back(strWrong + "副板SW1.6拨码");
					errflag = 1;
					iStep = iEndStep;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.6拨码正确\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "副板SW1.6拨码");
					vecErr.push_back(strRight + "副板SW1.6拨码");
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					if (pdoc->airlist[airNo].sw17_f == 0)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.7拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "副板SW1.7拨码");
						vecErr.push_back(strWrong + "副板SW1.7拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.7拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "副板SW1.7拨码");
						vecErr.push_back(strRight + "副板SW1.7拨码");
					}
					if (pdoc->airlist[airNo].sw18_f == 0)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.8拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "副板SW1.8拨码");
						vecErr.push_back(strWrong + "副板SW1.8拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.8拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "副板SW1.8拨码");
						vecErr.push_back(strRight + "副板SW1.8拨码");
					}
				}
				else
				{
					if (pdoc->airlist[airNo].sw17_f == 1)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.7拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "副板SW1.7拨码");
						vecErr.push_back(strWrong + "副板SW1.7拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.7拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "副板SW1.7拨码");
						vecErr.push_back(strRight + "副板SW1.7拨码");
					}
					if (pdoc->airlist[airNo].sw18_f == 1)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.8拨码错误\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "副板SW1.8拨码");
						vecErr.push_back(strWrong + "副板SW1.8拨码");
						errflag = 1;
						iStep = iEndStep;
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 副板SW1.8拨码正确\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "副板SW1.8拨码");
						vecErr.push_back(strRight + "副板SW1.8拨码");
					}
				}
			}
			if (iStep == 40 && (GetTickCount() - iLastTime) >= 500) //系统电加热过载是否闭合
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 10;
				iLastTime = GetTickCount();

			}
			if (iStep == 50 && (GetTickCount() - iLastTime) >= 50) //系统电加热过载是否闭合
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("TH1 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue = pdoc->airlist[airNo].s_tp1 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH1 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH1 TH8 温差");
					vecErr.push_back(strWrong + "TH1 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH1 TH8 温差");
					vecErr.push_back(strRight + "TH1 TH8 温差");
				}
			}
			if (iStep == 51 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("TH2 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue2 = pdoc->airlist[airNo].s_tp2 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue2) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH2 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH2 TH8 温差");
					vecErr.push_back(strWrong + "TH2 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH2 TH8 温差");
					vecErr.push_back(strRight + "TH2 TH8 温差");
				}
			}
			if (iStep == 52)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("TH9 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue9 = pdoc->airlist[airNo].s_tp9 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue9) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH9 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH9 TH8 温差");
					vecErr.push_back(strWrong + "TH9 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH9 TH8 温差");
					vecErr.push_back(strRight + "TH9 TH8 温差");
				}
			}
			if (iStep == 53 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("TH10 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue10 = pdoc->airlist[airNo].s_tp10 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue10) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH10 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH10 TH8 温差");
					vecErr.push_back(strWrong + "TH10 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH10 TH8 温差");
					vecErr.push_back(strRight + "TH10 TH8 温差");
				}
			}
			if (iStep == 54 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 6;
				iLastTime = GetTickCount();
				MessAddString("TH11 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue11 = pdoc->airlist[airNo].s_tp11 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue11) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH11 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH11 TH8 温差");
					vecErr.push_back(strWrong + "TH11 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH11 TH8 温差");
					vecErr.push_back(strRight + "TH11 TH8 温差");
				}
			}
			if (iStep == 60 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 5;
				iLastTime = GetTickCount();
				MessAddString("TH12 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue12 = pdoc->airlist[airNo].s_tp12 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue12) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH12 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH12 TH8 温差");
					vecErr.push_back(strWrong + "TH12 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH12 TH8 温差");
					vecErr.push_back(strRight + "TH12 TH8 温差");
				}
			}
			if (iStep == 65 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 5;
				iLastTime = GetTickCount();
				MessAddString("TH5 TH8 温差");
				float a;
				CString strTemp;
				m_edit_e.GetWindowText(strTemp);
				a = atof(strTemp);
				float cmpvalue5 = pdoc->airlist[airNo].s_tp5 - pdoc->airlist[airNo].s_tp8;//th1-th9
				if (abs(cmpvalue5) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH5 TH8 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH5 TH8 温差");
					vecErr.push_back(strWrong + "TH5 TH8 温差");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH5 TH8 温差");
					vecErr.push_back(strRight + "TH5 TH8 温差");
				}
				MessAddString("TH6 TH7 温差");
				cmpvalue5 = pdoc->airlist[airNo].s_tp6 - pdoc->airlist[airNo].s_tp7;//th1-th9
				if (abs(cmpvalue5) > a)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH6 TH7 温差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH6 TH7 温差");
					vecErr.push_back(strWrong + "TH6 TH7 温差");
					errflag = 1;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "TH6 TH7 温差");
					vecErr.push_back(strRight + "TH6 TH7 温差");
				}
				MessAddString("LP1 LP2比较");
				if (fabs(pdoc->airlist[airNo].s_lowpre - pdoc->airlist[airNo].s_highpre) > 1.2f)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" LP1 LP2 压力差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "LP1 LP2比较");
					vecErr.push_back(strWrong + "LP1 LP2比较");
					errflag = 1;
					//iStep = iEndStep;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "LP1 LP2比较");
					vecErr.push_back(strRight + "LP1 LP2比较");
				}
				MessAddString("LP3 LP2比较");
				if (fabs(pdoc->airlist[airNo].f_s_lowpre - pdoc->airlist[airNo].s_lowpre) > 1.2f)//下降温度超过2度，表示传感器测试合格
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" LP3 LP2 压力差大\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "LP3 LP2比较");
					vecErr.push_back(strWrong + "LP3 LP2比较");
					errflag = 1;
				}
				else
				{
					m_alarmlist3.AddString(strRight + "LP3 LP2比较");
					vecErr.push_back(strRight + "LP3 LP2比较");
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					MessAddString("LP3 LP4比较");
					if (fabs(pdoc->airlist[airNo].f_s_lowpre - pdoc->airlist[airNo].f_s_highpre) > 1.2f)//下降温度超过2度，表示传感器测试合格
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" LP3 LP4 压力差大\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "LP3 LP4比较");
						vecErr.push_back(strWrong + "LP3 LP4比较");
						errflag = 1;
						//iStep = iEndStep;
					}
					else
					{
						m_alarmlist3.AddString(strRight + "LP3 LP4比较");
						vecErr.push_back(strRight + "LP3 LP4比较");
					}
				}
			}
			if (iStep == 70 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 5;
				iLastTime = GetTickCount();
				MessAddString("检测水泵过载是否闭合");
				if (pdoc->airlist[airNo].DI6 == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 水泵过载未闭合\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "水泵过载闭合");
					vecErr.push_back(strWrong + "水泵过载闭合");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 水泵过载闭合\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "水泵过载闭合");
					vecErr.push_back(strRight + "水泵过载闭合");
				}
			}
			if (iStep == 75 && (GetTickCount() - iLastTime) >= 50)
			{
				bSendCmd[iStep - 10] = TRUE;
				iStep += 5;
				iLastTime = GetTickCount();
				MessAddString("检测水系统电加热过载是否闭合");
				if (pdoc->airlist[airNo].DI8 == 1)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 水系统电加热过载未闭合\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "水系统电加热过载闭合");
					vecErr.push_back(strWrong + "水系统电加热过载闭合");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 水系统电加热过载闭合\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "水系统电加热过载闭合");
					vecErr.push_back(strRight + "水系统电加热过载闭合");
				}
				MessAddString("检测水流开关是否断开");
				if (pdoc->airlist[airNo].DI3 == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 检测水流开关未断开\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "检测水流开关断开");
					vecErr.push_back(strWrong + "检测水流开关断开");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 检测水流开关断开\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "检测水流开关断开");
					vecErr.push_back(strRight + "检测水流开关断开");
				}

			}
			if (iStep == 80 && (GetTickCount() - iLastTime) >= 2000)
			{

				bSendCmd[iStep - 10] = TRUE;
				iLastTime = GetTickCount();
				iStep += 2;
				MessAddString("CT1");
				if (pdoc->airlist[airNo].s_ele == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" CT1==0\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "CT1");
					vecErr.push_back(strRight + "CT1");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" CT1!=0\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "CT1");
					vecErr.push_back(strWrong + "CT1");
					errflag = 1;
					iStep = iEndStep;
				}
				MessAddString("CT2");
				if (pdoc->airlist[airNo].s_ele2 == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" CT2==0\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "CT2");
					vecErr.push_back(strRight + "CT2");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" CT2!=0\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "CT2");
					vecErr.push_back(strWrong + "CT2");
					errflag = 1;

					iStep = iEndStep;
				}
				MessAddString("CT3");
				if (pdoc->airlist[airNo].f_s_ele1 == 0)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" CT3==0\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "CT3");
					vecErr.push_back(strRight + "CT3");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" CT3!=0\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "CT3");
					vecErr.push_back(strWrong + "CT3");
					errflag = 1;
					iStep = iEndStep;
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					MessAddString("CT4");
					if (pdoc->airlist[airNo].f_s_ele2 == 0)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" CT4==0\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "CT4");
						vecErr.push_back(strRight + "CT4");
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" CT4!=0\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "CT4");
						vecErr.push_back(strWrong + "CT4");
						errflag = 1;
						iStep = iEndStep;
					}
				}
			}
			if (iStep == 82 && (GetTickCount() - iLastTime) >= 50)
			{
				if (stop == 0) {

					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("水盘电加热输出\r\n");
					outfile.Close();
					MessAddString("系统1水盘电加热输出1运行");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DO13 == 1)
				{
					iStep += 3;
					stop = 0;
				}
				else
				{
					SetHP(0, 1);
				}
			}
			if (iStep == 85 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO13 == 1)
			{
				SetFan2High(0, 1);
				iStep += 5;
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1风机1运行\r\n");
				outfile.Close();
				MessAddString("系统1风机1运行");
				m_button.SetWindowText("若系统1风机1运行，请点击此按钮");
				m_button.ShowWindow(SW_SHOW);
				exv1errflag = 0;
				m_exv_button_ok = 0;
				m_button1 = 0;
				m_button2 = 0;
				iLastTime = GetTickCount();
			}
			if (iStep == 90 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1 || m_button1 == 1)
				{
					SetFan2High(0, 0);
					m_exv_button_ok = 0;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1风机1运行正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1风1运行");
					vecErr.push_back(strRight + "系统1风机1运行");
					iStep += 5;
				}
				else if (m_button2 == 1)
				{
					SetFan2High(0, 0);
					iStep = 811;
					//m_button.ShowWindow(SW_HIDE);
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1风机1运行异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1风机1运行");
					vecErr.push_back(strWrong + "系统1风机1运行");
					errflag = 1;
				}
			}
			if (iStep == 95 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO7 == 0)
			{
				SetFan1High(0, 1);
				iStep += 5;
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2风机1运行\r\n");
				outfile.Close();
				MessAddString("系统2风机1运行");
				m_button.SetWindowText("若系统2风机1运行，请点击此按钮");
				m_button.ShowWindow(SW_SHOW);
				exv1errflag = 0;
				m_exv_button_ok = 0;
				m_button1 = 0;
				m_button2 = 0;
				iLastTime = GetTickCount();
			}
			if (iStep == 100 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1 || m_button1 == 1)
				{
					SetFan1High(0, 0);
					m_exv_button_ok = 0;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2风机1运行正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2风机1运行");
					vecErr.push_back(strRight + "系统2风机1运行");
					iStep += 5;
				}
				else if (m_button2 == 1)
				{
					SetFan1High(0, 0);
					iStep = 811;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("系统2风机1运行异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2风机1运行");
					vecErr.push_back(strWrong + "系统2风机1运行");
					errflag = 1;
				}
			}
			if (iStep == 105 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO9 == 0) //运行5s
			{
				if (stop == 0)
				{
					SetFan3(0, 1, 1);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3风机1运行\r\n");
					outfile.Close();
					MessAddString("系统3风机1运行");
					m_button.SetWindowText("若系统3风机1运行，请点击此按钮");
					m_button.ShowWindow(SW_SHOW);
					exv1errflag = 0;
					m_exv_button_ok = 0;
					m_button1 = 0;
					m_button2 = 0;
					stop = 5;
				}
				if (pdoc->airlist[airNo].DOF7 == 1)
				{
					iStep += 5;
					stop = 0;
				}
				else
				{
					SetFan3(0, 1, 1);
				}
				iLastTime = GetTickCount();
			}
			if (iStep == 110 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1 || m_button1 == 1)
				{
					if (stop == 0)
					{
						SetFan3(0, 0, 1);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3风机1运行正常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统3风机1运行");
						vecErr.push_back(strRight + "系统3风机1运行");
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF7 == 0)
					{
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 5;
						stop = 0;
					}
					else {
						SetFan3(0, 0, 1);
					}
				}
				else if (m_button2 == 1)
				{
					SetFan3(0, 0, 1);
					iStep = 811;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("系统3风机1运行异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3风机1运行");
					vecErr.push_back(strWrong + "系统3风机1运行");
					errflag = 1;
				}
			}
			if (iStep == 115 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF7 == 0) //运行5s
			{
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 5;
				}
				else
				{
					iStep += 15;
				}
			}
			if (iStep == 120 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (stop == 0)
				{
					SetFan4(0, 1, 1);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4风机1运行\r\n");
					outfile.Close();
					MessAddString("系统4风机1运行");
					m_button.SetWindowText("若系统4风机1运行，请点击此按钮");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF9 == 1)
				{
					m_button.ShowWindow(SW_SHOW);
					exv1errflag = 0;
					m_exv_button_ok = 0;
					m_button1 = 0;
					m_button2 = 0;
					iStep += 5;
					stop = 0;
				}
				else {
					SetFan4(0, 1, 1);
				}
				iLastTime = GetTickCount();

			}
			if (iStep == 125 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1)
				{
					if (stop == 0)
					{
						SetFan4(0, 0, 1);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4风机1运行正常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统4风机1运行");
						vecErr.push_back(strRight + "系统4风机1运行");
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF9 == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 5;
						stop = 0;
					}
					else
					{
						SetFan4(0, 0, 1);
					}
				}
				else if (m_button2 == 1)
				{
					if (stop == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						iStep = 811;
						m_button.ShowWindow(SW_HIDE);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString("系统4风机1运行异常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统4风机1运行");
						vecErr.push_back(strWrong + "系统4风机1运行");
						errflag = 1;
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF9 == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 5;
						stop = 0;
					}
					else
					{
						SetFan4(0, 0, 1);
					}
				}
			}
			if (iStep == 130 && (GetTickCount() - iLastTime) >= 50)
			{
				SetFan2low(0, 1);
				iStep += 5;
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,风机2运行\r\n");
				outfile.Close();
				MessAddString("系统1,风机2运行");
				iLastTime = GetTickCount();
				m_button.SetWindowText("若系统1,风机2运行，请点击此按钮");
				m_button.ShowWindow(SW_SHOW);
				exv1errflag = 0;
				m_exv_button_ok = 0;
				m_button1 = 0;
				m_button2 = 0;
			}
			if (iStep == 135 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1 || m_button1 == 1)
				{
					SetFan2low(0, 0);
					m_exv_button_ok = 0;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,风机2运行正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,风机2运行");
					vecErr.push_back(strRight + "系统1,风机2运行");
					iStep += 5;
				}
				else if (m_button2 == 1)
				{
					SetFan2low(0, 0);
					iStep = 811;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("系统1,风机2运行异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1,风机2运行");
					vecErr.push_back(strWrong + "系统1,风机2运行");
					errflag = 1;
				}
			}
			if (iStep == 140 && (GetTickCount() - iLastTime) >= 50)
			{

				SetFan1Low(0, 1);
				iStep += 5;
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2风机2运行\r\n");
				outfile.Close();
				MessAddString("系统2风机2运行");
				m_button.SetWindowText("若系统2风机2运行，请点击此按钮");
				m_button.ShowWindow(SW_SHOW);
				exv1errflag = 0;
				m_exv_button_ok = 0;
				m_button1 = 0;
				m_button2 = 0;
				iLastTime = GetTickCount();

			}
			if (iStep == 145 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				stop = 0;
				if (m_exv_button_ok == 1 || m_button1 == 1)
				{
					SetFan1Low(0, 0);
					m_exv_button_ok = 0;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2风机2运行行正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2风机2运行");
					vecErr.push_back(strRight + "系统2风机2运行");
					iStep += 5;

				}
				else if (m_button2 == 1)
				{
					SetFan1Low(0, 0);
					iStep = 811;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("系统2风机2运行异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2风机2运行");
					vecErr.push_back(strWrong + "系统2风机2运行");
					errflag = 1;
				}
			}
			if (iStep == 150 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (stop == 0)
				{
					SetFan3(0, 1, 2);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3风机2运行\r\n");
					outfile.Close();
					MessAddString("系统3风机2运行");
					m_button.SetWindowText("若系统3风机2运行，请点击此按钮");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF8 == 1)
				{
					m_button.ShowWindow(SW_SHOW);
					exv1errflag = 0;
					m_exv_button_ok = 0;
					m_button1 = 0;
					m_button2 = 0;
					iStep += 5;
					stop = 0;
				}
				else {
					SetFan3(0, 1, 2);
				}
				iLastTime = GetTickCount();

			}
			if (iStep == 155 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1)
				{
					if (stop == 0)
					{
						SetFan3(0, 0, 2);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3风机2运行正常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统3风机2运行");
						vecErr.push_back(strRight + "系统3风机2运行");
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF8 == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 5;
						stop = 0;
					}
					else
					{
						SetFan3(0, 0, 2);
					}
				}
				else if (m_button2 == 1)
				{
					if (stop == 0)
					{
						SetFan3(0, 0, 2);
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						iStep = 811;
						m_button.ShowWindow(SW_HIDE);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString("系统3风机2运行异常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统3风机2运行");
						vecErr.push_back(strWrong + "系统3风机2运行");
						errflag = 1;
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF8 == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 5;
						stop = 0;
					}
					else
					{
						SetFan3(0, 0, 2);
					}
				}


			}
			if (iStep == 160 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 7;
				}

			}
			if (iStep == 161 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (stop == 0)
				{
					SetFan4(0, 1, 2);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4风机2运行\r\n");
					outfile.Close();
					MessAddString("系统4风机2运行");
					m_button.SetWindowText("若系统4风机2运行，请点击此按钮");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF10 == 1)
				{
					m_button.ShowWindow(SW_SHOW);
					exv1errflag = 0;
					m_exv_button_ok = 0;
					m_button1 = 0;
					m_button2 = 0;
					iStep += 5;
					stop = 0;
				}
				else {
					SetFan4(0, 1, 2);
				}
				iLastTime = GetTickCount();

			}
			if (iStep == 166 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1)
				{
					if (stop == 0)
					{
						SetFan4(0, 0, 2);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4风机2运行正常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统4风机2运行");
						vecErr.push_back(strRight + "系统4风机2运行");
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF10 == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 1;
						stop = 0;
					}
					else
					{
						SetFan4(0, 0, 2);
					}
				}
				else if (m_button2 == 1)
				{
					if (stop == 0)
					{
						SetFan4(0, 0, 2);
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						iStep = 811;
						m_button.ShowWindow(SW_HIDE);
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString("系统4风机2运行异常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统4风机2运行");
						vecErr.push_back(strWrong + "系统4风机2运行");
						errflag = 1;
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF10 == 0)
					{
						m_button.ShowWindow(FALSE);
						m_button11.ShowWindow(FALSE);
						m_button21.ShowWindow(FALSE);
						m_exv_button_ok = 0;
						m_button.ShowWindow(SW_HIDE);
						iStep += 2;
						stop = 0;
					}
					else
					{
						SetFan4(0, 0, 4);
					}
				}
			}
			if (iStep == 167 && (GetTickCount() - iLastTime) >= 50)
			{
				SetHP(0, 0);
				iStep += 1;
				iLastTime = GetTickCount();
				m_button.SetWindowText("若水盘电加热运行，请点击此按钮");
				m_button.ShowWindow(SW_SHOW);
				exv1errflag = 0;
				m_exv_button_ok = 0;
				m_button1 = 0;
				m_button2 = 0;
			}
			if (iStep == 168 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				if (m_exv_button_ok == 1 || m_button1 == 1)
				{
					SetHP(0, 0);
					m_exv_button_ok = 0;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 水盘电加热运行正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "水盘电加热运行");
					vecErr.push_back(strRight + "水盘电加热运行");
					iStep += 2;
				}
				else if (m_button2 == 1)
				{
					SetHP(0, 0);
					iStep = 811;
					m_button.ShowWindow(SW_HIDE);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("水盘电加热运行异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "水盘电加热运行");
					vecErr.push_back(strWrong + "水盘电加热运行");
					errflag = 1;
				}
			}
			if (iStep == 170 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				MessAddString("系统1风机1,风机2开启");
				SetFan2High(0, 1);
			}
			if (iStep == 175 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO7 == 1) //运行5s
			{
				SetFan2low(0, 1);
				iLastTime = GetTickCount();
				iStep += 5;
			}
			if (iStep == 180 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO8 == 1) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				MessAddString("系统1,EXV1开到480");
				SetExv(0, 480, 1);
			}
			if (iStep == 185 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].s_ele_distension_valve1 == 480) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				MessAddString("系统1压缩机启动");
				SetMachine(1, 1);
			}
			if (iStep == 190 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO11 == 1) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				SetFan1High(0, 1);
				MessAddString("系统2,风机1,风机2启动");
			}
			if (iStep == 195 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO9 == 1) //运行5s
			{
				SetFan1Low(0, 1);
				iLastTime = GetTickCount();
				iStep += 5;
			}
			if (iStep == 200 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO10 == 1) //运行5s
			{
				iLastTime = GetTickCount();

				if (stop == 0)
				{
					MessAddString("系统2,EXV2开到480");
					stop = 1;
				}
				if (pdoc->airlist[airNo].s_ele_distension_valve2 == 480)
				{
					iStep += 5;
					stop = 0;
				}
				else {
					SetExv(0, 480, 2);
				}
			}
			if (iStep == 205 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].s_ele_distension_valve2 == 480) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				MessAddString("系统2压缩机启动");
				SetMachine(2, 1);
			}
			if (iStep == 210 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].DO12 == 1) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0) {

					MessAddString("系统3风机1,风机2开启");
					stop = 1;
				}

				if (pdoc->airlist[airNo].DOF7 == 1)
				{
					iStep += 5;
					stop = 0;
				}
				else {
					SetFan3(0, 1, 1);
				}
			}
			if (iStep == 215 && (GetTickCount() - iLastTime) >= 500) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF8 == 1)
				{
					iStep += 5;
				}
				else {
					SetFan3(0, 1, 2);
				}
			}
			if (iStep == 220 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0) {
					MessAddString("系统3,EXV3开到480");
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 480)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetExv(0, 480, 5);
				}
			}
			if (iStep == 221 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0) {

					MessAddString("系统3压缩机启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF11 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetMachine(3, 1);
				}
			}
			if (iStep == 222 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 5;
				}

			}
			if (iStep == 223 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0) {

					MessAddString("系统4风机1,风机2开启");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF9 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFan4(0, 1, 1);
				}
			}
			if (iStep == 224 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (pdoc->airlist[airNo].DOF10 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFan4(0, 1, 2);
				}
			}
			if (iStep == 225 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("系统4,EXV4开到480");
				SetExv(0, 480, 6);
			}
			if (iStep == 226 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].f_s_ele_distension_valve2 == 480) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{

					MessAddString("系统4压缩机启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF12 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetMachine(4, 1);
				}
			}
			if (iStep == 227 && (GetTickCount() - iLastTime) >= 10000) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统1压缩机停止");
				SetMachine(1, 0);
			}
			if (iStep == 228 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO11 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统2压缩机停止");
				SetMachine(2, 0);
			}
			if (iStep == 229 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DO12 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3压缩机停止");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF11 == 0)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetMachine(3, 0);
				}
			}
			if (iStep == 230 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF11 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 2;
				}

			}
			if (iStep == 231 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4压缩机停止");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF12 == 0)
				{
					iStep += 10;
					stop = 0;
				}
				else {
					SetMachine(4, 0);
				}

			}
			if (iStep == 232 && (GetTickCount() - iLastTime) >= 3000) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统1风机停");
				SetFan2High(0, 0);

			}
			if (iStep == 233 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO7 == 0) //运行5s
			{
				SetFan2low(0, 0);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 234 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO8 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统2风机停");
				SetFan1High(0, 0);

			}
			if (iStep == 235 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO9 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				SetFan1Low(0, 0);
			}
			if (iStep == 236 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DO10 == 0) //运行5s
			{
				iLastTime = GetTickCount();

				if (stop == 0)
				{
					MessAddString("系统3风机停");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF7 == 0)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFan3(0, 0, 1);
				}
			}
			if (iStep == 237 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF8 == 0)
				{
					iStep += 1;
				}
				else
				{
					SetFan3(0, 0, 2);
				}
			}
			if (iStep == 238 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 3;
				}

			}
			if (iStep == 239 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();

				if (stop == 0)
				{
					MessAddString("系统4风机停");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF9 == 0)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFan4(0, 0, 1);
				}
			}
			if (iStep == 240 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF10 == 0)
				{
					iStep += 1;
				}
				else
				{
					SetFan4(0, 0, 2);
				}
			}
			if (iStep == 241 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					if (stricmp(models_tag, "1600") == 0)
					{
						MessAddString("系统1,2,3,4电子膨胀阀关到0");
					}
					else
					{
						MessAddString("系统1,2,3电子膨胀阀关到0");
					}
					stop = 1;
				}
				if (pdoc->airlist[airNo].s_ele_distension_valve1 == 0)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetExv(0, 0, 1);
				}
			}
			if (iStep == 242 && (GetTickCount() - iLastTime) >= 1000) //运行5s
			{

				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].s_ele_distension_valve2 == 0)
				{
					iStep += 1;
				}
				else { SetExv(0, 0, 2); }
			}
			if (iStep == 243 && (GetTickCount() - iLastTime) >= 1000) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 0)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 0, 5);
				}
				iLastTime = GetTickCount();

			}
			if (iStep == 244 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 2;
				}

			}
			if (iStep == 245 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 0)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 0, 6);
				}
				iLastTime = GetTickCount();
			}
			if (iStep == 246 && (GetTickCount() - iLastTime) >= 3000) //运行5s
			{
				iLastTime = GetTickCount();
				/*		CString name1, name2;
						int namenumber;
						m_userinfo1.GetWindowText(name1);
						namenumber = name1.Find("-");
						name2 = name1.Left(namenumber);
						name1 = name2.Right(2);
						if (stricmp(name1, "R1") == 0)
						{*/
				iStep += 4;
				SetFan2High(0, 1);
				MessAddString("制热模式");//模式显示对应显示(未添加:1109)
				moshi = 1;
				MessAddString("系统1,风机1,2启动");
				//}
				//else
				//{
				//	iStep = 580;
				//}

			}
			if (iStep == 250 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO7 == 1) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				SetFan2low(0, 1);
			}
			if (iStep == 255 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DO8 == 1) //运行5s
			{
				SetExv(0, 350, 1);
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1EXV1开到350\r\n");
				outfile.Close();
				iStep += 2;
				iLastTime = GetTickCount();
				MessAddString("系统1,EXV1开到350");
			}
			if (iStep == 257 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].s_ele_distension_valve1 == 350) //运行5s
			{
				m_edit_i.GetWindowText(ordersum_text);
				ordersum = atoi(ordersum_text);
				SetExv(0, ordersum, 3);
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1EXV3开到" + ordersum_text + "\r\n");
				outfile.Close();
				iStep += 3;
				iLastTime = GetTickCount();
				MessAddString("系统1,EXV3开到" + ordersum_text);
			}
			if (iStep == 260 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].s_ele_distension_valve3 == ordersum)
			{
				SetMachine(1, 1);//压缩机1  启动1
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1压缩机启动\r\n");
				outfile.Close();
				iStep += 10;
				iLastTime = GetTickCount();
				MessAddString("系统1压缩机启动");
			}
			if (iStep == 270 && (GetTickCount() - iLastTime) >= 5000 && pdoc->airlist[airNo].DO11 == 1)
			{
				iLastTime = GetTickCount();
				iStep += 30;
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime());
				outfile.WriteString(" 4WV1得电\r\n");
				//SetFourValve1(0, 1);
				MessAddString("4WV1得电");
				SetFourValve(0, 1, 1);
				F_FTH2 = pdoc->airlist[airNo].s_tp2;
				F_FTH10 = pdoc->airlist[airNo].s_tp10;
				F_FTH12 = pdoc->airlist[airNo].s_tp12;
				F_FTH4 = pdoc->airlist[airNo].s_tp4;
				F_FTH14 = pdoc->airlist[airNo].s_tp14;
				F_FFTH1 = pdoc->airlist[airNo].f_s_tp1;
				F_FFTH9 = pdoc->airlist[airNo].f_s_tp9;
				F_FFTH3 = pdoc->airlist[airNo].f_s_tp3;
				F_FFTH13 = pdoc->airlist[airNo].f_s_tp13;
				F_FFTH11 = pdoc->airlist[airNo].f_s_tp11;
				F_FFTH2 = pdoc->airlist[airNo].f_s_tp2;
				F_FFTH10 = pdoc->airlist[airNo].f_s_tp10;
				F_FFTH12 = pdoc->airlist[airNo].f_s_tp12;
				F_FFTH4 = pdoc->airlist[airNo].f_s_tp4;
				F_FFTH14 = pdoc->airlist[airNo].f_s_tp14;
				F_FLP2 = pdoc->airlist[airNo].s_highpre;
				F_FFLP1 = pdoc->airlist[airNo].f_s_lowpre;
				F_FFLP2 = pdoc->airlist[airNo].f_s_highpre;
				tempstr.Format("TH2=%.1f,TH10=%.1f,TH12=%.1f,FFTH1=%.1f,FFTH9=%.1f,FFTH11=%.1f,fFLP2=%.1f,FFLP1=%.1f,",
					pdoc->airlist[airNo].s_tp2, pdoc->airlist[airNo].s_tp10, pdoc->airlist[airNo].s_tp12, pdoc->airlist[airNo].f_s_tp1, pdoc->airlist[airNo].f_s_tp9, pdoc->airlist[airNo].f_s_tp11, pdoc->airlist[airNo].f_s_highpre, pdoc->airlist[airNo].f_s_lowpre);
				outfile.WriteString(tempstr);
				outfile.Close();
			}
			if (iStep == 300 && (GetTickCount() - iLastTime) >= 10000 && pdoc->airlist[airNo].DO5 == 1)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1电流");
				if (pdoc->airlist[airNo].s_ele - FELE1 > 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1电流正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1电流");
					vecErr.push_back(strRight + "系统1电流");
					iStep += 10;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1电流异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1电流");
					vecErr.push_back(strWrong + "系统1电流");
					errflag = 1; iStep += 10;
					//iStep = 811;
				}
			}
			if (iStep == 310 && (GetTickCount() - iLastTime) >= 50000)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1排温");
				iStep += 5;
				float a;
				CString strTemp;
				m_edit_a.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp1 - FTH1 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1排温");
					vecErr.push_back(strRight + "系统1排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1排温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1排温");
					vecErr.push_back(strWrong + "系统1排温");
					errflag = 1;
				}
				MessAddString("系统1出盘温度");
				m_edit_h.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FTH9 - pdoc->airlist[airNo].s_tp9 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1出盘温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1出盘温度");
					vecErr.push_back(strRight + "系统1出盘温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1出盘温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1出盘温度");
					vecErr.push_back(strWrong + "系统1出盘温度");
					errflag = 1;
				}
			}
			if (iStep == 315 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1吸气温度");
				iStep += 5;
				float a;
				CString strTemp;
				m_edit_b.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FTH11 - pdoc->airlist[airNo].s_tp11 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1吸气温度");
					vecErr.push_back(strRight + "系统1吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1吸气温度");
					vecErr.push_back(strWrong + "系统1吸气温度");
					errflag = 1;
				}
			}
			if (iStep == 320 && (GetTickCount() - iLastTime) >= 50)
			{

				iLastTime = GetTickCount();
				MessAddString("系统1吸气压力");
				iStep += 5;
				if (FLP1 - pdoc->airlist[airNo].s_lowpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1吸气压力");
					vecErr.push_back(strRight + "系统1吸气压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1吸气压力");
					vecErr.push_back(strWrong + "系统1吸气压力");
					errflag = 1;
					//iStep = 811;
				}
			}
			if (iStep == 325 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				MessAddString("系统2温度");
				iStep += 22;
				if (pdoc->airlist[airNo].s_tp2 - F_FTH2 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH2正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH2");
					vecErr.push_back(strRight + "TH2");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH2异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH2");
					vecErr.push_back(strWrong + "TH2");
					errflag = 1;
					MessAddString("系统2温度异常,请检查接线!");
				}
				if (pdoc->airlist[airNo].s_tp10 - F_FTH10 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH10正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH10");
					vecErr.push_back(strRight + "TH10");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH10异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH10");
					vecErr.push_back(strWrong + "TH10");
					errflag = 1;
					MessAddString("系统2温度异常,请检查接线!");
				}
				if (pdoc->airlist[airNo].s_tp12 - F_FTH12 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH12正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH12");
					vecErr.push_back(strRight + "TH12");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("TH12异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH12");
					vecErr.push_back(strWrong + "TH12");
					errflag = 1;
					MessAddString("系统2温度异常,请检查接线!");
				}
				if (pdoc->airlist[airNo].s_tp4 - F_FTH4 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH4正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH4");
					vecErr.push_back(strRight + "TH4");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH4异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH4");
					vecErr.push_back(strWrong + "TH4");
					errflag = 1;
					MessAddString("系统2温度异常,请检查接线!");
				}
				if (pdoc->airlist[airNo].s_tp14 - F_FTH14 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH14正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH14");
					vecErr.push_back(strRight + "TH14");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("TH14异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH14");
					vecErr.push_back(strWrong + "TH14");
					errflag = 1;
					MessAddString("系统2温度异常,请检查接线!");
				}
			}
			if (iStep == 347 && (GetTickCount() - iLastTime) >= 100)
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("TH1_3 温度");
				if (pdoc->airlist[airNo].f_s_tp1 - F_FFTH1 < 5.0f)//修改温度
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统TH1_3温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH1_3 温度");
					vecErr.push_back(strRight + " TH1_3 温度");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统TH1_3 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH1_3 温度");
					vecErr.push_back(strWrong + "TH1_3 温度");
					errflag = 1;
					MessAddString("系统3存在温度异常,检查接线");
				}
				MessAddString("TH9_3温度");
				if (pdoc->airlist[airNo].f_s_tp9 - F_FFTH9 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH9_3 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH9_3 温度");
					vecErr.push_back(strRight + "TH9_3 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH9_3 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH9_3 温度");
					vecErr.push_back(strWrong + "TH9_3 温度");
					errflag = 1;
					MessAddString("系统3存在温度异常,检查接线");
				}
				MessAddString("TH11_3温度");
				if (pdoc->airlist[airNo].f_s_tp11 - F_FFTH11 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH11_3 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH11_3 温度");
					vecErr.push_back(strRight + "TH11_3 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH11_3 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH11_3 温度");
					vecErr.push_back(strWrong + "TH11_3 温度");
					errflag = 1;
					MessAddString("系统3存在温度异常,检查接线");
				}
				MessAddString("TH3_3温度");
				if (pdoc->airlist[airNo].f_s_tp3 - F_FFTH3 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH3_3 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH3_3 温度");
					vecErr.push_back(strRight + "TH3_3 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH3_3 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH3_3 温度");
					vecErr.push_back(strWrong + "TH3_3 温度");
					errflag = 1;
					MessAddString("系统3存在温度异常,检查接线");
				}
				MessAddString("TH13_3温度");
				if (pdoc->airlist[airNo].f_s_tp13 - F_FFTH13 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH13_3 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH13_3 温度");
					vecErr.push_back(strRight + "TH13_3 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH13_3 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH13_3 温度");
					vecErr.push_back(strWrong + "TH13_3 温度");
					errflag = 1;
					MessAddString("系统3存在温度异常,检查接线");
				}
			}
			if (iStep == 348 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep = 350;
				}
			}
			if (iStep == 349 && (GetTickCount() - iLastTime) >= 100)
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("TH2_4 温度");
				if (pdoc->airlist[airNo].f_s_tp2 - F_FFTH2 < 5.0f)//修改温度
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统TH2_4 温度温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH2_4 温度");
					vecErr.push_back(strRight + "TH2_4 温度");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统TH2_4 温度温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH2_4 温度温度");
					vecErr.push_back(strWrong + "TH2_4 温度温度");
					errflag = 1;
					MessAddString("系统4存在温度异常,检查接线");
				}
				MessAddString("TH10_4 温度");
				if (pdoc->airlist[airNo].f_s_tp10 - F_FFTH10 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("TH10_4 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH10_4 温度");
					vecErr.push_back(strRight + "TH10_4 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH10_4 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH10_4 温度");
					vecErr.push_back(strWrong + "TH10_4 温度");
					errflag = 1;
					MessAddString("系统4存在温度异常,检查接线");
				}
				MessAddString("TH12_4 温度");
				if (pdoc->airlist[airNo].f_s_tp12 - F_FFTH12 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH12_4 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH12_4 温度");
					vecErr.push_back(strRight + "TH12_4 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("TH12_4 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH12_4 温度");
					vecErr.push_back(strWrong + "TH12_4 温度");
					errflag = 1;
					MessAddString("系统4存在温度异常,检查接线");
				}
				MessAddString("TH4_4 温度");
				if (pdoc->airlist[airNo].f_s_tp4 - F_FFTH4 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("TH4_4 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH4_4 温度");
					vecErr.push_back(strRight + "TH4_4 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH10_4 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH10_4 温度");
					vecErr.push_back(strWrong + "TH10_4 温度");
					errflag = 1;
					MessAddString("系统4存在温度异常,检查接线");
				}
				MessAddString("TH14_4 温度");
				if (pdoc->airlist[airNo].f_s_tp14 - F_FFTH14 < 5.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH14_4 温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH14_4 温度");
					vecErr.push_back(strRight + "TH14_4 温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("TH14_4 温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH14_4 温度");
					vecErr.push_back(strWrong + "TH14_4 温度");
					errflag = 1;
					MessAddString("系统4存在温度异常,检查接线");
				}
			}
			if (iStep == 350 && (GetTickCount() - iLastTime) >= 200)
			{
				iLastTime = GetTickCount();
				MessAddString("系统2压力");
				iStep += 1;
				if (fabs(F_FLP2 - pdoc->airlist[airNo].s_highpre) < 1.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2压力");
					vecErr.push_back(strRight + "系统2压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2压力");
					vecErr.push_back(strWrong + "系统2压力");
					errflag = 1;
					MessAddString("系统2压力存在异常");
				}
				MessAddString("系统3压力");
				if (fabs(F_FFLP1 - pdoc->airlist[airNo].f_s_lowpre) < 1.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3压力");
					vecErr.push_back(strRight + "系统3压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3压力");
					vecErr.push_back(strWrong + "系统3压力");
					errflag = 1;
					MessAddString("系统3压力异常");
				}
			}
			if (iStep == 351 && (GetTickCount() - iLastTime) >= 200)
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep = 355;
				}
			}
			if (iStep == 352 && (GetTickCount() - iLastTime) >= 5000)
			{
				iLastTime = GetTickCount();
				iStep += 3;
				MessAddString("系统4压力");
				if (fabs(F_FFLP2 - pdoc->airlist[airNo].f_s_highpre) < 1.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4压力");
					vecErr.push_back(strRight + "系统4压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4压力");
					vecErr.push_back(strWrong + "系统4压力");
					errflag = 1;
					MessAddString("系统4压力异常");
				}
			}
			if (iStep == 355 && (GetTickCount() - iLastTime) >= 200)
			{
				iStep += 5;
				iLastTime = GetTickCount();
				//float a;
				//CString strTemp;
				//m_edit_c.GetWindowText(strTemp);//C:水温温差
				//a = atof(strTemp);
				//MessAddString("TH7/TH6温差");
				//if (pdoc->airlist[airNo].s_tp7 -pdoc->airlist[airNo].s_tp6 >a)
				//{
				//	CArchive outfile(&logFile, CArchive::store);
				//	outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1制热正常\r\n");
				//	outfile.Close();
				//	m_alarmlist3.AddString(strRight + "系统1制热");
				//	vecErr.push_back(strRight + "系统1制热");
				//}
				//else
				//{
				//	CArchive outfile(&logFile, CArchive::store);
				//	outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1制热异常\r\n");
				//	outfile.Close();
				//	m_alarmlist3.AddString(strWrong + "系统1制热");
				//	vecErr.push_back(strWrong + "系统1制热");
				//	errflag = 1;
				//}
			}
			if (iStep == 360 && (GetTickCount() - iLastTime) >= 200)
			{
				iStep += 10;
				iLastTime = GetTickCount();
				MessAddString("系统2,风机1,2启动");
				SetFan1High(0, 1);
			}
			if (iStep == 370 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO9 == 1) //运行5s
			{
				SetFan1Low(0, 1);
				iLastTime = GetTickCount();
				iStep += 10;
			}
			if (iStep == 380 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO10 == 1) //运行5s
			{
				iStep += 5;
				SetExv(0, 350, 2);
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2,EXV2开到350\r\n");
				outfile.Close();
				iLastTime = GetTickCount();
				MessAddString("系统2,EXV2开到350");

			}
			if (iStep == 385 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].s_ele_distension_valve2 == 350) //运行5s
			{
				iStep += 5;
				SetExv(0, ordersum, 4);
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2,EXV4开到" + ordersum_text + "\r\n");
				outfile.Close();
				iLastTime = GetTickCount();
				MessAddString("系统2,EXV4开到" + ordersum_text);

			}
			if (iStep == 390 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].s_ele_distension_valve4 == ordersum)
			{
				SetMachine(2, 1);//压缩机1  启动1
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2压缩机启动\r\n");
				outfile.Close();
				iLastTime = GetTickCount();
				MessAddString("系统2压缩机启动");
				iStep += 10;
			}
			if (iStep == 400 && (GetTickCount() - iLastTime) >= 5000 && pdoc->airlist[airNo].DO12 == 1)//系统2四通阀1
			{
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 4WV2得电\r\n");
				outfile.Close();
				SetFourValve(0, 1, 2);
				iLastTime = GetTickCount();
				MessAddString("4WV2得电");
				iStep += 25;

			}
			if (iStep == 425 && (GetTickCount() - iLastTime) >= 10000 && pdoc->airlist[airNo].DO6 == 1)//系统2四通阀1
			{
				iLastTime = GetTickCount();
				MessAddString("系统2电流");
				if (pdoc->airlist[airNo].s_ele2 - FELE2 > 5)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2电流正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2电流");
					vecErr.push_back(strRight + "系统2电流");
					iStep += 5;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2电流异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2电流");
					vecErr.push_back(strWrong + "系统2电流");
					errflag = 1;	iStep += 5;
					//iStep = 811;
				}
			}
			if (iStep == 430 && (GetTickCount() - iLastTime) >= 50000)
			{
				iLastTime = GetTickCount();
				MessAddString("系统2排温");
				iStep += 15;
				int a;
				CString strTemp;
				m_edit_a.GetWindowText(strTemp);
				a = atoi(strTemp);
				if (pdoc->airlist[airNo].s_tp2 - FTH2 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2排温");
					vecErr.push_back(strRight + "系统2排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2排温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2排温");
					vecErr.push_back(strWrong + "系统2排温");
					errflag = 1;
				}
				MessAddString("系统2 出盘温度");
				m_edit_h.GetWindowText(strTemp);
				a = atoi(strTemp);
				if (FTH10 - pdoc->airlist[airNo].s_tp10 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2出盘温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2出盘温度");
					vecErr.push_back(strRight + "系统2出盘温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2出盘温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2出盘温度");
					vecErr.push_back(strWrong + "系统2出盘温度");
					errflag = 1;
				}
			}
			if (iStep == 445 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				MessAddString("系统2吸气温度");
				iStep += 10;
				float a;
				CString strTemp;
				m_edit_b.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FTH12 - pdoc->airlist[airNo].s_tp12 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2吸气温度");
					vecErr.push_back(strRight + "系统2吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2吸气温度");
					vecErr.push_back(strWrong + "系统2吸气温度");
					errflag = 1;
				}
			}
			if (iStep == 455 && (GetTickCount() - iLastTime) >= 50)
			{

				iLastTime = GetTickCount();
				MessAddString("系统2吸气压力");
				iStep += 5;
				if (FLP2 - pdoc->airlist[airNo].s_highpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2吸气压力");
					vecErr.push_back(strRight + "系统2吸气压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2吸气压力");
					vecErr.push_back(strWrong + "系统2吸气压力");
					errflag = 1;
				}
			}
			if (iStep == 460 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3,风机1,2启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF7 == 1)
				{
					iStep += 2;
					stop = 0;
				}
				else {
					SetFan3(0, 1, 1);
				}
			}
			if (iStep == 462 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF7 == 1)
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF8 == 1)
				{
					iStep += 3;
				}
				else {
					SetFan3(0, 1, 2);
				}
			}
			if (iStep == 465 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].DOF8 == 1)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3,EXV5开到350");
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 350)
				{
					iStep += 2;
					stop = 0;
				}
				else
				{
					SetExv(0, 350, 5);
				}
			}
			if (iStep == 467 && (GetTickCount() - iLastTime) >= 200)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3 EXV7开到" + ordersum_text);
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve3 == ordersum)
				{
					iStep += 3;
					stop = 0;
				}
				else
				{
					SetExv(0, ordersum, 7);
				}
			}
			if (iStep == 470 && (GetTickCount() - iLastTime) >= 2000)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3压缩机启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF11 == 1)
				{
					iStep += 5;
					stop = 0;
				}
				else {
					SetMachine(3, 1);
				}//压缩机1  启动1

			}
			if (iStep == 475 && (GetTickCount() - iLastTime) >= 5000 && pdoc->airlist[airNo].DOF11 == 1)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3,4WV3得电");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF5 == 1)
				{
					iStep += 5;
					stop = 0;
				}
				else {
					SetFourValve(0, 1, 3);
				}
			}
			if (iStep == 480 && (GetTickCount() - iLastTime) >= 10000 && pdoc->airlist[airNo].DOF5 == 1)
			{
				iLastTime = GetTickCount();
				MessAddString("系统3电流");

				if (pdoc->airlist[airNo].f_s_ele1 - FFELE1 > 5)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3电流正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3电流");
					vecErr.push_back(strRight + "系统3电流");
					iStep += 5;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3电流异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3电流");
					vecErr.push_back(strWrong + "系统3电流");
					errflag = 1;
					iStep += 5;
					//iStep = 811;
				}
			}
			if (iStep == 485 && (GetTickCount() - iLastTime) >= 50000)
			{
				MessAddString("系统3排气温度");
				iLastTime = GetTickCount();
				iStep += 5;
				int a;
				CString strTemp;
				m_edit_a.GetWindowText(strTemp);
				a = atoi(strTemp);
				if (pdoc->airlist[airNo].f_s_tp1 - FFTH1 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3排温");
					vecErr.push_back(strRight + "系统3排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3排温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3排温");
					vecErr.push_back(strWrong + "系统3排温");
					errflag = 1;
				}
			}
			if (iStep == 490 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 10;
				MessAddString("系统3吸气温度");
				float a;
				CString strTemp;
				m_edit_b.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FFTH11 - pdoc->airlist[airNo].f_s_tp11 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3吸气温度");
					vecErr.push_back(strRight + "系统3吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3吸气温度");
					vecErr.push_back(strWrong + "系统3吸气温度");
					errflag = 1;
				}
				MessAddString("系统3出盘温度");
				m_edit_h.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FFTH9 - pdoc->airlist[airNo].f_s_tp9 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3出盘温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3出盘温度");
					vecErr.push_back(strRight + "系统3出盘温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3出盘温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3出盘温度");
					vecErr.push_back(strWrong + "系统3出盘温度");
					errflag = 1;
				}
			}
			if (iStep == 500 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{

				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统3吸气压力");
				if (FFLP1 - pdoc->airlist[airNo].f_s_lowpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3吸气压力");
					vecErr.push_back(strRight + "系统3吸气压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3吸气压力");
					vecErr.push_back(strWrong + "系统3吸气压力");
					errflag = 1;
				}
			}
			if (iStep == 501 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep = 510;
				}
			}
			if (iStep == 502 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统4风机1,2开启");

			}
			if (iStep == 503 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF9 == 1)
				{
					iStep += 1;
				}
				else {
					SetFan4(0, 1, 1);
				}

			}
			if (iStep == 504 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF10 == 1)
				{
					iStep += 1;
				}
				else {
					SetFan4(0, 1, 2);
				}

			}
			if (iStep == 505 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4,EXV6开到350");
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 350)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetExv(0, 350, 6);
				}

			}
			if (iStep == 506 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4,EXV8开到" + ordersum_text);
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve4 == ordersum)
				{
					iStep += 4;
					stop = 0;
				}
				else
				{
					SetExv(0, ordersum, 8);
				}

			}
			if (iStep == 510 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4压缩机启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF12 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetMachine(4, 1);
				}//压缩机1  启动1

			}
			if (iStep == 511 && (GetTickCount() - iLastTime) >= 5000) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4,4WV4得电");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF6 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFourValve(0, 1, 4);
				}

			}
			if (iStep == 512 && (GetTickCount() - iLastTime) >= 10000) //运行5s
			{
				iLastTime = GetTickCount();
				MessAddString("系统4电流");
				if (pdoc->airlist[airNo].f_s_ele2 - FFELE2 > 5)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4电流正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4电流");
					vecErr.push_back(strRight + "系统4电流");
					iStep += 1;
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4电流异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4电流");
					vecErr.push_back(strWrong + "系统4电流");
					errflag = 1;
					iStep += 1;
					//iStep = 811;
				}

			}
			if (iStep == 513 && (GetTickCount() - iLastTime) >= 50000) //运行5s
			{
				MessAddString("系统4排气温度");
				iLastTime = GetTickCount();
				iStep += 1;
				int a;
				CString strTemp;
				m_edit_a.GetWindowText(strTemp);
				a = atoi(strTemp);
				if (pdoc->airlist[airNo].f_s_tp2 - FFTH2 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4排温");
					vecErr.push_back(strRight + "系统4排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4排温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4排温");
					vecErr.push_back(strWrong + "系统4排温");
					errflag = 1;
				}
				MessAddString("系统4出盘温度");
				float h;
				m_edit_h.GetWindowText(strTemp);
				h = atof(strTemp);
				if (FFTH10 - pdoc->airlist[airNo].f_s_tp10 > h)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4出盘温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4出盘温度");
					vecErr.push_back(strRight + "系统4出盘温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4出盘温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4出盘温度");
					vecErr.push_back(strWrong + "系统4出盘温度");
					errflag = 1;
				}
				MessAddString("系统4吸气温度");
				float b;
				m_edit_b.GetWindowText(strTemp);
				b = atof(strTemp);
				if (FFTH12 - pdoc->airlist[airNo].f_s_tp12 > b)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4吸气温度");
					vecErr.push_back(strRight + "系统4吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4吸气温度");
					vecErr.push_back(strWrong + "系统4吸气温度");
					errflag = 1;
				}
				MessAddString("系统4吸气压力");
				if (FFLP2 - pdoc->airlist[airNo].f_s_highpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4吸气压力");
					vecErr.push_back(strRight + "系统4吸气压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4吸气压力");
					vecErr.push_back(strWrong + "系统4吸气压力");
					errflag = 1;
				}
			}
			if (iStep == 514 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					if (stricmp(models_tag, "1600") == 0)
					{
						MessAddString("系统1,2,5,6 电子膨胀阀开到480");
					}
					else
					{
						MessAddString("系统1,2,3,电子膨胀阀开到480");
					}
					stop = 1;
				}
				if (pdoc->airlist[airNo].s_ele_distension_valve1 == 480)
				{
					iStep += 1;
				}
				else {
					SetExv(0, 480, 1);
				}
			}
			if (iStep == 515 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].s_ele_distension_valve2 == 480)
				{

					iStep += 2;
				}
				else
				{
					SetExv(0, 480, 2);
				}
			}
			if (iStep == 517 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 480)
				{
					iStep += 3;
				}
				else
				{
					SetExv(0, 480, 5);
				}
			}
			if (iStep == 520 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 480)
				{
					iStep += 4;
					int b;
					CString strTemp;
					m_edit_d.GetWindowText(strTemp);
					b = atoi(strTemp);
					b = abs(b);
					iSpantime = b * 1000;
				}
				else
				{
					SetExv(0, 480, 6);
				}
				iLastTime = GetTickCount();

			}
			if (iStep == 524 && (GetTickCount() - iLastTime) >= iSpantime) //运行5s
			{
				MessAddString("系统制热TH6/TH7温度");
				iLastTime = GetTickCount();
				iStep += 1;
				int a;
				CString strTemp;
				m_edit_f.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp7 - pdoc->airlist[airNo].s_tp6 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH6/TH7温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "TH6/TH7温度");
					vecErr.push_back(strRight + "TH6/TH7温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" TH6/TH7温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "TH6/TH7温度");
					vecErr.push_back(strWrong + "TH6/TH7温度");
					errflag = 1;
					MessAddString("系统制热TH6/TH7温度异常");
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					MessAddString("系统1,2,3,4低压");
					cycle = 0;
				}
				else
				{
					MessAddString("系统1,2,3低压");
					cycle = 0;
				}
			}
			if (iStep == 525 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (fabs(pdoc->airlist[airNo].s_lowpre - pdoc->airlist[airNo].s_highpre) <= 0.4f)
				{
					cycle = 0;
					iStep += 1;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,2压力平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,2压力平衡");
					vecErr.push_back(strRight + "系统1,2压力平衡");
				}
				else
				{
					cycle += 1;

					if (cycle > 31)
					{
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,2压力不平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统1,2压力平衡");
						vecErr.push_back(strWrong + "系统1,2压力平衡");
						errflag = 1;
						MessAddString("系统1,2压力不平衡超过预期");
					}
					else
					{
						iLastTime = GetTickCount();
						iStep = 525;
					}
				}
			}
			if (iStep == 526 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (fabs(pdoc->airlist[airNo].s_highpre - pdoc->airlist[airNo].f_s_lowpre) <= 0.4f)
				{
					cycle = 0;
					iStep += 1;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2,3压力平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2,3压力平衡");
					vecErr.push_back(strRight + "系统2,3压力平衡");
				}
				else
				{
					cycle += 1;

					if (cycle > 31)
					{
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2,3压力不平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统2,3压力平衡");
						vecErr.push_back(strWrong + "系统2,3压力平衡");
						errflag = 1;
						MessAddString("系统2,3压力不平衡超过预期");
					}
					else
					{
						iLastTime = GetTickCount();
						iStep = 526;
					}
				}
			}
			if (iStep == 527 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (fabs(pdoc->airlist[airNo].s_lowpre - pdoc->airlist[airNo].f_s_lowpre) <= 0.4f)
				{
					cycle = 0;
					iStep += 1;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,3压力平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,3压力平衡");
					vecErr.push_back(strRight + "系统1,3压力平衡");
				}
				else
				{
					cycle += 1;

					if (cycle > 31)
					{
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,3压力不平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统1,3压力平衡");
						vecErr.push_back(strWrong + "系统1,3压力平衡");
						errflag = 1;
						MessAddString("系统1,3压力不平衡超过预期");
					}
					else
					{
						iLastTime = GetTickCount();
						iStep = 527;
					}
				}
			}
			if (iStep == 528 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stricmp(models_tag, "1600") == 0)
				{
					if (fabs(pdoc->airlist[airNo].f_s_lowpre - pdoc->airlist[airNo].f_s_highpre) <= 0.4f)
					{
						cycle = 0;
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4,3压力平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统4,3压力平衡");
						vecErr.push_back(strRight + "系统4,3压力平衡");
					}
					else
					{
						cycle += 1;

						if (cycle > 31)
						{
							iStep += 1;
							CArchive outfile(&logFile, CArchive::store);
							outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4,3压力不平衡\r\n");
							outfile.Close();
							m_alarmlist3.AddString(strWrong + "系统4,3压力平衡");
							vecErr.push_back(strWrong + "系统4,3压力平衡");
							errflag = 1;
							MessAddString("系统4,3压力不平衡超过预期");
						}
						else
						{
							iLastTime = GetTickCount();
							iStep = 528;
						}
					}
				}
				else
				{
					iStep += 1;
				}
			}
			if (iStep == 529 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统1,EXV1开到300");
				SetExv(0, 300, 1);
				CArchive outfile(&logFile, CArchive::store);
				FLP1 = pdoc->airlist[airNo].s_lowpre;
				tempstr.Format("FLP1=%.1f\r\n", pdoc->airlist[airNo].s_lowpre);
				outfile.WriteString(tempstr);
				outfile.Close();
			}
			if (iStep == 530 && (GetTickCount() - iLastTime) >= 15000 && pdoc->airlist[airNo].s_ele_distension_valve1 == 300)
			{
				iLastTime = GetTickCount();
				iStep += 1;
				CArchive outfile(&logFile, CArchive::store);
				F_FLP2 = pdoc->airlist[airNo].s_highpre;
				ZF_FFLP1 = pdoc->airlist[airNo].f_s_lowpre;
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					F_FFLP2 = pdoc->airlist[airNo].f_s_highpre;
				}
				else
				{
					;
				}
			}
			if (iStep == 531 && (GetTickCount() - iLastTime) >= 30000)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1压力");
				iStep += 3;
				if (FLP1 - pdoc->airlist[airNo].s_lowpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1压力");
					vecErr.push_back(strRight + "系统1压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1压力");
					vecErr.push_back(strWrong + "系统1压力");
					errflag = 1;
					MessAddString("系统1压力异常,请检查接线");
				}

			}
			if (iStep == 534 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					MessAddString("系统2,3,4压力");
					iStep += 11;
					if (fabs(pdoc->airlist[airNo].s_highpre - F_FLP2) < 0.4f && fabs(pdoc->airlist[airNo].f_s_lowpre - ZF_FFLP1) < 0.4f && fabs(pdoc->airlist[airNo].f_s_highpre - F_FFLP2) < 0.4f)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2/3/4压力正常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统2/3/4压力");
						vecErr.push_back(strRight + "系统2/3/4压力");

					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2/3/4压力异常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统2/3/4压力");
						vecErr.push_back(strWrong + "系统2/3/4压力");
						errflag = 1;
						MessAddString("系统2,3,4压力异常,请检查接线");
					}
				}
				else
				{
					MessAddString("系统2,3压力");
					iStep += 11;
					if (fabs(pdoc->airlist[airNo].s_highpre - F_FLP2) < 0.4f && fabs(pdoc->airlist[airNo].f_s_lowpre - ZF_FFLP1) < 0.4f)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2/3压力正常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统2/3压力");
						vecErr.push_back(strRight + "系统2/3压力");

					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2/3压力异常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统2/3压力");
						vecErr.push_back(strWrong + "系统2/3压力");
						errflag = 1;
						MessAddString("系统2,3压力异常,请检查接线");
					}
				}
			}
			if (iStep == 535 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统1,2,3,4 EXV3,EXV4,EXV7,EXV8开到250");
				SetExv(0, 250, 3);
			}
			if (iStep == 536 && (GetTickCount() - iLastTime) >= 200 && pdoc->airlist[airNo].s_ele_distension_valve3 == 250) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				SetExv(0, 250, 4);
			}
			if (iStep == 537 && (GetTickCount() - iLastTime) >= 200 && pdoc->airlist[airNo].s_ele_distension_valve4 == 250) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve3 == 250)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 250, 7);
				}
			}
			if (iStep == 538 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve4 == 250)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 250, 8);
				}
			}
			if (iStep == 539 && (GetTickCount() - iLastTime) >= 12000) //运行5s
			{
				iLastTime = GetTickCount();
				MessAddString("系统1,2 EXV3,EXV4开到150");
				SetExv(0, 150, 3);
				iStep += 1;
			}
			if (iStep == 540 && (GetTickCount() - iLastTime) >= 200 && pdoc->airlist[airNo].s_ele_distension_valve3 == 150) //运行5s
			{
				iLastTime = GetTickCount();
				SetExv(0, 150, 4);
				iStep += 1;
			}
			if (iStep == 541 && (GetTickCount() - iLastTime) >= 10000 && pdoc->airlist[airNo].s_ele_distension_valve4 == 150) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统1补气温度");
				float a;
				CString strTemp;
				m_edit_j.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp13 - pdoc->airlist[airNo].s_tp3 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1补气温度");
					vecErr.push_back(strRight + "系统1补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1补气温度");
					vecErr.push_back(strWrong + "系统1补气温度");
					errflag = 1;
				}
				MessAddString("系统2补气温度");
				if (pdoc->airlist[airNo].s_tp14 - pdoc->airlist[airNo].s_tp4 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2补气温度");
					vecErr.push_back(strRight + "系统2补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2补气温度");
					vecErr.push_back(strWrong + "系统2补气温度");
					errflag = 1;
				}
				MessAddString("系统3,4 EXV7,EXV8开到150");
			}
			if (iStep == 542 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve3 == 150)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 150, 7);
				}
			}
			if (iStep == 543 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve4 == 150)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 150, 8);
				}
			}
			if (iStep == 544 && (GetTickCount() - iLastTime) >= 10000)
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统3补气温度");
				float a;
				CString strTemp;
				m_edit_j.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].f_s_tp13 - pdoc->airlist[airNo].f_s_tp3 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3补气温度");
					vecErr.push_back(strRight + "系统3补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3补气温度");
					vecErr.push_back(strWrong + "系统3补气温度");
					errflag = 1;
				}
				MessAddString("系统4补气温度");
				if (pdoc->airlist[airNo].f_s_tp14 - pdoc->airlist[airNo].f_s_tp4 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4补气温度");
					vecErr.push_back(strRight + "系统4补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4补气温度");
					vecErr.push_back(strWrong + "系统4补气温度");
					errflag = 1;
				}
			}
			if (iStep == 545 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1压缩机停止");
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1压缩机停止\r\n");
				outfile.Close();
				iStep += 1;
				SetMachine(1, 0);
			}
			if (iStep == 546 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO11 == 0)
			{
				iLastTime = GetTickCount();
				MessAddString("4WV1掉电");
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 4WV1掉电\r\n");
				outfile.Close();
				iStep += 1;
				SetFourValve(0, 0, 1);
				iLastTime = GetTickCount();
			}
			if (iStep == 547 && pdoc->airlist[airNo].DO5 == 0)
			{
				iLastTime = GetTickCount();
				MessAddString("系统2压缩机停止");
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2压缩机停止\r\n");
				outfile.Close();
				iStep += 1;
				SetMachine(2, 0);
			}
			if (iStep == 548 && (GetTickCount() - iLastTime) >= 1500 && pdoc->airlist[airNo].DO12 == 0)
			{
				iLastTime = GetTickCount();

				MessAddString("4WV2掉电");
				iStep += 1;
				SetFourValve(0, 0, 2);
			}
			if (iStep == 549 && pdoc->airlist[airNo].DO6 == 0)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3压缩机停止");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF11 == 0)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetMachine(3, 0);
				}
			}
			if (iStep == 550 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].DOF11 == 0)
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("关闭系统3,4WV3");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF5 == 0)
				{
					iStep += 1;
					stop = 0;
				}
				else
				{
					SetFourValve(0, 0, 3);
				}
			}
			if (iStep == 551 && (GetTickCount() - iLastTime) >= 2000)
			{
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iLastTime = GetTickCount();
					if (stop == 0)
					{
						MessAddString("系统4压缩机停止");
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF12 == 0)
					{
						iStep += 1;
						stop = 0;
					}
					else
					{
						SetMachine(4, 0);
					}
				}
				else
				{
					iStep += 1;
				}
			}
			if (iStep == 552 && (GetTickCount() - iLastTime) >= 2000)
			{
				CString a, b, c;
				m_userinfo1.GetWindowText(a);
				b = a.Left(8);
				c = b.Right(4);
				if (stricmp(models_tag, "1600") == 0)
				{
					iLastTime = GetTickCount();
					if (stop == 0)
					{
						MessAddString("关闭系统4,4WV4");
						stop = 1;
					}
					if (pdoc->airlist[airNo].DOF6 == 0)
					{
						iStep += 1;
						stop = 0;
					}
					else
					{
						SetFourValve(0, 0, 4);
					}
				}
				else
				{
					iStep += 1;
				}
			}
			if (iStep == 553 && (GetTickCount() - iLastTime) >= 1500)
			{
				if (stop == 0)
				{
					if (stricmp(models_tag, "1600") == 0)
					{
						MessAddString("系统1,2,3,4电子膨胀阀关到0");
					}
					else
					{
						MessAddString("系统1,2,3电子膨胀阀关到0");
					}
					stop = 1;
				}
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].s_ele_distension_valve1 == 20)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 20, 1);
				}
			}
			if (iStep == 554 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{

				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].s_ele_distension_valve2 == 20)
				{
					iStep += 1;
				}
				else { SetExv(0, 20, 2); }

			}
			if (iStep == 555 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{

				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].s_ele_distension_valve3 == 20)
				{
					iStep += 1;
				}
				else { SetExv(0, 20, 3); }

			}
			if (iStep == 556 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{

				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].s_ele_distension_valve4 == 20)
				{
					iStep += 1;
				}
				else { SetExv(0, 20, 4); }

			}
			if (iStep == 557 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 20)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 20, 5);
				}
			}
			if (iStep == 558 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 20)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 20, 6);
				}
			}
			if (iStep == 559 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve3 == 20)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 20, 7);
				}
			}
			if (iStep == 560 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve4 == 20)
				{
					iStep += 1;
				}
				else
				{
					SetExv(0, 20, 8);
				}
			}
			if (iStep == 561 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].f_s_ele_distension_valve2 == 20) //运行5s
			{
				if (stricmp(models_tag, "1600") == 0)
				{
					MessAddString("系统1,2,3,4风机停止");
				}
				else
				{
					MessAddString("系统1,2,3风机停止");
				}

				iLastTime = GetTickCount();
				iStep += 1;
				SetFan2High(0, 0);
			}
			if (iStep == 562 && (GetTickCount() - iLastTime) >= 200 && pdoc->airlist[airNo].DO7 == 0) //运行5s
			{
				SetFan2low(0, 0);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 563 && (GetTickCount() - iLastTime) >= 100 && pdoc->airlist[airNo].DO8 == 0) //运行5s
			{
				SetFan1High(0, 0);
				iLastTime = GetTickCount();
				iStep += 2;
			}
			if (iStep == 565 && (GetTickCount() - iLastTime) >= 100 && pdoc->airlist[airNo].DO9 == 0) //运行5s
			{
				SetFan1Low(0, 0);
				iLastTime = GetTickCount();
				iStep += 5;
			}
			if (iStep == 570 && (GetTickCount() - iLastTime) >= 200 && pdoc->airlist[airNo].DO10 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF7 == 0)
				{
					iStep += 1;
				}
				else { SetFan3(0, 0, 1); }
			}
			if (iStep == 571 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF7 == 0)
				{
					iStep += 1;
				}
				else { SetFan3(0, 0, 1); }
			}
			if (iStep == 572 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF7 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF8 == 0)
				{
					iStep += 1;
				}
				else { SetFan3(0, 0, 2); }
			}
			if (iStep == 573 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 7;
				}
			}
			if (iStep == 574 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF9 == 0)
				{
					iStep += 1;
				}
				else { SetFan4(0, 0, 1); }
			}
			if (iStep == 575 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF9 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF10 == 0)
				{
					iStep += 5;
				}
				else { SetFan4(0, 0, 2); }
			}
			if (iStep == 580 && (GetTickCount() - iLastTime) >= 5000) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				MessAddString("制冷模式");
				moshi = 2;
			}
			if (iStep == 585 && (GetTickCount() - iLastTime) >= 50)
			{
				iLastTime = GetTickCount();
				iStep += 2;
				MessAddString("系统1,2风机开启");
				SetFan2High(0, 1);
			}
			if (iStep == 587 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO7 == 1)
			{
				SetFan2low(0, 1);
				iLastTime = GetTickCount();
				iStep += 3;
			}
			if (iStep == 590 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO8 == 1)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1,EXV1开到350");
				iStep += 5;
				SetExv(0, 350, 1);
			}
			if (iStep == 595 && (GetTickCount() - iLastTime) >= 2000 && pdoc->airlist[airNo].s_ele_distension_valve1 == 350)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1压缩机启动");
				iStep += 1;
				SetMachine(1, 1);
			}
			if (iStep == 596 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DO11 == 1) //运行5s
			{
				m_edit_o.GetWindowText(ordersum_text);
				ordersum = atoi(ordersum_text);
				SetExv(0, ordersum, 3);
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1EXV3开到" + ordersum_text + "\r\n");
				outfile.Close();
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("系统1,EXV3开到" + ordersum_text);
			}
			if (iStep == 597 && (GetTickCount() - iLastTime) >= 30000 && pdoc->airlist[airNo].s_ele_distension_valve3 == ordersum)
			{
				iLastTime = GetTickCount();
				iStep += 3;
				MessAddString("系统1补气温度");
				float a;
				CString strTemp;
				m_edit_j.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp13 - pdoc->airlist[airNo].s_tp3 > a && FTH3 - pdoc->airlist[airNo].s_tp3 > 3)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1补气温度");
					vecErr.push_back(strRight + "系统1补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1补气温度");
					vecErr.push_back(strWrong + "系统1补气温度");
					errflag = 1;
				}
			}
			if (iStep == 600 && (GetTickCount() - iLastTime) >= 30000)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1排温");
				iStep += 5;
				float a;
				CString strTemp;
				m_edit_x.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp1 - FTH1 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1排温");
					vecErr.push_back(strRight + "系统1排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1排温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1排温");
					vecErr.push_back(strWrong + "系统1排温");
					errflag = 1;
				}
			}
			if (iStep == 605 && (GetTickCount() - iLastTime) >= 200)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1吸气温度");
				iStep += 3;
				float a;
				CString strTemp;
				m_edit_m.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FTH11 - pdoc->airlist[airNo].s_tp11 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1吸气温度");
					vecErr.push_back(strRight + "系统1吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1吸气温度");
					vecErr.push_back(strWrong + "系统1吸气温度");
					errflag = 1;
				}
			}
			if (iStep == 608 && (GetTickCount() - iLastTime) >= 200)
			{
				iLastTime = GetTickCount();
				MessAddString("系统1吸气压力");
				iStep += 2;
				if (FLP1 - pdoc->airlist[airNo].s_lowpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1吸气压力");
					vecErr.push_back(strRight + "系统1吸气压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1吸气压力");
					vecErr.push_back(strWrong + "系统1吸气压力");
					errflag = 1;
					//iStep = 811;
				}
			}
			if (iStep == 610 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				MessAddString("系统2,风机1,2启动");
				iLastTime = GetTickCount();
				iStep += 2;
				SetFan1High(0, 1);
			}
			if (iStep == 612 && (GetTickCount() - iLastTime) >= 200 && pdoc->airlist[airNo].DO9 == 1) //运行5s
			{
				SetFan1Low(0, 1);
				iLastTime = GetTickCount();
				iStep += 3;
			}
			if (iStep == 615 && (GetTickCount() - iLastTime) >= 150 && pdoc->airlist[airNo].DO10 == 1) //运行5s
			{
				MessAddString("系统2,EXV2开到350");
				iLastTime = GetTickCount();
				iStep += 1;
				SetExv(0, 350, 2);
			}
			if (iStep == 616 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].s_ele_distension_valve2 == 350) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统2压缩机启动");
				SetMachine(2, 1);
			}
			if (iStep == 617 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DO12 == 1) //运行5s
			{
				m_edit_o.GetWindowText(ordersum_text);
				ordersum = atoi(ordersum_text);
				SetExv(0, ordersum, 4);
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1 EXV4开到" + ordersum_text + "\r\n");
				outfile.Close();
				iStep += 1;
				iLastTime = GetTickCount();
				MessAddString("系统1,EXV4开到" + ordersum_text);
			}
			if (iStep == 618 && (GetTickCount() - iLastTime) >= 30000 && pdoc->airlist[airNo].s_ele_distension_valve4 == ordersum) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				float a;
				CString strTemp;
				m_edit_j.GetWindowText(strTemp);
				a = atof(strTemp);
				MessAddString("系统2补气温度");
				if (pdoc->airlist[airNo].s_tp14 - pdoc->airlist[airNo].s_tp4 > a && FTH4 - pdoc->airlist[airNo].s_tp4 > 3 && pdoc->airlist[airNo].s_tp13 - pdoc->airlist[airNo].s_tp14 > 1.5f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2补气温度");
					vecErr.push_back(strRight + "系统2补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2补气温度");
					vecErr.push_back(strWrong + "系统2补气温度");
					errflag = 1;
				}
			}
			if (iStep == 619 && (GetTickCount() - iLastTime) >= 30000) //运行5s
			{
				MessAddString("系统2排温");
				iLastTime = GetTickCount();
				iStep += 1;
				float a;
				CString strTemp;
				m_edit_x.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp2 - FTH2 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2排温");
					vecErr.push_back(strRight + "系统2排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2排温");
					vecErr.push_back(strWrong + "系统2排温");
					errflag = 1;
				}
			}
			if (iStep == 620 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				MessAddString("系统2吸气温度");
				iLastTime = GetTickCount();
				iStep += 1;
				float a;
				CString strTemp;
				m_edit_m.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FTH12 - pdoc->airlist[airNo].s_tp12 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2吸气温度");
					vecErr.push_back(strRight + "系统2吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2吸气温度");
					vecErr.push_back(strWrong + "系统2吸气温度");
					errflag = 1;
				}
			}
			if (iStep == 621 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				MessAddString("系统2吸气压力");
				iLastTime = GetTickCount();
				iStep += 1;
				if (FLP2 - pdoc->airlist[airNo].s_highpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2吸气压力");
					vecErr.push_back(strRight + "系统2吸气压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2吸气压力");
					vecErr.push_back(strWrong + "系统2吸气压力");
					errflag = 1;
					//	iStep = 811;
				}
			}
			if (iStep == 622 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3,风机1,2启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF7 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFan3(0, 1, 1);
				}

			}
			if (iStep == 623 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF8 == 1)
				{
					iStep += 2;
				}
				else
				{
					SetFan3(0, 1, 2);
				}

			}
			if (iStep == 625 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统3,EXV3开到350");
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 350)
				{
					iStep += 2;
					stop = 0;
				}
				else { SetExv(0, 350, 5); }
			}
			if (iStep == 627 && (GetTickCount() - iLastTime) >= 1500 && pdoc->airlist[airNo].f_s_ele_distension_valve1 == 350) //运行5s
			{
				if (stop == 0)
				{
					MessAddString("系统3压缩机启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF11 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else { SetMachine(3, 1); }
				iLastTime = GetTickCount();
			}
			if (iStep == 628 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DOF11 == 1) //运行5s
			{
				m_edit_o.GetWindowText(ordersum_text);
				ordersum = atoi(ordersum_text);
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统1,EXV7开到" + ordersum_text);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1 EXV7开到" + ordersum_text + "\r\n");
					outfile.Close();
					iStep += 1;
					iLastTime = GetTickCount();
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve3 == ordersum)
				{
					iStep += 1;
					stop = 0;
				}
				else { SetExv(0, ordersum, 7); }
			}
			if (iStep == 629 && (GetTickCount() - iLastTime) >= 30000) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统3补气温度");
				float a;
				CString strTemp;
				m_edit_j.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].f_s_tp13 - pdoc->airlist[airNo].f_s_tp3 > a && FFTH3 - pdoc->airlist[airNo].f_s_tp3 > 3 && pdoc->airlist[airNo].f_s_tp4 - pdoc->airlist[airNo].f_s_tp3 > 3)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3补气温度");
					vecErr.push_back(strRight + "系统3补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3补气温度");
					vecErr.push_back(strWrong + "系统3补气温度");
					errflag = 1;
				}
			}
			if (iStep == 630 && (GetTickCount() - iLastTime) >= 30000) //运行5s
			{
				MessAddString("系统3,排温");
				iLastTime = GetTickCount();
				iStep += 5;
				float a;
				CString strTemp;
				m_edit_x.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].f_s_tp1 - FFTH1 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3排温");
					vecErr.push_back(strRight + "系统3排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3排温");
					vecErr.push_back(strWrong + "系统3排温");
					errflag = 1;
				}
			}
			if (iStep == 635 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				MessAddString("系统3吸气温度");
				iLastTime = GetTickCount();
				iStep += 5;
				float a;
				CString strTemp;
				m_edit_m.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FFTH11 - pdoc->airlist[airNo].f_s_tp11 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3吸气温度");
					vecErr.push_back(strRight + "系统3吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3吸气温度");
					vecErr.push_back(strWrong + "系统3吸气温度");
					errflag = 1;
				}
			}
			if (iStep == 640 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				MessAddString("系统3吸气压力");
				iLastTime = GetTickCount();
				iStep += 1;
				if (FFLP1 - pdoc->airlist[airNo].f_s_lowpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3吸气压力");
					vecErr.push_back(strRight + "系统3吸气压力");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("系统3吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3吸气压力");
					vecErr.push_back(strWrong + "系统3吸气压力");
					errflag = 1;
				}

			}
			if (iStep == 641 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 8;
				}
			}
			if (iStep == 642 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4,风机1,2启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF9 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else {
					SetFan4(0, 1, 1);
				}
			}
			if (iStep == 643 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF10 == 1)
				{
					iStep += 1;
				}
				else
				{
					SetFan4(0, 1, 2);
				}

			}
			if (iStep == 644 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统4,EXV4开到350");
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 350)
				{
					iStep += 1;
					stop = 0;
				}
				else { SetExv(0, 350, 6); }
			}
			if (iStep == 645 && (GetTickCount() - iLastTime) >= 1500 && pdoc->airlist[airNo].f_s_ele_distension_valve2 == 350) //运行5s
			{
				if (stop == 0)
				{
					MessAddString("系统4压缩机启动");
					stop = 1;
				}
				if (pdoc->airlist[airNo].DOF12 == 1)
				{
					iStep += 1;
					stop = 0;
				}
				else { SetMachine(4, 1); }
				iLastTime = GetTickCount();
			}
			if (iStep == 646 && (GetTickCount() - iLastTime) >= 1000 && pdoc->airlist[airNo].DOF12 == 1) //运行5s
			{
				m_edit_o.GetWindowText(ordersum_text);
				ordersum = atoi(ordersum_text);
				iLastTime = GetTickCount();
				if (stop == 0)
				{
					MessAddString("系统1,EXV8开到" + ordersum_text);
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1 EXV8开到" + ordersum_text + "\r\n");
					outfile.Close();
					iStep += 1;
					iLastTime = GetTickCount();
					stop = 1;
				}
				if (pdoc->airlist[airNo].f_s_ele_distension_valve4 == ordersum)
				{
					iStep += 1;
					stop = 0;
				}
				else { SetExv(0, ordersum, 8); }
			}
			if (iStep == 647 && (GetTickCount() - iLastTime) >= 30000) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				float a;
				CString strTemp;
				m_edit_j.GetWindowText(strTemp);
				a = atof(strTemp);
				MessAddString("系统4补气温度");
				if (pdoc->airlist[airNo].f_s_tp14 - pdoc->airlist[airNo].f_s_tp4 > a && FFTH4 - pdoc->airlist[airNo].f_s_tp4 > 3 && pdoc->airlist[airNo].f_s_tp13 - pdoc->airlist[airNo].f_s_tp14 > 1.5)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4补气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4补气温度");
					vecErr.push_back(strRight + "系统4补气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4补气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4补气温度");
					vecErr.push_back(strWrong + "系统4补气温度");
					errflag = 1;
				}
			}
			if (iStep == 648 && (GetTickCount() - iLastTime) >= 30000) //运行5s
			{
				MessAddString("系统4,排温");
				iLastTime = GetTickCount();
				iStep += 1;
				float a;
				CString strTemp;
				m_edit_x.GetWindowText(strTemp);
				a = atof(strTemp);
				if (pdoc->airlist[airNo].f_s_tp2 - FFTH2 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4排温正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4排温");
					vecErr.push_back(strRight + "系统4排温");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4温异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4排温");
					vecErr.push_back(strWrong + "系统4排温");
					errflag = 1;
				}
			}
			if (iStep == 649 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				MessAddString("系统4吸气温度");
				iLastTime = GetTickCount();
				iStep += 1;
				float a;
				CString strTemp;
				m_edit_m.GetWindowText(strTemp);
				a = atof(strTemp);
				if (FFTH12 - pdoc->airlist[airNo].f_s_tp12 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气温度正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4吸气温度");
					vecErr.push_back(strRight + "系统4吸气温度");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气温度异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4吸气温度");
					vecErr.push_back(strWrong + "系统4吸气温度");
					errflag = 1;
				}
			}
			if (iStep == 650 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				MessAddString("系统4吸气压力");
				iLastTime = GetTickCount();
				iStep += 1;
				if (F_FFLP2 - pdoc->airlist[airNo].f_s_highpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4吸气压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4吸气压力");
					vecErr.push_back(strRight + "系统4吸气压力");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString("系统4吸气压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4吸气压力");
					vecErr.push_back(strWrong + "系统4吸气压力");
					errflag = 1;
				}

			}
			if (iStep == 651 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();

				if (stop == 0)
				{
					if (stricmp(models_tag, "1600") == 0)
					{
						MessAddString("系统1,2,5,6电子膨胀阀开到480");
					}
					else
					{
						MessAddString("系统1,2,3电子膨胀阀开到480");
					}
					stop = 1;
				}
				if (pdoc->airlist[airNo].s_ele_distension_valve1 == 480)
				{
					iStep += 1;
				}
				else {
					SetExv(0, 480, 1);
				}
			}
			if (iStep == 652 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();

				if (pdoc->airlist[airNo].s_ele_distension_valve2 == 480)
				{
					iStep += 1;
				}
				else {
					SetExv(0, 480, 2);
				}
			}
			if (iStep == 653 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 480)
				{
					iStep += 1;
				}
				else { SetExv(0, 480, 5); }
			}
			if (iStep == 654 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (stricmp(models_tag, "1600") == 0)
				{
					if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 480)
					{
						iStep += 1;
					}
					else { SetExv(0, 480, 6); }
				}
				else
				{
					iStep += 1;
				}
			}
			if (iStep == 655 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				int b;
				CString strTemp;
				m_edit_n.GetWindowText(strTemp);
				b = atoi(strTemp);
				b = abs(b);
				iSpantime = b * 1000;
			}
			if (iStep == 660 && (GetTickCount() - iLastTime) >= iSpantime) //运行5s
			{
				if (stricmp(models_tag, "1600") == 0)
				{
					MessAddString("系统1,2,3,4压缩机电流");
					iLastTime = GetTickCount();
					iStep += 5;
				}
				else
				{
					MessAddString("系统1,2,3压缩机电流");
					iLastTime = GetTickCount();
					iStep += 5;
				}
				if (fabs(pdoc->airlist[airNo].s_ele - pdoc->airlist[airNo].s_ele2) <= 3.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,2电流平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,2电流");
					vecErr.push_back(strRight + "系统1,2电流");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,2电流异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1,2电流");
					vecErr.push_back(strWrong + "系统1,2电流");
					errflag = 1;
				}
				if (fabs(pdoc->airlist[airNo].s_ele - pdoc->airlist[airNo].f_s_ele1) <= 3.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,3电流平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,3电流");
					vecErr.push_back(strRight + "系统1,3电流");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,3电流异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1,3电流");
					vecErr.push_back(strWrong + "系统1,3电流");
					errflag = 1;
				}
				if (stricmp(models_tag, "1600") == 0)
				{
					if (fabs(pdoc->airlist[airNo].f_s_ele1 - pdoc->airlist[airNo].f_s_ele2) <= 3.0f)
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3,4电流平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统3,4电流");
						vecErr.push_back(strRight + "系统3,4电流");
					}
					else
					{
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3,4电流异常\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统3,4电流");
						vecErr.push_back(strWrong + "系统3,4电流");
						errflag = 1;
					}
				}

			}
			if (iStep == 665 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				MessAddString("制冷模式TH6/TH7");
				iLastTime = GetTickCount();
				iStep += 5;
				float a;
				CString strTemp;
				m_edit_f.GetWindowText(strTemp);//F:
				a = atof(strTemp);
				if (pdoc->airlist[airNo].s_tp6 - pdoc->airlist[airNo].s_tp7 > a)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 制冷TH6/TH7正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "制冷TH6/TH7");
					vecErr.push_back(strRight + "制冷TH6/TH7");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 制冷TH6/TH7异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "制冷TH6/TH7");
					vecErr.push_back(strWrong + "制冷TH6/TH7");
					errflag = 1;
				}
				MessAddString("系统1,2,3,4低压");
				cycle = 0;
			}
			if (iStep == 670 && (GetTickCount() - iLastTime) >= 2000) //运行5s
			{
				iLastTime = GetTickCount();
				if (fabs(pdoc->airlist[airNo].s_lowpre - pdoc->airlist[airNo].s_highpre) <= 0.4f)
				{
					cycle = 0;
					iStep += 1;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,2压力平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,2压力平衡");
					vecErr.push_back(strRight + "系统1,2压力平衡");
				}
				else
				{
					cycle += 1;

					if (cycle > 31)
					{
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,2压力不平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统1,2压力平衡");
						vecErr.push_back(strWrong + "系统1,2压力平衡");
						errflag = 1;
						MessAddString("系统1,2压力不平衡超过预期");
					}
					else
					{
						iLastTime = GetTickCount();
						iStep == 670;
					}
				}
			}
			if (iStep == 671 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				if (fabs(pdoc->airlist[airNo].s_highpre - pdoc->airlist[airNo].f_s_lowpre) <= 0.4f)
				{
					cycle = 0;
					iStep += 1;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2,3压力平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2,3压力平衡");
					vecErr.push_back(strRight + "系统2,3压力平衡");
				}
				else
				{
					cycle += 1;

					if (cycle > 31)
					{
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2,3压力不平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统2,3压力平衡");
						vecErr.push_back(strWrong + "系统2,3压力平衡");
						errflag = 1;
						MessAddString("系统2,3压力不平衡超过预期");
					}
					else
					{
						iLastTime = GetTickCount();
						iStep == 671;
					}
				}
			}
			if (iStep == 672 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				if (stricmp(models_tag, "1600") == 0)
				{

					if (fabs(pdoc->airlist[airNo].f_s_lowpre - pdoc->airlist[airNo].f_s_highpre) <= 0.4f)
					{
						cycle = 0;
						iStep += 1;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4,3压力平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strRight + "系统4,3压力平衡");
						vecErr.push_back(strRight + "系统4,3压力平衡");
					}
					else
					{
						cycle += 1;

						if (cycle > 31)
						{
							iStep += 1;
							CArchive outfile(&logFile, CArchive::store);
							outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4,3压力不平衡\r\n");
							outfile.Close();
							m_alarmlist3.AddString(strWrong + "系统4,3压力平衡");
							vecErr.push_back(strWrong + "系统4,3压力平衡");
							errflag = 1;
							MessAddString("系统4,3压力不平衡超过预期");
						}
						else
						{
							iLastTime = GetTickCount();
							iStep == 672;
						}
					}
				}
				else
				{
					iStep += 1;

				}
			}
			if (iStep == 673 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				if (fabs(pdoc->airlist[airNo].s_lowpre - pdoc->airlist[airNo].f_s_lowpre) <= 0.4f)
				{
					cycle = 0;
					iStep += 2;
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,3压力平衡\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1,3压力平衡");
					vecErr.push_back(strRight + "系统1,3压力平衡");
				}
				else
				{
					cycle += 1;

					if (cycle > 31)
					{
						iStep += 2;
						CArchive outfile(&logFile, CArchive::store);
						outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1,3压力不平衡\r\n");
						outfile.Close();
						m_alarmlist3.AddString(strWrong + "系统1,3压力平衡");
						vecErr.push_back(strWrong + "系统1,3压力平衡");
						errflag = 1;
						MessAddString("系统1,3压力不平衡超过预期");
					}
					else
					{
						iLastTime = GetTickCount();
						iStep == 673;
					}
				}
			}
			if (iStep == 675 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				MessAddString("系统2电子膨胀阀开到300");
				iLastTime = GetTickCount();
				iStep += 1;
				SetExv(0, 300, 2);
				CArchive outfile(&logFile, CArchive::store);
				F_FLP2 = pdoc->airlist[airNo].s_highpre;
				outfile.WriteString(GetCurTime());
				tempstr.Format("FLP2=%.1f\r\n", pdoc->airlist[airNo].s_highpre);
				outfile.WriteString(tempstr);
				outfile.Close();
			}
			if (iStep == 676 && (GetTickCount() - iLastTime) >= 30000) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				CArchive outfile(&logFile, CArchive::store);
				F_FLP1 = pdoc->airlist[airNo].s_lowpre;
				F_FFLP1 = pdoc->airlist[airNo].f_s_lowpre;
				F_FFLP2 = pdoc->airlist[airNo].f_s_highpre;
				outfile.WriteString(GetCurTime());
				tempstr.Format("FLP1=%.1f,FFLP1=%.1f,FFLP2=%.1f\r\n", pdoc->airlist[airNo].s_lowpre, pdoc->airlist[airNo].f_s_lowpre, pdoc->airlist[airNo].f_s_highpre);
				outfile.WriteString(tempstr);
				outfile.Close();
			}
			if (iStep == 677 && (GetTickCount() - iLastTime) >= 15000 && pdoc->airlist[airNo].s_ele_distension_valve2 == 300) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 3;
				if (F_FLP2 - pdoc->airlist[airNo].s_highpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2关阀正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统2关阀");
					vecErr.push_back(strRight + "系统2关阀");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统2关阀异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统2关阀");
					vecErr.push_back(strWrong + "系统2关阀");
					MessAddString("系统2电子膨胀阀关阀异常,检查接线");
					errflag = 1;
				}
			}
			if (iStep == 680 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				MessAddString("系统1,3,4压力");
				iLastTime = GetTickCount();
				iStep += 5;
				if (abs(F_FLP1 - pdoc->airlist[airNo].s_lowpre) < 0.4f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统1压力");
					vecErr.push_back(strRight + "系统1压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统1压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统1压力");
					vecErr.push_back(strWrong + "系统1压力");
					MessAddString("系统1压力异常,检查接线");
					errflag = 1;
				}
				if (abs(F_FFLP1 - pdoc->airlist[airNo].f_s_lowpre) < 0.4f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3压力");
					vecErr.push_back(strRight + "系统3压力");

				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3压力");
					vecErr.push_back(strWrong + "系统3压力");
					MessAddString("系统3压力异常,检查接线");
					errflag = 1;
				}
				if (abs(F_FFLP2 - pdoc->airlist[airNo].f_s_highpre) < 0.4f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4压力");
					vecErr.push_back(strRight + "系统4压力");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4压力");
					vecErr.push_back(strWrong + "系统4压力");
					MessAddString("系统4压力异常,检查接线");
					errflag = 1;
				}
			}
			if (iStep == 685 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 5;
				MessAddString("系统3电子膨胀阀开到300");
				SetExv(0, 300, 5);
				CArchive outfile(&logFile, CArchive::store);
				F_FFLP1 = pdoc->airlist[airNo].f_s_lowpre;
				outfile.WriteString(GetCurTime());
				tempstr.Format("FLP2=%.1f\r\n", pdoc->airlist[airNo].f_s_lowpre);
				outfile.WriteString(tempstr);
				outfile.Close();
			}
			if (iStep == 690 && (GetTickCount() - iLastTime) >= 45000 && pdoc->airlist[airNo].f_s_ele_distension_valve1 == 300) //运行5s
			{

				iLastTime = GetTickCount();
				iStep += 1;
				if (F_FFLP1 - pdoc->airlist[airNo].f_s_lowpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统3压力");
					vecErr.push_back(strRight + "系统3压力");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统3压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统3压力");
					vecErr.push_back(strWrong + "系统3压力");
					MessAddString("系统3电子膨胀阀关阀异常,检查接线");
					errflag = 1;
				}

			}
			if (iStep == 691 && (GetTickCount() - iLastTime) >= 100) //运行5s
			{
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 120;
				}
			}
			if (iStep == 692 && (GetTickCount() - iLastTime) >= 200) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 1;
				MessAddString("系统4电子膨胀阀开到300");
				SetExv(0, 300, 6);
				CArchive outfile(&logFile, CArchive::store);
				F_FFLP2 = pdoc->airlist[airNo].f_s_highpre;
				outfile.WriteString(GetCurTime());
				tempstr.Format("FLP4=%.1f\r\n", pdoc->airlist[airNo].f_s_highpre);
				outfile.WriteString(tempstr);
				outfile.Close();
			}
			if (iStep == 693 && (GetTickCount() - iLastTime) >= 45000 && pdoc->airlist[airNo].f_s_ele_distension_valve2 == 300) //运行5s
			{

				iLastTime = GetTickCount();
				iStep += 118;
				if (F_FFLP2 - pdoc->airlist[airNo].f_s_highpre > 2.0f)
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4压力正常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strRight + "系统4压力");
					vecErr.push_back(strRight + "系统4压力");
				}
				else
				{
					CArchive outfile(&logFile, CArchive::store);
					outfile.WriteString(GetCurTime()); outfile.WriteString(" 系统4压力异常\r\n");
					outfile.Close();
					m_alarmlist3.AddString(strWrong + "系统4压力");
					vecErr.push_back(strWrong + "系统4压力");
					MessAddString("系统4电子膨胀阀关阀异常,检查接线");
					errflag = 1;
				}
			}
			if (iStep == 811 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				MessAddString("关闭所有动作");
				SetFourValve1(0, 0);
				iLastTime = GetTickCount();
				iStep += 2;
				SetMachine(1, 0);//压缩机1  启动1
			}
			if (iStep == 813 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO11 == 0) //运行5s
			{
				SetMachine(2, 0);//压缩机1  启动1
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 814 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO12 == 0) //运行5s
			{
				if (pdoc->airlist[airNo].DOF11 == 0)
				{
					iStep += 1;
				}
				else {
					SetMachine(3, 0);//压缩机1  启动1
				}
				iLastTime = GetTickCount();
			}
			if (iStep == 815 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF11 == 0) //运行5s
			{
				SetFan2High(0, 0);
				iStep += 1;
			}
			if (iStep == 816 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO7 == 0) //运行5s
			{
				SetFan2low(0, 0);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 817 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO8 == 0) //运行5s
			{
				SetFan1High(0, 0);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 818 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO9 == 0) //运行5s
			{
				SetFan1Low(0, 0);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 819 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO10 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF7 == 0)
				{
					iStep += 1;
				}
				else { SetFan3(0, 0, 1); }
			}
			if (iStep == 820 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (pdoc->airlist[airNo].DOF8 == 0)
				{
					iStep += 1;
				}
				else { SetFan3(0, 0, 2); }
				iLastTime = GetTickCount();
			}
			if (iStep == 821 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF8 == 0) //运行5s
			{
				SetExv(0, 300, 1);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 822 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].s_ele_distension_valve1 == 300) //运行5s
			{
				SetExv(0, 300, 2);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 823 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].s_ele_distension_valve2 == 300) //运行5s
			{
				SetExv(0, 300, 3);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 824 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].s_ele_distension_valve3 == 300) //运行5s
			{
				SetExv(0, 300, 4);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 825 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].s_ele_distension_valve4 == 300) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve1 == 300)
				{
					iStep += 1;
				}
				else { SetExv(0, 300, 5); }
				iLastTime = GetTickCount();
			}
			if (iStep == 826 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				SetFourValve(0, 0, 1);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 827 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO5 == 0) //运行5s
			{
				SetFourValve(0, 0, 2);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 828 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DO6 == 0) //运行5s
			{
				SetFourValve(0, 0, 3);
				iLastTime = GetTickCount();
				iStep += 1;
			}
			if (iStep == 829 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF5 == 0) //运行5s
			{
				if (stricmp(models_tag, "1600") == 0)
				{
					iStep += 1;
				}
				else
				{
					iStep += 11;
				}
			}
			if (iStep == 830 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (pdoc->airlist[airNo].DOF12 == 0)
				{
					iStep += 1;
				}
				else {
					SetMachine(4, 0);//压缩机1  启动1
				}
				iLastTime = GetTickCount();
			}
			if (iStep == 831 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF9 == 0)
				{
					iStep += 1;
				}
				else { SetFan4(0, 0, 1); }
			}
			if (iStep == 832 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF9 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF10 == 0)
				{
					iStep += 1;
				}
				else { SetFan4(0, 0, 2); }
			}
			if (iStep == 833 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF10 == 0) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve2 == 300)
				{
					iStep += 1;
				}
				else { SetExv(0, 300, 6); }
				iLastTime = GetTickCount();
			}
			if (iStep == 834 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve3 == 300)
				{
					iStep += 1;
				}
				else { SetExv(0, 300, 7); }
				iLastTime = GetTickCount();
			}
			if (iStep == 835 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				if (pdoc->airlist[airNo].f_s_ele_distension_valve4 == 300)
				{
					iStep += 2;
				}
				else { SetExv(0, 300, 8); }
				iLastTime = GetTickCount();
			}
			if (iStep == 837 && (GetTickCount() - iLastTime) >= 50) //运行5s
			{
				iLastTime = GetTickCount();
				if (pdoc->airlist[airNo].DOF6 == 0)
				{
					iStep += 1;
				}
				else { SetFourValve(0, 0, 4); }
			}
			if (iStep == 838 && (GetTickCount() - iLastTime) >= 50 && pdoc->airlist[airNo].DOF6 == 0) //运行5s
			{
				iLastTime = GetTickCount();
				iStep += 2;
			}
			if (iStep == 840) //总结分析结果
			{
				iStep += 10;
				ordersum = 0;
				m_static_title.SetFontSize(48, 32);
				m_static_title.SetFontColor(0, 0, 255);
				m_static_title.GetWindowTextA(m_static_title.Caption);
				m_static_title.ShowWindow(false);
				//2020.7.7
								//int iyun = m_cmb_yun.GetCurSel();
								//if (iyun == 0)//数据需要上云0401
								//{
								//	if (!loginService->LoginKpi())
								//	{
								//		CArchive outfile(&logFile, CArchive::store);
								//		outfile.WriteString(GetCurTime()); outfile.WriteString(" 数据上报到云平台失败!\r\n");
								//		outfile.Close();
								//		MessAddString("数据上报到云平台失败!");
								//		m_alarmlist3.AddString(strWrong + "数据上报到云平台");
								//		vecErr.push_back(strWrong + "数据上报到云平台");
								//		errflag = 1;
								//	}
								//}

				SetDataForFunNo26(0);//退出测试模式
				//停机
				KillTimer(6);
				//xg 180410 实时显示测试详细结果
				int count = m_alarmlist3.GetCount();
				for (int i = count; i != vecErr.size(); i++)
				{
					m_alarmlist3.AddString(vecErr[i]);
				}
				MessAddString("测试结束");
				CArchive outfile(&logFile, CArchive::store);
				outfile.WriteString(GetCurTime()); outfile.WriteString(" 设置停机\r\n");
				outfile.Close();
				//记录错误
				CFile errFile, printFile;
				CString strErrFile, strPrintFile, str1, str2, str3, str4, str5, strInfo;
				m_userinfo1.GetWindowText(str1);
				m_userinfo2.GetWindowText(str2);
				m_userinfo3.GetWindowText(str3);
				m_userinfo4.GetWindowText(str4);
				m_userinfo7.GetWindowText(str5);
				strErrFile.Format(_T("%s_%s_%s_测试结果.txt"), valstr3, str2, str3);
				strPrintFile.Format(_T("%s_%s_%s.txt"), valstr3, str2, str3);		//打印标签
				errFile.Open(strErrFile, CFile::modeReadWrite | CFile::modeCreate | CFile::shareDenyNone, NULL);
				printFile.Open(strPrintFile, CFile::modeReadWrite | CFile::modeCreate | CFile::shareDenyNone, NULL);
				CArchive ar(&errFile, CArchive::store);
				CArchive ar2(&printFile, CArchive::store);
				//打印测试结果
				logFile.Close();
				if (errflag == 0)
				{
					CTime tempTime = CTime::GetCurrentTime();
					tempstr.Format("%2.2d-%.2d-%.2d %.2d:%.2d:%.2d\r\n", tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
					ar.WriteString(tempstr);
					if (!vecErr.empty())
					{

						for (int i = 0; i != vecErr.size(); i++)
							ar.WriteString(vecErr[i] + "\r\n");
					}
					else
						ar.WriteString("无异常!\r\n");
					ar.Close();
					errFile.Close();
					CString strTemp;
					strTemp = _T("合格");
					for (int k = 0; k != vecErr.size(); k++)
					{
						if (vecErr[k].Find(_T("×")) == 0)
						{
							strTemp = _T("不合格");
							errflag = 1;
							break;
						}
					}
					strInfo.Format("机组型号:%s\r\nGPS IMEL:%s机组编号:%s\r\n生产日期:%s\r\n测试时间:%s\r\n测试人员:%s\r\n测试结果:%s",
						valstr3, str5, str2, str3, tempstr, str4, strTemp);
					ar2.WriteString(strInfo);
					ar2.Close();
					printFile.Close();
					char winexebuff[100];
					strcpy(winexebuff, "Notepad.exe ");
					strcat(winexebuff, strPrintFile.GetBuffer(40));
					WinExec(winexebuff, SW_SHOW);
				}
				else
				{
					CString  tempstr, tempstrok, tempstrcan;
					tempstr = "测试不合格,是否认为误判?是否修改测试记录?";
					tempstrok = "是";
					tempstrcan = "否";
					MESSAGEBOXDLG dlg;
					dlg.m_content = tempstr;
					dlg.m_okcontent = tempstrok;
					dlg.m_cancontent = tempstrcan;
					dlg.m_okvisable = 1;
					dlg.m_canvisable = 1;
					INT_PTR nResponse = dlg.DoModal();
					if (nResponse == IDOK)
					{
						CTime tempTime = CTime::GetCurrentTime();
						tempstr.Format("%2.2d-%.2d-%.2d %.2d:%.2d:%.2d\r\n", tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
						ar.WriteString(tempstr);
						if (!vecErr.empty())
						{

							for (int i = 0; i != vecErr.size(); i++)
								ar.WriteString(vecErr[i] + "\r\n");
						}
						else
							ar.WriteString("无异常!\r\n");
						ar.Close();
						errFile.Close();
						CString strTemp;
						strTemp = _T("合格");
						strInfo.Format("机组型号:%s\r\nGPS IMEL:%s机组编号:%s\r\n生产日期:%s\r\n测试时间:%s\r\n测试人员:%s\r\n测试结果:%s",
							valstr3, str5, str2, str3, tempstr, str4, strTemp);
						ar2.WriteString(strInfo);
						ar2.Close();
						printFile.Close();
						char winexebuff[100];
						strcpy(winexebuff, "Notepad.exe ");
						strcat(winexebuff, strPrintFile.GetBuffer(40));
						WinExec(winexebuff, SW_SHOW);
					}
					else
					{
						CTime tempTime = CTime::GetCurrentTime();
						tempstr.Format("%2.2d-%.2d-%.2d %.2d:%.2d:%.2d\r\n", tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
						ar.WriteString(tempstr);
						if (!vecErr.empty())
						{

							for (int i = 0; i != vecErr.size(); i++)
								ar.WriteString(vecErr[i] + "\r\n");
						}
						else
							ar.WriteString("无异常!\r\n");
						ar.Close();
						errFile.Close();
						CString strTemp;
						strTemp = _T("合格");
						for (int k = 0; k != vecErr.size(); k++)
						{
							if (vecErr[k].Find(_T("×")) == 0)
							{
								strTemp = _T("不合格");
								errflag = 1;
								break;
							}
						}
						strInfo.Format("机组型号:%s\r\nGPS IMEL:%s机组编号:%s\r\n生产日期:%s\r\n测试时间:%s\r\n测试人员:%s\r\n测试结果:%s",
							valstr3, str5, str2, str3, tempstr, str4, strTemp);
						ar2.WriteString(strInfo);
						ar2.Close();
						printFile.Close();
						char winexebuff[100];
						strcpy(winexebuff, "Notepad.exe ");
						strcat(winexebuff, strPrintFile.GetBuffer(40));
						WinExec(winexebuff, SW_SHOW);
					}
				}
				AfxMessageBox(_T("测试结束"));
				m_userinfo1.SetWindowText("");//分开字符后，清空扫码枪内容20191010
				m_userinfo2.SetWindowText("");//分开字符后，清空扫码枪内容20191010
				m_userinfo3.SetWindowText("");//分开字符后，清空扫码枪内容20191010
				m_userinfo5.SetWindowText("");//分开字符后，清空扫码枪内容20191010				
			}
		}

	}
End0:
	if (nIDEvent == 4)//定时器更新
	{
		;
	}

	if (nIDEvent == 5)//MYDog	
	{//加密狗心跳定时;	
		//	if (!theApp.QueryResponseOfDog(theApp.WhoAreYou,theApp.QueryOffsetPoint))
		if (!theApp.QuerySafeNet_EK())//2012-08-06
		{//检测失败，加密狗停止心跳； 软件死了:(
			ShowInformation(theApp.HintStrExit);
			//	HintStrExit.ReleaseBuffer();

			KillTimer(5);
			//	theApp.ExitDataThread();
			theApp.YourDogIsHere = false;//狗已不存；//MYDog	
			Sleep(2000);

			delete WaitingPDf;//清除提示窗口；
			::PostMessage(frame->m_hWnd, WM_CLOSE, 0, 0);
		}
	}
	CFormView::OnTimer(nIDEvent);
}

void CMDSView::ShowInformation(CString& InforStr)//显示信息框；
{
	WaitingPDf = new waitpdf;

	WaitingPDf->Create(IDD_WAITPDF);


	WaitingPDf->RefreshString(InforStr);
	WaitingPDf->MoveWindow(130, 130, 300, 100);
	WaitingPDf->ShowWindow(1);
	WaitingPDf->UpdateWindow();
	return;
}
void CMDSView::OnConnectbtn()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString temppath = logFile.GetFileName();
	m_button.ShowWindow(FALSE);
	if (temppath != "")
	{
		logFile.Close();  //xu170111
	}
	CMainFrame* frame;
	frame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CPassworddlg dlg;
	int iyun = m_cmb_yun.GetCurSel();//是否需要把数据记录到云平台0401
	int i;
	timing = 0, timing1 = 0, timing2 = 0, timing3 = 0, timing4 = 0, timing5 = 0, timing6 = 0, timing7 = 0;
	timing8 = 0, timing9 = 0, timing10 = 0, timing11 = 0, timing12 = 0, timing13 = 0, timing14 = 0, timing15 = 0;
	if (pdoc->m_connectflag == 0)
	{
		m_alarmlist2.ResetContent();//4.16 
		m_alarmlist3.ResetContent();
		m_alarmlist2.UpdateWindow();
		m_alarmlist3.UpdateWindow();

		CString str3, str4, str5, strNull = _T("");
		char st1[500], st2[500], st3[500], saomachr[500];
		if (m_bInput == 0)
		{
			m_userinfo5.GetWindowText(str5);//1 EKAC460BR1-FEA00000718 190117      共31个字符
			int strlen5 = str5.GetLength();
			if ((strlen5 > 40) || (strlen5 < 20))
			{
				AfxMessageBox(_T("机组信息扫码输入错误"));
				return;
			}
			if (str5 != strNull)
			{//分析扫码字符串
				strcpy(saomachr, str5);
				int len;
				len = strlen(saomachr);
				if (len > 16)
				{
					saomachr[len] = 0;
					strcpy(st3, &saomachr[len - 6]);

					saomachr[len - 7] = 0;
					strcpy(st2, &saomachr[len - 15]);

					saomachr[len - 15] = 0;
					strcpy(st1, &saomachr[2]);
					int st1len, ii;
					st1len = strlen(st1);
					for (ii = 0; ii < st1len; ii++)
						st1[ii] = toupper(st1[ii]);

					valstr1.Format("%s", st1);
					valstr2.Format("%s", st2);
					str3.Format("%s", st3);

					m_userinfo1.SetWindowText(valstr1);
					m_userinfo2.SetWindowText(valstr2);
					m_userinfo3.SetWindowText(str3);

				}


			}
		}

		CString str7;
		if (m_bGPSInput == 0)
		{
			m_userinfo7.GetWindowText(str7);//1 EKAC460BR1-FEA00000718 190116      共31个字符
			if (iyun == 0)//数据需要上云0401
			{
				int strlen7 = str7.GetLength();
				if (strlen7 != 15)
				{
					AfxMessageBox(_T("GPS IMEL信息扫码输入错误"));
					return;
				}
			}

		}
		valstr3 = valstr1;//记录文件命名记录
		valstr3.Replace('/', '-');
		m_userinfo1.GetWindowText(valstr1);
		valstr1.Remove(' ');
		if (m_bFunhavelow == 0)
		{
			if (stricmp(valstr1, "LR550D") == 0)
				valstr1 = "AH1600CHS1-FBB";

		}
		else
		{
			if (stricmp(valstr1, "ZJLR550D") == 0)
				valstr1 = "EKAH1600CHS1-FBB";
		}
		m_userinfo2.GetWindowText(valstr2);
		m_userinfo3.GetWindowText(str3);
		m_userinfo4.GetWindowText(str4);
		CString b, c;
		valstr1.Remove(' ');
		if (m_bFunhavelow == 1)
			b = valstr1.Left(8);
		else
			b = valstr1.Left(6);
		models_tag = b.Right(4);
		if (stricmp(valstr1, "HFRW-460FGF/AE") == 0 || stricmp(valstr1, "RW-460FGF/AE") == 0)
			models_tag = "1600";
		if (stricmp(valstr1, "HFRW-510FGF/EH") == 0 || stricmp(valstr1, "RW-510FGF/EH") == 0)
			models_tag = "1600";
		if (valstr1 == strNull || valstr2 == strNull || str3 == strNull || str4 == strNull)
		{
			AfxMessageBox(_T("机组型号/机组编号/生产日期/测试人员 不能为空"));
			return;
		}

		strcpy(testname, str4);
		_SaveInputNAMESet(testname);

		m_userinfo7.GetWindowText(str7);

		if (iyun == 0)//数据需要上云0401
		{
			if (str7 == strNull)
			{
				AfxMessageBox(_T("GPS IMEL 信息不能为空"));
				return;
			}
			int strlen7 = str7.GetLength();
			if (strlen7 != 15)
			{
				AfxMessageBox(_T("GPS IMEL信息输入错误"));
				return;
			}
		}

		GetDlgItem(IDC_AUTOTEST)->EnableWindow(FALSE);
		GetDlgItem(IDC_CONNECTBTN)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_HANDINPUT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_SAOMA))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_GPS_HANDINPUT))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_GPS_SAOMA))->EnableWindow(FALSE);
		if (iyun == 0)//数据需要上云0401
		{
			//访问欧科云平台		
			  //  m_alarmlist2.ResetContent();
			//	m_alarmlist3.ResetContent();
			MessAddString("正在登陆欧科云平台...");
			//		m_alarmlist2.UpdateWindow();
			CString strUsername;
			CString strPassword;
			CString strModelImel;
			CString password;
			password.Format("%s", yun_password);
			strUsername = "ek-produce";
			strPassword = password;
			strModelImel = str7;
			VAL1.Format("1 %s", valstr1);
			VAL2.Format(" %s", valstr2);
			VAL3.Format(" %s", str3);
			loginService = new LoginService(strUsername.GetBuffer(0), strPassword.GetBuffer(0), strModelImel.GetBuffer(0), VAL1.GetBuffer(0), VAL2.GetBuffer(0), VAL3.GetBuffer(0));
			if (!loginService->Login())
				//	if(0)
			{
				MessageBox(_T("登录欧科云平台失败!"), _T("提示"), MB_OK);
				//return;
			}
			else
			{
				MessAddString("成功登陆欧科云平台");
				MessAddString("按 开启自动测试 按钮开始测试");
			}

		}
		//xu161226 初始化
		pdoc->queryFunNo = 23;//进入测试模式
		pdoc->queryAirNo = 0;
		iStep = 10;
		for (i = 0; i != NUM_SENDCMD; i++)
			bSendCmd[i] = FALSE;
		vecErr.clear();
		logFile.Open("testLog.txt", CFile::modeReadWrite | CFile::modeCreate | CFile::shareDenyNone, NULL);


		pdoc->set_comm();
		pdoc->m_connectflag = 1;
		if (theApp.m_bLanguage == 0)
			m_connectbtn.SetWindowText("断开");
		else if (theApp.m_bLanguage == 1)
			m_connectbtn.SetWindowText("Disconnect");
		m_testcodebt.EnableWindow(FALSE);
		m_outnumberedit.EnableWindow(FALSE);

		//更新机组数量
		UpdateData(TRUE);
		if ((m_outnumber < 1) || (m_outnumber > 32))
		{
			m_outnumberedit.SetWindowText("1");
			m_outnumber = 1;
		}
		pdoc->airnum = m_outnumber;
		CString tempstr;
		for (i = m_airno.GetCount() - 1; i >= 0; i--)
			m_airno.DeleteString(i);
		for (i = 0; i < pdoc->airnum; i++)
		{
			tempstr.Format("%d#", i);
			m_airno.InsertString(-1, tempstr);
		}
		m_airno.SetCurSel(0);

		SetTimer(1, 100, NULL);
		SetTimer(2, 1000, NULL);
		SetTimer(3, 2000, NULL);
		//		SetTimer(6,800,NULL); //xu161226,定时发送命令
		UpdateData(TRUE);
		if (m_inifalg == 1)
		{
			pdoc->queryFunNo = 1;
			pdoc->queryAirNo = 0;
			pdoc->m_startflag = 0;
		}
		if (pdoc->m_startflag == 1)
		{
			if (theApp.m_bLanguage == 0)
				frame->m_wndStatusBar.SetPaneText(2, "初始化完成", TRUE);
			else if (theApp.m_bLanguage == 1)
				frame->m_wndStatusBar.SetPaneText(2, "Initialization completed", TRUE);
		}
		pdoc->m_starttime = CTime::GetCurrentTime();
		GetDlgItem(IDC_AUTOTEST)->EnableWindow(TRUE);
		GetDlgItem(IDC_CONNECTBTN)->EnableWindow(TRUE);
		//		CFile fl(_T("050601.mdsdata"),CFile::modeReadWrite);
		//		fl.Close();

		CString filename;
		CTime t = CTime::GetCurrentTime();
		i = 0;
		for (int tf = 0; tf < 100; tf++)
		{
			//filename.Format("%2.2d%.2d%.2d_%.2d\.txt",t.GetYear(),t.GetMonth(),t.GetDay(),i);
			filename.Format("%s%s_%.2d\.CSV", valstr3, valstr2, tf);
			if (pdoc->m_file[i].Open(filename, CFile::modeReadWrite | CFile::shareDenyNone, NULL))
			{
				//pdoc->m_file[i].SeekToEnd();
				pdoc->m_file[0].Close();//如果打开了这个文件，则要关闭，重新打开一个以这个文件加01,02这样的文件，表示第一次测，第二次测

			}
			else
			{
				pdoc->m_file[i].Open(filename, CFile::modeReadWrite | CFile::modeCreate | CFile::shareDenyNone, NULL);
				pdoc->m_recordstr.Format("记录日期:%2.2d-%.2d-%.2d\r\n机组号:%.2d\r\n软件版本%s\r\n F1~2---系统1风机1,2 F11~2---系统2风机1,2， F21~2---系统3风机1,2 ，F31~2---系统4风机1,2， S1~2---电磁阀1~2  CS1~4---系统1~4压缩机 Wa~d---系统1~3四通阀a~d  E1~4---系统1~4电子膨胀阀 EF1~4---系统副板1~4电子膨胀阀\r\n过热度---实际过热度  TSH--目标过热度 HIC---HIC回路目标过冷度\r\n", t.GetYear(), t.GetMonth(), t.GetDay(), i, theApp.SoftVer);
				pdoc->m_recordstr += "\r\n时间,模式,F1, F2, F11, F12, F21, F22, F31,F32, CS1, CS2, CS3, CS4,Wa,Wb ,Wc,Wd, E1, E2, E3, E4,EF1, EF2, EF3, EF4,Needhp ,TSH ,lowP1 ,过热度1 ,LowP2,过热度2,lowP3,lowP4, 实过热度3,实过热度4,TH1,TH2, TH3,TH4,TH5,TH6,TH7,TH8 ,TH9, TH10,  TH11 ,  TH12, TH13,TH14,FTH1 , FTH2 , FTH3, FTH4,FTH5, FTH6,FHT7 , FTH8 ,FTH9,FTH10 ,FTH11, FTH12 ,FTH13, FTH14 , 电流1,电流2, 电流3 ,电流4, 机组型号,机组编号 ,版本\r\n";
				CArchive ar(&pdoc->m_file[i], CArchive::store);
				ar.WriteString(pdoc->m_recordstr);
				ar.Close();
				break;
			}

		}



	}
	else
	{
		pdoc->sendcmdflag = 0;
		m_static_title.ShowWindow(FALSE);
		SetDataForFunNo26(0);
		for (i = m_alarmlist.GetCount() - 1; i >= 0; i--)
		{
			m_alarmlist.DeleteString(i);
		}
		//pdoc->queryFunNo = 26;
		m_ctrl1.SetBitmap(m_off);
		m_ctrl2.SetBitmap(m_off);
		m_comm1.SetPortOpen(0);
		pdoc->m_connectflag = 0;
		//m_iniflagchk.ShowWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_HANDINPUT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_SAOMA))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_GPS_HANDINPUT))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO_GPS_SAOMA))->EnableWindow(TRUE);
		if (theApp.m_bLanguage == 0)
			m_connectbtn.SetWindowText("连接");
		else if (theApp.m_bLanguage == 1)
			m_connectbtn.SetWindowText("Connection");
		m_testcodebt.EnableWindow(TRUE);
		m_button11.ShowWindow(FALSE);
		m_button21.ShowWindow(FALSE);
		//	m_outnumberedit.EnableWindow(TRUE);
		if (theApp.m_bLanguage == 0)
			frame->m_wndStatusBar.SetPaneText(0, "串口关闭，已断开连接", TRUE);
		else if (theApp.m_bLanguage == 1)
			frame->m_wndStatusBar.SetPaneText(0, "Serial port closed and disconnected", TRUE);
		frame->m_wndStatusBar.SetPaneText(1, "", TRUE);
		frame->m_wndStatusBar.SetPaneText(2, "", TRUE);
		KillTimer(1);
		KillTimer(2);
		KillTimer(3);
		KillTimer(6);//xu161226
		KillTimer(8);
		KillTimer(9);
		KillTimer(10);
		pdoc->m_file[0].Close();//只测机组0，只关一个文件


	}
}
//在窗口中输出主机的各个数据
void CMDSView::showdata(int No)
{
	CString tempstr, str;
	float f;

	tempstr = "EKAC";
	//能力
	int AHPstr[] = { 180,210,230,460 };
	str.Format("%.3d", AHPstr[pdoc->airlist[No].air_hp]);

	tempstr += str;
	tempstr += 'B';
	//机组类型  1--单冷  0--热泵
	if (pdoc->airlist[No].air_type2 == 0)
		tempstr += "R";
	//if(pdoc->airlist[No].low_type)
	tempstr += "SR";
	m_airtype1.SetWindowText(tempstr);

	//外机程序版本
	int v1, v2, v3;
	v3 = pdoc->airlist[No].out_version / 10;
	v2 = pdoc->airlist[No].out_version % 10;
	v1 = pdoc->airlist[No].out_version_end;
	tempstr.Format("%.1d.%.1d.%.1d", v3, v2, v1);
	m_airversion.SetWindowText(tempstr);

	//内机数量  
	tempstr.Format("%d", pdoc->airlist[No].in_num);
	m_innuber.SetWindowText(tempstr);
	//阀门初始开度
	tempstr.Format("%d", pdoc->airlist[No].air_valve_ini);
	m_hp.SetWindowText(tempstr);

	//状态参数
		//运行模式  0--停机 1--制冷 2--制热 3--自动
		//			4--除霜 5--调试
	CString media_style[3] = { "R22","R410A","R407C" };
	//	if(pdoc->airlist[No].cool_media_type>=0&&pdoc->airlist[No].cool_media_type<=2)
		//	m_edit_media_m.SetWindowText(media_style[pdoc->airlist[No].cool_media_type]);
	CString runmode[3] = { "停机","制热模式","制冷模式" };
	CString runmode_english[8] = { "OFF","Cooling","Heating","Hot water","Defrost","Recycle","Standby","Commissioning" };
	if (moshi >= 0 && moshi <= 6)
	{
		if (theApp.m_bLanguage == 0)
		{
			m_runmode.SetWindowText(runmode[moshi]);
		}
		else
		{
			m_runmode.SetWindowText(runmode_english[moshi]);
		}
	}

	//0--油回收停止 1--油回收运行
	/*if(pdoc->airlist[No].s_oil_reclaim_run==0)
	{
		if(theApp.m_bLanguage==0)
			tempstr.Format("停止");
		else if(theApp.m_bLanguage==1)
			tempstr.Format("Stop");
	}
	else
	{
		if(theApp.m_bLanguage==0)
			tempstr.Format("运行");
		else if(theApp.m_bLanguage==1)
			tempstr.Format("Operation");
	}
	m_oilre.SetWindowText(tempstr)

	//0--油平衡停止 1--油平衡运行
	if(pdoc->airlist[No].s_oil_blance_run==0)
	{
		if(theApp.m_bLanguage==0)
			tempstr.Format("停止");
		else if(theApp.m_bLanguage==1)
			tempstr.Format("Stop");
	}
	else
	{
		if(theApp.m_bLanguage==0)
			tempstr.Format("运行");
		else if(theApp.m_bLanguage==1)
			tempstr.Format("Operation");
	}
	m_oilblance.SetWindowText(tempstr);;*/


	//系统1风机1
	if (pdoc->airlist[No].DO7 == 0)
	{
		m_edbldc_speed1.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DO7 == 1)
	{
		m_edbldc_speed1.SetWindowText("高速");
	}
	//系统1风机2
	if (pdoc->airlist[No].DO8 == 0)
	{
		m_edbldc_speed2.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DO8 == 1)
	{
		m_edbldc_speed2.SetWindowText("高速");
	}
	//系统2风机1
	if (pdoc->airlist[No].DO9 == 0)
	{
		m_fan3.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DO9 == 1)
	{
		m_fan3.SetWindowText("高速");
	}
	//系统2风机2
	if (pdoc->airlist[No].DO10 == 0)
	{
		m_fan4.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DO10 == 1)
	{
		m_fan4.SetWindowText("高速");
	}
	//系统3风机1
	if (pdoc->airlist[No].DOF7 == 0)
	{


		m_exv2_216.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DOF7 == 1)
	{
		m_exv2_216.SetWindowText("高速");
	}
	//系统3风机2
	if (pdoc->airlist[No].DOF8 == 0)
	{
		m_exv5_216.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DOF8 == 1)
	{
		m_exv5_216.SetWindowText("高速");
	}
	//系统4风机1
	if (pdoc->airlist[No].DOF9 == 0)
	{
		m_exv3_216.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DOF9 == 1)
	{
		m_exv3_216.SetWindowText("高速");
	}
	//系统4风机2
	if (pdoc->airlist[No].DOF10 == 0)
	{
		m_exv6_216.SetWindowText("停止");
	}
	else if (pdoc->airlist[No].DOF10 == 1)
	{
		m_exv6_216.SetWindowText("高速");
	}
	/////////////////////////////////////////////////////////压缩机状态/ah1000
		//压缩机1状态 0--关 1--开
	tempstr.Format("%d", pdoc->airlist[No].s_comp1_real);
	m_comp1.SetWindowText(tempstr);
	tempstr.Format("%d", pdoc->airlist[No].s_comp2_real);
	m_comp2.SetWindowText(tempstr);
	tempstr.Format("%d", pdoc->airlist[No].s_comp3_real);
	m_f4wv1.SetWindowText(tempstr);
	tempstr.Format("%d", pdoc->airlist[No].s_comp4_real);
	m_ffan2.SetWindowText(tempstr);
	/////////////////////////////////////////////////////////风机状态/ah1000
	tempstr.Format("%d", pdoc->airlist[No].s_fan1_real);
	m_edbldc_speed1.SetWindowText(tempstr);
	tempstr.Format("%d", pdoc->airlist[No].s_fan2_real);
	m_edbldc_speed2.SetWindowText(tempstr);
	tempstr.Format("%d", pdoc->airlist[No].s_fan3_real);
	m_exv2_216.SetWindowText(tempstr);
	tempstr.Format("%d", pdoc->airlist[No].s_fan4_real);
	m_exv5_216.SetWindowText(tempstr);
	//压缩机1状态 0--关 1--开
	//if (pdoc->airlist[No].DO11 == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关闭");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("Close");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_comp1.SetWindowText(tempstr);

	//压缩机2状态 0--关 1--开
	//if (pdoc->airlist[No].DO12 == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关闭");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("Close");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_comp2.SetWindowText(tempstr);

	//压缩机3状态 0--关 1--开
	//if (pdoc->airlist[No].DOF11 == 0)
	//{
	//	tempstr.Format("关闭");
	//}
	//else
	//{
	//	tempstr.Format("开");
	//}
	//m_f4wv1.SetWindowText(tempstr);

	//压缩机4状态 0--关 1--开
	//if (pdoc->airlist[No].DOF12 == 0)
	//{
	//	tempstr.Format("关闭");
	//}
	//else
	//{
	//	tempstr.Format("开");
	//}
	//m_ffan2.SetWindowText(tempstr);
	/*
  //压缩机5状态 0--关 1--开
	if(pdoc->airlist[No].s_compre[4]==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_comp5.SetWindowText(tempstr);

  //压缩机6状态 0--关 1--开
	if(pdoc->airlist[No].s_compre[5]==0)
		tempstr.Format("关闭");
	else
		tempstr.Format("开");
	m_comp6.SetWindowText(tempstr);*/

	//四通阀1状态 0--关 1--开
	if (pdoc->airlist[No].DO5 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_fourvalve1.SetWindowText(tempstr);

	//四通阀2状态 0--关 1--开
	if (pdoc->airlist[No].DO6 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_fourvalve2.SetWindowText(tempstr);

	//四通阀3状态 0--关 1--开
	if (pdoc->airlist[No].DOF5 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_4wv3.SetWindowText(tempstr);
	if (pdoc->airlist[No].DOF6 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_4wv4.SetWindowText(tempstr);

	//电磁阀0 0--关 1--开
	//if (pdoc->airlist[No].DO17 == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关闭");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("Close");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_esv1.SetWindowText(tempstr);

	////电磁阀1 0--关 1--开
	//if (pdoc->airlist[No].DO18 == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关闭");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("Close");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_esv2.SetWindowText(tempstr);

	//if (pdoc->airlist[No].DO16 == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关闭");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("Close");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_esv3.SetWindowText(tempstr);

	//if (pdoc->airlist[No].s_ele_valve3 == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关闭");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("Close");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_esv4.SetWindowText(tempstr);

	//水泵
	if (pdoc->airlist[No].s_pumpstate == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("停止");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Stop");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("运行");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Operation");
	}
	m_pumpedit.SetWindowText(tempstr);

	if (pdoc->airlist[No].s_pump2state == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("停止");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Stop");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("运行");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Operation");
	}
	m_edit_pump2.SetWindowText(tempstr);
	//辅热
	if (pdoc->airlist[No].s_ahot == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_ahot.SetWindowText(tempstr);

	//电加热
	if (pdoc->airlist[No].s_ehot == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_ehot.SetWindowText(tempstr);

	//if (pdoc->airlist[No].hot_eheat == 0)
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("关");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("OFF");
	//}
	//else
	//{
	//	if (theApp.m_bLanguage == 0)
	//		tempstr.Format("开");
	//	else if (theApp.m_bLanguage == 1)
	//		tempstr.Format("ON");
	//}
	//m_edithot_eheat.SetWindowText(tempstr);

	//电磁膨胀阀1开度
	tempstr.Format("%d", pdoc->airlist[No].s_ele_distension_valve1);
	m_eledisten1.SetWindowText(tempstr);

	//电磁膨胀阀2开度
	tempstr.Format("%d", pdoc->airlist[No].s_ele_distension_valve2);
	m_eledisten2.SetWindowText(tempstr);

	//电磁膨胀阀3开度
	tempstr.Format("%d", pdoc->airlist[No].s_ele_distension_valve3);
	m_eledisten3.SetWindowText(tempstr);

	//电磁膨胀阀4开度
	tempstr.Format("%d", pdoc->airlist[No].s_ele_distension_valve4);
	m_eledisten4.SetWindowText(tempstr);

	//总能力需求(单位HP)
	tempstr.Format("%.1fHP", pdoc->airlist[No].s_total_needed_HP);
	m_totalneedhp.SetWindowText(tempstr);

	//数码压缩机PWM输出百分比
//	tempstr.Format("%d%%",pdoc->airlist[No].s_datacompre_PWM);
//	m_pwmout.SetWindowText(tempstr);

	//TP1
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp1);
	m_tp1.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp1 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			m_tp1.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp1.SetWindowText("Short");
	}
	else
	{
		if (pdoc->airlist[No].s_tp1 <= 5)
		{
			if (theApp.m_bLanguage == 0)
				m_tp1.SetWindowText("开路");
			else if (theApp.m_bLanguage == 1)
				m_tp1.SetWindowText("Open");
		}
	}

	//TP2
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp2);
	m_tp2.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp2 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			m_tp2.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp2.SetWindowText("Short");
	}
	else
	{
		if (pdoc->airlist[No].s_tp2 <= 5)
		{
			if (theApp.m_bLanguage == 0)
				m_tp2.SetWindowText("开路");
			else if (theApp.m_bLanguage == 1)
				m_tp2.SetWindowText("Open");
		}
	}

	//TP3
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp3);
	m_tp3.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp3 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp3.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp3.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp3 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp3.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp3.SetWindowText("Open");
	}

	//TP4
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp4);
	m_tp4.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp4 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp4.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp4.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp4 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp4.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp4.SetWindowText("Open");
	}


	//TP5
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp5);
	m_tp5.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp5 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp5.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp5.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp5 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp5.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp5.SetWindowText("Open");
	}

	//TP6
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp6);
	m_tp6.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp6 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp6.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp6.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp6 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp6.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp6.SetWindowText("Open");
	}

	//TP7
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp7);
	m_tp7.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp7 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp7.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp7.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp7 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp7.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp7.SetWindowText("Open");
	}

	//TP8
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp8);
	m_tp8.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp8 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp8.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp8.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp8 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp8.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp8.SetWindowText("Open");
	}


	//TP9
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp9);
	m_tp9.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp9 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp9.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp9.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp9 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp9.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp9.SetWindowText("Open");
	}


	//TP10
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp10);
	m_tp10.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp10 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp10.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp10.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp10 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp10.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp10.SetWindowText("Open");
	}


	//TP11
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp11);
	m_tp11.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp11 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp11.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp11.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp11 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp11.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp11.SetWindowText("Open");
	}


	//TP12
	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp12);
	m_tp12.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp12 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp12.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tp12.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp12 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp12.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp12.SetWindowText("Open");
	}

	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp13);
	m_tph13.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp13 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tph13.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tph13.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp13 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tph13.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tph13.SetWindowText("Open");
	}


	tempstr.Format("%.1f℃", pdoc->airlist[No].s_tp14);
	m_tph14.SetWindowText(tempstr);
	if (pdoc->airlist[No].s_tp14 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_tph14.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_tph14.SetWindowText("Short");
	}
	if (pdoc->airlist[No].s_tp14 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tph14.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tph14.SetWindowText("Open");
	}

	//TP1
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp1);
	m_ftp1.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp1 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp1.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp1.SetWindowText("Short");
	}
	else
	{
		if (pdoc->airlist[No].f_s_tp1 <= 5)
		{
			if (theApp.m_bLanguage == 0)
				m_ftp1.SetWindowText("开路");
			else if (theApp.m_bLanguage == 1)
				m_ftp1.SetWindowText("Open");
		}
	}

	//TP2
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp2);
	m_ftp2.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp2 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp2.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp2.SetWindowText("Short");
	}
	else
	{
		if (pdoc->airlist[No].f_s_tp2 <= 5)
		{
			if (theApp.m_bLanguage == 0)
				m_ftp2.SetWindowText("开路");
			else if (theApp.m_bLanguage == 1)
				m_ftp2.SetWindowText("Open");
		}
	}

	//TP3
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp3);
	m_ftp3.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp3 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp3.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp3.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp3 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp3.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp3.SetWindowText("Open");
	}

	//TP4
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp4);
	m_ftp4.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp4 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp4.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp4.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp4 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp4.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp4.SetWindowText("Open");
	}


	//TP5
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp5);
	m_ftp5.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp5 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp5.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp5.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp5 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp5.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp5.SetWindowText("Open");
	}

	//TP6
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp6);
	m_ftp6.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp6 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp6.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp6.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp6 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp6.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp6.SetWindowText("Open");
	}

	//TP7
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp7);
	m_ftp7.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp7 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp7.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp7.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp7 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp7.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp7.SetWindowText("Open");
	}

	//TP8
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp8);
	m_ftp8.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp8 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp8.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp8.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp8 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp8.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp8.SetWindowText("Open");
	}


	//TP9
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp9);
	m_ftp9.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp9 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp9.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp9.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp9 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp9.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp9.SetWindowText("Open");
	}


	//TP10
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp10);
	m_ftp10.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp10 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp10.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp10.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp10 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_tp10.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_tp10.SetWindowText("Open");
	}


	//TP11
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp11);
	m_ftp11.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp11 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp11.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp11.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp11 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp11.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp11.SetWindowText("Open");
	}


	//TP12
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp12);
	m_ftp12.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp12 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp12.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp12.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp12 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp12.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp12.SetWindowText("Open");
	}

	//TP13
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp13);
	m_ftp13.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp13 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp13.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp13.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp13 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp13.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp13.SetWindowText("Open");
	}

	//TP14
	tempstr.Format("%.1f℃", pdoc->airlist[No].f_s_tp14);
	m_ftp14.SetWindowText(tempstr);
	if (pdoc->airlist[No].f_s_tp14 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp14.SetWindowText("短路");
		else if (theApp.m_bLanguage == 1)
			m_ftp14.SetWindowText("Short");
	}
	if (pdoc->airlist[No].f_s_tp14 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			m_ftp14.SetWindowText("开路");
		else if (theApp.m_bLanguage == 1)
			m_ftp14.SetWindowText("Open");
	}

	//实际过热度3
	tempstr.Format("%.1f", pdoc->airlist[No].s_factsuperhot3);
	m_highpre1.SetWindowText(tempstr);

	//实际过热度4
	tempstr.Format("%.1f", pdoc->airlist[No].s_factsuperhot4);
	m_highpre2.SetWindowText(tempstr);

	tempstr.Format("%.1fBar", pdoc->airlist[No].s_highpre);
	m_highpre.SetWindowText(tempstr);
	//低压
	tempstr.Format("%.1fBar", pdoc->airlist[No].s_lowpre);
	m_lowpre.SetWindowText(tempstr);

	//系统3低压
	tempstr.Format("%.1fBar", pdoc->airlist[No].f_s_lowpre);
	m_flp1.SetWindowText(tempstr);
	//系统3低压
	tempstr.Format("%.1fBar", pdoc->airlist[No].f_s_highpre);
	m_ffan1.SetWindowText(tempstr);


	tempstr.Format("%.1fA", pdoc->airlist[No].s_ele);
	m_ele1.SetWindowText(tempstr);

	tempstr.Format("%.1fA", pdoc->airlist[No].s_ele2);
	m_ele2.SetWindowText(tempstr);

	tempstr.Format("%.1fA", pdoc->airlist[No].f_s_ele1);
	m_fele1.SetWindowText(tempstr);

	tempstr.Format("%.1fA", pdoc->airlist[No].f_s_ele2);
	m_fcomp3.SetWindowText(tempstr);
	/////////副板
	//高压
	tempstr.Format("%.1fBar", pdoc->airlist[No].f_s_gaoya);
	m_edit_gaoyaf1.SetWindowText(tempstr);
	//高压2
	tempstr.Format("%.1fBar", pdoc->airlist[No].f_s_gaoya2);
	m_edit_gaoyaf2.SetWindowText(tempstr);

	//高压
	tempstr.Format("%.1fBar", pdoc->airlist[No].s_gaoya1);
	m_edit_gaoya1.SetWindowText(tempstr);
	//高压2
	tempstr.Format("%.1fBar", pdoc->airlist[No].s_gaoya2);
	m_edit_gaoya2.SetWindowText(tempstr);


	//电磁膨胀阀1开度
	tempstr.Format("%d", pdoc->airlist[No].f_s_ele_distension_valve1);
	m_eledisten5.SetWindowText(tempstr);

	//电磁膨胀阀2开度
	tempstr.Format("%d", pdoc->airlist[No].f_s_ele_distension_valve2);
	m_eledisten6.SetWindowText(tempstr);

	//电磁膨胀阀3开度
	tempstr.Format("%d", pdoc->airlist[No].f_s_ele_distension_valve3);
	m_eledisten7.SetWindowText(tempstr);

	//电磁膨胀阀4开度
	tempstr.Format("%d", pdoc->airlist[No].f_s_ele_distension_valve4);
	m_eledisten8.SetWindowText(tempstr);

	//tempstr.Format("%d", pdoc->airlist[No].s_exv1_216);
	//m_exv1_216.SetWindowText(tempstr);
	//tempstr.Format("%d", pdoc->airlist[No].s_exv2_216);
	//m_exv2_216.SetWindowText(tempstr);
	//tempstr.Format("%d", pdoc->airlist[No].s_exv3_216);
	//m_exv3_216.SetWindowText(tempstr);
	//tempstr.Format("%d", pdoc->airlist[No].s_exv4_216);
	//m_exv4_216.SetWindowText(tempstr);
	//tempstr.Format("%d", pdoc->airlist[No].s_exv5_216);
	//m_exv5_216.SetWindowText(tempstr);
	//tempstr.Format("%d", pdoc->airlist[No].s_exv6_216);
	//m_exv6_216.SetWindowText(tempstr);
	//	tempstr.Format("%d",pdoc->airlist[No].water_step);
	   // m_wexv_step.SetWindowText(tempstr);

		/*tempstr.Format("%d",pdoc->airlist[No].BLDC_speed1);
		m_edbldc_speed1.SetWindowText(tempstr);



		tempstr.Format("%d",pdoc->airlist[No].BLDC_speed2);
		m_edbldc_speed2.SetWindowText(tempstr);*/

		/*	//除霜检测开始温度(-3~3℃),带符号表示
			tempstr.Format("%d℃",pdoc->airlist[No].s_delfrost_check_start_tp);
			m_dfroststarttp.SetWindowText(tempstr);


			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
			tempstr.Format("%d",pdoc->airlist[No].s_delfrost_set_tp);
			m_dfrosttp.SetWindowText(tempstr);

			//除霜结束温度  (10~50℃	默认15℃)
			tempstr.Format("%d",pdoc->airlist[No].s_delfrost_exit_tp);
			m_dfrostendtp.SetWindowText(tempstr);

			//除霜间隔时间  (0~90min,  默认45min)
			tempstr.Format("%d",pdoc->airlist[No].s_delfrost_intertime);
			m_dfrostintertime.SetWindowText(tempstr);

			//除霜运行时间  (5~25min,  默认10min)
			tempstr.Format("%d",pdoc->airlist[No].s_delfrost_runtime);
			m_dfrostruntime.SetWindowText(tempstr);

			//降噪延迟时间(3~9,默认6)
			tempstr.Format("%d",pdoc->airlist[No].s_delnoise_delaytime);
			m_dnoisedelaytime.SetWindowText(tempstr);
		*/

		//实际过热度
	tempstr.Format("%.1f", pdoc->airlist[No].s_factsuperhot);
	m_factshot.SetWindowText(tempstr);
	tempstr.Format("%.1f", pdoc->airlist[No].s_factsuperhot2);
	m_hicsupercool.SetWindowText(tempstr);
	//目标过热度
	f = (float)pdoc->airlist[No].s_targetsuperhot;
	f /= 10;
	tempstr.Format("%.1f", f);
	m_targetshot.SetWindowText(tempstr);


	//HIC回路目标过冷度
/*	tempstr.Format("%d",pdoc->airlist[No].s_targetsupercool);
	m_hicsupercool.SetWindowText(tempstr);*/

	/*	//控制器当前时间
		CString cweek[7]={"一","二","三","四","五","六","天"};
		tempstr="星期";
		tempstr+=cweek[pdoc->airlist[No].out_week];
		str.Format("   %.2d:%.2d:%.2d",pdoc->airlist[No].out_hour,pdoc->airlist[No].out_minute,pdoc->airlist[No].out_sencond);
		tempstr+=str;
		m_outtime.SetWindowText(tempstr);
		*/
		//if (pdoc->airlist[No].in_num != 0)
		//{
		//	showdata_s(No, m_showNo_s);
		//}
}
//在窗口中输出从机的各个数据
void CMDSView::showdata_s(int No, int No_s)
{


	CString tempstr, str;
	float f;
	tempstr = "EKAC";
	int AHPstr[8] = { 80,100,120,150,180,210,230,240 };
	//	if(pdoc->airlist[No].indoor_air[No])
		//能力
	//	int AHPstr[4]={24,30,36,24};
	if (pdoc->airlist[No].indoor_air[No_s].air_hp < 0 || pdoc->airlist[No].indoor_air[No_s].air_hp>7)//检查防止溢出
		pdoc->airlist[No].indoor_air[No_s].air_hp = 0;
	str.Format("%.3d", AHPstr[pdoc->airlist[No].indoor_air[No_s].air_hp]);
	tempstr += str;
	tempstr += "D";
	//机组类型  1--单冷  0--热泵
	if (pdoc->airlist[No].air_type2 == 0)
		tempstr += "R";
	if (pdoc->airlist[No].low_type)
		tempstr += "LH";
	m_airtype1_s.SetWindowText(tempstr);

	//外机程序版本
	if (pdoc->airlist[No].indoor_air[No_s].s_out_version < 100)
		tempstr.Format("%.1f", (float)pdoc->airlist[No].indoor_air[No_s].s_out_version / 10);
	else
	{
		int v1, v2, v3;
		v3 = pdoc->airlist[No].indoor_air[No_s].s_out_version / 100;
		v1 = pdoc->airlist[No].indoor_air[No_s].s_out_version % 100;
		v2 = v1 / 10;
		v1 = v1 % 10;
		tempstr.Format("%.1d.%.1d.%.1d", v3, v2, v1);
	}
	m_airversion_s.SetWindowText(tempstr);


	//阀门初始开度
	tempstr.Format("%d", pdoc->airlist[No].indoor_air[No_s].s_air_valve_ini);
	m_hp_s1.SetWindowText(tempstr);

	//状态参数
		//运行模式  0--停机 1--制冷 2--制热 3--自动
		//			4--除霜 5--调试
	CString media_style[3] = { "R22","R410A","R407C" };
	if (pdoc->airlist[No].indoor_air[No_s].cool_media_s >= 0 && pdoc->airlist[No].indoor_air[No_s].cool_media_s <= 2)
		m_edit_media_s.SetWindowText(media_style[pdoc->airlist[No].indoor_air[No_s].cool_media_s]);
	CString runmode[8] = { "测试","制冷","制热","热水","除霜","回收","待机","调试" };
	CString runmode_english[8] = { "OFF","Cooling","Heating","Hot water","Defrost","Recycle","Standby","Commissioning" };

	if (pdoc->airlist[No].indoor_air[No_s].s_runmode >= 0 && pdoc->airlist[No].indoor_air[No_s].s_runmode <= 7)
	{
		//m_runmode_s.SetWindowText(runmode[pdoc->airlist[No].indoor_air[No_s].s_runmode]);
		if (theApp.m_bLanguage == 0)
			m_runmode_s.SetWindowText(runmode[pdoc->airlist[No].indoor_air[No_s].s_runmode]);
		else if (theApp.m_bLanguage == 1)
			m_runmode_s.SetWindowText(runmode_english[pdoc->airlist[No].indoor_air[No_s].s_runmode]);

	}

	CString wind[4] = { "停止","高速","高速","高速" };
	CString wind_english[4] = { "Stop","High","High","High" };
	//风机1  0--停 1--低速 2--中速 3--高速
	if (pdoc->airlist[No].indoor_air[No_s].s_windmotor1 >= 0 && pdoc->airlist[No].indoor_air[No_s].s_windmotor1 <= 3)//有效性检查
	{
		if (theApp.m_bLanguage == 0)
			m_edbldc_speed1.SetWindowText(wind[pdoc->airlist[No].indoor_air[No_s].s_windmotor1]);
		else if (theApp.m_bLanguage == 1)
			m_edbldc_speed1.SetWindowText(wind_english[pdoc->airlist[No].indoor_air[No_s].s_windmotor1]);

		//	m_fan1_s.SetWindowText(wind[pdoc->airlist[No].indoor_air[No_s].s_windmotor1]);
		tempstr = wind[pdoc->airlist[No].indoor_air[No_s].s_windmotor1];

	}

	//风机2  0--停 1--低速 2--中速 3--高速
	if (pdoc->airlist[No].indoor_air[No_s].s_windmotor2 >= 0 && pdoc->airlist[No].indoor_air[No_s].s_windmotor2 <= 3)
	{
		if (theApp.m_bLanguage == 0)
			m_edbldc_speed2.SetWindowText(wind[pdoc->airlist[No].indoor_air[No_s].s_windmotor2]);
		else if (theApp.m_bLanguage == 1)
			m_edbldc_speed2.SetWindowText(wind_english[pdoc->airlist[No].indoor_air[No_s].s_windmotor2]);

		//		m_fan2_s.SetWindowText(wind[pdoc->airlist[No].indoor_air[No_s].s_windmotor2]);
		tempstr = wind[pdoc->airlist[No].indoor_air[No_s].s_windmotor2];
	}


	//压缩机2状态 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_compre[0] == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_comp1_s.SetWindowText(tempstr);

	//压缩机2状态 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_compre[1] == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_comp2_s.SetWindowText(tempstr);


	//压缩机3状态 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_compre[2] == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_comp3_s.SetWindowText(tempstr);
	//  
	   ////压缩机4状态 0--关 1--开
	   //if(pdoc->airlist[No].indoor_air[No_s].s_compre[3]==0)
	   //{
	   //	if(theApp.m_bLanguage==0)
	   //		tempstr.Format("关闭");
	   //	else if(theApp.m_bLanguage==1)
	   //		tempstr.Format("Close");
	   //}
	   //else
	   //{
	   //	if(theApp.m_bLanguage==0)
	   //		tempstr.Format("开");
	   //	else if(theApp.m_bLanguage==1)
	   //		tempstr.Format("ON");
	   //}
	   //m_comp4_s.SetWindowText(tempstr);


	 //压缩机5状态 0--关 1--开
	   //if(pdoc->airlist[No].indoor_air[No_s].s_compre[4]==0)
	   //{
	   //	if(theApp.m_bLanguage==0)
	   //		tempstr.Format("关闭");
	   //	else if(theApp.m_bLanguage==1)
	   //		tempstr.Format("Close");
	   //}
	   //else
	   //{
	   //	if(theApp.m_bLanguage==0)
	   //		tempstr.Format("开");
	   //	else if(theApp.m_bLanguage==1)
	   //		tempstr.Format("ON");
	   //}
	   //m_comp5_s.SetWindowText(tempstr);

	// //压缩机6状态 0--关 1--开
	   //if(pdoc->airlist[No].indoor_air[No_s].s_compre[5]==0)
	   //{
	   //	if(theApp.m_bLanguage==0)
	   //		tempstr.Format("关闭");
	   //	else if(theApp.m_bLanguage==1)
	   //		tempstr.Format("Close");
	   //}
	   //else
	   //{
	   //	if(theApp.m_bLanguage==0)
	   //		tempstr.Format("开");
	   //	else if(theApp.m_bLanguage==1)
	   //		tempstr.Format("ON");
	   //}
	   //m_comp6_s.SetWindowText(tempstr);

	   //四通阀1状态 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_fourvalve1 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_fourvalve1_s.SetWindowText(tempstr);


	//四通阀2状态 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_fourvalve2 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_fourvalve2_s.SetWindowText(tempstr);

	//电磁阀0 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_ele_valve0 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_elevavle_s.SetWindowText(tempstr);


	//电磁阀1 0--关 1--开
	if (pdoc->airlist[No].indoor_air[No_s].s_ele_valve1 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_elevavle2_s.SetWindowText(tempstr);


	//辅热
	if (pdoc->airlist[No].indoor_air[No_s].s_ahot == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关闭");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("Close");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	m_ahot_s.SetWindowText(tempstr);

	//电磁膨胀阀1开度
	tempstr.Format("%d", pdoc->airlist[No].indoor_air[No_s].s_ele_distension_valve1);
	m_eledisten1_s.SetWindowText(tempstr);


	//电磁膨胀阀2开度
	tempstr.Format("%d", pdoc->airlist[No].indoor_air[No_s].s_ele_distension_valve2);
	m_eledisten2_s.SetWindowText(tempstr);

	//电磁膨胀阀3开度
	tempstr.Format("%d", pdoc->airlist[No].indoor_air[No_s].s_ele_distension_valve3);
	m_eledisten3_s.SetWindowText(tempstr);


	//电磁膨胀阀4开度
	tempstr.Format("%d", pdoc->airlist[No].indoor_air[No_s].s_ele_distension_valve4);
	m_eledisten4_s.SetWindowText(tempstr);

	//总能力需求(单位HP)
	tempstr.Format("%.1fHP", pdoc->airlist[No].indoor_air[No_s].s_total_needed_HP);
	m_totalneedhp_s.SetWindowText(tempstr);

	//TP1
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp1);
	m_tp1_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp1 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
		m_tp1_s.SetWindowText(tempstr);
	}
	else
	{
		if (pdoc->airlist[No].indoor_air[No_s].s_tp1 <= 5)
		{
			if (theApp.m_bLanguage == 0)
				tempstr = "开路";
			else if (theApp.m_bLanguage == 1)
				tempstr = "Open";
			m_tp1_s.SetWindowText(tempstr);
		}
	}
	//TP2
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp2);
	m_tp2_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp2 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
		m_tp2_s.SetWindowText(tempstr);
	}
	else
	{
		if (pdoc->airlist[No].indoor_air[No_s].s_tp2 <= 5)
		{
			if (theApp.m_bLanguage == 0)
				tempstr = "开路";
			else if (theApp.m_bLanguage == 1)
				tempstr = "Open";
			m_tp2_s.SetWindowText(tempstr);
		}
	}
	//TP3
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp3);
	m_tp3_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp3 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp3_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp3 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp3_s.SetWindowText(tempstr);

	//TP4
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp4);
	m_tp4_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp4 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp4_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp4 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp4_s.SetWindowText(tempstr);

	//TP5
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp5);
	m_tp5_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp5 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp5_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp5 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp5_s.SetWindowText(tempstr);

	//TP6
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp6);
	m_tp6_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp6 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp6_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp6 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp6_s.SetWindowText(tempstr);

	//TP7
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp7);
	m_tp7_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp7 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp7_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp7 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp7_s.SetWindowText(tempstr);

	//TP8
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp8);
	m_tp8_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp8 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp8_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp8 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp8_s.SetWindowText(tempstr);

	//TP9
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp9);
	m_tp9_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp9 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp9_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp9 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp9_s.SetWindowText(tempstr);

	//TP10
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp10);
	m_tp10_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp10 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp10_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp10 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp10_s.SetWindowText(tempstr);

	//TP11
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp11);
	m_tp11_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp11 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp11_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp11 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp11_s.SetWindowText(tempstr);

	//TP12
	tempstr.Format("%.1f℃", pdoc->airlist[No].indoor_air[No_s].s_tp12);
	m_tp12_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp12 >= 127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "短路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Short";
	}
	m_tp12_s.SetWindowText(tempstr);
	if (pdoc->airlist[No].indoor_air[No_s].s_tp12 <= -127)
	{
		if (theApp.m_bLanguage == 0)
			tempstr = "开路";
		else if (theApp.m_bLanguage == 1)
			tempstr = "Open";
	}
	m_tp12_s.SetWindowText(tempstr);

	//高压
	tempstr.Format("%.1fBar", pdoc->airlist[No].indoor_air[No_s].s_highpre);
	m_highpre_s.SetWindowText(tempstr);

	//低压
	tempstr.Format("%.1fBar", pdoc->airlist[No].indoor_air[No_s].s_lowpre);
	m_lowpre_s.SetWindowText(tempstr);


	//实际过热度
	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[No_s].s_factsuperhot);
	m_factshot_s.SetWindowText(tempstr);
	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[No_s].s_factsuperhot2);
	m_hicsupercool_s.SetWindowText(tempstr);

	//目标过热度
	f = (float)pdoc->airlist[No].indoor_air[No_s].s_targetsuperhot;
	f /= 10;
	tempstr.Format("%.1f", f);
	m_targetshot_s.SetWindowText(tempstr);

}
//在窗口中输出各个数据
void CMDSView::recorddata(int No)
{

	CArchive ar(&pdoc->m_file[No], CArchive::store);
	pdoc->m_recordstr.Empty();
	CString tempstr, str;
	float f;
	CTime t = CTime::GetCurrentTime();
	tempstr.Format("%.2d%.2d%.2d", t.GetHour(), t.GetMinute(), t.GetSecond());
	pdoc->m_recordstr = tempstr;


	//状态参数
		//运行模式  0--停机 1--制冷 2--制热 3--自动
		//			4--送风 5--除湿 6--除霜 7--调试
		//CString runmode[8]={"测试","制冷","制热","热水","除霜","回收","待机","调试"}; 
	 //   CString runmode_english[8]={"OFF","Cooling","Heating","Hot water","Defrost","Recycle","Standby","Commissioning"}; 
		//if(pdoc->airlist[No].s_runmode>=0&&pdoc->airlist[No].s_runmode<=7)
		//{
		//	pdoc->m_recordstr+="  ";
		//	if(theApp.m_bLanguage==0)
		//		pdoc->m_recordstr+=runmode[pdoc->airlist[No].s_runmode];
		//	else if(theApp.m_bLanguage==1)
		//		pdoc->m_recordstr+=runmode_english[pdoc->airlist[No].s_runmode];

		//}
	CString runmode[3] = { "停机","制热模式","制冷模式" };
	CString runmode_english[8] = { "OFF","Cooling","Heating","Hot water","Defrost","Recycle","Standby","Commissioning" };
	if (moshi >= 0 && moshi <= 6)
	{
		pdoc->m_recordstr += ",";
		if (theApp.m_bLanguage == 0)
		{
			pdoc->m_recordstr += runmode[moshi];
		}
		else
		{
			pdoc->m_recordstr += runmode_english[moshi];
		}
	}
	CString wind[4] = { "停","低","中","高" };
	CString wind_english[4] = { "Stop","Low","Medium","High" };

	//系统1风机1
	if (pdoc->airlist[No].DO7 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DO7 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统1风机2
	if (pdoc->airlist[No].DO8 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DO8 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统2风机1
	if (pdoc->airlist[No].DO9 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DO9 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统2风机2
	if (pdoc->airlist[No].DO10 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DO10 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统3风机1
	if (pdoc->airlist[No].DOF7 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DOF7 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统3风机2
	if (pdoc->airlist[No].DOF8 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DOF8 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统4风机1
	if (pdoc->airlist[No].DOF9 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DOF9 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}
	//系统4风机2
	if (pdoc->airlist[No].DOF10 == 0)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "停止";
	}
	else if (pdoc->airlist[No].DOF10 == 1)
	{
		pdoc->m_recordstr += ",";
		pdoc->m_recordstr += "高速";
	}


	//压缩机1状态 0--关 1--开
	if (pdoc->airlist[No].DO11 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//压缩机2状态 0--关 1--开
	if (pdoc->airlist[No].DO12 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//压缩机3状态 0--关 1--开
	if (pdoc->airlist[No].DOF11 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//压缩机4状态 0--关 1--开
	if (pdoc->airlist[No].DOF12 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//四通阀1状态 0--关 1--开
	if (pdoc->airlist[No].DO5 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//四通阀2状态 0--关 1--开
	if (pdoc->airlist[No].DO6 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;
	//副板 四通阀3
	if (pdoc->airlist[No].DOF5 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//副板 四通阀4
	if (pdoc->airlist[No].DOF6 == 0)
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("关");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("OFF");
	}
	else
	{
		if (theApp.m_bLanguage == 0)
			tempstr.Format("开");
		else if (theApp.m_bLanguage == 1)
			tempstr.Format("ON");
	}
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//电磁膨胀阀1开度
	tempstr.Format("%3d", pdoc->airlist[No].s_ele_distension_valve1);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//电磁膨胀阀2开度
	tempstr.Format("%3d", pdoc->airlist[No].s_ele_distension_valve2);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//副板系统3电磁膨胀阀3开度
	tempstr.Format("%3d", pdoc->airlist[No].s_ele_distension_valve3);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//电磁膨胀阀4开度
	tempstr.Format("%3d", pdoc->airlist[No].s_ele_distension_valve4);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;


	//电磁膨胀阀1开度
	tempstr.Format("%3d", pdoc->airlist[No].f_s_ele_distension_valve1);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//电磁膨胀阀2开度
	tempstr.Format("%3d", pdoc->airlist[No].f_s_ele_distension_valve2);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//副板系统3电磁膨胀阀3开度
	tempstr.Format("%3d", pdoc->airlist[No].f_s_ele_distension_valve3);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//电磁膨胀阀4开度
	tempstr.Format("%3d", pdoc->airlist[No].f_s_ele_distension_valve4);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//总能力需求(单位HP)
	tempstr.Format("%5.1fHP", pdoc->airlist[No].s_total_needed_HP);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//目标过热度
	f = (float)pdoc->airlist[No].s_targetsuperhot;
	f /= 10;
	tempstr.Format("%5.1f", f);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//低压 
	tempstr.Format("%5.1f", pdoc->airlist[No].s_lowpre);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//实际过热度
	tempstr.Format("%5.1f", pdoc->airlist[No].s_factsuperhot);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//高压
	tempstr.Format("%5.1f", pdoc->airlist[No].s_highpre);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//实际过热度2
	tempstr.Format("%5.1f", pdoc->airlist[No].s_factsuperhot2);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//低压 
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_lowpre);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;


	//高压
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_highpre);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//实际过热度3
	tempstr.Format("%5.1f", pdoc->airlist[No].s_factsuperhot3);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//实际过热度4
	tempstr.Format("%5.1f", pdoc->airlist[No].s_factsuperhot4);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;


	//排气温度			TH1
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp1);
	pdoc->m_recordstr += ",";
	if (pdoc->airlist[No].s_tp1 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "开路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Open";
	}
	else if (pdoc->airlist[No].s_tp1 <= 5)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "短路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Short";
	}
	else
		pdoc->m_recordstr += tempstr;

	//1#进盘温度		TH2
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp2);
	pdoc->m_recordstr += ",";
	if (pdoc->airlist[No].s_tp2 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "开路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Open";
	}
	else if (pdoc->airlist[No].s_tp2 <= 5)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "短路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Short";
	}
	else
		pdoc->m_recordstr += tempstr;

	//1#中盘温度		TH3
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp3);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//2#进盘温度		TH4
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp4);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//2#中盘温度		TH5
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp5);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//3#进盘温度		//TH6
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp6);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//3#中盘温度		TH7
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp7);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//环境温度			TH8
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp8);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//1#出盘温度		TH9
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp9);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;



	//2#出盘温度		TH10
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp10);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;



	//3#出盘温度		TH11
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp11);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//回气温度			TH12
	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp12);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp13);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%5.1f", pdoc->airlist[No].s_tp14);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;
	//副板数据
	//排气温度			TH1
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp1);
	pdoc->m_recordstr += ",";
	if (pdoc->airlist[No].f_s_tp1 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "开路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Open";
	}
	else if (pdoc->airlist[No].f_s_tp1 <= 5)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "短路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Short";
	}
	else
		pdoc->m_recordstr += tempstr;

	//1#进盘温度		TH2
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp2);
	pdoc->m_recordstr += ",";
	if (pdoc->airlist[No].f_s_tp2 >= 150)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "开路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Open";
	}
	else if (pdoc->airlist[No].f_s_tp2 <= 5)
	{
		if (theApp.m_bLanguage == 0)
			pdoc->m_recordstr += "短路";
		else if (theApp.m_bLanguage == 1)
			pdoc->m_recordstr += "Short";
	}
	else
		pdoc->m_recordstr += tempstr;

	//1#中盘温度		TH3
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp3);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//2#进盘温度		TH4
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp4);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//2#中盘温度		TH5
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp5);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//3#进盘温度		//TH6
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp6);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//3#中盘温度		TH7
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp7);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//环境温度			TH8
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp8);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//1#出盘温度		TH9
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp9);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;



	//2#出盘温度		TH10
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp10);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//3#出盘温度		TH11
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp11);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//回气温度			TH12
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp12);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//3#出盘温度		TH11
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp13);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	//回气温度			TH12
	tempstr.Format("%5.1f", pdoc->airlist[No].f_s_tp14);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1fA", pdoc->airlist[No].s_ele);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1fA", pdoc->airlist[No].s_ele2);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1fA", pdoc->airlist[No].f_s_ele1);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1fA", pdoc->airlist[No].f_s_ele2);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += valstr1;

	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += valstr2;

	//外机程序版本
	int v1, v2, v3;
	v3 = pdoc->airlist[No].out_version / 10;
	v2 = pdoc->airlist[No].out_version % 10;
	v1 = pdoc->airlist[No].out_version_end;
	tempstr.Format("%.1d.%.1d.%.1d", v3, v2, v1);
	pdoc->m_recordstr += ",";
	pdoc->m_recordstr += tempstr;

	pdoc->m_recordstr += "\r\n";
	ar.WriteString(pdoc->m_recordstr);
	ar.Close();
	//	pdoc->m_file.WtiteString(pdoc->m_recordstr);*/
}
void CMDSView::OnSelchangeAirno()
{
	// TODO: Add your control notification handler code here
	m_showNo = m_airno.GetCurSel();
	refreshslave_sel(m_showNo);
	showdata(m_showNo);
}
void CMDSView::OnSelchangeAirnoS()
{
	// TODO: Add your control notification handler code here
	m_showNo_s = m_airno_s.GetCurSel();
	showdata_s(m_showNo, m_showNo_s);
}

void CMDSView::OnApecilebtn()
{
	// TODO: Add your control notification handler code here
	CSpecilcmddlg dlg;
	dlg.outairNo = m_showNo;
	dlg.DoModal();
}

void CMDSView::OnSelchangeComno()
{
	// TODO: Add your control notification handler code here
	pdoc->m_commNo = m_comNo.GetCurSel() + 1;
}

void CMDSView::OnSelchangeBand()
{
	// TODO: Add your control notification handler code here
	pdoc->m_commband = m_bandno.GetCurSel();
}
void CMDSView::showerror(int No)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	CString str;
	m_alarmlist.ShowWindow(TRUE);

	for (i = m_alarmlist.GetCount() - 1; i >= 0; i--)
	{
		m_alarmlist.DeleteString(i);
	}

	CString errorstr[16] = { "1系统压缩机电流保护","2系统压缩机电流保护","水泵过载","水流量不足","系统1高压故障","系统1低压故障","压缩机3故障","系统1风机过载","系统2高压故障","出水温度过低保护","电加热过载","环境温度过高/低禁止运行","与风机驱动器1通讯故障","过热度小于2度保护","系统2风机过载"," " };
	CString errorstr2[8] = { "系统1回气温度过高","系统1排气温度过高","系统2回气温度过高","系统2排气温度过高","系统2低压","系统2过热度小","系统1冷煤泄露","系统2冷煤泄露" };
	CString errorstr3[16] = { "TH1故障","TH2故障","TH3故障","TH4故障","TH5故障","TH6故障","TH7故障","TH8故障","TH9故障","TH10故障","TH11故障","TH12故障","低压2传感器故障","低压1传感器故障","补水泵过载","四通阀换向故障1" };
	CString errorstr41[16] = { "TH13故障","出水温度过高","电流互感器1故障","电流互感器2故障","与扩展板通讯故障","热水侧水流不足","四通阀换向故障2","TH14故障","高压传感器1故障","高压传感器2故障","压缩机通讯故障1","压缩机通讯故障2","压缩机通讯故障3","压缩机通讯故障4","压缩机4故障","与风机驱动器2通讯故障" };
	CString errorstr4[2] = { "排温>115℃","压缩机电流不在2A到56A范围之内" };

	CString errorstrs[16] = { "系统3压缩机电流保护","系统4压缩机电流保护","水泵过载","水流量不足","系统1高压故障","系统1低压故障","压缩机3故障","系统1风机过载","系统2高压故障","出水温度过低保护","电加热过载","环境温度过高/低禁止运行","与风机驱动器1通讯故障","过热度小于2度保护","系统2风机过载"," " };
	CString errorstr2s[8] = { "系统1回气温度过高","系统1排气温度过高","系统2回气温度过高","系统2排气温度过高","系统2低压","系统2过热度小","系统1冷煤泄露","系统2冷煤泄露" };
	CString errorstr3s[16] = { "TH1故障","TH2故障","TH3故障","TH4故障","TH5故障","TH6故障","TH7故障","TH8故障","TH9故障","TH10故障","TH11故障","TH12故障","低压2传感器故障","低压1传感器故障","补水泵过载","四通阀换向故障1" };
	CString errorstr4s[16] = { "TH13故障","出水温度过高","电流互感器1故障","电流互感器2故障","与扩展板通讯故障","热水侧水流不足","水位过低","TH14故障","高压传感器1故障","高压传感器2故障","压缩机通讯故障1","压缩机通讯故障2","压缩机通讯故障3","压缩机通讯故障4","压缩机4故障","与风机驱动器2通讯故障" };

	CString errorstr_s0[16] = { "1系统压缩机过载","2系统压缩机过载","水泵过载","水流量不足","系统1高压故障","系统1低压故障","探头故障","系统1风机过载","系统2高压故障","出水温度过低保护","电加热过载","环境温度过高/低禁止运行","单系统下启动紧急运行功能(线控器显示)","过热度小于2度保护","系统2风机过载"," " };
	CString errorstr2_s0[8] = { "系统1回气温度过高","系统1排气温度过高","系统2回气温度过高","系统2排气温度过高","系统2低压","系统2过热度小","系统1冷煤","系统2冷煤不足" };
	CString errorstr3_s0[16] = { "TH1故障","TH2故障","TH3故障","TH4故障","TH5故障","TH6故障","TH7故障","TH8故障","TH9故障","TH10故障","TH11故障","TH12故障","低压2传感器故障","低压1传感器故障","补水泵过载","冷却水温过高过低保护" };
	CString errorstr4_s0[16] = { "水位开关故障","出水温度过高","系统1电流互感器故障","系统2电流互感器故障","与副板通讯故障","热水侧水流不足","水位过低","水位开关2故障","高压传感器1故障","高压传感器2故障","热水测水流开关断开","","","","","" };
	for (i = 0; i < pdoc->airlist[No].in_num; i++)
	{
		if (pdoc->airlist[No].com_error[i] == 1)
		{
			str.Format("%d#从机通讯故障", i);
			m_alarmlist.AddString(str);
		}
	}
	if (pdoc->airlist[No].com_error[15] == 1)//锁机故障标志位
	{
		str.Format("910 锁机故障");
		m_alarmlist.AddString(str);
	}
	//temp = 0;
	//for (i = 0; i < 56; i++)
	//{
	//	if (pdoc->airlist[No].s_error[i] == 1)
	//	{
	//		temp = 1;
	//	}
	//}

	//if (temp == 1)
	//{
	//	str.Format("主机主板:");

	//	for (i = 0; i < 16; i++)
	//	{
	//		if (pdoc->airlist[No].s_error[i] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr[i]);
	//			if (iStep >= 246 && iStep < 617)
	//			{
	//				if (pdoc->airlist[No].s_error[5] == 1)
	//				{
	//					if (iStep >= 811)
	//					{
	//					}
	//					else
	//					{
	//						m_alarmlist.AddString(str + "系统1低压故障");
	//						//iStep = 811;
	//					}
	//				}
	//			}
	//			if (pdoc->airlist[No].s_error[0] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统1压缩机电流保护.停止测试");
	//					//iStep = 811;
	//				}
	//			}
	//			if (pdoc->airlist[No].s_error[1] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统2压缩机电流保护.停止测试");
	//					//iStep = 811;
	//				}
	//			}
	//		}				//故障*/
	//	}
	//	for (i = 0; i < 8; i++)
	//	{
	//		if (pdoc->airlist[No].s_error[i + 16] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr2[i]);
	//			if (pdoc->airlist[No].s_error[20] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统2低压故障");
	//					//iStep = 811;
	//				}
	//			}
	//		}				//故障*/	
	//	}
	//	for (i = 0; i < 16; i++)
	//	{
	//		if (pdoc->airlist[No].s_error[i + 24] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr3[i]);
	//			if (pdoc->airlist[No].s_error[24] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "TH1故障");
	//					//iStep = 811;
	//				}
	//			}
	//			if (pdoc->airlist[No].s_error[25] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "TH2故障");
	//					//iStep = 811;
	//				}
	//			}
	//			if (pdoc->airlist[No].s_error[36] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统1低压传感器1故障");
	//					//iStep = 811;
	//				}
	//			}
	//			if (pdoc->airlist[No].s_error[37] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统2低压传感器2故障");
	//					//iStep = 811;
	//				}
	//			}
	//		}				//故障*/	
	//	}
	//	for (i = 0; i < 16; i++)
	//	{
	//		if (pdoc->airlist[No].s_error[i + 40] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr41[i]);
	//		}

	//		//故障*/	
	//	}

	//}
	//temp = 0;
	//for (i = 0; i < 56; i++)
	//{
	//	if (pdoc->airlist[No].f_s_error[i] == 1)
	//	{
	//		temp = 1;
	//	}
	//}

	//if (temp == 1)
	//{
	//	str.Format("主机副板:");

	//	for (i = 0; i < 16; i++)
	//	{
	//		if (pdoc->airlist[No].f_s_error[i] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstrs[i]);
	//			if (iStep >= 246 && iStep < 617)
	//			{
	//				if (pdoc->airlist[No].f_s_error[5] == 1)
	//				{
	//					if (iStep >= 811)
	//					{
	//					}
	//					else
	//					{
	//						m_alarmlist.AddString(str + "低压故障,停止测试");
	//						//iStep = 811;
	//					}
	//				}
	//			}
	//			if (pdoc->airlist[No].f_s_error[0] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统1压缩机电流保护.停止测试");
	//					//iStep = 811;
	//				}
	//			}
	//			if (stricmp(models_tag, "1600") == 0)
	//			{
	//				if (pdoc->airlist[No].f_s_error[1] == 1)
	//				{
	//					if (iStep >= 811)
	//					{
	//					}
	//					else
	//					{
	//						m_alarmlist.AddString(str + "系统2压缩机电流保护.停止测试");
	//						//	iStep = 811;
	//					}
	//				}
	//			}
	//		}				//故障*/
	//	}
	//	for (i = 0; i < 8; i++)
	//	{
	//		if (pdoc->airlist[No].f_s_error[i + 16] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr2s[i]);
	//			if (stricmp(models_tag, "1600") == 0)
	//			{
	//				if (pdoc->airlist[No].f_s_error[20] == 1)
	//				{
	//					if (iStep >= 811)
	//					{
	//					}
	//					else
	//					{
	//						m_alarmlist.AddString(str + "系统2低压故障");
	//						//	iStep = 811;
	//					}
	//				}
	//			}
	//		}				//故障*/	
	//	}
	//	for (i = 0; i < 16; i++)
	//	{
	//		if (pdoc->airlist[No].f_s_error[i + 24] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr3s[i]);
	//			if (pdoc->airlist[No].f_s_error[36] == 1)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					m_alarmlist.AddString(str + "系统1低压传感器1故障");
	//					//iStep = 811;
	//				}
	//			}
	//			if (stricmp(models_tag, "1600") == 0)
	//			{
	//				if (pdoc->airlist[No].f_s_error[37] == 1)
	//				{
	//					if (iStep >= 811)
	//					{
	//					}
	//					else
	//					{
	//						m_alarmlist.AddString(str + "系统2低压传感器2故障");
	//						//iStep = 811;
	//					}
	//				}
	//			}
	//		}				//故障*/	
	//	}
	//	for (i = 0; i < 16; i++)
	//	{
	//		if (pdoc->airlist[No].f_s_error[i + 40] == 1)
	//		{
	//			m_alarmlist.AddString(str + errorstr4s[i]);
	//		}				//故障*/	
	//	}
	//}
	////排温>130℃
	//if (pdoc->airlist[No].s_tp1 > 115)
	//{
	//	if (timing12 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing12 = 1;
	//	}
	//	if ((GetTickCount() - iTime) >= 10000)
	//	{
	//		m_alarmlist.AddString(errorstr4[0]);

	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//		}
	//	}
	//	errflag = 1;
	//}

	////进水温度监测
	////if (iStep >= 20)
	////{
	//if (pdoc->airlist[No].s_tp6 > 35)
	//{
	//	if (timing12 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing12 = 1;
	//		m_alarmlist.AddString("进水温度>35");
	//		m_alarmlist2.AddString("进水温度>35");
	//		CArchive outfile(&logFile, CArchive::store);
	//		outfile.WriteString(GetCurTime()); outfile.WriteString("进水温度异常\r\n");
	//		outfile.Close();
	//		vecErr.push_back("× 进水温度");
	//	}
	//	if ((GetTickCount() - iTime) >= 3000)
	//	{
	//		m_static_title.SetFontSize(25, 25);
	//		m_static_title.SetFontColor(0, 0, 255);
	//		m_static_title.GetWindowTextA(m_static_title.Caption);
	//		m_static_title.ShowWindow(TRUE);
	//	}
	//	errflag = 1;
	//}
	//if (pdoc->airlist[No].s_tp6 > 40)
	//{
	//	if (timing12 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing12 = 1;
	//		m_alarmlist.AddString("进水温度过高");
	//		m_alarmlist2.AddString("进水温度过高");
	//		CArchive outfile(&logFile, CArchive::store);
	//		outfile.WriteString(GetCurTime()); outfile.WriteString("进水温度异常\r\n");
	//		outfile.Close();
	//		vecErr.push_back("× 进水温度");
	//	}
	//	if ((GetTickCount() - iTime) >= 3000)
	//	{
	//		if (iStep >= 811)
	//		{
	//			;
	//		}
	//		else
	//		{
	//			iStep = 811;
	//		}
	//	}
	//	errflag = 1;
	//}
	////}
	//if (pdoc->airlist[No].s_tp2 > 115)
	//{
	//	if (timing13 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing13 = 1;
	//	}
	//	if ((GetTickCount() - iTime) >= 10000)
	//	{
	//		m_alarmlist.AddString(errorstr4[0]);
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//		}
	//	}
	//	errflag = 1;
	//}
	////低压保护
	//if (iStep >= 617 && iStep < 811)//制冷模式
	//{
	//	if (pdoc->airlist[No].s_lowpre < 3.8)
	//	{
	//		if (timing == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 10000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//iStep = 811;
	//			}
	//			if (pdoc->airlist[No].s_lowpre < 6.5)
	//			{
	//				m_alarmlist.AddString("系统1低压<3.8");
	//			}
	//		}
	//		else
	//		{
	//			;
	//		}
	//	}
	//	if (pdoc->airlist[No].s_highpre < 3.8)
	//	{
	//		if (timing1 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing1 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 10000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//iStep = 811;
	//			}
	//			if (pdoc->airlist[No].s_highpre < 6.5)
	//			{
	//				m_alarmlist.AddString("系统2低压<3.8");
	//			}
	//		}
	//	}
	//	if (pdoc->airlist[No].f_s_lowpre < 3.8)
	//	{
	//		if (timing2 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing2 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 10000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//iStep = 811;
	//			}
	//			if (pdoc->airlist[No].f_s_lowpre < 6.5)
	//			{
	//				m_alarmlist.AddString("系统3低压<3.8");
	//			}
	//		}
	//	}
	//	if (stricmp(models_tag, "1600") == 0)
	//	{
	//		if (pdoc->airlist[No].f_s_highpre < 3.8)
	//		{
	//			if (timing3 == 0)
	//			{
	//				iTime = GetTickCount();
	//				timing3 = 1;
	//			}
	//			if ((GetTickCount() - iTime) >= 10000)
	//			{
	//				if (iStep >= 811)
	//				{
	//				}
	//				else
	//				{
	//					//	iStep = 811;
	//				}
	//				if (pdoc->airlist[No].s_lowpre < 6.5)
	//				{
	//					m_alarmlist.AddString("系统4低压<3.8");
	//				}
	//			}
	//		}
	//	}
	//}
	//if (iStep >= 246 && iStep < 617)//制热
	//{
	//	if (pdoc->airlist[No].s_lowpre <= 1.7)
	//	{
	//		if (timing4 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing4 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 30000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//iStep = 811;
	//			}
	//			if (pdoc->airlist[No].s_lowpre < 2.2)
	//			{
	//				m_alarmlist.AddString("系统1低压<=1.7");
	//			}
	//		}
	//	}
	//	if (pdoc->airlist[No].s_highpre <= 1.7)
	//	{
	//		if (timing5 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing5 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 30000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//iStep = 811;
	//			}
	//			if (pdoc->airlist[No].s_highpre < 2.2)
	//			{
	//				m_alarmlist.AddString("系统2低压<=1.7");
	//			}
	//		}
	//	}
	//	if (pdoc->airlist[No].f_s_lowpre <= 1.7)
	//	{
	//		if (timing6 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing6 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 30000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//	iStep = 811;
	//			}
	//			if (pdoc->airlist[No].f_s_lowpre < 2.2)
	//			{
	//				m_alarmlist.AddString("系统3低压<=1.7");
	//			}
	//		}
	//	}
	//	if (pdoc->airlist[No].f_s_highpre <= 1.7)
	//	{
	//		if (timing6 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing6 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 30000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//iStep = 811;
	//			}
	//			if (pdoc->airlist[No].s_lowpre < 2.2)
	//			{
	//				m_alarmlist.AddString("系统2低压<=1.7");
	//			}
	//		}
	//	}
	//	if (pdoc->airlist[No].s_lowpre < 1.5)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//		}
	//		if (pdoc->airlist[No].s_lowpre < 2.2)
	//		{
	//			m_alarmlist.AddString("系统1低压<1.5");
	//		}
	//	}
	//	if (pdoc->airlist[No].s_highpre < 1.5)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//		}
	//		if (pdoc->airlist[No].s_highpre < 2.2)
	//		{
	//			m_alarmlist.AddString("系统2低压<1.5");
	//		}
	//	}
	//	if (pdoc->airlist[No].f_s_lowpre < 1.5)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//		}
	//		if (pdoc->airlist[No].f_s_lowpre < 2.2)
	//		{
	//			m_alarmlist.AddString("系统3低压<1.5");
	//		}
	//	}
	//	if (pdoc->airlist[No].f_s_highpre < 1.5)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//		}
	//		if (pdoc->airlist[No].s_lowpre < 2.2)
	//		{
	//			m_alarmlist.AddString("系统2低压<1.5");
	//		}
	//	}
	//}
	////高压保护
	//		//if (pdoc->airlist[No].s_gaoya1 >=41.5)
	//		//{
	//		//	if (pdoc->airlist[No].s_gaoya1 >= 33)
	//		//	{
	//		//		if (iStep >= 811)
	//		//		{
	//		//		}
	//		//		else
	//		//		{
	//		//			m_alarmlist2.AddString("高压1故障");
	//		//			iStep = 811;
	//		//		}
	//		//	}
	//		//}
	////压缩机驱动保护
	//if (pdoc->airlist[No].s_ele >= 65)
	//{
	//	if (timing8 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing8 = 1;
	//	}
	//	if ((GetTickCount() - iTime) >= 30000)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//			m_alarmlist.AddString("压缩机1电流过大");
	//		}

	//	}
	//}
	//if (pdoc->airlist[No].s_ele2 >= 65)
	//{
	//	if (timing9 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing9 = 1;
	//	}
	//	if ((GetTickCount() - iTime) >= 30000)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//			m_alarmlist.AddString("压缩机2电流过大");
	//		}

	//	}
	//}
	//if (pdoc->airlist[No].f_s_ele1 >= 65)
	//{
	//	if (timing10 == 0)
	//	{
	//		iTime = GetTickCount();
	//		timing10 = 1;
	//	}
	//	if ((GetTickCount() - iTime) >= 30000)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			//iStep = 811;
	//			m_alarmlist.AddString("压缩机3电流过大");
	//		}

	//	}
	//}
	//if (stricmp(models_tag, "1600") == 0)
	//{
	//	if (pdoc->airlist[No].f_s_ele2 >= 65)
	//	{
	//		if (timing11 == 0)
	//		{
	//			iTime = GetTickCount();
	//			timing11 = 1;
	//		}
	//		if ((GetTickCount() - iTime) >= 30000)
	//		{
	//			if (iStep >= 811)
	//			{
	//			}
	//			else
	//			{
	//				//	iStep = 811;
	//				m_alarmlist.AddString("压缩机4电流过大");
	//			}

	//		}
	//	}
	//}
	////高压传感器故障
	//		//if (pdoc->airlist[No].s_gaoya1 == 0)
	//		//{
	//		//		if (iStep >= 811)
	//		//		{
	//		//		}
	//		//		else
	//		//		{
	//		//			m_alarmlist2.AddString("高压传感器1故障");
	//		//			iStep = 811;
	//		//		}
	//		//}
	//		//if (pdoc->airlist[No].s_gaoya2 == 0)
	//		//{
	//		//	if (iStep >= 811)
	//		//	{
	//		//	}
	//		//	else
	//		//	{
	//		//		m_alarmlist2.AddString("高压传感器2故障");
	//		//		iStep = 811;
	//		//	}
	//		//}
	////低压传感器
	//if (pdoc->airlist[No].s_lowpre == 0)
	//{
	//	if (iStep >= 811)
	//	{
	//	}
	//	else
	//	{
	//		m_alarmlist.AddString("低压传感器1故障");
	//		//	iStep = 811;
	//	}
	//}
	//if (pdoc->airlist[No].s_highpre == 0)
	//{
	//	if (iStep >= 811)
	//	{
	//	}
	//	else
	//	{
	//		m_alarmlist.AddString("低压传感器2故障");
	//		//	iStep = 811;
	//	}
	//}
	//if (pdoc->airlist[No].f_s_lowpre == 0)
	//{
	//	if (iStep >= 811)
	//	{
	//	}
	//	else
	//	{
	//		m_alarmlist.AddString("低压传感器3故障");
	//		//	iStep = 811;
	//	}
	//}
	//if (stricmp(models_tag, "1600") == 0)
	//{
	//	if (pdoc->airlist[No].f_s_highpre == 0)
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("低压传感器4故障");
	//			//	iStep = 811;
	//		}
	//	}
	//}
	//if (stricmp(models_tag, "1600") == 0)
	//{
	//	if (pdoc->airlist[No].DI1 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关1断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//	if (pdoc->airlist[No].DI2 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关2断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//	if (pdoc->airlist[No].DIF1 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关3断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//	if (pdoc->airlist[No].DIF2 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关4断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//}
	//else
	//{
	//	if (pdoc->airlist[No].DI1 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关1断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//	if (pdoc->airlist[No].DI2 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关2断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//	if (pdoc->airlist[No].DIF1 == 0)
	//	{
	//	}
	//	else
	//	{
	//		if (iStep >= 811)
	//		{
	//		}
	//		else
	//		{
	//			m_alarmlist.AddString("高压开关3断开,停止测试");
	//			//	iStep = 811;
	//		}
	//	}
	//}
	m_alarmlist.ShowWindow(TRUE);
}

void CMDSView::OnAlarmbtn()
{
	// TODO: Add your control notification handler code here
	CAlarmdlg dlg;
	dlg.DoModal();
}

HBRUSH CMDSView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return m_bkbrush;
	}
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(m_bkcolor);
		//	pDC->SetTextColor(RGB(255,255,255));
		return m_bkbrush;
	}

	if (nCtlColor == CTLCOLOR_LISTBOX && pWnd->GetDlgCtrlID() == IDC_ALARMLIST)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		pDC->SetTextColor(RGB(255, 0, 0));
		HBRUSH b = CreateSolidBrush(RGB(255, 255, 255));
		return b;

	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMDSView::OnTestcode()
{
	// TODO: Add your control notification handler code here
	CTestcodedlg dlg;
	dlg.DoModal();
}

//查看从机状态
void CMDSView::OnSlaveoutbtn()
{
	// TODO: Add your control notification handler code here

}

//读压缩机累计运行时间
void CMDSView::OnReadcomptime()
{
	Ccompdlg dlg;
	dlg.outairNo = m_showNo;
	dlg.DoModal();
	m_exv_button_ok = 1;
	// TODO: Add your control notification handler code here
/*	if(pdoc->m_connectflag==1&&pdoc->m_startflag==1)//如果串口打开
	{

		pdoc->queryFunNo1=pdoc->queryFunNo;
		pdoc->queryAirNo1=pdoc->queryAirNo;
		pdoc->sendcmdflag=1;
		pdoc->m_errorcount=0;
		pdoc->queryFunNo=13;
		pdoc->queryAirNo=m_showNo;
	}*/
}
//显示压缩机运行时间
void CMDSView::showcomptime(int No)
{

}

void CMDSView::OnDraw(CDC* pDC)
{
	// TODO: Add your specialized code here and/or call the base class
/*	CDC dc;
	BITMAP  bmpinfo;//图片信息
	m_logobmp.GetBitmap(&bmpinfo);
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&m_logobmp);
	TransparentBlt(pDC->m_hDC,752,4,bmpinfo.bmWidth*2/3,bmpinfo.bmHeight*2/3,dc.m_hDC,0,0,bmpinfo.bmWidth,bmpinfo.bmHeight,RGB(198,198,198));
	dc.DeleteDC(); */
}

void CMDSView::refreshslave_sel(int No)
{
	int i;
	CString tempstr;
	for (i = m_airno_s.GetCount() - 1; i >= 0; i--)
		m_airno_s.DeleteString(i);
	for (i = 0; i < pdoc->airlist[No].in_num; i++)
	{
		tempstr.Format("%d#", i);
		m_airno_s.InsertString(-1, tempstr);
	}
	m_airno_s.SetCurSel(0);
}

void CMDSView::OnOpapply()
{
	// TODO: Add your control notification handler code here
	CString tempstr;
	CString tempstr1, tempstrok, tempstrcan;
	pdoc->airlist[m_showNo].i_ctl_workmode = m_opmode.GetCurSel() + 1;
	pdoc->airlist[m_showNo].i_ctl_open = m_oponoff.GetCurSel();
	pdoc->airlist[m_showNo].i_ctl_coolsetin = m_coolsetin.GetCurSel(); //制冷进水设置
	pdoc->airlist[m_showNo].i_ctl_heatsetin = m_heatsetin.GetCurSel(); //制热进水设置	
	pdoc->airlist[m_showNo].m_ctrl_hotset = m_hotset.GetCurSel();
	if (pdoc->m_connectflag == 1 && pdoc->m_startflag == 1)//如果串口打开
	{
		pdoc->queryFunNo1 = pdoc->queryFunNo;
		pdoc->queryAirNo1 = pdoc->queryAirNo;
		pdoc->sendcmdflag = 1;
		pdoc->m_errorcount = 0;
		pdoc->queryFunNo = 7;
		pdoc->queryAirNo = m_showNo;
	}
}


void CMDSView::OnViewmpara()
{
	// TODO: Add your control notification handler code here
/*	Cmodoutdlg dlg;
	CPassworddlg pdlg;

//	if(pdlg.DoModal()!=IDOK)
//		return;

	dlg.m_airnum=pdoc->airnum;
	dlg.outairNo=m_showNo;
	if(dlg.DoModal()==IDOK)
	{
		;
	}	*/
}

void CMDSView::OnViewspara()
{
	// TODO: Add your control notification handler code here
	Cmod_slave_cfg dlg;
	if (dlg.DoModal() == IDOK)
	{
		;

	}


}


void CMDSView::OnClrRecord()
{
	// TODO: Add your control notification handler code here
	/*int No_s;
	CString TempSql;
	CString TableName;
	_bstr_t selectSql;
	for(No_s=0;No_s<15;No_s++)
	{
		TableName.Format("s%d",No_s);
		TempSql.Format("delete * from %s",TableName);
		selectSql=TempSql;
		theApp.ExcuteSql(theApp.m_pRecordset,selectSql);
	}*/
}

void CMDSView::recorddata_slave(int slave_no)
{
	CArchive ar(&pdoc->m_file[slave_no + 1], CArchive::store);
	pdoc->m_recordstr.Empty();
	CString tempstr, str;
	float f;
	int No = 0;
	CTime t = CTime::GetCurrentTime();
	tempstr.Format("%.2d%.2d%.2d", t.GetHour(), t.GetMinute(), t.GetSecond());
	pdoc->m_recordstr = tempstr;
	CString runmode[8] = { "测试","制冷","制热","热水","除霜","回收","待机","调试" };
	if (pdoc->airlist[No].indoor_air[slave_no].s_runmode >= 0 && pdoc->airlist[No].indoor_air[slave_no].s_runmode <= 5)
	{
		pdoc->m_recordstr += "  ";
		pdoc->m_recordstr += runmode[pdoc->airlist[No].indoor_air[slave_no].s_runmode];
	}
	CString wind[4] = { "停","低","中","高" };
	if (pdoc->airlist[No].indoor_air[slave_no].s_windmotor1 >= 0 && pdoc->airlist[No].indoor_air[slave_no].s_windmotor1 <= 3)
	{
		pdoc->m_recordstr += " ";
		pdoc->m_recordstr += wind[pdoc->airlist[No].indoor_air[slave_no].s_windmotor1];
	}
	if (pdoc->airlist[No].indoor_air[slave_no].s_windmotor2 >= 0 && pdoc->airlist[No].indoor_air[slave_no].s_windmotor2 <= 3)
	{
		pdoc->m_recordstr += " ";
		pdoc->m_recordstr += wind[pdoc->airlist[No].indoor_air[slave_no].s_windmotor2];
	}
	if (pdoc->airlist[No].indoor_air[slave_no].s_compre[0] == 0)
		tempstr.Format("关");
	else
		tempstr.Format("开");
	pdoc->m_recordstr += " ";
	pdoc->m_recordstr += tempstr;

	if (pdoc->airlist[No].indoor_air[slave_no].s_compre[1] == 0)
		tempstr.Format("关");
	else
		tempstr.Format("开");
	pdoc->m_recordstr += " ";
	pdoc->m_recordstr += tempstr;

	if (pdoc->airlist[No].indoor_air[slave_no].s_compre[2] == 0)
		tempstr.Format("关");
	else
		tempstr.Format("开");
	pdoc->m_recordstr += " ";
	pdoc->m_recordstr += tempstr;

	if (pdoc->airlist[No].indoor_air[slave_no].s_fourvalve1 == 0)
		tempstr.Format("关");
	else
		tempstr.Format("开");
	pdoc->m_recordstr += " ";
	pdoc->m_recordstr += tempstr;

	if (pdoc->airlist[No].indoor_air[slave_no].s_fourvalve2 == 0)
		tempstr.Format("关");
	else
		tempstr.Format("开");
	pdoc->m_recordstr += " ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%3d", pdoc->airlist[No].indoor_air[slave_no].s_ele_distension_valve1);
	pdoc->m_recordstr += "  ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%3d", pdoc->airlist[No].indoor_air[slave_no].s_ele_distension_valve2);
	pdoc->m_recordstr += "  ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%3d", pdoc->airlist[No].indoor_air[slave_no].s_ele_distension_valve3);
	pdoc->m_recordstr += "  ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%3d", pdoc->airlist[No].indoor_air[slave_no].s_ele_distension_valve4);
	pdoc->m_recordstr += "  ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1fHP", pdoc->airlist[No].indoor_air[slave_no].s_total_needed_HP);
	pdoc->m_recordstr += "    ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_targetsuperhot);
	pdoc->m_recordstr += "  ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_lowpre);
	pdoc->m_recordstr += "    ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_factsuperhot);
	pdoc->m_recordstr += "     ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_highpre);
	pdoc->m_recordstr += "      ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_factsuperhot2);
	pdoc->m_recordstr += "    ";
	pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp1);
	pdoc->m_recordstr += "     ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 150)
		pdoc->m_recordstr += "开路";
	else if (pdoc->airlist[No].s_tp1 <= 5)
		pdoc->m_recordstr += "短路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp2);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 150)
		pdoc->m_recordstr += "开路";
	else if (pdoc->airlist[No].s_tp1 <= 5)
		pdoc->m_recordstr += "短路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp3);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;


	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp4);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;
	//pdoc->m_recordstr+=tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp5);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp6);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp7);
	pdoc->m_recordstr += "  ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp8);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp9);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp10);
	pdoc->m_recordstr += "  ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp11);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	tempstr.Format("%.1f", pdoc->airlist[No].indoor_air[slave_no].s_tp12);
	pdoc->m_recordstr += "   ";
	if (pdoc->airlist[No].indoor_air[slave_no].s_tp1 >= 127)
		pdoc->m_recordstr += "短路";
	else if (pdoc->airlist[No].s_tp1 <= -127)
		pdoc->m_recordstr += "开路";
	else
		pdoc->m_recordstr += tempstr;

	/*tempstr.Format("%.1fA",pdoc->airlist[No].indoor_air[slave_no].s_ele1);
	pdoc->m_recordstr+="    ";
	pdoc->m_recordstr+=tempstr;

	tempstr.Format("%.1fA",pdoc->airlist[No].indoor_air[slave_no].s_ele2);
	pdoc->m_recordstr+="    ";
	pdoc->m_recordstr+=tempstr;*/
	pdoc->m_recordstr += "   ";
	pdoc->m_recordstr += valstr1;

	pdoc->m_recordstr += "   ";
	pdoc->m_recordstr += valstr2;

	pdoc->m_recordstr += "\r\n";
	ar.WriteString(pdoc->m_recordstr);
	ar.Close();
}

void CMDSView::SetHP(int airNo, int iHP)
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_sethp1 = iHP;
	SetDataForFunNo24(airNo);
}

void CMDSView::SetFan3(int airNo, int i, int num)//系统3风机1,2
{
	pdoc->airlist[airNo].DataToTemp();
	if (num == 1)
	{
		pdoc->airlist[airNo].s_f_windmotor21 = i;
	}
	if (num == 2)
	{
		pdoc->airlist[airNo].s_f_windmotor22 = i;
	}
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFan4(int airNo, int i, int num)
{
	pdoc->airlist[airNo].DataToTemp();
	if (num == 1)
	{
		pdoc->airlist[airNo].s_f_windmotor11 = i;
	}
	if (num == 2)
	{
		pdoc->airlist[airNo].s_f_windmotor12 = i;
	}
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFan1High(int airNo, int i)//系统2风机1
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_windmotor11 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFan1Low(int airNo, int i)//系统2风机2
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_windmotor12 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFan2High(int airNo, int i)//系统1风机1
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_windmotor21 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFan2low(int airNo, int i)//系统1风机2
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_windmotor22 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFourValve(int airNo, int i, int ms)
{
	pdoc->airlist[airNo].DataToTemp();
	if (ms == 1)//系统1四通阀
	{
		pdoc->airlist[airNo].s_fourvalve11 = i;
	}
	else if (ms == 2)//系统2四通阀
	{
		pdoc->airlist[airNo].s_fourvalve21 = i;
	}
	else if (ms == 3)//系统3四通阀
	{
		pdoc->airlist[airNo].s_f_fourvalve11 = i;
	}
	else if (ms == 4)//系统四四通阀
	{
		pdoc->airlist[airNo].s_f_fourvalve21 = i;
	}
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFourValve1(int airNo, int i)//系统1四通阀
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_fourvalve11 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFourValve12(int airNo, int i)//系统1四通阀2
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_fourvalve21 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFourValve2(int airNo, int i)//系统1四通阀
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_fourvalve31 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetFourValve21(int airNo, int i)//系统1四通阀
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_fourvalve41 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetMachine(int type, int open)
{
	if (type != 1 && type != 2 && type != 3 && type != 4)
		return;
	pdoc->airlist[0].DataToTemp();

	if (type == 1)//压缩机1
		pdoc->airlist[0].s_compre1[0] = open;
	else if (type == 2)//压缩机2
		pdoc->airlist[0].s_compre1[1] = open;
	else if (type == 3)//压缩机3
		pdoc->airlist[0].s_f_compre1[0] = open;
	else if (type == 4)//压缩机4
		pdoc->airlist[0].s_f_compre1[1] = open;
	SetDataForFunNo24(0);
}


void CMDSView::SetExv(int airNo, int iExv, int iIndex)
{
	/*if(iIndex!=1 && iIndex!=2&& iIndex!=3&& iIndex!=4)
		return;*/
	pdoc->airlist[airNo].DataToTemp();

	if (iIndex == 1)
		pdoc->airlist[airNo].s_ele_distension_valve11 = iExv;
	else if (iIndex == 2)
		pdoc->airlist[airNo].s_ele_distension_valve21 = iExv;
	else if (iIndex == 3)
		pdoc->airlist[airNo].s_ele_distension_valve31 = iExv;
	else if (iIndex == 4)
		pdoc->airlist[airNo].s_ele_distension_valve41 = iExv;
	if (iIndex == 5)
		pdoc->airlist[airNo].s_f_ele_distension_valve11 = iExv;
	else if (iIndex == 6)
		pdoc->airlist[airNo].s_f_ele_distension_valve21 = iExv;
	else if (iIndex == 7)
		pdoc->airlist[airNo].s_f_ele_distension_valve31 = iExv;
	else if (iIndex == 8)
		pdoc->airlist[airNo].s_f_ele_distension_valve41 = iExv;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetSolenValve1(int airNo, int i)//电磁阀1
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_ele_valve01 = i;
	SetDataForFunNo24(airNo);
}
void CMDSView::SetSolenValve2(int airNo, int i)//电磁阀2
{
	pdoc->airlist[airNo].DataToTemp();
	pdoc->airlist[airNo].s_ele_valve11 = i;
	SetDataForFunNo24(airNo);
}
/*
void CMDSView::SetExv(int airNo,int iIndex,int nStep)
{
	if(iIndex!=1 && iIndex!=2 )
		return;
	pdoc->airlist[airNo].DataToTemp();
	if(iIndex==1)   //设置EXV1,4=480
	{
		pdoc->airlist[airNo].s_ele_distension_valve11 = nStep;

	}
	else
	{
		pdoc->airlist[airNo].s_ele_distension_valve21 = nStep;
	}
	SetDataForFunNo6(airNo);
}*/
void CMDSView::SetRunmode(int iIndex)
{
	if (iIndex == 0)
	{
		m_oponoff.SetCurSel(0);
		OnOpapply();
	}
	else if (iIndex == 1)
	{
		m_oponoff.SetCurSel(1);
		m_opmode.SetCurSel(0);
		OnOpapply();
	}
	else if (iIndex == 2)
	{
		m_oponoff.SetCurSel(1);
		m_opmode.SetCurSel(1);
		OnOpapply();
	}

}

void CMDSView::SetFanFre(int airNo, int i, int num)
{
	pdoc->airlist[airNo].DataToTemp();
	if (i == 1)
		pdoc->airlist[airNo].s_fan_fre1 = num;
	else if (i == 2)
		pdoc->airlist[airNo].s_fan_fre2 = num;
	else if (i == 3)
		pdoc->airlist[airNo].s_fan_fre3 = num;
	else if (i == 4)
		pdoc->airlist[airNo].s_fan_fre4 = num;
	SetDataForFunNo24(airNo);
}

void CMDSView::SetMachineFre(int airNo, int type, int open)
{
	pdoc->airlist[airNo].DataToTemp();
	if (type == 1)
		pdoc->airlist[airNo].s_comp_fre1 = open;
	else if (type == 2)
		pdoc->airlist[airNo].s_comp_fre2 = open;
	else if (type == 3)
		pdoc->airlist[airNo].s_comp_fre3 = open;
	else if (type == 4)
		pdoc->airlist[airNo].s_comp_fre4 = open;
	SetDataForFunNo24(airNo);
}

int CMDSView::_SaveTestmodeSet(int& uchLanguage)
{
	BOOL nRetCode;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	strLanguage.Format("%d", uchLanguage);
	nRetCode = (BOOL)WritePrivateProfileString("LANGSET", "TESTMODE", strLanguage, strPath);

	return nRetCode;
}

int CMDSView::_ReadTestmodeSet(int& uchLanguage)
{
	int nTmp = 0;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	nTmp = GetPrivateProfileInt("LANGSET", "TESTMODE", FALSE, strPath);
	uchLanguage = nTmp;

	return TRUE;
}

void CMDSView::SetDo(int airNo, int donum, int i)
{
	pdoc->airlist[airNo].DataToTemp();
	if (donum == 1)
	{
		pdoc->airlist[airNo].S_DO1 = i;
	}
	else if (donum == 2)
	{
		pdoc->airlist[airNo].S_DO2 = i;
	}
	else if (donum == 3)
	{
		pdoc->airlist[airNo].S_DO3 = i;
	}
	else if (donum == 4)
	{
		pdoc->airlist[airNo].S_DO4 = i;
	}
	else if (donum == 11)
	{
		pdoc->airlist[airNo].SF_DO1 = i;
	}
	SetDataForFunNo24(airNo);
}

void CMDSView::SetDataForFunNo6(int outairNo)
{
	pdoc->queryFunNo1 = pdoc->queryFunNo;
	pdoc->queryAirNo1 = pdoc->queryAirNo;
	pdoc->sendcmdflag = 1;
	pdoc->m_errorcount = 0;
	pdoc->queryFunNo = 6;
	pdoc->queryAirNo = outairNo;
	pdoc->querySAirNo = 0;
	pdoc->airlist[outairNo].unit_no = 0xff;
}



void CMDSView::SetDataForFunNo24(int outairNo)
{
	pdoc->queryFunNo1 = pdoc->queryFunNo;
	pdoc->queryAirNo1 = pdoc->queryAirNo;
	pdoc->sendcmdflag = 1;
	pdoc->m_errorcount = 0;
	pdoc->queryFunNo = 24;
	pdoc->queryAirNo = outairNo;
	pdoc->querySAirNo = 0;
	pdoc->airlist[outairNo].unit_no = 0xff;
}


void CMDSView::SetDataForFunNo26(int outairNo)
{
	pdoc->queryFunNo1 = pdoc->queryFunNo;
	pdoc->queryAirNo1 = pdoc->queryAirNo;
	pdoc->sendcmdflag = 0;
	pdoc->m_errorcount = 0;
	pdoc->queryFunNo = 26;
	pdoc->queryAirNo = outairNo;
	pdoc->querySAirNo = 0;
	pdoc->airlist[outairNo].unit_no = 0xff;
}

void RecordTempData(int airNo)
{
	fTH1 = pdoc->airlist[airNo].s_tp1;
	fTH2 = pdoc->airlist[airNo].s_tp2;
	fTH3 = pdoc->airlist[airNo].s_tp3;
	fTH4 = pdoc->airlist[airNo].s_tp4;
	fTH8 = pdoc->airlist[airNo].s_tp8;
	fTH9 = pdoc->airlist[airNo].s_tp9;
	fTH10 = pdoc->airlist[airNo].s_tp10;
	fTH11 = pdoc->airlist[airNo].s_tp11;
	fTH12 = pdoc->airlist[airNo].s_tp12;
	fLP1 = pdoc->airlist[airNo].s_lowpre;
	fLP2 = pdoc->airlist[airNo].s_highpre; // 系统1,2低压,对应s_lowpre, s_highpre;
	fELE1 = pdoc->airlist[airNo].s_ele;
	fELE2 = pdoc->airlist[airNo].s_ele2;

}

CString GetCurTime()
{
	CString strRet("");
	CTime tempTime = CTime::GetCurrentTime();
	strRet.Format("%2.2d%.2d%.2d_%.2d:%.2d:%.2d", tempTime.GetYear(), tempTime.GetMonth(), tempTime.GetDay(), tempTime.GetHour(), tempTime.GetMinute(), tempTime.GetSecond());
	return strRet;
}

int GetSections(CStringArray& arrSection, CString iniFullPath)
{
	int iLength = 0;
	int   iPos = 0;
	TCHAR   chSectionNames[2000] = { 0 };   //总的提出来的字符串   
	TCHAR   chSection[100] = { 0 };   //存放一个段名。   
	//char   chSectionNames[2000]={0};   //总的提出来的字符串   
	//char   chSection[100]={0};   //存放一个段名。   
	DWORD nChar = GetPrivateProfileSectionNames(chSectionNames, sizeof(chSectionNames), iniFullPath);
	arrSection.RemoveAll();//xu
	//以下循环，截断到两个连续的0   
	for (int i = 0; i < nChar; i++)
	{
		if (chSectionNames[i] == 0)
		{
			arrSection.Add(chSection);
			if (chSectionNames[i] == chSectionNames[i + 1])
			{
				break;
			}
			memset(chSection, 0, iLength);
			iPos = 0;
			iLength = 0;
		}
		else
		{
			chSection[iPos++] = chSectionNames[i];
			iLength++;
		}
	}
	return   (int)arrSection.GetSize();
}

CString getExeDir()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH在WINDEF.h中定义了，等于260  
	memset(exeFullPath, 0, MAX_PATH);
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	CString stemp1 = CString(exeFullPath);
	int n = stemp1.ReverseFind(_T('\\'));
	CString ret = stemp1.Left(n);
	return ret;

}

void CMDSView::OnSelchangeComboConfigname()
{
	// TODO: Add your control notification handler code here
		//xu170215
	CStringArray arrSection;
	CString strTemp;
	GetSections(arrSection, iniFullPath);
	int iNo = m_cmb_configname.GetCurSel();
	CString curSection = arrSection.GetAt(iNo + 1);
	strTemp.Format(_T("%d"), iNo + 1);
	WritePrivateProfileString("LANGSET", "CURRENT", strTemp, iniFullPath);

	GetPrivateProfileString(curSection, "A", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_a.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "B", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_b.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "C", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_c.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "D", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_d.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "E", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_e.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "F", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_f.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "G", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_g.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "H", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_x.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "I", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_m.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "J", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_n.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "K", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_h.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "L", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_j.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "M", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_i.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "N", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	m_edit_o.SetWindowText(strTemp);
	GetPrivateProfileString(curSection, "V", "0", strTemp.GetBuffer(20), 20, iniFullPath);
	yun_password = strTemp;


}

void CMDSView::OnButtonSaveconfig()
{
	// TODO: Add your control notification handler code here
	CStringArray arrSection;
	CString strTemp;
	GetSections(arrSection, iniFullPath);
	int iNo = m_cmb_configname.GetCurSel();
	CString curSection = arrSection.GetAt(iNo + 1);
	strTemp.Format(_T("%d"), iNo + 1);

	m_edit_a.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "A", strTemp, iniFullPath);
	m_edit_b.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "B", strTemp, iniFullPath);
	m_edit_c.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "C", strTemp, iniFullPath);
	m_edit_d.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "D", strTemp, iniFullPath);
	m_edit_e.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "E", strTemp, iniFullPath);
	m_edit_f.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "F", strTemp, iniFullPath);
	m_edit_g.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "G", strTemp, iniFullPath);
	m_edit_x.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "H", strTemp, iniFullPath);
	m_edit_m.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "I", strTemp, iniFullPath);
	m_edit_n.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "J", strTemp, iniFullPath);
	m_edit_h.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "K", strTemp, iniFullPath);
	m_edit_j.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "L", strTemp, iniFullPath);
	m_edit_i.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "M", strTemp, iniFullPath);
	m_edit_o.GetWindowText(strTemp);
	WritePrivateProfileString(curSection, "N", strTemp, iniFullPath);
	m_edit_a.EnableWindow(FALSE);
	m_edit_b.EnableWindow(FALSE);
	m_edit_c.EnableWindow(FALSE);
	m_edit_d.EnableWindow(FALSE);
	m_edit_e.EnableWindow(FALSE);
	m_edit_f.EnableWindow(FALSE);
	m_edit_g.EnableWindow(FALSE);
	m_edit_x.EnableWindow(FALSE);
	m_edit_m.EnableWindow(FALSE);
	m_edit_n.EnableWindow(FALSE);
	m_edit_h.EnableWindow(FALSE);
	m_edit_j.EnableWindow(FALSE);
	m_edit_i.EnableWindow(FALSE);
	m_edit_o.EnableWindow(FALSE);
}

void CMDSView::OnButtonAddconfig()
{

	CPassworddlg pdlg;

	if (pdlg.DoModal() != IDOK)
		return;
	m_edit_a.EnableWindow(TRUE);
	m_edit_b.EnableWindow(TRUE);
	m_edit_c.EnableWindow(TRUE);
	m_edit_d.EnableWindow(TRUE);
	m_edit_e.EnableWindow(TRUE);
	m_edit_f.EnableWindow(TRUE);
	m_edit_g.EnableWindow(TRUE);
	m_edit_x.EnableWindow(TRUE);
	m_edit_m.EnableWindow(TRUE);
	m_edit_n.EnableWindow(TRUE);
	m_edit_h.EnableWindow(TRUE);
	m_edit_j.EnableWindow(TRUE);
	m_edit_i.EnableWindow(TRUE);
	m_edit_o.EnableWindow(TRUE);
	// TODO: Add your control notification handler code here
	/*CAddConfig aDlg;
	if(aDlg.DoModal()==IDOK)
	{
		m_cmb_configname.AddString(aDlg.m_configname);
		m_cmb_configname.SetCurSel(m_cmb_configname.GetCount()-1);
		OnSelchangeComboConfigname();
	}*/
}

void CMDSView::OnButtonDelonfig()
{
	// TODO: Add your control notification handler code here
	int iTotal = m_cmb_configname.GetCount();
	if (iTotal <= 1)
	{
		AfxMessageBox(_T("至少保留一个配置"));
		return;
	}

	int iNo = m_cmb_configname.GetCurSel();
	CString curSection;
	m_cmb_configname.GetLBText(iNo, curSection);
	WritePrivateProfileString(curSection, NULL, NULL, iniFullPath);
	m_cmb_configname.DeleteString(iNo);

	m_cmb_configname.SetCurSel(0);
	OnSelchangeComboConfigname();
}


int CMDSView::_SaveInputSet(int& uchLanguage)
{
	BOOL nRetCode;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	strLanguage.Format("%d", uchLanguage);
	nRetCode = (BOOL)WritePrivateProfileString("LANGSET", "INPUT", strLanguage, strPath);

	return nRetCode;
}
int CMDSView::_ReadInputSet(int& uchLanguage)
{
	int nTmp = 0;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	nTmp = GetPrivateProfileInt("LANGSET", "INPUT", FALSE, strPath);
	uchLanguage = nTmp;

	return TRUE;
}

int CMDSView::_ReadInputNAMESet(char* strLanguage)
{
	int nTmp = 0;
	char exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";
	nTmp = GetPrivateProfileString("LANGSET", "NAME", "", strLanguage, 20, strPath);

	return TRUE;
}

int CMDSView::_SaveInputNAMESet(char* strLanguage)
{
	int nTmp = 0;
	char exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";
	nTmp = WritePrivateProfileString("LANGSET", "NAME", strLanguage, strPath);

	return TRUE;
}
int CMDSView::_SaveInputGPSSet(int& uchLanguage)
{
	BOOL nRetCode;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	strLanguage.Format("%d", uchLanguage);
	nRetCode = (BOOL)WritePrivateProfileString("LANGSET", "INPUTGPS", strLanguage, strPath);

	return nRetCode;
}
int CMDSView::_ReadInputGPSSet(int& uchLanguage)
{
	int nTmp = 0;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	nTmp = GetPrivateProfileInt("LANGSET", "INPUTGPS", FALSE, strPath);
	uchLanguage = nTmp;

	return TRUE;
}


int CMDSView::_SaveFunhavelowSet(int& uchLanguage)
{
	BOOL nRetCode;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	strLanguage.Format("%d", uchLanguage);
	nRetCode = (BOOL)WritePrivateProfileString("LANGSET", "FUNHAVELOW", strLanguage, strPath);

	return nRetCode;
}

int CMDSView::_ReadFunhavelowSet(int& uchLanguage)
{
	int nTmp = 0;
	char exeFullPath[MAX_PATH];
	CString strPath, strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	nTmp = GetPrivateProfileInt("LANGSET", "FUNHAVELOW", FALSE, strPath);
	uchLanguage = nTmp;

	return TRUE;
}
void CMDSView::OnBnClickedRadioSaoma()
{
	// TODO: Add your control notification handler code here

	m_bInput = 0;

	((CButton*)GetDlgItem(IDC_RADIO_SAOMA))->SetCheck(1);
	GetDlgItem(IDC_EDIT_USERINFO5)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_USERINFO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_USERINFO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_USERINFO3)->EnableWindow(FALSE);
	m_userinfo1.SetWindowText("");
	m_userinfo2.SetWindowText("");
	m_userinfo3.SetWindowText("");
	//	 m_userinfo4.SetWindowText("");
	m_userinfo5.SetWindowText("");
	_SaveInputSet(m_bInput);
}


void CMDSView::OnBnClickedRadioHandinput()
{
	// TODO: Add your control notification handler code here
	m_bInput = 1;
	((CButton*)GetDlgItem(IDC_RADIO_HANDINPUT))->SetCheck(1);
	GetDlgItem(IDC_EDIT_USERINFO5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_USERINFO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_USERINFO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_USERINFO3)->EnableWindow(TRUE);
	m_userinfo1.SetWindowText("");
	m_userinfo2.SetWindowText("");
	m_userinfo3.SetWindowText("");
	//	 m_userinfo4.SetWindowText("");
	m_userinfo5.SetWindowText("");
	_SaveInputSet(m_bInput);
}


void CMDSView::OnChangeEditUserinfo5()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString str1, str2, str3, str4, str5, str6, str7, strNull = _T("");
	char st1[500], st2[500], st3[500], saomachr[500];
	if (m_bInput == 0)
	{
		m_userinfo5.GetWindowText(str5);//1 EKAC460BR1-FEA00000718 190116      共31个字符
		if (str5 != strNull)
		{//分析扫码字符串
			strcpy(saomachr, str5);
			int len;
			len = strlen(saomachr);
			if (len > 16)
			{
				saomachr[len] = 0;
				strcpy(st3, &saomachr[len - 6]);

				saomachr[len - 7] = 0;
				strcpy(st2, &saomachr[len - 15]);

				saomachr[len - 15] = 0;
				strcpy(st1, &saomachr[2]);
				int st1len, ii;
				st1len = strlen(st1);
				for (ii = 0; ii < st1len; ii++)
					st1[ii] = toupper(st1[ii]);

				str1.Format("%s", st1);
				str2.Format("%s", st2);
				str3.Format("%s", st3);

				m_userinfo1.SetWindowText(str1);
				m_userinfo2.SetWindowText(str2);
				m_userinfo3.SetWindowText(str3);

			}
		}


	}
}


void CMDSView::OnSelchangeFunhavelow()
{
	// TODO: Add your control notification handler code here
	int uch;
	uch = m_funhavelow.GetCurSel();
	if (uch != m_bFunhavelow)
	{
		_SaveFunhavelowSet(uch);
		m_bFunhavelow = uch;
	}
}


void CMDSView::OnBnClickedAutotest()
{
	// TODO: Add your control notification handler code here
	if (m_bFunhavelow == 0)
	{
		SetTimer(8, 800, NULL);
	}
	else if (m_bFunhavelow == 1)
	{
		SetTimer(6, 800, NULL);
	}
	else if (m_bFunhavelow == 2)
	{
		SetTimer(10, 800, NULL);
	}
	else
	{
		SetTimer(9, 800, NULL);
	}

}


void CMDSView::OnSetfocusEditUserinfo5()
{
	// TODO: Add your control notification handler code here
}


void CMDSView::OnBnClickedRadioGpsSaoma()
{
	// TODO: Add your control notification handler code here
	m_bGPSInput = 0;

	((CButton*)GetDlgItem(IDC_RADIO_GPS_SAOMA))->SetCheck(1);
	//	   GetDlgItem(IDC_EDIT_USERINFO6)->EnableWindow(TRUE);
	//	  GetDlgItem(IDC_EDIT_USERINFO7)->EnableWindow(FALSE);

	m_userinfo7.SetWindowText("");

	_SaveInputGPSSet(m_bGPSInput);
}


void CMDSView::OnBnClickedRadioGpsHandinput()
{
	// TODO: Add your control notification handler code here
	m_bGPSInput = 1;
	((CButton*)GetDlgItem(IDC_RADIO_GPS_HANDINPUT))->SetCheck(1);
	//	  GetDlgItem(IDC_EDIT_USERINFO6)->EnableWindow(FALSE);
		//  	  GetDlgItem(IDC_EDIT_USERINFO7)->EnableWindow(TRUE);

	m_userinfo7.SetWindowText("");

	_SaveInputGPSSet(m_bGPSInput);
}


void CMDSView::OnBnClickedButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_exv_button_ok = 1;
}


void CMDSView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_button1 = 1;
}


void CMDSView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_button2 = 1;
}

HBITMAP CMDSView::GetBitmapHandle(UINT uID, HBITMAP& hBitmap)
{
	CBitmap bitmap;
	bitmap.LoadBitmap(uID);
	hBitmap = (HBITMAP)bitmap.Detach();
	return HBITMAP();
}


void CMDSView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//SetTimer(6, 800, NULL);
	iStep = 811;

}


void CMDSView::OnCbnSelchangeComboTest()
{
	// TODO: 在此添加控件通知处理程序代码
	int uch;
	uch = m_test_mode.GetCurSel();
	if (uch != m_bFunhavelow)
	{
		_SaveTestmodeSet(uch);
		m_bFunhavelow = uch;
	}
}

