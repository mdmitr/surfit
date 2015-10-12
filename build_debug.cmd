echo off

rmdir /s /q Debug
mkdir Debug
cd Debug

cmake -DCMAKE_BUILD_TYPE=Debug -G "NMake Makefiles" -DSWIG_EXECUTABLE=c:\swig\swig.exe -DSWIG_DIR=c:\swig\ ..\src\ && nmake 

cd ..