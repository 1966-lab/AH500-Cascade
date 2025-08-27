# Microsoft Developer Studio Project File - Name="MDS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MDS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MDS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MDS.mak" CFG="MDS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MDS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MDS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MDS - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SentinelKeyW.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MDS - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SentinelKeyW.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MDS - Win32 Release"
# Name "MDS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\adodata.cpp
# End Source File
# Begin Source File

SOURCE=.\air.cpp
# End Source File
# Begin Source File

SOURCE=.\Alarmdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Colorstatic.cpp
# End Source File
# Begin Source File

SOURCE=.\compdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Connectindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\globaldlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HoverEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Inputstrdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MDS.cpp
# End Source File
# Begin Source File

SOURCE=.\MDS.rc
# End Source File
# Begin Source File

SOURCE=.\MDSDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MDSView.cpp
# End Source File
# Begin Source File

SOURCE=.\MESSAGEBOXDLG.cpp
# End Source File
# Begin Source File

SOURCE=.\mod_slave_cfg.cpp
# End Source File
# Begin Source File

SOURCE=.\modoutdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mscomm.cpp
# End Source File
# Begin Source File

SOURCE=.\Passworddlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Specilcmddlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Testcodedlg.cpp
# End Source File
# Begin Source File

SOURCE=.\waitpdf.cpp
# End Source File
# Begin Source File

SOURCE=.\XPButton.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddConfig.h
# End Source File
# Begin Source File

SOURCE=.\adodata.h
# End Source File
# Begin Source File

SOURCE=.\air.h
# End Source File
# Begin Source File

SOURCE=.\Alarmdlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorEdit.h
# End Source File
# Begin Source File

SOURCE=.\ColorListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Colorstatic.h
# End Source File
# Begin Source File

SOURCE=.\compdlg.h
# End Source File
# Begin Source File

SOURCE=.\Connectindlg.h
# End Source File
# Begin Source File

SOURCE=.\globaldlg.h
# End Source File
# Begin Source File

SOURCE=.\HoverEdit.h
# End Source File
# Begin Source File

SOURCE=.\Inputstrdlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MDS.h
# End Source File
# Begin Source File

SOURCE=.\MDSDoc.h
# End Source File
# Begin Source File

SOURCE=.\MDSView.h
# End Source File
# Begin Source File

SOURCE=.\MESSAGEBOXDLG.h
# End Source File
# Begin Source File

SOURCE=.\mod_slave_cfg.h
# End Source File
# Begin Source File

SOURCE=.\modoutdlg.h
# End Source File
# Begin Source File

SOURCE=.\mscomm.h
# End Source File
# Begin Source File

SOURCE=.\Passworddlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SentinelKeys.h
# End Source File
# Begin Source File

SOURCE=.\SentinelKeysLicense.h
# End Source File
# Begin Source File

SOURCE=.\SentinelKeystypes.h
# End Source File
# Begin Source File

SOURCE=.\Specilcmddlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Testcodedlg.h
# End Source File
# Begin Source File

SOURCE=.\TrackControl.h
# End Source File
# Begin Source File

SOURCE=.\waitpdf.h
# End Source File
# Begin Source File

SOURCE=.\XPButton.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\animat3.ico
# End Source File
# Begin Source File

SOURCE=.\res\animat3.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\codeoffb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\codeonbm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fbackoff.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\logo2.bmp
# End Source File
# Begin Source File

SOURCE=".\res\MCC-STOP.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MCC-Í£»ú.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MCC£­COOL.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MCC£­HOT.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\MCKCOOL.bmp
# End Source File
# Begin Source File

SOURCE=".\res\MCK£­HOT.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\MCK£­STOP.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\MCM_COOL.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MCM_HOT.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MCM_STOP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\McQuay.bmp
# End Source File
# Begin Source File

SOURCE=".\res\McQuayOk 5.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\mdbcoolb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mdbhotbm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mdbstopb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MDS.ico
# End Source File
# Begin Source File

SOURCE=.\res\MDS.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MDSDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\outdoor.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section MDS : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
# Section MDS : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm.h
# 	2:8:ImplFile:mscomm.cpp
# End Section
