#pragma once


// waitpdf dialog
#include "resource.h"
class waitpdf : public CDialog
{
	DECLARE_DYNAMIC(waitpdf)

public:
	waitpdf(CWnd* pParent = NULL);   // standard constructor
	virtual ~waitpdf();
	void RefreshString(CString &Str);
// Dialog Data
	enum { IDD = IDD_WAITPDF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_showdata;
};
