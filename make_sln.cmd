echo off

mkdir build
cd build

cmake ..\src\ -G "Visual Studio 14 2015" -DSWIG_EXECUTABLE=c:\swig\swig.exe -DSWIG_DIR=c:\swig\ -DPYTHON_INCLUDE_DIR=C:\Python35\include\ -DPYTHON_LIBRARY=C:\Python35\libs\python35.lib 