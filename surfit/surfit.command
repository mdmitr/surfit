script_name=`echo $0`
path_to_script=${script_name%/surfit.command}
libpath=${path_to_script}/lib
binpath=${path_to_script}/bin
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$libpath
cd $path_to_script
bin/surfit
