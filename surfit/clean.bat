
del Bula.exe
del funner.exe

cd bin
del Bula.exe
del funner.exe
del libsurfit.dll
del libsurfit.map
del libsurfit.pdb
del libsurfit_gl.dll
del libglobe.dll
del libfreeflow.dll
del *.ilk
del *.SUP
del *.tcl
del *.nmp
cd ..

del /Q /S *.dat
del /Q /S *.log
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

cd vc6
del *.ncb
del *.plg
cd ..

del surfit\examples\test\task_residuals.txt

del *.o
del *.lo
del *.la