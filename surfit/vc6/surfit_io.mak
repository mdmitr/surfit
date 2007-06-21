# Microsoft Developer Studio Generated NMAKE File, Based on surfit_io.dsp
!IF "$(CFG)" == ""
CFG=surfit_io - Win32 Debug
!MESSAGE No configuration specified. Defaulting to surfit_io - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "surfit_io - Win32 Release" && "$(CFG)" != "surfit_io - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "surfit_io.mak" CFG="surfit_io - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "surfit_io - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "surfit_io - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "surfit_io - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libsurfit_io.dll" "$(OUTDIR)\surfit_io.bsc"

!ELSE 

ALL : "surfit - Win32 Release" "sstuff - Win32 Release" "..\bin\libsurfit_io.dll" "$(OUTDIR)\surfit_io.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"sstuff - Win32 ReleaseCLEAN" "surfit - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\area_bln.obj"
	-@erase "$(INTDIR)\area_bln.sbr"
	-@erase "$(INTDIR)\area_io_tcl.obj"
	-@erase "$(INTDIR)\area_io_tcl.sbr"
	-@erase "$(INTDIR)\area_shp.obj"
	-@erase "$(INTDIR)\area_shp.sbr"
	-@erase "$(INTDIR)\cntr_bln.obj"
	-@erase "$(INTDIR)\cntr_bln.sbr"
	-@erase "$(INTDIR)\cntr_io_tcl.obj"
	-@erase "$(INTDIR)\cntr_io_tcl.sbr"
	-@erase "$(INTDIR)\cntr_shp.obj"
	-@erase "$(INTDIR)\cntr_shp.sbr"
	-@erase "$(INTDIR)\curv_bln.obj"
	-@erase "$(INTDIR)\curv_bln.sbr"
	-@erase "$(INTDIR)\curv_io_tcl.obj"
	-@erase "$(INTDIR)\curv_io_tcl.sbr"
	-@erase "$(INTDIR)\curv_shp.obj"
	-@erase "$(INTDIR)\curv_shp.sbr"
	-@erase "$(INTDIR)\dbfopen.obj"
	-@erase "$(INTDIR)\dbfopen.sbr"
	-@erase "$(INTDIR)\EasyBMP.obj"
	-@erase "$(INTDIR)\EasyBMP.sbr"
	-@erase "$(INTDIR)\mask_grd.obj"
	-@erase "$(INTDIR)\mask_grd.sbr"
	-@erase "$(INTDIR)\mask_io_tcl.obj"
	-@erase "$(INTDIR)\mask_io_tcl.sbr"
	-@erase "$(INTDIR)\mask_xyz.obj"
	-@erase "$(INTDIR)\mask_xyz.sbr"
	-@erase "$(INTDIR)\pnts_io_tcl.obj"
	-@erase "$(INTDIR)\pnts_io_tcl.sbr"
	-@erase "$(INTDIR)\pnts_shp.obj"
	-@erase "$(INTDIR)\pnts_shp.sbr"
	-@erase "$(INTDIR)\shpopen.obj"
	-@erase "$(INTDIR)\shpopen.sbr"
	-@erase "$(INTDIR)\surf_arcgis.obj"
	-@erase "$(INTDIR)\surf_arcgis.sbr"
	-@erase "$(INTDIR)\surf_bmp.obj"
	-@erase "$(INTDIR)\surf_bmp.sbr"
	-@erase "$(INTDIR)\surf_gmt.obj"
	-@erase "$(INTDIR)\surf_gmt.sbr"
	-@erase "$(INTDIR)\surf_grass.obj"
	-@erase "$(INTDIR)\surf_grass.sbr"
	-@erase "$(INTDIR)\surf_grd.obj"
	-@erase "$(INTDIR)\surf_grd.sbr"
	-@erase "$(INTDIR)\surf_io_tcl.obj"
	-@erase "$(INTDIR)\surf_io_tcl.sbr"
	-@erase "$(INTDIR)\surf_jpg.obj"
	-@erase "$(INTDIR)\surf_jpg.sbr"
	-@erase "$(INTDIR)\surf_xyz.obj"
	-@erase "$(INTDIR)\surf_xyz.sbr"
	-@erase "$(INTDIR)\surfit_io.obj"
	-@erase "$(INTDIR)\surfit_io.sbr"
	-@erase "$(INTDIR)\surfit_io_data_manager.obj"
	-@erase "$(INTDIR)\surfit_io_data_manager.sbr"
	-@erase "$(INTDIR)\surfit_io_variables.obj"
	-@erase "$(INTDIR)\surfit_io_variables.sbr"
	-@erase "$(INTDIR)\surfit_io_wrap.obj"
	-@erase "$(INTDIR)\surfit_io_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\surfit_io.bsc"
	-@erase "..\bin\libsurfit_io.dll"
	-@erase "..\bin\libsurfit_io.exp"
	-@erase "..\bin\libsurfit_io.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /Ob2 /I "../src/sstuff" /I "../src/sstuff/ptypes" /I "../src/surfit" /I "..\..\libs\jpeg-6b\\" /I "../../libs/tcl8.3.5/generic" /I "..\..\libs\NETCDF\LIBSRC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\surfit_io.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\surfit_io.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\surf_arcgis.sbr" \
	"$(INTDIR)\surf_bmp.sbr" \
	"$(INTDIR)\surf_gmt.sbr" \
	"$(INTDIR)\surf_grass.sbr" \
	"$(INTDIR)\surf_grd.sbr" \
	"$(INTDIR)\surf_io_tcl.sbr" \
	"$(INTDIR)\surf_jpg.sbr" \
	"$(INTDIR)\surf_xyz.sbr" \
	"$(INTDIR)\EasyBMP.sbr" \
	"$(INTDIR)\dbfopen.sbr" \
	"$(INTDIR)\shpopen.sbr" \
	"$(INTDIR)\pnts_io_tcl.sbr" \
	"$(INTDIR)\pnts_shp.sbr" \
	"$(INTDIR)\curv_bln.sbr" \
	"$(INTDIR)\curv_io_tcl.sbr" \
	"$(INTDIR)\curv_shp.sbr" \
	"$(INTDIR)\area_bln.sbr" \
	"$(INTDIR)\area_io_tcl.sbr" \
	"$(INTDIR)\area_shp.sbr" \
	"$(INTDIR)\cntr_bln.sbr" \
	"$(INTDIR)\cntr_io_tcl.sbr" \
	"$(INTDIR)\cntr_shp.sbr" \
	"$(INTDIR)\mask_grd.sbr" \
	"$(INTDIR)\mask_io_tcl.sbr" \
	"$(INTDIR)\mask_xyz.sbr" \
	"$(INTDIR)\surfit_io.sbr" \
	"$(INTDIR)\surfit_io_data_manager.sbr" \
	"$(INTDIR)\surfit_io_variables.sbr" \
	"$(INTDIR)\surfit_io_wrap.sbr"

"$(OUTDIR)\surfit_io.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib zdll.lib netcdf.lib libjpeg.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libsurfit_io.pdb" /machine:I386 /nodefaultlib:"LIBC" /out:"../bin/libsurfit_io.dll" /implib:"../bin/libsurfit_io.lib" /libpath:"..\..\libs\jpeg-6b" /libpath:"..\..\libs\tcl8.3.5\win\RELEASE" /libpath:"..\..\libs\zlib123-dll\lib\\" /libpath:"..\..\libs\netcdf\libsrc\\" 
LINK32_OBJS= \
	"$(INTDIR)\surf_arcgis.obj" \
	"$(INTDIR)\surf_bmp.obj" \
	"$(INTDIR)\surf_gmt.obj" \
	"$(INTDIR)\surf_grass.obj" \
	"$(INTDIR)\surf_grd.obj" \
	"$(INTDIR)\surf_io_tcl.obj" \
	"$(INTDIR)\surf_jpg.obj" \
	"$(INTDIR)\surf_xyz.obj" \
	"$(INTDIR)\EasyBMP.obj" \
	"$(INTDIR)\dbfopen.obj" \
	"$(INTDIR)\shpopen.obj" \
	"$(INTDIR)\pnts_io_tcl.obj" \
	"$(INTDIR)\pnts_shp.obj" \
	"$(INTDIR)\curv_bln.obj" \
	"$(INTDIR)\curv_io_tcl.obj" \
	"$(INTDIR)\curv_shp.obj" \
	"$(INTDIR)\area_bln.obj" \
	"$(INTDIR)\area_io_tcl.obj" \
	"$(INTDIR)\area_shp.obj" \
	"$(INTDIR)\cntr_bln.obj" \
	"$(INTDIR)\cntr_io_tcl.obj" \
	"$(INTDIR)\cntr_shp.obj" \
	"$(INTDIR)\mask_grd.obj" \
	"$(INTDIR)\mask_io_tcl.obj" \
	"$(INTDIR)\mask_xyz.obj" \
	"$(INTDIR)\surfit_io.obj" \
	"$(INTDIR)\surfit_io_data_manager.obj" \
	"$(INTDIR)\surfit_io_variables.obj" \
	"$(INTDIR)\surfit_io_wrap.obj" \
	"..\bin\libsstuff.lib" \
	"..\bin\libsurfit.lib"

"..\bin\libsurfit_io.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "surfit_io - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libsurfit_io.dll" "$(OUTDIR)\surfit_io.bsc"

!ELSE 

ALL : "surfit - Win32 Debug" "sstuff - Win32 Debug" "..\bin\libsurfit_io.dll" "$(OUTDIR)\surfit_io.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"sstuff - Win32 DebugCLEAN" "surfit - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\area_bln.obj"
	-@erase "$(INTDIR)\area_bln.sbr"
	-@erase "$(INTDIR)\area_io_tcl.obj"
	-@erase "$(INTDIR)\area_io_tcl.sbr"
	-@erase "$(INTDIR)\area_shp.obj"
	-@erase "$(INTDIR)\area_shp.sbr"
	-@erase "$(INTDIR)\cntr_bln.obj"
	-@erase "$(INTDIR)\cntr_bln.sbr"
	-@erase "$(INTDIR)\cntr_io_tcl.obj"
	-@erase "$(INTDIR)\cntr_io_tcl.sbr"
	-@erase "$(INTDIR)\cntr_shp.obj"
	-@erase "$(INTDIR)\cntr_shp.sbr"
	-@erase "$(INTDIR)\curv_bln.obj"
	-@erase "$(INTDIR)\curv_bln.sbr"
	-@erase "$(INTDIR)\curv_io_tcl.obj"
	-@erase "$(INTDIR)\curv_io_tcl.sbr"
	-@erase "$(INTDIR)\curv_shp.obj"
	-@erase "$(INTDIR)\curv_shp.sbr"
	-@erase "$(INTDIR)\dbfopen.obj"
	-@erase "$(INTDIR)\dbfopen.sbr"
	-@erase "$(INTDIR)\EasyBMP.obj"
	-@erase "$(INTDIR)\EasyBMP.sbr"
	-@erase "$(INTDIR)\mask_grd.obj"
	-@erase "$(INTDIR)\mask_grd.sbr"
	-@erase "$(INTDIR)\mask_io_tcl.obj"
	-@erase "$(INTDIR)\mask_io_tcl.sbr"
	-@erase "$(INTDIR)\mask_xyz.obj"
	-@erase "$(INTDIR)\mask_xyz.sbr"
	-@erase "$(INTDIR)\pnts_io_tcl.obj"
	-@erase "$(INTDIR)\pnts_io_tcl.sbr"
	-@erase "$(INTDIR)\pnts_shp.obj"
	-@erase "$(INTDIR)\pnts_shp.sbr"
	-@erase "$(INTDIR)\shpopen.obj"
	-@erase "$(INTDIR)\shpopen.sbr"
	-@erase "$(INTDIR)\surf_arcgis.obj"
	-@erase "$(INTDIR)\surf_arcgis.sbr"
	-@erase "$(INTDIR)\surf_bmp.obj"
	-@erase "$(INTDIR)\surf_bmp.sbr"
	-@erase "$(INTDIR)\surf_gmt.obj"
	-@erase "$(INTDIR)\surf_gmt.sbr"
	-@erase "$(INTDIR)\surf_grass.obj"
	-@erase "$(INTDIR)\surf_grass.sbr"
	-@erase "$(INTDIR)\surf_grd.obj"
	-@erase "$(INTDIR)\surf_grd.sbr"
	-@erase "$(INTDIR)\surf_io_tcl.obj"
	-@erase "$(INTDIR)\surf_io_tcl.sbr"
	-@erase "$(INTDIR)\surf_jpg.obj"
	-@erase "$(INTDIR)\surf_jpg.sbr"
	-@erase "$(INTDIR)\surf_xyz.obj"
	-@erase "$(INTDIR)\surf_xyz.sbr"
	-@erase "$(INTDIR)\surfit_io.obj"
	-@erase "$(INTDIR)\surfit_io.sbr"
	-@erase "$(INTDIR)\surfit_io_data_manager.obj"
	-@erase "$(INTDIR)\surfit_io_data_manager.sbr"
	-@erase "$(INTDIR)\surfit_io_variables.obj"
	-@erase "$(INTDIR)\surfit_io_variables.sbr"
	-@erase "$(INTDIR)\surfit_io_wrap.obj"
	-@erase "$(INTDIR)\surfit_io_wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\libsurfit_io.pdb"
	-@erase "$(OUTDIR)\surfit_io.bsc"
	-@erase "..\bin\libsurfit_io.dll"
	-@erase "..\bin\libsurfit_io.exp"
	-@erase "..\bin\libsurfit_io.ilk"
	-@erase "..\bin\libsurfit_io.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/sstuff/ptypes" /I "../src/surfit" /I "..\..\LIBS\JPEG-6B" /I "../../libs/tcl8.3.5/generic" /I "..\..\libs\NETCDF\LIBSRC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\surfit_io.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\surfit_io.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\surf_arcgis.sbr" \
	"$(INTDIR)\surf_bmp.sbr" \
	"$(INTDIR)\surf_gmt.sbr" \
	"$(INTDIR)\surf_grass.sbr" \
	"$(INTDIR)\surf_grd.sbr" \
	"$(INTDIR)\surf_io_tcl.sbr" \
	"$(INTDIR)\surf_jpg.sbr" \
	"$(INTDIR)\surf_xyz.sbr" \
	"$(INTDIR)\EasyBMP.sbr" \
	"$(INTDIR)\dbfopen.sbr" \
	"$(INTDIR)\shpopen.sbr" \
	"$(INTDIR)\pnts_io_tcl.sbr" \
	"$(INTDIR)\pnts_shp.sbr" \
	"$(INTDIR)\curv_bln.sbr" \
	"$(INTDIR)\curv_io_tcl.sbr" \
	"$(INTDIR)\curv_shp.sbr" \
	"$(INTDIR)\area_bln.sbr" \
	"$(INTDIR)\area_io_tcl.sbr" \
	"$(INTDIR)\area_shp.sbr" \
	"$(INTDIR)\cntr_bln.sbr" \
	"$(INTDIR)\cntr_io_tcl.sbr" \
	"$(INTDIR)\cntr_shp.sbr" \
	"$(INTDIR)\mask_grd.sbr" \
	"$(INTDIR)\mask_io_tcl.sbr" \
	"$(INTDIR)\mask_xyz.sbr" \
	"$(INTDIR)\surfit_io.sbr" \
	"$(INTDIR)\surfit_io_data_manager.sbr" \
	"$(INTDIR)\surfit_io_variables.sbr" \
	"$(INTDIR)\surfit_io_wrap.sbr"

"$(OUTDIR)\surfit_io.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib netcdf.lib libjpeg.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\libsurfit_io.pdb" /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"../bin/libsurfit_io.dll" /implib:"../bin/libsurfit_io.lib" /pdbtype:sept /libpath:"..\..\libs\jpeg-6b" /libpath:"..\..\libs\NETCDF\LIBSRC" /libpath:"..\..\LIBS\TCL8.3.5\WIN\DEBUG" /libpath:"..\..\libs\jpeg-6b\\" 
LINK32_OBJS= \
	"$(INTDIR)\surf_arcgis.obj" \
	"$(INTDIR)\surf_bmp.obj" \
	"$(INTDIR)\surf_gmt.obj" \
	"$(INTDIR)\surf_grass.obj" \
	"$(INTDIR)\surf_grd.obj" \
	"$(INTDIR)\surf_io_tcl.obj" \
	"$(INTDIR)\surf_jpg.obj" \
	"$(INTDIR)\surf_xyz.obj" \
	"$(INTDIR)\EasyBMP.obj" \
	"$(INTDIR)\dbfopen.obj" \
	"$(INTDIR)\shpopen.obj" \
	"$(INTDIR)\pnts_io_tcl.obj" \
	"$(INTDIR)\pnts_shp.obj" \
	"$(INTDIR)\curv_bln.obj" \
	"$(INTDIR)\curv_io_tcl.obj" \
	"$(INTDIR)\curv_shp.obj" \
	"$(INTDIR)\area_bln.obj" \
	"$(INTDIR)\area_io_tcl.obj" \
	"$(INTDIR)\area_shp.obj" \
	"$(INTDIR)\cntr_bln.obj" \
	"$(INTDIR)\cntr_io_tcl.obj" \
	"$(INTDIR)\cntr_shp.obj" \
	"$(INTDIR)\mask_grd.obj" \
	"$(INTDIR)\mask_io_tcl.obj" \
	"$(INTDIR)\mask_xyz.obj" \
	"$(INTDIR)\surfit_io.obj" \
	"$(INTDIR)\surfit_io_data_manager.obj" \
	"$(INTDIR)\surfit_io_variables.obj" \
	"$(INTDIR)\surfit_io_wrap.obj" \
	"..\bin\libsstuff.lib" \
	"..\bin\libsurfit.lib"

"..\bin\libsurfit_io.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("surfit_io.dep")
!INCLUDE "surfit_io.dep"
!ELSE 
!MESSAGE Warning: cannot find "surfit_io.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "surfit_io - Win32 Release" || "$(CFG)" == "surfit_io - Win32 Debug"
SOURCE=..\src\surfit_io\surf_arcgis.cpp

"$(INTDIR)\surf_arcgis.obj"	"$(INTDIR)\surf_arcgis.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_bmp.cpp

"$(INTDIR)\surf_bmp.obj"	"$(INTDIR)\surf_bmp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_gmt.cpp

"$(INTDIR)\surf_gmt.obj"	"$(INTDIR)\surf_gmt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_grass.cpp

"$(INTDIR)\surf_grass.obj"	"$(INTDIR)\surf_grass.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_grd.cpp

"$(INTDIR)\surf_grd.obj"	"$(INTDIR)\surf_grd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_io_tcl.cpp

"$(INTDIR)\surf_io_tcl.obj"	"$(INTDIR)\surf_io_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_jpg.cpp

"$(INTDIR)\surf_jpg.obj"	"$(INTDIR)\surf_jpg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surf_xyz.cpp

"$(INTDIR)\surf_xyz.obj"	"$(INTDIR)\surf_xyz.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\EasyBmp\EasyBMP.cpp

"$(INTDIR)\EasyBMP.obj"	"$(INTDIR)\EasyBMP.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\shapelib\dbfopen.c

"$(INTDIR)\dbfopen.obj"	"$(INTDIR)\dbfopen.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\shapelib\shpopen.c

"$(INTDIR)\shpopen.obj"	"$(INTDIR)\shpopen.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\pnts_io_tcl.cpp

"$(INTDIR)\pnts_io_tcl.obj"	"$(INTDIR)\pnts_io_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\pnts_shp.cpp

"$(INTDIR)\pnts_shp.obj"	"$(INTDIR)\pnts_shp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\curv_bln.cpp

"$(INTDIR)\curv_bln.obj"	"$(INTDIR)\curv_bln.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\curv_io_tcl.cpp

"$(INTDIR)\curv_io_tcl.obj"	"$(INTDIR)\curv_io_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\curv_shp.cpp

"$(INTDIR)\curv_shp.obj"	"$(INTDIR)\curv_shp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\area_bln.cpp

"$(INTDIR)\area_bln.obj"	"$(INTDIR)\area_bln.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\area_io_tcl.cpp

"$(INTDIR)\area_io_tcl.obj"	"$(INTDIR)\area_io_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\area_shp.cpp

"$(INTDIR)\area_shp.obj"	"$(INTDIR)\area_shp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\cntr_bln.cpp

"$(INTDIR)\cntr_bln.obj"	"$(INTDIR)\cntr_bln.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\cntr_io_tcl.cpp

"$(INTDIR)\cntr_io_tcl.obj"	"$(INTDIR)\cntr_io_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\cntr_shp.cpp

"$(INTDIR)\cntr_shp.obj"	"$(INTDIR)\cntr_shp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\mask_grd.cpp

"$(INTDIR)\mask_grd.obj"	"$(INTDIR)\mask_grd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\mask_io_tcl.cpp

"$(INTDIR)\mask_io_tcl.obj"	"$(INTDIR)\mask_io_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\mask_xyz.cpp

"$(INTDIR)\mask_xyz.obj"	"$(INTDIR)\mask_xyz.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surfit_io.cpp

"$(INTDIR)\surfit_io.obj"	"$(INTDIR)\surfit_io.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surfit_io_data_manager.cpp

"$(INTDIR)\surfit_io_data_manager.obj"	"$(INTDIR)\surfit_io_data_manager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surfit_io_variables.cpp

"$(INTDIR)\surfit_io_variables.obj"	"$(INTDIR)\surfit_io_variables.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit_io\surfit_io_wrap.cxx

"$(INTDIR)\surfit_io_wrap.obj"	"$(INTDIR)\surfit_io_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit_io\interface\surfit_io.i

!IF  "$(CFG)" == "surfit_io - Win32 Release"

InputPath=.\..\src\surfit_io\interface\surfit_io.i

"..\src\surfit_io\surfit_io_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	surfit_io_swig.bat
<< 
	

!ELSEIF  "$(CFG)" == "surfit_io - Win32 Debug"

InputPath=.\..\src\surfit_io\interface\surfit_io.i

"..\src\surfit_io\surfit_io_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	surfit_io_swig.bat
<< 
	

!ENDIF 

!IF  "$(CFG)" == "surfit_io - Win32 Release"

"sstuff - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" 
   cd "."

"sstuff - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "surfit_io - Win32 Debug"

"sstuff - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Debug" 
   cd "."

"sstuff - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

!IF  "$(CFG)" == "surfit_io - Win32 Release"

"surfit - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Release" 
   cd "."

"surfit - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "surfit_io - Win32 Debug"

"surfit - Win32 Debug" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Debug" 
   cd "."

"surfit - Win32 DebugCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\surfit.mak CFG="surfit - Win32 Debug" RECURSE=1 CLEAN 
   cd "."

!ENDIF 


!ENDIF 

