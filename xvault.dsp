# Microsoft Developer Studio Project File - Name="xvault" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=xvault - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "xvault.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xvault.mak" CFG="xvault - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xvault - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "xvault - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "xvault - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "xvault - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "xvault - Win32 Release"
# Name "xvault - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\engine\baseencryption.cpp
# End Source File
# Begin Source File

SOURCE=.\configuration\baseenvconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\os\basefilemanagement.cpp
# End Source File
# Begin Source File

SOURCE=.\generic\baserecord.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\basevaultkey.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=.\configuration\dosenvconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\generic\main.cpp
# End Source File
# Begin Source File

SOURCE=.\os\msfilemanagement.cpp
# End Source File
# Begin Source File

SOURCE=.\generic\random.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\sdbaccessor.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\sdbdetailrec.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\sdbmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\singlefile.cpp
# End Source File
# Begin Source File

SOURCE=.\configuration\startupoptions.cpp
# End Source File
# Begin Source File

SOURCE=.\xvault\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\vaultheader.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\vaultmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\engine\vaultrecord.cpp
# End Source File
# Begin Source File

SOURCE=.\xvault\xvault.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\engine\baseencryption.h
# End Source File
# Begin Source File

SOURCE=.\configuration\baseenvconfig.h
# End Source File
# Begin Source File

SOURCE=.\os\basefilemanagement.h
# End Source File
# Begin Source File

SOURCE=.\generic\baserecord.h
# End Source File
# Begin Source File

SOURCE=.\engine\basevaultkey.h
# End Source File
# Begin Source File

SOURCE=.\engine\blowfish.h
# End Source File
# Begin Source File

SOURCE=.\engine\blowfish.h2
# End Source File
# Begin Source File

SOURCE=.\generic\DataArray.h
# End Source File
# Begin Source File

SOURCE=.\generic\DataArray.inl
# End Source File
# Begin Source File

SOURCE=.\configuration\dosenvconfig.h
# End Source File
# Begin Source File

SOURCE=.\generic\exceptions.h
# End Source File
# Begin Source File

SOURCE=.\generic\main.h
# End Source File
# Begin Source File

SOURCE=.\os\msfilemanagement.h
# End Source File
# Begin Source File

SOURCE=.\generic\random.h
# End Source File
# Begin Source File

SOURCE=.\engine\sdbaccessor.h
# End Source File
# Begin Source File

SOURCE=.\engine\sdbdetailrec.h
# End Source File
# Begin Source File

SOURCE=.\engine\sdbmanager.h
# End Source File
# Begin Source File

SOURCE=.\engine\singlefile.h
# End Source File
# Begin Source File

SOURCE=.\configuration\startupoptions.h
# End Source File
# Begin Source File

SOURCE=.\xvault\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\engine\vaultheader.h
# End Source File
# Begin Source File

SOURCE=.\engine\vaultmanager.h
# End Source File
# Begin Source File

SOURCE=.\engine\vaultrecord.h
# End Source File
# Begin Source File

SOURCE=.\os\windoze.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\license.txt
# End Source File
# End Target
# End Project
