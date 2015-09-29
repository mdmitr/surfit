echo off

mkdir build64
cd build64

cmake -G "Visual Studio 12 Win64" ..\src\ -DSWIG_EXECUTABLE=c:\swig\swig.exe -DSWIG_DIR=c:\swig\