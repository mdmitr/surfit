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
  OutFile "surfit-2.2-setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\surfit-2.2"
  
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

  ${VersionCompare} "2.2" $SURFIT_VERSION" $R0

  StrCmp $R0 "0" can_continue_install

  MessageBox MB_OK "You should uninstall installed version of surfit first!"
  Abort

can_continue_install:

  StrCpy $STARTMENU_FOLDER "surfit-2.2"
  StrCpy $VERSION "2.2"

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

Section "binaries" SecBinary

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

	  Push $INSTDIR/bin
	  Call AddToPath

	  SetOutPath "$INSTDIR\bin"

	  cpudesc::tell
	  Pop $0                     ;full identification string in $0

	  StrCpy $3 $0 1 41         ;pull out one character after SSE2=
	  IntCmpU $3 1 +1 check_sse check_sse
	  File "..\bin_SSE2\libsstuff.dll"
	  File "..\bin_SSE2\libsurfit.dll"
	  File "..\bin_SSE2\libfreeflow.dll"
	  File "..\bin_SSE2\libglobe.dll"
	  File "..\bin_SSE2\libsurfit_io.dll"
	  Goto binary_done

check_sse:

	  StrCpy $3 $0 1 34         ;pull out one character after SSE=
  	  IntCmpU $3 1 +1 usual_install usual_install
	  File "..\bin_SSE\libsstuff.dll"
	  File "..\bin_SSE\libsurfit.dll"
	  File "..\bin_SSE\libfreeflow.dll"
	  File "..\bin_SSE\libglobe.dll"
	  File "..\bin_SSE\libsurfit_io.dll"
	  Goto binary_done

usual_install:

	  File "..\bin\libsstuff.dll"
	  File "..\bin\libsurfit.dll"
	  File "..\bin\libfreeflow.dll"
	  File "..\bin\libglobe.dll"
	  File "..\bin\libsurfit_io.dll"

binary_done:

 	  File "..\bin\zlib1.dll"
	  File "..\bin\netcdf.dll"


SectionEnd

Section "examples" SecExamples

  SetOutPath "$INSTDIR\examples"
  File /r /x .svn "..\examples\*.*"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\examples.lnk" "$INSTDIR\examples\"

SectionEnd

Section "sources" SecSources
	  SetOutPath "$INSTDIR\src\sstuff"
	  File /r /x .svn "..\src\sstuff\*.*"
	  SetOutPath "$INSTDIR\src\surfit"
	  File /r /x .svn "..\src\surfit\*.*"
	  SetOutPath "$INSTDIR\src\freeflow\"
	  File /r /x .svn "..\src\freeflow\*.*"
	  SetOutPath "$INSTDIR\src\globe"
	  File /r /x .svn "..\src\globe\*.*"
	  SetOutPath "$INSTDIR\src\surfit_io"
	  File /r /x .svn "..\src\surfit_io\*.*"
	  SetOutPath "$INSTDIR\vc6"
	  File /r /x .svn "..\vc6\*.bat"
	  File /r /x .svn "..\vc6\*.dsp"
	  File /r /x .svn "..\vc6\*.dsw"
	  File /r /x .svn "..\vc6\*.mak"
	  File /r /x .svn "..\vc7\*.sln"
	  File /r /x .svn "..\vc7\*.bat"
	  File /r /x .svn "..\vc7\*.vcproj"
	  File /r /x .svn "..\vc8\*.sln"
	  File /r /x .svn "..\vc8\*.bat"
	  File /r /x .svn "..\vc8\*.vcproj"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\sources"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\sources\vc6"
	  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\sources\vc6\surfit.lnk" "$INSTDIR\vc6\surfit.dsw"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\sources\vc7"
	  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\sources\vc7\surfit.lnk" "$INSTDIR\vc7\surfit.sln"
	  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\sources\vc8"
	  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\sources\vc8\surfit.lnk" "$INSTDIR\vc8\surfit.sln"
          SetOutPath "$INSTDIR"
	  File ..\*.*
SectionEnd

Section "documentation" SecDocs
  SetOutPath "$INSTDIR\doc\"
  File /x .svn "..\bin\surfit.chm"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\surfit.lnk" "$INSTDIR\doc\surfit.chm"
SectionEnd


;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecDocs ${LANG_ENGLISH} "documentation for surfit, freeflow and globe"
  LangString DESC_Src ${LANG_ENGLISH} "source files (*.cpp, *.h, ...)"
  LangString DESC_Examples ${LANG_ENGLISH} "set of scripts for example"
  LangString DESC_Binary ${LANG_ENGLISH} "libsstuff.dll libsurfit.dll libfreeflow.dll libglobe.dll"


  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecDocs} $(DESC_SecDocs)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSources} $(DESC_Src)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecExamples} $(DESC_Examples)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecBinary} $(DESC_Binary)
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


