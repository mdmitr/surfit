!define MUI_PRODUCT "surfit" ;Define your own software name here
!define MUI_VERSION "1.0" ;Define your own software version here

!include "MUI.nsh"

;--------------------------------
;Configuration

  ;General
  OutFile "surfit.exe"

  ;Folder selection page
  InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"
  
  ;Remember install folder
  InstallDirRegKey HKCU "Software\${MUI_PRODUCT}" ""

;Remember the Start Menu Folder
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\${MUI_PRODUCT}" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"


;--------------------------------
;Modern UI Configuration

; !define MUI_LICENSEPAGE
  !define MUI_COMPONENTSPAGE
  !define MUI_DIRECTORYPAGE
  
  !define MUI_ABORTWARNING
	
  !define MUI_STARTMENUPAGE
  
  !define MUI_UNINSTALLER
  !define MUI_UNCONFIRMPAGE
  
  !define MUI_HEADERBITMAP "surfit-1.0.0\images\nsis_logo.bmp"


  !define TEMP $R0
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  
;--------------------------------
;Language Strings

  ;Description
  LangString DESC_SecCopyCalc ${LANG_ENGLISH} "Copy base surfit package."
  LangString DESC_SecCopyVis ${LANG_ENGLISH} "Copy visualization tools."
  LangString DESC_SecCopyData ${LANG_ENGLISH} "Copy sample data."
  LangString DESC_SecCopyExamples ${LANG_ENGLISH} "Copy scripts with exapmles"
  LangString DESC_SecCopyDoc ${LANG_ENGLISH} "Copy surfit documentation"

;--------------------------------
;Data
  
  ;LicenseData "${NSISDIR}\Contrib\Modern UI\License.txt"

;--------------------------------
;Reserve Files
  
  ;Things that need to be extracted on first (keep these lines before any File command!)
  ;Only useful for BZIP2 compression
  
  ;ReserveFile "surfit-1.0.0\images\logo.bmp"

;--------------------------------
;Installer Sections

Section "calculation" SecCopyCalc

  ;ADD YOUR OWN STUFF HERE!
  SectionIn RO

  SetOutPath "$INSTDIR\bin\library"
  File "bin\library\*"

  SetOutPath "$INSTDIR\bin"
  File "bin\tclsh83.exe"
  File "bin\tcl83.dll"
  File "bin\libsurfit.dll"
  File "bin\grd2dat.bat"
  File "bin\dat2grd.bat"
  File "bin\run_examples.bat"
   

  ReadRegStr $1 HKCU "Environment" PATH
                     
  WriteRegStr HKCU "Environment" PATH $1;$INSTDIR\bin

  ReadRegStr $1 HKCU "Environment" TCL_LIBRARY

  WriteRegStr HKCU "Environment" TCL_LIBRARY $1;$INSTDIR\bin\library
  File "surfit-1.0.0\tools\setpath.exe"
  
  ;Store install folder
  WriteRegStr HKCU "Software\${MUI_PRODUCT}" "" $INSTDIR

!insertmacro MUI_STARTMENU_WRITE_BEGIN
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}"
    CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\tclsh.lnk" "$INSTDIR\bin\tclsh84.exe"
    CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\run_examples.lnk" "$INSTDIR\bin\run_examples.bat"
    CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

Section "visualization" SecCopyVis
  SetOutPath "$INSTDIR\bin"
  File "bin\funner.exe"
  File "bin\Bula.exe"
  File "bin\libsurfit_gl.dll"
  CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\bula.lnk" "$INSTDIR\bin\Bula.exe"
  CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\funner.lnk" "$INSTDIR\bin\funner.exe"
SectionEnd

Section "sample data" SecCopyData
  SetOutPath "$INSTDIR\data\"
  File "data\make_all_bins.bat"

  ; 1d
  SetOutPath "$INSTDIR\data\1d"
  File "data\1d\make_all_bins.bat"
  File "data\1d\make_bin.bat"
  File "data\1d\make_bin.tcl"
  File "data\1d\sin.txt"
  File "data\1d\sin1000.txt"
  SetOutPath "$INSTDIR\data\1d\test1d"
  File "data\1d\test1d\ex2.txt"
  File "data\1d\test1d\make_bin.bat"
  File "data\1d\test1d\make_bin.tcl"
  File "data\1d\test1d\trend1.txt"
  File "data\1d\test1d\trend2.txt"

  ; 2d
  SetOutPath "$INSTDIR\data\2d"
  File "data\2d\make_all_bins.bat"
  SetOutPath "$INSTDIR\data\2d\oilfield1"
  File "data\2d\oilfield1\aobt.xyz"
  File "data\2d\oilfield1\make_sin.m"
  File "data\2d\oilfield1\sin_trend.xyz"
  File "data\2d\oilfield1\make_bin.bat"
  File "data\2d\oilfield1\make_bin.tcl"

  SetOutPath "$INSTDIR\data\2d\oilfield2"
  File "data\2d\oilfield2\2d_seism.xyz"
  File "data\2d\oilfield2\3d_seism.xyz"
  File "data\2d\oilfield2\aoup.xyz"
  File "data\2d\oilfield2\make_bin.bat"
  File "data\2d\oilfield2\make_bin.tcl"

  SetOutPath "$INSTDIR\data\2d\oilfield3"
  File "data\2d\oilfield3\aobt.xyz"
  File "data\2d\oilfield3\aoup.xyz"
  File "data\2d\oilfield3\heff.xyz"
  File "data\2d\oilfield3\heffoil.xyz"
  File "data\2d\oilfield3\make_bin.bat"
  File "data\2d\oilfield3\make_bin.tcl"
  File "data\2d\oilfield3\trend.m"
  File "data\2d\oilfield3\trend.xyz"
  File "data\2d\oilfield3\woc.xyz"

SectionEnd

Section "examples" SecCopyExamples
  SetOutPath "$INSTDIR\examples"
  File "examples\run.bat"
  File "examples\surfit.tcl"
  File "examples\surfit_1d.tcl"
  File "examples\surfit_2d.tcl"

  SetOutPath "$INSTDIR\examples\1d"
  File "examples\1d\pre_trend.tcl"
  File "examples\1d\sin.tcl"
  File "examples\1d\sin1000.tcl"
  File "examples\1d\use_trend.tcl"

  SetOutPath "$INSTDIR\examples\2d"
  File "examples\2d\oilfield1.tcl"
  File "examples\2d\oilfield2.tcl"
  File "examples\2d\oilfield3.tcl"

  SetOutPath "$INSTDIR\examples\2d\oilfield1"
  File "examples\2d\oilfield1\map_trend.tcl"
  File "examples\2d\oilfield1\map_aobt.tcl"
  File "examples\2d\oilfield1\map_aobt_wtrend.tcl"
  File "examples\2d\oilfield1\map_aobt_noised.tcl"
  File "examples\2d\oilfield1\set_params.tcl"

  SetOutPath "$INSTDIR\examples\2d\oilfield2"
  File "examples\2d\oilfield2\map_2d_seism.tcl"
  File "examples\2d\oilfield2\map_3d_seism.tcl"
  File "examples\2d\oilfield2\map_aoup.tcl"
  File "examples\2d\oilfield2\map_aoup_wrong.tcl"
  File "examples\2d\oilfield2\set_params.tcl"

  SetOutPath "$INSTDIR\examples\2d\oilfield3"
  File "examples\2d\oilfield3\map_aobt.tcl"
  File "examples\2d\oilfield3\map_aoup.tcl"
  File "examples\2d\oilfield3\map_aoup_wrong.tcl"
  File "examples\2d\oilfield3\map_heff.tcl"
  File "examples\2d\oilfield3\map_heffoil.tcl"
  File "examples\2d\oilfield3\map_hoil.tcl"
  File "examples\2d\oilfield3\map_htotal.tcl"
  File "examples\2d\oilfield3\map_oil.tcl"
  File "examples\2d\oilfield3\map_water.tcl"
  File "examples\2d\oilfield3\map_watoil.tcl"
  File "examples\2d\oilfield3\map_woc.tcl"
  File "examples\2d\oilfield3\map_trend.tcl"
  File "examples\2d\oilfield3\set_params.tcl"

  SetOutPath "$INSTDIR\results\1d"
  
  SetOutPath "$INSTDIR\results\2d\oilfield1"
  
  SetOutPath "$INSTDIR\results\2d\oilfield2"
  
  SetOutPath "$INSTDIR\results\2d\oilfield3"

SectionEnd

;Section "documentation" SecCopyDoc
;  SetOutPath "$INSTDIR\doc"
;  File /r "doc\html\*.*"
;  CreateShortCut "$SMPROGRAMS\${MUI_STARTMENUPAGE_VARIABLE}\documentation.lnk" "$INSTDIR\doc\index.html"
;SectionEnd

;Display the Finish header
;Insert this macro after the sections if you are not using a finish page
!insertmacro MUI_SECTIONS_FINISHHEADER

;--------------------------------
;Descriptions

!insertmacro MUI_FUNCTIONS_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCopyCalc} $(DESC_SecCopyCalc)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCopyVis} $(DESC_SecCopyVis)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCopyData} $(DESC_SecCopyData)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCopyExamples} $(DESC_SecCopyExamples)
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCopyDoc} $(DESC_SecCopyDoc)
!insertmacro MUI_FUNCTIONS_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"

  Delete "$INSTDIR\Uninstall.exe"

  ;Remove shortcut
  ReadRegStr ${TEMP} "${MUI_STARTMENUPAGE_REGISTRY_ROOT}" "${MUI_STARTMENUPAGE_REGISTRY_KEY}" "${MUI_STARTMENUPAGE_REGISTRY_VALUENAME}"
  
  StrCmp ${TEMP} "" noshortcuts
  
    Delete "$SMPROGRAMS\${TEMP}\tclsh.lnk"
    Delete "$SMPROGRAMS\${TEMP}\run_examples.lnk"
    Delete "$SMPROGRAMS\${TEMP}\bula.lnk"
    Delete "$SMPROGRAMS\${TEMP}\funner1d.lnk"
    Delete "$SMPROGRAMS\${TEMP}\funner2d.lnk"
    Delete "$SMPROGRAMS\${TEMP}\documentation.lnk"
    Delete "$SMPROGRAMS\${TEMP}\Uninstall.lnk"
    RMDir "$SMPROGRAMS\${TEMP}" ;Only if empty, so it won't delete other shortcuts
    
  noshortcuts:

  RMDir /r "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\${MUI_PRODUCT}"

  DeleteRegKey /ifempty HKCU "Software\${MUI_PRODUCT}"

  ;Display the Finish header
  !insertmacro MUI_UNFINISHHEADER

SectionEnd

 Function .onInstSuccess
    Exec "$INSTDIR\bin\setpath.exe"
    Delete "$INSTDIR\bin\setpath.exe"
 FunctionEnd
