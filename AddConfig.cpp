// AddConfig.cpp : implementation file
//

#include "stdafx.h"
#include "MDS.h"
#include "AddConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddConfig dialog

extern CString getExeDir();

CAddConfig::CAddConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CAddConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddConfig)
	m_configname = _T("");
	m_a = _T("20");
	m_b = _T("5");
	m_c = _T("5");
	m_d = _T("5");
	m_e = _T("2");
	m_f = _T("20");
	m_g = _T("10");
	m_h = _T("5");
	m_i = _T("3");
	m_j = _T("2");
	m_k = _T("3");
	//}}AFX_DATA_INIT
}


void CAddConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddConfig)
	DDX_Text(pDX, IDC_EDIT_CONFNAME, m_configname);
	DDX_Text(pDX, IDC_EDIT_A, m_a);
	DDX_Text(pDX, IDC_EDIT_B, m_b);
	DDX_Text(pDX, IDC_EDIT_C, m_c);
	DDX_Text(pDX, IDC_EDIT_D, m_d);
	DDX_Text(pDX, IDC_EDIT_E, m_e);
	DDX_Text(pDX, IDC_EDIT_F, m_f);
	DDX_Text(pDX, IDC_EDIT_G, m_g);
	DDX_Text(pDX, IDC_EDIT_H, m_h);
	DDX_Text(pDX, IDC_EDIT_I, m_i);
	DDX_Text(pDX, IDC_EDIT_J, m_j);
	DDX_Text(pDX, IDC_EDIT_K, m_k);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddConfig, CDialog)
	//{{AFX_MSG_MAP(CAddConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddConfig message handlers

void CAddConfig::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	if(m_configname==_T(""))
	{
		AfxMessageBox("配置名称不能为空");
		return;
	}
	if(m_a==_T("") || m_b==_T("") || m_c==_T("") || m_d==_T("") || m_e==_T("") || m_f==_T("") ||
		 m_g==_T("") || m_h==_T("") || m_i==_T("") || m_j==_T("") || m_k==_T("") )
	{
		AfxMessageBox("参数不能为空");
		return;
	}

	CString inifullpath = getExeDir() + _T("\\Setting.config");
	WritePrivateProfileString(m_configname, "A", m_a, inifullpath);
	WritePrivateProfileString(m_configname, "B", m_b, inifullpath);
	WritePrivateProfileString(m_configname, "C", m_c, inifullpath);
	WritePrivateProfileString(m_configname, "D", m_d, inifullpath);
	WritePrivateProfileString(m_configname, "E", m_e, inifullpath);
	WritePrivateProfileString(m_configname, "F", m_f, inifullpath);
	WritePrivateProfileString(m_configname, "G", m_g, inifullpath);
	WritePrivateProfileString(m_configname, "H", m_h, inifullpath);
	WritePrivateProfileString(m_configname, "I", m_i, inifullpath);
	WritePrivateProfileString(m_configname, "J", m_j, inifullpath);
	WritePrivateProfileString(m_configname, "K", m_k, inifullpath);
	
	CDialog::OnOK();
}
