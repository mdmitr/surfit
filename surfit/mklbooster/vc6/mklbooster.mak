# Microsoft Developer Studio Generated NMAKE File, Based on mklbooster.dsp
!IF "$(CFG)" == ""
CFG=mklbooster - Win32 Debug
!MESSAGE No configuration specified. Defaulting to mklbooster - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "mklbooster - Win32 Release" && "$(CFG)" != "mklbooster - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mklbooster.mak" CFG="mklbooster - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mklbooster - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mklbooster - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "mklbooster - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libmklbooster.dll" "$(OUTDIR)\mklbooster.bsc"

!ELSE 

ALL : "..\bin\libmklbooster.dll" "$(OUTDIR)\mklbooster.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\mkl_cg.obj"
	-@erase "$(INTDIR)\mkl_cg.sbr"
	-@erase "$(INTDIR)\mkl_threads.obj"
	-@erase "$(INTDIR)\mkl_threads.sbr"
	-@erase "$(INTDIR)\mklbooster.obj"
	-@erase "$(INTDIR)\mklbooster.sbr"
	-@erase "$(INTDIR)\mklbooster_wrap.obj"
	-@erase "$(INTDIR)\mklbooster_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\mklbooster.bsc"
	-@erase "..\bin\libmklbooster.dll"
	-@erase "..\bin\libmklbooster.exp"
	-@erase "..\bin\libmklbooster.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /Ob2 /I "../../sstuff/src" /I "../../surfit/src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MKLBOOSTER_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mklbooster.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mklbooster.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\mkl_cg.sbr" \
	"$(INTDIR)\mkl_threads.sbr" \
	"$(INTDIR)\mklbooster.sbr" \
	"$(INTDIR)\mklbooster_wrap.sbr"

"$(OUTDIR)\mklbooster.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib mkl_c.lib libsstuff.lib libsurfit.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libmklbooster.pdb" /machine:I386 /out:"../bin/libmklbooster.dll" /implib:"../bin/libmklbooster.lib" /libpath:"../../bin" 
LINK32_OBJS= \
	"$(INTDIR)\mkl_cg.obj" \
	"$(INTDIR)\mkl_threads.obj" \
	"$(INTDIR)\mklbooster.obj" \
	"$(INTDIR)\mklbooster_wrap.obj"

"..\bin\libmklbooster.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mklbooster - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libmklbooster.dll" "$(OUTDIR)\mklbooster.bsc"

!ELSE 

ALL : "..\bin\libmklbooster.dll" "$(OUTDIR)\mklbooster.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\mkl_cg.obj"
	-@erase "$(INTDIR)\mkl_cg.sbr"
	-@erase "$(INTDIR)\mkl_threads.obj"
	-@erase "$(INTDIR)\mkl_threads.sbr"
	-@erase "$(INTDIR)\mklbooster.obj"
	-@erase "$(INTDIR)\mklbooster.sbr"
	-@erase "$(INTDIR)\mklbooster_wrap.obj"
	-@erase "$(INTDIR)\mklbooster_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\libmklbooster.pdb"
	-@erase "$(OUTDIR)\mklbooster.bsc"
	-@erase "..\bin\libmklbooster.dll"
	-@erase "..\bin\libmklbooster.exp"
	-@erase "..\bin\libmklbooster.ilk"
	-@erase "..\bin\libmklbooster.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "../../sstuff/src" /I "../../surfit/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MKLBOOSTER_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\mklbooster.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mklbooster.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\mkl_cg.sbr" \
	"$(INTDIR)\mkl_threads.sbr" \
	"$(INTDIR)\mklbooster.sbr" \
	"$(INTDIR)\mklbooster_wrap.sbr"

"$(OUTDIR)\mklbooster.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib mkl_c.lib libsurfit.lib libsstuff.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\libmklbooster.pdb" /debug /machine:I386 /out:"../bin/libmklbooster.dll" /implib:"../bin/libmklbooster.lib" /pdbtype:sept /libpath:"../../bin" 
LINK32_OBJS= \
	"$(INTDIR)\mkl_cg.obj" \
	"$(INTDIR)\mkl_threads.obj" \
	"$(INTDIR)\mklbooster.obj" \
	"$(INTDIR)\mklbooster_wrap.obj"

"..\bin\libmklbooster.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mklbooster.dep")
!INCLUDE "mklbooster.dep"
!ELSE 
!MESSAGE Warning: cannot find "mklbooster.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mklbooster - Win32 Release" || "$(CFG)" == "mklbooster - Win32 Debug"
SOURCE=..\src\mkl_cg.cpp

"$(INTDIR)\mkl_cg.obj"	"$(INTDIR)\mkl_cg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\mkl_threads.cpp

"$(INTDIR)\mkl_threads.obj"	"$(INTDIR)\mkl_threads.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\mklbooster.cpp

"$(INTDIR)\mklbooster.obj"	"$(INTDIR)\mklbooster.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\mklbooster_wrap.cxx

"$(INTDIR)\mklbooster_wrap.obj"	"$(INTDIR)\mklbooster_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\interface\mklbooster.i

!IF  "$(CFG)" == "mklbooster - Win32 Release"

!ELSEIF  "$(CFG)" == "mklbooster - Win32 Debug"

InputPath=..\src\interface\mklbooster.i

"..\src\mklbooster_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	mklbooster_swig.bat
<< 
	

!ENDIF 

!IF  "$(CFG)" == "mklbooster - Win32 Release"

!ELSEIF  "$(CFG)" == "mklbooster - Win32 Debug"

!ENDIF 

!IF  "$(CFG)" == "mklbooster - Win32 Release"

!ELSEIF  "$(CFG)" == "mklbooster - Win32 Debug"

!ENDIF 


!ENDIF 

