// air.h: interface for the air class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIR_H__77FA88E1_0E3D_4C13_AEC8_AB32CD127472__INCLUDED_)
#define AFX_AIR_H__77FA88E1_0E3D_4C13_AEC8_AB32CD127472__INCLUDED_

#if _MSC_VER > 1000
#pragma once 
#endif // _MSC_VER > 1000

float caldec(BYTE temp, BYTE temp1, int hiflag); //计算小数
float caldec_dlt(unsigned char temp, unsigned char temp1, int hifag);

//室内机结构
struct inair {
	//MDS从机基本参数
	int s_out_version;				    //外机程序版本					
	int address;					//机组地址     最大32台
	int s_air_type2;					//机组类型  0--单冷  1--热泵 
	int air_hp;						//能力
	int s_air_valve_ini;				//阀的初始开度

//状态参数
	int s_runmode;					//运行模式  0--停机 1--制冷 2--制热 3--自动
								//			4--送风 5--除湿 6--除霜 7--调试

	int s_oil_reclaim_run;			//0--油回收停止 1--油回收运行
	int s_oil_blance_run;			//0--油平衡停止 1--油平衡运行

	int s_windmotor1;				//风机1  0--停 1--低速 2--中速 3--高速
	int s_windmotor2;				//风机2  0--停 1--低速 2--中速 3--高速	
	int s_windmotor3;				//风机3  0--停 1--低速 2--中速 3--高速

	//手动控制风机用变量		
	int s_windmotor11;				//风机1  0--停 1--低速 2--中速 3--高速
	int s_windmotor21;				//风机2  0--停 1--低速 2--中速 3--高速	
	int s_windmotor31;				//风机3  0--停 1--低速 2--中速 3--高速

	int s_compre[6];				//压缩机1状态 0--关 1--开
//		int s_compre2;					//压缩机2状态 0--关 1--开
//		int s_compre3;					//压缩机3状态 0--关 1--开
//		int s_compre4;					//压缩机4状态 0--关 1--开
//		int s_compre5;					//压缩机5状态 0--关 1--开
//		int s_compre6;					//压缩机6状态 0--关 1--开

	int s_fourvalve1;				//四通阀1状态 0--关 1--开
	int s_fourvalve2;				//四通阀2状态 0--关 1--开

	int s_ele_valve0;				//0#电磁阀状态  0--关  1--开
	int s_ele_valve1;				//1#电磁阀状态  0--关  1--开
	int s_ahot;						//辅热输出

	int s_ele_distension_valve1;	//电磁膨胀阀1开度
	int s_ele_distension_valve2;	//电磁膨胀阀2开度
	int s_ele_distension_valve3;	//电磁膨胀阀3开度
	int s_ele_distension_valve4;	//电磁膨胀阀4开度
	//暂时使用数据
	int s_ele_distension_valve11;	//电磁膨胀阀1开度
	int s_ele_distension_valve21;	//电磁膨胀阀2开度
	int s_ele_distension_valve31;	//电磁膨胀阀3开度
	int s_ele_distension_valve41;	//电磁膨胀阀4开度
	//.............
	float s_total_needed_HP;			//总能力需求(单位HP)
	float s_total_needed_HP1;

	float s_tp1;				//排气温度
	float s_tp2;			//环境温度
	float s_tp3;				//回气温度

	float s_tp4;				//1#进盘温度
	float s_tp5;				//1#中盘温度
	float s_tp6;				//1#出盘温度

	float s_tp7;				//2#进盘温度
	float s_tp8;				//2#中盘温度
	float s_tp9;				//2#出盘温度

	float s_tp10;				//3#进盘温度
	float s_tp11;				//3#中盘温度
	float s_tp12;				//3#出盘温度

	float s_highpre;				//高压
	float s_highpre2;
	float s_lowpre;					//低压
	float s_lowpre2;
	float s_ele;
	float s_ele2;
	int s_exv1_216;
	int s_exv2_216;
	int s_exv3_216;
	int s_exv4_216;
	int s_exv5_216;
	int s_exv6_216;

	float s_factsuperhot;			//实际过热度

	float s_inmidpantp;				//内机中盘平均温度
	int s_targetsuperhot;			//目标过热度
	int s_targetsupercool;			//HIC回路目标过冷度

	int s_error[40];				//故障

	int s_delfrost_check_start_tp;	//除霜检测开始温度(-3~3℃),带符号表示
	int s_delfrost_set_tp;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	int s_delfrost_exit_tp;			//除霜结束温度  (10~50℃	默认15℃)
	int s_delfrost_intertime;		//除霜间隔时间  (0~90min,  默认45min)
	int s_delfrost_runtime;			//除霜运行时间  (5~25min,  默认10min)

	int s_delnoise_delaytime;		//降噪延迟时间(3~9,默认6)

	int s_movefac1;					//动作系数1
	int s_movefac2;					//动作系数2
	int  s_out_byte22;
	int  s_out_byte49;
	int s_p1;						//TscA1
	int s_p2;						//TscA2
	int s_p3;						//TscT1
	int s_p4;						//TscT2
	int s_p5;						//TscT3
	int s_p6;						//制热能力限制倍数
	int s_p7;						//制冷能力衰减系数
	int s_p8;						//连管参数3
	int s_p9;						//目标过热度
	int s_ev1time;					//热气旁通阀打开时间

	int s_delfrost_check_start_tp1;	//除霜检测开始温度(-3~3℃),带符号表示
	int s_delfrost_set_tp1;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	int s_delfrost_exit_tp1;			//除霜结束温度  (10~50℃	默认15℃)
	int s_delfrost_intertime1;		//除霜间隔时间  (0~90min,  默认45min)
	int s_delfrost_runtime1;			//除霜运行时间  (5~25min,  默认10min)

	int s_delnoise_delaytime1;		//降噪延迟时间(3~9,默认6)

	int s_targetsuperhot1;			//目标过热度
	int s_movefac11;					//动作系数1
	int s_movefac21;					//动作系数2
	int  s_out_byte221;
	int  s_out_byte491;
	int s_p11;						//TscA1
	int s_p21;						//TscA2
	int s_p31;						//TscT1
	int s_p41;						//TscT2
	int s_p51;						//TscT3
	int s_p61;						//制热能力限制倍数
	int s_p71;						//制冷能力衰减系数
	int s_p81;						//连管参数3
	int s_p91;						//目标过热度
	int s_ev1time1;					//热气旁通阀打开时间
	//压缩机累计运行时间
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
//空调机组类
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
	unsigned int BLDC_speed2; //系统2风机转速
	unsigned int BLDC_speed1; //系统1风机转速
	float hpre2; //高压2
	float hpre1; //高压1

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
	void reply_out_set(CByteArray* inbyte);		//响应外机配置
	void reply_in_set(CByteArray* inbyte);		//响应内机配置
	void reply_air_status(CByteArray* inbyte); //响应机组运行状态
	void reply_out_para(CByteArray* inbyte);   //响应外机运行参数
	void reply_in_para(CByteArray* inbyte);    //响应内机运行参数
	void reply_comp_time(CByteArray* inbyte);	//响应读压缩机状态

	void modify_out_para(CByteArray* outbyte);//修改外机配置参数
	void modify_specvalve_para(CByteArray* outbyte);
	void modify_out_para1();//修改成功后改变给参数副给修改后的值

//MDS空调基本参数
	int out_version;				//外机程序版本		
	int out_version_end;				//外机程序版本
	int address;					//机组地址     最大32台
	int air_type1;					//机组类型  0--MDS-A 1--MDS--B
	int air_type2;					//机组类型  0--单冷  1--热泵
	int air_type21;
	int s_remote_open;//远程开关机连锁
	int s_remote_open1;
	int ele_auto_open;//来电自启
	int ele_auto_open1;
	int s_liuliang;//定流量水系统
	int s_liuliang1;
	int watertemp;//常水温 低水温
	int watertemp1;
	int putonorhot;//普通 热回收
	int putonorhot1;
	int in_num;						//内机数量  
	int air_hp;						//能力
	int air_valve_ini;				//阀的初始开度
	int air_valve_ini1;
	int slave_ini;					//主机查询从机初始化完成

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
//副板数据
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
//特殊用途变量		
	int in_group;				//内机组 用于内机分组查询时用，不同于内机里面的分组号
									//0:(内机数 1--18 时)  1:(19~36) 3:(37~48)
									//初始化完成后用查询得来的数据计算此变量值
	BYTE in_groupquery;				//用于查询时作标记用
//线控器辅助设置（风速、摆风、锁定、电加热、定时、开关）
	int i_ctl_open;						//线控器开关 0--关机 1--开机
	int i_ctl_workmode;
	int i_ctl_lock;						//锁定内机   0--解除 1--锁定
	int i_ctl_hand_defrost;				//手动除霜	 0--禁止 1--允许
	int i_ctl_ass_hot;					//辅助加热   0--禁止 1--允许
	int i_ctl_sleep;					//睡眠		 0--禁止 1--允许
	int i_ctl_wind;						//摆风		 0--禁止 1--允许
	int i_ctl_wind_speed;				//风速		 0--低速 1--中速 2--高速 3--自动
	int i_ctl_coolsetin;				//制冷进水设置
	int i_ctl_heatsetin;				//制热进水设置

	int i_workmode;					//内机运行模式 0--停机 1--制冷 2--制热 3--自动 4--送风 5-除湿 6--除霜 7--调试
	int i_ele_hot;						//电加热	 0--关 1--开
	int i_pump;							//水泵		 0--关 1--开
	int i_wind;							//摆风		 0--关 1--开
	int i_wind_speed;					//风速		 0--停止 1--低速 2--中速 3--高速

	int i_pump_error;					//水泵故障
	int i_mode_error;					//模式冲突
	int i_memory_error;					//存储器故障
	int i_timechip_error;				//线控器时钟芯片故障
	int i_com_error;					//线控器和内机通讯故障	 0--无 1--有


//状态参数
	int s_runmode;					//运行模式  0--停机 1--制冷 2--制热 3--自动
								//			4--送风 5--除湿 6--除霜 7--调试

	int s_oil_reclaim_run;			//0--油回收停止 1--油回收运行
	int s_oil_blance_run;			//0--油平衡停止 1--油平衡运行

	int s_windmotor1;				//风机1  0--停 1--低速 2--中速 3--高速
	int s_windmotor2;				//风机2  0--停 1--低速 2--中速 3--高速	
	int s_windmotor3;				//风机3  0--停 1--低速 2--中速 3--高速

	//手动设置能力
	int s_sethp;
	int s_sethp1;
	//手动控制风机用变量		
	int s_windmotor11;				//风机1  0--停 1--低速 2--中速 3--高速
	int s_windmotor12;
	int s_windmotor21;				//风机2  0--停 1--低速 2--中速 3--高速	
	int s_windmotor22;
	//风机3  0--停 1--低速 2--中速 3--高速
	int s_f_windmotor11;				//风机1  0--停 1--低速 2--中速 3--高速
	int s_f_windmotor12;
	int s_f_windmotor21;				//风机2  0--停 1--低速 2--中速 3--高速	
	int s_f_windmotor22;

	int s_ele_valve0;				//0#电磁阀状态  0--关  1--开
	int s_ele_valve1;				//1#电磁阀状态  0--关  1--开
	//手动电磁阀用变量
	int s_ele_valve01;				//0#电磁阀状态  0--关  1--开
	int s_ele_valve11;				//0#电磁阀状态  0--关  1--开

	int s_compre[6];				//压缩机1状态 0--关 1--开
	int s_compre1[4];				//压缩机1状态 0--关 1--开
	int s_f_compre1[4];				//压缩机1状态 0--关 1--开
//		int s_compre2;					//压缩机2状态 0--关 1--开
//		int s_compre3;					//压缩机3状态 0--关 1--开
//		int s_compre4;					//压缩机4状态 0--关 1--开
//		int s_compre5;					//压缩机3状态 0--关 1--开
//		int s_compre6;					//压缩机4状态 0--关 1--开

	int s_fourvalve1;				//四通阀1状态 0--关 1--开
	int s_fourvalve11;				//修改四通阀1状态用 0--关 1--开

	int s_f_fourvalve21;				//四通阀1状态 0--关 1--开//副板
	int s_f_fourvalve11;				//修改四通阀1状态用 0--关 1--开

	int s_fourvalve2 ;				//四通阀2状态 0--关 1--开
	int s_fourvalve21;				//修改四通阀1状态用 0--关 1--开

	int s_fourvalve3 ;				//四通阀3状态 0--关 1--开
	int s_fourvalve31 ;
	int s_fourvalve4 ;				//四通阀4状态 0--关 1--开
	int s_fourvalve41 ;

	int s_fan_fre1;//风机1频率
	int s_fan_fre2;//风机2频率
	int s_fan_fre3;//风机3频率
	int s_fan_fre4;//风机4频率

	int s_comp_fre1;//压缩机1频率
	int s_comp_fre2;//压缩机2频率
	int s_comp_fre3;//压缩机3频率
	int s_comp_fre4;//压缩机4频率

	int s_pumpstate;				//水泵输出
	int s_ahot;						//辅热输出
	int s_ehot;						//电加热输出

	int s_ele_distension_valve1;	//电磁膨胀阀1开度
	int s_ele_distension_valve2;	//电磁膨胀阀2开度
	int s_ele_distension_valve3;	//电磁膨胀阀3开度
	int s_ele_distension_valve4;	//电磁膨胀阀4开度
	//暂时使用数据
	int s_ele_distension_valve11;	//电磁膨胀阀1开度
	int s_ele_distension_valve21;	//电磁膨胀阀2开度
	int s_ele_distension_valve31;	//电磁膨胀阀3开度
	int s_ele_distension_valve41;	//电磁膨胀阀4开度

	int s_f_ele_distension_valve11;	//电磁膨胀阀1开度
	int s_f_ele_distension_valve21;	//电磁膨胀阀2开度
	int s_f_ele_distension_valve31;	//电磁膨胀阀3开度
	int s_f_ele_distension_valve41;	//电磁膨胀阀4开度

	//.............
	float s_total_needed_HP;			//总能力需求(单位HP)
	float s_total_needed_HP1;
	int s_datacompre_PWM;			//数码压缩机PWM输出百分比

	float s_tp1;				//排气温度
	float s_tp2;			//环境温度
	float s_tp3;				//回气温度

	float s_tp4;				//1#进盘温度
	float s_tp5;				//1#中盘温度
	float s_tp6;				//1#出盘温度

	float s_tp7;				//2#进盘温度
	float s_tp8;				//2#中盘温度
	float s_tp9;				//2#出盘温度

	float s_tp10;				//3#进盘温度
	float s_tp11;				//3#中盘温度
	float s_tp12;				//3#出盘温度

	float s_highpre;				//低压2
	float s_highpre2;
	float s_lowpre;					//低压
	float s_lowpre2;

	float s_gaoya1;					//低压
	float s_gaoya2;

	float s_ele;//	电流1(CT1)
	float s_ele2;
	float s_ele3;

	int s_fan1_real;//风机1实际频率
	int s_fan2_real;
	int s_fan3_real;
	int s_fan4_real;

	int s_comp1_real;//压缩机1实际频率
	int s_comp2_real;
	int s_comp3_real;
	int s_comp4_real;

	int s_exv1_216;
	int s_exv2_216;
	int s_exv3_216;
	int s_exv4_216;
	int s_exv5_216;
	int s_exv6_216;
	//暂时使用数据
	int s_exv1_2161;
	int s_exv2_2161;
	int s_exv3_2161;
	int s_exv4_2161;
	int s_exv5_2161;
	int s_exv6_2161;

	float s_factsuperhot;			//实际过热度
	float s_factsuperhot3;			//实际过热度
	float s_factsuperhot4;			//实际过热度
	float s_inmidpantp;				//内机中盘平均温度
	int s_targetsuperhot;			//目标过热度
	int s_targetsupercool;			//HIC回路目标过冷度

	int com_error[16];				//内机通讯故障	
	int s_error[40];				//故障

	int s_delfrost_check_start_tp;	//除霜检测开始温度(-3~3℃),带符号表示
	int s_delfrost_set_tp;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	int s_delfrost_exit_tp;			//除霜结束温度  (10~50℃	默认15℃)
	int s_delfrost_intertime;		//除霜间隔时间  (0~90min,  默认45min)
	int s_delfrost_runtime;			//除霜运行时间  (5~25min,  默认10min)

	int s_delnoise_delaytime;		//降噪延迟时间(3~9,默认6)

	int s_antifreeze;				//防冻温度
	int s_winterantif;				//冬季防冻温度

	int s_movefac1;					//动作系数1
	int s_movefac2;					//动作系数2
	int  s_out_byte22;
	int  s_out_byte49;
	int s_p1;						//TscA1
	int s_p2;						//TscA2
	int s_p3;						//TscT1
	int s_p4;						//TscT2
	int s_p5;						//TscT3
	int s_p6;						//制热能力限制倍数
	int s_p7;						//制冷能力衰减系数
	int s_p8;						//连管参数3
	int s_p9;						//目标过热度

	int s_delfrost_check_start_tp1;	//除霜检测开始温度(-3~3℃),带符号表示
	int s_delfrost_set_tp1;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	int s_delfrost_exit_tp1;			//除霜结束温度  (10~50℃	默认15℃)
	int s_delfrost_intertime1;		//除霜间隔时间  (0~90min,  默认45min)
	int s_delfrost_runtime1;			//除霜运行时间  (5~25min,  默认10min)

	int s_delnoise_delaytime1;		//降噪延迟时间(3~9,默认6)

	int s_antifreeze1;				//防冻温度
	int s_winterantif1;				//冬季防冻温度

	int s_targetsuperhot1;			//目标过热度
	int s_movefac11;					//动作系数1
	int s_movefac21;					//动作系数2
	int  s_out_byte221;
	int  s_out_byte491;

	int s_p11;						//TscA1
	int s_p21;						//TscA2
	int s_p31;						//TscT1
	int s_p41;						//TscT2
	int s_p51;						//TscT3
	int s_p61;						//制热能力限制倍数
	int s_p71;						//制冷能力衰减系数
	int s_p81;						//连管参数3
	int s_p91;						//目标过热度


	int s_wenshuifa;//温水阀控制周期
//		int s_hotwaterarg;//热水水温补偿参数
	int s_fuluobjgrd;//辅路目标过热度
	int s_hotwatercontrol;//热水温差控制/模糊控制（0~1，实际值）
	int s_hotwatercontrol1;
	int s_coolandhotrun;//制冷+热水运行状态选择（0~2，实际值）
	int s_coolandhotrun1;
	int s_hotandhotrun;//制热+热水运行状态选择（0~1，实际值）
	int s_hotandhotrun1;
	int s_singledoublebox;//单水箱/双水箱（0~1，实际值）
	int s_singledoublebox1;
	int s_putongslavenum;//普通从机台数（0~15，实际值）
	int s_putongslavenum1;

	inair indoor_air[16];			//室内机
//外机时间
	int out_week;
	int out_hour;
	int out_minute;
	int out_sencond;
	//压缩机累计运行时间
	BYTE data_13[18];

	int f_s_runmode;
	int f_s_windmotor1;				//风机1  0--停 1--低速 2--中速 3--高速
	int f_s_windmotor2;				//风机2  0--停 1--低速 2--中速 3--高速	
	int f_s_windmotor3;				//风机3  0--停 1--低速 2--中速 3--高速
	int f_sr_windmotor1;				//风机1  0--停 1--低速 2--中速 3--高速
	int f_sr_windmotor2;
	int f_s_fourvalve1;
	int f_s_fourvalve2;
	int f_s_compre[6];
	int f_s_pumpstate3;
	int f_s_pumpstate;				//水泵输出
	int f_s_ahot;						//辅热输出
	int f_s_ehot;						//电加热输出
	int f_s_ele_valve1;
	int f_s_pumpstate2;
	int f_int_cool_fan;
	int f_chvalve;
	int f_s_ele_valve0;
	int f_s_fourvalve4;
	int f_s_ele_distension_valve1;	//电磁膨胀阀1开度
	int f_s_ele_distension_valve2;	//电磁膨胀阀2开度
	int f_s_ele_distension_valve3;	//电磁膨胀阀3开度
	int f_s_ele_distension_valve4;	//电磁膨胀阀4开度
	float f_s_tp1;				//排气温度
	float f_s_tp2;			//环境温度
	float f_s_tp3;				//回气温度
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
	float f_s_highpre;				//高压
	float f_s_lowpre;					//低压
	float f_s_gaoya;				//高压
	float f_s_gaoya2;					//gaoya2
	float f_s_factsuperhot;
	float f_s_factsuperhot2;
	int f_s_targetsuperhot;
	float f_s_total_needed_HP;
	int f_s_error[56];
	float f_s_ele1;//电流1
	float f_s_ele2;//电流2

private:


};

#endif // !defined(AFX_AIR_H__77FA88E1_0E3D_4C13_AEC8_AB32CD127472__INCLUDED_)
