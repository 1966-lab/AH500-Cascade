// air.cpp: implementation of the air class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "air.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
air::air()
{
	int i, j;
	//MDS空调基本参数
	out_version = 0;				//外机程序版本		
	out_version_end = 0;				//外机程序版本	
	address = 0;					//机组地址     最大32台
	air_type1 = 1;					//机组类型  0--MDS-A 1--MDS--B
	air_type2 = 0;					//机组类型  0--单冷  1--热泵
	low_type = 0;
	in_num = 0;						//内机数量 
	air_valve_ini = 0;				//阀的初始开度
	air_hp = 0;						//能力
	slave_ini = 0;
	//特殊用途变量		
	in_group = 0;					//内机组 用于内机分组查询时用，不同于内机里面的分组号
									//0:(内机数 1--16 时)  1:(16~32) 2:(33~48)
									//初始化完成后用查询得来的数据计算此变量值
	in_groupquery = 0;				//用于查询时作标记用

//状态参数
	s_runmode = 0;					//运行模式  0--停机 1--制冷 2--制热 3--自动
								//			4--送风 5--除湿 6--除霜 7--调试

	s_oil_reclaim_run = 0;			//0--油回收停止 1--油回收运行
	s_oil_blance_run = 0;			//0--油平衡停止 1--油平衡运行

	s_windmotor1 = 0;				//风机1  0--停 1--低速 2--中速 3--高速
	s_windmotor2 = 0;				//风机2  0--停 1--低速 2--中速 3--高速	
	s_windmotor3 = 0;				//风机3  0--停 1--低速 2--中速 3--高速

	//手动设置能力
	s_sethp = 0;
	//手动控制风机用变量		
	//s_windmotor11 = 0;				//风机1  0--停 1--低速 2--中速 3--高速
	//s_windmotor12 = 0;
	//s_windmotor21 = 0;				//风机2  0--停 1--低速 2--中速 3--高速	
	//s_windmotor22 = 0;
	//风机3  0--停 1--低速 2--中速 3--高速
	//s_fourvalve11 = 0;	//四通阀1
	//s_fourvalve21 = 0;
	//s_fourvalve31 = 0;
	//s_fourvalve41 = 0;

	s_ele_valve0 = 0;				//0#电磁阀状态  0--关  1--开
	s_ele_valve1 = 0;				//1#电磁阀状态  0--关  1--开

	//s_ele_valve01 = 0;			//手动设置电磁阀0

	s_ahot = 0;						//辅热输出
	s_ehot = 0;						//电加热输出 

	for (i = 0; i < 6; i++)
		s_compre[i] = 0;				//压缩机1状态 0--关 1--开
//		s_compre2=0;				//压缩机2状态 0--关 1--开
//		s_compre3=0;				//压缩机3状态 0--关 1--开
//		s_compre4=0;				//压缩机4状态 0--关 1--开
//		s_compre5=0;				//压缩机3状态 0--关 1--开
//		s_compre6=0;				//压缩机4状态 0--关 1--开

	s_fourvalve1 = 0;				//四通阀1状态 0--关 1--开
	s_fourvalve2 = 0;				//四通阀2状态 0--关 1--开
	s_fourvalve3 = 0;				//四通阀3状态 0--关 1--开
	s_fourvalve4 = 0;				//四通阀4状态 0--关 1--开


	s_ele_distension_valve1 = 0;	//电磁膨胀阀1开度
	s_ele_distension_valve2 = 0;	//电磁膨胀阀2开度
	s_ele_distension_valve3 = 0;	//电磁膨胀阀3开度
	s_ele_distension_valve4 = 0;	//电磁膨胀阀4开度

	f_s_ele_distension_valve1=0;
	f_s_ele_distension_valve2=0;
	f_s_ele_distension_valve3=0;
	f_s_ele_distension_valve4=0;
	//s_ele_distension_valve11 = 0;		//电磁膨胀阀1开度
	//s_ele_distension_valve21 = 0;		//电磁膨胀阀2开度
	//s_ele_distension_valve31 = 0;		//电磁膨胀阀3开度
	//s_ele_distension_valve41 = 0;		//电磁膨胀阀4开度

	s_total_needed_HP = 0;			//总能力需求(单位HP)
	s_total_needed_HP1 = 0;

	s_datacompre_PWM = 0;			//数码压缩机PWM输出百分比

	s_tp1 = 0;				//排气温度
	s_tp2 = 0;			//环境温度
	s_tp3 = 0;				//回气温度

	s_tp4 = 0;				//1#进盘温度
	s_tp5 = 0;				//1#中盘温度
	s_tp6 = 0;				//1#出盘温度

	s_tp7 = 0;				//2#进盘温度
	s_tp8 = 0;				//2#中盘温度
	s_tp9 = 0;				//2#出盘温度

	s_tp10 = 0;				//3#进盘温度
	s_tp11 = 0;				//3#中盘温度
	s_tp12 = 0;				//3#出盘温度

	s_highpre = 0;				//高压
	s_lowpre = 0;					//低压

	s_factsuperhot = 0;			//实际过热度
	s_factsuperhot3 = 0;			//实际过热度
	s_factsuperhot4 = 0;			//实际过热度
	s_factsuperhot2 = 0;
	s_inmidpantp = 0;				//内机中盘平均温度
	s_targetsuperhot = 40;		//目标过热度
	s_targetsupercool = 0;		//HIC回路目标过冷度

	s_delfrost_check_start_tp = -4;	//除霜检测开始温度(-3~3℃),带符号表示
	s_delfrost_set_tp = -20;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	s_delfrost_exit_tp = 28;			//除霜结束温度  (10~50℃	默认15℃)
	s_delfrost_intertime = 45;		//除霜间隔时间  (0~90min,  默认45min)
	s_delfrost_runtime = 10;			//除霜运行时间  (5~25min,  默认10min)

	s_delnoise_delaytime = 30;		//降噪延迟时间(3~9,默认6)

	s_antifreeze = 5;				//防冻温度
	s_winterantif = 5;				//冬季防冻温度

	s_movefac1 = 30;					//动作系数1
	s_movefac2 = 5;					//动作系数2

	s_out_byte22 = 4;
	s_out_byte221 = 4;
	s_out_byte49 = 0;
	s_out_byte491 = 0;
	s_putongslavenum = 0;
	s_p1 = 30;
	s_p2 = 40;
	s_p3 = 3;
	s_p4 = 8;
	s_p5 = 12;
	s_p6 = 7;
	s_p7 = 45;
	s_p8 = 180;
	s_p9 = 0;

	s_p11 = 30;
	s_p21 = 40;
	s_putongslavenum1 = 0;
	s_p31 = 3;
	s_p41 = 8;
	s_p51 = 12;
	s_p61 = 7;
	s_p71 = 45;
	s_p81 = 180;
	s_p91 = 0;

	s_delfrost_check_start_tp1 = -4;	//除霜检测开始温度(-3~3℃),带符号表示
	s_delfrost_set_tp1 = -20;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	s_delfrost_exit_tp1 = 28;			//除霜结束温度  (10~50℃	默认15℃)
	s_delfrost_intertime1 = 45;		//除霜间隔时间  (0~90min,  默认45min)
	s_delfrost_runtime1 = 10;			//除霜运行时间  (5~25min,  默认10min)

	s_delnoise_delaytime1 = 30;		//降噪延迟时间(3~9,默认6)

	s_antifreeze1 = 5;				//防冻温度
	s_winterantif1 = 5;				//冬季防冻温度

	s_targetsuperhot1 = 40;			//目标过热度
	s_movefac11 = 10;					//动作系数1
	s_movefac21 = 5;					//动作系数2

	//内机
	for (i = 0; i < 16; i++)
	{
		//MDS空调基本参数
		indoor_air[i].s_out_version = 0;				//内机程序版本					
		indoor_air[i].address = 0;					//机组地址     最大32台
		indoor_air[i].s_air_type2 = 0;					//机组类型  0--单冷  1--热泵
		indoor_air[i].low_type_s = 0;
		indoor_air[i].s_air_valve_ini = 0;				//阀的初始开度
		indoor_air[i].air_hp = 3;						//能力

		//状态参数
		indoor_air[i].s_runmode = 0;					//运行模式  0--停机 1--制冷 2--制热 3--自动
										//			4--送风 5--除湿 6--除霜 7--调试

		indoor_air[i].s_oil_reclaim_run = 0;			//0--油回收停止 1--油回收运行
		indoor_air[i].s_oil_blance_run = 0;			//0--油平衡停止 1--油平衡运行

		indoor_air[i].s_windmotor1 = 0;				//风机1  0--停 1--低速 2--中速 3--高速
		indoor_air[i].s_windmotor2 = 0;				//风机2  0--停 1--低速 2--中速 3--高速	
		indoor_air[i].s_windmotor3 = 0;				//风机3  0--停 1--低速 2--中速 3--高速

		//手动控制风机用变量		
		indoor_air[i].s_windmotor11 = 0;				//风机1  0--停 1--低速 2--中速 3--高速
		indoor_air[i].s_windmotor21 = 0;				//风机2  0--停 1--低速 2--中速 3--高速	
		indoor_air[i].s_windmotor31 = 0;				//风机3  0--停 1--低速 2--中速 3--高速

		for (j = 0; j < 6; j++)
			indoor_air[i].s_compre[6] = 0;				//压缩机1状态 0--关 1--开
//			indoor_air[i].s_compre2=0;				//压缩机2状态 0--关 1--开
//			indoor_air[i].s_compre3=0;				//压缩机3状态 0--关 1--开
//			indoor_air[i].s_compre4=0;				//压缩机4状态 0--关 1--开

		indoor_air[i].s_fourvalve1 = 0;				//四通阀1状态 0--关 1--开
		indoor_air[i].s_fourvalve2 = 0;				//四通阀2状态 0--关 1--开

		indoor_air[i].s_ele_distension_valve1 = 0;	//电磁膨胀阀1开度
		indoor_air[i].s_ele_distension_valve2 = 0;	//电磁膨胀阀2开度
		indoor_air[i].s_ele_distension_valve3 = 0;	//电磁膨胀阀3开度
		indoor_air[i].s_ele_distension_valve4 = 0;	//电磁膨胀阀4开度

		indoor_air[i].s_ele_distension_valve11 = 0;		//电磁膨胀阀1开度
		indoor_air[i].s_ele_distension_valve21 = 0;		//电磁膨胀阀2开度
		indoor_air[i].s_ele_distension_valve31 = 0;		//电磁膨胀阀3开度
		indoor_air[i].s_ele_distension_valve41 = 0;		//电磁膨胀阀4开度

		indoor_air[i].s_total_needed_HP = 0;			//总能力需求(单位HP)
		indoor_air[i].s_total_needed_HP1 = 0;

		indoor_air[i].s_tp1 = 0;				//排气温度
		indoor_air[i].s_tp2 = 0;			//环境温度
		indoor_air[i].s_tp3 = 0;				//回气温度

		indoor_air[i].s_tp4 = 0;				//1#进盘温度
		indoor_air[i].s_tp5 = 0;				//1#中盘温度
		indoor_air[i].s_tp6 = 0;				//1#出盘温度

		indoor_air[i].s_tp7 = 0;				//2#进盘温度
		indoor_air[i].s_tp8 = 0;				//2#中盘温度
		indoor_air[i].s_tp9 = 0;				//2#出盘温度

		indoor_air[i].s_tp10 = 0;				//3#进盘温度
		indoor_air[i].s_tp11 = 0;				//3#中盘温度
		indoor_air[i].s_tp12 = 0;				//3#出盘温度

		indoor_air[i].s_highpre = 0;				//高压
		indoor_air[i].s_lowpre = 0;					//低压

		indoor_air[i].s_factsuperhot = 0;			//实际过热度
		indoor_air[i].s_factsuperhot2 = 0;
		indoor_air[i].s_inmidpantp = 0;				//内机中盘平均温度
		indoor_air[i].s_targetsuperhot = 40;		//目标过热度
		indoor_air[i].s_targetsupercool = 0;		//HIC回路目标过冷度

		indoor_air[i].s_delfrost_check_start_tp = -4;	//除霜检测开始温度(-3~3℃),带符号表示
		indoor_air[i].s_delfrost_set_tp = -20;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
		indoor_air[i].s_delfrost_exit_tp = 28;			//除霜结束温度  (10~50℃	默认15℃)
		indoor_air[i].s_delfrost_intertime = 45;		//除霜间隔时间  (0~90min,  默认45min)
		indoor_air[i].s_delfrost_runtime = 10;			//除霜运行时间  (5~25min,  默认10min)

		indoor_air[i].s_delnoise_delaytime = 30;		//降噪延迟时间(3~9,默认6)

		indoor_air[i].s_movefac1 = 30;					//动作系数1
		indoor_air[i].s_movefac2 = 5;					//动作系数2

		indoor_air[i].s_out_byte22 = 4;
		indoor_air[i].s_out_byte49 = 0;
		indoor_air[i].s_p1 = 30;
		indoor_air[i].s_p2 = 40;
		indoor_air[i].s_putongslavenum = 0;
		indoor_air[i].s_p3 = 3;
		indoor_air[i].s_p4 = 8;
		indoor_air[i].s_p5 = 12;
		indoor_air[i].s_p6 = 7;
		indoor_air[i].s_p7 = 45;
		indoor_air[i].s_p8 = 180;
		indoor_air[i].s_p9 = 0;

		indoor_air[i].s_p11 = 30;
		indoor_air[i].s_p21 = 40;
		indoor_air[i].s_putongslavenum1 = 0;
		indoor_air[i].s_p31 = 3;
		indoor_air[i].s_p41 = 8;
		indoor_air[i].s_p51 = 12;
		indoor_air[i].s_p61 = 7;
		indoor_air[i].s_p71 = 45;
		indoor_air[i].s_p81 = 180;
		indoor_air[i].s_p91 = 0;

		indoor_air[i].s_delfrost_check_start_tp1 = -4;	//除霜检测开始温度(-3~3℃),带符号表示
		indoor_air[i].s_delfrost_set_tp1 = -20;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
		indoor_air[i].s_delfrost_exit_tp1 = 28;			//除霜结束温度  (10~50℃	默认15℃)
		indoor_air[i].s_delfrost_intertime1 = 45;		//除霜间隔时间  (0~90min,  默认45min)
		indoor_air[i].s_delfrost_runtime1 = 10;			//除霜运行时间  (5~25min,  默认10min)

		indoor_air[i].s_delnoise_delaytime1 = 30;		//降噪延迟时间(3~9,默认6)

		indoor_air[i].s_targetsuperhot1 = 40;			//目标过热度
		indoor_air[i].s_movefac11 = 10;					//动作系数1
		indoor_air[i].s_movefac21 = 5;					//动作系数2
		indoor_air[i].s_out_byte221 = 4;
		indoor_air[i].s_out_byte491 = 4;
		//压缩机累计运行时间
		for (j = 0; j < 18; j++)
			indoor_air[i].data_13[j] = 0;
	}
	for (i = 0; i < 16; i++)
	{
		com_error[i] = 0;				//内机通讯故障	
	}
	for (i = 0; i < 16; i++)
	{
		s_error[i] = 0;				//故障
	}
	//压缩机累计运行时间
	for (i = 0; i < 18; i++)
		data_13[i] = 0;
	//外机时间
	out_week = 0;
	out_hour = 0;
	out_minute = 0;
	out_sencond = 0;
}

air::~air()
{

}

//响应外机配置  1号命令
void air::reply_out_set(CByteArray* inbyte)
{


	BYTE temp, temp1;
	int flag = 0;
	int i, sum, k;
	float nTemp;
	sum = inbyte->GetAt(2);
	for (k = 3; k < sum + 3; k++)
	{
		if (k == 4)
		{
			nTemp = CheckNegative(inbyte->GetAt(3), inbyte->GetAt(4));
			s_tp5 = nTemp / 10.0f;
		}
		if (k == 5)
		{
			nTemp = CheckNegative(inbyte->GetAt(5), inbyte->GetAt(6));
			s_tp6 = nTemp / 10.0f;
		}
		if (k == 8)
		{
			nTemp = CheckNegative(inbyte->GetAt(7), inbyte->GetAt(8));
			s_tp7 = nTemp / 10.0f;
		}
		if (k == 10)
		{
			nTemp = CheckNegative(inbyte->GetAt(9), inbyte->GetAt(10));
			s_tp1 = nTemp / 10.0f;
		}
		if (k == 12)
		{
			nTemp = CheckNegative(inbyte->GetAt(11), inbyte->GetAt(12));
			s_tp2 = nTemp / 10.0f;
		}
		if (k == 14)
		{
			nTemp = CheckNegative(inbyte->GetAt(13), inbyte->GetAt(14));
			f_s_tp1 = nTemp / 10.0f;
		}
		if (k == 16)
		{
			nTemp = CheckNegative(inbyte->GetAt(15), inbyte->GetAt(16));
			f_s_tp2 = nTemp / 10.0f;
		}
		if (k == 18)
		{
			nTemp = CheckNegative(inbyte->GetAt(17), inbyte->GetAt(18));
			s_tp8 = nTemp / 10.0f;
		}
		if (k == 20)
		{
			nTemp = CheckNegative(inbyte->GetAt(19), inbyte->GetAt(20));
			s_tp3 = nTemp / 10.0f;
		}
		if (k == 22)
		{
			nTemp = CheckNegative(inbyte->GetAt(21), inbyte->GetAt(22));
			s_tp4 = nTemp / 10.0f;
		}
		if (k == 24)
		{
			nTemp = CheckNegative(inbyte->GetAt(23), inbyte->GetAt(24));
			s_tp9 = nTemp / 10.0f;
		}
		if (k == 26)
		{
			nTemp = CheckNegative(inbyte->GetAt(25), inbyte->GetAt(26));
			s_tp10 = nTemp / 10.0f;
		}
		if (k == 28)
		{
			nTemp = CheckNegative(inbyte->GetAt(27), inbyte->GetAt(28));
			f_s_tp9 = nTemp / 10.0f;
		}
		if (k == 30)
		{
			nTemp = CheckNegative(inbyte->GetAt(29), inbyte->GetAt(30));
			f_s_tp10 = nTemp / 10.0f;
		}
		if (k == 32)
		{
			nTemp = CheckNegative(inbyte->GetAt(31), inbyte->GetAt(32));
			s_lowpre = nTemp / 10.0f;
		}
		if (k == 34)
		{
			nTemp = CheckNegative(inbyte->GetAt(33), inbyte->GetAt(34));
			s_highpre = nTemp / 10.0f;
		}
		if (k == 36)
		{
			nTemp = CheckNegative(inbyte->GetAt(35), inbyte->GetAt(36));
			s_gaoya1 = nTemp / 10.0f;
		}
		if (k == 38)
		{
			nTemp = CheckNegative(inbyte->GetAt(37), inbyte->GetAt(38));
			s_gaoya2 = nTemp / 10.0f;
		}
		if (k == 40)
		{
			nTemp = CheckNegative(inbyte->GetAt(39), inbyte->GetAt(40));
			f_s_lowpre = nTemp / 10.0f;
		}
		if (k == 42)
		{
			nTemp = CheckNegative(inbyte->GetAt(41), inbyte->GetAt(42));
			f_s_highpre = nTemp / 10.0f;
		}
		if (k == 44)
		{
			nTemp = CheckNegative(inbyte->GetAt(43), inbyte->GetAt(44));
			f_s_gaoya1 = nTemp / 10.0f;
		}
		if (k == 46)
		{
			nTemp = CheckNegative(inbyte->GetAt(45), inbyte->GetAt(46));
			f_s_gaoya2 = nTemp / 10.0f;
		}
		if (k == 48)
		{
			nTemp = CheckNegative(inbyte->GetAt(47), inbyte->GetAt(48));
			s_tp11 = nTemp / 10.0f; // 补气进口温度1-1
		}
		if (k == 50)
		{
			nTemp = CheckNegative(inbyte->GetAt(49), inbyte->GetAt(50));
			s_tp12 = nTemp / 10.0f; // 补气进口温度2-1
		}
		if (k == 52)
		{
			nTemp = CheckNegative(inbyte->GetAt(51), inbyte->GetAt(52));
			s_tp13 = nTemp / 10.0f; // 补气出口温度1-1
		}
		if (k == 54)
		{
			nTemp = CheckNegative(inbyte->GetAt(53), inbyte->GetAt(54));
			s_tp14 = nTemp / 10.0f; // 补气出口温度2-1
		}
		if (k == 56)
		{
			nTemp = CheckNegative(inbyte->GetAt(55), inbyte->GetAt(56));
			s_ele_distension_valve1 = nTemp / 10.0f; // 主路膨胀阀1-1
		}
		if (k == 58)
		{
			nTemp = CheckNegative(inbyte->GetAt(57), inbyte->GetAt(58));
			s_ele_distension_valve2 = nTemp / 10.0f; // 主路膨胀阀2-1
		}
		if (k == 60)
		{
			nTemp = CheckNegative(inbyte->GetAt(59), inbyte->GetAt(60));
			f_s_ele_distension_valve1 = nTemp / 10.0f; // 主路膨胀阀1-2
		}
		if (k == 62)
		{
			nTemp = CheckNegative(inbyte->GetAt(61), inbyte->GetAt(62));
			f_s_ele_distension_valve2 = nTemp / 10.0f; // 主路膨胀阀2-2
		}
		if (k == 64)
		{
			nTemp = CheckNegative(inbyte->GetAt(63), inbyte->GetAt(64));
			s_ele_distension_valve3 = nTemp / 10.0f; // 辅路膨胀阀1-1
		}
		if (k == 66)
		{
			nTemp = CheckNegative(inbyte->GetAt(65), inbyte->GetAt(66));
			s_ele_distension_valve4 = nTemp / 10.0f; // 辅路膨胀阀2-1
		}
		if (k == 68)
		{
			nTemp = CheckNegative(inbyte->GetAt(67), inbyte->GetAt(68));
			s_ele = nTemp / 10.0f; // 压机电流1-1
		}
		if (k == 70)
		{
			nTemp = CheckNegative(inbyte->GetAt(69), inbyte->GetAt(70));
			s_ele2 = nTemp / 10.0f; // 压机电流2-1
		}
		if (k == 72)
		{
			nTemp = CheckNegative(inbyte->GetAt(71), inbyte->GetAt(72));
			f_s_ele1 = nTemp / 10.0f; // 压机电流1-2
		}
		if (k == 74)
		{
			nTemp = CheckNegative(inbyte->GetAt(73), inbyte->GetAt(74));
			f_s_ele2 = nTemp / 10.0f; // 压机电流2-2
		}
	}
}

//响应从机配置  2号命令
void air::reply_in_set(CByteArray* inbyte)
{
	int group = 0;		 //内机组别
	int No = 0;			//当前正记录内机号
	BYTE temp, temp1;
	int ntemp = 0;
	No = inbyte->GetAt(2);
	if (No > 2 || No < 0)	//做一有效性检查，防止溢出
		return;
	ntemp =inbyte->GetAt(3);
	DO5 = (ntemp >> 2) & 0x01;//四通阀1
	DO6 = (ntemp >> 3) & 0x01;
	s_ahot = (ntemp >> 4) & 0x01;//曲轴电加热1
	hot_eheat = (ntemp >> 5) & 0x01;//曲轴电加热2
	ntemp = inbyte->GetAt(4);
	s_comp3_real = ntemp & 0x01;//压缩机1
	s_comp4_real = (ntemp >> 1) & 0x01;//压缩机2
	DOF5 = (ntemp >> 2) & 0x01;//副板电加热1
	DOF6 = (ntemp >> 3) & 0x01;//副板电加热2
}

//查询主机运行状态、状态 3号命令 
void air::reply_air_status(CByteArray* inbyte)
{
	int temp, temp1;
	int k, byte_count, sum;
	//byte(3到5)是线控器设置的温度模式等
	//byte(6到9)是主机状态
	sum = inbyte->GetAt(2);
	for (k = 3; k < sum + 3; k++)
	{
		if (k == 4)
		{
			temp = CheckNegative(inbyte->GetAt(3), inbyte->GetAt(4));
			s_comp1_real = temp;
		}
		if (k == 6)
		{
			temp = CheckNegative(inbyte->GetAt(5), inbyte->GetAt(6));
			s_comp2_real = temp;
		}
		if (k == 12)
		{
			temp = CheckNegative(inbyte->GetAt(11), inbyte->GetAt(12));
			s_fan1_real = temp;
		}
		if (k == 14)
		{
			temp = CheckNegative(inbyte->GetAt(13), inbyte->GetAt(14));
			s_fan2_real = temp;
		}
	}

}

//响应从机运行参数
void air::reply_out_para(CByteArray* inbyte)
{
	int temp, temp1;
	int addr;
	//byte(3到5)是线控器设置的温度模式等
	//byte(6到9)是主机状态
	addr = inbyte->GetAt(3);
	if ((addr < 0) || (addr > 15))			//判断从机地址的有效性
		return;
	temp = inbyte->GetAt(4);
	//运行模式  0--停机 1--制冷 2--制热 3--自动
	//			4--除霜 5--调试
	indoor_air[addr].s_runmode = temp & 0x7;
	//风机1  0--停 1--低速 2--中速 3--高速
	temp1 = temp >> 3;
	indoor_air[addr].s_windmotor1 = temp1 & 0x3;
	//风机2  0--停 1--低速 2--中速 3--高速	
	temp1 = temp >> 5;
	indoor_air[addr].s_windmotor2 = temp1 & 0x3;

	//电磁阀1状态
//	temp1=temp>>7;
//	indoor_air[addr].s_ele_valve0=temp1&0x1;
	temp = inbyte->GetAt(7);
	temp1 = temp >> 3;
	indoor_air[addr].s_ele_valve0 = temp1 & 0x1;
	temp1 = temp >> 5;
	indoor_air[addr].s_ele_valve1 = temp1 & 0x1;
	//    temp1=temp>>5;
	//    indoor_air[addr].s_ele_valve3=temp1&0x1;
		//压缩机1状态 0--关 1--开
	temp = inbyte->GetAt(5);
	temp1 = temp >> 2;
	indoor_air[addr].s_compre[0] = temp1 & 0x1;
	//压缩机2状态 0--关 1--开
	temp1 = temp >> 3;
	indoor_air[addr].s_compre[1] = temp1 & 0x1;
	//压缩机3状态 0--关 1--开
	temp1 = temp >> 4;
	indoor_air[addr].s_compre[2] = temp1 & 0x1;
	//压缩机4状态 0--关 1--开
	temp1 = temp >> 5;
	indoor_air[addr].s_compre[3] = temp1 & 0x1;
	//压缩机5状态 0--关 1--开
//	temp1=temp>>6;
 //   indoor_air[addr].s_compre[4]=temp1&0x1;	
	//压缩机6状态 0--关 1--开
//	temp1=temp>>7;
//    indoor_air[addr].s_compre[5]=temp1&0x1;	

	//四通阀1状态 0--关 1--开
	indoor_air[addr].s_fourvalve1 = temp & 0x1;
	//四通阀2状态 0--关 1--开
	temp1 = temp >> 1;
	indoor_air[addr].s_fourvalve2 = temp1 & 0x1;
	temp = inbyte->GetAt(8);
	temp1 = temp >> 4;
	indoor_air[addr].s_fourvalve3 = temp1 & 0x1;
	temp1 = temp >> 5;
	indoor_air[addr].s_fourvalve4 = temp1 & 0x1;
	temp = inbyte->GetAt(6);
	//辅热
	temp1 = temp >> 2;
	indoor_air[addr].s_ahot = temp1 & 0x1;
	//二通阀  用原来的SV3变量表示
	temp1 = temp >> 4;
	indoor_air[addr].s_ele_valve2 = temp1 & 0x1;
	//总能力需求(单位HP)
	temp = inbyte->GetAt(38);
	//	temp1=inbyte->GetAt(27);
	//	temp1=temp1>>4;
	//	temp1=temp1&0x0F;
	indoor_air[addr].s_total_needed_HP = temp;
	//电磁膨胀阀1开度
	temp = inbyte->GetAt(9);
	indoor_air[addr].s_ele_distension_valve1 = temp * 2;
	//电磁膨胀阀2开度
	temp = inbyte->GetAt(10);
	indoor_air[addr].s_ele_distension_valve2 = temp * 2;
	//电磁膨胀阀3开度
	temp = inbyte->GetAt(11);
	indoor_air[addr].s_ele_distension_valve3 = temp * 2;
	//电磁膨胀阀4开度
	temp = inbyte->GetAt(12);
	indoor_air[addr].s_ele_distension_valve4 = temp * 2;

	//排气温度
	temp = inbyte->GetAt(13);
	temp1 = inbyte->GetAt(27);
	indoor_air[addr].s_tp1 = caldec_dlt(temp, temp1, 0);
	//环境温度
	temp = inbyte->GetAt(14);
	temp1 = inbyte->GetAt(28);
	indoor_air[addr].s_tp2 = caldec_dlt(temp, temp1, 0);
	//回气温度	
	temp = inbyte->GetAt(15);
	temp1 = inbyte->GetAt(28);
	indoor_air[addr].s_tp3 = caldec(temp, temp1, 0);
	//1#进盘温度
	temp = inbyte->GetAt(16);
	temp1 = inbyte->GetAt(29);
	indoor_air[addr].s_tp4 = caldec(temp, temp1, 1);
	//1#中盘温度
	temp = inbyte->GetAt(17);
	temp1 = inbyte->GetAt(29);
	indoor_air[addr].s_tp5 = caldec(temp, temp1, 0);
	//1#出盘温度
	temp = inbyte->GetAt(18);
	temp1 = inbyte->GetAt(30);
	indoor_air[addr].s_tp6 = caldec(temp, temp1, 1);
	//2#进盘温度
	temp = inbyte->GetAt(19);
	temp1 = inbyte->GetAt(30);
	indoor_air[addr].s_tp7 = caldec(temp, temp1, 0);
	//2#中盘温度
	temp = inbyte->GetAt(20);
	temp1 = inbyte->GetAt(31);
	indoor_air[addr].s_tp8 = caldec(temp, temp1, 1);
	//2#出盘温度
	temp = inbyte->GetAt(21);
	temp1 = inbyte->GetAt(31);
	indoor_air[addr].s_tp9 = caldec(temp, temp1, 0);
	//3#进盘温度
	temp = inbyte->GetAt(22);
	temp1 = inbyte->GetAt(32);
	indoor_air[addr].s_tp10 = caldec(temp, temp1, 1);
	//3#中盘温度
	temp = inbyte->GetAt(23);
	temp1 = inbyte->GetAt(32);
	indoor_air[addr].s_tp11 = caldec(temp, temp1, 0);
	//3#出盘温度
	temp = inbyte->GetAt(24);
	temp1 = inbyte->GetAt(33);
	indoor_air[addr].s_tp12 = caldec(temp, temp1, 1);

	temp = inbyte->GetAt(51);
	temp1 = inbyte->GetAt(53);
	indoor_air[addr].s_tp13 = caldec(temp, temp1, 0);    //TH13
	temp = inbyte->GetAt(52);
	indoor_air[addr].s_tp14 = caldec(temp, temp1, 1);    //TH13
	//低压2
	temp = inbyte->GetAt(25);
	temp1 = inbyte->GetAt(34);
	temp1 = temp1 >> 4;
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_lowpre2 = temp + (float)temp1 / 10;

	//低压
	temp = inbyte->GetAt(26);
	temp1 = inbyte->GetAt(34);
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_lowpre = temp + (float)temp1 / 10;


	//实际过热度					
	temp = inbyte->GetAt(35);
	temp1 = inbyte->GetAt(33);
	indoor_air[addr].s_factsuperhot = caldec(temp, temp1, 0);
	//系统2的实际过热度
	temp = inbyte->GetAt(36);
	temp1 = inbyte->GetAt(27);
	indoor_air[addr].s_factsuperhot2 = caldec(temp, temp1, 1);
	//目标过热度					
	temp = inbyte->GetAt(37);
	indoor_air[addr].s_targetsuperhot = temp;
	//HIC回路目标过冷度			
	temp = inbyte->GetAt(38);
	indoor_air[addr].s_targetsupercool = temp;

	int j;
	temp = inbyte->GetAt(39);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[j] = temp1 & 1;
	}
	temp = inbyte->GetAt(40);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[8 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(41);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[16 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(42);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[24 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(43);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[32 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(44);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].exs_err[j] = temp1 & 1;
	}
	temp = inbyte->GetAt(45);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].exs_err[8 + j] = temp1 & 1;
	}


	//电流1
	temp = inbyte->GetAt(54);
	temp1 = inbyte->GetAt(55);
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_ele = temp + (float)temp1 / 10;
	//电流2
	temp = inbyte->GetAt(56);
	temp1 = inbyte->GetAt(57);
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_ele2 = temp + (float)temp1 / 10;


	//高压1
	temp = inbyte->GetAt(58);
	temp1 = inbyte->GetAt(60);
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_highpre = temp + (float)temp1 / 10;
	//高压2
	temp = inbyte->GetAt(59);
	temp1 = inbyte->GetAt(60);
	temp1 = temp1 >> 4;
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_highpre2 = temp + (float)temp1 / 10;

	temp = inbyte->GetAt(61);
	indoor_air[addr].s_exv1_216 = temp * 2;
	temp = inbyte->GetAt(62);
	indoor_air[addr].s_exv2_216 = temp * 2;
	temp = inbyte->GetAt(63);
	indoor_air[addr].s_exv3_216 = temp * 2;
	temp = inbyte->GetAt(64);
	indoor_air[addr].s_exv4_216 = temp * 2;
	temp = inbyte->GetAt(65);
	indoor_air[addr].s_exv5_216 = temp * 2;
	temp = inbyte->GetAt(66);
	indoor_air[addr].s_exv6_216 = temp * 2;

}

//响应内机运行参数
void air::reply_in_para(CByteArray* inbyte)
{
	;
}
void air::modify_specvalve_para(CByteArray* outbyte)
{
	int temp;

	temp = s_ele_distension_valve11 / 2;		//电磁膨胀阀1开度
	outbyte->SetAt(3, temp);
	temp = s_ele_distension_valve21 / 2;		//电磁膨胀阀2开度
	outbyte->SetAt(4, temp);
	temp = s_ele_distension_valve31 / 2;		//电磁膨胀阀3开度
	outbyte->SetAt(5, temp);
	temp = s_ele_distension_valve41 / 2;		//电磁膨胀阀4开度
	outbyte->SetAt(6, temp);

	temp = s_exv1_2161 / 2;
	outbyte->SetAt(7, temp);
	temp = s_exv2_2161 / 2;
	outbyte->SetAt(8, temp);
	temp = s_exv3_2161 / 2;
	outbyte->SetAt(9, temp);
	temp = s_exv4_2161 / 2;
	outbyte->SetAt(10, temp);
	temp = s_exv5_2161 / 2;
	outbyte->SetAt(11, temp);
	temp = s_exv6_2161 / 2;
	outbyte->SetAt(12, temp);
}

void air::modify_out_para(CByteArray* outbyte)
{
	int temp;
	temp = s_delfrost_check_start_tp1;	//除霜检测开始温度(-3~3℃),带符号表示
	if (temp < 0)
	{
		temp = temp + 256;
	}
	outbyte->SetAt(4, temp);

	temp = s_delfrost_set_tp1;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	if (temp < 0)
	{
		temp = temp + 256;
	}
	outbyte->SetAt(5, temp);

	temp = s_delfrost_exit_tp1;			//除霜结束温度  (10~50℃	默认15℃)
	outbyte->SetAt(6, temp);
	temp = s_delfrost_intertime1;		//除霜间隔时间  (0~90min,  默认45min)
	outbyte->SetAt(7, temp);
	temp = s_delfrost_runtime1;			//除霜运行时间  (5~25min,  默认10min)
	outbyte->SetAt(8, temp);
	temp = s_delnoise_delaytime1;		//降噪延迟时间(3~9,默认6)
	outbyte->SetAt(9, temp);

	//动作系数1
	temp = s_movefac11;
	outbyte->SetAt(10, temp);
	//动作系数2
	temp = s_movefac21;
	outbyte->SetAt(11, temp);

	outbyte->SetAt(12, s_p11);
	//	outbyte->SetAt(13,s_p21);
	outbyte->SetAt(14, s_p31);
	//	outbyte->SetAt(15,s_p41);
	outbyte->SetAt(16, s_p51);
	outbyte->SetAt(17, s_p61);
	outbyte->SetAt(18, s_p71);
	outbyte->SetAt(19, s_p81);
	//目标过热度					

	temp = s_targetsuperhot1;
	outbyte->SetAt(20, temp);

	//制冷防冻温度设置
	temp = s_antifreeze1;
	if (temp < 0)
	{
		temp = temp + 256;
	}
	outbyte->SetAt(21, temp);
	//冬季防冻温度
	temp = s_winterantif1;
	if (temp < 0)
	{
		temp = temp + 256;
	}
	outbyte->SetAt(22, temp);

	//热水水温补偿参数
	temp = s_out_byte221;
	outbyte->SetAt(24, temp);

	temp = ele_auto_open1;
	outbyte->SetAt(26, temp);

	temp = s_remote_open1;
	outbyte->SetAt(27, temp);

	temp = air_type21;
	outbyte->SetAt(28, temp);

	temp = s_liuliang1;
	outbyte->SetAt(29, temp);

	temp = s_hotwatercontrol1;
	outbyte->SetAt(30, temp);

	temp = watertemp1;
	outbyte->SetAt(31, temp);

	temp = s_coolandhotrun1;
	outbyte->SetAt(32, temp);

	temp = s_hotandhotrun1;
	outbyte->SetAt(33, temp);

	temp = s_singledoublebox1;
	outbyte->SetAt(34, temp);

	temp = air_valve_ini1;
	outbyte->SetAt(35, temp);

	temp = s_putongslavenum1;
	outbyte->SetAt(36, temp);

	temp = cool_media_type1;
	outbyte->SetAt(37, temp);

	temp = putonorhot1;
	outbyte->SetAt(38, temp);



	temp = s_ele_distension_valve11 / 2;		//电磁膨胀阀1开度
	outbyte->SetAt(44, temp);
	temp = s_ele_distension_valve21 / 2;		//电磁膨胀阀2开度
	outbyte->SetAt(45, temp);
	temp = s_ele_distension_valve31 / 2;		//电磁膨胀阀3开度
	outbyte->SetAt(46, temp);
	temp = s_ele_distension_valve41 / 2;		//电磁膨胀阀4开度
	outbyte->SetAt(47, temp);

	//	temp=s_sethp1/10;		//手动设置能力
	//	outbyte->SetAt(27,temp);
	//	temp=s_sethp1%10;		//手动设置能力
	//	outbyte->SetAt(28,temp);

		//手动控制风机用变量		
	temp = s_windmotor11;				//风机1  0--停 1--低速 2--中速 3--高速
	temp |= s_windmotor21 << 2;				//风机2  0--停 1--低速 2--中速 3--高速	
//	temp|=s_windmotor31<<4;				//风机3  0--停 1--低速 2--中速 3--高速
	//电磁阀
	//temp |= s_ele_valve01 << 4;
	//电磁阀2
	//temp |= s_ele_valve11 << 5;
	outbyte->SetAt(50, temp);


	temp = s_exv1_2161 / 2;
	outbyte->SetAt(52, temp);
	temp = s_exv2_2161 / 2;
	outbyte->SetAt(53, temp);
	temp = s_exv3_2161 / 2;
	outbyte->SetAt(54, temp);
	temp = s_exv4_2161 / 2;
	outbyte->SetAt(55, temp);
	temp = s_exv5_2161 / 2;
	outbyte->SetAt(56, temp);
	temp = s_exv6_2161 / 2;
	outbyte->SetAt(57, temp);

	/*xg
		temp=0;
		temp|=s_fourvalve11;			//四通阀a
		temp|=s_fourvalve21<<1;			//压缩机0
		temp|=s_compre1[0]<<2;			//压缩机0
		temp|=s_compre1[1]<<3;			//压缩机1
		temp|=s_compre1[2]<<4;			//压缩机1
		temp|=s_compre1[3]<<5;			//压缩机1
		outbyte->SetAt(30,temp);
	*/

	//	temp=(int)(s_total_needed_HP1*10);		//能力需求
	//	if(temp>255)
	//		temp=255;
	//	if(temp<0)
	//		temp=0;
	//	outbyte->SetAt(15,temp);

}
void air::modify_out_para1()
{
	s_delfrost_check_start_tp = s_delfrost_check_start_tp1;	//除霜检测开始温度(-3~3℃),带符号表示
	s_delfrost_set_tp = s_delfrost_set_tp1;			//除霜温度设置  范围0~-7℃度 默认-5℃ 带符号表示
	s_delfrost_exit_tp = s_delfrost_exit_tp1;			//除霜结束温度  (10~50℃	默认15℃)
	s_delfrost_intertime = s_delfrost_intertime1;		//除霜间隔时间  (0~90min,  默认45min)
	s_delfrost_runtime = s_delfrost_runtime1;			//除霜运行时间  (5~25min,  默认10min)	
	s_delnoise_delaytime = s_delnoise_delaytime1;		//降噪延迟时间(3~9,默认6)
	//目标过热度					
	s_targetsuperhot = s_targetsuperhot1;
	//动作系数1
	s_movefac1 = s_movefac11;
	//动作系数2
	s_movefac2 = s_movefac21;

	s_out_byte22 - s_out_byte221;
	s_out_byte49 - s_out_byte491;
	s_p1 = s_p11;
	s_putongslavenum = s_putongslavenum1;
	s_p3 = s_p31;
	s_p4 = s_p41;
	s_p5 = s_p51;
	s_p6 = s_p61;
	s_p7 = s_p71;
	s_p8 = s_p81;
	s_p9 = s_p91;
	//s_sethp = s_sethp1;
	s_windmotor1 = s_windmotor11;
	s_windmotor2 = s_windmotor21;
	s_ele_valve0 = s_ele_valve01;
	s_ele_valve1 = s_ele_valve11;
	//制冷防冻温度
	s_antifreeze = s_antifreeze1;
	//冬季防冻温度
	s_winterantif = s_winterantif1;

	ele_auto_open = ele_auto_open1;
	s_remote_open = s_remote_open1;
	air_type2 = air_type21;
	s_liuliang = s_liuliang1;
	air_valve_ini = air_valve_ini1;
	s_hotwatercontrol = s_hotwatercontrol1;
	watertemp = watertemp1;
	s_coolandhotrun = s_coolandhotrun1;
	s_hotandhotrun = s_hotandhotrun1;
	s_singledoublebox = s_singledoublebox1;
	cool_media_type = cool_media_type1;
	putonorhot = putonorhot1;
	s_exv1_216 = s_exv1_2161;
	s_exv2_216 = s_exv2_2161;
	s_exv3_216 = s_exv3_2161;
	s_exv4_216 = s_exv4_2161;
	s_exv5_216 = s_exv5_2161;
	s_exv6_216 = s_exv6_2161;
}

void air::modify_sout_para1()
{
	;
}

float caldec(BYTE temp, BYTE temp1, int hiflag)		//计算小数(带正负数)hiflag为1则temp1高四位为小数，否则 temp1低四位为小数部分
{
	int temp2;
	float f = 0;
	temp2 = temp;
	if (temp & 0x80)//负数
	{
		temp2 -= 128;
		if (hiflag == 1)
			temp1 = temp1 >> 4;
		temp1 = temp1 & 0x0F;
		f = -(temp2 + (float)temp1 / 10);
	}
	else//正数
	{
		if (hiflag == 1)
			temp1 = temp1 >> 4;
		temp1 = temp1 & 0x0F;
		f = temp2 + (float)temp1 / 10;
	}
	return f;
}

float caldec_dlt(unsigned char temp, unsigned char temp1, int hiflag)
{
	int temp2;
	float f = 0;
	temp2 = temp;
	if (hiflag == 1)
		temp1 = temp1 >> 4;
	temp1 = temp1 & 0x0F;
	f = temp2 + (float)temp1 / 10;
	return f;
}

//响应读压缩机状态 13号命令
void air::reply_comp_time(CByteArray* inbyte)
{
	int temp = 0;
	int No = 0;			//当前正记录内机号
	if (inbyte->GetSize() == 24)
	{
		No = inbyte->GetAt(3);
		if (No == 0xff)	// 主机
		{
			for (temp = 0; temp < 19; temp++)
			{
				data_13[temp] = inbyte->GetAt(temp + 4);
			}
		}
		else			//从机
		{
			for (temp = 0; temp < 19; temp++)
			{
				indoor_air[No].data_13[temp] = inbyte->GetAt(temp + 4);
			}
		}
	}
}

void air::modify_out_para_s(int slave_no, CByteArray* outbyte)
{
	int temp;
	CString str;
	temp = indoor_air[slave_no].s_delfrost_check_start_tp;  //除霜A点
	if (temp < 0)
	{
		temp = temp + 256;
	}
	outbyte->SetAt(4, temp);
	temp = indoor_air[slave_no].s_delfrost_set_tp;         //除霜B点
	if (temp < 0)
	{
		temp = temp + 256;
	}
	outbyte->SetAt(5, temp);
	temp = indoor_air[slave_no].s_delfrost_exit_tp;
	outbyte->SetAt(6, temp);
	temp = indoor_air[slave_no].s_delfrost_intertime;    //除霜间隔时间
	outbyte->SetAt(7, temp);
	temp = indoor_air[slave_no].s_delfrost_runtime;      //除霜运行时间
	outbyte->SetAt(8, temp);
	temp = 50;
	outbyte->SetAt(9, temp);                            //能力计算周期
	temp = 30;
	outbyte->SetAt(10, temp);
	temp = 5;
	outbyte->SetAt(11, temp);
	temp = 30;
	outbyte->SetAt(12, temp);
	temp = 2;
	outbyte->SetAt(13, temp);
	temp = 3;
	outbyte->SetAt(14, temp);
	temp = 14;
	outbyte->SetAt(15, temp);
	temp = 45;
	outbyte->SetAt(16, temp);
	temp = 7;
	outbyte->SetAt(17, temp);
	temp = 45;
	outbyte->SetAt(18, temp);
	temp = 60;
	outbyte->SetAt(19, temp);
	temp = indoor_air[slave_no].s_targetsuperhot1;
	outbyte->SetAt(20, temp);
	temp = indoor_air[slave_no].s_cool_ant;
	outbyte->SetAt(21, temp);
	temp = indoor_air[slave_no].s_winter_ant;
	outbyte->SetAt(22, temp);
}

//void air::reply_master_status(CByteArray* inbyte)
//{
//	int temp, temp1;
//	unsigned char temp2;
//	temp2 = inbyte->GetAt(3);
//	coolset = temp2 & 0x1f;
//	coolset = coolset + 3;
//	temp2 = inbyte->GetAt(4);
//	m_heatset = temp2 & 0x1f;
//	m_heatset = m_heatset + 25;
//	temp2 = inbyte->GetAt(5);
//	m_hotset = temp2;
//	temp = inbyte->GetAt(6);
//	//运行模式  0--停机 1--制冷 2--制热 3--自动
//	//			4--除霜 5--调试
//	s_runmode = temp & 0x7;
//	//风机1  0--停 1--低速 2--中速 3--高速
//	temp1 = temp >> 3;
//	s_windmotor1 = temp1 & 0x3;
//	//风机2  0--停 1--低速 2--中速 3--高速	
//	temp1 = temp >> 5;
//	s_windmotor2 = temp1 & 0x3;
//
//	//电磁阀1状态
//	temp1 = temp >> 7;
//	s_ele_valve0 = temp1 & 0x1;
//	temp = inbyte->GetAt(9);
//	temp1 = temp >> 3;
//	s_ele_valve1 = temp1 & 0x1;
//	temp1 = temp >> 4;
//	s_ele_valve2 = temp1 & 0x1;
//	temp1 = temp >> 5;
//	s_ele_valve3 = temp1 & 0x1;
//	//压缩机1状态 0--关 1--开
//	temp = inbyte->GetAt(7);
//	temp1 = temp >> 2;
//	s_compre[0] = temp1 & 0x1;
//	//压缩机2状态 0--关 1--开
//	temp1 = temp >> 3;
//	s_compre[1] = temp1 & 0x1;
//	//压缩机3状态 0--关 1--开
//	temp1 = temp >> 4;
//	s_compre[2] = temp1 & 0x1;
//	//压缩机4状态 0--关 1--开
//	temp1 = temp >> 5;
//	s_compre[3] = temp1 & 0x1;
//	//压缩机5状态 0--关 1--开
//	temp1 = temp >> 6;
//	s_compre[4] = temp1 & 0x1;
//	//压缩机6状态 0--关 1--开
//	temp1 = temp >> 7;
//	s_compre[5] = temp1 & 0x1;
//
//	//四通阀1状态 0--关 1--开
//	s_fourvalve1 = temp & 0x1;
//	//四通阀2状态 0--关 1--开
//	temp1 = temp >> 1;
//	s_fourvalve2 = temp1 & 0x1;
//	//四通阀3状态 0-关 1--开
//	temp = inbyte->GetAt(10);
//	hot_eheat = temp & 0x1;
//	temp1 = temp >> 4;
//	s_fourvalve3 = temp1 & 0x1;
//	temp1 = temp >> 5;
//	s_fourvalve4 = temp1 & 0x1;
//	//水泵输出
//	temp = inbyte->GetAt(8);
//	s_pumpstate = temp & 0x1;
//	temp1 = temp >> 1;
//	s_ehot = temp1 & 0x1;
//	temp1 = temp >> 2;
//	s_ahot = temp1 & 0x1;
//
//
//	temp = inbyte->GetAt(9);
//	s_pump2state = temp & 0x1;
//
//
//
//	//总能力需求(单位HP)
//	temp = inbyte->GetAt(40);
//	//	temp1=inbyte->GetAt(29);
//	//	temp1=temp1>>4;
//	//	temp1=temp1&0x0F;
//	s_total_needed_HP = temp;
//	//电磁膨胀阀1开度
//	temp = inbyte->GetAt(11);
//	s_ele_distension_valve1 = temp * 2;
//	//电磁膨胀阀2开度
//	temp = inbyte->GetAt(12);
//	s_ele_distension_valve2 = temp * 2;
//	//电磁膨胀阀3开度
//	temp = inbyte->GetAt(13);
//	s_ele_distension_valve3 = temp * 2;
//	//电磁膨胀阀4开度
//	temp = inbyte->GetAt(14);
//	s_ele_distension_valve4 = temp * 2;
//
//	//排气温度
//	temp = inbyte->GetAt(15);
//	temp1 = inbyte->GetAt(29);
//	s_tp1 = caldec_dlt(temp, temp1, 0);
//	//环境温度
//	temp = inbyte->GetAt(16);
//	temp1 = inbyte->GetAt(30);
//	s_tp2 = caldec_dlt(temp, temp1, 1);
//	//回气温度	
//	temp = inbyte->GetAt(17);
//	temp1 = inbyte->GetAt(30);
//	s_tp3 = caldec(temp, temp1, 0);
//	//1#进盘温度
//	temp = inbyte->GetAt(18);
//	temp1 = inbyte->GetAt(31);
//	s_tp4 = caldec(temp, temp1, 1);
//	//1#中盘温度
//	temp = inbyte->GetAt(19);
//	temp1 = inbyte->GetAt(31);
//	s_tp5 = caldec(temp, temp1, 0);
//	//1#出盘温度
//	temp = inbyte->GetAt(20);
//	temp1 = inbyte->GetAt(32);
//	s_tp6 = caldec(temp, temp1, 1);
//	//2#进盘温度
//	temp = inbyte->GetAt(21);
//	temp1 = inbyte->GetAt(32);
//	s_tp7 = caldec(temp, temp1, 0);
//	//2#中盘温度
//	temp = inbyte->GetAt(22);
//	temp1 = inbyte->GetAt(33);
//	s_tp8 = caldec(temp, temp1, 1);
//	//2#出盘温度
//	temp = inbyte->GetAt(23);
//	temp1 = inbyte->GetAt(33);
//	s_tp9 = caldec(temp, temp1, 0);
//	//3#进盘温度
//	temp = inbyte->GetAt(24);
//	temp1 = inbyte->GetAt(34);
//	s_tp10 = caldec(temp, temp1, 1);
//	//3#中盘温度
//	temp = inbyte->GetAt(25);
//	temp1 = inbyte->GetAt(34);
//	s_tp11 = caldec(temp, temp1, 0);
//	//3#出盘温度
//	temp = inbyte->GetAt(26);
//	temp1 = inbyte->GetAt(35);
//	s_tp12 = caldec(temp, temp1, 1);
//	temp = inbyte->GetAt(53);
//	temp1 = inbyte->GetAt(55);
//	s_tp13 = caldec(temp, temp1, 0);
//	//s_tp20=caldec(temp,temp1,0);
//	temp = inbyte->GetAt(54);
//	temp1 = inbyte->GetAt(55);
//	s_tp14 = caldec(temp, temp1, 1);
//	//	s_tp21=caldec(temp,temp1,1);
//		//低压2
//	temp = inbyte->GetAt(27);
//	temp1 = inbyte->GetAt(36);
//	temp1 = temp1 >> 4;
//	temp1 = temp1 & 0x0F;
//	s_highpre = temp + (float)temp1 / 10;
//
//	//低压1
//	temp = inbyte->GetAt(28);
//	temp1 = inbyte->GetAt(36);
//	temp1 = temp1 & 0x0F;
//	s_lowpre = temp + (float)temp1 / 10;
//
//
//	//实际过热度					
//	temp = inbyte->GetAt(37);
//	temp1 = inbyte->GetAt(35);
//	s_factsuperhot = caldec(temp, temp1, 0);
//	//实际过热度2
//	temp = inbyte->GetAt(38);
//	temp1 = inbyte->GetAt(29);
//	s_factsuperhot2 = caldec(temp, temp1, 1);
//	//目标过热度					
//	temp = inbyte->GetAt(39);
//	s_targetsuperhot = temp;
//	//HIC回路目标过冷度			
//	temp = inbyte->GetAt(40);
//	s_targetsupercool = temp;
//
//
//	//从机通讯故障
//	for (int i = 0; i < 2; i++)
//	{
//		temp = inbyte->GetAt(41 + i);
//		for (int j = 0; j < 8; j++)
//		{
//			temp1 = temp >> j;
//			com_error[i * 8 + j] = temp1 & 1;
//		}
//	}
//	int j;
//	temp = inbyte->GetAt(43);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		s_error[j] = temp1 & 1;
//	}
//	temp = inbyte->GetAt(44);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		s_error[8 + j] = temp1 & 1;
//	}
//	temp = inbyte->GetAt(45);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		s_error[16 + j] = temp1 & 1;
//	}
//	temp = inbyte->GetAt(46);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		s_error[24 + j] = temp1 & 1;
//	}
//	temp = inbyte->GetAt(47);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		s_error[32 + j] = temp1 & 1;
//	}
//	temp = inbyte->GetAt(48);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		ex_err[j] = temp1 & 1;
//	}
//	temp = inbyte->GetAt(49);
//	for (j = 0; j < 8; j++)
//	{
//		temp1 = temp >> j;
//		ex_err[j + 8] = temp1 & 1;
//	}
//
//
//	/*
//		temp=inbyte->GetAt(51);
//		water_level1=temp&0x01;
//		temp1=temp>>1;
//		water_level2=temp1&0x01;
//		temp1=temp>>2;
//		water_level3=temp1&0x01;
//		temp1=temp>>3;
//		water_level4=temp1&0x01;
//		temp1=temp>>4;
//		water_level5=temp1&0x01;
//
//		water_step=inbyte->GetAt(55);
//		temp=inbyte->GetAt(56);
//		water_step=water_step*100+temp;
//	*/
//	temp = inbyte->GetAt(57);
//	temp1 = inbyte->GetAt(59);
//	temp1 = temp1 & 0x0f;
//	hpre1 = temp + (float)temp1 / 10;//系统1高压
//
//	temp = inbyte->GetAt(58);
//	temp1 = inbyte->GetAt(59);
//	temp1 = temp1 >> 4;
//	temp1 = temp1 & 0x0f;
//	hpre2 = temp + (float)temp1 / 10; //系统2高压
//
///*	temp=inbyte->GetAt(61);
//	temp1=inbyte->GetAt(60);
//	BLDC_speed1=temp*255+temp1;
//
//	temp=inbyte->GetAt(63);
//	temp1=inbyte->GetAt(62);
//	BLDC_speed2=temp*255+temp1;*/
//
//	temp = inbyte->GetAt(56);
//	temp1 = inbyte->GetAt(52);
//	s_tp20 = caldec(temp, temp1, 0);
//
//	temp = inbyte->GetAt(57);
//	temp1 = inbyte->GetAt(52);
//	s_tp21 = caldec(temp, temp1, 1);
//
//
//
//	/*
//	temp=inbyte->GetAt(67);
//	water_vm1=temp&0x01;
//	temp1=temp>>1;
//	water_vm2=temp1&0x01;
//	temp1=temp>>2;
//	water_vm3=temp1&0x01;
//	temp1=temp>>3;
//	water_vm4=temp1&0x01;
//	temp1=temp>>4;
//	wadd_pump=temp1&0x01;*/
//}

int air::CheckNegative(const BYTE bHight, const BYTE bLow)
{
	int nTemp = 0;
	UINT uHight;
	UINT uLow;


	nTemp = bHight & 0x80;
	if (nTemp == 128)
	{
		uHight = bHight << 8;
		uLow = bLow;
		nTemp = ~((0xFFFF0000 | uHight | uLow) - 0x1);
		nTemp = -nTemp;
	}
	else
	{
		uHight = bHight << 8;
		uLow = bLow;
		nTemp = uHight | uLow;
	}

	return nTemp;
}

void air::reply_slave_para(CByteArray* inbyte)
{
	int temp, temp1;
	int addr;
	//byte(3到5)是线控器设置的温度模式等
	//byte(6到9)是主机状态
	addr = inbyte->GetAt(3);
	if ((addr < 0) || (addr > 15))			//判断从机地址的有效性
		return;
	temp = inbyte->GetAt(4);
	//运行模式  0--停机 1--制冷 2--制热 3--自动
	//			4--除霜 5--调试
	indoor_air[addr].s_runmode = temp & 0x7;
	//风机1  0--停 1--低速 2--中速 3--高速
	temp1 = temp >> 3;
	indoor_air[addr].s_windmotor1 = temp1 & 0x3;
	//风机2  0--停 1--低速 2--中速 3--高速	
	temp1 = temp >> 5;
	indoor_air[addr].s_windmotor2 = temp1 & 0x3;

	//电磁阀1状态
	temp1 = temp >> 7;
	indoor_air[addr].s_ele_valve0 = temp1 & 0x1;
	temp = inbyte->GetAt(7);
	temp1 = temp >> 3;
	indoor_air[addr].s_ele_valve1 = temp1 & 0x1;
	temp1 = temp >> 4;
	indoor_air[addr].s_ele_valve2 = temp1 & 0x1;
	temp1 = temp >> 5;
	indoor_air[addr].s_ele_valve3 = temp1 & 0x1;
	//压缩机1状态 0--关 1--开
	temp = inbyte->GetAt(5);
	temp1 = temp >> 2;
	indoor_air[addr].s_compre[0] = temp1 & 0x1;
	//压缩机2状态 0--关 1--开
	temp1 = temp >> 3;
	indoor_air[addr].s_compre[1] = temp1 & 0x1;
	//压缩机3状态 0--关 1--开
	temp1 = temp >> 4;
	indoor_air[addr].s_compre[2] = temp1 & 0x1;
	//压缩机4状态 0--关 1--开
	temp1 = temp >> 5;
	indoor_air[addr].s_compre[3] = temp1 & 0x1;
	//压缩机5状态 0--关 1--开
	temp1 = temp >> 6;
	indoor_air[addr].s_compre[4] = temp1 & 0x1;
	//压缩机6状态 0--关 1--开
	temp1 = temp >> 7;
	indoor_air[addr].s_compre[5] = temp1 & 0x1;

	//四通阀1状态 0--关 1--开
	indoor_air[addr].s_fourvalve1 = temp & 0x1;
	//四通阀2状态 0--关 1--开
	temp1 = temp >> 1;
	indoor_air[addr].s_fourvalve2 = temp1 & 0x1;
	temp = inbyte->GetAt(8);
	temp1 = temp >> 4;
	indoor_air[addr].s_fourvalve3 = temp1 & 0x1;
	temp1 = temp >> 5;
	indoor_air[addr].s_fourvalve4 = temp1 & 0x1;
	temp = inbyte->GetAt(6);
	//辅热
	temp1 = temp >> 2;
	indoor_air[addr].s_ahot = temp1 & 0x1;
	//电磁阀2状态

	//总能力需求(单位HP)
	temp = inbyte->GetAt(38);
	//	temp1=inbyte->GetAt(27);
	//	temp1=temp1>>4;
	//	temp1=temp1&0x0F;
	indoor_air[addr].s_total_needed_HP = temp;
	//电磁膨胀阀1开度
	temp = inbyte->GetAt(9);
	indoor_air[addr].s_ele_distension_valve1 = temp * 2;
	//电磁膨胀阀2开度
	temp = inbyte->GetAt(10);
	indoor_air[addr].s_ele_distension_valve2 = temp * 2;
	//电磁膨胀阀3开度
	temp = inbyte->GetAt(11);
	indoor_air[addr].s_ele_distension_valve3 = temp * 2;
	//电磁膨胀阀4开度
	temp = inbyte->GetAt(12);
	indoor_air[addr].s_ele_distension_valve4 = temp * 2;

	//排气温度
	temp = inbyte->GetAt(13);
	temp1 = inbyte->GetAt(27);
	indoor_air[addr].s_tp1 = caldec_dlt(temp, temp1, 0);
	//环境温度
	temp = inbyte->GetAt(14);
	temp1 = inbyte->GetAt(28);
	indoor_air[addr].s_tp2 = caldec_dlt(temp, temp1, 0);
	//回气温度	
	temp = inbyte->GetAt(15);
	temp1 = inbyte->GetAt(28);
	indoor_air[addr].s_tp3 = caldec(temp, temp1, 0);
	//1#进盘温度
	temp = inbyte->GetAt(16);
	temp1 = inbyte->GetAt(29);
	indoor_air[addr].s_tp4 = caldec(temp, temp1, 1);
	//1#中盘温度
	temp = inbyte->GetAt(17);
	temp1 = inbyte->GetAt(29);
	indoor_air[addr].s_tp5 = caldec(temp, temp1, 0);
	//1#出盘温度
	temp = inbyte->GetAt(18);
	temp1 = inbyte->GetAt(30);
	indoor_air[addr].s_tp6 = caldec(temp, temp1, 1);
	//2#进盘温度
	temp = inbyte->GetAt(19);
	temp1 = inbyte->GetAt(30);
	indoor_air[addr].s_tp7 = caldec(temp, temp1, 0);
	//2#中盘温度
	temp = inbyte->GetAt(20);
	temp1 = inbyte->GetAt(31);
	indoor_air[addr].s_tp8 = caldec(temp, temp1, 1);
	//2#出盘温度
	temp = inbyte->GetAt(21);
	temp1 = inbyte->GetAt(31);
	indoor_air[addr].s_tp9 = caldec(temp, temp1, 0);
	//3#进盘温度
	temp = inbyte->GetAt(22);
	temp1 = inbyte->GetAt(32);
	indoor_air[addr].s_tp10 = caldec(temp, temp1, 1);
	//3#中盘温度
	temp = inbyte->GetAt(23);
	temp1 = inbyte->GetAt(32);
	indoor_air[addr].s_tp11 = caldec(temp, temp1, 0);
	//3#出盘温度
	temp = inbyte->GetAt(24);
	temp1 = inbyte->GetAt(33);
	indoor_air[addr].s_tp12 = caldec(temp, temp1, 1);

	temp = inbyte->GetAt(47);
	temp1 = inbyte->GetAt(49);
	indoor_air[addr].s_tp13 = caldec(temp, temp1, 0);    //TH13
	temp = inbyte->GetAt(48);
	indoor_air[addr].s_tp14 = caldec(temp, temp1, 1);    //TH14
	//高压
	temp = inbyte->GetAt(25);
	temp1 = inbyte->GetAt(34);
	temp1 = temp1 >> 4;
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_highpre = temp + (float)temp1 / 10;

	//低压
	temp = inbyte->GetAt(26);
	temp1 = inbyte->GetAt(34);
	temp1 = temp1 & 0x0F;
	indoor_air[addr].s_lowpre = temp + (float)temp1 / 10;


	//实际过热度					
	temp = inbyte->GetAt(35);
	temp1 = inbyte->GetAt(33);
	indoor_air[addr].s_factsuperhot = caldec(temp, temp1, 0);
	//系统2的实际过热度
	temp = inbyte->GetAt(36);
	temp1 = inbyte->GetAt(27);
	indoor_air[addr].s_factsuperhot2 = caldec(temp, temp1, 1);
	//目标过热度					
	temp = inbyte->GetAt(37);
	indoor_air[addr].s_targetsuperhot = temp;
	//HIC回路目标过冷度			
	temp = inbyte->GetAt(38);
	indoor_air[addr].s_targetsupercool = temp;

	int j;
	temp = inbyte->GetAt(39);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[j] = temp1 & 1;
	}
	temp = inbyte->GetAt(40);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[8 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(41);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[16 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(42);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[24 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(43);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].s_error[32 + j] = temp1 & 1;
	}
	temp = inbyte->GetAt(44);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].exs_err[j] = temp1 & 1;
	}
	temp = inbyte->GetAt(45);
	for (j = 0; j < 8; j++)
	{
		temp1 = temp >> j;
		indoor_air[addr].exs_err[j + 8] = temp1 & 1;
	}
	indoor_air[addr].water_exv_step = inbyte->GetAt(50);
	temp = inbyte->GetAt(51);
	indoor_air[addr].water_exv_step = indoor_air[addr].water_exv_step * 100 + temp;
	temp = inbyte->GetAt(52);
	temp1 = inbyte->GetAt(54);
	temp1 = temp1 & 0x0f;
	indoor_air[addr].s_hpre1 = temp + (float)temp1 / 10;
	temp = inbyte->GetAt(53);
	temp1 = inbyte->GetAt(54);
	temp1 = temp1 >> 4;
	temp1 = temp1 & 0x0f;
	indoor_air[addr].s_hpre2 = temp + (float)temp1 / 10;
	temp = inbyte->GetAt(56);
	temp1 = inbyte->GetAt(55);
	indoor_air[addr].S_BLDC_speed1 = temp * 255 + temp1;
	temp = inbyte->GetAt(58);
	temp1 = inbyte->GetAt(57);
	indoor_air[addr].S_BLDC_speed2 = temp * 255 + temp1;

}
void air::DataToTemp()
{
	s_delfrost_check_start_tp1 = s_delfrost_check_start_tp;
	s_delfrost_set_tp1 = s_delfrost_set_tp;
	s_delfrost_exit_tp1 = s_delfrost_exit_tp;
	s_delfrost_intertime1 = s_delfrost_intertime;
	s_delfrost_runtime1 = s_delfrost_runtime;
	s_delnoise_delaytime1 = s_delnoise_delaytime;
	s_ele_distension_valve11 = s_ele_distension_valve1;
	s_ele_distension_valve21 = s_ele_distension_valve2;
	s_ele_distension_valve31 = s_ele_distension_valve3;
	s_ele_distension_valve41 = s_ele_distension_valve4;
	s_f_ele_distension_valve11 = f_s_ele_distension_valve1;
	s_f_ele_distension_valve21 = f_s_ele_distension_valve2;
	s_f_ele_distension_valve31 = f_s_ele_distension_valve3;
	s_f_ele_distension_valve41 = f_s_ele_distension_valve4;
	S_DO1 = DO1;
	S_DO2 = DO2;
	S_DO3 = DO3;
	S_DO4 = DO4;
	S_DO15 = DO15;
	SF_DO1 = DOF1;
	s_windmotor11 = DO9;
	s_windmotor12 = DO10;
	s_windmotor22 = DO8;
	s_windmotor21 = DO7;
	s_f_windmotor11 = DOF9;
	s_f_windmotor12 = DOF10;
	s_f_windmotor22 = DOF8;
	s_f_windmotor21 = DOF7;
	s_compre1[0]=DO11;
	s_compre1[1] = DO12;
	s_sethp1 = DO13;
	s_f_compre1[0] = DOF11;
	s_f_compre1[1] = DOF12;
	s_fourvalve11 = DO5;
	s_fourvalve21 = DO6;
	s_f_fourvalve11 = DOF5;
	s_f_fourvalve21 = DOF6;
	s_targetsuperhot1 = s_targetsuperhot;
	s_movefac11 = s_movefac1;
	s_movefac21 = s_movefac2;
	s_p11 = s_p1;
	s_p21 = s_p2;
	s_p31 = s_p3;
	s_p41 = s_p4;
	s_p51 = s_p5;
	s_p61 = s_p6;
	s_p71 = s_p7;
	s_p81 = s_p8;

	s_antifreeze1 = s_antifreeze;
	s_winterantif1 = s_winterantif;

	s_fan_fre1 = s_fan1_real;//风机1频率
	s_fan_fre2 = s_fan2_real;//风机2频率
	s_fan_fre3 = s_fan3_real;//风机3频率
	s_fan_fre4 = s_fan4_real;//风机4频率

	s_comp_fre1 = s_comp1_real;//压缩机1频率
	s_comp_fre2 = s_comp2_real;//压缩机2频率
	s_comp_fre3 = s_comp3_real;//压缩机3频率
	s_comp_fre4 = s_comp4_real;//压缩机4频率
}
void air::modify_out_para_24(CByteArray* outbyte) //6号命令
{

	int temp, temp1;
	temp = 0;
	temp |= S_DO1 << 0;
	temp |= S_DO2 << 1;
	temp |= S_DO3 << 2;
	temp |= S_DO4 << 3;
	temp |= s_fourvalve11 <<4 ;	//系统1四通阀
	temp |= s_fourvalve21 <<5;	//系统2四通阀
	if (s_windmotor22 == 1)//系统1风机2高速
		temp1 = 1;
	else
		temp1 = 0;
	temp |= temp1 <<7;
	if (s_windmotor21 == 1)//系统1风机1高速
		temp1 = 1;
	else
		temp1 = 0;
	temp |= temp1 << 6;
	outbyte->SetAt(3, temp);

	temp = 0;
	if (s_windmotor11 == 1)//系统2风机1高速
		temp1 = 1;
	else
		temp1 = 0;
	temp |= temp1 << 0;
	if (s_windmotor12 == 1)//系统2风机2高速
		temp1 = 1;
	else
		temp1 = 0;
	temp |= temp1 << 1;
	temp |= s_compre1[0] <<2;
	temp |= s_compre1[1] <<3;
	temp |= s_sethp1 << 4;
	temp |= S_DO15 << 6;
	outbyte->SetAt(4, temp);

	temp = s_ele_distension_valve11 / 0x100;
	outbyte->SetAt(6, temp);

	temp = s_ele_distension_valve11 % 0x100;
	outbyte->SetAt(7, temp);

	temp = s_ele_distension_valve21 / 0x100;
	outbyte->SetAt(8, temp);

	temp = s_ele_distension_valve21 % 0x100;
	outbyte->SetAt(9, temp);

	temp = s_ele_distension_valve31 / 0x100;
	outbyte->SetAt(10, temp);

	temp = s_ele_distension_valve31 % 0x100;
	outbyte->SetAt(11, temp);

	temp = s_ele_distension_valve41 / 0x100;
	outbyte->SetAt(12, temp);

	temp = s_ele_distension_valve41 % 0x100;
	outbyte->SetAt(13, temp);
//副板数据写入
	temp = 0;
	temp |= SF_DO1 << 0;	//系统3四通阀
	temp |= s_f_fourvalve11 << 4;	//系统3四通阀
	temp |= s_f_fourvalve21 << 5;	//系统4四通阀

	
//系统1风机1高速
	temp |= s_f_windmotor21 << 6;
//系统1风机2高速
	temp |= s_f_windmotor22 << 7;
	outbyte->SetAt(14, temp);
	temp = 0;
//系统2风机1高速
	temp |= s_f_windmotor11 << 0;
//系统2风机2高速
	temp |= s_f_windmotor12 << 1;
	temp |= s_f_compre1[0] << 2;
	temp |= s_f_compre1[1] << 3;
	outbyte->SetAt(15, temp);
	temp = s_f_ele_distension_valve11 / 0x100;
	outbyte->SetAt(17, temp);

	temp = s_f_ele_distension_valve11 % 0x100;
	outbyte->SetAt(18, temp);

	temp = s_f_ele_distension_valve21 / 0x100;
	outbyte->SetAt(19, temp);

	temp = s_f_ele_distension_valve21 % 0x100;
	outbyte->SetAt(20, temp);

	temp = s_f_ele_distension_valve31 / 0x100;
	outbyte->SetAt(21, temp);

	temp = s_f_ele_distension_valve31 % 0x100;
	outbyte->SetAt(22, temp);

	temp = s_f_ele_distension_valve41 / 0x100;
	outbyte->SetAt(23, temp);

	temp = s_f_ele_distension_valve41 % 0x100;
	outbyte->SetAt(24, temp);
///////////主板频率
	temp = 0;
	outbyte->SetAt(25, temp);
	temp = s_fan_fre1;
	outbyte->SetAt(26, temp);

	temp = 0;
	outbyte->SetAt(27, temp);
	temp = s_fan_fre2;
	outbyte->SetAt(28, temp);

	temp = 0;
	outbyte->SetAt(29, temp);
	temp = 0;
	outbyte->SetAt(30, temp);

	temp = 0;
	outbyte->SetAt(31, temp);
	temp = 0;
	outbyte->SetAt(32, temp);

	temp = s_comp_fre1;
	outbyte->SetAt(33, temp);
	temp = s_comp_fre2;
	outbyte->SetAt(34, temp);
	temp = 0;
	outbyte->SetAt(35, temp);
	temp = 0;
	outbyte->SetAt(36, temp);
/////////////副板[频率
	temp = 0;
	outbyte->SetAt(37, temp);
	temp = s_fan_fre3;
	outbyte->SetAt(38, temp);

	temp = 0;
	outbyte->SetAt(39, temp);
	temp = s_fan_fre4;
	outbyte->SetAt(40, temp);

	temp = 0;
	outbyte->SetAt(41, temp);
	temp = 0;
	outbyte->SetAt(42, temp);

	temp = 0;
	outbyte->SetAt(43, temp);
	temp = 0;
	outbyte->SetAt(44, temp);

	temp = s_comp_fre3;
	outbyte->SetAt(45, temp);
	temp = s_comp_fre4;
	outbyte->SetAt(46, temp);
	temp = 0;
	outbyte->SetAt(47, temp);
	temp = 0;
	outbyte->SetAt(48, temp);
}
void air::reply_test_status(CByteArray* inbyte)
{

	int temp, temp1;
	int byte_count;
	//byte(3到5)是线控器设置的温度模式等
	//byte(6到9)是主机状态
	out_version = CheckNegative(inbyte->GetAt(3), inbyte->GetAt(4));

	//temp = inbyte->GetAt(5);
	////（拨码开关，0  OFF  1ON） 
	//sw11 = temp & 0x01;
	//temp1 = temp >> 1;
	//sw12 = temp1 & 0x01;
	//temp1 = temp >> 2;
	//sw13 = temp1 & 0x01;
	//temp1 = temp >> 3;
	//sw14 = temp1 & 0x01;
	//temp1 = temp >> 4;
	//sw15 = temp1 & 0x01;
	//temp1 = temp >> 5;
	//sw16 = temp1 & 0x01;
	//temp1 = temp >> 6;
	//sw17 = temp1 & 0x01;
	//temp1 = temp >> 7;
	//sw18= temp1 & 0x01;

	
	temp = inbyte->GetAt(5);
	DI1 = temp & 0x01;
	temp1 = temp >> 1;
	DI2 = temp1 & 0x01;
	temp1 = temp >> 2;
	DI3 = temp1 & 0x01;
	temp1 = temp >> 3;
	DI4 = temp1 & 0x01;
	temp1 = temp >> 4;
	DI5 = temp1 & 0x01;
	temp1 = temp >> 5;
	DI6 = temp1 & 0x01;
	temp1 = temp >> 6;
	DI7 = temp1 & 0x01;
	temp1 = temp >> 7;
	DI8 = temp1 & 0x01;

	temp = inbyte->GetAt(6);
	DI9 = temp & 0x01;
	temp1 = temp >> 1;
	DI10 = temp1 & 0x01;
	temp1 = temp >> 2;
	DI11 = temp1 & 0x01;
	temp1 = temp >> 3;
	DI12 = temp1 & 0x01;

	temp = inbyte->GetAt(7);
	DIF1 = temp & 0x01;
	temp1 = temp >> 1;
	DIF2 = temp1 & 0x01;

}