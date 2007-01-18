set PATH=%PATH%;..\..\..\libs\swig
cd ..
cd src
cd freeflow
swig.exe -c++ -tcl -o freeflow_wrap.cxx interface/freeflow.i
