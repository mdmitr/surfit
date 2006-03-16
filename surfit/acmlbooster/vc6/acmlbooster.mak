# Microsoft Developer Studio Generated NMAKE File, Based on acmlbooster.dsp
!IF "$(CFG)" == ""
CFG=acmlbooster - Win32 Debug
!MESSAGE No configuration specified. Defaulting to acmlbooster - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "acmlbooster - Win32 Release" && "$(CFG)" != "acmlbooster - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "acmlbooster.mak" CFG="acmlbooster - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "acmlbooster - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "acmlbooster - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "acmlbooster - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libacmlbooster.dll" "$(OUTDIR)\acmlbooster.bsc"

!ELSE 

ALL : "..\bin\libacmlbooster.dll" "$(OUTDIR)\acmlbooster.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\acml_cg.obj"
	-@erase "$(INTDIR)\acml_cg.sbr"
	-@erase "$(INTDIR)\acml_threads.obj"
	-@erase "$(INTDIR)\acml_threads.sbr"
	-@erase "$(INTDIR)\acmlbooster.obj"
	-@erase "$(INTDIR)\acmlbooster.sbr"
	-@erase "$(INTDIR)\acmlbooster_wrap.obj"
	-@erase "$(INTDIR)\acmlbooster_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\acmlbooster.bsc"
	-@erase "..\bin\libacmlbooster.dll"
	-@erase "..\bin\libacmlbooster.exp"
	-@erase "..\bin\libacmlbooster.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /Ob2 /I "../../sstuff/src" /I "../../surfit/src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ACMLBOOSTER_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\acmlbooster.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\acmlbooster.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\acml_cg.sbr" \
	"$(INTDIR)\acml_threads.sbr" \
	"$(INTDIR)\acmlbooster.sbr" \
	"$(INTDIR)\acmlbooster_wrap.sbr"

"$(OUTDIR)\acmlbooster.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib libacml.lib libsstuff.lib libsurfit.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libacmlbooster.pdb" /machine:I386 /out:"../bin/libacmlbooster.dll" /implib:"../bin/libacmlbooster.lib" /libpath:"../../bin" 
LINK32_OBJS= \
	"$(INTDIR)\acml_cg.obj" \
	"$(INTDIR)\acml_threads.obj" \
	"$(INTDIR)\acmlbooster.obj" \
	"$(INTDIR)\acmlbooster_wrap.obj"

"..\bin\libacmlbooster.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "acmlbooster - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libacmlbooster.dll" "$(OUTDIR)\acmlbooster.bsc"

!ELSE 

ALL : "..\bin\libacmlbooster.dll" "$(OUTDIR)\acmlbooster.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\acml_cg.obj"
	-@erase "$(INTDIR)\acml_cg.sbr"
	-@erase "$(INTDIR)\acml_threads.obj"
	-@erase "$(INTDIR)\acml_threads.sbr"
	-@erase "$(INTDIR)\acmlbooster.obj"
	-@erase "$(INTDIR)\acmlbooster.sbr"
	-@erase "$(INTDIR)\acmlbooster_wrap.obj"
	-@erase "$(INTDIR)\acmlbooster_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\acmlbooster.bsc"
	-@erase "$(OUTDIR)\libacmlbooster.pdb"
	-@erase "..\bin\libacmlbooster.dll"
	-@erase "..\bin\libacmlbooster.exp"
	-@erase "..\bin\libacmlbooster.ilk"
	-@erase "..\bin\libacmlbooster.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "../../sstuff/src" /I "../../surfit/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ACMLBOOSTER_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\acmlbooster.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\acmlbooster.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\acml_cg.sbr" \
	"$(INTDIR)\acml_threads.sbr" \
	"$(INTDIR)\acmlbooster.sbr" \
	"$(INTDIR)\acmlbooster_wrap.sbr"

"$(OUTDIR)\acmlbooster.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib libacml.lib libsurfit.lib libsstuff.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\libacmlbooster.pdb" /debug /machine:I386 /out:"../bin/libacmlbooster.dll" /implib:"../bin/libacmlbooster.lib" /pdbtype:sept /libpath:"../../bin" 
LINK32_OBJS= \
	"$(INTDIR)\acml_cg.obj" \
	"$(INTDIR)\acml_threads.obj" \
	"$(INTDIR)\acmlbooster.obj" \
	"$(INTDIR)\acmlbooster_wrap.obj"

"..\bin\libacmlbooster.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("acmlbooster.dep")
!INCLUDE "acmlbooster.dep"
!ELSE 
!MESSAGE Warning: cannot find "acmlbooster.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "acmlbooster - Win32 Release" || "$(CFG)" == "acmlbooster - Win32 Debug"
SOURCE=..\src\acml_cg.cpp

"$(INTDIR)\acml_cg.obj"	"$(INTDIR)\acml_cg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\acml_threads.cpp

"$(INTDIR)\acml_threads.obj"	"$(INTDIR)\acml_threads.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\acmlbooster.cpp

"$(INTDIR)\acmlbooster.obj"	"$(INTDIR)\acmlbooster.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\acmlbooster_wrap.cxx

"$(INTDIR)\acmlbooster_wrap.obj"	"$(INTDIR)\acmlbooster_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\interface\acmlbooster.i

!IF  "$(CFG)" == "acmlbooster - Win32 Release"

!ELSEIF  "$(CFG)" == "acmlbooster - Win32 Debug"

InputPath=..\src\interface\acmlbooster.i

"..\src\acmlbooster_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	acmlbooster_swig.bat
<< 
	

!ENDIF 

!IF  "$(CFG)" == "acmlbooster - Win32 Release"

!ELSEIF  "$(CFG)" == "acmlbooster - Win32 Debug"

!ENDIF 

!IF  "$(CFG)" == "acmlbooster - Win32 Release"

!ELSEIF  "$(CFG)" == "acmlbooster - Win32 Debug"

!ENDIF 


!ENDIF 

