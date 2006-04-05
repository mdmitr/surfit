# Microsoft Developer Studio Generated NMAKE File, Based on globe.dsp
!IF "$(CFG)" == ""
CFG=globe - Win32 Debug
!MESSAGE No configuration specified. Defaulting to globe - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "globe - Win32 Release" && "$(CFG)" != "globe - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "globe - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libglobe.dll" "$(OUTDIR)\globe.bsc"

!ELSE 

ALL : "sstuff - Win32 Release" "surfit - Win32 Release" "..\bin\libglobe.dll" "$(OUTDIR)\globe.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"surfit - Win32 ReleaseCLEAN" "sstuff - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dem.obj"
	-@erase "$(INTDIR)\dem.sbr"
	-@erase "$(INTDIR)\dem_internal.obj"
	-@erase "$(INTDIR)\dem_internal.sbr"
	-@erase "$(INTDIR)\dem_tcl.obj"
	-@erase "$(INTDIR)\dem_tcl.sbr"
	-@erase "$(INTDIR)\dems_tcl.obj"
	-@erase "$(INTDIR)\dems_tcl.sbr"
	-@erase "$(INTDIR)\f_dem.obj"
	-@erase "$(INTDIR)\f_dem.sbr"
	-@erase "$(INTDIR)\globe.obj"
	-@erase "$(INTDIR)\globe.sbr"
	-@erase "$(INTDIR)\globe_data_manager.obj"
	-@erase "$(INTDIR)\globe_data_manager.sbr"
	-@erase "$(INTDIR)\globe_surf_internal.obj"
	-@erase "$(INTDIR)\globe_surf_internal.sbr"
	-@erase "$(INTDIR)\globe_surf_tcl.obj"
	-@erase "$(INTDIR)\globe_surf_tcl.sbr"
	-@erase "$(INTDIR)\globe_variables.obj"
	-@erase "$(INTDIR)\globe_variables.sbr"
	-@erase "$(INTDIR)\globe_wrap.obj"
	-@erase "$(INTDIR)\globe_wrap.sbr"
	-@erase "$(INTDIR)\ioapi.obj"
	-@erase "$(INTDIR)\ioapi.sbr"
	-@erase "$(INTDIR)\shortmrf.obj"
	-@erase "$(INTDIR)\shortmrf.sbr"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\unzip.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\globe.bsc"
	-@erase "..\bin\libglobe.dll"
	-@erase "..\bin\libglobe.exp"
	-@erase "..\bin\libglobe.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GR /GX /O2 /Ob2 /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\globe.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\globe.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dem.sbr" \
	"$(INTDIR)\dem_internal.sbr" \
	"$(INTDIR)\dem_tcl.sbr" \
	"$(INTDIR)\globe_surf_internal.sbr" \
	"$(INTDIR)\globe_surf_tcl.sbr" \
	"$(INTDIR)\dems_tcl.sbr" \
	"$(INTDIR)\f_dem.sbr" \
	"$(INTDIR)\ioapi.sbr" \
	"$(INTDIR)\unzip.sbr" \
	"$(INTDIR)\globe.sbr" \
	"$(INTDIR)\globe_data_manager.sbr" \
	"$(INTDIR)\globe_variables.sbr" \
	"$(INTDIR)\globe_wrap.sbr" \
	"$(INTDIR)\shortmrf.sbr"

"$(OUTDIR)\globe.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib zdll.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libglobe.pdb" /machine:I386 /out:"../bin/libglobe.dll" /implib:"../bin/libglobe.lib" 
LINK32_OBJS= \
	"$(INTDIR)\dem.obj" \
	"$(INTDIR)\dem_internal.obj" \
	"$(INTDIR)\dem_tcl.obj" \
	"$(INTDIR)\globe_surf_internal.obj" \
	"$(INTDIR)\globe_surf_tcl.obj" \
	"$(INTDIR)\dems_tcl.obj" \
	"$(INTDIR)\f_dem.obj" \
	"$(INTDIR)\ioapi.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\globe.obj" \
	"$(INTDIR)\globe_data_manager.obj" \
	"$(INTDIR)\globe_variables.obj" \
	"$(INTDIR)\globe_wrap.obj" \
	"$(INTDIR)\shortmrf.obj" \
	"..\bin\libsurfit.lib" \
	"..\bin\libsstuff.lib"

"..\bin\libglobe.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libglobe.dll" "$(OUTDIR)\globe.bsc"

!ELSE 

ALL : "sstuff - Win32 Debug" "surfit - Win32 Debug" "..\bin\libglobe.dll" "$(OUTDIR)\globe.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"surfit - Win32 DebugCLEAN" "sstuff - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\dem.obj"
	-@erase "$(INTDIR)\dem.sbr"
	-@erase "$(INTDIR)\dem_internal.obj"
	-@erase "$(INTDIR)\dem_internal.sbr"
	-@erase "$(INTDIR)\dem_tcl.obj"
	-@erase "$(INTDIR)\dem_tcl.sbr"
	-@erase "$(INTDIR)\dems_tcl.obj"
	-@erase "$(INTDIR)\dems_tcl.sbr"
	-@erase "$(INTDIR)\f_dem.obj"
	-@erase "$(INTDIR)\f_dem.sbr"
	-@erase "$(INTDIR)\globe.obj"
	-@erase "$(INTDIR)\globe.sbr"
	-@erase "$(INTDIR)\globe_data_manager.obj"
	-@erase "$(INTDIR)\globe_data_manager.sbr"
	-@erase "$(INTDIR)\globe_surf_internal.obj"
	-@erase "$(INTDIR)\globe_surf_internal.sbr"
	-@erase "$(INTDIR)\globe_surf_tcl.obj"
	-@erase "$(INTDIR)\globe_surf_tcl.sbr"
	-@erase "$(INTDIR)\globe_variables.obj"
	-@erase "$(INTDIR)\globe_variables.sbr"
	-@erase "$(INTDIR)\globe_wrap.obj"
	-@erase "$(INTDIR)\globe_wrap.sbr"
	-@erase "$(INTDIR)\ioapi.obj"
	-@erase "$(INTDIR)\ioapi.sbr"
	-@erase "$(INTDIR)\shortmrf.obj"
	-@erase "$(INTDIR)\shortmrf.sbr"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\unzip.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\globe.bsc"
	-@erase "$(OUTDIR)\libglobe.pdb"
	-@erase "..\bin\libglobe.dll"
	-@erase "..\bin\libglobe.exp"
	-@erase "..\bin\libglobe.ilk"
	-@erase "..\bin\libglobe.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\globe.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\globe.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dem.sbr" \
	"$(INTDIR)\dem_internal.sbr" \
	"$(INTDIR)\dem_tcl.sbr" \
	"$(INTDIR)\globe_surf_internal.sbr" \
	"$(INTDIR)\globe_surf_tcl.sbr" \
	"$(INTDIR)\dems_tcl.sbr" \
	"$(INTDIR)\f_dem.sbr" \
	"$(INTDIR)\ioapi.sbr" \
	"$(INTDIR)\unzip.sbr" \
	"$(INTDIR)\globe.sbr" \
	"$(INTDIR)\globe_data_manager.sbr" \
	"$(INTDIR)\globe_variables.sbr" \
	"$(INTDIR)\globe_wrap.sbr" \
	"$(INTDIR)\shortmrf.sbr"

"$(OUTDIR)\globe.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib zdll.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\libglobe.pdb" /debug /machine:I386 /out:"../bin/libglobe.dll" /implib:"../bin/libglobe.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dem.obj" \
	"$(INTDIR)\dem_internal.obj" \
	"$(INTDIR)\dem_tcl.obj" \
	"$(INTDIR)\globe_surf_internal.obj" \
	"$(INTDIR)\globe_surf_tcl.obj" \
	"$(INTDIR)\dems_tcl.obj" \
	"$(INTDIR)\f_dem.obj" \
	"$(INTDIR)\ioapi.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\globe.obj" \
	"$(INTDIR)\globe_data_manager.obj" \
	"$(INTDIR)\globe_variables.obj" \
	"$(INTDIR)\globe_wrap.obj" \
	"$(INTDIR)\shortmrf.obj" \
	"..\bin\libsurfit.lib" \
	"..\bin\libsstuff.lib"

"..\bin\libglobe.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("globe.dep")
!INCLUDE "globe.dep"
!ELSE 
!MESSAGE Warning: cannot find "globe.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "globe - Win32 Release" || "$(CFG)" == "globe - Win32 Debug"
SOURCE=..\src\globe\dem.cpp

"$(INTDIR)\dem.obj"	"$(INTDIR)\dem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\dem_internal.cpp

"$(INTDIR)\dem_internal.obj"	"$(INTDIR)\dem_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\dem_tcl.cpp

"$(INTDIR)\dem_tcl.obj"	"$(INTDIR)\dem_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\globe_surf_internal.cpp

"$(INTDIR)\globe_surf_internal.obj"	"$(INTDIR)\globe_surf_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\globe_surf_tcl.cpp

"$(INTDIR)\globe_surf_tcl.obj"	"$(INTDIR)\globe_surf_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\dems_tcl.cpp

"$(INTDIR)\dems_tcl.obj"	"$(INTDIR)\dems_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\f_dem.cpp

"$(INTDIR)\f_dem.obj"	"$(INTDIR)\f_dem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\minizip\ioapi.c

"$(INTDIR)\ioapi.obj"	"$(INTDIR)\ioapi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\minizip\unzip.c

"$(INTDIR)\unzip.obj"	"$(INTDIR)\unzip.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\globe\globe.cpp

"$(INTDIR)\globe.obj"	"$(INTDIR)\globe.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\globe_data_manager.cpp

"$(INTDIR)\globe_data_manager.obj"	"$(INTDIR)\globe_data_manager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\globe\globe_variables.cpp

"$(INTDIR)\globe_variables.obj"	"$(INTDIR)\globe_variables.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\globe\globe_wrap.cxx

!IF  "$(CFG)" == "globe - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GR /GX /Ob2 /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\globe.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\globe_wrap.obj"	"$(INTDIR)\globe_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/surfit" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GLOBE_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\globe.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\globe_wrap.obj"	"$(INTDIR)\globe_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\src\globe\shortmrf.cpp

"$(INTDIR)\shortmrf.obj"	"$(INTDIR)\shortmrf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\globe\interface\globe.i

!IF  "$(CFG)" == "globe - Win32 Release"

InputPath=.\..\src\globe\interface\globe.i
USERDEP__GLOBE="../src/freeflow/interface/flow_draw.i"	

"..\src\globe\globe_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__GLOBE)
	<<tempfile.bat 
	@echo off 
	globe_swig.bat
<< 
	

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

InputPath=.\..\src\globe\interface\globe.i
USERDEP__GLOBE="../src/freeflow/interface/flow_draw.i"	

"..\src\globe\globe_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__GLOBE)
	<<tempfile.bat 
	@echo off 
	globe_swig.bat
<< 
	

!ENDIF 

!IF  "$(CFG)" == "globe - Win32 Release"

"surfit - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Release" 
   cd "."

"surfit - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

"surfit - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Debug" 
   cd "."

"surfit - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "globe - Win32 Release"

"sstuff - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" 
   cd "."

"sstuff - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "globe - Win32 Debug"

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

