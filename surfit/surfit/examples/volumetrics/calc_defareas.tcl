#
load libsurfit[info sharedlibextension]

if { [file exists map_aoup.dat] == 0 } {
puts ""
puts "Please run map_aoup.tcl first!"
puts ""
return -1
}

if { [file exists map_aobt.dat] == 0 } {
puts ""
puts "Please run map_aobt.tcl first!"
puts ""
return -1
}

if { [file exists map_woc.dat] == 0 } {
puts ""
puts "Please run map_woc.tcl first!"
puts ""
return -1
}



clear_data


# processing "water with oil" area
funcs_load map_aoup.dat map_aoup
func_load map_woc.dat map_woc
func_minus_undef [funcs_last]
func_name $map_name
funcs_delall
func_to_defarea 0 10000
defarea_save water_and_oil.dat water_and_oil


# processing "oil" area
defarea_unload
func_unload
func_load map_woc.dat map_woc
funcs_load map_aobt.dat map_aobt
func_minus_undef [funcs_last]
func_name $map_name
func_to_defarea 0 10000
defarea_save oil.dat oil




