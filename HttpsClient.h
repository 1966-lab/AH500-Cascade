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

	BOOL InitializeSocketContext();                            //!��ʼ���׽��ֻ���
	BOOL InitializeSslContext();                               //!��ʼ��SSL����
	BOOL SocketConnect();                                      //!Socket����
	BOOL SslConnect();                                         //!SSL����
	BOOL SendLoginPostData();							       //!���͵�¼����
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
	
	
	void RecvLoginPostData(CString &cstrRecvData);             //!���յ�¼����
	void ParseCookieFromRecvData(const CString cstrRecvData);  //!�������յ������ݣ���ȡcookie��Ϣ
	void ParseModelIdFromRecvData(const CString cstrRecvData);  //!�������յ������ݣ���ȡcookie��Ϣ
	void ParseStartGatewayFromRecvData(const CString cstrRecvData); 
	void ParseDeviceKpiFromRecvData(const CString cstrRecvData); 
	void ParseDeviceIdFromRecvData(const CString cstrRecvData);
	void ParseGatewayIdFromRecvData(const CString cstrRecvData); 
	void ParseStartDeviceFromRecvData(const CString cstrRecvData); 
	void ParseStopDeviceFromRecvData(const CString cstrRecvData); 
	
	/*
	  @���ܣ���ȡ����ͷ�������֤
	  @ע�⣺�ò����ǿ�ѡ�ģ���Ӱ�������ͨ��
	         ֻ��Ϊ�˰�ȫ�Կ���
	 */
	BOOL SslGetCipherAndCertification();

public:
	WSADATA *wsaData;
	SOCKET  socketClient;
	SOCKADDR_IN *socketAddrClient;

	CString cstrServerUrl;                //!��������ַ
	int nServerPort;                      //!�������˿�
	CString cstrUserName;				  //!��¼�û���
	CString cstrPassWord;                 //!��¼����
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
	hash_map<CString, CString, CStringHash>    hmapCookiesSet;       //!���cookie��Ϣ��hash��
};

