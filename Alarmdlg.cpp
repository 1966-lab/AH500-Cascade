// Alarmdlg.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "Alarmdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmdlg dialog


CAlarmdlg::CAlarmdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAlarmdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmdlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmdlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmdlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmdlg message handlers
