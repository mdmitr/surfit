#
load libsurfit[info sharedlibextension]

if { [file exists map_T0.dat] == 0 } {
puts ""
puts "Please run map_T0.tcl first!"
puts ""
return -1
}


clear_data

set tol 1e-6
func_load map_T0.dat
grid_get_from_func
set map_name map_speed
wtasks_delall
task_read aoup.xyz
task_update_by_func
task_to_tasks
task_read aoup.xyz
task_div [tasks_last]
func_unload
tasks_delall
completer_set 1 5

solve
func_decomp
func_save map_speed.dat
