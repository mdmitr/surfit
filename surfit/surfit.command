script_name=`echo $0`
path_to_script=${script_name%/surfit.command}
#echo $path_to_script
libpath=${path_to_script}/lib
binpath=${path_to_script}/bin
#iecho $libpath
#echo $binpath
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$libpath
cd $binpath
./surfit
