#include "StdAfx.h"
#include "HttpsClient.h"

#pragma comment( lib, "lib\\libeay32.lib" )
#pragma comment( lib, "lib\\ssleay32.lib" )
HttpsClient::HttpsClient(void):
			 wsaData(NULL),
		     socketAddrClient(NULL),
			 ssl(NULL),
			 sslCtx(NULL),
			 sslMethod(NULL),
			 serverCertification(NULL)
{
	SSL_load_error_strings();
	SSLeay_add_ssl_algorithms();
}

HttpsClient::~HttpsClient(void)
{
	//!清理打开的句柄
	if (NULL != ssl)
	{
		SSL_shutdown(ssl);
		closesocket(socketClient);
		SSL_free(ssl);
		ssl = NULL;
	}

	if (NULL != sslCtx)
	{
		SSL_CTX_free(sslCtx);
	}

	WSACleanup();
}

BOOL HttpsClient::ConnectToServer(const CString strServerUrl, const int nPort)
{
	cstrServerUrl = strServerUrl;
	nServerPort = nPort;
	BOOL bRet = FALSE;

	do 
	{
		if (!InitializeSocketContext())
		{
			break;
		}

		if (!SocketConnect())
		{
			break;
		}

		if (!InitializeSslContext())
		{
			break;
		}

		if (!SslConnect())
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForAddDevice(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder,const CString strUnittime)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	cstrUnitname = strUnitname+strUnitorder+strUnittime;
	cstrUnitorder = strUnitname+strUnitorder+strUnittime;
	cstrUnittime =strUnittime;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForAddDevice())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseDeviceIdFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForSendConfig(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	cstrUnitname = strUnitname;
	cstrUnitorder = strUnitorder;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForSendConfig())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

	//	ParseAddDeviceFromRecvData(cstrRecvData);

		//if (cstrCookieUid.IsEmpty() || cstrCookieUid.Compare("EXPIRED") == 0)
		//{
		//	break;
		//}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForModelId(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForModelId())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseModelIdFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForStartGateway(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForStartGateway())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

	    ParseStartGatewayFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForStartDevice(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForStopDevice())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}
		ParseStopDeviceFromRecvData(cstrRecvData);

		if (!SendLoginPostDataForStartDevice())
		{
			break;
		}

		CString cstrRecvData1;
		RecvLoginPostData(cstrRecvData1);
		if (cstrRecvData1.GetLength() == 0)
		{
			break;
		}
		ParseStartDeviceFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

//获取信号强度KPI
BOOL HttpsClient::LoginToServerForDeviceKpi_RSSI(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForDeviceKpi_RSSI())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

	    ParseDeviceKpiFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForDeviceKpi(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForDeviceKpi())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

	    ParseDeviceKpiFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}


BOOL HttpsClient::LoginToServerForAddGateway(const CString strUsername, const CString strPasswd,const CString strModelImel,const CString strUnitinfo)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	cstrModelImel = strModelImel;
	cstrUnitinfo =  strModelImel;//网关名称
	//cstrUnitinfo = strUnitinfo+"-"+strModelImel;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForAddGateway())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseGatewayIdFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LoginToServerForCheckGateway(const CString strUsername, const CString strPasswd,const CString strModelImel,const CString strUnitinfo)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	cstrModelImel = strModelImel;
	cstrUnitinfo =  strModelImel;//网关名称
	//cstrUnitinfo = strUnitinfo+"-"+strModelImel;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForCheckGatewayId())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseGatewayIdFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}


BOOL HttpsClient::LoginToServer(const CString strUsername, const CString strPasswd)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostData())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseCookieFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL HttpsClient::LogoutOfServer()
{
	return FALSE;
}

BOOL HttpsClient::InitializeSocketContext()
{
	//!初始化winSocket环境
	BOOL bRet = FALSE;
	wsaData = new WSADATA;
	WORD wVersion = MAKEWORD(2, 2);

	do 
	{
		if(0 != WSAStartup(wVersion, wsaData))
		{
			break;
		}

		if(LOBYTE( wsaData->wVersion ) != 2 || HIBYTE( wsaData->wVersion ) != 2 )
		{
			WSACleanup();
			break;
		}

		LPHOSTENT lpHostTent;
		lpHostTent = gethostbyname(cstrServerUrl);
		if (NULL == lpHostTent)
		{
			break;
		}

		socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (socketClient == INVALID_SOCKET)
		{
			WSACleanup();
			break;
		}

		socketAddrClient = new SOCKADDR_IN;
		socketAddrClient->sin_family = AF_INET;
		socketAddrClient->sin_port = htons(nServerPort);
		socketAddrClient->sin_addr = *((LPIN_ADDR)*lpHostTent->h_addr_list);
		memset(socketAddrClient->sin_zero, 0, sizeof(socketAddrClient->sin_zero));

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SocketConnect()
{
	//!原生socket连接
	BOOL bRet = FALSE;

	do 
	{
		if (SOCKET_ERROR == connect(socketClient, (LPSOCKADDR)socketAddrClient, sizeof(SOCKADDR_IN)))
		{
			int nErrorCode = WSAGetLastError();
			closesocket(socketClient);
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::InitializeSslContext()
{
	//!SSL通信初始化
	BOOL bRet = FALSE;

	do 
	{
		sslMethod = SSLv23_client_method();
		if(NULL == sslMethod)
		{
			break;
		}

		sslCtx = SSL_CTX_new(sslMethod);
		if (NULL == sslCtx)
		{
			break;
		}

		ssl = SSL_new(sslCtx);
		if (NULL == ssl)
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SslConnect()
{
	//!SSL绑定原生socket,并连接服务器
	BOOL bRet = FALSE;

	do 
	{
		SSL_set_fd(ssl, socketClient);

		int nRet = SSL_connect(ssl);
		if (-1 == nRet)
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SslGetCipherAndCertification()
{
	BOOL bRet = FALSE;

	do 
	{
		cstrSslCipher = SSL_get_cipher(ssl);
		serverCertification = SSL_get_certificate(ssl);

		if (NULL == serverCertification)
		{
			break;
		}

		cstrSslSubject = X509_NAME_oneline(X509_get_subject_name(serverCertification), 0, 0);
		cstrSslIssuer = X509_NAME_oneline(X509_get_issuer_name(serverCertification), 0, 0);

		X509_free(serverCertification);

		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostData()
{
	CString cstrSendData;
	//CString cstrSendParam = "redirect=&username="+cstrUserName+"&password="+cstrPassWord+"&auto_login=checked&submit=%E7%99%BB%E5%BD%95";
	//CString cstrSendParam = "[]";
	CString cstrSendParam = "";
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());

	cstrSendData = "POST https://www.ek-cloud.net/api/oauth2/access_token?grant_type=password&username="+cstrUserName+"&password="+cstrPassWord+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/api/oauth2/access_token?grant_type=password&username="+cstrUserName+"&password="+cstrPassWord+"\r\n";
	cstrSendData += "DNT: 1\r\n";	
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForAddDevice()
{
	/* 单独测试
	cstrAccesstoken = "9476d1f4535b73d9a436b22afa7bee2b";
	cstrGatewayId = "34449758212439";
	cstrModelId = "537113630189500";
	*/
	CString cstrSendData;
//	CString cstrSendParam ="{ \"id\": 0, \"from\": \"gateway\", \"attrType\": null, \"gatewayId\": "+cstrGatewayId+",\"projectId\":537113630196240, \"domainPath\": \"/0/141935137496068/\", \"customerId\": 537113630196238, \"accessMode\": \"single\", \"modelId\": "+cstrModelId+", \"sn\": \"SN0101\", \"label\": \"AutoAddDevice\", \"externalDevId\": \"1\"}";
	CString cstrSendParam ="{ \"id\": 0, \"from\": \"gateway\", \"physicalConfig\": {\"autoActive\": null,\"modelConfig\": {},\"stationNo\": 1,\"analysisConfigs\": {},\"taskConfigs\": [],\"analysisProtocol\": null,\"accessConfigs\": [],\"storageConfigs\": [],\"accessProtocol\": \"MQTT\"}, \"attrType\": null, \"gatewayId\": "+cstrGatewayId+",\"projectId\":537113630196240, \"domainPath\": \"/0/141935137496068/\", \"customerId\": 537113630196238, \"accessMode\": \"single\", \"modelId\": "+cstrModelId+", \"sn\": \""+cstrUnitorder+"\", \"label\": \""+cstrUnitname+"\", \"externalDevId\": \"1\"}";
	
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/addResource?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForCheckDevice()
{
	/* 单独测试
	cstrAccesstoken = "9476d1f4535b73d9a436b22afa7bee2b";
	cstrGatewayId = "34449758212439";
	cstrModelId = "537113630189500";
	*/
	CString cstrSendData;
    CString cstrSendParam ="{\"orCondition\":\""+cstrUnitorder+"\",\"conditionField\":[\"sn\",\"label\"]}";

	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/getDevicesByCondition?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}


BOOL HttpsClient::SendLoginPostDataForSendConfig()
{
	/* 单独测试
	cstrAccesstoken = "9476d1f4535b73d9a436b22afa7bee2b";
	cstrGatewayId = "34449758212439";
	cstrModelId = "537113630189500";
	*/
	CString cstrSendData;
	CString cstrSendParam = cstrGatewayId;
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/sendGatewayConfig?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForModelId()
{
	CString cstrSendData;
	CString cstrSendParam ="[{ \"label\": \"EKAH-258\"}]";
	//CString cstrSendParam ="[{ \"label\": \"多联机(EK258)通讯协议\"}]";
	//String cstrSendParam ="[{ \"label\": \"\"}]";
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/getModelsByCondition?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForStartGateway()
{
	CString cstrSendData;
	CString cstrSendParam =cstrGatewayId;
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/activateGateway?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}


BOOL HttpsClient::SendLoginPostDataForDeviceKpi_RSSI()
{
	CString cstrSendData;
//EKAC-258模板下的cstrDeviceId设备下的KPI项:信号强度 的KPI ID是419603026741239

//	CString cstrSendParam ="[\"kpi\",{\"isRealTimeData\":true,\"nodeIds\":[95997609613780],\"kpiCodes\":[419603026741673],\"includeInstance\":true}]";
	CString cstrSendParam ="[\"kpi\",{\"isRealTimeData\":true,\"nodeIds\":["+cstrDeviceId+"],\"kpiCodes\":[419603026741239],\"includeInstance\":true}]";
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/kpiDataFlexService/getKpiValueList?includeFields=value&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}


BOOL HttpsClient::SendLoginPostDataForDeviceKpi()
{
	CString cstrSendData;
//EKAC-258模板下的cstrDeviceId设备下的KPI项:0#从机主板报警 的KPI ID是419603026741673

//	CString cstrSendParam ="[\"kpi\",{\"isRealTimeData\":true,\"nodeIds\":[95997609613780],\"kpiCodes\":[419603026741673],\"includeInstance\":true}]";
	CString cstrSendParam ="[\"kpi\",{\"isRealTimeData\":true,\"nodeIds\":["+cstrDeviceId+"],\"kpiCodes\":[419603026741673],\"includeInstance\":true}]";
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/kpiDataFlexService/getKpiValueList?includeFields=value&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForStartDevice()
{
	CString cstrSendData;
	CString cstrSendParam =cstrDeviceId;
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/activateDevice?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	//cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/deactivateDevice?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForStopDevice()
{
	CString cstrSendData;
	CString cstrSendParam =cstrDeviceId;
	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	//cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/activateDevice?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/deactivateDevice?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::SendLoginPostDataForAddGateway()
{
	CString cstrSendData;
	CString cstrUnitinfo1, cstrModelImel1;     //20210526
	cstrUnitinfo1 = "4G" + cstrUnitinfo;
	cstrModelImel1 = "4G" + cstrModelImel;
	//广东欧科工厂仓库
	CString cstrSendParam = "{ \"protocol\": \"MQTT\", \"protocolVersion\": \"1.0.0\", \"accessAddress\": \"http://app.ek-cloud.net\",\"accessPassword\": \"\",\"type\": 1, \"enterpriseIds\": \"1004,1006,1007,1010,\", \"productIds\": \"1004_1,1006_4,1007_2,1010_1,\", \"protocols\": \"MQTT\", \"domain\": \"/0/141935137496068/537113630196237/\", \"id\": 0, \"customerId\": 537113630196238, \"projectId\": 537113630196240, \"name\":\"" + cstrUnitinfo1 + "\", \"externalGwId\": \"" + cstrModelImel + "\", \"accessName\": \"\", \"protocolType\": \"\", \"onlineStatus\": \"\", \"managedStatus\": \"deactive\", \"values\": {  \"simple\": true,  \"mac\":\"" + cstrModelImel1 + "\" }, \"offlineAlert\": false, \"timeOutCycle\": 3, \"heartbeatTime\": 60}";

	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/addGateway?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

void HttpsClient::RecvLoginPostData(CString &cstrRecvData)
{
	BOOL bRet = FALSE;
	int received, count = 0;
	int TotalReceived = 0;
	FD_SET fds;
	TIMEVAL timeout;
	do 
	{
		while(TRUE)
		{

			char recvData[10000] = {0};
			int nRecvLen;

			//int nSelect = select(FD_SETSIZE, &fds, NULL, NULL, &tval);
			//if (1 != nSelect)
			//{
			//	break;
			//}

			received = SSL_read(ssl, recvData, sizeof(recvData));
			if (received > 0) {
				TotalReceived += received;
				cstrRecvData += recvData;
				if (received < 10000) {
					int sock = SSL_get_rfd(ssl);
                    FD_ZERO(&fds);
                    FD_SET(sock, &fds);

                    timeout.tv_sec = 2;
                    timeout.tv_usec = 0;

                    int err = select(sock+1, &fds, NULL, NULL, &timeout);
                    if (err > 0)
                        continue; // more data to read...

                    if (err == 0) {
                        // timeout...
                    } else {
                        // error...
                    }

                    break;
				}
			} else {
				count++;
				int err = SSL_get_error(ssl,received);
				switch (err)
                {
                    case SSL_ERROR_NONE:
                    {
                        // no real error, just try again...
                        printf("SSL_ERROR_NONE %i\n", count);
                        continue;
                    }   

                    case SSL_ERROR_ZERO_RETURN: 
                    {
                        // peer disconnected...
                        printf("SSL_ERROR_ZERO_RETURN %i\n", count);
                        break;
                    }   

                    case SSL_ERROR_WANT_READ: 
                    {
                        // no data available right now, wait a few seconds in case new data arrives...
                        printf("SSL_ERROR_WANT_READ %i\n", count);

                        int sock = SSL_get_rfd(ssl);
                        FD_ZERO(&fds);
                        FD_SET(sock, &fds);

                        timeout.tv_sec = 2;
                        timeout.tv_usec = 0;

                        err = select(sock+1, &fds, NULL, NULL, &timeout);
                        if (err > 0)
                            continue; // more data to read...

                        if (err == 0) {
                            // timeout...
                        } else {
                            // error...
                        }

                        break;
                    }

                    case SSL_ERROR_WANT_WRITE: 
                    {
                        // socket not writable right now, wait a few seconds and try again...
                        printf("SSL_ERROR_WANT_WRITE %i\n", count);

                        int sock = SSL_get_wfd(ssl);
                        FD_ZERO(&fds);
                        FD_SET(sock, &fds);

                        timeout.tv_sec = 5;
                        timeout.tv_usec = 0;

                        err = select(sock+1, NULL, &fds, NULL, &timeout);
                        if (err > 0)
                            continue; // can write more data now...

                        if (err == 0) {
                            // timeout...
                        } else {
                            // error...
                        }

                        break;
                    }

                    default:
                    {
                        printf("error %i:%i\n", received, err); 
                        break;
                    }
                }     

                break;
			}
		}

		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
}

void HttpsClient::ParseCookieFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"access_token\":\"";    //!查找标记
	CString cstrFind2 = "\"refresh_token\":\"";
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串

	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('"',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
//	nCount=cstrFind1.GetLength()+4+32;//32位TOKEN
//	cstrAccesstoken=cstrRecvData.Mid(nStart+cstrFind1.GetLength()+3,32);
	cstrAccesstoken=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);

	nStart= cstrRecvData.Find(cstrFind2);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('"',nStart+cstrFind2.GetLength());
	nCount=nEnd-nStart-cstrFind2.GetLength();
//	nCount=cstrFind2.GetLength()+4+32;//32位TOKEN
//	cstrRefreshtoken=cstrRecvData.Mid(nStart,nCount);
	cstrRefreshtoken=cstrRecvData.Mid(nStart+cstrFind2.GetLength(),nCount);
/*	int nPos = 0;
	int nStart = cstrRecvData.Find(cstrSeperator);

	while(nStart != -1)
	{
		CString cstrSessionLine = cstrRecvData.Mid(nPos, nStart - nPos + 1);

		if (cstrSessionLine.Find(cstrFind) != -1)
		{
			CString cstrRealRecord = cstrSessionLine.Right(cstrSessionLine.GetLength() - cstrFind.GetLength() - 3);
			list<CString>::iterator it = find(lstCookiesLine.begin(), lstCookiesLine.end(), cstrRealRecord);
			if (it == lstCookiesLine.end())
			{
				lstCookiesLine.push_back(cstrRealRecord);
			}
		}

		nPos = nStart;
		nStart = cstrRecvData.Find(cstrSeperator, nPos + 2);
	}

	//!根据每行获取的cookie值，解析为key-value的形式
	vector<CString> vecCookieSet;
	for (list<CString>::iterator it = lstCookiesLine.begin(); it != lstCookiesLine.end(); it++)
	{
		CString cstrCookies = *it;
		CString cstrSeperator = ";";
		StaticUtility::StringSplit(cstrCookies, cstrSeperator, vecCookieSet);
	}

	vector<CString> vecTemp;
	for (vector<CString>::iterator it = vecCookieSet.begin(); it != vecCookieSet.end(); it++)
	{
		vecTemp.clear();
		CString cstrOneCookies = *it;
		CString cstrSeperator = "=";

		StaticUtility::StringSplit(cstrOneCookies, cstrSeperator, vecTemp);
		CString cstrKey;
		CString cstrVal;

		if (vecTemp.size() == 2)
		{
			cstrKey = vecTemp[0];
			cstrVal = vecTemp[1];
		}

		if(cstrKey.Compare("userId") == 0)
		{
			cstrCookieUid = cstrVal;
			break;
		}
	}*/
	cstrCookieUid="0000";//test by xiaogang
}

void HttpsClient::ParseGatewayIdFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"id\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串

	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	//nCount=cstrFind1.GetLength()+4+14;//14位网关ID
	//{"code":"0","message":null,"data":[{"id":64937343379533}]}判断到}结束
	cstrGatewayId=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);


	cstrCookieUid="0000";//test by xiaogang
}

void HttpsClient::ParseDeviceIdFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"id\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串
	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	//nCount=cstrFind1.GetLength()+4+14;//14位网关ID
	cstrDeviceId=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);
	cstrCookieUid="0000";//test by xiaogang
}

void HttpsClient::ParseStartGatewayFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"id\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串
	CString cstrGatewayIdWhenStartRetrun; //启用网关时返回的网关ID
	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	cstrGatewayIdWhenStartRetrun=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);
	cstrCookieUid="0000";//test by xiaogang
}


void HttpsClient::ParseDeviceKpiFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"value\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串
	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	cstrDeviceKpiValue=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);
	cstrCookieUid="0000";//test by xiaogang
}



void HttpsClient::ParseModelIdFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"id\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串

    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	cstrModelId=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);
//测试用，多联机(EK258)通讯协议  这协议ID为 537113630189500
//	cstrModelId="537113630189500";
	cstrCookieUid="0000";//test by xiaogang
}

void HttpsClient::ParseStartDeviceFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"id\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串
	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	cstrStartDeviceId=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);
	cstrCookieUid="0000";//test by xiaogang
}

void HttpsClient::ParseStopDeviceFromRecvData(const CString cstrRecvData)
{
	list<CString> lstCookiesLine;        //!存放Set-Cookie的一行，例：Set-Cookie: vso_uname=houqd_1111;
	CString cstrFind1 = "\"id\":";    //!查找标记
	CString cstrSeperator = "\r\n";      //!以"\r\n"分割号来分割字符串
	cstrCookieUid="";//赋初值
    int nPos = 0;
	int nStart,nCount,nEnd;
	nStart= cstrRecvData.Find(cstrFind1);
	if(nStart==-1)
		return;
	nEnd=cstrRecvData.Find('}',nStart+cstrFind1.GetLength());
	nCount=nEnd-nStart-cstrFind1.GetLength();
	cstrStopDeviceId=cstrRecvData.Mid(nStart+cstrFind1.GetLength(),nCount);
	cstrCookieUid="0000";//test by xiaogang
}

///////////////////////for check

BOOL HttpsClient::SendLoginPostDataForCheckGatewayId()
{
	CString cstrSendData;
	CString cstrSendParam ="{\"name\":\""+cstrUnitinfo+"\"}";

	BOOL bRet = FALSE;

	CString cstrSendParamLen;
	cstrSendParamLen.Format("%d", cstrSendParam.GetLength());
	cstrSendData = "POST https://www.ek-cloud.net/api/rest/post/resourceUIService/getAllGatewaysByCondition?includeFields=id&token="+cstrAccesstoken+" HTTP/1.1\r\n";
	cstrSendData += "Host: www.ek-cloud.net\r\n";
	cstrSendData += "Origin: https://www.ek-cloud.net\r\n";
	cstrSendData += "Connection: keep-alive\r\n";
	cstrSendData += "Content-Length: " + cstrSendParamLen +"\r\n";
	cstrSendData += "Accept: application/json, text/plain, */*\r\n";
	cstrSendData += "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:35.0) Gecko/20100101 Firefox/35.0\r\n";
	cstrSendData += "Content-Type: text/plain;charset=UTF-8\r\n";
	cstrSendData += "Accept-Encoding: gzip, deflate, br\r\n";
	cstrSendData += "Accept-Language: zh-cn,zh;q=0.9,en;q=0.8,zh-TW;q=0.7\r\n";
	cstrSendData += "Referer: https://www.ek-cloud.net/app-oc/index.html\r\n";
	cstrSendData += "Sec-Fetch-Dest: empty\r\n";
	cstrSendData += "Sec-Fetch-Mode: cors\r\n";
	cstrSendData += "Sec-Fetch-Site: same-origin\r\n";
	cstrSendData += "DNT: 1\r\n";
	cstrSendData += "\r\n";
	cstrSendData += cstrSendParam;

	CString cstrRecvData;
	do 
	{
		int nRet = SSL_write(ssl, cstrSendData, cstrSendData.GetLength());

		if(-1 == nRet)
		{
			break;
		}
        
		bRet = TRUE;
	} while (FALSE);

	return bRet;
}

BOOL HttpsClient::LoginToServerForCheckDevice(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder,const CString strUnittime)
{
	cstrUserName = strUsername;
	cstrPassWord = strPasswd;
	cstrUnitname = strUnitname+strUnitorder+strUnittime;
	cstrUnitorder = strUnitname+strUnitorder+strUnittime;
//	cstrUnitname = strUnitname+strUnitorder+strUnittime;
//	cstrUnitorder = strUnitname+strUnitorder+strUnittime;
	BOOL bRet = FALSE;

	do 
	{
		if (!SendLoginPostDataForCheckDevice())
		{
			break;
		}

		CString cstrRecvData;
		RecvLoginPostData(cstrRecvData);
		if (cstrRecvData.GetLength() == 0)
		{
			break;
		}

		ParseDeviceIdFromRecvData(cstrRecvData);

		if (cstrCookieUid.IsEmpty() )
		{
			break;
		}

		bRet = TRUE;
	} while (FALSE);
	return bRet;
}
