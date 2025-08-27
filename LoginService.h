#pragma once

#include <string>
#include "HttpClient.h"
#include "HttpsClient.h"
#include "SocketClient.h"

//#define VIEW_MESS

#ifdef VIEW_MESS
#include "waitpdf.h"
#endif

using namespace std;

class LoginService
{
public:
	LoginService(void);
	LoginService(const CString strName, const CString strPass, const CString strImel, const CString strUnit, const CString strOrder, const CString strTime);
	~LoginService(void);

	BOOL Login();
	BOOL LoginKpi();
	BOOL Logout();
#ifdef VIEW_MESS
	void ShowInformation(CString &InforStr);
	waitpdf * WaitingPDf;//œ‘ æÃ· æøÚ£ª
#endif

public:
   CString strUsername;
   CString strPassword;
   CString strModelImel;
   CString strUnitname;
   CString strUnitorder;
	CString strUnittime;
   CString strUrl;
   BaseClient *pHttpClient;
   
};