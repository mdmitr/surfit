set PATH=%PATH%;..\..\..\libs\swig
cd ..
cd src
cd surfit_io
swig.exe -c++ -tcl -o surfit_io_wrap.cxx interface/surfit_io.i
