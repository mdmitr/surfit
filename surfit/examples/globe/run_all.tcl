load libglobe[info sharedlibextension]

if { [file exists N00E006.hgt.zip] == 0 } {
	puts "Can't find file N00E006.hgt.zip! Download it first before running libglobe examples!"
	return 0
}

#
# dem
#
if { [source "dem.tcl"] == 0 } {
	return 0
}

if { [source "dem_add.tcl"] == 0 } {
	return 0
}
