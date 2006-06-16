# Microsoft Developer Studio Generated NMAKE File, Based on surfit.dsp
!IF "$(CFG)" == ""
CFG=surfit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to surfit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "surfit - Win32 Release" && "$(CFG)" != "surfit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "surfit - Win32 Release"

OUTDIR=.\../Release
INTDIR=.\../Release
# Begin Custom Macros
OutDir=.\../Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libsurfit.dll" "$(OUTDIR)\surfit.bsc"

!ELSE 

ALL : "sstuff - Win32 Release" "..\bin\libsurfit.dll" "$(OUTDIR)\surfit.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"sstuff - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\area.obj"
	-@erase "$(INTDIR)\area.sbr"
	-@erase "$(INTDIR)\area_internal.obj"
	-@erase "$(INTDIR)\area_internal.sbr"
	-@erase "$(INTDIR)\area_tcl.obj"
	-@erase "$(INTDIR)\area_tcl.sbr"
	-@erase "$(INTDIR)\CG.obj"
	-@erase "$(INTDIR)\CG.sbr"
	-@erase "$(INTDIR)\cmofs.obj"
	-@erase "$(INTDIR)\cmofs.sbr"
	-@erase "$(INTDIR)\cntr.obj"
	-@erase "$(INTDIR)\cntr.sbr"
	-@erase "$(INTDIR)\cntr_internal.obj"
	-@erase "$(INTDIR)\cntr_internal.sbr"
	-@erase "$(INTDIR)\cntr_tcl.obj"
	-@erase "$(INTDIR)\cntr_tcl.sbr"
	-@erase "$(INTDIR)\curv.obj"
	-@erase "$(INTDIR)\curv.sbr"
	-@erase "$(INTDIR)\curv_internal.obj"
	-@erase "$(INTDIR)\curv_internal.sbr"
	-@erase "$(INTDIR)\curv_tcl.obj"
	-@erase "$(INTDIR)\curv_tcl.sbr"
	-@erase "$(INTDIR)\curvs_tcl.obj"
	-@erase "$(INTDIR)\curvs_tcl.sbr"
	-@erase "$(INTDIR)\data.obj"
	-@erase "$(INTDIR)\data.sbr"
	-@erase "$(INTDIR)\data_manager.obj"
	-@erase "$(INTDIR)\data_manager.sbr"
	-@erase "$(INTDIR)\dbfopen.obj"
	-@erase "$(INTDIR)\dbfopen.sbr"
	-@erase "$(INTDIR)\f_area.obj"
	-@erase "$(INTDIR)\f_area.sbr"
	-@erase "$(INTDIR)\f_area_ineq.obj"
	-@erase "$(INTDIR)\f_area_ineq.sbr"
	-@erase "$(INTDIR)\f_area_mean.obj"
	-@erase "$(INTDIR)\f_area_mean.sbr"
	-@erase "$(INTDIR)\f_area_surf.obj"
	-@erase "$(INTDIR)\f_area_surf.sbr"
	-@erase "$(INTDIR)\f_area_surf_ineq.obj"
	-@erase "$(INTDIR)\f_area_surf_ineq.sbr"
	-@erase "$(INTDIR)\f_area_wmean.obj"
	-@erase "$(INTDIR)\f_area_wmean.sbr"
	-@erase "$(INTDIR)\f_cntr.obj"
	-@erase "$(INTDIR)\f_cntr.sbr"
	-@erase "$(INTDIR)\f_cntr_ineq.obj"
	-@erase "$(INTDIR)\f_cntr_ineq.sbr"
	-@erase "$(INTDIR)\f_completer.obj"
	-@erase "$(INTDIR)\f_completer.sbr"
	-@erase "$(INTDIR)\f_curv.obj"
	-@erase "$(INTDIR)\f_curv.sbr"
	-@erase "$(INTDIR)\f_curv_ineq.obj"
	-@erase "$(INTDIR)\f_curv_ineq.sbr"
	-@erase "$(INTDIR)\f_curv_surf.obj"
	-@erase "$(INTDIR)\f_curv_surf.sbr"
	-@erase "$(INTDIR)\f_curv_surf_ineq.obj"
	-@erase "$(INTDIR)\f_curv_surf_ineq.sbr"
	-@erase "$(INTDIR)\f_hist.obj"
	-@erase "$(INTDIR)\f_hist.sbr"
	-@erase "$(INTDIR)\f_ineq.obj"
	-@erase "$(INTDIR)\f_ineq.sbr"
	-@erase "$(INTDIR)\f_mask.obj"
	-@erase "$(INTDIR)\f_mask.sbr"
	-@erase "$(INTDIR)\f_mean.obj"
	-@erase "$(INTDIR)\f_mean.sbr"
	-@erase "$(INTDIR)\f_points.obj"
	-@erase "$(INTDIR)\f_points.sbr"
	-@erase "$(INTDIR)\f_points_ineq.obj"
	-@erase "$(INTDIR)\f_points_ineq.sbr"
	-@erase "$(INTDIR)\f_points_tcl.obj"
	-@erase "$(INTDIR)\f_points_tcl.sbr"
	-@erase "$(INTDIR)\f_surf.obj"
	-@erase "$(INTDIR)\f_surf.sbr"
	-@erase "$(INTDIR)\f_surf_ineq.obj"
	-@erase "$(INTDIR)\f_surf_ineq.sbr"
	-@erase "$(INTDIR)\f_trend.obj"
	-@erase "$(INTDIR)\f_trend.sbr"
	-@erase "$(INTDIR)\f_value.obj"
	-@erase "$(INTDIR)\f_value.sbr"
	-@erase "$(INTDIR)\f_wmean.obj"
	-@erase "$(INTDIR)\f_wmean.sbr"
	-@erase "$(INTDIR)\free_elements.obj"
	-@erase "$(INTDIR)\free_elements.sbr"
	-@erase "$(INTDIR)\functional.obj"
	-@erase "$(INTDIR)\functional.sbr"
	-@erase "$(INTDIR)\grid.obj"
	-@erase "$(INTDIR)\grid.sbr"
	-@erase "$(INTDIR)\grid_internal.obj"
	-@erase "$(INTDIR)\grid_internal.sbr"
	-@erase "$(INTDIR)\grid_line.obj"
	-@erase "$(INTDIR)\grid_line.sbr"
	-@erase "$(INTDIR)\grid_line_internal.obj"
	-@erase "$(INTDIR)\grid_line_internal.sbr"
	-@erase "$(INTDIR)\grid_line_tcl.obj"
	-@erase "$(INTDIR)\grid_line_tcl.sbr"
	-@erase "$(INTDIR)\grid_line_user.obj"
	-@erase "$(INTDIR)\grid_line_user.sbr"
	-@erase "$(INTDIR)\grid_tcl.obj"
	-@erase "$(INTDIR)\grid_tcl.sbr"
	-@erase "$(INTDIR)\grid_user.obj"
	-@erase "$(INTDIR)\grid_user.sbr"
	-@erase "$(INTDIR)\hist.obj"
	-@erase "$(INTDIR)\hist.sbr"
	-@erase "$(INTDIR)\hist_internal.obj"
	-@erase "$(INTDIR)\hist_internal.sbr"
	-@erase "$(INTDIR)\hist_tcl.obj"
	-@erase "$(INTDIR)\hist_tcl.sbr"
	-@erase "$(INTDIR)\J.obj"
	-@erase "$(INTDIR)\J.sbr"
	-@erase "$(INTDIR)\JCG.obj"
	-@erase "$(INTDIR)\JCG.sbr"
	-@erase "$(INTDIR)\license.obj"
	-@erase "$(INTDIR)\license.sbr"
	-@erase "$(INTDIR)\mask.obj"
	-@erase "$(INTDIR)\mask.sbr"
	-@erase "$(INTDIR)\mask_internal.obj"
	-@erase "$(INTDIR)\mask_internal.sbr"
	-@erase "$(INTDIR)\mask_tcl.obj"
	-@erase "$(INTDIR)\mask_tcl.sbr"
	-@erase "$(INTDIR)\matlab.obj"
	-@erase "$(INTDIR)\matlab.sbr"
	-@erase "$(INTDIR)\matr.obj"
	-@erase "$(INTDIR)\matr.sbr"
	-@erase "$(INTDIR)\matr_diag.obj"
	-@erase "$(INTDIR)\matr_diag.sbr"
	-@erase "$(INTDIR)\matr_eye.obj"
	-@erase "$(INTDIR)\matr_eye.sbr"
	-@erase "$(INTDIR)\matr_onesrow.obj"
	-@erase "$(INTDIR)\matr_onesrow.sbr"
	-@erase "$(INTDIR)\matrD1.obj"
	-@erase "$(INTDIR)\matrD1.sbr"
	-@erase "$(INTDIR)\matrD1_aniso.obj"
	-@erase "$(INTDIR)\matrD1_aniso.sbr"
	-@erase "$(INTDIR)\matrD1_rect.obj"
	-@erase "$(INTDIR)\matrD1_rect.sbr"
	-@erase "$(INTDIR)\matrD2.obj"
	-@erase "$(INTDIR)\matrD2.sbr"
	-@erase "$(INTDIR)\matrD2_aniso.obj"
	-@erase "$(INTDIR)\matrD2_aniso.sbr"
	-@erase "$(INTDIR)\matrD2_rect.obj"
	-@erase "$(INTDIR)\matrD2_rect.sbr"
	-@erase "$(INTDIR)\mrf.obj"
	-@erase "$(INTDIR)\mrf.sbr"
	-@erase "$(INTDIR)\others_tcl.obj"
	-@erase "$(INTDIR)\others_tcl.sbr"
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
	-@erase "$(INTDIR)\pnts_internal.obj"
	-@erase "$(INTDIR)\pnts_internal.sbr"
	-@erase "$(INTDIR)\pnts_tcl.obj"
	-@erase "$(INTDIR)\pnts_tcl.sbr"
	-@erase "$(INTDIR)\points.obj"
	-@erase "$(INTDIR)\points.sbr"
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
	-@erase "$(INTDIR)\RF.obj"
	-@erase "$(INTDIR)\RF.sbr"
	-@erase "$(INTDIR)\shpopen.obj"
	-@erase "$(INTDIR)\shpopen.sbr"
	-@erase "$(INTDIR)\solvers.obj"
	-@erase "$(INTDIR)\solvers.sbr"
	-@erase "$(INTDIR)\sort_alg.obj"
	-@erase "$(INTDIR)\sort_alg.sbr"
	-@erase "$(INTDIR)\SSOR.obj"
	-@erase "$(INTDIR)\SSOR.sbr"
	-@erase "$(INTDIR)\surf.obj"
	-@erase "$(INTDIR)\surf.sbr"
	-@erase "$(INTDIR)\surf_internal.obj"
	-@erase "$(INTDIR)\surf_internal.sbr"
	-@erase "$(INTDIR)\surf_tcl.obj"
	-@erase "$(INTDIR)\surf_tcl.sbr"
	-@erase "$(INTDIR)\surfit.obj"
	-@erase "$(INTDIR)\surfit.sbr"
	-@erase "$(INTDIR)\surfit_wrap.obj"
	-@erase "$(INTDIR)\surfit_wrap.sbr"
	-@erase "$(INTDIR)\surfs_tcl.obj"
	-@erase "$(INTDIR)\surfs_tcl.sbr"
	-@erase "$(INTDIR)\threads.obj"
	-@erase "$(INTDIR)\threads.sbr"
	-@erase "$(INTDIR)\variables.obj"
	-@erase "$(INTDIR)\variables.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\surfit.bsc"
	-@erase "..\bin\libsurfit.dll"
	-@erase "..\bin\libsurfit.exp"
	-@erase "..\bin\libsurfit.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GR /GX /O2 /Op /Ob2 /I "../src/sstuff" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gs /Gs /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\surfit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\matlab.sbr" \
	"$(INTDIR)\matr.sbr" \
	"$(INTDIR)\matr_diag.sbr" \
	"$(INTDIR)\matr_eye.sbr" \
	"$(INTDIR)\matr_onesrow.sbr" \
	"$(INTDIR)\matrD1.sbr" \
	"$(INTDIR)\matrD1_aniso.sbr" \
	"$(INTDIR)\matrD1_rect.sbr" \
	"$(INTDIR)\matrD2.sbr" \
	"$(INTDIR)\matrD2_aniso.sbr" \
	"$(INTDIR)\matrD2_rect.sbr" \
	"$(INTDIR)\free_elements.sbr" \
	"$(INTDIR)\license.sbr" \
	"$(INTDIR)\CG.sbr" \
	"$(INTDIR)\J.sbr" \
	"$(INTDIR)\JCG.sbr" \
	"$(INTDIR)\RF.sbr" \
	"$(INTDIR)\SSOR.sbr" \
	"$(INTDIR)\cmofs.sbr" \
	"$(INTDIR)\solvers.sbr" \
	"$(INTDIR)\grid.sbr" \
	"$(INTDIR)\grid_internal.sbr" \
	"$(INTDIR)\grid_tcl.sbr" \
	"$(INTDIR)\grid_user.sbr" \
	"$(INTDIR)\variables.sbr" \
	"$(INTDIR)\mask.sbr" \
	"$(INTDIR)\mask_internal.sbr" \
	"$(INTDIR)\mask_tcl.sbr" \
	"$(INTDIR)\surf.sbr" \
	"$(INTDIR)\surf_internal.sbr" \
	"$(INTDIR)\surf_tcl.sbr" \
	"$(INTDIR)\pnts_internal.sbr" \
	"$(INTDIR)\pnts_tcl.sbr" \
	"$(INTDIR)\points.sbr" \
	"$(INTDIR)\cntr.sbr" \
	"$(INTDIR)\cntr_internal.sbr" \
	"$(INTDIR)\cntr_tcl.sbr" \
	"$(INTDIR)\grid_line.sbr" \
	"$(INTDIR)\grid_line_internal.sbr" \
	"$(INTDIR)\grid_line_tcl.sbr" \
	"$(INTDIR)\grid_line_user.sbr" \
	"$(INTDIR)\curv.sbr" \
	"$(INTDIR)\curv_internal.sbr" \
	"$(INTDIR)\curv_tcl.sbr" \
	"$(INTDIR)\hist.sbr" \
	"$(INTDIR)\hist_internal.sbr" \
	"$(INTDIR)\hist_tcl.sbr" \
	"$(INTDIR)\area.sbr" \
	"$(INTDIR)\area_internal.sbr" \
	"$(INTDIR)\area_tcl.sbr" \
	"$(INTDIR)\data.sbr" \
	"$(INTDIR)\f_points.sbr" \
	"$(INTDIR)\f_points_ineq.sbr" \
	"$(INTDIR)\f_points_tcl.sbr" \
	"$(INTDIR)\f_completer.sbr" \
	"$(INTDIR)\f_hist.sbr" \
	"$(INTDIR)\f_ineq.sbr" \
	"$(INTDIR)\f_mean.sbr" \
	"$(INTDIR)\f_value.sbr" \
	"$(INTDIR)\f_wmean.sbr" \
	"$(INTDIR)\others_tcl.sbr" \
	"$(INTDIR)\curvs_tcl.sbr" \
	"$(INTDIR)\f_area.sbr" \
	"$(INTDIR)\f_area_ineq.sbr" \
	"$(INTDIR)\f_area_mean.sbr" \
	"$(INTDIR)\f_area_surf.sbr" \
	"$(INTDIR)\f_area_surf_ineq.sbr" \
	"$(INTDIR)\f_area_wmean.sbr" \
	"$(INTDIR)\f_cntr.sbr" \
	"$(INTDIR)\f_cntr_ineq.sbr" \
	"$(INTDIR)\f_curv.sbr" \
	"$(INTDIR)\f_curv_ineq.sbr" \
	"$(INTDIR)\f_curv_surf.sbr" \
	"$(INTDIR)\f_curv_surf_ineq.sbr" \
	"$(INTDIR)\f_mask.sbr" \
	"$(INTDIR)\f_surf.sbr" \
	"$(INTDIR)\f_surf_ineq.sbr" \
	"$(INTDIR)\f_trend.sbr" \
	"$(INTDIR)\surfs_tcl.sbr" \
	"$(INTDIR)\functional.sbr" \
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
	"$(INTDIR)\dbfopen.sbr" \
	"$(INTDIR)\shpopen.sbr" \
	"$(INTDIR)\data_manager.sbr" \
	"$(INTDIR)\mrf.sbr" \
	"$(INTDIR)\sort_alg.sbr" \
	"$(INTDIR)\surfit.sbr" \
	"$(INTDIR)\surfit_wrap.sbr" \
	"$(INTDIR)\threads.sbr"

"$(OUTDIR)\surfit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83.lib netcdfs.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\libsurfit.pdb" /machine:I386 /out:"../bin/libsurfit.dll" /implib:"../bin/libsurfit.lib" 
LINK32_OBJS= \
	"$(INTDIR)\matlab.obj" \
	"$(INTDIR)\matr.obj" \
	"$(INTDIR)\matr_diag.obj" \
	"$(INTDIR)\matr_eye.obj" \
	"$(INTDIR)\matr_onesrow.obj" \
	"$(INTDIR)\matrD1.obj" \
	"$(INTDIR)\matrD1_aniso.obj" \
	"$(INTDIR)\matrD1_rect.obj" \
	"$(INTDIR)\matrD2.obj" \
	"$(INTDIR)\matrD2_aniso.obj" \
	"$(INTDIR)\matrD2_rect.obj" \
	"$(INTDIR)\free_elements.obj" \
	"$(INTDIR)\license.obj" \
	"$(INTDIR)\CG.obj" \
	"$(INTDIR)\J.obj" \
	"$(INTDIR)\JCG.obj" \
	"$(INTDIR)\RF.obj" \
	"$(INTDIR)\SSOR.obj" \
	"$(INTDIR)\cmofs.obj" \
	"$(INTDIR)\solvers.obj" \
	"$(INTDIR)\grid.obj" \
	"$(INTDIR)\grid_internal.obj" \
	"$(INTDIR)\grid_tcl.obj" \
	"$(INTDIR)\grid_user.obj" \
	"$(INTDIR)\variables.obj" \
	"$(INTDIR)\mask.obj" \
	"$(INTDIR)\mask_internal.obj" \
	"$(INTDIR)\mask_tcl.obj" \
	"$(INTDIR)\surf.obj" \
	"$(INTDIR)\surf_internal.obj" \
	"$(INTDIR)\surf_tcl.obj" \
	"$(INTDIR)\pnts_internal.obj" \
	"$(INTDIR)\pnts_tcl.obj" \
	"$(INTDIR)\points.obj" \
	"$(INTDIR)\cntr.obj" \
	"$(INTDIR)\cntr_internal.obj" \
	"$(INTDIR)\cntr_tcl.obj" \
	"$(INTDIR)\grid_line.obj" \
	"$(INTDIR)\grid_line_internal.obj" \
	"$(INTDIR)\grid_line_tcl.obj" \
	"$(INTDIR)\grid_line_user.obj" \
	"$(INTDIR)\curv.obj" \
	"$(INTDIR)\curv_internal.obj" \
	"$(INTDIR)\curv_tcl.obj" \
	"$(INTDIR)\hist.obj" \
	"$(INTDIR)\hist_internal.obj" \
	"$(INTDIR)\hist_tcl.obj" \
	"$(INTDIR)\area.obj" \
	"$(INTDIR)\area_internal.obj" \
	"$(INTDIR)\area_tcl.obj" \
	"$(INTDIR)\data.obj" \
	"$(INTDIR)\f_points.obj" \
	"$(INTDIR)\f_points_ineq.obj" \
	"$(INTDIR)\f_points_tcl.obj" \
	"$(INTDIR)\f_completer.obj" \
	"$(INTDIR)\f_hist.obj" \
	"$(INTDIR)\f_ineq.obj" \
	"$(INTDIR)\f_mean.obj" \
	"$(INTDIR)\f_value.obj" \
	"$(INTDIR)\f_wmean.obj" \
	"$(INTDIR)\others_tcl.obj" \
	"$(INTDIR)\curvs_tcl.obj" \
	"$(INTDIR)\f_area.obj" \
	"$(INTDIR)\f_area_ineq.obj" \
	"$(INTDIR)\f_area_mean.obj" \
	"$(INTDIR)\f_area_surf.obj" \
	"$(INTDIR)\f_area_surf_ineq.obj" \
	"$(INTDIR)\f_area_wmean.obj" \
	"$(INTDIR)\f_cntr.obj" \
	"$(INTDIR)\f_cntr_ineq.obj" \
	"$(INTDIR)\f_curv.obj" \
	"$(INTDIR)\f_curv_ineq.obj" \
	"$(INTDIR)\f_curv_surf.obj" \
	"$(INTDIR)\f_curv_surf_ineq.obj" \
	"$(INTDIR)\f_mask.obj" \
	"$(INTDIR)\f_surf.obj" \
	"$(INTDIR)\f_surf_ineq.obj" \
	"$(INTDIR)\f_trend.obj" \
	"$(INTDIR)\surfs_tcl.obj" \
	"$(INTDIR)\functional.obj" \
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
	"$(INTDIR)\dbfopen.obj" \
	"$(INTDIR)\shpopen.obj" \
	"$(INTDIR)\data_manager.obj" \
	"$(INTDIR)\mrf.obj" \
	"$(INTDIR)\sort_alg.obj" \
	"$(INTDIR)\surfit.obj" \
	"$(INTDIR)\surfit_wrap.obj" \
	"$(INTDIR)\threads.obj" \
	"..\bin\libsstuff.lib"

"..\bin\libsurfit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

OUTDIR=.\../Debug
INTDIR=.\../Debug
# Begin Custom Macros
OutDir=.\../Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\libsurfit.dll" "$(OUTDIR)\surfit.bsc"

!ELSE 

ALL : "sstuff - Win32 Debug" "..\bin\libsurfit.dll" "$(OUTDIR)\surfit.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"sstuff - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\area.obj"
	-@erase "$(INTDIR)\area.sbr"
	-@erase "$(INTDIR)\area_internal.obj"
	-@erase "$(INTDIR)\area_internal.sbr"
	-@erase "$(INTDIR)\area_tcl.obj"
	-@erase "$(INTDIR)\area_tcl.sbr"
	-@erase "$(INTDIR)\CG.obj"
	-@erase "$(INTDIR)\CG.sbr"
	-@erase "$(INTDIR)\cmofs.obj"
	-@erase "$(INTDIR)\cmofs.sbr"
	-@erase "$(INTDIR)\cntr.obj"
	-@erase "$(INTDIR)\cntr.sbr"
	-@erase "$(INTDIR)\cntr_internal.obj"
	-@erase "$(INTDIR)\cntr_internal.sbr"
	-@erase "$(INTDIR)\cntr_tcl.obj"
	-@erase "$(INTDIR)\cntr_tcl.sbr"
	-@erase "$(INTDIR)\curv.obj"
	-@erase "$(INTDIR)\curv.sbr"
	-@erase "$(INTDIR)\curv_internal.obj"
	-@erase "$(INTDIR)\curv_internal.sbr"
	-@erase "$(INTDIR)\curv_tcl.obj"
	-@erase "$(INTDIR)\curv_tcl.sbr"
	-@erase "$(INTDIR)\curvs_tcl.obj"
	-@erase "$(INTDIR)\curvs_tcl.sbr"
	-@erase "$(INTDIR)\data.obj"
	-@erase "$(INTDIR)\data.sbr"
	-@erase "$(INTDIR)\data_manager.obj"
	-@erase "$(INTDIR)\data_manager.sbr"
	-@erase "$(INTDIR)\dbfopen.obj"
	-@erase "$(INTDIR)\dbfopen.sbr"
	-@erase "$(INTDIR)\f_area.obj"
	-@erase "$(INTDIR)\f_area.sbr"
	-@erase "$(INTDIR)\f_area_ineq.obj"
	-@erase "$(INTDIR)\f_area_ineq.sbr"
	-@erase "$(INTDIR)\f_area_mean.obj"
	-@erase "$(INTDIR)\f_area_mean.sbr"
	-@erase "$(INTDIR)\f_area_surf.obj"
	-@erase "$(INTDIR)\f_area_surf.sbr"
	-@erase "$(INTDIR)\f_area_surf_ineq.obj"
	-@erase "$(INTDIR)\f_area_surf_ineq.sbr"
	-@erase "$(INTDIR)\f_area_wmean.obj"
	-@erase "$(INTDIR)\f_area_wmean.sbr"
	-@erase "$(INTDIR)\f_cntr.obj"
	-@erase "$(INTDIR)\f_cntr.sbr"
	-@erase "$(INTDIR)\f_cntr_ineq.obj"
	-@erase "$(INTDIR)\f_cntr_ineq.sbr"
	-@erase "$(INTDIR)\f_completer.obj"
	-@erase "$(INTDIR)\f_completer.sbr"
	-@erase "$(INTDIR)\f_curv.obj"
	-@erase "$(INTDIR)\f_curv.sbr"
	-@erase "$(INTDIR)\f_curv_ineq.obj"
	-@erase "$(INTDIR)\f_curv_ineq.sbr"
	-@erase "$(INTDIR)\f_curv_surf.obj"
	-@erase "$(INTDIR)\f_curv_surf.sbr"
	-@erase "$(INTDIR)\f_curv_surf_ineq.obj"
	-@erase "$(INTDIR)\f_curv_surf_ineq.sbr"
	-@erase "$(INTDIR)\f_hist.obj"
	-@erase "$(INTDIR)\f_hist.sbr"
	-@erase "$(INTDIR)\f_ineq.obj"
	-@erase "$(INTDIR)\f_ineq.sbr"
	-@erase "$(INTDIR)\f_mask.obj"
	-@erase "$(INTDIR)\f_mask.sbr"
	-@erase "$(INTDIR)\f_mean.obj"
	-@erase "$(INTDIR)\f_mean.sbr"
	-@erase "$(INTDIR)\f_points.obj"
	-@erase "$(INTDIR)\f_points.sbr"
	-@erase "$(INTDIR)\f_points_ineq.obj"
	-@erase "$(INTDIR)\f_points_ineq.sbr"
	-@erase "$(INTDIR)\f_points_tcl.obj"
	-@erase "$(INTDIR)\f_points_tcl.sbr"
	-@erase "$(INTDIR)\f_surf.obj"
	-@erase "$(INTDIR)\f_surf.sbr"
	-@erase "$(INTDIR)\f_surf_ineq.obj"
	-@erase "$(INTDIR)\f_surf_ineq.sbr"
	-@erase "$(INTDIR)\f_trend.obj"
	-@erase "$(INTDIR)\f_trend.sbr"
	-@erase "$(INTDIR)\f_value.obj"
	-@erase "$(INTDIR)\f_value.sbr"
	-@erase "$(INTDIR)\f_wmean.obj"
	-@erase "$(INTDIR)\f_wmean.sbr"
	-@erase "$(INTDIR)\free_elements.obj"
	-@erase "$(INTDIR)\free_elements.sbr"
	-@erase "$(INTDIR)\functional.obj"
	-@erase "$(INTDIR)\functional.sbr"
	-@erase "$(INTDIR)\grid.obj"
	-@erase "$(INTDIR)\grid.sbr"
	-@erase "$(INTDIR)\grid_internal.obj"
	-@erase "$(INTDIR)\grid_internal.sbr"
	-@erase "$(INTDIR)\grid_line.obj"
	-@erase "$(INTDIR)\grid_line.sbr"
	-@erase "$(INTDIR)\grid_line_internal.obj"
	-@erase "$(INTDIR)\grid_line_internal.sbr"
	-@erase "$(INTDIR)\grid_line_tcl.obj"
	-@erase "$(INTDIR)\grid_line_tcl.sbr"
	-@erase "$(INTDIR)\grid_line_user.obj"
	-@erase "$(INTDIR)\grid_line_user.sbr"
	-@erase "$(INTDIR)\grid_tcl.obj"
	-@erase "$(INTDIR)\grid_tcl.sbr"
	-@erase "$(INTDIR)\grid_user.obj"
	-@erase "$(INTDIR)\grid_user.sbr"
	-@erase "$(INTDIR)\hist.obj"
	-@erase "$(INTDIR)\hist.sbr"
	-@erase "$(INTDIR)\hist_internal.obj"
	-@erase "$(INTDIR)\hist_internal.sbr"
	-@erase "$(INTDIR)\hist_tcl.obj"
	-@erase "$(INTDIR)\hist_tcl.sbr"
	-@erase "$(INTDIR)\J.obj"
	-@erase "$(INTDIR)\J.sbr"
	-@erase "$(INTDIR)\JCG.obj"
	-@erase "$(INTDIR)\JCG.sbr"
	-@erase "$(INTDIR)\license.obj"
	-@erase "$(INTDIR)\license.sbr"
	-@erase "$(INTDIR)\mask.obj"
	-@erase "$(INTDIR)\mask.sbr"
	-@erase "$(INTDIR)\mask_internal.obj"
	-@erase "$(INTDIR)\mask_internal.sbr"
	-@erase "$(INTDIR)\mask_tcl.obj"
	-@erase "$(INTDIR)\mask_tcl.sbr"
	-@erase "$(INTDIR)\matlab.obj"
	-@erase "$(INTDIR)\matlab.sbr"
	-@erase "$(INTDIR)\matr.obj"
	-@erase "$(INTDIR)\matr.sbr"
	-@erase "$(INTDIR)\matr_diag.obj"
	-@erase "$(INTDIR)\matr_diag.sbr"
	-@erase "$(INTDIR)\matr_eye.obj"
	-@erase "$(INTDIR)\matr_eye.sbr"
	-@erase "$(INTDIR)\matr_onesrow.obj"
	-@erase "$(INTDIR)\matr_onesrow.sbr"
	-@erase "$(INTDIR)\matrD1.obj"
	-@erase "$(INTDIR)\matrD1.sbr"
	-@erase "$(INTDIR)\matrD1_aniso.obj"
	-@erase "$(INTDIR)\matrD1_aniso.sbr"
	-@erase "$(INTDIR)\matrD1_rect.obj"
	-@erase "$(INTDIR)\matrD1_rect.sbr"
	-@erase "$(INTDIR)\matrD2.obj"
	-@erase "$(INTDIR)\matrD2.sbr"
	-@erase "$(INTDIR)\matrD2_aniso.obj"
	-@erase "$(INTDIR)\matrD2_aniso.sbr"
	-@erase "$(INTDIR)\matrD2_rect.obj"
	-@erase "$(INTDIR)\matrD2_rect.sbr"
	-@erase "$(INTDIR)\mrf.obj"
	-@erase "$(INTDIR)\mrf.sbr"
	-@erase "$(INTDIR)\others_tcl.obj"
	-@erase "$(INTDIR)\others_tcl.sbr"
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
	-@erase "$(INTDIR)\pnts_internal.obj"
	-@erase "$(INTDIR)\pnts_internal.sbr"
	-@erase "$(INTDIR)\pnts_tcl.obj"
	-@erase "$(INTDIR)\pnts_tcl.sbr"
	-@erase "$(INTDIR)\points.obj"
	-@erase "$(INTDIR)\points.sbr"
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
	-@erase "$(INTDIR)\RF.obj"
	-@erase "$(INTDIR)\RF.sbr"
	-@erase "$(INTDIR)\shpopen.obj"
	-@erase "$(INTDIR)\shpopen.sbr"
	-@erase "$(INTDIR)\solvers.obj"
	-@erase "$(INTDIR)\solvers.sbr"
	-@erase "$(INTDIR)\sort_alg.obj"
	-@erase "$(INTDIR)\sort_alg.sbr"
	-@erase "$(INTDIR)\SSOR.obj"
	-@erase "$(INTDIR)\SSOR.sbr"
	-@erase "$(INTDIR)\surf.obj"
	-@erase "$(INTDIR)\surf.sbr"
	-@erase "$(INTDIR)\surf_internal.obj"
	-@erase "$(INTDIR)\surf_internal.sbr"
	-@erase "$(INTDIR)\surf_tcl.obj"
	-@erase "$(INTDIR)\surf_tcl.sbr"
	-@erase "$(INTDIR)\surfit.obj"
	-@erase "$(INTDIR)\surfit.sbr"
	-@erase "$(INTDIR)\surfit_wrap.obj"
	-@erase "$(INTDIR)\surfit_wrap.sbr"
	-@erase "$(INTDIR)\surfs_tcl.obj"
	-@erase "$(INTDIR)\surfs_tcl.sbr"
	-@erase "$(INTDIR)\threads.obj"
	-@erase "$(INTDIR)\threads.sbr"
	-@erase "$(INTDIR)\variables.obj"
	-@erase "$(INTDIR)\variables.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\libsurfit.map"
	-@erase "$(OUTDIR)\surfit.bsc"
	-@erase "..\bin\libsurfit.dll"
	-@erase "..\bin\libsurfit.exp"
	-@erase "..\bin\libsurfit.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\surfit.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\matlab.sbr" \
	"$(INTDIR)\matr.sbr" \
	"$(INTDIR)\matr_diag.sbr" \
	"$(INTDIR)\matr_eye.sbr" \
	"$(INTDIR)\matr_onesrow.sbr" \
	"$(INTDIR)\matrD1.sbr" \
	"$(INTDIR)\matrD1_aniso.sbr" \
	"$(INTDIR)\matrD1_rect.sbr" \
	"$(INTDIR)\matrD2.sbr" \
	"$(INTDIR)\matrD2_aniso.sbr" \
	"$(INTDIR)\matrD2_rect.sbr" \
	"$(INTDIR)\free_elements.sbr" \
	"$(INTDIR)\license.sbr" \
	"$(INTDIR)\CG.sbr" \
	"$(INTDIR)\J.sbr" \
	"$(INTDIR)\JCG.sbr" \
	"$(INTDIR)\RF.sbr" \
	"$(INTDIR)\SSOR.sbr" \
	"$(INTDIR)\cmofs.sbr" \
	"$(INTDIR)\solvers.sbr" \
	"$(INTDIR)\grid.sbr" \
	"$(INTDIR)\grid_internal.sbr" \
	"$(INTDIR)\grid_tcl.sbr" \
	"$(INTDIR)\grid_user.sbr" \
	"$(INTDIR)\variables.sbr" \
	"$(INTDIR)\mask.sbr" \
	"$(INTDIR)\mask_internal.sbr" \
	"$(INTDIR)\mask_tcl.sbr" \
	"$(INTDIR)\surf.sbr" \
	"$(INTDIR)\surf_internal.sbr" \
	"$(INTDIR)\surf_tcl.sbr" \
	"$(INTDIR)\pnts_internal.sbr" \
	"$(INTDIR)\pnts_tcl.sbr" \
	"$(INTDIR)\points.sbr" \
	"$(INTDIR)\cntr.sbr" \
	"$(INTDIR)\cntr_internal.sbr" \
	"$(INTDIR)\cntr_tcl.sbr" \
	"$(INTDIR)\grid_line.sbr" \
	"$(INTDIR)\grid_line_internal.sbr" \
	"$(INTDIR)\grid_line_tcl.sbr" \
	"$(INTDIR)\grid_line_user.sbr" \
	"$(INTDIR)\curv.sbr" \
	"$(INTDIR)\curv_internal.sbr" \
	"$(INTDIR)\curv_tcl.sbr" \
	"$(INTDIR)\hist.sbr" \
	"$(INTDIR)\hist_internal.sbr" \
	"$(INTDIR)\hist_tcl.sbr" \
	"$(INTDIR)\area.sbr" \
	"$(INTDIR)\area_internal.sbr" \
	"$(INTDIR)\area_tcl.sbr" \
	"$(INTDIR)\data.sbr" \
	"$(INTDIR)\f_points.sbr" \
	"$(INTDIR)\f_points_ineq.sbr" \
	"$(INTDIR)\f_points_tcl.sbr" \
	"$(INTDIR)\f_completer.sbr" \
	"$(INTDIR)\f_hist.sbr" \
	"$(INTDIR)\f_ineq.sbr" \
	"$(INTDIR)\f_mean.sbr" \
	"$(INTDIR)\f_value.sbr" \
	"$(INTDIR)\f_wmean.sbr" \
	"$(INTDIR)\others_tcl.sbr" \
	"$(INTDIR)\curvs_tcl.sbr" \
	"$(INTDIR)\f_area.sbr" \
	"$(INTDIR)\f_area_ineq.sbr" \
	"$(INTDIR)\f_area_mean.sbr" \
	"$(INTDIR)\f_area_surf.sbr" \
	"$(INTDIR)\f_area_surf_ineq.sbr" \
	"$(INTDIR)\f_area_wmean.sbr" \
	"$(INTDIR)\f_cntr.sbr" \
	"$(INTDIR)\f_cntr_ineq.sbr" \
	"$(INTDIR)\f_curv.sbr" \
	"$(INTDIR)\f_curv_ineq.sbr" \
	"$(INTDIR)\f_curv_surf.sbr" \
	"$(INTDIR)\f_curv_surf_ineq.sbr" \
	"$(INTDIR)\f_mask.sbr" \
	"$(INTDIR)\f_surf.sbr" \
	"$(INTDIR)\f_surf_ineq.sbr" \
	"$(INTDIR)\f_trend.sbr" \
	"$(INTDIR)\surfs_tcl.sbr" \
	"$(INTDIR)\functional.sbr" \
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
	"$(INTDIR)\dbfopen.sbr" \
	"$(INTDIR)\shpopen.sbr" \
	"$(INTDIR)\data_manager.sbr" \
	"$(INTDIR)\mrf.sbr" \
	"$(INTDIR)\sort_alg.sbr" \
	"$(INTDIR)\surfit.sbr" \
	"$(INTDIR)\surfit_wrap.sbr" \
	"$(INTDIR)\threads.sbr"

"$(OUTDIR)\surfit.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=tcl83d.lib netcdfs.lib /nologo /dll /pdb:none /map:"$(INTDIR)\libsurfit.map" /debug /machine:I386 /nodefaultlib:"LIBCMT" /out:"../bin/libsurfit.dll" /implib:"../bin/libsurfit.lib" 
LINK32_OBJS= \
	"$(INTDIR)\matlab.obj" \
	"$(INTDIR)\matr.obj" \
	"$(INTDIR)\matr_diag.obj" \
	"$(INTDIR)\matr_eye.obj" \
	"$(INTDIR)\matr_onesrow.obj" \
	"$(INTDIR)\matrD1.obj" \
	"$(INTDIR)\matrD1_aniso.obj" \
	"$(INTDIR)\matrD1_rect.obj" \
	"$(INTDIR)\matrD2.obj" \
	"$(INTDIR)\matrD2_aniso.obj" \
	"$(INTDIR)\matrD2_rect.obj" \
	"$(INTDIR)\free_elements.obj" \
	"$(INTDIR)\license.obj" \
	"$(INTDIR)\CG.obj" \
	"$(INTDIR)\J.obj" \
	"$(INTDIR)\JCG.obj" \
	"$(INTDIR)\RF.obj" \
	"$(INTDIR)\SSOR.obj" \
	"$(INTDIR)\cmofs.obj" \
	"$(INTDIR)\solvers.obj" \
	"$(INTDIR)\grid.obj" \
	"$(INTDIR)\grid_internal.obj" \
	"$(INTDIR)\grid_tcl.obj" \
	"$(INTDIR)\grid_user.obj" \
	"$(INTDIR)\variables.obj" \
	"$(INTDIR)\mask.obj" \
	"$(INTDIR)\mask_internal.obj" \
	"$(INTDIR)\mask_tcl.obj" \
	"$(INTDIR)\surf.obj" \
	"$(INTDIR)\surf_internal.obj" \
	"$(INTDIR)\surf_tcl.obj" \
	"$(INTDIR)\pnts_internal.obj" \
	"$(INTDIR)\pnts_tcl.obj" \
	"$(INTDIR)\points.obj" \
	"$(INTDIR)\cntr.obj" \
	"$(INTDIR)\cntr_internal.obj" \
	"$(INTDIR)\cntr_tcl.obj" \
	"$(INTDIR)\grid_line.obj" \
	"$(INTDIR)\grid_line_internal.obj" \
	"$(INTDIR)\grid_line_tcl.obj" \
	"$(INTDIR)\grid_line_user.obj" \
	"$(INTDIR)\curv.obj" \
	"$(INTDIR)\curv_internal.obj" \
	"$(INTDIR)\curv_tcl.obj" \
	"$(INTDIR)\hist.obj" \
	"$(INTDIR)\hist_internal.obj" \
	"$(INTDIR)\hist_tcl.obj" \
	"$(INTDIR)\area.obj" \
	"$(INTDIR)\area_internal.obj" \
	"$(INTDIR)\area_tcl.obj" \
	"$(INTDIR)\data.obj" \
	"$(INTDIR)\f_points.obj" \
	"$(INTDIR)\f_points_ineq.obj" \
	"$(INTDIR)\f_points_tcl.obj" \
	"$(INTDIR)\f_completer.obj" \
	"$(INTDIR)\f_hist.obj" \
	"$(INTDIR)\f_ineq.obj" \
	"$(INTDIR)\f_mean.obj" \
	"$(INTDIR)\f_value.obj" \
	"$(INTDIR)\f_wmean.obj" \
	"$(INTDIR)\others_tcl.obj" \
	"$(INTDIR)\curvs_tcl.obj" \
	"$(INTDIR)\f_area.obj" \
	"$(INTDIR)\f_area_ineq.obj" \
	"$(INTDIR)\f_area_mean.obj" \
	"$(INTDIR)\f_area_surf.obj" \
	"$(INTDIR)\f_area_surf_ineq.obj" \
	"$(INTDIR)\f_area_wmean.obj" \
	"$(INTDIR)\f_cntr.obj" \
	"$(INTDIR)\f_cntr_ineq.obj" \
	"$(INTDIR)\f_curv.obj" \
	"$(INTDIR)\f_curv_ineq.obj" \
	"$(INTDIR)\f_curv_surf.obj" \
	"$(INTDIR)\f_curv_surf_ineq.obj" \
	"$(INTDIR)\f_mask.obj" \
	"$(INTDIR)\f_surf.obj" \
	"$(INTDIR)\f_surf_ineq.obj" \
	"$(INTDIR)\f_trend.obj" \
	"$(INTDIR)\surfs_tcl.obj" \
	"$(INTDIR)\functional.obj" \
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
	"$(INTDIR)\dbfopen.obj" \
	"$(INTDIR)\shpopen.obj" \
	"$(INTDIR)\data_manager.obj" \
	"$(INTDIR)\mrf.obj" \
	"$(INTDIR)\sort_alg.obj" \
	"$(INTDIR)\surfit.obj" \
	"$(INTDIR)\surfit_wrap.obj" \
	"$(INTDIR)\threads.obj" \
	"..\bin\libsstuff.lib"

"..\bin\libsurfit.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("surfit.dep")
!INCLUDE "surfit.dep"
!ELSE 
!MESSAGE Warning: cannot find "surfit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "surfit - Win32 Release" || "$(CFG)" == "surfit - Win32 Debug"
SOURCE=.\..\src\surfit\matlab.cpp

"$(INTDIR)\matlab.obj"	"$(INTDIR)\matlab.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matr.cpp

"$(INTDIR)\matr.obj"	"$(INTDIR)\matr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matr_diag.cpp

"$(INTDIR)\matr_diag.obj"	"$(INTDIR)\matr_diag.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matr_eye.cpp

"$(INTDIR)\matr_eye.obj"	"$(INTDIR)\matr_eye.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matr_onesrow.cpp

"$(INTDIR)\matr_onesrow.obj"	"$(INTDIR)\matr_onesrow.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matrD1.cpp

"$(INTDIR)\matrD1.obj"	"$(INTDIR)\matrD1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matrD1_aniso.cpp

"$(INTDIR)\matrD1_aniso.obj"	"$(INTDIR)\matrD1_aniso.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matrD1_rect.cpp

"$(INTDIR)\matrD1_rect.obj"	"$(INTDIR)\matrD1_rect.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matrD2.cpp

"$(INTDIR)\matrD2.obj"	"$(INTDIR)\matrD2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matrD2_aniso.cpp

"$(INTDIR)\matrD2_aniso.obj"	"$(INTDIR)\matrD2_aniso.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\matrD2_rect.cpp

"$(INTDIR)\matrD2_rect.obj"	"$(INTDIR)\matrD2_rect.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\free_elements.cpp

"$(INTDIR)\free_elements.obj"	"$(INTDIR)\free_elements.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\license.cpp

"$(INTDIR)\license.obj"	"$(INTDIR)\license.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\solvers\CG.cpp

"$(INTDIR)\CG.obj"	"$(INTDIR)\CG.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\solvers\J.cpp

"$(INTDIR)\J.obj"	"$(INTDIR)\J.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\solvers\JCG.cpp

"$(INTDIR)\JCG.obj"	"$(INTDIR)\JCG.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\solvers\RF.cpp

"$(INTDIR)\RF.obj"	"$(INTDIR)\RF.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\solvers\SSOR.cpp

"$(INTDIR)\SSOR.obj"	"$(INTDIR)\SSOR.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\cmofs.cpp

"$(INTDIR)\cmofs.obj"	"$(INTDIR)\cmofs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\solvers.cpp

"$(INTDIR)\solvers.obj"	"$(INTDIR)\solvers.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid.cpp

"$(INTDIR)\grid.obj"	"$(INTDIR)\grid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid_internal.cpp

"$(INTDIR)\grid_internal.obj"	"$(INTDIR)\grid_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid_tcl.cpp

"$(INTDIR)\grid_tcl.obj"	"$(INTDIR)\grid_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid_user.cpp

"$(INTDIR)\grid_user.obj"	"$(INTDIR)\grid_user.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\variables.cpp

"$(INTDIR)\variables.obj"	"$(INTDIR)\variables.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\mask.cpp

"$(INTDIR)\mask.obj"	"$(INTDIR)\mask.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\mask_internal.cpp

"$(INTDIR)\mask_internal.obj"	"$(INTDIR)\mask_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\mask_tcl.cpp

"$(INTDIR)\mask_tcl.obj"	"$(INTDIR)\mask_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\surf.cpp

"$(INTDIR)\surf.obj"	"$(INTDIR)\surf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\surf_internal.cpp

"$(INTDIR)\surf_internal.obj"	"$(INTDIR)\surf_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\surf_tcl.cpp

"$(INTDIR)\surf_tcl.obj"	"$(INTDIR)\surf_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\pnts_internal.cpp

"$(INTDIR)\pnts_internal.obj"	"$(INTDIR)\pnts_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\pnts_tcl.cpp

"$(INTDIR)\pnts_tcl.obj"	"$(INTDIR)\pnts_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\points.cpp

"$(INTDIR)\points.obj"	"$(INTDIR)\points.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\cntr.cpp

"$(INTDIR)\cntr.obj"	"$(INTDIR)\cntr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\cntr_internal.cpp

"$(INTDIR)\cntr_internal.obj"	"$(INTDIR)\cntr_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\cntr_tcl.cpp

"$(INTDIR)\cntr_tcl.obj"	"$(INTDIR)\cntr_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid_line.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GR /GX /O2 /Op /Ob2 /I "../src/sstuff" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gs /Gs /c 

"$(INTDIR)\grid_line.obj"	"$(INTDIR)\grid_line.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\grid_line.obj"	"$(INTDIR)\grid_line.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\..\src\surfit\grid_line_internal.cpp

"$(INTDIR)\grid_line_internal.obj"	"$(INTDIR)\grid_line_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid_line_tcl.cpp

"$(INTDIR)\grid_line_tcl.obj"	"$(INTDIR)\grid_line_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\grid_line_user.cpp

"$(INTDIR)\grid_line_user.obj"	"$(INTDIR)\grid_line_user.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\curv.cpp

"$(INTDIR)\curv.obj"	"$(INTDIR)\curv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\curv_internal.cpp

"$(INTDIR)\curv_internal.obj"	"$(INTDIR)\curv_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\curv_tcl.cpp

"$(INTDIR)\curv_tcl.obj"	"$(INTDIR)\curv_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\hist.cpp

"$(INTDIR)\hist.obj"	"$(INTDIR)\hist.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\hist_internal.cpp

"$(INTDIR)\hist_internal.obj"	"$(INTDIR)\hist_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\hist_tcl.cpp

"$(INTDIR)\hist_tcl.obj"	"$(INTDIR)\hist_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\area.cpp

"$(INTDIR)\area.obj"	"$(INTDIR)\area.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\area_internal.cpp

"$(INTDIR)\area_internal.obj"	"$(INTDIR)\area_internal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\area_tcl.cpp

"$(INTDIR)\area_tcl.obj"	"$(INTDIR)\area_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\data.cpp

"$(INTDIR)\data.obj"	"$(INTDIR)\data.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_points.cpp

"$(INTDIR)\f_points.obj"	"$(INTDIR)\f_points.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_points_ineq.cpp

"$(INTDIR)\f_points_ineq.obj"	"$(INTDIR)\f_points_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_points_tcl.cpp

"$(INTDIR)\f_points_tcl.obj"	"$(INTDIR)\f_points_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_completer.cpp

"$(INTDIR)\f_completer.obj"	"$(INTDIR)\f_completer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_hist.cpp

"$(INTDIR)\f_hist.obj"	"$(INTDIR)\f_hist.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_ineq.cpp

"$(INTDIR)\f_ineq.obj"	"$(INTDIR)\f_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_mean.cpp

"$(INTDIR)\f_mean.obj"	"$(INTDIR)\f_mean.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_value.cpp

"$(INTDIR)\f_value.obj"	"$(INTDIR)\f_value.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_wmean.cpp

"$(INTDIR)\f_wmean.obj"	"$(INTDIR)\f_wmean.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\others_tcl.cpp

"$(INTDIR)\others_tcl.obj"	"$(INTDIR)\others_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\curvs_tcl.cpp

"$(INTDIR)\curvs_tcl.obj"	"$(INTDIR)\curvs_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_area.cpp

"$(INTDIR)\f_area.obj"	"$(INTDIR)\f_area.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_area_ineq.cpp

"$(INTDIR)\f_area_ineq.obj"	"$(INTDIR)\f_area_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_area_mean.cpp

"$(INTDIR)\f_area_mean.obj"	"$(INTDIR)\f_area_mean.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_area_surf.cpp

"$(INTDIR)\f_area_surf.obj"	"$(INTDIR)\f_area_surf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_area_surf_ineq.cpp

"$(INTDIR)\f_area_surf_ineq.obj"	"$(INTDIR)\f_area_surf_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_area_wmean.cpp

"$(INTDIR)\f_area_wmean.obj"	"$(INTDIR)\f_area_wmean.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_cntr.cpp

"$(INTDIR)\f_cntr.obj"	"$(INTDIR)\f_cntr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_cntr_ineq.cpp

"$(INTDIR)\f_cntr_ineq.obj"	"$(INTDIR)\f_cntr_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_curv.cpp

"$(INTDIR)\f_curv.obj"	"$(INTDIR)\f_curv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_curv_ineq.cpp

"$(INTDIR)\f_curv_ineq.obj"	"$(INTDIR)\f_curv_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_curv_surf.cpp

"$(INTDIR)\f_curv_surf.obj"	"$(INTDIR)\f_curv_surf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_curv_surf_ineq.cpp

"$(INTDIR)\f_curv_surf_ineq.obj"	"$(INTDIR)\f_curv_surf_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_mask.cpp

"$(INTDIR)\f_mask.obj"	"$(INTDIR)\f_mask.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_surf.cpp

"$(INTDIR)\f_surf.obj"	"$(INTDIR)\f_surf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_surf_ineq.cpp

"$(INTDIR)\f_surf_ineq.obj"	"$(INTDIR)\f_surf_ineq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\f_trend.cpp

"$(INTDIR)\f_trend.obj"	"$(INTDIR)\f_trend.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\surfs_tcl.cpp

"$(INTDIR)\surfs_tcl.obj"	"$(INTDIR)\surfs_tcl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\functional.cpp

"$(INTDIR)\functional.obj"	"$(INTDIR)\functional.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pasync.cxx

"$(INTDIR)\pasync.obj"	"$(INTDIR)\pasync.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\patomic.cxx

"$(INTDIR)\patomic.obj"	"$(INTDIR)\patomic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pexcept.cxx

"$(INTDIR)\pexcept.obj"	"$(INTDIR)\pexcept.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pfatal.cxx

"$(INTDIR)\pfatal.obj"	"$(INTDIR)\pfatal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pmem.cxx

"$(INTDIR)\pmem.obj"	"$(INTDIR)\pmem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pmsgq.cxx

"$(INTDIR)\pmsgq.obj"	"$(INTDIR)\pmsgq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\psemaphore.cxx

"$(INTDIR)\psemaphore.obj"	"$(INTDIR)\psemaphore.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pstring.cxx

"$(INTDIR)\pstring.obj"	"$(INTDIR)\pstring.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\pthread.cxx

"$(INTDIR)\pthread.obj"	"$(INTDIR)\pthread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\ptimedsem.cxx

"$(INTDIR)\ptimedsem.obj"	"$(INTDIR)\ptimedsem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\ptypes\punknown.cxx

"$(INTDIR)\punknown.obj"	"$(INTDIR)\punknown.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\shapelib\dbfopen.c

"$(INTDIR)\dbfopen.obj"	"$(INTDIR)\dbfopen.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\shapelib\shpopen.c

"$(INTDIR)\shpopen.obj"	"$(INTDIR)\shpopen.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\surfit\data_manager.cpp

"$(INTDIR)\data_manager.obj"	"$(INTDIR)\data_manager.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\mrf.cpp

!IF  "$(CFG)" == "surfit - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GR /GX /Op /Ob2 /I "../src/sstuff" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gs /Gs /c 

"$(INTDIR)\mrf.obj"	"$(INTDIR)\mrf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\mrf.obj"	"$(INTDIR)\mrf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\src\surfit\sort_alg.cpp

"$(INTDIR)\sort_alg.obj"	"$(INTDIR)\sort_alg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\surfit.cpp

"$(INTDIR)\surfit.obj"	"$(INTDIR)\surfit.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\surfit_wrap.cxx

!IF  "$(CFG)" == "surfit - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GR /GX /Op /Oy- /Ob2 /I "../src/sstuff" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Gs /Gs /c 

"$(INTDIR)\surfit_wrap.obj"	"$(INTDIR)\surfit_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\surfit_wrap.obj"	"$(INTDIR)\surfit_wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\src\surfit\threads.cpp

"$(INTDIR)\threads.obj"	"$(INTDIR)\threads.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\..\src\surfit\interface\surfit.i

!IF  "$(CFG)" == "surfit - Win32 Release"

InputPath=.\..\src\surfit\interface\surfit.i
USERDEP__SURFI="../src/surfit/interface/fileio.i"	"../src/surfit/interface/solve.i"	"../src/surfit/interface/task.i"	"../src/surfit/interface/geom.i"	"../src/surfit/interface/func.i"	"../src/surfit/interface/curv.i"	

"..\src\surfit\surfit_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__SURFI)
	<<tempfile.bat 
	@echo off 
	surfit_swig.bat
<< 
	

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

InputPath=.\..\src\surfit\interface\surfit.i
USERDEP__SURFI="../src/surfit/interface/fileio.i"	"../src/surfit/interface/solve.i"	"../src/surfit/interface/task.i"	"../src/surfit/interface/geom.i"	"../src/surfit/interface/func.i"	"../src/surfit/interface/curv.i"	

"..\src\surfit\surfit_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)" $(USERDEP__SURFI)
	<<tempfile.bat 
	@echo off 
	surfit_swig.bat
<< 
	

!ENDIF 

!IF  "$(CFG)" == "surfit - Win32 Release"

"sstuff - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" 
   cd "."

"sstuff - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\sstuff.mak CFG="sstuff - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ELSEIF  "$(CFG)" == "surfit - Win32 Debug"

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

