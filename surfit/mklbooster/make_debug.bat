mkdir bin
cd vc6
del *.dep
nmake.exe mklbooster.mak 	CFG="mklbooster - Win32 Debug"
cd ..