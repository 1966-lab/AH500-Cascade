// adodata.cpp: implementation of the adodata class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "adodata.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

adodata::adodata()
{

}

adodata::~adodata()
{

}

BOOL adodata::initcreate()
{   
	HRESULT hr;
	try{
    m_pConnection.CreateInstance(__uuidof(Connection));
  //  m_pConnection->Open("DSN=mhs","","",-1);
	m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=mac.mdb","","",adModeUnknown);
    hr = pRecordset.CreateInstance(__uuidof(Recordset));
        if (SUCCEEDED(hr))
         return true;
		else
			return  false;
	}
    catch( _com_error &e)
    {
        // get info from _com_error
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
		//AfxMessageBox(e.ErrorMessage());
		return false;
     }
}

void adodata::adddata(int temp[8],CString stime,long stimeid)
{
	CString s;
	try
	{
	      HRESULT hr;    
          hr=pRecordset->Open("SELECT * FROM datatable",m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
            if (SUCCEEDED(hr))
			{ 
                COleSafeArray vaFieldList;
                vaFieldList.CreateOneDim(VT_VARIANT, 10);

                // Fill the fields name now
                long lArrayIndex[1];
                lArrayIndex[0] = 0;					
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("timeid")));
                lArrayIndex[0] = 1;					
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("watertime")));
                lArrayIndex[0] = 2;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel0")));
                lArrayIndex[0] = 3;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel1")));
                 lArrayIndex[0] =4;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel2")));
				lArrayIndex[0] = 5;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel3")));
				lArrayIndex[0] = 6;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel4")));
				lArrayIndex[0] = 7;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel5")));
				lArrayIndex[0] = 8;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel6")));
				lArrayIndex[0] = 9;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("chanel7")));
                // Create an array of values to be added
                COleSafeArray vaValueArray;
                vaValueArray.CreateOneDim(VT_VARIANT, 10);

                //Fill the values in each field
                lArrayIndex[0] = 0;	
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(stimeid)) );
                lArrayIndex[0] = 1;	
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(stime)) );
                lArrayIndex[0] = 2;
				s.Format("%d",temp[0]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
                lArrayIndex[0] = 3;
				s.Format("%d",temp[1]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
				lArrayIndex[0] = 4;
				s.Format("%d",temp[2]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
				lArrayIndex[0] = 5;
				s.Format("%d",temp[3]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
				lArrayIndex[0] = 6;
				s.Format("%d",temp[4]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
				lArrayIndex[0] = 7;
				s.Format("%d",temp[5]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
				lArrayIndex[0] = 8;
				s.Format("%d",temp[6]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
				lArrayIndex[0] = 9;
				s.Format("%d",temp[7]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)) );
                // call Addnew of recordset now
                pRecordset->AddNew( vaFieldList, vaValueArray );
				
                pRecordset->Close();
			}  
       
    }
	    catch( _com_error &e)
    {
        // get info from _com_error
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
       TRACE("%s", e.ErrorMessage());
     }
    catch(...)
    {
        TRACE("*** UNHANDELED EXCEPTION ***");
    }

	//-----------------------------------------
}

void adodata::getonehourdata(int* pdata,CString onestr,CString str)
{

  //_bstr_t bstrQuery("SELECT * FROM datatable");
  //_variant_t vRecsAffected(0L);
  /*_variant_t  thevalue;
  _variant_t  sel;
  _variant_t  onesel;
  onesel=_bstr_t(onestr);
  sel=_variant_t(str);
    try
    {     
            pRecordset->Open(onesel,
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	   if ( !pRecordset->EndOfFile)
	   {
             int i = 0;
            while ( !pRecordset->EndOfFile)
            {   
               thevalue=pRecordset->GetCollect(&sel) ;
                pRecordset->MoveNext();
				pdata[i]=thevalue.iVal;
				i++;
				
            }
        }      
        pRecordset->Close();
    }
    catch( _com_error &e)
    {
        // get info from _com_error
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
        TRACE("%s", e.ErrorMessage());
     }*/
}

void adodata::getallchaneldata(CListCtrl* m_datalist,CString allstr)
{/*
 _variant_t  thevalue;
 _variant_t  thevalue1;
 _variant_t  stemp;
   CString   str;
  	CString alarm[64]={" ","1#ѹ������ѹ����", "2#ѹ������ѹ����",    "3#ѹ������ѹ����",
       				 "1#ѹ������ѹ����",     "2#ѹ������ѹ����",    "3#ѹ������ѹ����",
					 "1#ѹ���������¶ȹ���", "2#ѹ���������¶ȹ���", "3#�����������¶ȹ���",
					 "1#ѹ�����¶ȹ���",     "2#ѹ�����¶ȹ���",    "3#ѹ�����¶ȹ���",
					 "1#ѹ��������",         "2#ѹ��������",        "3#ѹ��������",
					 "ϵͳ1ȱ�ౣ��ϵͳ",    "ϵͳ2ȱ�ౣ��ϵͳ",	"ϵͳ3ȱ�ౣ��",
					 "1#�������ȶȹ���",	 "2#�������ȶȹ���",	"3#�������ȶȹ���",
					 "1#�������ȶȹ���",	 "2#�������ȶȹ���",	"3#�������ȶȹ���",
        			 "ϵͳ1�����й©",		 "ϵͳ2�����й©",		"ϵͳ3�����й©",
					 "ϵͳ1�������",		 "ϵͳ2�������",		"ϵͳ3�������"," ",
  					 "ϵͳ1�������",		 "ϵͳ2�������",		"ϵͳ3�������",	
 					 "ˮ�û���", " ","", "��������",      "ˮ�¹���(��ˮ)",	"ˮ�¹���(��ˮ)",
					 "ͻȻ����",  "ˮ�����ر���",  "�����¶ȹ��߱���",  "�����¶ȹ��ͱ���",
					 "ϵͳ1��ѹ����������",	 "ϵͳ2��ѹ����������",	"ϵͳ3��ѹ����������",
					 "ϵͳ1��ѹ����������",	 "ϵͳ2��ѹ����������", "ϵͳ3��ѹ����������",
					 "�����¶ȴ���������",	  "��ˮ�¶ȴ���������", "��ˮ�¶ȴ���������",
					 "ϵͳ1���ֽ����¶ȴ���������",	"ϵͳ2���ֽ����¶ȴ���������","ϵͳ3���ֽ����¶ȴ���������",
    				 "ϵͳ1�����¶ȴ���������","ϵͳ2�����¶ȴ���������","ϵͳ3�����¶ȴ���������",
  					 "ϵͳ1����",              "ϵͳ2����",          "ϵͳ3����",""
					};
  stemp=_bstr_t(allstr);
   short temp[2];
    try
    {     
            pRecordset->Open(stemp,
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

	   if ( !pRecordset->EndOfFile)
	   {
            while (!pRecordset->EndOfFile)
            {   
               thevalue=pRecordset->GetCollect("AbortTime");
			   thevalue1=pRecordset->GetCollect("MacNo");
			   temp[0]=thevalue1.iVal;
			   thevalue1=pRecordset->GetCollect("AbortNo");
			   temp[1]=thevalue1.iVal;
			   pRecordset->MoveNext();
			   str=(char*)_bstr_t(thevalue);
                m_datalist->InsertItem(0,str);
				str.Format("%d#",temp[0]);
				m_datalist->SetItemText(0,1,str);
                m_datalist->SetItemText(0,2,alarm[temp[1]]);
            }
	   }       
        pRecordset->Close();
    }
    catch( _com_error &e)
    {
        // get info from _com_error
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
     //   AfxMessageBox(e.ErrorMessage());
     }*/
}

void adodata::deldata(CString allstr)
{
/*	_variant_t  thevalue;
    _variant_t  thevalue1;
    _variant_t  stemp;
    CString   str;
    stemp=_bstr_t(allstr);
    try
    {     
            pRecordset->Open(stemp,
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);

	   if ( !pRecordset->EndOfFile)
	   {
            while ( !pRecordset->EndOfFile)
            { 
			  pRecordset->Delete(adAffectCurrent);
			  pRecordset->Update();
			  pRecordset->MoveNext();
            }
        }  
	   
        pRecordset->Close();
    }
    catch( _com_error &e)
    {
        // get info from _com_error
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
        TRACE("%s", e.ErrorMessage());
     }*/

}

void adodata::recordwatertp(float tp[2], CString stime, CString stimeid,int address)
{
	CString s;
	CString openstr;
	_variant_t stemp;
	openstr.Format("SELECT * FROM airmac%d",address);
	stemp=_bstr_t(openstr);
	try
	{
	      HRESULT hr;   
          hr=pRecordset->Open(stemp,m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
            if (SUCCEEDED(hr))
			{ 
                COleSafeArray vaFieldList;
                vaFieldList.CreateOneDim(VT_VARIANT,4);
 
                // Fill the fields name now
                long lArrayIndex[1];
                lArrayIndex[0] = 0;					
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("timeid")));
                lArrayIndex[0] = 1;					
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("tptime")));
                lArrayIndex[0] = 2;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("inlettp")));
                lArrayIndex[0] = 3;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("outlettp")));

                // Create an array of values to be added
                COleSafeArray vaValueArray;
                vaValueArray.CreateOneDim(VT_VARIANT,4);

                //Fill the values in each field
                lArrayIndex[0] = 0;	
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(stimeid)));
                lArrayIndex[0] = 1;	
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(stime)));
                lArrayIndex[0] = 2;
				s.Format("%.1f",tp[0]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)));
                lArrayIndex[0] = 3;
				s.Format("%.1f",tp[1]);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)));

                // call Addnew of recordset now
				try
				{
                pRecordset->AddNew(vaFieldList,vaValueArray); 
				}
				catch(...)
				{
					;
				}
                pRecordset->Close();
			}  
    }
	    catch( _com_error &e)
    {
        // get info from _com_error
       _bstr_t bstrSource(e.Source());
       _bstr_t bstrDescription(e.Description());
     //  AfxMessageBox(e.ErrorMessage());
     }
}

void adodata::recordalarm(int address, int alarmNo, CString stime)
{
	CString s;
	try
	{
	      HRESULT hr;    
          hr=pRecordset->Open("SELECT * FROM abort",m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
            if (SUCCEEDED(hr))
			{ 
                COleSafeArray vaFieldList;
                vaFieldList.CreateOneDim(VT_VARIANT,3);
 
                // Fill the fields name now
                long lArrayIndex[1];
                lArrayIndex[0] = 0;					
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("AbortTime")));
                lArrayIndex[0] = 1;					
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("MacNo")));
                lArrayIndex[0] = 2;
                vaFieldList.PutElement( lArrayIndex, &(_variant_t("AbortNo")));

                // Create an array of values to be added
                COleSafeArray vaValueArray;
                vaValueArray.CreateOneDim(VT_VARIANT,3);

                //Fill the values in each field
                lArrayIndex[0] = 0;	
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(stime)));
                lArrayIndex[0] = 1;
				s.Format("%d",address);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)));
                lArrayIndex[0] = 2;
				s.Format("%d",alarmNo);
                vaValueArray.PutElement( lArrayIndex, &(_variant_t(s)));

                // call Addnew of recordset now
				try
				{
                pRecordset->AddNew(vaFieldList,vaValueArray); 
				}
				catch(...)
				{
					;
				}
				pRecordset->Close();
			}  
    } 
    catch( _com_error &e)
    {
        // get info from _com_error
        _bstr_t bstrSource(e.Source());
        _bstr_t bstrDescription(e.Description());
	//	AfxMessageBox(e.ErrorMessage());
     }
	catch(...)
	{
		;
	}

}
