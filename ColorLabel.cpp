// ColorLabel.cpp : implementation file
//

#include "stdafx.h"
#include "ColorLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorLabel

CColorLabel::CColorLabel()
{
	colorIndex=0;
	Value=20;
	ColorB=0;
	ColorG=0;
	ColorR=0;
	fontH=15;
	fontW=8;
}

CColorLabel::~CColorLabel()
{
}

void CColorLabel::SetFontSize(int h,int w)
{
	fontH=h;
	fontW=w;
	
}
void CColorLabel::SetFontColor(int r,int g,int b)
{
	if(r<0)r=0;
	if (r>255)r=255;
	if(g<0)g=0;
	if (g>255)g=255;
	if(b<0)b=0;
	if (b>255)b=255;
	ColorR=r;
	ColorG=g;
	ColorB=b;



}
BEGIN_MESSAGE_MAP(CColorLabel, CStatic)
	//{{AFX_MSG_MAP(CColorLabel)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorLabel message handlers



void CColorLabel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
//	if(colorIndex==1)
//		dc.SetTextColor(RGB(186,218,250));
//	else dc.SetTextColor(RGB(165,171,94));
	dc.SetTextColor(RGB(ColorR,ColorG,ColorB));
	dc.SetBkMode(TRANSPARENT);
	LOGFONT lf;
	int TempfontW;

	if(Caption=="-127"||Caption=="127")
	{
     TempfontW=20;
	}

	
	lf.lfOutPrecision= OUT_DEFAULT_PRECIS; 
	lf.lfClipPrecision= CLIP_DEFAULT_PRECIS; 
	lf.lfQuality =PROOF_QUALITY; 
	lf.lfPitchAndFamily= VARIABLE_PITCH|FF_MODERN; 
	lf.lfHeight = fontH; 
	if(Caption=="-127"||Caption=="127")
	  lf.lfWidth = 20; 
	else
	  lf.lfWidth = fontW; 

	lf.lfEscapement = 0; 
	lf.lfOrientation = 0; 
	lf.lfWeight =500; 
	lf.lfItalic = FALSE; 
	lf.lfUnderline = FALSE; 
	lf.lfStrikeOut = FALSE; 
	lf.lfCharSet = GB2312_CHARSET; 
	strcpy(lf.lfFaceName,"ËÎÌו"); 


	CFont m_font; 
	m_font.CreateFontIndirect(&lf); 
	CFont* pOldFont =(CFont*)dc.SelectObject(&m_font);
		  
	CRect rect;
	GetClientRect(&rect);
	dc.DrawText(Caption,&rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dc.SelectObject(pOldFont);
	m_font.DeleteObject();


	// Do not call CStatic::OnPaint() for painting messages
}






