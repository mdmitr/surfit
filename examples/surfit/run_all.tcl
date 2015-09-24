load libsurfit[info sharedlibextension]

cd tests

# get list of all script files
set tcl_files [glob *.tcl]

foreach scr $tcl_files {
	if { [ source $scr ] == 0 } {
		return 0
	}
}

cd ..

cd realworld
source run_all.tcl
cd ..


