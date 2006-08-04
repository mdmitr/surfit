;NSIS Modern User Interface


;--------------------------------
;Include Modern UI

  !include "MUI.nsh"
  !include "path_man.nsi"
  !include "WordFunc.nsh"

  !insertmacro VersionCompare

;--------------------------------
;General

  ;Name and file
  Name "surfit"
  OutFile "surfit-2.1-setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\surfit-2.1"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\surfit" ""


;--------------------------------
;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER
  Var VERSION
  Var SURFIT_VERSION

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

Function ConnectInternet

  Push $R0
    
    ClearErrors
    Dialer::AttemptConnect
    IfErrors noie3
    
    Pop $R0
    StrCmp $R0 "online" connected
      MessageBox MB_OK|MB_ICONSTOP "Cannot connect to the internet."
      Quit
    
    noie3:
  
    ; IE3 not installed
    MessageBox MB_OK|MB_ICONINFORMATION "Please connect to the internet now."
    
    connected:
  
  Pop $R0
  
FunctionEnd

Function .onInit

  ReadRegStr $SURFIT_VERSION HKCU "Software\surfit" "Version"

  StrCmp $SURFIT_VERSION "" can_continue_install

  ${VersionCompare} "2.1" $SURFIT_VERSION" $R0

  StrCmp $R0 "0" can_continue_install

  MessageBox MB_OK "You should uninstall installed version of surfit first!"
  Abort

can_continue_install:

  StrCpy $STARTMENU_FOLDER "surfit-2.1"
  StrCpy $VERSION "2.1"

  InitPluginsDir
  SearchPath $1 tclsh83.exe

  StrCmp $1 "" wanna_tcl
  Goto end
  
  wanna_tcl:

  	MessageBox MB_YESNOCANCEL "Installer can't find Tcl8.3 library! Installation will be aborted. Do you want to automatically download Active Tcl8.3.5 (about 7mb)? Press NO to download manually, CANCEL to abort installation" IDYES auto IDNO manual

		Abort 

		manual:

		ExecShell "open" "http://downloads.activestate.com/ActiveTcl/Windows/8.3.5/"
		Abort

		auto:

        	Call ConnectInternet ;Make an internet connection (if no connection available)
		StrCpy $2 "$TEMP\ActiveTcl8.3.5.0-2-win32-ix86.exe"
 		StrCpy $3 http://downloads.activestate.com/ActiveTcl/Windows/8.3.5/ActiveTcl8.3.5.0-win32-ix86.exe 
		NSISdl::download $3 $2
		Pop $R0 ;Get the return value

		StrCmp $R0 "success" tcl_success tcl_failed

		  tcl_success:
		  Exec '$2'

		  tcl_failed:
                  MessageBox MB_OK "Download failed: $R0, you can download it manually from $3" IDYES true2 IDNO false2
		  
		  true2:
		  ExecShell "open" "http://downloads.activestate.com/ActiveTcl/Windows/8.3.5/"

		  false2:

		Abort
  
	Abort
  end:

FunctionEnd

  Function .onInstSuccess
    MessageBox MB_YESNO "Congratulations, installation is completed! Do you want to download GUI for surfit?" IDNO NoGui
      ExecShell "open" "http://www.gridding.info/funner.php"
    NoGui:
  FunctionEnd


;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "..\copying"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Modern UI Test" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"

 
  !insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER


  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

SectionGroup "binaries" SecBinary

	Section "libsurfit" SecSurfitDll

	  SetOutPath "$INSTDIR\bin"
	  SectionIn RO

	  ;Store installation folder
	  WriteRegStr HKCU "Software\surfit" "" $INSTDIR
	  ;Store startmenu folder
	  WriteRegStr HKCU "Software\surfit" "StartMenuFolder" $STARTMENU_FOLDER
	  ;Store version
	  WriteRegStr HKCU "Software\surfit" "Version" $VERSION
  
	  ;Create uninstaller
	  WriteUninstaller "$INSTDIR\Uninstall.exe"

	  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
	    ;Create shortcuts
	    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
	  !insertmacro MUI_STARTMENU_WRITE_END

	  File "..\bin\libsstuff.dll"
	  File "..\bin\libsurfit.dll"

	  Push $INSTDIR/bin
	  Call AddToPath

	SectionEnd

	Section "libfreeflow" SecFreeflowDll
	  SetOutPath "$INSTDIR\bin"
	  File "..\bin\libsstuff.dll"
	  File "..\bin\libfreeflow.dll"
	SectionEnd

	Section "libglobe" SecGlobeDll
	  SetOutPath "$INSTDIR\bin"
	  File "..\bin\libsstuff.dll"
	  File "..\bin\libglobe.dll"
	  File "..\bin\zlib1.dll"
	SectionEnd

	Section "libsurfit_io" SecSurfitIODll
	  SetOutPath "$INSTDIR\bin"
	  File "..\bin\libsurfit_io.dll"
	  File "..\bin\netcdf.dll"
	  File "..\bin\shapelib.dll"
        SectionEnd
	 

SectionGroupEnd

Section "examples" SecExamples

  SetOutPath "$INSTDIR\examples"
  File /r /x CVS "..\examples\*.*"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\examples.lnk" "$INSTDIR\examples\"

SectionEnd

SectionGroup "sources" SecSources

	Section "surfit" SecSurfitSources
	  SetOutPath "$INSTDIR\src\sstuff"
	  File /r /x CVS "..\src\sstuff\*.*"
	  SetOutPath "$INSTDIR\src\surfit"
	  File /r /x CVS "..\src\surfit\*.*"
	SectionEnd

	Section "freeflow" SecFreeflowSources
	  SetOutPath "$INSTDIR\src\freeflow\"
	  File /r /x CVS "..\src\freeflow\*.*"
	SectionEnd

	Section "globe" SecGlobeSources
	  SetOutPath "$INSTDIR\src\globe"
	  File /r /x CVS "..\src\globe\*.*"
	SectionEnd
       
	Section "surfit_io" SecSurfitIOSources
	  SetOutPath "$INSTDIR\src\surfit_io"
	  File /r /x CVS "..\src\surfit_io\*.*"
	SectionEnd

	Section "VC6 project files" SecVC6
	  SetOutPath "$INSTDIR\vc6"
	  File /r /x CVS "..\vc6\*.bat"
	  File /r /x CVS "..\vc6\*.dsp"
	  File /r /x CVS "..\vc6\*.dsw"
	  File /r /x CVS "..\vc6\*.mak"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\build"
	  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\build\surfit.lnk" "$INSTDIR\vc6\surfit.dsw"
        SectionEnd

	Section "configure scripts" SecLinux
          SetOutPath "$INSTDIR"
	  File ..\*.*
        SectionEnd

SectionGroupEnd

Section "documentation" SecDocs
  SetOutPath "$INSTDIR\doc\"
  File /x CVS "..\bin\surfit.chm"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\surfit.lnk" "$INSTDIR\doc\surfit.chm"
SectionEnd


;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecSurfitDll ${LANG_ENGLISH} "libsurfit.dll"
  LangString DESC_SecFreeflowDll ${LANG_ENGLISH} "libfreeflow.dll"
  LangString DESC_SecGlobeDll ${LANG_ENGLISH} "libglobe.dll"
  LangString DESC_SecSurfitIODll ${LANG_ENGLISH} "libsurfit_io.dll"
  LangString DESC_SecSurfitSources ${LANG_ENGLISH} "surfit sources."
  LangString DESC_SecFreeflowSources ${LANG_ENGLISH} "freeflow sources."
  LangString DESC_SecGlobeSources ${LANG_ENGLISH} "globe sources."
  LangString DESC_SecSurfitIOSources ${LANG_ENGLISH} "surfit_io sources."
  LangString DESC_SecDocs ${LANG_ENGLISH} "documentation for surfit, freeflow and globe"
  LangString DESC_Src ${LANG_ENGLISH} "source files (*.cpp, *.h, ...)"
  LangString DESC_Examples ${LANG_ENGLISH} "set of scripts for example"
  LangString DESC_Binary ${LANG_ENGLISH} "libsstuff.dll libsurfit.dll libfreeflow.dll libglobe.dll"
  LangString DESC_VC6 ${LANG_ENGLISH} "Contains *.dsw and *.dsp files"


  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSurfitDll} $(DESC_SecSurfitDll)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecFreeflowDll} $(DESC_SecFreeflowDll)    
    !insertmacro MUI_DESCRIPTION_TEXT ${SecGlobeDll} $(DESC_SecGlobeDll)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSurfitIODll} $(DESC_SecSurfitIODll)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSurfitSources} $(DESC_SecSurfitSources)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecFreeflowSources} $(DESC_SecFreeflowSources)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecGlobeSources} $(DESC_SecGlobeSources)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSurfitIOSources} $(DESC_SecSurfitIOSources)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDocs} $(DESC_SecDocs)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSources} $(DESC_Src)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecExamples} $(DESC_Examples)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecBinary} $(DESC_Binary)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecVC6} $(DESC_VC6)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"

  RMDir /r /REBOOTOK "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\surfit"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
    
  Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\doc.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\surfit_examples.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\freeflow_examples.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\globe_examples.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\surfit.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\build\surfit.lnk"
  RMDir "$SMPROGRAMS\$MUI_TEMP\build"

  RMDir /r /REBOOTOK "$SMPROGRAMS\$MUI_TEMP"

; ;Delete empty start menu parent diretories
;  StrCpy $MUI_TEMP "$SMPROGRAMS\$MUI_TEMP"
 
;  startMenuDeleteLoop:
;	ClearErrors
;    RMDir $MUI_TEMP
;    GetFullPathName $MUI_TEMP "$MUI_TEMP\.."
    
;    IfErrors startMenuDeleteLoopDone
  
;    StrCmp $MUI_TEMP $SMPROGRAMS startMenuDeleteLoopDone startMenuDeleteLoop
;  startMenuDeleteLoopDone:

  Push $INSTDIR/bin
  Call un.RemoveFromPath


SectionEnd


