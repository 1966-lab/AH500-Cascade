// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MDS.h"

#include "MainFrm.h"

#include "MDSDoc.h"
#include "MDSView.h"
#include "globaldlg.h"
#include "Connectindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_GLOBLE, OnGloble)
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_COMMAND(ID_CONNECTIN, OnConnectin)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT indicators_english[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS_ENGLISH,
	ID_INDICATOR_NUM_ENGLISH,
	ID_INDICATOR_SCRL_ENGLISH,
};
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
extern CMDSApp theApp;
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_curview=1;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

 if(theApp.m_bLanguage==0)
 {
 	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
}
 else if(theApp.m_bLanguage==1)
 {
 	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators_english,
		  sizeof(indicators_english)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
}
	m_wndStatusBar.SetPaneInfo(3,NULL,SBPS_NORMAL,300);
	m_wndStatusBar.SetPaneInfo(2,NULL,SBPS_NORMAL,100);
	m_wndStatusBar.SetPaneInfo(1,NULL,SBPS_NORMAL,200);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style&=~FWS_ADDTOTITLE;
//	cs.style&=~WS_MAXIMIZEBOX; 
    cs.lpszName="07 (09-04-25)Euroklimat EKAC冷水机组监控软件EK100_B1.1";
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
 
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	//lpMMI->ptMaxTrackSize.x=1300;//1080;
	//lpMMI->ptMaxTrackSize.y =730;//735;
	//lpMMI->ptMinTrackSize.x = 1300;//1080;
	//lpMMI->ptMinTrackSize.y = 730;//735;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::switchview(int nView)
{
		CString tempstr;
		CView* pOldView=GetActiveView();

		if(nView==m_curview)		
			return;
		CView* pNewView=(CView*)GetDlgItem(nView);
        if(pNewView==NULL)
		{	
			switch(nView)
			{
			case 1:
				pNewView=(CView*)new CMDSView;
				break;
			case 2:
				pNewView=(CView*)new globaldlg;
				break;
			case 3:
				pNewView=(CView*)new CConnectindlg;
				break;
			}
			CCreateContext context;
			context.m_pCurrentDoc=pOldView->GetDocument();
            pNewView->Create(NULL,NULL,NULL,
			CMainFrame::rectDefault,this,nView,&context);
	        pNewView->OnInitialUpdate();
		}
        SetActiveView(pNewView);
		pNewView->ShowWindow(SW_SHOW);
        pOldView->ShowWindow(SW_HIDE);
        
		int nID=2;
		if(pOldView->GetRuntimeClass()==RUNTIME_CLASS(CMDSView))
			nID=1;
		if(pOldView->GetRuntimeClass()==RUNTIME_CLASS(globaldlg))
			nID=2;
		if(pOldView->GetRuntimeClass()==RUNTIME_CLASS(CConnectindlg))
			nID=3;
		pOldView->SetDlgCtrlID(nID);

//		tempstr.Format("包数量%d",pOldView->GetDlgCtrlID());
//				AfxMessageBox(tempstr);

		SetWindowLong(pNewView->m_hWnd,GWL_ID,AFX_IDW_PANE_FIRST);
		RecalcLayout();
}

void CMainFrame::OnGloble() 
{
	// TODO: Add your command handler code here
	
	//switchview(2);
	//m_curview=2;
CMenu   *menu; 
	CString strMenu;
	//改为英文界面

	 theApp.m_bLanguage=1;
	_SaveLangSet(theApp.m_bLanguage);

	 menu   =   this->GetMenu(); 

	 strMenu.LoadString(IDS_STR_MAIN_TITLE_ENGLISH);
	 	 strMenu+=theApp.SoftVer;
	 theApp.m_pMainWnd->SetWindowText(strMenu);

	 UINT id = menu->GetMenuItemID(0);
	 strMenu.LoadString(IDS_STR_MENU_CHINESE_ENGLISH);
	 menu->ModifyMenu(0,MF_BYPOSITION|MF_STRING,id,strMenu);//L"中文界面 "

     id = menu->GetMenuItemID(1);
	 strMenu.LoadString(IDS_STR_MENU_ENGLISH_ENGLISH);
	 menu-> ModifyMenu(1,MF_BYPOSITION|MF_STRING,id,strMenu);//L"英文界面 "
     DrawMenuBar();
     ::PostMessage(theApp.p_MDSView_Message_Wnd->m_hWnd,defEK_AC_MDSVIEW_MESSAGE,0,0);

}

void CMainFrame::OnNormal() 
{
	// TODO: Add your command handler code here
	//switchview(1);
//	m_curview=1;
 CMenu   *menu; 
	CString strMenu;

	//改为中文界面
	 theApp.m_bLanguage=0;
	_SaveLangSet(theApp.m_bLanguage);

	 menu   =   this->GetMenu(); 

	 strMenu.LoadString(IDS_STR_MAIN_TITLE);
	 	 strMenu+=theApp.SoftVer;
	 theApp.m_pMainWnd->SetWindowText(strMenu);

	 UINT id = menu->GetMenuItemID(0);
	 strMenu.LoadString(IDS_STR_MENU_CHINESE);
	 menu->ModifyMenu(0,MF_BYPOSITION|MF_STRING,id,strMenu);//L"中文界面 "

     id = menu->GetMenuItemID(1);
	 strMenu.LoadString(IDS_STR_MENU_ENGLISH);
	 menu-> ModifyMenu(1,MF_BYPOSITION|MF_STRING,id,strMenu);//L"英文界面 "
     DrawMenuBar();
	 ::PostMessage(theApp.p_MDSView_Message_Wnd->m_hWnd,defEK_AC_MDSVIEW_MESSAGE,0,0);


}
int CMainFrame::_SaveLangSet(int &uchLanguage)
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
int CMainFrame::_ReadLangSet(int &uchLanguage)
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

void CMainFrame::OnConnectin() 
{
	// TODO: Add your command handler code here
	switchview(3);
	m_curview=3;
}
void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (!theApp.YourDogIsHere)//MYDog	
	{
		theApp.ReleaseSafeNet_EK();//2012-08-06
	}
	CFrameWnd::OnClose();
}