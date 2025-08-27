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

//�ڴ����������������
void CSlavedlg::showdata(int No)
{
	CString tempstr,str;
	float f;
	tempstr="MDS";
	//����
	int AHPstr[2][10]={{3,4,5,6,0,9,0,11,0,0},{3,4,5,6,0,8,0,10,0,0}};
	int BHPstr[2][11]={{8,10,12,15,18,20,22,24,26,28,30},{8,10,12,15,18,20,22,24,26,28,30}};
	if(pdoc->airlist[No].air_hp<0||pdoc->airlist[No].air_type1>10)//����ֹ���
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
	//��������  0--MDS-B 1--MDS--A
	if(pdoc->airlist[No].air_type1_s0==0)
		str.Format("B");
	else
		str.Format("A");
	tempstr+=str;
	//��������  1--����  0--�ȱ�
	if(pdoc->airlist[No].air_type2_s0==0)
		tempstr+="R";
	m_airtype1.SetWindowText(tempstr);

	
	//�������汾
	tempstr.Format("%.1f",(float)pdoc->airlist[No].out_version_s0/10);
	m_airversion.SetWindowText(tempstr);

	//���ų�ʼ����
	tempstr.Format("%d",pdoc->airlist[No].air_valve_ini_s0);
	m_hp.SetWindowText(tempstr);

//״̬����
	//����ģʽ  0--ͣ�� 1--���� 2--���� 3--�Զ�
	//			4--�ͷ� 5--��ʪ 6--��˪ 7--����
	CString runmode[8]={"ͣ��","����","����","�Զ�","�ͷ�","��ʪ","��˪","����"}; 
	if(pdoc->airlist[No].s_runmode_s0>=0&&pdoc->airlist[No].s_runmode_s0<=7)
	{
		m_runmode.SetWindowText(runmode[pdoc->airlist[No].s_runmode_s0]);
	}

	//0--�ͻ���ֹͣ 1--�ͻ�������
	if(pdoc->airlist[No].s_oil_reclaim_run_s0==0)
		tempstr.Format("ֹͣ");
	else
		tempstr.Format("����");
	m_oilre.SetWindowText(tempstr);
				
	//0--��ƽ��ֹͣ 1--��ƽ������
	if(pdoc->airlist[No].s_oil_blance_run_s0==0)
		tempstr.Format("ֹͣ");
	else
		tempstr.Format("����");
	m_oilblance.SetWindowText(tempstr);
	
	CString wind[4]={"ֹͣ","����","����","����"}; 
	//���1  0--ͣ 1--���� 2--���� 3--����
	if(pdoc->airlist[No].s_windmotor1_s0>=0&&pdoc->airlist[No].s_windmotor1_s0<=3)//��Ч�Լ��
	{
		m_fan1.SetWindowText(wind[pdoc->airlist[No].s_windmotor1_s0]);
	}
	//���2  0--ͣ 1--���� 2--���� 3--����
	if(pdoc->airlist[No].s_windmotor2_s0>=0&&pdoc->airlist[No].s_windmotor2_s0<=3)
	{
		m_fan2.SetWindowText(wind[pdoc->airlist[No].s_windmotor2]);
	}
	//���3  0--ͣ 1--���� 2--���� 3--����
	if(pdoc->airlist[No].s_windmotor3_s0>=0&&pdoc->airlist[No].s_windmotor3_s0<=3)
	{
		m_fan3.SetWindowText(wind[pdoc->airlist[No].s_windmotor3_s0]);
	}

	//0#��ŷ�״̬  0--��  1--��
	if(pdoc->airlist[No].s_ele_valve0_s0==0)
		tempstr.Format("ֹͣ");
	else
		tempstr.Format("����");
	m_elevalve0.SetWindowText(tempstr);

	//0#��ŷ�״̬  0--��  1--��
	if(pdoc->airlist[No].s_ele_valve1_s0==0)
		tempstr.Format("ֹͣ");
	else
		tempstr.Format("����");
	m_elevavle1.SetWindowText(tempstr);

	//ѹ����1״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_compre1_s0==0)
		tempstr.Format("�ر�");
	else
		tempstr.Format("��");
	m_comp1.SetWindowText(tempstr);

	//ѹ����2״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_compre2_s0==0)
	{
		tempstr.Format("�ر�");
	}
	else
	{
		tempstr.Format("��");
	}
	m_comp2.SetWindowText(tempstr);
	
	//ѹ����3״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_compre3_s0==0)
	{
		tempstr.Format("�ر�");
	}
	else
	{
		tempstr.Format("��");
	}
	m_comp3.SetWindowText(tempstr);


	//��ͨ��1״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_fourvalve1_s0==0)
		tempstr.Format("�ر�");
	else
		tempstr.Format("��");
	m_fourvalve1.SetWindowText(tempstr);

	//��ͨ��2״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_fourvalve2_s0==0)
		tempstr.Format("�ر�");
	else
		tempstr.Format("��");
	m_fourvalve2.SetWindowText(tempstr);

	//��ͨ��3״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_fourvalve3_s0==0)
		tempstr.Format("�ر�");
	else
		tempstr.Format("��");
	m_fourvalve3.SetWindowText(tempstr);

	//��ͨ��4״̬ 0--�� 1--��
	if(pdoc->airlist[No].s_fourvalve4_s0==0)
		tempstr.Format("�ر�");
	else
		tempstr.Format("��");
	m_fourvalve4.SetWindowText(tempstr);
	
	//������ͷ�1����
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve1_s0);
	m_eledisten1.SetWindowText(tempstr);
	//������ͷ�2����
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve2_s0);
	m_eledisten2.SetWindowText(tempstr);
	//������ͷ�3����
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve3_s0);
	m_eledisten3.SetWindowText(tempstr);
	//������ͷ�4����
	tempstr.Format("%d",pdoc->airlist[No].s_ele_distension_valve4_s0);
	m_eledisten4.SetWindowText(tempstr);

	//����������(��λHP)
	tempstr.Format("%.1fHP",pdoc->airlist[No].s_total_needed_HP_s0);
	m_totalneedhp.SetWindowText(tempstr);

	//����ѹ����PWM����ٷֱ�
	tempstr.Format("%d%%",pdoc->airlist[No].s_datacompre_PWM_s0);
	m_pwmout.SetWindowText(tempstr);
		
	//�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_outgas_tp_s0);
	m_outgas.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outgas_tp_s0>=150)
		m_outgas.SetWindowText("��·");
	if(pdoc->airlist[No].s_outgas_tp_s0<=5)
		m_outgas.SetWindowText("��·");

	//�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_environment_tp_s0);
	m_outdoortp.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_environment_tp_s0>=127)
		m_outdoortp.SetWindowText("��·");
	if(pdoc->airlist[No].s_environment_tp_s0<=-127)
		m_outdoortp.SetWindowText("��·");

	//�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_ingas_tp_s0);
	m_ingas.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_ingas_tp_s0>=127)
		m_ingas.SetWindowText("��·");
	if(pdoc->airlist[No].s_ingas_tp_s0<=-127)
		m_ingas.SetWindowText("��·");

	//1#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_inpan1_tp_s0);
	m_inpan1.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_inpan1_tp_s0>=127)
		m_inpan1.SetWindowText("��·");
	if(pdoc->airlist[No].s_inpan1_tp_s0<=-127)
		m_inpan1.SetWindowText("��·");
	//1#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_midpan1_tp_s0);
	m_midpan1.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_midpan1_tp_s0>=127)
		m_midpan1.SetWindowText("��·");
	if(pdoc->airlist[No].s_midpan1_tp_s0<=-127)
		m_midpan1.SetWindowText("��·");
	//1#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_outpan1_tp_s0);
	m_outpan1.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outpan1_tp_s0>=127)
		m_outpan1.SetWindowText("��·");
	if(pdoc->airlist[No].s_outpan1_tp_s0<=-127)
		m_outpan1.SetWindowText("��·");

	//2#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_inpan2_tp_s0);
	m_inpan2.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_inpan2_tp_s0>=127)
		m_inpan2.SetWindowText("��·");
	if(pdoc->airlist[No].s_inpan2_tp_s0<=-127)
		m_inpan2.SetWindowText("��·");
	//2#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_midpan2_tp_s0);
	m_midpan2.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_midpan2_tp_s0>=127)
		m_midpan2.SetWindowText("��·");
	if(pdoc->airlist[No].s_midpan2_tp_s0<=-127)
		m_midpan2.SetWindowText("��·");
	//2#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_outpan2_tp_s0);
	m_outpan2.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outpan2_tp_s0>=127)
		m_outpan2.SetWindowText("��·");
	if(pdoc->airlist[No].s_outpan2_tp_s0<=-127)
		m_outpan2.SetWindowText("��·");

	//3#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_inpan3_tp_s0);
	m_inpan3.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_inpan3_tp_s0>=127)
		m_inpan3.SetWindowText("��·");
	if(pdoc->airlist[No].s_inpan3_tp_s0<=-127)
		m_inpan3.SetWindowText("��·");
	//3#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_midpan3_tp_s0);
	m_midpan3.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_midpan3_tp_s0>=127)
		m_midpan3.SetWindowText("��·");
	if(pdoc->airlist[No].s_midpan3_tp_s0<=-127)
		m_midpan3.SetWindowText("��·");
	//3#�����¶�
	tempstr.Format("%.1f��",pdoc->airlist[No].s_outpan3_tp_s0);
	m_outpan3.SetWindowText(tempstr);
	if(pdoc->airlist[No].s_outpan3_tp_s0>=127)
		m_outpan3.SetWindowText("��·");
	if(pdoc->airlist[No].s_outpan3_tp_s0<=-127)
		m_outpan3.SetWindowText("��·");

	//��ѹ
	tempstr.Format("%.1fBar",pdoc->airlist[No].s_highpre_s0);
	m_highpre.SetWindowText(tempstr);

	//��ѹ
	tempstr.Format("%.1fBar",pdoc->airlist[No].s_lowpre_s0);
	m_lowpre.SetWindowText(tempstr);

	//��˪��⿪ʼ�¶�(-3~3��),�����ű�ʾ
	tempstr.Format("%d��",pdoc->airlist[No].s_delfrost_check_start_tp_s0);
	m_dfroststarttp.SetWindowText(tempstr);

	//��˪�¶�����  ��Χ0~-7��� Ĭ��-5�� �����ű�ʾ
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_set_tp_s0);
	m_dfrosttp.SetWindowText(tempstr);
	
	//��˪�����¶�  (10~50��	Ĭ��15��)
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_exit_tp_s0);
	m_dfrostendtp.SetWindowText(tempstr);
	
	//��˪���ʱ��  (0~90min,  Ĭ��45min)
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_intertime_s0);
	m_dfrostintertime.SetWindowText(tempstr);
	
	//��˪����ʱ��  (5~25min,  Ĭ��10min)
	tempstr.Format("%d",pdoc->airlist[No].s_delfrost_runtime_s0);
	m_dfrostruntime.SetWindowText(tempstr);
		
	//�����ӳ�ʱ��(3~9,Ĭ��6)
	tempstr.Format("%d",pdoc->airlist[No].s_delnoise_delaytime_s0);
	m_dnoisedelaytime.SetWindowText(tempstr);

	//ʵ�ʹ��ȶ�
	tempstr.Format("%.1f",pdoc->airlist[No].s_factsuperhot_s0);
	m_factshot.SetWindowText(tempstr);

	//Ŀ����ȶ�
	f=(float)pdoc->airlist[No].s_targetsuperhot_s0;
	f/=10;
	tempstr.Format("%.1f",f);
	m_targetshot.SetWindowText(tempstr);
	//HIC��·Ŀ������
/*	tempstr.Format("%d",pdoc->airlist[No].s_targetsupercool_s0);
	m_hicsupercool.SetWindowText(tempstr);*/
}

BOOL CSlavedlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString tempstr;
	tempstr.Format("(%d#���)  0#�ӻ�״̬",outairNo);
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
	if(nIDEvent==0)//������ʾ����
	{
		showdata(outairNo);
	}
	if(nIDEvent==1)//������ʾ����
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
	CString errorstr[15]={"����ѹ����1����","����ѹ����2����","����ѹ����3����","����ѹ����4����","��ѹ����","��ѹ����","̽ͷ����","ϵͳ����","�����¶ȹ���","�����ͨѶ����","��ͨ������","�����¶ȹ���/��","��������","���ȶȹ�С","��ýй¶"};
//	m_alarmlist.AddString("0#�ӻ������б�");
	for(i=0;i<15;i++)
	{
		if(pdoc->airlist[No].s_error_s0[i]==1)
		{
			if(i!=9)
				m_alarmlist.AddString(errorstr[i]);
		}
	}//����*/
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
