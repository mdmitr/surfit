#
load libsurfit[info sharedlibextension]

clear_data 

set tol 2.5e-7
set map_name map_T0
task_read 2d_seism.xyz 2d_seism
grid_get_for_task 1024 1024
task_to_wtasks 0.1
task_read 3d_seism.xyz 3d_seism
task_to_wtasks 10
completer_set 1 5

solve
func_decomp
func_decomp
func_save map_T0.dat
