// air.h: interface for the air class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIR_H__77FA88E1_0E3D_4C13_AEC8_AB32CD127472__INCLUDED_)
#define AFX_AIR_H__77FA88E1_0E3D_4C13_AEC8_AB32CD127472__INCLUDED_

#if _MSC_VER > 1000
#pragma once 
#endif // _MSC_VER > 1000

float caldec(BYTE temp, BYTE temp1, int hiflag); //����С��
float caldec_dlt(unsigned char temp, unsigned char temp1, int hifag);

//���ڻ��ṹ
struct inair {
	//MDS�ӻ���������
	int s_out_version;				    //�������汾					
	int address;					//�����ַ     ���32̨
	int s_air_type2;					//��������  0--����  1--�ȱ� 
	int air_hp;						//����
	int s_air_valve_ini;				//���ĳ�ʼ����

//״̬����
	int s_runmode;					//����ģʽ  0--ͣ�� 1--���� 2--���� 3--�Զ�
								//			4--�ͷ� 5--��ʪ 6--��˪ 7--����

	int s_oil_reclaim_run;			//0--�ͻ���ֹͣ 1--�ͻ�������
	int s_oil_blance_run;			//0--��ƽ��ֹͣ 1--��ƽ������

	int s_windmotor1;				//���1  0--ͣ 1--���� 2--���� 3--����
	int s_windmotor2;				//���2  0--ͣ 1--���� 2--���� 3--����	
	int s_windmotor3;				//���3  0--ͣ 1--���� 2--���� 3--����

	//�ֶ����Ʒ���ñ���		
	int s_windmotor11;				//���1  0--ͣ 1--���� 2--���� 3--����
	int s_windmotor21;				//���2  0--ͣ 1--���� 2--���� 3--����	
	int s_windmotor31;				//���3  0--ͣ 1--���� 2--���� 3--����

	int s_compre[6];				//ѹ����1״̬ 0--�� 1--��
//		int s_compre2;					//ѹ����2״̬ 0--�� 1--��
//		int s_compre3;					//ѹ����3״̬ 0--�� 1--��
//		int s_compre4;					//ѹ����4״̬ 0--�� 1--��
//		int s_compre5;					//ѹ����5״̬ 0--�� 1--��
//		int s_compre6;					//ѹ����6״̬ 0--�� 1--��

	int s_fourvalve1;				//��ͨ��1״̬ 0--�� 1--��
	int s_fourvalve2;				//��ͨ��2״̬ 0--�� 1--��

	int s_ele_valve0;				//0#��ŷ�״̬  0--��  1--��
	int s_ele_valve1;				//1#��ŷ�״̬  0--��  1--��
	int s_ahot;						//�������

	int s_ele_distension_valve1;	//������ͷ�1����
	int s_ele_distension_valve2;	//������ͷ�2����
	int s_ele_distension_valve3;	//������ͷ�3����
	int s_ele_distension_valve4;	//������ͷ�4����
	//��ʱʹ������
	int s_ele_distension_valve11;	//������ͷ�1����
	int s_ele_distension_valve21;	//������ͷ�2����
	int s_ele_distension_valve31;	//������ͷ�3����
	int s_ele_distension_valve41;	//������ͷ�4����
	//.............
	float s_total_needed_HP;			//����������(��λHP)
	float s_total_needed_HP1;

	float s_tp1;				//�����¶�
	float s_tp2;			//�����¶�
	float s_tp3;				//�����¶�

	float s_tp4;				//1#�����¶�
	float s_tp5;				//1#�����¶�
	float s_tp6;				//1#�����¶�

	float s_tp7;				//2#�����¶�
	float s_tp8;				//2#�����¶�
	float s_tp9;				//2#�����¶�

	float s_tp10;				//3#�����¶�
	float s_tp11;				//3#�����¶�
	float s_tp12;				//3#�����¶�

	float s_highpre;				//��ѹ
	float s_highpre2;
	float s_lowpre;					//��ѹ
	float s_lowpre2;
	float s_ele;
	float s_ele2;
	int s_exv1_216;
	int s_exv2_216;
	int s_exv3_216;
	int s_exv4_216;
	int s_exv5_216;
	int s_exv6_216;

	float s_factsuperhot;			//ʵ�ʹ��ȶ�

	float s_inmidpantp;				//�ڻ�����ƽ���¶�
	int s_targetsuperhot;			//Ŀ����ȶ�
	int s_targetsupercool;			//HIC��·Ŀ������

	int s_error[40];				//����

	int s_delfrost_check_start_tp;	//��˪��⿪ʼ�¶�(-3~3��),�����ű�ʾ
	int s_delfrost_set_tp;			//��˪�¶�����  ��Χ0~-7��� Ĭ��-5�� �����ű�ʾ
	int s_delfrost_exit_tp;			//��˪�����¶�  (10~50��	Ĭ��15��)
	int s_delfrost_intertime;		//��˪���ʱ��  (0~90min,  Ĭ��45min)
	int s_delfrost_runtime;			//��˪����ʱ��  (5~25min,  Ĭ��10min)

	int s_delnoise_delaytime;		//�����ӳ�ʱ��(3~9,Ĭ��6)

	int s_movefac1;					//����ϵ��1
	int s_movefac2;					//����ϵ��2
	int  s_out_byte22;
	int  s_out_byte49;
	int s_p1;						//TscA1
	int s_p2;						//TscA2
	int s_p3;						//TscT1
	int s_p4;						//TscT2
	int s_p5;						//TscT3
	int s_p6;						//�����������Ʊ���
	int s_p7;						//��������˥��ϵ��
	int s_p8;						//���ܲ���3
	int s_p9;						//Ŀ����ȶ�
	int s_ev1time;					//������ͨ����ʱ��

	int s_delfrost_check_start_tp1;	//��˪��⿪ʼ�¶�(-3~3��),�����ű�ʾ
	int s_delfrost_set_tp1;			//��˪�¶�����  ��Χ0~-7��� Ĭ��-5�� �����ű�ʾ
	int s_delfrost_exit_tp1;			//��˪�����¶�  (10~50��	Ĭ��15��)
	int s_delfrost_intertime1;		//��˪���ʱ��  (0~90min,  Ĭ��45min)
	int s_delfrost_runtime1;			//��˪����ʱ��  (5~25min,  Ĭ��10min)

	int s_delnoise_delaytime1;		//�����ӳ�ʱ��(3~9,Ĭ��6)

	int s_targetsuperhot1;			//Ŀ����ȶ�
	int s_movefac11;					//����ϵ��1
	int s_movefac21;					//����ϵ��2
	int  s_out_byte221;
	int  s_out_byte491;
	int s_p11;						//TscA1
	int s_p21;						//TscA2
	int s_p31;						//TscT1
	int s_p41;						//TscT2
	int s_p51;						//TscT3
	int s_p61;						//�����������Ʊ���
	int s_p71;						//��������˥��ϵ��
	int s_p81;						//���ܲ���3
	int s_p91;						//Ŀ����ȶ�
	int s_ev1time1;					//������ͨ����ʱ��
	//ѹ�����ۼ�����ʱ��
	BYTE data_13[18];
public:
	unsigned int water_exv_step;
	unsigned int S_BLDC_speed2;
	unsigned int S_BLDC_speed1;
	float s_hpre2;
	float s_hpre1;
	int exs_err[16];
	int s_winter_ant;
	int s_cool_ant;
	float s_tp14;
	float s_tp13;
	int s_ele_valve3;
	int s_ele_valve2;
	int s_fourvalve4;
	int s_fourvalve3;
	unsigned char cool_media_s;
	int low_type_s;
	float s_factsuperhot2;
	int s_wenshuifa;
	int s_hotwaterarg;
	int s_hotwatercontrol;
	int s_coolandhotrun;
	int s_hotandhotrun;
	int s_singledoublebox;
	int s_putongslavenum;
	int s_putongslavenum1;
	int s_putongorhot;
};
//�յ�������
class air
{
public:
	int water_level5;
	int water_level4;
	int water_level3;
	int water_level2;
	int water_level1;
	int wadd_pump;
	int water_vm4;
	int water_vm3;
	int water_vm2;
	int water_vm1;
	int hot_eheat;
	int m_hotset;
	int m_heatset;
	//	int heatset();
	int coolset;
	float s_tp21;
	float s_tp20;
	unsigned int water_step;
	//unsigned int wexv_setp;
	float s_hpre1;
	unsigned int BLDC_speed2; //ϵͳ2���ת��
	unsigned int BLDC_speed1; //ϵͳ1���ת��
	float hpre2; //��ѹ2
	float hpre1; //��ѹ1

	void reply_slave_para(CByteArray* inbyte);
	void DataToTemp();
	void modify_out_para_24(CByteArray* outbyte);
	void reply_test_status(CByteArray* inbyte);
	void reply_master_status(CByteArray* inbyte);
	int ex_err[16];
	void modify_out_para_s(int slave_no, CByteArray* outbyte);
	int unit_no;
	int unit_on;
	float s_tp14;
	float s_tp13;
	int s_ele_valve3;
	int s_ele_valve2;
	int s_pump2state;
	int m_ctrl_hotset;
	unsigned char cool_media_type;
	unsigned char cool_media_type1;
	int low_type;
	float s_factsuperhot2;
	void modify_sout_para1();
	air();
	virtual ~air();
	void reply_out_set(CByteArray* inbyte);		//��Ӧ�������
	void reply_in_set(CByteArray* inbyte);		//��Ӧ�ڻ�����
	void reply_air_status(CByteArray* inbyte); //��Ӧ��������״̬
	void reply_out_para(CByteArray* inbyte);   //��Ӧ������в���
	void reply_in_para(CByteArray* inbyte);    //��Ӧ�ڻ����в���
	void reply_comp_time(CByteArray* inbyte);	//��Ӧ��ѹ����״̬

	void modify_out_para(CByteArray* outbyte);//�޸�������ò���
	void modify_specvalve_para(CByteArray* outbyte);
	void modify_out_para1();//�޸ĳɹ���ı�����������޸ĺ��ֵ

//MDS�յ���������
	int out_version;				//�������汾		
	int out_version_end;				//�������汾
	int address;					//�����ַ     ���32̨
	int air_type1;					//��������  0--MDS-A 1--MDS--B
	int air_type2;					//��������  0--����  1--�ȱ�
	int air_type21;
	int s_remote_open;//Զ�̿��ػ�����
	int s_remote_open1;
	int ele_auto_open;//��������
	int ele_auto_open1;
	int s_liuliang;//������ˮϵͳ
	int s_liuliang1;
	int watertemp;//��ˮ�� ��ˮ��
	int watertemp1;
	int putonorhot;//��ͨ �Ȼ���
	int putonorhot1;
	int in_num;						//�ڻ�����  
	int air_hp;						//����
	int air_valve_ini;				//���ĳ�ʼ����
	int air_valve_ini1;
	int slave_ini;					//������ѯ�ӻ���ʼ�����

	int sw11;
	int sw12;
	int sw13;
	int sw14;
	int sw15;
	int sw16;
	int sw17;
	int sw18;
	int sw11_f;
	int sw12_f;
	int sw13_f;
	int sw14_f;
	int sw15_f;
	int sw16_f;
	int sw17_f;
	int sw18_f;
	int DI1;
	int DI2;
	int DI3;
	int DI4;
	int DI5;
	int DI6;
	int DI7;
	int DI8;
	int DI9;
	int DI10;
	int DI11;
	int DI12;
	int DI13;
	int DI14;
	int DI15;
	int DI16;
	int DO1;
	int DO2;
	int DO3;
	int DO4;
	int DO5;
	int DO6;
	int DO7;
	int DO8;
	int DO9;
	int DO10;
	int DO11;
	int DO12;
	int DO13;
	int DO14;
	int DO15;
	int DO16;
	int DO17;
	int DO18;
	int DO19;
//��������
	int DIF1;
	int DIF2;
	int DIF3;
	int DIF4;
	int DIF5;
	int DIF6;
	int DIF7;
	int DIF8;
	int DIF9;
	int DIF10;
	int DIF11;
	int DIF12;
	int DIF13;
	int DIF14;
	int DIF15;
	int DIF16;
	int DOF1;
	int DOF2;
	int DOF3;
	int DOF4;
	int DOF5;
	int DOF6;
	int DOF7;
	int DOF8;
	int DOF9;
	int DOF10;
	int DOF11;
	int DOF12;
	int DOF13;
	int DOF14;
	int DOF15;
	int DOF16;
	int DOF17;
	int DOF18;
	int DOF19;


	int S_DO1;
	int S_DO2;
	int S_DO3;
	int S_DO4;
	int S_DO15;
	int S_DO13;
	int SF_DO1;
//������;����		
	int in_group;				//�ڻ��� �����ڻ������ѯʱ�ã���ͬ���ڻ�����ķ����
									//0:(�ڻ��� 1--18 ʱ)  1:(19~36) 3:(37~48)
									//��ʼ����ɺ��ò�ѯ���������ݼ���˱���ֵ
	BYTE in_groupquery;				//���ڲ�ѯʱ�������
//�߿����������ã����١��ڷ硢����������ȡ���ʱ�����أ�
	int i_ctl_open;						//�߿������� 0--�ػ� 1--����
	int i_ctl_workmode;
	int i_ctl_lock;						//�����ڻ�   0--��� 1--����
	int i_ctl_hand_defrost;				//�ֶ���˪	 0--��ֹ 1--����
	int i_ctl_ass_hot;					//��������   0--��ֹ 1--����
	int i_ctl_sleep;					//˯��		 0--��ֹ 1--����
	int i_ctl_wind;						//�ڷ�		 0--��ֹ 1--����
	int i_ctl_wind_speed;				//����		 0--���� 1--���� 2--���� 3--�Զ�
	int i_ctl_coolsetin;				//�����ˮ����
	int i_ctl_heatsetin;				//���Ƚ�ˮ����

	int i_workmode;					//�ڻ�����ģʽ 0--ͣ�� 1--���� 2--���� 3--�Զ� 4--�ͷ� 5-��ʪ 6--��˪ 7--����
	int i_ele_hot;						//�����	 0--�� 1--��
	int i_pump;							//ˮ��		 0--�� 1--��
	int i_wind;							//�ڷ�		 0--�� 1--��
	int i_wind_speed;					//����		 0--ֹͣ 1--���� 2--���� 3--����

	int i_pump_error;					//ˮ�ù���
	int i_mode_error;					//ģʽ��ͻ
	int i_memory_error;					//�洢������
	int i_timechip_error;				//�߿���ʱ��оƬ����
	int i_com_error;					//�߿������ڻ�ͨѶ����	 0--�� 1--��


//״̬����
	int s_runmode;					//����ģʽ  0--ͣ�� 1--���� 2--���� 3--�Զ�
								//			4--�ͷ� 5--��ʪ 6--��˪ 7--����

	int s_oil_reclaim_run;			//0--�ͻ���ֹͣ 1--�ͻ�������
	int s_oil_blance_run;			//0--��ƽ��ֹͣ 1--��ƽ������

	int s_windmotor1;				//���1  0--ͣ 1--���� 2--���� 3--����
	int s_windmotor2;				//���2  0--ͣ 1--���� 2--���� 3--����	
	int s_windmotor3;				//���3  0--ͣ 1--���� 2--���� 3--����

	//�ֶ���������
	int s_sethp;
	int s_sethp1;
	//�ֶ����Ʒ���ñ���		
	int s_windmotor11;				//���1  0--ͣ 1--���� 2--���� 3--����
	int s_windmotor12;
	int s_windmotor21;				//���2  0--ͣ 1--���� 2--���� 3--����	
	int s_windmotor22;
	//���3  0--ͣ 1--���� 2--���� 3--����
	int s_f_windmotor11;				//���1  0--ͣ 1--���� 2--���� 3--����
	int s_f_windmotor12;
	int s_f_windmotor21;				//���2  0--ͣ 1--���� 2--���� 3--����	
	int s_f_windmotor22;

	int s_ele_valve0;				//0#��ŷ�״̬  0--��  1--��
	int s_ele_valve1;				//1#��ŷ�״̬  0--��  1--��
	//�ֶ���ŷ��ñ���
	int s_ele_valve01;				//0#��ŷ�״̬  0--��  1--��
	int s_ele_valve11;				//0#��ŷ�״̬  0--��  1--��

	int s_compre[6];				//ѹ����1״̬ 0--�� 1--��
	int s_compre1[4];				//ѹ����1״̬ 0--�� 1--��
	int s_f_compre1[4];				//ѹ����1״̬ 0--�� 1--��
//		int s_compre2;					//ѹ����2״̬ 0--�� 1--��
//		int s_compre3;					//ѹ����3״̬ 0--�� 1--��
//		int s_compre4;					//ѹ����4״̬ 0--�� 1--��
//		int s_compre5;					//ѹ����3״̬ 0--�� 1--��
//		int s_compre6;					//ѹ����4״̬ 0--�� 1--��

	int s_fourvalve1;				//��ͨ��1״̬ 0--�� 1--��
	int s_fourvalve11;				//�޸���ͨ��1״̬�� 0--�� 1--��

	int s_f_fourvalve21;				//��ͨ��1״̬ 0--�� 1--��//����
	int s_f_fourvalve11;				//�޸���ͨ��1״̬�� 0--�� 1--��

	int s_fourvalve2 ;				//��ͨ��2״̬ 0--�� 1--��
	int s_fourvalve21;				//�޸���ͨ��1״̬�� 0--�� 1--��

	int s_fourvalve3 ;				//��ͨ��3״̬ 0--�� 1--��
	int s_fourvalve31 ;
	int s_fourvalve4 ;				//��ͨ��4״̬ 0--�� 1--��
	int s_fourvalve41 ;

	int s_fan_fre1;//���1Ƶ��
	int s_fan_fre2;//���2Ƶ��
	int s_fan_fre3;//���3Ƶ��
	int s_fan_fre4;//���4Ƶ��

	int s_comp_fre1;//ѹ����1Ƶ��
	int s_comp_fre2;//ѹ����2Ƶ��
	int s_comp_fre3;//ѹ����3Ƶ��
	int s_comp_fre4;//ѹ����4Ƶ��

	int s_pumpstate;				//ˮ�����
	int s_ahot;						//�������
	int s_ehot;						//��������

	int s_ele_distension_valve1;	//������ͷ�1����
	int s_ele_distension_valve2;	//������ͷ�2����
	int s_ele_distension_valve3;	//������ͷ�3����
	int s_ele_distension_valve4;	//������ͷ�4����
	//��ʱʹ������
	int s_ele_distension_valve11;	//������ͷ�1����
	int s_ele_distension_valve21;	//������ͷ�2����
	int s_ele_distension_valve31;	//������ͷ�3����
	int s_ele_distension_valve41;	//������ͷ�4����

	int s_f_ele_distension_valve11;	//������ͷ�1����
	int s_f_ele_distension_valve21;	//������ͷ�2����
	int s_f_ele_distension_valve31;	//������ͷ�3����
	int s_f_ele_distension_valve41;	//������ͷ�4����

	//.............
	float s_total_needed_HP;			//����������(��λHP)
	float s_total_needed_HP1;
	int s_datacompre_PWM;			//����ѹ����PWM����ٷֱ�

	float s_tp1;				//�����¶�
	float s_tp2;			//�����¶�
	float s_tp3;				//�����¶�

	float s_tp4;				//1#�����¶�
	float s_tp5;				//1#�����¶�
	float s_tp6;				//1#�����¶�

	float s_tp7;				//2#�����¶�
	float s_tp8;				//2#�����¶�
	float s_tp9;				//2#�����¶�

	float s_tp10;				//3#�����¶�
	float s_tp11;				//3#�����¶�
	float s_tp12;				//3#�����¶�

	float s_highpre;				//��ѹ2
	float s_highpre2;
	float s_lowpre;					//��ѹ
	float s_lowpre2;

	float s_gaoya1;					//��ѹ
	float s_gaoya2;

	float s_ele;//	����1(CT1)
	float s_ele2;
	float s_ele3;

	int s_fan1_real;//���1ʵ��Ƶ��
	int s_fan2_real;
	int s_fan3_real;
	int s_fan4_real;

	int s_comp1_real;//ѹ����1ʵ��Ƶ��
	int s_comp2_real;
	int s_comp3_real;
	int s_comp4_real;

	int s_exv1_216;
	int s_exv2_216;
	int s_exv3_216;
	int s_exv4_216;
	int s_exv5_216;
	int s_exv6_216;
	//��ʱʹ������
	int s_exv1_2161;
	int s_exv2_2161;
	int s_exv3_2161;
	int s_exv4_2161;
	int s_exv5_2161;
	int s_exv6_2161;

	float s_factsuperhot;			//ʵ�ʹ��ȶ�
	float s_factsuperhot3;			//ʵ�ʹ��ȶ�
	float s_factsuperhot4;			//ʵ�ʹ��ȶ�
	float s_inmidpantp;				//�ڻ�����ƽ���¶�
	int s_targetsuperhot;			//Ŀ����ȶ�
	int s_targetsupercool;			//HIC��·Ŀ������

	int com_error[16];				//�ڻ�ͨѶ����	
	int s_error[40];				//����

	int s_delfrost_check_start_tp;	//��˪��⿪ʼ�¶�(-3~3��),�����ű�ʾ
	int s_delfrost_set_tp;			//��˪�¶�����  ��Χ0~-7��� Ĭ��-5�� �����ű�ʾ
	int s_delfrost_exit_tp;			//��˪�����¶�  (10~50��	Ĭ��15��)
	int s_delfrost_intertime;		//��˪���ʱ��  (0~90min,  Ĭ��45min)
	int s_delfrost_runtime;			//��˪����ʱ��  (5~25min,  Ĭ��10min)

	int s_delnoise_delaytime;		//�����ӳ�ʱ��(3~9,Ĭ��6)

	int s_antifreeze;				//�����¶�
	int s_winterantif;				//���������¶�

	int s_movefac1;					//����ϵ��1
	int s_movefac2;					//����ϵ��2
	int  s_out_byte22;
	int  s_out_byte49;
	int s_p1;						//TscA1
	int s_p2;						//TscA2
	int s_p3;						//TscT1
	int s_p4;						//TscT2
	int s_p5;						//TscT3
	int s_p6;						//�����������Ʊ���
	int s_p7;						//��������˥��ϵ��
	int s_p8;						//���ܲ���3
	int s_p9;						//Ŀ����ȶ�

	int s_delfrost_check_start_tp1;	//��˪��⿪ʼ�¶�(-3~3��),�����ű�ʾ
	int s_delfrost_set_tp1;			//��˪�¶�����  ��Χ0~-7��� Ĭ��-5�� �����ű�ʾ
	int s_delfrost_exit_tp1;			//��˪�����¶�  (10~50��	Ĭ��15��)
	int s_delfrost_intertime1;		//��˪���ʱ��  (0~90min,  Ĭ��45min)
	int s_delfrost_runtime1;			//��˪����ʱ��  (5~25min,  Ĭ��10min)

	int s_delnoise_delaytime1;		//�����ӳ�ʱ��(3~9,Ĭ��6)

	int s_antifreeze1;				//�����¶�
	int s_winterantif1;				//���������¶�

	int s_targetsuperhot1;			//Ŀ����ȶ�
	int s_movefac11;					//����ϵ��1
	int s_movefac21;					//����ϵ��2
	int  s_out_byte221;
	int  s_out_byte491;

	int s_p11;						//TscA1
	int s_p21;						//TscA2
	int s_p31;						//TscT1
	int s_p41;						//TscT2
	int s_p51;						//TscT3
	int s_p61;						//�����������Ʊ���
	int s_p71;						//��������˥��ϵ��
	int s_p81;						//���ܲ���3
	int s_p91;						//Ŀ����ȶ�


	int s_wenshuifa;//��ˮ����������
//		int s_hotwaterarg;//��ˮˮ�²�������
	int s_fuluobjgrd;//��·Ŀ����ȶ�
	int s_hotwatercontrol;//��ˮ�²����/ģ�����ƣ�0~1��ʵ��ֵ��
	int s_hotwatercontrol1;
	int s_coolandhotrun;//����+��ˮ����״̬ѡ��0~2��ʵ��ֵ��
	int s_coolandhotrun1;
	int s_hotandhotrun;//����+��ˮ����״̬ѡ��0~1��ʵ��ֵ��
	int s_hotandhotrun1;
	int s_singledoublebox;//��ˮ��/˫ˮ�䣨0~1��ʵ��ֵ��
	int s_singledoublebox1;
	int s_putongslavenum;//��ͨ�ӻ�̨����0~15��ʵ��ֵ��
	int s_putongslavenum1;

	inair indoor_air[16];			//���ڻ�
//���ʱ��
	int out_week;
	int out_hour;
	int out_minute;
	int out_sencond;
	//ѹ�����ۼ�����ʱ��
	BYTE data_13[18];

	int f_s_runmode;
	int f_s_windmotor1;				//���1  0--ͣ 1--���� 2--���� 3--����
	int f_s_windmotor2;				//���2  0--ͣ 1--���� 2--���� 3--����	
	int f_s_windmotor3;				//���3  0--ͣ 1--���� 2--���� 3--����
	int f_sr_windmotor1;				//���1  0--ͣ 1--���� 2--���� 3--����
	int f_sr_windmotor2;
	int f_s_fourvalve1;
	int f_s_fourvalve2;
	int f_s_compre[6];
	int f_s_pumpstate3;
	int f_s_pumpstate;				//ˮ�����
	int f_s_ahot;						//�������
	int f_s_ehot;						//��������
	int f_s_ele_valve1;
	int f_s_pumpstate2;
	int f_int_cool_fan;
	int f_chvalve;
	int f_s_ele_valve0;
	int f_s_fourvalve4;
	int f_s_ele_distension_valve1;	//������ͷ�1����
	int f_s_ele_distension_valve2;	//������ͷ�2����
	int f_s_ele_distension_valve3;	//������ͷ�3����
	int f_s_ele_distension_valve4;	//������ͷ�4����
	float f_s_tp1;				//�����¶�
	float f_s_tp2;			//�����¶�
	float f_s_tp3;				//�����¶�
	float f_s_tp4;				
	float f_s_tp5;			
	float f_s_tp6;				
	float f_s_tp7;				
	float f_s_tp8;				
	float f_s_tp9;				
	float f_s_tp10;				
	float f_s_tp11;				
	float f_s_tp12;				
	float f_s_tp13;				//
	float f_s_tp14;				//
	float f_s_highpre;				//��ѹ
	float f_s_lowpre;					//��ѹ
	float f_s_gaoya;				//��ѹ
	float f_s_gaoya2;					//gaoya2
	float f_s_factsuperhot;
	float f_s_factsuperhot2;
	int f_s_targetsuperhot;
	float f_s_total_needed_HP;
	int f_s_error[56];
	float f_s_ele1;//����1
	float f_s_ele2;//����2

private:


};

#endif // !defined(AFX_AIR_H__77FA88E1_0E3D_4C13_AEC8_AB32CD127472__INCLUDED_)
