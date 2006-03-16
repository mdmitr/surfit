mkdir bin
cd vc6
del *.dep
nmake.exe acmlbooster.mak 	CFG="acmlbooster - Win32 Release"
cd ..