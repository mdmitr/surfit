#
load libsurfit[info sharedlibextension]

if { [file exists map_aoup.dat] == 0 } {
puts ""
puts "Please run map_aoup.tcl first!"
puts ""
return -1
}

set tol 2.5e-7

set map_name map_aobt
func_load map_aoup.dat
grid_get_from_func
func_to_trend 1 5
task_read aobt.xyz
solve
grid_unload
file_save structures.dat
