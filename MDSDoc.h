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
	void query_out_set(int airNo);//��ѯ�������
	void query_in_set(int airNo);//��ѯ�ڻ�����
	void query_air_status(int airNo);//��ѯ��������״̬
	void query_test_status(int airNo);
	void query_out_para(int airNo);//��ѯ������в���
	void query_in_para(int airNo);//��ѯ�ڻ����в���

	
	void modify_out_para(int airNo);  //�޸�������ò���

	void send_oc_inair(int airNo);			 //���ز����ڻ����п�������
	void send_oc_allinair(int airNo);		 //����ȫ���ڻ����п�������
	void send_defro_spe(int airNo);			//�ֶ���˪�������п�������
	void seng_openvalve_spe(int airNo);		//����ʱ������������
	void seng_maskin_spe(int airNo);		//�����ڻ�ͨѶ��������
	
	void query_comp_time(int airNo);		//��ѹ�����ۼ�����ʱ��
	void query_exit_mode(int airNo);
	void clear_eePROM(int airNo);			//���ѹ�����ۼ�����ʱ��

	int reply_out_set(CByteArray* inbyte);//��Ӧ�������
	int reply_in_set(CByteArray* inbyte);//��Ӧ�ڻ�����
	int reply_air_status(CByteArray* inbyte);//��Ӧ��������״̬
	int reply_test_status(CByteArray* inbyte);
	int reply_out_para(CByteArray* inbyte);//��Ӧ������в���
	int reply_in_para(CByteArray* inbyte);//��Ӧ�ڻ����в���
	int reply_comp_time(CByteArray* inbyte);//��Ӧ��ѹ�����ۼ�����ʱ��

	int reply_mofify_out_para(CByteArray* inbyte);	//��Ӧ�޸�������ò���

	int getcommdata(CByteArray* inbyte);	//�Ӵ��ڵõ����ݲ�У�飬���ع��ܺţ�����0�յ����ݲ���ȷ
	void set_comm();			//���ô���
	air airlist[1];//�������
	int airnum;		//��������
	int queryopen;	//��ʱ��ѯ���ر�־
	int queryAirNo;	//Ҫ��ǰ��ѯ�Ļ����
	int queryFunNo; //��ѯ�Ĺ��ܺ�
	int sendcmdflag;//�����ѯ��6��7��8���������ѯ���
	int queryAirNo1;//���浱ǰ��ѯ�Ļ����
	int queryFunNo1; //�����ѯ�Ĺ��ܺ�
	int querySAirNo;	//Ҫ��ǰ��ѯ�Ĵӻ������

	int m_errorcount;//����һ������֮��Ĵ������
	int m_commNo;	//���ں�
	int m_commband;	//������
	int m_startflag;//��ʼ����־
	int m_connectflag;	//���ӱ�־
	
	inair m_inair;
	int m_select[48];

	int m_maskflag[48];	//��������11
	//�����������
	CByteArray outbuf;	
	COleVariant varOutput; 
	UINT crc;
	int temp;

	//�ļ���¼
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
