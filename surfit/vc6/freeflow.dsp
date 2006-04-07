# Microsoft Developer Studio Project File - Name="freeflow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=freeflow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "freeflow.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "freeflow.mak" CFG="freeflow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "freeflow - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "freeflow - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "freeflow - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEFLOW_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /Ob2 /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib /nologo /dll /machine:I386 /out:"../bin/libfreeflow.dll" /implib:"../bin/libfreeflow.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEFLOW_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib /nologo /dll /pdb:none /debug /machine:I386 /out:"../bin/libfreeflow.dll" /implib:"../bin/libfreeflow.lib" /libpath:"D:\fltk\lib"

!ENDIF 

# Begin Target

# Name "freeflow - Win32 Release"
# Name "freeflow - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "data_cpp"

# PROP Default_Filter ""
# Begin Group "surf_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\flow_surf_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_surf_tcl.cpp
# End Source File
# End Group
# End Group
# Begin Group "functionals_cpp"

# PROP Default_Filter ""
# Begin Group "points.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\flow_points.cpp
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_points_tcl.cpp
# End Source File
# End Group
# Begin Group "curvs.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\flow_area.cpp
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_cntr.cpp
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_curv.cpp
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_curvs_tcl.cpp
# End Source File
# End Group
# Begin Group "global.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\f_lcm_simple.cpp
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\f_lcm_simple_tcl.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\src\freeflow\flow_data_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\freeflow\flow_variables.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\freeflow\freeflow_wrap.cxx

!IF  "$(CFG)" == "freeflow - Win32 Release"

# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "data_h"

# PROP Default_Filter ""
# Begin Group "surf_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\flow_surf_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_surf_tcl.h
# End Source File
# End Group
# End Group
# Begin Group "functionals_h"

# PROP Default_Filter ""
# Begin Group "points.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\flow_points.h
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_points_tcl.h
# End Source File
# End Group
# Begin Group "curvs.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\flow_area.h
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_cntr.h
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_curv.h
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\flow_curvs_tcl.h
# End Source File
# End Group
# Begin Group "globals.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\freeflow\f_lcm_simple.h
# End Source File
# Begin Source File

SOURCE=..\src\freeflow\f_lcm_simple_tcl.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\src\freeflow\flow_data_manager.h
# End Source File
# Begin Source File

SOURCE=.\..\src\freeflow\flow_ie.h
# End Source File
# Begin Source File

SOURCE=.\..\src\freeflow\flow_variables.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\freeflow\interface\freeflow.i

!IF  "$(CFG)" == "freeflow - Win32 Release"

USERDEP__FREEF="../src/freeflow/interface/lcm.i"	"../src/freeflow/interface/flow_draw.i"	
# Begin Custom Build
InputPath=.\..\src\freeflow\interface\freeflow.i

"../src/freeflow/freeflow_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	freeflow_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

USERDEP__FREEF="../src/freeflow/interface/lcm.i"	"../src/freeflow/interface/flow_draw.i"	
# Begin Custom Build
InputPath=.\..\src\freeflow\interface\freeflow.i

"../src/freeflow/freeflow_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	freeflow_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\src\freeflow\interface\lcm.i
# End Source File
# End Group
# Begin Group "Deprecated code"

# PROP Default_Filter ""
# End Group
# Begin Group "Samples"

# PROP Default_Filter ""
# End Group
# End Target
# End Project
