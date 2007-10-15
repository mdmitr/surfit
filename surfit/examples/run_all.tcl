#
# surfit
#
cd surfit
if { [source "run_all.tcl"] == 0 } {
	return 0
}
cd ..

#
# freeflow
#
cd freeflow
if { [source "run_all.tcl"] == 0 } {
	return 0
}
cd ..

#
# globe
#
cd globe
if { [source "run_all.tcl"] == 0 } {
	return 0
}
cd ..
           
