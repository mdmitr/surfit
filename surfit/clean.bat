mkdir bin
cd bin
del libsstuff.*
del libsurfit.*
del libglobe.*
del libfreeflow.*
del libsurfit_io.*
del libacml*.*
del surfit.chm
del surfit.exe
cd ..

mkdir bin_SSE
cd bin_SSE
del libsstuff.*
del libsurfit.*
del libglobe.*
del libfreeflow.*
del libsurfit_io.*
del libacml*.*
del surfit.chm
cd ..

mkdir bin_SSE2
cd bin_SSE2
del libsstuff.*
del libsurfit.*
del libglobe.*
del libfreeflow.*
del libsurfit_io.*
del libacml*.*
del surfit.chm
cd ..

mkdir examples
cd examples
del /Q /S *.jpg
del /Q /S *.bmp
del /Q /S *hist_src.txt
del /Q /S *hist_result.txt
cd ..

del /Q /S *.dat
del /Q /S *.grd
del /Q /S *.ps
del /Q /S *.log
del /Q /S *.errlog
del /Q /S .#*
del /Q /S *.sbr
del /Q /S *.pdb
del /Q /S *.pgc
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

mkdir Release_SSE
cd Release_SSE
del /Q /S *.*
cd ..

mkdir Release_SSE2
cd Release_SSE2
del /Q /S *.*
cd ..

mkdir vc6
cd vc6
del *.ncb
del *.plg
cd ..

mkdir vc7
cd vc7
del *.ncb
del *.plg
cd ..

mkdir vc8
cd vc8
del *.ncb
del *.plg
cd ..

del *.o
del *.lo
del *.la

cd acmlbooster
call clean.bat
cd ..

cd mklbooster
call clean.bat
cd ..
