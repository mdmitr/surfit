script_name=`echo $0`
path_to_script=${script_name%/run_examples.command}
libpath=${path_to_script}/lib
binpath=${path_to_script}/bin
examples=${path_to_script}/examples
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$libpath
cd $examples
../bin/surfit run_all.tcl
