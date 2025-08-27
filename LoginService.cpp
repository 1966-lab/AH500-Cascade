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
	//pHttpClient = new HttpClient;     //!http��ʽ��¼
	//pHttpClient = new SocketClient;   //!socket��ʽ��¼
	pHttpClient = new HttpsClient;      //!https��ʽ��¼
}

LoginService::~LoginService(void)
{
}
#ifdef VIEW_MESS
void LoginService::ShowInformation(CString &InforStr)//��ʾ��Ϣ��
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
		Hintstr="׼������";
	    ShowInformation(Hintstr);
#endif
		if (!pHttpClient->ConnectToServer(strUrl, 443))
		{
			break;
		}
		TRACE("���ӳɹ�\n");
#ifdef VIEW_MESS
		Hintstr="׼��ȡTOKEN";
	    ShowInformation(Hintstr);
#endif
		//get ����ȡ��TOKEN
		if (!pHttpClient->LoginToServer(strUsername, strPassword))
		{
			break;
		}
		TRACE("����ȡ��TOKEN\n");
#ifdef VIEW_MESS
		Hintstr="������������";
	    ShowInformation(Hintstr);
#endif
		//post ������������
		if (!pHttpClient->LoginToServerForAddGateway(strUsername, strPassword,strModelImel,strUnitname+strUnitorder+strUnittime))
		{
			if (!pHttpClient->LoginToServerForCheckGateway(strUsername, strPassword,strModelImel,strUnitname+strUnitorder+strUnittime))
			{
			   break;
			}
		}
		TRACE("������������\n");
#ifdef VIEW_MESS
		Hintstr="����Ӳ������";
	    ShowInformation(Hintstr);	
#endif
		//post ����	����Ӳ������
		if (!pHttpClient->LoginToServerForStartGateway(strUsername, strPassword))
		{
			break;
		}
		TRACE("����Ӳ������\n");
#ifdef VIEW_MESS
		Hintstr="�������豸ģ���б�";
	    ShowInformation(Hintstr);	
#endif
		// post �������豸ģ���б�
		if (!pHttpClient->LoginToServerForModelId(strUsername, strPassword))
		{
			break;
		}
		TRACE("�������豸ģ���б�\n");
#ifdef VIEW_MESS
		Hintstr="���Ӳ���豸";
	    ShowInformation(Hintstr);	
#endif
		// post	���Ӳ���豸
		if (!pHttpClient->LoginToServerForAddDevice(strUsername, strPassword,strUnitname,strUnitorder,strUnittime))
		{
			if (!pHttpClient->LoginToServerForCheckDevice(strUsername, strPassword,strUnitname,strUnitorder,strUnittime))
			{
			  break;
			}
		}
		TRACE("���Ӳ���豸\n");
//add by xg
#ifdef VIEW_MESS
		Hintstr="����Ӳ��";
	    ShowInformation(Hintstr);	
#endif
		//post ����	����Ӳ��
		if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
		{
			break;
		}
		TRACE("����Ӳ��\n");

		//post ����	��ȡ�ź�ǿ�� KP1
	/*	if (!pHttpClient->LoginToServerForDeviceKpi_RSSI(strUsername, strPassword))
		{
			int flag=0;
			int sumnumber=0;
			while(1)
			{
				#ifdef VIEW_MESS
				Hintstr.Format("û�л���ź�KPI����%d",sumnumber);
				ShowInformation(Hintstr);	
				#endif
				Sleep(3000);
				if (pHttpClient->LoginToServerForDeviceKpi_RSSI(strUsername, strPassword))
				{
					flag=1;//��ȡ���ź�ǿ��KPI�˳�ȥ
					break;
				}
				else
					sumnumber++;//û���ҵ����ۼ�

				if(sumnumber>5) {
					//post ����	����Ӳ��
					if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
					{
						break;
					}
					sumnumber = 0;
				}
			}

		}*/

#ifdef VIEW_MESS
		Hintstr="����·�����";
	    ShowInformation(Hintstr);	
#endif
		// post	����·�����
		if (!pHttpClient->LoginToServerForSendConfig(strUsername, strPassword,strUnitname,strUnitorder))
		{
			break;
		}
		TRACE("����·�����\n");

		//post ����	����Ӳ��
		//if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
		//{
		//	break;
		//}
		//TRACE("����Ӳ��\n");

		//post ����	��ȡ�豸KP1
/*		if (!pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
		{
			int flag=0;
			int sumnumber=0;
			while(1)
			{
				#ifdef VIEW_MESS
				Hintstr.Format("û�л���豸KPI����%d",sumnumber);
				ShowInformation(Hintstr);	
				#endif
				TRACE("û�л���豸KPI����%d\n",sumnumber);
				Sleep(10000);
				if (pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
				{
					flag=1;//��ȡ��KPI�˳�ȥ
					break;
				}
				else
					sumnumber++;//û���ҵ����ۼ�

				if(sumnumber>10) {
					// post	����·�����
					if (!pHttpClient->LoginToServerForSendConfig(strUsername, strPassword,strUnitname,strUnitorder))
					{
						break;
					}
					TRACE("�ٴ�����·�����\n");

					//post ����	����Ӳ��
					if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
					{
						break;
					}
					TRACE("�ٴ�����Ӳ��\n");
					sumnumber = 0;
				}
			}
			if(flag==1)
				bRet = TRUE;
			else
				bRet = FALSE;
			TRACE("��λ���豸KPI");
			break;
		}
		TRACE("��һ�ξͻ���豸KPI");
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
		Hintstr="׼������";
	    ShowInformation(Hintstr);
#endif
		if (!pHttpClient->ConnectToServer(strUrl, 443))
		{
			break;
		}
		TRACE("���ӳɹ�\n");
#ifdef VIEW_MESS
		Hintstr="׼��ȡTOKEN";
	    ShowInformation(Hintstr);
#endif
		//get ����ȡ��TOKEN
		if (!pHttpClient->LoginToServer(strUsername, strPassword))
		{
			break;
		}
		TRACE("����ȡ��TOKEN\n");
		//post ����	��ȡ�豸KP1
		if (!pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
		{
			int flag=0;
			int sumnumber=0;
			while(1)
			{
				#ifdef VIEW_MESS
				Hintstr.Format("û�л���豸KPI����%d",sumnumber);
				ShowInformation(Hintstr);	
				#endif
				TRACE("û�л���豸KPI����%d\n",sumnumber);
				Sleep(10000);
				if (pHttpClient->LoginToServerForDeviceKpi(strUsername, strPassword))
				{
					flag=1;//��ȡ��KPI�˳�ȥ
					break;
				}
				else
					sumnumber++;//û���ҵ����ۼ�

				if(sumnumber>10) {
					// post	����·�����
					if (!pHttpClient->LoginToServerForSendConfig(strUsername, strPassword,strUnitname,strUnitorder))
					{
						break;
					}
					TRACE("�ٴ�����·�����\n");

					//post ����	����Ӳ��
					if (!pHttpClient->LoginToServerForStartDevice(strUsername, strPassword))
					{
						break;
					}
					TRACE("�ٴ�����Ӳ��\n");
					sumnumber = 0;
				}
			}
			if(flag==1)
				bRet = TRUE;
			else
				bRet = FALSE;
			TRACE("��λ���豸KPI");
			break;
		}
		TRACE("��һ�ξͻ���豸KPI");

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}
