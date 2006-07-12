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
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /Op /Ob2 /I "../src/sstuff" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /FD /Gs /Gs /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib netcdfs.lib libjpeg.lib /nologo /dll /machine:I386 /nodefaultlib:"LIBC" /out:"../bin/libsurfit.dll" /implib:"../bin/libsurfit.lib"
# SUBTRACT LINK32 /pdb:none /debug

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib /nologo /dll /pdb:none /map /debug /machine:I386 /out:"../bin/libsurfit.dll" /implib:"../bin/libsurfit.lib"

!ENDIF 

# Begin Target

# Name "surfit - Win32 Release"
# Name "surfit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "matr_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\matlab.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr_diag.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr_eye.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr_onesrow.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD1.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD1_aniso.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD1_rect.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD2.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD2_aniso.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD2_rect.cpp
# End Source File
# End Group
# Begin Group "common_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\free_elements.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\license.cpp
# End Source File
# End Group
# Begin Group "methods_cpp"

# PROP Default_Filter ""
# Begin Group "solvers_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\solvers\CG.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\solvers\J.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\solvers\JCG.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\solvers\RF.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\solvers\SSOR.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\cmofs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\solvers.cpp
# End Source File
# End Group
# Begin Group "grid_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\grid.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_user.cpp
# End Source File
# End Group
# Begin Group "data_cpp"

# PROP Default_Filter ""
# Begin Group "surf_cpp"

# PROP Default_Filter ""
# Begin Group "mask_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\mask.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\mask_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\mask_tcl.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\surf.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surf_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surf_tcl.cpp
# End Source File
# End Group
# Begin Group "points_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\pnts_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\pnts_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\points.cpp
# End Source File
# End Group
# Begin Group "curv_cpp"

# PROP Default_Filter ""
# Begin Group "cntr_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\cntr.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\cntr_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\cntr_tcl.cpp
# End Source File
# End Group
# Begin Group "grid_line_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\grid_line.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_line_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_line_tcl.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_line_user.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\src\surfit\curv.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\curv_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\curv_tcl.cpp
# End Source File
# End Group
# Begin Group "hist_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\hist.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\hist_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\hist_tcl.cpp
# End Source File
# End Group
# Begin Group "area_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\area.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\area_internal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\area_tcl.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\src\surfit\data.cpp
# End Source File
# End Group
# Begin Group "functionals_cpp"

# PROP Default_Filter ""
# Begin Group "points.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\f_points.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_points_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_points_tcl.cpp
# End Source File
# End Group
# Begin Group "others.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\f_completer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_hist.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_mean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_value.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_wmean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\others_tcl.cpp
# End Source File
# End Group
# Begin Group "curvs.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\curvs_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_mean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_surf.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_surf_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_wmean.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_cntr.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_cntr_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv_surf.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv_surf_ineq.cpp
# End Source File
# End Group
# Begin Group "surfs.cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\f_mask.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_surf.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_surf_ineq.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_trend.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surfs_tcl.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\functional.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\data_manager.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\mrf.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\surfit\sort_alg.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\surfit.cpp
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\surfit_wrap.cxx

!IF  "$(CFG)" == "surfit - Win32 Release"

# ADD CPP /Oy-
# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\variables.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "solvers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\solvers.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surfit_solvers.h
# End Source File
# End Group
# Begin Group "matr_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\matfile.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\matlab.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr_diag.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr_eye.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matr_onesrow.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD1.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD1_aniso.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD2.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\matrD2_aniso.h
# End Source File
# End Group
# Begin Group "common_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\free_elements.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\license.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surfit_ie.h
# End Source File
# End Group
# Begin Group "variables_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\variables.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\variables_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\variables_tcl.h
# End Source File
# End Group
# Begin Group "data_h"

# PROP Default_Filter ""
# Begin Group "surf_h"

# PROP Default_Filter ""
# Begin Group "mask_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\mask.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\mask_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\mask_tcl.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\surf.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surf_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surf_tcl.h
# End Source File
# End Group
# Begin Group "points_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\pnts_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\pnts_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\points.h
# End Source File
# End Group
# Begin Group "curv_h"

# PROP Default_Filter ""
# Begin Group "cntr_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\cntr.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\cntr_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\cntr_tcl.h
# End Source File
# End Group
# Begin Group "grid_line_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\grid_line.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_line_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_line_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_line_user.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\..\src\surfit\curv.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\curv_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\curv_tcl.h
# End Source File
# End Group
# Begin Group "hist_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\hist.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\hist_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\hist_tcl.h
# End Source File
# End Group
# Begin Group "area_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\area.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\area_internal.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\area_tcl.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\other_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surfit_data.h
# End Source File
# End Group
# Begin Group "functionals_h"

# PROP Default_Filter ""
# Begin Group "points.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\f_points.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_points_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_points_tcl.h
# End Source File
# End Group
# Begin Group "other.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\f_completer.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_hist.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_mean.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_value.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_wmean.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\others_tcl.h
# End Source File
# End Group
# Begin Group "curvs.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\curvs_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_mean.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_surf.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_surf_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_area_wmean.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_cntr.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_cntr_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv_surf.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_curv_surf_ineq.h
# End Source File
# End Group
# Begin Group "surfs.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit\f_mask.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_surf.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_surf_ineq.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\f_trend.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\surfs_tcl.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\functional.h
# End Source File
# End Group
# Begin Group "grid_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\grid.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_internal.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_tcl.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\grid_user.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit\cmofs.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\data_manager.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\mrf.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit\sort_alg.h
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\surfit.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter "*.i"
# Begin Source File

SOURCE=.\..\src\surfit\interface\curv.i
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\interface\fileio.i
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\interface\func.i
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\interface\geom.i
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\interface\solve.i
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\interface\surfit.i

!IF  "$(CFG)" == "surfit - Win32 Release"

USERDEP__SURFI="../src/surfit/interface/fileio.i"	"../src/surfit/interface/solve.i"	"../src/surfit/interface/task.i"	"../src/surfit/interface/geom.i"	"../src/surfit/interface/func.i"	"../src/surfit/interface/curv.i"	
# Begin Custom Build
InputPath=.\..\src\surfit\interface\surfit.i

"../src/surfit/surfit_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	surfit_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

USERDEP__SURFI="../src/surfit/interface/fileio.i"	"../src/surfit/interface/solve.i"	"../src/surfit/interface/task.i"	"../src/surfit/interface/geom.i"	"../src/surfit/interface/func.i"	"../src/surfit/interface/curv.i"	
# Begin Custom Build
InputPath=.\..\src\surfit\interface\surfit.i

"../src/surfit/surfit_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	surfit_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\interface\task.i
# End Source File
# End Group
# Begin Group "Unix files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\AUTHORS
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\ChangeLog
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\configure.in
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\COPYING
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\INSTALL
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\Makefile.am
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\NEWS
# End Source File
# Begin Source File

SOURCE=.\..\src\surfit\README
# End Source File
# End Group
# Begin Group "Deprecated code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit\deprecated
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
