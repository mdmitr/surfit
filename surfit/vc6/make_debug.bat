mkdir ..\bin
cd vc6
del *.dep
nmake.exe sstuff.mak 		CFG="sstuff - Win32 Debug"
nmake.exe surfit.mak 		CFG="surfit - Win32 Debug"
nmake.exe freeflow.mak 		CFG="freeflow - Win32 Debug"
nmake.exe globe.mak 		CFG="globe - Win32 Debug"
nmake.exe surfit_io.mak 	CFG="surfit_io - Win32 Debug"
