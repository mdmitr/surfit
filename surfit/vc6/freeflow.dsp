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
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../surfit/src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib opengl32.lib fltk.lib fltkgl.lib gdi32.lib comctl32.lib wsock32.lib ole32.lib shell32.lib user32.lib /nologo /dll /machine:I386 /out:"../bin/libfreeflow.dll"
# SUBTRACT LINK32 /map /debug

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
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../surfit/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FREEFLOW_EXPORTS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib opengl32.lib fltkd.lib fltkgld.lib gdi32.lib comctl32.lib wsock32.lib ole32.lib shell32.lib user32.lib /nologo /dll /pdb:none /debug /machine:I386 /out:"../bin/libfreeflow.dll" /libpath:"D:\fltk\lib"

!ENDIF 

# Begin Target

# Name "freeflow - Win32 Release"
# Name "freeflow - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "data_cpp"

# PROP Default_Filter ""
# Begin Group "ptask_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\ptask.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptask_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\ptask_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptask_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptask_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptasks.cpp
# End Source File
# End Group
# Begin Group "curv_cpp"

# PROP Default_Filter ""
# Begin Group "parea_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\parea.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\parea_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\parea_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\parea_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\parea_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pareas.cpp
# End Source File
# End Group
# Begin Group "piso_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\piso.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\piso_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\piso_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\piso_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\piso_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pisos.cpp
# End Source File
# End Group
# Begin Group "pcntr_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\pcntr_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntrs.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\freeflow\src\flow_curv_show.cpp
# End Source File
# End Group
# Begin Group "lcms_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple_user.cpp
# End Source File
# End Group
# Begin Group "func_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\flow_func_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_func_tcl.cpp
# End Source File
# End Group
# End Group
# Begin Group "gl_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\freeflow\src\flow_colors.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\freeflow\src\flow.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_file_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_variables.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\freeflow.cpp
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\freeflow_wrap.cxx

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
# Begin Group "ptask_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\ptask.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptask_internal.h
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\ptask_show.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptask_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptask_user.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\ptasks.h
# End Source File
# End Group
# Begin Group "curv_h"

# PROP Default_Filter ""
# Begin Group "parea_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\parea.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\parea_internal.h
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\parea_show.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\parea_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\parea_user.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pareas.h
# End Source File
# End Group
# Begin Group "piso_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\piso.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\piso_internal.h
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\piso_show.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\piso_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\piso_user.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pisos.h
# End Source File
# End Group
# Begin Group "pcntr_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr_internal.h
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\pcntr_show.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntr_user.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\pcntrs.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\freeflow\src\flow_curv_show.h
# End Source File
# End Group
# Begin Group "lcms_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\lcm_simple_user.h
# End Source File
# End Group
# Begin Group "func_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\freeflow\src\flow_func_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_func_tcl.h
# End Source File
# End Group
# End Group
# Begin Group "gl_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\freeflow\src\flow_colors.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\freeflow\src\flow.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_file_manager.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_ie.h
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\flow_variables.h
# End Source File
# Begin Source File

SOURCE=..\freeflow\src\freeflow.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\freeflow\src\interface\flow_draw.i
# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\interface\freeflow.i

!IF  "$(CFG)" == "freeflow - Win32 Release"

USERDEP__FREEF="../freeflow/src/interface/lcm.i"	"../freeflow/src/interface/flow_draw.i"	
# Begin Custom Build
InputPath=.\..\freeflow\src\interface\freeflow.i

"../freeflow/src/freeflow_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	freeflow_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

USERDEP__FREEF="../freeflow/src/interface/lcm.i"	"../freeflow/src/interface/flow_draw.i"	
# Begin Custom Build
InputPath=.\..\freeflow\src\interface\freeflow.i

"../freeflow/src/freeflow_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	freeflow_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\freeflow\src\interface\lcm.i
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
