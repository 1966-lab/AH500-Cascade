// modfi_slave.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "modfi_slave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cmodfi_slave dialog


Cmodfi_slave::Cmodfi_slave(CWnd* pParent /*=NULL*/)
	: CDialog(Cmodfi_slave::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cmodfi_slave)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cmodfi_slave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cmodfi_slave)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cmodfi_slave, CDialog)
	//{{AFX_MSG_MAP(Cmodfi_slave)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cmodfi_slave message handlers
