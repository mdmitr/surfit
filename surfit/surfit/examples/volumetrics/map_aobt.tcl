#
load libsurfit[info sharedlibextension]

clear_data
set map_name map_aobt

if { [file exists map_aoup.dat] == 0 } {
puts ""
puts "Please run map_aoup.tcl first!"
puts ""
return -1
}

if { [file exists map_htotal.dat] == 0 } {
puts ""
puts "Please run map_htotal.tcl first!"
puts ""
return -1
}

func_load map_aoup.dat
funcs_load map_htotal.dat

func_plus [funcs_last]
funcs_delall
func_name map_aobt
file_save map_aobt.dat
