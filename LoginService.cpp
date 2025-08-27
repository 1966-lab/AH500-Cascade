#include "StdAfx.h"
#include "LoginService.h"


LoginService::LoginService(void):
              strUsername(""),
			  strPassword(""),
			  strModelImel(""),
			  strUnitname(""),
			  strUnitorder(""),
			  strUnittime(""),
			  strUrl("www.ek-cloud.net")
{
}

LoginService::LoginService(const CString strName, const CString strPass, const CString strImel, const CString strUnit, const CString strOrder, const CString strTime):
			  strUrl("www.ek-cloud.net")
{
	strUsername = strName;
	strPassword = strPass;
	strModelImel = strImel;
	strUnitname =strUnit;
	strUnitorder=strOrder;
	strUnittime=strTime;
	//pHttpClient = new HttpClient;     //!http方式登录
	//pHttpClient = new SocketClient;   //!socket方式登录
	pHttpClient = new HttpsClient;      //!https方式登录
}

LoginService::~LoginService(void)
{
}
#ifdef VIEW_MESS
void LoginService::ShowInformation(CString &InforStr)//显示信息框；
{
	WaitingPDf = new waitpdf;

	WaitingPDf->Create(IDD_WAITPDF);


	WaitingPDf->RefreshString(InforStr);
	WaitingPDf->MoveWindow(130,130,300,100);
	WaitingPDf->ShowWindow(1);
	WaitingPDf->UpdateWindow();	
	return;
}
#endif

BOOL LoginService::Login()
{
	BOOL bRet = FALSE;
	do 
	{
		if (NULL == pHttpClient)
		{
			break;
		}
#ifdef VIEW_MESS
		CString Hintstr;
		Hintstr="准备链接";
	    ShowInformation(Hintstr);
#endif
		if (!pHttpClient->ConnectToServer(strUrl, 443))
		{
			break;
		}
		TRACE("链接成功\n");
#ifdef VIEW_MESS
		Hintstr="准备取TOKEN";
	    ShowInformation(Hintstr);
#endif
		//get 方法取到TOKEN
		if (!pHttpClient->LoginToServer(strUsername, strPassword))
		{
			break;
		}
		TRACE("方法取到TOKEN\n");
#ifdef VIEW_MESS
		Hintstr="请求增加网关";
	    ShowInformation(Hintstr);
#endif
		//post 请求增加网关
		if (!pHttpClient->LoginToServerForAddGateway(strUsername, strPassword,strModelImel,strUnitname+strUnitorder+strUnittime))
		{
			if (!pHttpClient->LoginToServerForCheckGateway(strUsername, strPassword,strModelImel,strUnitname+strUnitorder+strUnittime))
			{
			   break;
			}
		}
		TRACE("请求增加网关\n");
#ifdef VIEW_MESS
		Hintstr="启动硬件网关";
	    ShowInformation(Hintstr);	
#endif
		//post 请求	启动硬件网关
		if (!pHttpClient->LoginToServerForStartGateway(strUsername, strPassword))
		{
			break;
		}
		TRACE("启动硬件网关\n");
#ifdef VIEW_MESS
		Hintstr="请求获得设备模板列表";
	    ShowInformation(Hintstr);	
#endif
		// post 请求获得设备模板列表
		if (!pHttpClient->LoginToServerForModelId(strUsername, strPassword))
		{
			break;
		}
		TRACE("请求获得设备模板列表\n");
#ifdef VIEW_MESS
		Hintstr="添加硬件设备";
	    ShowInformation(Hintstr);	
#endif
		// post	添加硬件设备
		if (!pHttpClient->LoginToServerForAddDevice(strUsername, strPassword,strUnitname,strUnitorder,strUnittime))
		{
			if (!pHttpClient->LoginToServerForCheckDevice(strUsername, strPassword,strUnitname,strUnitorder,strUnittime))
			{
			  break;
			}
		}
		TRACE("添加硬件设备\n");
//add by xg
#ifdef VIEW_MESS
		Hintstr="启动硬件";
	    ShowInformation(Hintstr);	
#endif
		//post 请求	启动硬件
		if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
		{
			break;
		}
		TRACE("启动硬件\n");

		//post 请求	获取信号强度 KP1
	/*	if (!pHttpClient->LoginToServerForDeviceKpi_RSSI(strUsername, strPassword))
		{
			int flag=0;
			int sumnumber=0;
			while(1)
			{
				#ifdef VIEW_MESS
				Hintstr.Format("没有获得信号KPI次数%d",sumnumber);
				ShowInformation(Hintstr);	
				#endif
				Sleep(3000);
				if (pHttpClient->LoginToServerForDeviceKpi_RSSI(strUsername, strPassword))
				{
					flag=1;//获取到信号强度KPI退出去
					break;
				}
				else
					sumnumber++;//没有找到，累计

				if(sumnumber>5) {
					//post 请求	启动硬件
					if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
					{
						break;
					}
					sumnumber = 0;
				}
			}

		}*/

#ifdef VIEW_MESS
		Hintstr="添加下发配置";
	    ShowInformation(Hintstr);	
#endif
		// post	添加下发配置
		if (!pHttpClient->LoginToServerForSendConfig(strUsername, strPassword,strUnitname,strUnitorder))
		{
			break;
		}
		TRACE("添加下发配置\n");

		//post 请求	启动硬件
		//if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
		//{
		//	break;
		//}
		//TRACE("启动硬件\n");

		//post 请求	获取设备KP1
/*		if (!pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
		{
			int flag=0;
			int sumnumber=0;
			while(1)
			{
				#ifdef VIEW_MESS
				Hintstr.Format("没有获得设备KPI次数%d",sumnumber);
				ShowInformation(Hintstr);	
				#endif
				TRACE("没有获得设备KPI次数%d\n",sumnumber);
				Sleep(10000);
				if (pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
				{
					flag=1;//获取到KPI退出去
					break;
				}
				else
					sumnumber++;//没有找到，累计

				if(sumnumber>10) {
					// post	添加下发配置
					if (!pHttpClient->LoginToServerForSendConfig(strUsername, strPassword,strUnitname,strUnitorder))
					{
						break;
					}
					TRACE("再次添加下发配置\n");

					//post 请求	启动硬件
					if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
					{
						break;
					}
					TRACE("再次启动硬件\n");
					sumnumber = 0;
				}
			}
			if(flag==1)
				bRet = TRUE;
			else
				bRet = FALSE;
			TRACE("多次获得设备KPI");
			break;
		}
		TRACE("第一次就获得设备KPI");
*/
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL LoginService::Logout()
{
	return TRUE;
}
BOOL LoginService::LoginKpi()
{
	BOOL bRet = FALSE;
	do 
	{
		if (NULL == pHttpClient)
		{
			break;
		}
#ifdef VIEW_MESS
		CString Hintstr;
		Hintstr="准备链接";
	    ShowInformation(Hintstr);
#endif
		if (!pHttpClient->ConnectToServer(strUrl, 443))
		{
			break;
		}
		TRACE("链接成功\n");
#ifdef VIEW_MESS
		Hintstr="准备取TOKEN";
	    ShowInformation(Hintstr);
#endif
		//get 方法取到TOKEN
		if (!pHttpClient->LoginToServer(strUsername, strPassword))
		{
			break;
		}
		TRACE("方法取到TOKEN\n");
		//post 请求	获取设备KP1
		if (!pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
		{
			int flag=0;
			int sumnumber=0;
			while(1)
			{
				#ifdef VIEW_MESS
				Hintstr.Format("没有获得设备KPI次数%d",sumnumber);
				ShowInformation(Hintstr);	
				#endif
				TRACE("没有获得设备KPI次数%d\n",sumnumber);
				Sleep(10000);
				if (pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
				{
					flag=1;//获取到KPI退出去
					break;
				}
				else
					sumnumber++;//没有找到，累计

				if(sumnumber>10) {
					// post	添加下发配置
					if (!pHttpClient->LoginToServerForSendConfig(strUsername, strPassword,strUnitname,strUnitorder))
					{
						break;
					}
					TRACE("再次添加下发配置\n");

					//post 请求	启动硬件
					if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
					{
						break;
					}
					TRACE("再次启动硬件\n");
					sumnumber = 0;
				}
			}
			if(flag==1)
				bRet = TRUE;
			else
				bRet = FALSE;
			TRACE("多次获得设备KPI");
			break;
		}
		TRACE("第一次就获得设备KPI");

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}
