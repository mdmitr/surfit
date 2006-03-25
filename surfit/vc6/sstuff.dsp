# Microsoft Developer Studio Project File - Name="sstuff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sstuff - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sstuff.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/sstuff", HAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sstuff - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SSTUFF_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /Op /Ob2 /I "../sstuff/src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /FD /Gs /Gs /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib /nologo /dll /machine:I386 /out:"../bin/libsstuff.dll" /implib:"../bin/libsstuff.lib"
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "sstuff - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SSTUFF_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /Zi /Od /I "../sstuff/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib /nologo /dll /pdb:none /map /debug /machine:I386 /out:"../bin/libsstuff.dll" /implib:"../bin/libsstuff.lib"

!ENDIF 

# Begin Target

# Name "sstuff - Win32 Release"
# Name "sstuff - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "vec_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\sstuff\bitvec.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\boolvec.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\intvec.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\shortvec.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\strvec.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\vec.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\vec_alg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\sstuff\datafile.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\fileio.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\geom_alg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\interp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\read_txt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\rnd.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\sstuff.cpp
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\stepFunc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "vec_h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\sstuff\bitvec.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\bitvec_alg.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\boolvec.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\intvec.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\shortvec.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\strvec.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\vec.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\vec_alg.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\sstuff\byteswap_alg.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\datafile.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\fileio.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\geom_alg.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\interp.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\read_txt.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\real.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\rnd.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\sstuff.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\sstuff_ie.h
# End Source File
# Begin Source File

SOURCE=..\src\sstuff\stepFunc.h
# End Source File
# End Group
# End Target
# End Project
