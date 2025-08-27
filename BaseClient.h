#pragma once

/************************************************************************/
/*��GET��POST���͵Ļ��࣬���ڹ涨�����������ʵ�ֵĽӿ�                                                                      */
/************************************************************************/

class BaseClient
{
public:
	BaseClient(void);
	~BaseClient(void);

public:
	virtual BOOL ConnectToServer(const CString strServerUrl, const int nPort) = 0;  //!���ӵ�������
	virtual BOOL LoginToServer(const CString strUsername, const CString strPasswd) = 0;
	virtual BOOL LoginToServerForAddGateway(const CString strUsername, const CString strPasswd,const CString strModelImel,const CString strUnitinfo) = 0;
	virtual BOOL LoginToServerForCheckGateway(const CString strUsername, const CString strPasswd,const CString strModelImel,const CString strUnitinfo) = 0;
	virtual BOOL LoginToServerForStartGateway(const CString strUsername, const CString strPasswd) = 0;

	virtual BOOL LoginToServerForModelId(const CString strUsername, const CString strPasswd) = 0;
	virtual BOOL LoginToServerForAddDevice(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder,const CString strUnittime) = 0;
	virtual BOOL LoginToServerForCheckDevice(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder,const CString strUnittime) = 0;
	virtual BOOL LoginToServerForSendConfig(const CString strUsername, const CString strPasswd,const CString strUnitname,const CString strUnitorder) = 0;
	virtual BOOL LogoutOfServer() = 0;

	virtual BOOL LoginToServerForStartDevice(const CString strUsername, const CString strPasswd) = 0;
	virtual BOOL LoginToServerForDeviceKpi(const CString strUsername, const CString strPasswd) = 0;
	virtual BOOL LoginToServerForDeviceKpi_RSSI(const CString strUsername, const CString strPasswd) = 0;
};

