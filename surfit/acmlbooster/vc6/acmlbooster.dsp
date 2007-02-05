# Microsoft Developer Studio Project File - Name="acmlbooster" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=acmlbooster - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "acmlbooster.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "acmlbooster - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ACMLBOOSTER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /Ob2 /I "../../src/sstuff" /I "../../src/sstuff/ptypes" /I "../../src/surfit" /I "../../../libs/acml/include" /I "c:\Tcl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ACMLBOOSTER_EXPORTS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib libacml.lib libsstuff.lib libsurfit.lib /nologo /dll /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"../../bin/libacmlbooster.dll" /implib:"../../bin/libacmlbooster.lib" /libpath:"../../bin" /libpath:"../../../libs/acml/lib" /libpath:"c:\tcl\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "acmlbooster - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ACMLBOOSTER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "../../src/sstuff" /I "../../src/sstuff/ptypes" /I "../../src/surfit" /I "../../../libs/acml/include" /I "c:\Tcl\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ACMLBOOSTER_EXPORTS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib libacml.lib libsurfit.lib libsstuff.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /out:"../../bin/libacmlbooster.dll" /implib:"../../bin/libacmlbooster.lib" /pdbtype:sept /libpath:"../../bin" /libpath:"../../../libs/acml/lib" /libpath:"../../../libs/tcl8.3.5/win/debug"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "acmlbooster - Win32 Release"
# Name "acmlbooster - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\acml_cg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\acml_threads.cpp
# End Source File
# Begin Source File

SOURCE=..\src\acmlbooster.cpp
# End Source File
# Begin Source File

SOURCE=..\src\acmlbooster_wrap.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\acmlbooster.h
# End Source File
# Begin Source File

SOURCE=..\src\acmlbooster_ie.h
# End Source File
# End Group
# Begin Group "Interface Files"

# PROP Default_Filter "i"
# Begin Source File

SOURCE=..\src\interface\acmlbooster.i

!IF  "$(CFG)" == "acmlbooster - Win32 Release"

# Begin Custom Build
InputPath=..\src\interface\acmlbooster.i

"../src/acmlbooster_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	acmlbooster_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "acmlbooster - Win32 Debug"

# Begin Custom Build
InputPath=..\src\interface\acmlbooster.i

"../src/acmlbooster_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	acmlbooster_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
