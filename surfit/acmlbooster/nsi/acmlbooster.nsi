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
  Name "acmlbooster-1.0"
  OutFile "acmlbooster-1.0-setup.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\surfit-2.0"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\surfit" ""


;--------------------------------
;Variables

  Var MUI_TEMP
  Var STARTMENU_FOLDER
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

  ReadRegStr $STARTMENU_FOLDER HKCU "Software\surfit" "StartMenuFolder"
  ReadRegStr $SURFIT_VERSION HKCU "Software\surfit" "Version"

  ${VersionCompare} "2.0" $SURFIT_VERSION" $R0

  InitPluginsDir

  StrCmp $R0 "1" wanna_surfit
  Goto end
  
  wanna_surfit:

  	MessageBox MB_YESNO "Installer can't find surfit library! Installation will be aborted. Do you want to download surfit? Press NO to abort installation" IDYES manual

		Abort 

		manual:

		ExecShell "open" "http://sourceforge.net/project/showfiles.php?group_id=57520"
		Abort

	Abort
  end:

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
  WriteRegStr HKCU "Software\surfit-1.0" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall_acmlbooster.exe"

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall_acmlbooster.lnk" "$INSTDIR\Uninstall_acmlbooster.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END

  Push $INSTDIR/bin
  Call AddToPath

  File "..\bin\libacmlbooster.dll"

SectionEnd

Section "sources" SecSources

  SetOutPath "$INSTDIR\acmlbooster\src"
  File /r /x CVS "..\src\*.*"
  SetOutPath "$INSTDIR\acmlbooster\vc6"
  File /r /x CVS "..\vc6\*.bat"
  File /r /x CVS "..\vc6\*.dsp"
  File /r /x CVS "..\vc6\*.dsw"
  File /r /x CVS "..\vc6\*.mak"

  SetOutPath "$INSTDIR"
  File /x CVS ..\*.*

  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER\build"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\build\acmlbooster.lnk" "$INSTDIR\acmlbooster\vc6\acmlbooster.dsw"


SectionEnd

Section "examples" SecExamples

  SetOutPath "$INSTDIR\examples\acmlbooster"
  File /r /x CVS "..\examples\acmlbooster\points.txt"
  File /r /x CVS "..\examples\acmlbooster\acml_test.tcl"
  CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
  CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\examples.lnk" "$INSTDIR\examples\"
  SetOutPath "$INSTDIR\doc\acmlbooster"
  File /r /x CVS "..\doc\readme.txt"

SectionEnd



;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_Sources ${LANG_ENGLISH} "source files (*.cpp, *.h, ...)"
  LangString DESC_Binary ${LANG_ENGLISH} "libacmlbooster.dll"
  LangString DESC_Binary ${LANG_ENGLISH} "acml_test.tcl"


  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecBinary} $(DESC_Binary)
    !insertmacro MUI_DESCRIPTION_TEXT ${SecSources} $(DESC_Sources)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...
  Delete "$INSTDIR\Uninstall_acmlbooster.exe"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
  Delete "$SMPROGRAMS\$MUI_TEMP\build\acmlbooster.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall_acmlbooster.lnk"
    
  ;Delete empty start menu parent diretories
  StrCpy $MUI_TEMP "$SMPROGRAMS\$MUI_TEMP"

  Push $INSTDIR/bin
  Call un.RemoveFromPath
 
SectionEnd


