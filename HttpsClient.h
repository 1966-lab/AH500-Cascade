#pragma once

#include "BaseClient.h"
#include "openssl/ssl.h"
#include "StaticUtility.h"
#include "CStringHash.h"

#include <list>
#include <hash_map>
#include <algorithm>
#include <iostream>
using namespace std;

class HttpsClient :	public BaseClient
{
public:
	HttpsClient(void);
	~HttpsClient(void);

public:
	BOOL ConnectToServer(const CString strServerUrl, const int nPort);
	BOOL LoginToServer(const CString strUsername, const CString strPasswd);
	BOOL LoginToServerForAddGateway(const CString strUsername, const CString strPasswd,const CString strModelImel,const CString strUnitinfo);
	BOOL LoginToServerForCheckGateway(const CString strUsername, const CString strPasswd,const CString strModelImel,const CString strUnitinfo);
	BOOL LoginToServerForStartGateway(const CString strUsername, const CString strPasswd);
	BOOL LoginToServerForStartDevice(const CString strUsername, const CString strPasswd);
	BOOL LoginToServerForDeviceKpi(const CString strUsername, const CString strPasswd);
	BOOL LoginToServerForDeviceKpi_RSSI(const CString strUsername, const CString strPasswd);
	BOOL LoginToServerForModelId(const CString strUsername, const CString strPasswd);
	BOOL LoginToServerForAddDevice(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder,const CString strUnittime);
	BOOL LoginToServerForCheckDevice(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder,const CString strUnittime);
	BOOL LoginToServerForSendConfig(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder);

	BOOL LogoutOfServer();

	BOOL InitializeSocketContext();                            //!初始化套接字环境
	BOOL InitializeSslContext();                               //!初始化SSL环境
	BOOL SocketConnect();                                      //!Socket连接
	BOOL SslConnect();                                         //!SSL连接
	BOOL SendLoginPostData();							       //!发送登录数据
	BOOL SendLoginPostDataForAddGateway();
	BOOL SendLoginPostDataForCheckGatewayId();
	BOOL SendLoginPostDataForStartGateway();
	BOOL SendLoginPostDataForDeviceKpi();
	BOOL SendLoginPostDataForDeviceKpi_RSSI();
	BOOL SendLoginPostDataForStartDevice();
	BOOL SendLoginPostDataForStopDevice();
	BOOL SendLoginPostDataForModelId();
	BOOL SendLoginPostDataForAddDevice();
	BOOL SendLoginPostDataForCheckDevice();
	BOOL SendLoginPostDataForSendConfig();
	
	
	void RecvLoginPostData(CString &cstrRecvData);             //!接收登录数据
	void ParseCookieFromRecvData(const CString cstrRecvData);  //!解析接收到的数据，获取cookie信息
	void ParseModelIdFromRecvData(const CString cstrRecvData);  //!解析接收到的数据，获取cookie信息
	void ParseStartGatewayFromRecvData(const CString cstrRecvData); 
	void ParseDeviceKpiFromRecvData(const CString cstrRecvData); 
	void ParseDeviceIdFromRecvData(const CString cstrRecvData);
	void ParseGatewayIdFromRecvData(const CString cstrRecvData); 
	void ParseStartDeviceFromRecvData(const CString cstrRecvData); 
	void ParseStopDeviceFromRecvData(const CString cstrRecvData); 
	
	/*
	  @功能：获取密码和服务器端证
	  @注意：该操作是可选的，不影响下面的通信
	         只是为了安全性考虑
	 */
	BOOL SslGetCipherAndCertification();

public:
	WSADATA *wsaData;
	SOCKET  socketClient;
	SOCKADDR_IN *socketAddrClient;

	CString cstrServerUrl;                //!服务器地址
	int nServerPort;                      //!服务器端口
	CString cstrUserName;				  //!登录用户名
	CString cstrPassWord;                 //!登录密码
	CString cstrModelImel;
	CString cstrUnitinfo;
	CString cstrUnitname;
	CString cstrUnitorder;
	CString cstrUnittime;

	SSL *ssl;
	SSL_CTX *sslCtx;
	SSL_METHOD *sslMethod;
	X509 *serverCertification;

	CString cstrSslCipher;
	CString cstrSslSubject;
	CString cstrSslIssuer;
	CString cstrCookieUid;
	CString cstrAccesstoken;
	CString cstrRefreshtoken;
	CString cstrGatewayId;
	CString cstrDeviceId;
	CString cstrModelId;
	CString cstrStartDeviceId;
	CString cstrStopDeviceId;
	CString cstrDeviceKpiValue;
	hash_map<CString, CString, CStringHash>    hmapCookiesSet;       //!存放cookie信息的hash表
};

