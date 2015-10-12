echo off

rmdir /s /q Release
mkdir Release
cd Release

cmake -DCMAKE_BUILD_TYPE=Release -G "NMake Makefiles" -DSWIG_EXECUTABLE=c:\swig\swig.exe -DSWIG_DIR=c:\swig\ ..\src\ && nmake 

cd ..