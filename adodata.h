// adodata.h: interface for the adodata class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADODATA_H__69A715C1_92C5_11D8_BA6F_0050BA1187B9__INCLUDED_)
#define AFX_ADODATA_H__69A715C1_92C5_11D8_BA6F_0050BA1187B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class adodata  
{
public:
	void recordalarm(int address,int alarmNo,CString stime);
	void recordwatertp(float tp[2],CString stime ,CString stimeid,int address);
	void deldata(CString allstr);
	void getallchaneldata(CListCtrl* m_datalist,CString allstr);
	void getonehourdata(int* pdata,CString onestr,CString str);
	void adddata(int temp[8],CString sdate,long stime);

  BOOL	initcreate();
	adodata();
	virtual ~adodata();

private:
	_RecordsetPtr pRecordset;
	_ConnectionPtr m_pConnection;

};

#endif // !defined(AFX_ADODATA_H__69A715C1_92C5_11D8_BA6F_0050BA1187B9__INCLUDED_)
