#
load libsurfit[info sharedlibextension]

if { [file exists map_T0.dat] == 0 } {
puts ""
puts "Please run map_T0.tcl first!"
puts ""
return -1
}

if { [file exists map_speed.dat] == 0 } {
puts ""
puts "Please run map_speed.tcl first!"
puts ""
return -1
}

clear_data

func_load map_T0.dat
grid_get_from_func
func_to_funcs
func_load map_speed.dat
func_project
func_mult [funcs_last]
task_read aoup.xyz
grid_unload
funcs_delall
file_save map_aoup.dat

