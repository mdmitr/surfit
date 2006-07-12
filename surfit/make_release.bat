mkdir bin
cd vc6
del *.dep
nmake.exe sstuff.mak 		CFG="sstuff - Win32 Release"
nmake.exe surfit.mak 		CFG="surfit - Win32 Release"
nmake.exe freeflow.mak 		CFG="freeflow - Win32 Release"
nmake.exe globe.mak 		CFG="globe - Win32 Release"
nmake.exe surfit_io.mak 	CFG="surfit_io - Win32 Release"
cd ..