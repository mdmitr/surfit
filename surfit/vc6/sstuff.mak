# Microsoft Developer Studio Generated NMAKE File, Based on sstuff.dsp
!IF "$(CFG)" == ""
CFG=sstuff - Win32 Debug
!MESSAGE No configuration specified. Defaulting to sstuff - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "sstuff - Win32 Release" && "$(CFG)" != "sstuff - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sstuff.mak" CFG="sstuff - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sstuff - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sstuff - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sstuff - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

ALL : "..\bin\libsstuff.dll" "$(OUTDIR)\sstuff.bsc"


CLEAN :
	-@erase "$(INTDIR)\bitvec.obj"
	-@erase "$(INTDIR)\bitvec.sbr"
	-@erase "$(INTDIR)\boolvec.obj"
	-@erase "$(INTDIR)\boolvec.sbr"
	-@erase "$(INTDIR)\datafile.obj"
	-@erase "$(INTDIR)\datafile.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\geom_alg.obj"
	-@erase "$(INTDIR)\geom_alg.sbr"
	-@erase "$(INTDIR)\interp.obj"
	-@erase "$(INTDIR)\interp.sbr"
	-@erase "$(INTDIR)\intvec.obj"
	-@erase "$(INTDIR)\intvec.sbr"
	-@erase "$(INTDIR)\pasync.obj"
	-@erase "$(INTDIR)\pasync.sbr"
	-@erase "$(INTDIR)\patomic.obj"
	-@erase "$(INTDIR)\patomic.sbr"
	-@erase "$(INTDIR)\pexcept.obj"
	-@erase "$(INTDIR)\pexcept.sbr"
	-@erase "$(INTDIR)\pfatal.obj"
	-@erase "$(INTDIR)\pfatal.sbr"
	-@erase "$(INTDIR)\pmem.obj"
	-@erase "$(INTDIR)\pmem.sbr"
	-@erase "$(INTDIR)\pmsgq.obj"
	-@erase "$(INTDIR)\pmsgq.sbr"
	-@erase "$(INTDIR)\psemaphore.obj"
	-@erase "$(INTDIR)\psemaphore.sbr"
	-@erase "$(INTDIR)\pstring.obj"
	-@erase "$(INTDIR)\pstring.sbr"
	-@erase "$(INTDIR)\pthread.obj"
	-@erase "$(INTDIR)\pthread.sbr"
	-@erase "$(INTDIR)\ptimedsem.obj"
	-@erase "$(INTDIR)\ptimedsem.sbr"
	-@erase "$(INTDIR)\punknown.obj"
	-@erase "$(INTDIR)\punknown.sbr"
	-@erase "$(INTDIR)\read_txt.obj"
	-@erase "$(INTDIR)\read_txt.sbr"
	-@erase "$(INTDIR)\rnd.obj"
	-@erase "$(INTDIR)\rnd.sbr"
	-@erase "$(INTDIR)\shortvec.obj"
	-@erase "$(INTDIR)\shortvec.sbr"
	-@erase "$(INTDIR)\sstuff.obj"
	-@erase "$(INTDIR)\sstuff.sbr"
	-@erase "$(INTDIR)\stepFunc.obj"
	-@erase "$(INTDIR)\stepFunc.sbr"
	-@erase "$(INTDIR)\strvec.obj"
	-@erase "$(INTDIR)\strvec.sbr"
	-@erase "$(INTDIR)\threads.obj"
	-@erase "$(INTDIR)\threads.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vec.obj"
	-@erase "$(INTDIR)\vec.sbr"
	-@erase "$(INTDIR)\vec_alg.obj"
	-@erase "$(INTDIR)\vec_alg.sbr"
	-@erase "$(OUTDIR)\sstuff.bsc"
	-@erase "..\bin\libsstuff.dll"
	-@erase "..\bin\libsstuff.exp"
	-@erase "..\bin\libsstuff.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GR /GX /O2 /Op /Ob2 /I "../sstuff/src" /I "../src/sstuff/ptypes" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gs /Gs /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sstuff.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bitvec.sbr" \
	"$(INTDIR)\boolvec.sbr" \
	"$(INTDIR)\intvec.sbr" \
	"$(INTDIR)\shortvec.sbr" \
	"$(INTDIR)\strvec.sbr" \
	"$(INTDIR)\vec.sbr" \
	"$(INTDIR)\vec_alg.sbr" \
	"$(INTDIR)\pasync.sbr" \
	"$(INTDIR)\patomic.sbr" \
	"$(INTDIR)\pexcept.sbr" \
	"$(INTDIR)\pfatal.sbr" \
	"$(INTDIR)\pmem.sbr" \
	"$(INTDIR)\pmsgq.sbr" \
	"$(INTDIR)\psemaphore.sbr" \
	"$(INTDIR)\pstring.sbr" \
	"$(INTDIR)\pthread.sbr" \
	"$(INTDIR)\ptimedsem.sbr" \
	"$(INTDIR)\punknown.sbr" \
	"$(INTDIR)\datafile.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\geom_alg.sbr" \
	"$(INTDIR)\interp.sbr" \
	"$(INTDIR)\read_txt.sbr" \
	"$(INTDIR)\rnd.sbr" \
	"$(INTDIR)\sstuff.sbr" \
	"$(INTDIR)\stepFunc.sbr" \
	"$(INTDIR)\threads.sbr"

"$(OUTDIR)\sstuff.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libsstuff.pdb" /machine:I386 /out:"../bin/libsstuff.dll" /implib:"../bin/libsstuff.lib" 
LINK32_OBJS= \
	"$(INTDIR)\bitvec.obj" \
	"$(INTDIR)\boolvec.obj" \
	"$(INTDIR)\intvec.obj" \
	"$(INTDIR)\shortvec.obj" \
	"$(INTDIR)\strvec.obj" \
	"$(INTDIR)\vec.obj" \
	"$(INTDIR)\vec_alg.obj" \
	"$(INTDIR)\pasync.obj" \
	"$(INTDIR)\patomic.obj" \
	"$(INTDIR)\pexcept.obj" \
	"$(INTDIR)\pfatal.obj" \
	"$(INTDIR)\pmem.obj" \
	"$(INTDIR)\pmsgq.obj" \
	"$(INTDIR)\psemaphore.obj" \
	"$(INTDIR)\pstring.obj" \
	"$(INTDIR)\pthread.obj" \
	"$(INTDIR)\ptimedsem.obj" \
	"$(INTDIR)\punknown.obj" \
	"$(INTDIR)\datafile.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\geom_alg.obj" \
	"$(INTDIR)\interp.obj" \
	"$(INTDIR)\read_txt.obj" \
	"$(INTDIR)\rnd.obj" \
	"$(INTDIR)\sstuff.obj" \
	"$(INTDIR)\stepFunc.obj" \
	"$(INTDIR)\threads.obj"

"..\bin\libsstuff.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sstuff - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

ALL : "..\bin\libsstuff.dll" "$(OUTDIR)\sstuff.bsc"


CLEAN :
	-@erase "$(INTDIR)\bitvec.obj"
	-@erase "$(INTDIR)\bitvec.sbr"
	-@erase "$(INTDIR)\boolvec.obj"
	-@erase "$(INTDIR)\boolvec.sbr"
	-@erase "$(INTDIR)\datafile.obj"
	-@erase "$(INTDIR)\datafile.sbr"
	-@erase "$(INTDIR)\fileio.obj"
	-@erase "$(INTDIR)\fileio.sbr"
	-@erase "$(INTDIR)\geom_alg.obj"
	-@erase "$(INTDIR)\geom_alg.sbr"
	-@erase "$(INTDIR)\interp.obj"
	-@erase "$(INTDIR)\interp.sbr"
	-@erase "$(INTDIR)\intvec.obj"
	-@erase "$(INTDIR)\intvec.sbr"
	-@erase "$(INTDIR)\pasync.obj"
	-@erase "$(INTDIR)\pasync.sbr"
	-@erase "$(INTDIR)\patomic.obj"
	-@erase "$(INTDIR)\patomic.sbr"
	-@erase "$(INTDIR)\pexcept.obj"
	-@erase "$(INTDIR)\pexcept.sbr"
	-@erase "$(INTDIR)\pfatal.obj"
	-@erase "$(INTDIR)\pfatal.sbr"
	-@erase "$(INTDIR)\pmem.obj"
	-@erase "$(INTDIR)\pmem.sbr"
	-@erase "$(INTDIR)\pmsgq.obj"
	-@erase "$(INTDIR)\pmsgq.sbr"
	-@erase "$(INTDIR)\psemaphore.obj"
	-@erase "$(INTDIR)\psemaphore.sbr"
	-@erase "$(INTDIR)\pstring.obj"
	-@erase "$(INTDIR)\pstring.sbr"
	-@erase "$(INTDIR)\pthread.obj"
	-@erase "$(INTDIR)\pthread.sbr"
	-@erase "$(INTDIR)\ptimedsem.obj"
	-@erase "$(INTDIR)\ptimedsem.sbr"
	-@erase "$(INTDIR)\punknown.obj"
	-@erase "$(INTDIR)\punknown.sbr"
	-@erase "$(INTDIR)\read_txt.obj"
	-@erase "$(INTDIR)\read_txt.sbr"
	-@erase "$(INTDIR)\rnd.obj"
	-@erase "$(INTDIR)\rnd.sbr"
	-@erase "$(INTDIR)\shortvec.obj"
	-@erase "$(INTDIR)\shortvec.sbr"
	-@erase "$(INTDIR)\sstuff.obj"
	-@erase "$(INTDIR)\sstuff.sbr"
	-@erase "$(INTDIR)\stepFunc.obj"
	-@erase "$(INTDIR)\stepFunc.sbr"
	-@erase "$(INTDIR)\strvec.obj"
	-@erase "$(INTDIR)\strvec.sbr"
	-@erase "$(INTDIR)\threads.obj"
	-@erase "$(INTDIR)\threads.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vec.obj"
	-@erase "$(INTDIR)\vec.sbr"
	-@erase "$(INTDIR)\vec_alg.obj"
	-@erase "$(INTDIR)\vec_alg.sbr"
	-@erase "$(OUTDIR)\libsstuff.map"
	-@erase "$(OUTDIR)\sstuff.bsc"
	-@erase "..\bin\libsstuff.dll"
	-@erase "..\bin\libsstuff.exp"
	-@erase "..\bin\libsstuff.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/sstuff/ptypes" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sstuff.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\bitvec.sbr" \
	"$(INTDIR)\boolvec.sbr" \
	"$(INTDIR)\intvec.sbr" \
	"$(INTDIR)\shortvec.sbr" \
	"$(INTDIR)\strvec.sbr" \
	"$(INTDIR)\vec.sbr" \
	"$(INTDIR)\vec_alg.sbr" \
	"$(INTDIR)\pasync.sbr" \
	"$(INTDIR)\patomic.sbr" \
	"$(INTDIR)\pexcept.sbr" \
	"$(INTDIR)\pfatal.sbr" \
	"$(INTDIR)\pmem.sbr" \
	"$(INTDIR)\pmsgq.sbr" \
	"$(INTDIR)\psemaphore.sbr" \
	"$(INTDIR)\pstring.sbr" \
	"$(INTDIR)\pthread.sbr" \
	"$(INTDIR)\ptimedsem.sbr" \
	"$(INTDIR)\punknown.sbr" \
	"$(INTDIR)\datafile.sbr" \
	"$(INTDIR)\fileio.sbr" \
	"$(INTDIR)\geom_alg.sbr" \
	"$(INTDIR)\interp.sbr" \
	"$(INTDIR)\read_txt.sbr" \
	"$(INTDIR)\rnd.sbr" \
	"$(INTDIR)\sstuff.sbr" \
	"$(INTDIR)\stepFunc.sbr" \
	"$(INTDIR)\threads.sbr"

"$(OUTDIR)\sstuff.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib /nologo /dll /pdb:none /map:"$(INTDIR)\libsstuff.map" /debug /machine:I386 /out:"../bin/libsstuff.dll" /implib:"../bin/libsstuff.lib" 
LINK32_OBJS= \
	"$(INTDIR)\bitvec.obj" \
	"$(INTDIR)\boolvec.obj" \
	"$(INTDIR)\intvec.obj" \
	"$(INTDIR)\shortvec.obj" \
	"$(INTDIR)\strvec.obj" \
	"$(INTDIR)\vec.obj" \
	"$(INTDIR)\vec_alg.obj" \
	"$(INTDIR)\pasync.obj" \
	"$(INTDIR)\patomic.obj" \
	"$(INTDIR)\pexcept.obj" \
	"$(INTDIR)\pfatal.obj" \
	"$(INTDIR)\pmem.obj" \
	"$(INTDIR)\pmsgq.obj" \
	"$(INTDIR)\psemaphore.obj" \
	"$(INTDIR)\pstring.obj" \
	"$(INTDIR)\pthread.obj" \
	"$(INTDIR)\ptimedsem.obj" \
	"$(INTDIR)\punknown.obj" \
	"$(INTDIR)\datafile.obj" \
	"$(INTDIR)\fileio.obj" \
	"$(INTDIR)\geom_alg.obj" \
	"$(INTDIR)\interp.obj" \
	"$(INTDIR)\read_txt.obj" \
	"$(INTDIR)\rnd.obj" \
	"$(INTDIR)\sstuff.obj" \
	"$(INTDIR)\stepFunc.obj" \
	"$(INTDIR)\threads.obj"

"..\bin\libsstuff.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("sstuff.dep")
!INCLUDE "sstuff.dep"
!ELSE 
!MESSAGE Warning: cannot find "sstuff.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "sstuff - Win32 Release" || "$(CFG)" == "sstuff - Win32 Debug"
SOURCE=..\src\sstuff\bitvec.cpp

"$(INTDIR)\bitvec.obj"	"$(INTDIR)\bitvec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\boolvec.cpp

"$(INTDIR)\boolvec.obj"	"$(INTDIR)\boolvec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\intvec.cpp

"$(INTDIR)\intvec.obj"	"$(INTDIR)\intvec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\shortvec.cpp

"$(INTDIR)\shortvec.obj"	"$(INTDIR)\shortvec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\strvec.cpp

"$(INTDIR)\strvec.obj"	"$(INTDIR)\strvec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\vec.cpp

"$(INTDIR)\vec.obj"	"$(INTDIR)\vec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\vec_alg.cpp

"$(INTDIR)\vec_alg.obj"	"$(INTDIR)\vec_alg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pasync.cxx

"$(INTDIR)\pasync.obj"	"$(INTDIR)\pasync.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\patomic.cxx

"$(INTDIR)\patomic.obj"	"$(INTDIR)\patomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pexcept.cxx

"$(INTDIR)\pexcept.obj"	"$(INTDIR)\pexcept.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pfatal.cxx

"$(INTDIR)\pfatal.obj"	"$(INTDIR)\pfatal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pmem.cxx

"$(INTDIR)\pmem.obj"	"$(INTDIR)\pmem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pmsgq.cxx

"$(INTDIR)\pmsgq.obj"	"$(INTDIR)\pmsgq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\psemaphore.cxx

"$(INTDIR)\psemaphore.obj"	"$(INTDIR)\psemaphore.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pstring.cxx

"$(INTDIR)\pstring.obj"	"$(INTDIR)\pstring.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\pthread.cxx

"$(INTDIR)\pthread.obj"	"$(INTDIR)\pthread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\ptimedsem.cxx

"$(INTDIR)\ptimedsem.obj"	"$(INTDIR)\ptimedsem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\ptypes\punknown.cxx

"$(INTDIR)\punknown.obj"	"$(INTDIR)\punknown.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\datafile.cpp

"$(INTDIR)\datafile.obj"	"$(INTDIR)\datafile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\fileio.cpp

"$(INTDIR)\fileio.obj"	"$(INTDIR)\fileio.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\geom_alg.cpp

"$(INTDIR)\geom_alg.obj"	"$(INTDIR)\geom_alg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\interp.cpp

"$(INTDIR)\interp.obj"	"$(INTDIR)\interp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\read_txt.cpp

"$(INTDIR)\read_txt.obj"	"$(INTDIR)\read_txt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\rnd.cpp

"$(INTDIR)\rnd.obj"	"$(INTDIR)\rnd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\sstuff.cpp

"$(INTDIR)\sstuff.obj"	"$(INTDIR)\sstuff.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\stepFunc.cpp

"$(INTDIR)\stepFunc.obj"	"$(INTDIR)\stepFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\sstuff\threads.cpp

"$(INTDIR)\threads.obj"	"$(INTDIR)\threads.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

