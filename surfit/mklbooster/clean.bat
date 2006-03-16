mkdir bin
cd bin
del libmklbooster.*
cd ..

del /Q /S *.dat
del /Q /S *.grd
del /Q /S *.log
del /Q /S .#*
del *.plg
del *.stt

mkdir Debug

cd Debug
del /Q /S *.*
cd ..

mkdir Release 

cd Release
del /Q /S *.*
cd ..

mkdir vc6
cd vc6
del *.ncb
del *.plg
cd ..

del *.o
del *.lo
del *.la