# Microsoft Developer Studio Project File - Name="globe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=globe - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "globe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "globe.mak" CFG="globe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "globe - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "globe - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "globe - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /Ob2 /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /Fr /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib zdll.lib /nologo /dll /machine:I386 /out:"../bin/libglobe.dll" /implib:"../bin/libglobe.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib zdll.lib /nologo /dll /debug /machine:I386 /out:"../bin/libglobe.dll" /implib:"../bin/libglobe.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "globe - Win32 Release"
# Name "globe - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "data_cpp"

# PROP Default_Filter ""
# Begin Group "dem_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\dem.cpp
# End Source File
# Begin Source File

SOURCE=..\src\globe\dem_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\globe\dem_tcl.cpp
# End Source File
# End Group
# Begin Group "func_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\globe_func_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_func_tcl.cpp
# End Source File
# End Group
# End Group
# Begin Group "functionals_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\dems_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\globe\f_dem.cpp
# End Source File
# End Group
# Begin Group "minizip_c"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\minizip\ioapi.c
# End Source File
# Begin Source File

SOURCE=..\src\globe\minizip\unzip.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\src\globe\globe.cpp
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_data_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_variables.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\globe\globe_wrap.cxx

!IF  "$(CFG)" == "globe - Win32 Release"

# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\globe\shortmrf.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "data_h"

# PROP Default_Filter ""
# Begin Group "dem_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\dem.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\dem_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\dem_tcl.h
# End Source File
# End Group
# Begin Group "func_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\globe_func_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_func_tcl.h
# End Source File
# End Group
# End Group
# Begin Group "functionals_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\dems_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\f_dem.h
# End Source File
# End Group
# Begin Group "minizip_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\globe\minizip\crypt.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\minizip\ioapi.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\minizip\unzip.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\src\globe\globe.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_data_manager.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_ie.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\globe_variables.h
# End Source File
# Begin Source File

SOURCE=..\src\globe\shortmrf.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\globe\interface\globe.i

!IF  "$(CFG)" == "globe - Win32 Release"

USERDEP__GLOBE="../src/freeflow/interface/flow_draw.i"	
# Begin Custom Build
InputPath=.\..\src\globe\interface\globe.i

"../src/globe/globe_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	globe_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

USERDEP__GLOBE="../src/freeflow/interface/flow_draw.i"	
# Begin Custom Build
InputPath=.\..\src\globe\interface\globe.i

"../src/globe/globe_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	globe_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\globe\interface\globe_draw.i
# End Source File
# End Group
# End Target
# End Project
