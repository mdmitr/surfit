# Microsoft Developer Studio Generated NMAKE File, Based on freeflow.dsp
!IF "$(CFG)" == ""
CFG=freeflow - Win32 Debug
!MESSAGE No configuration specified. Defaulting to freeflow - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "freeflow - Win32 Release" && "$(CFG)" != "freeflow - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "freeflow - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libfreeflow.dll" "$(OUTDIR)\freeflow.bsc"

!ELSE 

ALL : "sstuff - Win32 Release" "surfit - Win32 Release" "..\bin\libfreeflow.dll" "$(OUTDIR)\freeflow.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"surfit - Win32 ReleaseCLEAN" "sstuff - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\f_lcm_simple.obj"
	-@erase "$(INTDIR)\f_lcm_simple.sbr"
	-@erase "$(INTDIR)\f_lcm_simple_tcl.obj"
	-@erase "$(INTDIR)\f_lcm_simple_tcl.sbr"
	-@erase "$(INTDIR)\flow.obj"
	-@erase "$(INTDIR)\flow.sbr"
	-@erase "$(INTDIR)\flow_data_manager.obj"
	-@erase "$(INTDIR)\flow_data_manager.sbr"
	-@erase "$(INTDIR)\flow_func_internal.obj"
	-@erase "$(INTDIR)\flow_func_internal.sbr"
	-@erase "$(INTDIR)\flow_func_tcl.obj"
	-@erase "$(INTDIR)\flow_func_tcl.sbr"
	-@erase "$(INTDIR)\flow_variables.obj"
	-@erase "$(INTDIR)\flow_variables.sbr"
	-@erase "$(INTDIR)\freeflow.obj"
	-@erase "$(INTDIR)\freeflow.sbr"
	-@erase "$(INTDIR)\freeflow_wrap.obj"
	-@erase "$(INTDIR)\freeflow_wrap.sbr"
	-@erase "$(INTDIR)\pcurvs_tcl.obj"
	-@erase "$(INTDIR)\pcurvs_tcl.sbr"
	-@erase "$(INTDIR)\prod_area.obj"
	-@erase "$(INTDIR)\prod_area.sbr"
	-@erase "$(INTDIR)\prod_cntr.obj"
	-@erase "$(INTDIR)\prod_cntr.sbr"
	-@erase "$(INTDIR)\prod_iso.obj"
	-@erase "$(INTDIR)\prod_iso.sbr"
	-@erase "$(INTDIR)\prod_points.obj"
	-@erase "$(INTDIR)\prod_points.sbr"
	-@erase "$(INTDIR)\prod_points_tcl.obj"
	-@erase "$(INTDIR)\prod_points_tcl.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\freeflow.bsc"
	-@erase "..\bin\libfreeflow.dll"
	-@erase "..\bin\libfreeflow.exp"
	-@erase "..\bin\libfreeflow.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GR /GX /O2 /Ob2 /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeflow.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\flow_func_internal.sbr" \
	"$(INTDIR)\flow_func_tcl.sbr" \
	"$(INTDIR)\prod_points.sbr" \
	"$(INTDIR)\prod_points_tcl.sbr" \
	"$(INTDIR)\pcurvs_tcl.sbr" \
	"$(INTDIR)\prod_area.sbr" \
	"$(INTDIR)\prod_cntr.sbr" \
	"$(INTDIR)\prod_iso.sbr" \
	"$(INTDIR)\f_lcm_simple.sbr" \
	"$(INTDIR)\f_lcm_simple_tcl.sbr" \
	"$(INTDIR)\flow.sbr" \
	"$(INTDIR)\flow_data_manager.sbr" \
	"$(INTDIR)\flow_variables.sbr" \
	"$(INTDIR)\freeflow.sbr" \
	"$(INTDIR)\freeflow_wrap.sbr"

"$(OUTDIR)\freeflow.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libfreeflow.pdb" /machine:I386 /out:"../bin/libfreeflow.dll" /implib:"../bin/libfreeflow.lib" 
LINK32_OBJS= \
	"$(INTDIR)\flow_func_internal.obj" \
	"$(INTDIR)\flow_func_tcl.obj" \
	"$(INTDIR)\prod_points.obj" \
	"$(INTDIR)\prod_points_tcl.obj" \
	"$(INTDIR)\pcurvs_tcl.obj" \
	"$(INTDIR)\prod_area.obj" \
	"$(INTDIR)\prod_cntr.obj" \
	"$(INTDIR)\prod_iso.obj" \
	"$(INTDIR)\f_lcm_simple.obj" \
	"$(INTDIR)\f_lcm_simple_tcl.obj" \
	"$(INTDIR)\flow.obj" \
	"$(INTDIR)\flow_data_manager.obj" \
	"$(INTDIR)\flow_variables.obj" \
	"$(INTDIR)\freeflow.obj" \
	"$(INTDIR)\freeflow_wrap.obj" \
	"..\bin\libsurfit.lib" \
	"..\bin\libsstuff.lib"

"..\bin\libfreeflow.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libfreeflow.dll" "$(OUTDIR)\freeflow.bsc"

!ELSE 

ALL : "sstuff - Win32 Debug" "surfit - Win32 Debug" "..\bin\libfreeflow.dll" "$(OUTDIR)\freeflow.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"surfit - Win32 DebugCLEAN" "sstuff - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\f_lcm_simple.obj"
	-@erase "$(INTDIR)\f_lcm_simple.sbr"
	-@erase "$(INTDIR)\f_lcm_simple_tcl.obj"
	-@erase "$(INTDIR)\f_lcm_simple_tcl.sbr"
	-@erase "$(INTDIR)\flow.obj"
	-@erase "$(INTDIR)\flow.sbr"
	-@erase "$(INTDIR)\flow_data_manager.obj"
	-@erase "$(INTDIR)\flow_data_manager.sbr"
	-@erase "$(INTDIR)\flow_func_internal.obj"
	-@erase "$(INTDIR)\flow_func_internal.sbr"
	-@erase "$(INTDIR)\flow_func_tcl.obj"
	-@erase "$(INTDIR)\flow_func_tcl.sbr"
	-@erase "$(INTDIR)\flow_variables.obj"
	-@erase "$(INTDIR)\flow_variables.sbr"
	-@erase "$(INTDIR)\freeflow.obj"
	-@erase "$(INTDIR)\freeflow.sbr"
	-@erase "$(INTDIR)\freeflow_wrap.obj"
	-@erase "$(INTDIR)\freeflow_wrap.sbr"
	-@erase "$(INTDIR)\pcurvs_tcl.obj"
	-@erase "$(INTDIR)\pcurvs_tcl.sbr"
	-@erase "$(INTDIR)\prod_area.obj"
	-@erase "$(INTDIR)\prod_area.sbr"
	-@erase "$(INTDIR)\prod_cntr.obj"
	-@erase "$(INTDIR)\prod_cntr.sbr"
	-@erase "$(INTDIR)\prod_iso.obj"
	-@erase "$(INTDIR)\prod_iso.sbr"
	-@erase "$(INTDIR)\prod_points.obj"
	-@erase "$(INTDIR)\prod_points.sbr"
	-@erase "$(INTDIR)\prod_points_tcl.obj"
	-@erase "$(INTDIR)\prod_points_tcl.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\freeflow.bsc"
	-@erase "..\bin\libfreeflow.dll"
	-@erase "..\bin\libfreeflow.exp"
	-@erase "..\bin\libfreeflow.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\freeflow.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeflow.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\flow_func_internal.sbr" \
	"$(INTDIR)\flow_func_tcl.sbr" \
	"$(INTDIR)\prod_points.sbr" \
	"$(INTDIR)\prod_points_tcl.sbr" \
	"$(INTDIR)\pcurvs_tcl.sbr" \
	"$(INTDIR)\prod_area.sbr" \
	"$(INTDIR)\prod_cntr.sbr" \
	"$(INTDIR)\prod_iso.sbr" \
	"$(INTDIR)\f_lcm_simple.sbr" \
	"$(INTDIR)\f_lcm_simple_tcl.sbr" \
	"$(INTDIR)\flow.sbr" \
	"$(INTDIR)\flow_data_manager.sbr" \
	"$(INTDIR)\flow_variables.sbr" \
	"$(INTDIR)\freeflow.sbr" \
	"$(INTDIR)\freeflow_wrap.sbr"

"$(OUTDIR)\freeflow.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib /nologo /dll /pdb:none /debug /machine:I386 /out:"../bin/libfreeflow.dll" /implib:"../bin/libfreeflow.lib" /libpath:"D:\fltk\lib" 
LINK32_OBJS= \
	"$(INTDIR)\flow_func_internal.obj" \
	"$(INTDIR)\flow_func_tcl.obj" \
	"$(INTDIR)\prod_points.obj" \
	"$(INTDIR)\prod_points_tcl.obj" \
	"$(INTDIR)\pcurvs_tcl.obj" \
	"$(INTDIR)\prod_area.obj" \
	"$(INTDIR)\prod_cntr.obj" \
	"$(INTDIR)\prod_iso.obj" \
	"$(INTDIR)\f_lcm_simple.obj" \
	"$(INTDIR)\f_lcm_simple_tcl.obj" \
	"$(INTDIR)\flow.obj" \
	"$(INTDIR)\flow_data_manager.obj" \
	"$(INTDIR)\flow_variables.obj" \
	"$(INTDIR)\freeflow.obj" \
	"$(INTDIR)\freeflow_wrap.obj" \
	"..\bin\libsurfit.lib" \
	"..\bin\libsstuff.lib"

"..\bin\libfreeflow.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("freeflow.dep")
!INCLUDE "freeflow.dep"
!ELSE 
!MESSAGE Warning: cannot find "freeflow.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "freeflow - Win32 Release" || "$(CFG)" == "freeflow - Win32 Debug"
SOURCE=.\..\src\freeflow\flow_func_internal.cpp

"$(INTDIR)\flow_func_internal.obj"	"$(INTDIR)\flow_func_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\freeflow\flow_func_tcl.cpp

"$(INTDIR)\flow_func_tcl.obj"	"$(INTDIR)\flow_func_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\prod_points.cpp

"$(INTDIR)\prod_points.obj"	"$(INTDIR)\prod_points.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\prod_points_tcl.cpp

"$(INTDIR)\prod_points_tcl.obj"	"$(INTDIR)\prod_points_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\pcurvs_tcl.cpp

"$(INTDIR)\pcurvs_tcl.obj"	"$(INTDIR)\pcurvs_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\prod_area.cpp

"$(INTDIR)\prod_area.obj"	"$(INTDIR)\prod_area.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\prod_cntr.cpp

"$(INTDIR)\prod_cntr.obj"	"$(INTDIR)\prod_cntr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\prod_iso.cpp

"$(INTDIR)\prod_iso.obj"	"$(INTDIR)\prod_iso.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\f_lcm_simple.cpp

"$(INTDIR)\f_lcm_simple.obj"	"$(INTDIR)\f_lcm_simple.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\f_lcm_simple_tcl.cpp

"$(INTDIR)\f_lcm_simple_tcl.obj"	"$(INTDIR)\f_lcm_simple_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\freeflow\flow.cpp

"$(INTDIR)\flow.obj"	"$(INTDIR)\flow.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\freeflow\flow_data_manager.cpp

"$(INTDIR)\flow_data_manager.obj"	"$(INTDIR)\flow_data_manager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\freeflow\flow_variables.cpp

"$(INTDIR)\flow_variables.obj"	"$(INTDIR)\flow_variables.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\freeflow\freeflow.cpp

"$(INTDIR)\freeflow.obj"	"$(INTDIR)\freeflow.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\freeflow\freeflow_wrap.cxx

!IF  "$(CFG)" == "freeflow - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GR /GX /Ob2 /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\freeflow_wrap.obj"	"$(INTDIR)\freeflow_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\freeflow.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\freeflow_wrap.obj"	"$(INTDIR)\freeflow_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\..\src\freeflow\interface\freeflow.i

!IF  "$(CFG)" == "freeflow - Win32 Release"

InputPath=.\..\src\freeflow\interface\freeflow.i
USERDEP__FREEF="../src/freeflow/interface/lcm.i"	"../src/freeflow/interface/flow_draw.i"	

"..\src\freeflow\freeflow_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__FREEF)
	<<tempfile.bat 
	@echo off 
	freeflow_swig.bat
<< 
	

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

InputPath=.\..\src\freeflow\interface\freeflow.i
USERDEP__FREEF="../src/freeflow/interface/lcm.i"	"../src/freeflow/interface/flow_draw.i"	

"..\src\freeflow\freeflow_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__FREEF)
	<<tempfile.bat 
	@echo off 
	freeflow_swig.bat
<< 
	

!ENDIF 

!IF  "$(CFG)" == "freeflow - Win32 Release"

"surfit - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Release" 
   cd "."

"surfit - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

"surfit - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Debug" 
   cd "."

"surfit - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "freeflow - Win32 Release"

"sstuff - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" 
   cd "."

"sstuff - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "freeflow - Win32 Debug"

"sstuff - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Debug" 
   cd "."

"sstuff - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 
