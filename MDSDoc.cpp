// MDSDoc.cpp : implementation of the CMDSDoc class
//

#include "stdafx.h"
#include "MDS.h"

#include "MDSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDSDoc
CMSComm	m_comm1;
IMPLEMENT_DYNCREATE(CMDSDoc, CDocument)

BEGIN_MESSAGE_MAP(CMDSDoc, CDocument)
	//{{AFX_MSG_MAP(CMDSDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDSDoc construction/destruction

CMDSDoc::CMDSDoc()
{
	// TODO: add one-time construction code here
	airnum=1;		//机组数量
	m_startflag=0;//初始化标志
	m_commNo=1;
	m_commband=5;
	m_connectflag=0;	//连接标志
	crc=0;
	temp=0;
	queryAirNo=0;	//要当前查询的机组号
	querySAirNo=0;	//要当前查询的从机机组号
	queryFunNo=23; //查询的功能号
	queryAirNo1=0;//保存当前查询的机组号
	queryFunNo1=23; //保存查询的功能号
	sendcmdflag=0;
	m_errorcount=0;

//	m_inair.i_ctl_workmode=1;
//	m_inair.i_ctl_settp=16;

	m_timer1runtime=0;
	m_timer2runtime=0;
	m_timer3runtime=0;
	m_timer4runtime=0;
	m_timer5runtime=0;
	m_timer6runtime=0;

	m_timername[0]="计时1:";
	m_timername[1]="计时2:";
	m_timername[2]="计时3:";
	m_timername[3]="计时4:";
	m_timername[4]="计时5:";
	m_timername[5]="计时6:";
//	for(int i=0;i<32;i++)
//			m_file[i]=NULL;
//	ftestfile=NULL;
}

CMDSDoc::~CMDSDoc()
{
}

BOOL CMDSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMDSDoc serialization

void CMDSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMDSDoc diagnostics

#ifdef _DEBUG
void CMDSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMDSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDSDoc commands

//打开串口
void CMDSDoc::set_comm()
{
	int band[6]={600,1200,2400,4800,9600,19200};	
	CString tempstr;
	tempstr.Format("%d,n,8,1",band[m_commband]);//修改
	m_comm1.SetSettings(tempstr);
    m_comm1.SetRThreshold(0);
    m_comm1.SetInputLen(0);
	m_comm1.SetCommPort(m_commNo);
	m_comm1.SetInputMode(1);
	if(!m_comm1.GetPortOpen())
		m_comm1.SetPortOpen(1);	
}
//CRC校验计算
UINT calcrc(CByteArray* bytebuf)
{
    BYTE temp;
	BYTE i;
	UINT crc=0xffff;
	for(int c=0;c<bytebuf->GetSize()-2;c++)
	{
		temp=bytebuf->GetAt(c);
		crc=crc^temp;
		for(i=0;i<8;i++)
		{
			BYTE TT;
			TT=crc&1;
			crc=crc>>1;
			crc=crc&0x7fff;
			if (TT==1)
				crc=crc^0xa001;
			crc=crc&0xffff;
		}
	}
	return crc;
}

//查询外机配置
void CMDSDoc::query_out_set(int airNo)
{
	int ret;
	outbuf.SetSize(8);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0] = airNo + 1;							//PC直接接外机标志
	outbuf[1] = 0x04;                         //功能代码
	outbuf[2] = 0x00;//0x00;							//00 c8 表示从30199开始的地址
	outbuf[3] = 0x01;//0xc7;						//
	outbuf[4] = 0x00;
	outbuf[5] = 0x28;

	crc = calcrc(&outbuf);
	temp = crc & 0x00ff;
	outbuf[6] = temp;
	temp = crc & 0xff00;
	temp = temp >> 8;
	outbuf[7] = temp;
	varOutput = outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);	

	outbuf.SetSize(100);
	varOutput=outbuf; 
}

//查询内机配置
void CMDSDoc::query_in_set(int airNo)
{
	int ret;
	outbuf.SetSize(8);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0] = airNo + 1;							//PC直接接外机标志
	outbuf[1] = 0x02;                         //功能代码
	outbuf[2] = 0x00;//0x00;							//00 c8 表示从30199开始的地址
	outbuf[3] = 0x01;//0xc7;						//
	outbuf[4] = 0x00;
	outbuf[5] = 0x0C;
	crc = calcrc(&outbuf);
	temp = crc & 0x00ff;
	outbuf[6] = temp;
	temp = crc & 0xff00;
	temp = temp >> 8;
	outbuf[7] = temp;
	varOutput = outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);

	outbuf.SetSize(100);
	varOutput=outbuf; 
}

//查询机组运行状态
void CMDSDoc::query_air_status(int airNo)
{
	outbuf.SetSize(8);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0] = airNo + 1;							//PC直接接外机标志
	outbuf[1] = 0x04;                         //功能代码
	outbuf[2] = 0x00;//0x00;							//00 c8 表示从30199开始的地址
	outbuf[3] = 0x41;//			
	outbuf[4] = 0x00;
	outbuf[5] = 0x6;
	crc = calcrc(&outbuf);
	temp = crc & 0x00ff;
	outbuf[6] = temp;
	temp = crc & 0xff00;
	temp = temp >> 8;
	outbuf[7] = temp;
	varOutput = outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);

	outbuf.SetSize(100);
	varOutput = outbuf;
}

//查询测试模式的输出状态
void CMDSDoc::query_test_status(int airNo)
{
	outbuf.SetSize(8);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0] = airNo + 1;							//PC直接接外机标志
	outbuf[1] = 0x04;                         //功能代码
	outbuf[2] = 0x00;//0x00;							//00 c8 表示从30199开始的地址
	outbuf[3] = 0x59;//			
	outbuf[4] = 0x00;
	outbuf[5] = 0x5;
	crc = calcrc(&outbuf);
	temp = crc & 0x00ff;
	outbuf[6] = temp;
	temp = crc & 0xff00;
	temp = temp >> 8;
	outbuf[7] = temp;
	varOutput = outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);

	outbuf.SetSize(100);
	varOutput=outbuf; 
}

//查询从机运行参数
void CMDSDoc::query_out_para(int airNo)
{
	outbuf.SetSize(6);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=airNo;						//PC直接接外机标志
	outbuf[1]=0x04;                         //功能代码
	outbuf[2]=1;							//字节长度
	outbuf[3]=airlist[airNo].in_groupquery;	//从机地址
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[4]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[5]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
	outbuf.SetSize(100);
	varOutput=outbuf; 
}

//查询内机运行参数
void CMDSDoc::query_in_para(int airNo)
{
	outbuf.SetSize(7);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=0xff;							//PC直接接外机标志
	outbuf[1]=0x05;                         //功能代码
	outbuf[2]=2;							//字节长度
	outbuf[3]=airNo;						//外机地址
	outbuf[4]=airlist[airNo].in_groupquery;	//内机组别
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[5]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[6]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
	
	outbuf.SetSize(100);
	varOutput=outbuf; 
}
//修改外机配置参数
void CMDSDoc::modify_out_para(int airNo)
{
	int slave_no;
	outbuf.SetSize(35);					    //外机地址
	outbuf[0]=airNo;						//PC直接接外机标志
	outbuf[1]=0x06;                         //功能代码
	outbuf[2]=30;							//字节长度
	outbuf[3]=airlist[airNo].unit_no;							
//	airlist[airNo].modify_out_para(&outbuf);
	if(airlist[airNo].unit_no==0xff)
		airlist[airNo].modify_out_para(&outbuf);
	else
	{
		slave_no=airlist[airNo].unit_no;
		airlist[airNo].modify_out_para_s(slave_no,&outbuf);	
	}
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[33]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[34]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
}

//开关部分内机运行控制命令   7号命令
void CMDSDoc::send_oc_inair(int airNo)
{
	BYTE temp1,temp2;

	outbuf.SetSize(8);			    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=airNo;				//外机地址
	outbuf[1]=0x07;                 //功能代码
	outbuf[2]=3;					//字节长度						

	temp2=airlist[airNo].i_ctl_workmode;
	temp2=temp2<<5;
	temp2&=0xE0;
	outbuf[3]=temp2;
	temp2=airlist[airNo].i_ctl_coolsetin;  //制冷进水设置
	temp2&=0x1f;
	outbuf[3]|=temp2;
			
	temp2=airlist[airNo].i_ctl_open;
	temp2=temp2&0x1;
	temp2=temp2<<7;
	outbuf[4]=temp2;
	temp2=airlist[airNo].i_ctl_heatsetin; //制热进水设置
	temp2&=0x1f;
	outbuf[4]|=temp2;

	temp2=airlist[airNo].m_ctrl_hotset; //制热进水设置
	outbuf[5]=temp2;

    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[6]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[7]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutput(varOutput);
}

//开关全部内机运行控制命令
void CMDSDoc::send_oc_allinair(int airNo)
{
/*	BYTE temp1,temp2;
	outbuf.SetSize(8);			    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=0xff;							//PC直接接外机标志
	outbuf[1]=0x08;                         //功能代码
	outbuf[2]=3;						//字节长度
	outbuf[3]=airNo;						//外机地址

	temp1=m_inair.i_ctl_settp;
	temp1&=0x1F;
	temp2=m_inair.i_ctl_workmode;
	temp2=temp2<<5;
	temp2&=0xE0;
	outbuf[4]=temp1|temp2;

	temp1=m_inair.i_ctl_wind_speed;
	temp1&=0x03;
	temp2=m_inair.i_ctl_wind;
	temp2=temp2&0x1;
	temp2=temp2<<2;
	temp1|=temp2;
	temp2=m_inair.i_ctl_sleep;
	temp2=temp2&0x1;
	temp2=temp2<<3;
	temp1|=temp2;
	temp2=m_inair.i_ctl_ass_hot;
	temp2=temp2&0x1;
	temp2=temp2<<4;
	temp1|=temp2;
	temp2=m_inair.i_ctl_hand_defrost;
	temp2=temp2&0x1;
	temp2=temp2<<5;
	temp1|=temp2;
	temp2=m_inair.i_ctl_lock;
	temp2=temp2&0x1;
	temp2=temp2<<6;
	temp1|=temp2;
	temp2=m_inair.i_ctl_open;
	temp2=temp2&0x1;
	temp2=temp2<<7;
	temp1|=temp2;
	outbuf[5]=temp1;
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[6]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[7]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutput(varOutput);*/
	;
}

void CMDSDoc::send_defro_spe(int airNo)			//手动除霜特殊运行控制命令
{
	outbuf.SetSize(6);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=airNo;							//PC直接接外机标志
	outbuf[1]=0x09;                         //功能代码
	outbuf[2]=1;							//字节长度
	outbuf[3]=0xff;						//外机地址
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[4]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[5]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
void CMDSDoc::seng_openvalve_spe(int airNo)		//调试时开阀控制命令
{
	outbuf.SetSize(6);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=airNo;							//PC直接接外机标志
	outbuf[1]=0x0A;                         //功能代码
	outbuf[2]=1;							//字节长度
	outbuf[3]=0xff;							//外机地址
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[4]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[5]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
void CMDSDoc::seng_maskin_spe(int airNo)
{
	BYTE temp1,temp2;
	outbuf.SetSize(12);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=0xff;							//PC直接接外机标志
	outbuf[1]=0x0B;                         //功能代码
	outbuf[2]=7;							//字节长度
	outbuf[3]=airNo;						//外机地址
	for(int i=0;i<48;i++)
	{
		if(i%8==0)
			temp1=0;
		temp2=m_maskflag[i];
		temp2&=0x1;
		temp2<<=i%8;
		temp1|=temp2;
		outbuf[i/8+4]=temp1;
	}
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[10]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[11]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
void CMDSDoc::query_code_set()	//测试拨码
{
	outbuf.SetSize(5);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=0xff;							//PC直接接外机标志
	outbuf[1]=0x20;                         //功能代码
	outbuf[2]=0;							//字节长度
	crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[3]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[4]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
void CMDSDoc::query_exit_mode(int airNo)
{
	outbuf.SetSize(6);					    //设置输出字节大小，构造MODBUS数据格式
	outbuf[0]=0;							//PC直接接外机标志
	outbuf[1]=0x17;                         //功能代码
	outbuf[2]=0x1;							//字节长度
	outbuf[3]=0x00;	//外机地址
	
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[4]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[5]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
//读压缩机累计运行时间
void CMDSDoc::query_comp_time(int airNo)
{
	outbuf.SetSize(6);					    
	outbuf[0]=0;							
	outbuf[1]=0x17;                       
	outbuf[2]=0x1;							
	outbuf[3]=0xff;	
	
    crc=calcrc(&outbuf);
	temp=crc&0x00ff;
	outbuf[4]=temp;
	temp=crc&0xff00;
	temp=temp>>8;		
	outbuf[5]=temp;
	varOutput=outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
//24号命令，设置参数
void CMDSDoc::clear_eePROM(int airNo)
{
	//int slave_no;
	//outbuf.SetSize(27);					    //外机地址
	//outbuf[0]=0;						//PC直接接外机标志
	//outbuf[1]=0x18;                         //功能代码
	//outbuf[2]=0x16;							//字节长度

	//airlist[airNo].modify_out_para_24(&outbuf);
 //   crc=calcrc(&outbuf);
	//temp=crc&0x00ff;
	//outbuf[25]=temp;
	//temp=crc&0xff00;
	//temp=temp>>8;		
	//outbuf[26]=temp;
	//varOutput=outbuf;
	//m_comm1.SetInBufferCount(0);
	//m_comm1.SetOutBufferCount(0);
	//m_comm1.SetOutput(varOutput);

	int slave_no;
	outbuf.SetSize(51);					    //外机地址
	outbuf[0] = 0;						//PC直接接外机标志
	outbuf[1] = 0x18;                         //功能代码
	outbuf[2] = 46;							//字节长度

	airlist[airNo].modify_out_para_24(&outbuf);
	crc = calcrc(&outbuf);
	temp = crc & 0x00ff;
	outbuf[49] = temp;
	temp = crc & 0xff00;
	temp = temp >> 8;
	outbuf[50] = temp;
	varOutput = outbuf;
	m_comm1.SetInBufferCount(0);
	m_comm1.SetOutBufferCount(0);
	m_comm1.SetOutput(varOutput);
}
//从串口得到数据并校验，返回功能号，返回0收到数据不正确
int CMDSDoc::getcommdata(CByteArray* inbyte)
{
	COleVariant olearray;
	int reply=0;
	UINT crc=0;
	int ncount=m_comm1.GetInBufferCount();
	if(ncount==0)
		return reply;
	inbyte->SetSize(ncount);
	olearray.Attach(m_comm1.GetInput()); 
	for(int i=0;i<ncount;i++)
		inbyte->SetAt(i,((unsigned char*)olearray.parray->pvData)[i]);
	//此处要加一数据解密函数
	int temp1,temp2;
	crc=calcrc(inbyte);
	temp1=crc&0x00ff;	
	temp2=crc&0xff00;
	temp2=temp2>>8;
	//xu170216
	if (ncount<2)
		return reply;
	if(inbyte->GetAt(ncount-2)!=temp1||inbyte->GetAt(ncount-1)!=temp2)
		reply=0;
	else if ((inbyte->GetAt(1) == 0x04) && (inbyte->GetAt(2) == 80))//读命令12循环命令
	{
		reply = 1;
	}
	else if ((inbyte->GetAt(1) == 0x04) && (inbyte->GetAt(2) == 12))//读命令12循环命令
	{
		reply = 3;
	}
	else if ((inbyte->GetAt(1) == 0x02) && (inbyte->GetAt(2) == 2))//读命令12循环命令
	{
		reply = 2;
	}
	else if ((inbyte->GetAt(1) == 0x04) && (inbyte->GetAt(2) == 10))//读命令12循环命令
	{
		reply = 25;
	}
	else
		reply=inbyte->GetAt(1);
	return reply;
}

//响应外机配置
int CMDSDoc::reply_out_set(CByteArray* inbyte)
{
	int address=inbyte->GetAt(0)-1;
	if(address<0||address>31||address!=queryAirNo)
		return 0;
	airlist[address].reply_out_set(inbyte);
	return 1;

}

//响应内机配置  //现在为响应从机配置
int CMDSDoc::reply_in_set(CByteArray* inbyte)
{
	int address=inbyte->GetAt(0)-1;
	if(address<0||address>31||address!=queryAirNo)
		return 0;
	airlist[address].reply_in_set(inbyte);
	return 1;
}

//响应机组运行状态 //主机运行参数
int CMDSDoc::reply_air_status(CByteArray* inbyte)
{
	int address=inbyte->GetAt(0)-1;
	if(address<0||address>31||address!=queryAirNo)
		return 0;
	airlist[address].reply_air_status(inbyte);
	return 1;
}

//响应测试模式输出状态
int CMDSDoc::reply_test_status(CByteArray* inbyte)
{
	int address=inbyte->GetAt(0)-1;
	if(address<0||address>31)
		return 0;
	airlist[address].reply_test_status(inbyte);
	return 1;
}

//响应外机运行参数  从机运行参数
int CMDSDoc::reply_out_para(CByteArray* inbyte)
{
	int address=inbyte->GetAt(0);
	if(address<0||address>31||address!=queryAirNo)
		return 0;
	airlist[address].in_groupquery=inbyte->GetAt(3);
	airlist[address].reply_out_para(inbyte);
	if(airlist[address].in_groupquery<airlist[address].in_num-1)
	{
		airlist[address].in_groupquery++;
		return 2;
	}
	else
	{
		airlist[address].in_groupquery=0;
		return 1;
	}
	return 1;
}

//响应内机运行参数
int CMDSDoc::reply_in_para(CByteArray* inbyte)
{
	int address=inbyte->GetAt(3);
	if(address<0||address>31||address!=queryAirNo)
		return 0;
	airlist[address].in_groupquery=inbyte->GetAt(4);
	airlist[address].reply_in_para(inbyte);
	if(airlist[address].in_groupquery<airlist[address].in_group)
	{
		airlist[address].in_groupquery++;
		return 2;
	}
	else
	{
		airlist[address].in_groupquery=0;
		return 1;
	}
	return 1;
}

int CMDSDoc::reply_mofify_out_para(CByteArray* inbyte)
{
	int address=inbyte->GetAt(0);
	if(address<0||address>16||address!=queryAirNo)
		return 0;
	if(querySAirNo==0)
		airlist[address].modify_out_para1();
	else
		airlist[address].modify_sout_para1();
	return 1;
}

int CMDSDoc::reply_comp_time(CByteArray* inbyte)	//响应读压缩机累计运行时间
{
	int address=inbyte->GetAt(0);
	if(address<0||address>32||address!=queryAirNo)
		return 0;
	airlist[address].in_groupquery=inbyte->GetAt(3);
	airlist[address].reply_comp_time(inbyte);
	if(airlist[address].in_groupquery<airlist[address].in_num-1)
	{
		airlist[address].in_groupquery++;
		return 2;
	}
	else
	{
		if(airlist[address].in_groupquery==0xff)
		{
			airlist[address].in_groupquery=0;
			return 1;
		}
		else
		{
			airlist[address].in_groupquery=0xff;
			return 2;
		}
	}
	return 1;
}
