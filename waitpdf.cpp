// waitpdf.cpp : implementation file
//

#include "stdafx.h"
#include "waitpdf.h"
//#include "afxdialogex.h"


// waitpdf dialog

IMPLEMENT_DYNAMIC(waitpdf, CDialog)

waitpdf::waitpdf(CWnd* pParent /*=NULL*/)
	: CDialog(waitpdf::IDD, pParent)
{

	m_showdata = _T("");
}

waitpdf::~waitpdf()
{
}

void waitpdf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SHOWDATA, m_showdata);
	DDV_MaxChars(pDX, m_showdata, 30);
}


BEGIN_MESSAGE_MAP(waitpdf, CDialog)
END_MESSAGE_MAP()


// waitpdf message handlers
void waitpdf::RefreshString(CString &Str)
{
	m_showdata = Str;
	UpdateData(false);

}