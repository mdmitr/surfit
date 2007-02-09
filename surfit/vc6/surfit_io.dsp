# Microsoft Developer Studio Project File - Name="surfit_io" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=surfit_io - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "surfit_io.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "surfit_io - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "surfit_io_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /Ob2 /I "../src/sstuff" /I "../src/sstuff/ptypes" /I "../src/surfit" /I "..\..\libs\jpeg-6b\\" /I "C:\Tcl\include\\" /I "..\..\libs\NETCDF\LIBSRC" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fr /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 tcl83.lib zdll.lib netcdf.lib libjpeg.lib /nologo /dll /machine:I386 /nodefaultlib:"LIBC" /out:"../bin/libsurfit_io.dll" /implib:"../bin/libsurfit_io.lib" /libpath:"..\..\libs\jpeg-6b" /libpath:"C:\Tcl\lib" /libpath:"..\..\libs\zlib123-dll\lib\\" /libpath:"..\..\libs\netcdf\libsrc\\"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "surfit_io - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "surfit_io_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../src/sstuff" /I "../src/sstuff/ptypes" /I "../src/surfit" /I "..\..\LIBS\JPEG-6B" /I "C:\Tcl\include\\" /I "..\..\libs\NETCDF\LIBSRC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 tcl83d.lib netcdf.lib libjpeg.lib /nologo /dll /debug /machine:I386 /nodefaultlib:"MSVCRT" /out:"../bin/libsurfit_io.dll" /implib:"../bin/libsurfit_io.lib" /pdbtype:sept /libpath:"..\..\libs\jpeg-6b" /libpath:"..\..\libs\NETCDF\LIBSRC" /libpath:"..\..\LIBS\TCL8.3.5\WIN\DEBUG" /libpath:"..\..\libs\jpeg-6b\\"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "surfit_io - Win32 Release"
# Name "surfit_io - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "surf_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\surf_arcgis.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_gmt.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_grass.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_grd.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_io_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_jpg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_xyz.cpp
# End Source File
# End Group
# Begin Group "EasyBmp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\EasyBmp\EasyBMP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\EasyBmp\EasyBMP.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\EasyBmp\EasyBMP_BMP.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\EasyBmp\EasyBMP_DataStructures.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\EasyBmp\EasyBMP_VariousBMPutilities.h
# End Source File
# End Group
# Begin Group "shapelib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\shapelib\dbfopen.c
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\shapelib\shapefil.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\shapelib\shpopen.c
# End Source File
# End Group
# Begin Group "pnts_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\pnts_io_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\pnts_shp.cpp
# End Source File
# End Group
# Begin Group "curv_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\curv_bln.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\curv_io_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\curv_shp.cpp
# End Source File
# End Group
# Begin Group "area_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\area_bln.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\area_io_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\area_shp.cpp
# End Source File
# End Group
# Begin Group "cntr_cpp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\src\surfit_io\cntr_io_tcl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\cntr_shp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io_data_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io_variables.cpp
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io_wrap.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\surfit_io\area_io.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\area_io_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\cntr_io.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\cntr_io_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\curv_io.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\curv_io_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\pnts_io.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\pnts_io_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_io.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surf_io_tcl.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io_data_manager.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io_ie.h
# End Source File
# Begin Source File

SOURCE=..\src\surfit_io\surfit_io_variables.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\..\src\surfit_io\interface\surfit_io.i

!IF  "$(CFG)" == "surfit_io - Win32 Release"

# Begin Custom Build
InputPath=.\..\src\surfit_io\interface\surfit_io.i

"../src/surfit_io/surfit_io_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	surfit_io_swig.bat

# End Custom Build

!ELSEIF  "$(CFG)" == "surfit_io - Win32 Debug"

# Begin Custom Build
InputPath=.\..\src\surfit_io\interface\surfit_io.i

"../src/surfit_io/surfit_io_wrap.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	surfit_io_swig.bat

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
