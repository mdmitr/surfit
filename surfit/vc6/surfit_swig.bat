set PATH=%PATH%;..\..\..\libs\swig
cd ..
cd src
cd surfit
swig.exe -c++ -tcl -o surfit_wrap.cxx interface/surfit.i
