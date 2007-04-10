load libfreeflow[info sharedlibextension]

#
# press1
#
cd "press1"
if { [source "press1.tcl"] == 0 } {
	return 0
}
cd ..

#
# press2
#
cd "press2"
if { [source "press2.tcl"] == 0 } {
	return 0
}
cd ..



