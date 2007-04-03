set PATH=%PATH%;..\..\..\libs\swig
cd ..
cd src
swig.exe -c++ -tcl -o acmlbooster_wrap.cxx interface/acmlbooster.i
