// MDSDoc.h : interface of the CMDSDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDSDOC_H__1EFA001C_B321_4685_A816_0B11C7D3ABF9__INCLUDED_)
#define AFX_MDSDOC_H__1EFA001C_B321_4685_A816_0B11C7D3ABF9__INCLUDED_
#include "mscomm.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "air.h"

class CMDSDoc : public CDocument
{
protected: // create from serialization only
	CMDSDoc();
	DECLARE_DYNCREATE(CMDSDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDSDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CTimeSpan m_oldruntime;
	CTimeSpan m_timer1runtime;
	CTimeSpan m_timer2runtime;
	CTimeSpan m_timer3runtime;
	CTimeSpan m_timer4runtime;
	CTimeSpan m_timer5runtime;
	CTimeSpan m_timer6runtime;

	CTime m_starttime;
	CTime m_starttimer1;
	CTime m_starttimer2;
	CTime m_starttimer3;
	CTime m_starttimer4;
	CTime m_starttimer5;
	CTime m_starttimer6;
	
	CString m_timername[6];
	void query_code_set();
	void query_out_set(int airNo);//查询外机配置
	void query_in_set(int airNo);//查询内机配置
	void query_air_status(int airNo);//查询机组运行状态
	void query_test_status(int airNo);
	void query_out_para(int airNo);//查询外机运行参数
	void query_in_para(int airNo);//查询内机运行参数

	
	void modify_out_para(int airNo);  //修改外机配置参数

	void send_oc_inair(int airNo);			 //开关部分内机运行控制命令
	void send_oc_allinair(int airNo);		 //开关全部内机运行控制命令
	void send_defro_spe(int airNo);			//手动除霜特殊运行控制命令
	void seng_openvalve_spe(int airNo);		//调试时开阀控制命令
	void seng_maskin_spe(int airNo);		//屏蔽内机通讯控制命令
	
	void query_comp_time(int airNo);		//读压缩机累计运行时间
	void query_exit_mode(int airNo);
	void clear_eePROM(int airNo);			//清除压缩机累计运行时间

	int reply_out_set(CByteArray* inbyte);//响应外机配置
	int reply_in_set(CByteArray* inbyte);//响应内机配置
	int reply_air_status(CByteArray* inbyte);//响应机组运行状态
	int reply_test_status(CByteArray* inbyte);
	int reply_out_para(CByteArray* inbyte);//响应外机运行参数
	int reply_in_para(CByteArray* inbyte);//响应内机运行参数
	int reply_comp_time(CByteArray* inbyte);//响应读压缩机累计运行时间

	int reply_mofify_out_para(CByteArray* inbyte);	//响应修改外机配置参数

	int getcommdata(CByteArray* inbyte);	//从串口得到数据并校验，返回功能号，返回0收到数据不正确
	void set_comm();			//设置串口
	air airlist[1];//机组对象
	int airnum;		//机组数量
	int queryopen;	//定时查询开关标志
	int queryAirNo;	//要当前查询的机组号
	int queryFunNo; //查询的功能号
	int sendcmdflag;//常规查询与6、7、8发送命令查询标号
	int queryAirNo1;//保存当前查询的机组号
	int queryFunNo1; //保存查询的功能号
	int querySAirNo;	//要当前查询的从机机组号

	int m_errorcount;//发送一次命令之后的错误次数
	int m_commNo;	//串口号
	int m_commband;	//波特率
	int m_startflag;//初始化标志
	int m_connectflag;	//连接标志
	
	inair m_inair;
	int m_select[48];

	int m_maskflag[48];	//用于命令11
	//串口输出数据
	CByteArray outbuf;	
	COleVariant varOutput; 
	UINT crc;
	int temp;

	//文件记录
	CFile m_file[32];
//	CFile ftestfile=NULL;
//	CArchive m_archive;
	CString m_recordstr;
	
	virtual ~CMDSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDSDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDSDOC_H__1EFA001C_B321_4685_A816_0B11C7D3ABF9__INCLUDED_)
