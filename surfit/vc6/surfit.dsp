# Microsoft Developer Studio Project File - Name="surfit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=surfit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "surfit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "surfit.mak" CFG="surfit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "surfit - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "surfit - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/surfit", HAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "surfit - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SURFIT_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /Op /Ob0 /I "surfit" /I "../" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /FD /Gs /Gs /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib opengl32.lib fltk.lib fltkgl.lib gdi32.lib comctl32.lib wsock32.lib ole32.lib shell32.lib user32.lib /nologo /dll /machine:I386 /nodefaultlib:"libcmt" /out:"../bin/libsurfit.dll"
# SUBTRACT LINK32 /incremental:yes /map /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SURFIT_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GZ /c
# SUBTRACT CPP /Gf /Gy /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib opengl32.lib fltkd.lib fltkgld.lib gdi32.lib comctl32.lib wsock32.lib ole32.lib shell32.lib user32.lib /nologo /dll /pdb:none /map /debug /machine:I386 /nodefaultlib:"libcd" /nodefaultlib:"libcmtd" /out:"../bin/libsurfit.dll" /libpath:"D:\fltk\lib"
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "surfit - Win32 Release"
# Name "surfit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "matr_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\boolvec.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\intvec.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\matlab.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\oper.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\oper_points.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\operD1.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\operD1_rect.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\operD2.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\operD2_rect.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\vec.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\vec_alg.cpp
# End Source File
# End Group
# Begin Group "common_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\datafile.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\fileio.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\license.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\read_txt.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\rnd.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\sort_alg.cpp
# End Source File
# End Group
# Begin Group "methods_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\geom_alg.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\main_method.cpp
# End Source File
# End Group
# Begin Group "grid_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\grid.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\grid_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_user.cpp
# End Source File
# End Group
# Begin Group "variables_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\variables.cpp
# End Source File
# End Group
# Begin Group "data_cpp"

# PROP Default_Filter ""
# Begin Group "func_cpp"

# PROP Default_Filter ""
# Begin Group "trend_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\trend.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trend_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\trend_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trend_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trend_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trends.cpp
# End Source File
# End Group
# Begin Group "defarea_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\defarea.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defarea_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\defarea_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defarea_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defarea_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defareas.cpp
# End Source File
# End Group
# Begin Group "wfunc_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wfunc.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfunc_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wfunc_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfunc_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfunc_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfuncs.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\func.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\func_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\func_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\func_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\func_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\funcs.cpp
# End Source File
# End Group
# Begin Group "points_cpp"

# PROP Default_Filter ""
# Begin Group "task_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\task.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\task_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\task_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\task_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\task_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\tasks.cpp
# End Source File
# End Group
# Begin Group "wtask_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wtask.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtask_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wtask_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtask_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtask_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtasks.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\points.cpp
# End Source File
# End Group
# Begin Group "curv_cpp"

# PROP Default_Filter ""
# Begin Group "iso_cpp"

# PROP Default_Filter ""
# Begin Group "wiso_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wiso.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wiso_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wiso_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wiso_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wiso_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wisos.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\iso.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\iso_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\iso_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\iso_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\iso_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\isos.cpp
# End Source File
# End Group
# Begin Group "flt_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\flt.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flt_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\flt_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flt_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flt_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flts.cpp
# End Source File
# End Group
# Begin Group "area_cpp"

# PROP Default_Filter ""
# Begin Group "warea_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\warea.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\warea_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\warea_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\warea_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\warea_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wareas.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\area.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\area_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\area_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\area_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\area_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\areas.cpp
# End Source File
# End Group
# Begin Group "cntr_cpp"

# PROP Default_Filter ""
# Begin Group "wcntr_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wcntr.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntr_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wcntr_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntr_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntr_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntrs.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\cntr.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntr_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\cntr_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntr_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntr_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntrs.cpp
# End Source File
# End Group
# Begin Group "grid_line_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\grid_line.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_line_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_line_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_line_user.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\curv.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curv_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\curv_show.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curv_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curv_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curvs.cpp
# End Source File
# End Group
# Begin Group "dynamic_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\dynamic.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamic_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamic_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamic_user.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamics.cpp
# End Source File
# End Group
# Begin Group "completer_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\completer.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\completer_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\completer_user.cpp
# End Source File
# End Group
# Begin Group "fill_with_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\fill_with.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\fill_with_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\fill_with_user.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\data.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\user.cpp
# End Source File
# End Group
# Begin Group "gl_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\surfit\src\colors.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\conrec.cxx
# End Source File
# Begin Source File

SOURCE=..\surfit\src\draw.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\draw_object.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\projector.cpp
# End Source File
# Begin Source File

SOURCE=..\surfit\src\trackball.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\color_scale.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\file_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\mrf.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\surfit.cpp
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\surfit_wrap.cxx

!IF  "$(CFG)" == "surfit - Win32 Release"

# ADD CPP /Oy-
# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "solvers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\cg.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cg2.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\jacobi.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\simpiter.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\simpiter2.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\solvers.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\sor.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\ssor.h
# End Source File
# End Group
# Begin Group "sort_alg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\bitvec_alg.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\geom_alg.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\sort_alg.h
# End Source File
# End Group
# Begin Group "matr_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\bitvec.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\boolvec.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\intvec.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\matfile.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\matlab.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\oper.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\oper_points.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\operD1.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\operD2.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\vec.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\vec_alg.h
# End Source File
# End Group
# Begin Group "common_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\datafile.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\fileio.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\free_elements.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\ie.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\license.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\read_txt.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\real.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\rnd.h
# End Source File
# End Group
# Begin Group "methods_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\main_method.h
# End Source File
# End Group
# Begin Group "grid_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\grid.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\grid_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_user.h
# End Source File
# End Group
# Begin Group "variables_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\variables.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\variables_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\variables_tcl.h
# End Source File
# End Group
# Begin Group "data_h"

# PROP Default_Filter ""
# Begin Group "func_h"

# PROP Default_Filter ""
# Begin Group "trend_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\trend.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trend_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\trend_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trend_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trend_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\trends.h
# End Source File
# End Group
# Begin Group "defarea_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\defarea.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defarea_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\defarea_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defarea_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defarea_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\defareas.h
# End Source File
# End Group
# Begin Group "wfunc_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wfunc.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfunc_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wfunc_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfunc_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfunc_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wfuncs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\func.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\func_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\func_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\func_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\func_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\funcs.h
# End Source File
# End Group
# Begin Group "points_h"

# PROP Default_Filter ""
# Begin Group "task_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\task.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\task_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\task_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\task_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\task_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\tasks.h
# End Source File
# End Group
# Begin Group "wtask_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wtask.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtask_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wtask_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtask_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtask_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wtasks.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\points.h
# End Source File
# End Group
# Begin Group "curv_h"

# PROP Default_Filter ""
# Begin Group "iso_h"

# PROP Default_Filter ""
# Begin Group "wiso_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wiso.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wiso_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wiso_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wiso_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wiso_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wisos.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\iso.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\iso_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\iso_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\iso_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\iso_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\isos.h
# End Source File
# End Group
# Begin Group "flt_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\flt.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flt_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\flt_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flt_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flt_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\flts.h
# End Source File
# End Group
# Begin Group "area_h"

# PROP Default_Filter ""
# Begin Group "warea_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\warea.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\warea_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\warea_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\warea_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\warea_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wareas.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\area.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\area_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\area_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\area_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\area_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\areas.h
# End Source File
# End Group
# Begin Group "cntr_h"

# PROP Default_Filter ""
# Begin Group "wcntr_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\wcntr.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntr_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\wcntr_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntr_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntr_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\wcntrs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\cntr.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntr_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\cntr_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntr_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntr_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\cntrs.h
# End Source File
# End Group
# Begin Group "grid_line_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\grid_line.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_line_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_line_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\grid_line_user.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\curv.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curv_internal.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\curv_show.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curv_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curv_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\curvs.h
# End Source File
# End Group
# Begin Group "dynamic_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\dynamic.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamic_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamic_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamic_user.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\dynamics.h
# End Source File
# End Group
# Begin Group "completer_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\completer.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\completer_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\completer_user.h
# End Source File
# End Group
# Begin Group "fill_with_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\fill_with.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\fill_with_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\fill_with_user.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\data.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\user.h
# End Source File
# End Group
# Begin Group "gl_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\surfit\src\colors.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\draw.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\draw_object.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\projector.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\trackball.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\surfit\src\color_scale.h
# End Source File
# Begin Source File

SOURCE=..\surfit\src\config.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\file_manager.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\mrf.h
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\surfit.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter "*.i"
# Begin Source File

SOURCE=.\..\surfit\src\interface\curv.i
# End Source File
# Begin Source File

SOURCE=..\surfit\src\interface\draw.i
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\fileio.i
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\func.i
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\geom.i
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\mrf.i
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\solve.i
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\surfit.i

!IF  "$(CFG)" == "surfit - Win32 Release"

USERDEP__SURFI="../surfit/src/interface/fileio.i"	"../surfit/src/interface/solve.i"	"../surfit/src/interface/task.i"	"../surfit/src/interface/geom.i"	"../surfit/src/interface/func.i"	"../surfit/src/interface/mrf.i"	"../surfit/src/interface/curv.i"	"../surfit/src/real.h"	"../surfit/src/interface/draw.i"	
# Begin Custom Build
InputPath=.\..\surfit\src\interface\surfit.i

"../surfit/src/surfit_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	surfit_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

USERDEP__SURFI="../surfit/src/interface/fileio.i"	"../surfit/src/interface/solve.i"	"../surfit/src/interface/task.i"	"../surfit/src/interface/geom.i"	"../surfit/src/interface/func.i"	"../surfit/src/interface/mrf.i"	"../surfit/src/interface/curv.i"	"../surfit/src/interface/draw.i"	
# Begin Custom Build
InputPath=.\..\surfit\src\interface\surfit.i

"../surfit/src/surfit_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	surfit_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\interface\task.i
# End Source File
# End Group
# Begin Group "Unix files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\AUTHORS
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\ChangeLog
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\configure.in
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\COPYING
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\INSTALL
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\Makefile.am
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\NEWS
# End Source File
# Begin Source File

SOURCE=.\..\surfit\src\README
# End Source File
# End Group
# Begin Group "Deprecated code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\surfit\src\deprecated
# End Source File
# End Group
# Begin Group "examples"

# PROP Default_Filter ""
# Begin Group "test"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\surfit\examples\test\map_area.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_cntr.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_defarea.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_flt.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_func.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_iso.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_task.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_trend.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_warea.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_wcntr.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_wfunc.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_wiso.doc
# End Source File
# Begin Source File

SOURCE=..\surfit\examples\test\map_wtask.doc
# End Source File
# End Group
# Begin Group "Usage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\samples\usage\grid_usage.tcl
# End Source File
# Begin Source File

SOURCE=..\samples\usage\task_usage.tcl
# End Source File
# End Group
# Begin Group "seism"

# PROP Default_Filter ""
# End Group
# Begin Group "volumetrics"

# PROP Default_Filter ""
# End Group
# End Group
# End Target
# End Project
