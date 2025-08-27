// MDSView.h : interface of the CMDSView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES
#include "ColorEdit.h"
#include "Colorstatic.h"
#include "XPButton.h"
#include "HoverEdit.h"
#include "waitpdf.h"
#include "ColorLabel.h"
#include "LoginService.h"

#if !defined(AFX_MDSVIEW_H__834B453F_11F1_400C_88B9_7DFA05A3EE36__INCLUDED_)
#define AFX_MDSVIEW_H__834B453F_11F1_400C_88B9_7DFA05A3EE36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMDSView : public CFormView
{
public: // create from serialization only
	CMDSView(); 
	DECLARE_DYNCREATE(CMDSView)
 	void ExcuteSql(_RecordsetPtr &rs,_bstr_t sql);
	_RecordsetPtr  m_pRecordset1;
public:
	//{{AFX_DATA(CMDSView)
	enum { IDD = IDD_MDS_FORM };
	CHoverEdit	m_edit_cfan;
	CHoverEdit	m_edit_chvalve;
	CHoverEdit	m_edit_revalve;
	CComboBox	m_hotset;
	CHoverEdit	m_deit_pump3;
	CHoverEdit	m_edit_pump2;
	CHoverEdit	m_edit_media_s;
	CHoverEdit	m_edit_media_m;
	CXPButton	m_clr_record;
	CHoverEdit	m_hp_s1;
	CHoverEdit	m_elevavle2_s;
	CHoverEdit	m_elevavle_s;
	CHoverEdit	m_airversion_s;
	CHoverEdit	m_airtype1_s;
	CHoverEdit	m_ahot_s;
	CXPButton	m_viewspara;
	CXPButton	m_viewmpara;
	CHoverEdit	m_ahot;
	CHoverEdit	m_ehot;
	CHoverEdit	m_4wv4;
	CHoverEdit	m_pumpedit;
	CComboBox	m_heatsetin;
	CComboBox	m_coolsetin;
	CHoverEdit	m_4wv3;
	CXPButton	m_opapplybt;
	CComboBox	m_oponoff;
	CComboBox	m_opmode;
	CComboBox	m_airno_s;
	CHoverEdit	m_hicsupercool_s;
	CHoverEdit	m_targetshot_s;
	CHoverEdit	m_factshot_s;
	CHoverEdit	m_totalneedhp_s;
	CHoverEdit	m_runmode_s;
	CHoverEdit	m_tp1_s;
	CHoverEdit	m_tp2_s;
	CHoverEdit	m_tp3_s;
	CHoverEdit	m_tp4_s;
	CHoverEdit	m_tp5_s;
	CHoverEdit	m_tp6_s;
	CHoverEdit	m_tp7_s;
	CHoverEdit	m_tp8_s;
	CHoverEdit	m_tp9_s;
	CHoverEdit	m_tp10_s;
	CHoverEdit	m_tp11_s;
	CHoverEdit	m_tp12_s;
	CHoverEdit	m_oilre_s;
	CHoverEdit	m_oilblance_s;
	CHoverEdit	m_lowpre_s;
	CHoverEdit	m_hp_s;
	CHoverEdit	m_highpre_s;
	CHoverEdit	m_fourvalve2_s;
	CHoverEdit	m_fourvalve1_s;
	CHoverEdit	m_fan2_s;
	CHoverEdit	m_fan1_s;
	CHoverEdit	m_eledisten4_s;
	CHoverEdit	m_eledisten3_s;
	CHoverEdit	m_eledisten2_s;
	CHoverEdit	m_eledisten1_s;
	CHoverEdit	m_comp6_s;
	CHoverEdit	m_comp5_s;
	CHoverEdit	m_comp4_s;
	CHoverEdit	m_comp3_s;
	CHoverEdit	m_comp2_s;
	CHoverEdit	m_comp1_s;
	CXPButton	m_readcomptimer;
	CXPButton	m_modoutbt;
	CXPButton	m_bt1;
	CXPButton	m_apecilbt;
	CXPButton	m_alarmbt;
	CHoverEdit	m_recordtimeedit;
	CHoverEdit	m_outnumberedit;
	CComboBox	m_bandno;
	CHoverEdit	m_runtime;
	CHoverEdit	m_outtime;
	CXPButton	m_testcodebt;
	CHoverEdit	m_hicsupercool;
	CHoverEdit	m_targetshot;
	CHoverEdit	m_factshot;
	CButton		m_iniflagchk;
	CListBox	m_alarmlist;
	CListBox	m_alarmlist2;
	CListBox	m_alarmlist3;
	CComboBox	m_comNo;
	CComboBox	m_airno;
	CHoverEdit	m_totalneedhp;
	CHoverEdit	m_runmode;
	CHoverEdit	m_pwmout;
	CHoverEdit	m_tp1;
	CHoverEdit	m_tp2;
	CHoverEdit	m_tp3;
	CHoverEdit	m_tp4;
	CHoverEdit	m_tp5;
	CHoverEdit	m_tp6;
	CHoverEdit	m_tp7;
	CHoverEdit	m_tp8;
	CHoverEdit	m_tp9;
	CHoverEdit	m_tp10;
	CHoverEdit	m_tp11;
	CHoverEdit	m_tp12;
	CHoverEdit	m_oilre;
	CHoverEdit	m_oilblance;
	CHoverEdit	m_lowpre;
	CHoverEdit	m_innuber;
	CHoverEdit	m_hp;
	CHoverEdit	m_highpre;
	CHoverEdit	m_fourvalve2;
	CHoverEdit	m_fourvalve1;
	CHoverEdit	m_edbldc_speed2;
	CHoverEdit	m_edbldc_speed1;
	CHoverEdit	m_eledisten4;
	CHoverEdit	m_eledisten3;
	CHoverEdit	m_eledisten2;
	CHoverEdit	m_eledisten1;
	CHoverEdit	m_esv1;
	CHoverEdit	m_esv2;
	CHoverEdit	m_esv3;
	CHoverEdit	m_esv4;
	CHoverEdit	m_comp2;
	CHoverEdit	m_comp1;
	CHoverEdit	m_airversion;
	CHoverEdit	m_airtype3;
	CHoverEdit	m_airtype2;
	CHoverEdit	m_airtype1;
	CXPButton	m_connectbtn;
	CHoverEdit	m_edit_a; //xu170213
	CHoverEdit	m_edit_b;
	CHoverEdit	m_edit_c;
	CHoverEdit	m_edit_d;
	CHoverEdit	m_edit_e;
	CHoverEdit	m_edit_f;
	CHoverEdit	m_edit_g;
	CHoverEdit	m_edit_h;
	CHoverEdit	m_edit_i;
	CHoverEdit	m_edit_j;
	CHoverEdit	m_edit_k;
	CComboBox	m_cmb_configname;
	CXPButton   m_saveconfig;
	CXPButton   m_delconfig;
	CXPButton   m_addconfig;
	CHoverEdit  m_userinfo1;
	CHoverEdit  m_userinfo2;
	CHoverEdit  m_userinfo3;
	CHoverEdit  m_userinfo4;
		CHoverEdit  m_userinfo5;
			//CColorLabel m_static_title;
	BOOL	m_inifalg;
	int		m_outnumber;
	int		m_recordtime;
	int m_bInput;
	int m_bGPSInput;
	int m_bFunhavelow;
	int errflag;
	CString valstr1,valstr2,valstr3;//3为机型名称,
	CString VAL1, VAL2,VAL3;
		char testname[20];
	LoginService *loginService;
	//}}AFX_DATA

// Attributes
public:
	CMDSDoc* GetDocument();
	void ShowInformation(CString &InforStr);
		int _ReadInputSet(int &uchLanguage);
	int _SaveInputSet(int &uchLanguage);
	int _SaveFunhavelowSet(int &uchLanguage);
	int _ReadFunhavelowSet(int &uchLanguage);
		int _ReadInputGPSSet(int &uchLanguage);
	int _SaveInputGPSSet(int &uchLanguage);
		int _ReadInputNAMESet(char *strLanguage);
		int _SaveInputNAMESet(char *strLanguage);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDSView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	void recorddata_slave(int slave_no);
	virtual ~CMDSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDSView)
	afx_msg void OnIndoorbtn();
	afx_msg void OnModoutbtn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConnectbtn();
	afx_msg void OnSelchangeAirno();
	afx_msg void OnApecilebtn();
	afx_msg void OnSelchangeComno();
	afx_msg void OnAlarmbtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTestcode();
	afx_msg void OnSlaveoutbtn();
	afx_msg void OnSelchangeBand();
	afx_msg void OnReadcomptime();
	afx_msg void OnSelchangeAirnoS();
	afx_msg void OnOpapply();
	afx_msg void OnViewmpara();
	afx_msg void OnViewspara();
	afx_msg void OnClrRecord();
	afx_msg LRESULT OnMdsViewMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSelchangeComboConfigname();
	afx_msg void OnButtonSaveconfig();
	afx_msg void OnButtonAddconfig();
	afx_msg void OnButtonDelonfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MessAddString(CString valstring);
	void refreshslave_sel(int No);
	void showerror(int No);
	void showdata(int No);
	void showdata_s(int No,int No_s);
	void showdata_slave(int No,int No_s);
	void showcomptime(int No);
	void recorddata(int No);
   void SetMDSViewMessage();
	int m_tempbytecount;
	int m_readlenght;
	int m_showNo;			//当前查询机组号
	int m_showNo_s;			//当前查询机组号
	CByteArray Inputdata;
	HBRUSH m_listbkbrush;
	HBRUSH m_bkbrush;
	HBRUSH m_bkbrush1;
	HBRUSH m_bkbrush2;
	HBRUSH m_bkbrush3;
	HBRUSH m_bkbrush4;
	COLORREF m_bkcolor;

	CBitmap m_logobmp;

	int timer1flag;		//0--停止 1--计时
	int timer2flag;
	int timer3flag;
	int timer4flag;
	int timer5flag;
	int timer6flag;

	int timecount;
	waitpdf * WaitingPDf;//显示提示框；

public:
	int _SaveTestmodeSet(int& uchLanguage);
	int _ReadTestmodeSet(int& uchLanguage);
	void SetDo(int airNo, int donum, int i);
	void SetDataForFunNo6(int outairNo); //设置数据,准备发射命令6
	void SetDataForFunNo24(int outairNo); 
	void SetDataForFunNo26(int outairNo); 
	void SetHP(int airNo,int iHP);//设置水盘电加热
	void SetFan3(int airNo, int i, int num);
	void SetFan4(int airNo, int i, int num);
	//设置HP
	void SetFan1High(int airNo, int i);
	void SetFan1Low(int airNo, int i);
	void SetFan2High(int airNo,int i);
	void SetFan2low(int airNo, int i);
	void SetFourValve(int airNo, int i,int ms);
	void SetFourValve1(int airNo,int i);
	void SetFourValve12(int airNo,int i);
	void SetFourValve2(int airNo, int i);
	void SetFourValve21(int airNo, int i);
	void SetExv(int airNo,int iExv,int iIndex);//设置EXV, iIndex:1--EXV1  2--EXV2
	void SetSolenValve1(int airNo, int i);
	void SetSolenValve2(int airNo, int i);
	void SetMachine(int type,int open);
	//void Set2Exv(int airNo,int iIndex); //设置2个exv, iIndex:1--exv1,4=480  2--exv2,3=480
	void SetRunmode(int iIndex);     //iIndex:0--关机  1--制冷启动  2--制热启动
	void SetFanFre(int airNo, int i, int num);
	void SetMachineFre(int airNo, int type, int open);
	int m_iUnitType; //xu170106 机型: 0--标准,1--低温
	int m_radio_erweima;//二维码扫码标志
	CString iniFullPath;//Setting.config 路径
	afx_msg void OnBnClickedRadioSaoma();
	afx_msg void OnBnClickedRadioHandinput();
	afx_msg void OnChangeEditUserinfo5();
	CComboBox m_funhavelow;
	CString s_funhavelow;
	afx_msg void OnSelchangeFunhavelow();
//	CEdit m_ele1;
//	CEdit m_ele2;
	afx_msg void OnBnClickedAutotest();
	afx_msg void OnSetfocusEditUserinfo5();
	CColorLabel m_static_title;
	CHoverEdit m_userinfo7;
	afx_msg void OnBnClickedRadioGpsSaoma();
	afx_msg void OnBnClickedRadioGpsHandinput();
	CComboBox m_cmb_yun;
	CHoverEdit m_ele1;
	CHoverEdit m_ele2;
	CHoverEdit m_highpre1;
	CHoverEdit m_highpre2;
	CHoverEdit m_tph13;
	CHoverEdit m_tph14;
	CHoverEdit m_exv1_216;
	CHoverEdit m_exv4_216;
	CHoverEdit m_edithot_eheat;
	CHoverEdit m_exv2_216;
	CHoverEdit m_exv5_216;
	CHoverEdit m_exv3_216;
	CHoverEdit m_exv6_216;
	CHoverEdit m_edit_x;
	CButton m_button;
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CButton m_button11;
	CButton m_button21;
	//CButton m_check;
	HBITMAP GetBitmapHandle(UINT uID, HBITMAP& hBitmap);
	HBITMAP m_open;
	HBITMAP m_off;
	CStatic m_ctrl1;
	CStatic m_ctrl2;
	//CStatic* m_vt;
	afx_msg void OnBnClickedButton3();
	CHoverEdit m_fan3;
	CHoverEdit m_fan4;
	CHoverEdit m_ftp1;
	CHoverEdit m_ftp2;
	CHoverEdit m_ftp3;
	CHoverEdit m_ftp4;
	CHoverEdit m_ftp5;
	CHoverEdit m_ftp6;
	CHoverEdit m_ftp7;
	CHoverEdit m_ftp8;
	CHoverEdit m_ftp9;
	CHoverEdit m_ftp10;
	CHoverEdit m_ftp11;
	CHoverEdit m_ftp12;

	CHoverEdit m_flp1;
	CHoverEdit m_ffan1;
	CHoverEdit m_ffan2;
	CHoverEdit m_f4wv1;
	CHoverEdit m_fele1;
	CHoverEdit m_fcomp3;
	CHoverEdit m_edit_m;
	CHoverEdit m_edit_n;
	//CComboBox m_mchange;
	CString yun_password;
	CHoverEdit m_ftp13;
	CHoverEdit m_ftp14;
	CHoverEdit m_eledisten5;
	CHoverEdit m_eledisten6;
	CHoverEdit m_eledisten7;
	CHoverEdit m_eledisten8;
	CHoverEdit m_edit_o;
	afx_msg void OnCbnSelchangeComboTest();
	CComboBox m_test_mode;
	CEdit m_edit_gaoya1;
	CEdit m_edit_gaoya2;
	CEdit m_edit_gaoyaf1;
	CEdit m_edit_gaoyaf2;
};

#ifndef _DEBUG  // debug version in MDSView.cpp
inline CMDSDoc* CMDSView::GetDocument()
   { return (CMDSDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDSVIEW_H__834B453F_11F1_400C_88B9_7DFA05A3EE36__INCLUDED_)
