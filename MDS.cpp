// MDS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MDS.h"

#include "MainFrm.h"
#include "MDSDoc.h"
#include "MDSView.h"

#include "XPButton.h"
#include "HoverEdit.h"
/* 为此许可证使用这些类 */
#include    "SentinelKeys.h"         /*  圣天狗客户端库的头文件  */
#include    "SentinelKeysLicense.h"  /*  此许可证的头文件  */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDSApp

BEGIN_MESSAGE_MAP(CMDSApp, CWinApp)
	//{{AFX_MSG_MAP(CMDSApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDSApp construction

CMDSApp::CMDSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	MYDOGISLIVE=0;//不要狗屏蔽这里
	YourDogIsHere=1;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMDSApp object

CMDSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMDSApp initialization
SP_HANDLE   licHandle;            /* 许可证句柄  */

 #define    MAX_STRING_LENGTH  256          /* 圣天狗 API 函数 ASCII 字符串的最大长度 */
bool CMDSApp::ReleaseSafeNet_EK()//2012-08-06
{
/* 使用 SFNTReleaseLicense API 函数来释放获取的许可证。 */
	SP_DWORD status;
   status = SFNTReleaseLicense(licHandle );
   if (status != SP_SUCCESS)
   {
     /*
       如果许可证已释放，此 API 函数将返回错误。 
     */
	   	return false;
   }
   return true;
}

bool CMDSApp::QuerySafeNet_EK()//2012-08-06
{
	unsigned long int  status;
	unsigned long int  featureID=SP_EK_QUERY_AES;
	unsigned long int  queryFlag=SP_SIMPLE_QUERY;
	unsigned char      queryValue[] = { 0x45, 0x55, 0x52, 0x4F, 0x4B, 0x4C, 0x49, 0x4D, 0x41, 0x54,0x0};
	unsigned char      queryValue_return[] = { 0x1f, 0x0e, 0x99, 0x7c, 0x8e, 0xf2, 0x75, 0x2d, 0x44, 0xd5,0x0};
	unsigned long int  queryLength=10; 
	unsigned char      response[112]; 
	unsigned long int  responseLength=10;

	status = SFNTQueryFeature( licHandle,
		featureID,
		queryFlag,
		queryValue,
		queryLength,
		response,
		responseLength );

	if (status != SP_SUCCESS)   
	{ 
		return false;
		// If featureID is invalid, then this API will return error.
	}
	for(int i=0;i<10;i++)
		if(response[i]!=queryValue_return[i])
			return false;
	return true;
}


bool CMDSApp::AreYouHaveTheDog()//判断是否插入加密狗；//MYDog   //2012-08-06	
{


SP_DWORD     status;              

  SP_DWORD    DeveloperID=DEVELOPERID;        
  SP_DWORD    flags=SP_STANDALONE_MODE;               



  //SPP_CHAR   readStringValue;   
 
  //SPP_CHAR   writeStringValue;               
  SP_DWORD   stringLen = MAX_STRING_LENGTH;
   char readStringValue[MAX_STRING_LENGTH+1];
//  SP_DWORD   writepassword_String;         
   //setvbuf(stdout, NULL,_IONBF,0);

   status = SFNTGetLicense(DeveloperID, SOFTWARE_KEY, LICENSEID, flags, &licHandle );
   if (status != SP_SUCCESS)
   {

	return false;
   }

   //readStringValue = (char*) malloc(stringLen + 1);
   //memset(readStringValue, 0 , stringLen + 1);
   int i;
   for(i=0;i<MAX_STRING_LENGTH+1;i++)
	   readStringValue[i]=0;
 
   status = SFNTReadString(licHandle, SP_TEST_STRING, readStringValue, stringLen );
   if (status != SP_SUCCESS)
   {

//	   free(readStringValue);
	   return false;
   }
   else
   {
     if(strcmp(readStringValue,"all_eurokliamt")==0)//所有功能都有
	  {
	//	 free(readStringValue);
		return true;
	  }
	  else
	  {
	//    free(readStringValue);
	   	return false;
	  }
   }
    
  //  free(readStringValue);

   return true;
}

BOOL CMDSApp::InitInstance()
{
	AfxEnableControlContainer();
	CoInitialize(NULL);
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	RegisterOcx("MSCOMM32.OCX");
//	UnRegisterOcx("MSCOMM32.OCX");
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    int iIndex;
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	//参数加载启动
/*	CString  tmp = GetCommandLine();
	iIndex = tmp.ReverseFind(' ');
	tmp = tmp.Mid(iIndex+1,tmp.GetLength()-iIndex-1);
	if (tmp!="password")
		return FALSE;	*/
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	//初始化操作；
	_ReadLangSet(m_bLanguage);	
	_ReadInputSet(m_bInput);
	if (MYDOGISLIVE==1)	//MYDog	
	{
		bool DogIsExist = AreYouHaveTheDog();//判断是否插入加密狗；
		if (!DogIsExist)//没有加密狗自动退出；
		{	
			if (m_bLanguage==0)
			{
			AfxMessageBox("系统未检测到加密狗");
			}
			else
			{
			AfxMessageBox("system don't find key");			
			}
			return false;
		}
	}	
	SetDialogBkColor(RGB(172,255,214),RGB(0,0,0));
//	SetDialogBkColor(RGB(128,180,208),RGB(0,0,0));
	GetModuleFileName(NULL,szPath,MAX_PATH);//双击打开文件时定位文件路径
	CString path;
	path = szPath;
    iIndex = path.ReverseFind('\\');
	szPath[iIndex] = '\0';
	 path1=szPath;
    //AfxMessageBox(path1);

	/*if (!ConnectAccess())
	{
		CString HintStr;
		HintStr = "连接数据库失败!";
		
		AfxMessageBox(HintStr);
		return false;
	}*/
	_ReadLangSet(m_bLanguage);	
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
	m_bLanguage? IDR_MAINFRAME1 : IDR_MAINFRAME,
		RUNTIME_CLASS(CMDSDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMDSView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	if (m_bLanguage==0)
	{
      HintStrExit="系统未检测到加密狗，正在退出！";
	}
	else if (m_bLanguage==1)
	{
		HintStrExit="System don't find key and is quiting......";		
	}
	// The one and only window has been initialized, so show and update it.
//	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
//	m_pMainWnd->MoveWindow(2,2,808,580,TRUE);
//	m_pMainWnd->UpdateWindow();
	CString strMenu;
		SoftVer="date:20250826";
    if(m_bLanguage==0)	
	  strMenu.LoadString(IDS_STR_MAIN_TITLE);
	else if(m_bLanguage==1)	
	  strMenu.LoadString(IDS_STR_MAIN_TITLE_ENGLISH);
	strMenu+=SoftVer;
	 m_pMainWnd->SetWindowText(strMenu);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXPButton	m_okbt;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_okbt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMDSApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMDSApp message handlers
BOOL CMDSApp::RegisterOcx(LPCTSTR OcxFileName)
{
	LPCTSTR pszDllName = OcxFileName ;         //ActiveX控件的路径及文件名         
     HINSTANCE hLib = LoadLibrary(pszDllName); //装载ActiveX控件
     if (hLib < (HINSTANCE)HINSTANCE_ERROR)
     {
            return FALSE ;
     }
     FARPROC lpDllEntryPoint; 
     lpDllEntryPoint = GetProcAddress(hLib,_T("DllRegisterServer"));   //获取注册函数DllRegisterServer地址
     if(lpDllEntryPoint!=NULL)   //调用注册函数DllRegisterServer
     {
		if(FAILED((*lpDllEntryPoint)()))
	   {
               FreeLibrary(hLib);
                    return FALSE ;
       }
          return TRUE ;
      }
         else
              return FALSE ;
}
BOOL CMDSApp::UnRegisterOcx(LPCTSTR OcxFileName)
{
	LPCTSTR pszDllName = OcxFileName ;         //ActiveX控件的路径及文件名         
	HINSTANCE hLib = LoadLibrary(pszDllName); //装载ActiveX控件
	if (hLib < (HINSTANCE)HINSTANCE_ERROR)
	{
		return FALSE ;
	}
	FARPROC lpDllEntryPoint; 
	lpDllEntryPoint = GetProcAddress(hLib,_T("DllUnregisterServer"));        //获取注册函数DllUnregisterServer地址
	if(lpDllEntryPoint!=NULL)   //调用注册函数DllUnregisterServer
	{
		if(FAILED((*lpDllEntryPoint)()))
		{
			FreeLibrary(hLib);
			return FALSE ;
		}
		return TRUE ;
	}
	else
		return FALSE ;
}

//连接数据库
/*int  CMDSApp::ConnectAccess()
{
	HRESULT hr;	
	try
	{
		//AfxMessageBox("szConnect");
		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		CString str;
		str.Format("%d",hr);
		//AfxMessageBox(str);
		if(SUCCEEDED(hr))
		{
		//	AfxMessageBox("szConnect");
			_bstr_t szConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
			szConnect += ((CMDSApp*)AfxGetApp())->szPath;//
			szConnect += "\\mdsb.mdb;Persist Security Info=FALSE";//MDSdata.tbs ;Jet OLEDB:Database Password=admincofmds
			m_pConnection->Open(szConnect,"","",adModeUnknown);//用adModeShareDenyNone错误
	        //AfxMessageBox(szConnect);
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description());	
		return 0;
	}
	return 1;
}*/

void CMDSApp::ExcuteSql(_RecordsetPtr &rs,_bstr_t sql)
{	
	try
	{
		rs.CreateInstance(__uuidof(Recordset));

		rs->CursorLocation = adUseClient;//设置此属性后,GetRecordCout()返回值才大于0
		rs->Open(sql,_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
	}
	catch(_com_error &e)
	{
		
		AfxMessageBox(e.Description());
	}
}

int CMDSApp::_SaveLangSet(int &uchLanguage)
{
	BOOL nRetCode;
	char exeFullPath[MAX_PATH];
	CString strPath,strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

    strLanguage.Format("%d",uchLanguage);
	nRetCode = (BOOL)WritePrivateProfileString("LANGSET", "LANGUAGE", strLanguage, strPath);

	return nRetCode;
}
int CMDSApp::_ReadLangSet(int &uchLanguage)
{
	int nTmp=0;
	char exeFullPath[MAX_PATH];
	CString strPath,strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";

	nTmp = GetPrivateProfileInt("LANGSET", "LANGUAGE", FALSE, strPath);
	uchLanguage = nTmp;

	return TRUE;
}


int CMDSApp::_SaveInputSet(int &uchLanguage)
{
	BOOL nRetCode;
	char exeFullPath[MAX_PATH];
	CString strPath,strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";
	
    strLanguage.Format("%d",uchLanguage);
	nRetCode = (BOOL)WritePrivateProfileString("LANGSET", "INPUT", strLanguage, strPath);
	
	return nRetCode;
}
int CMDSApp::_ReadInputSet(int &uchLanguage)
{
	int nTmp=0;
	char exeFullPath[MAX_PATH];
	CString strPath,strLanguage;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = CString(exeFullPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += "\\Setting.config";
	
	nTmp = GetPrivateProfileInt("LANGSET", "INPUT", FALSE, strPath);
	uchLanguage = nTmp;
	
	return TRUE;
}

int CMDSApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	//获取窗口句柄
	CWnd *pWnd=CWnd::FindWindow(NULL,_T("欧科空调监控软件主界面")); 
	if(pWnd!=NULL)
	{//要求看守进程退出；
		//发送消息
		::PostMessage(pWnd->m_hWnd,WM_STARTWATCHER,0,0);
	}		
	return CWinApp::ExitInstance();
}
