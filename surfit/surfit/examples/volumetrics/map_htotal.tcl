load libsurfit[info sharedlibextension]

clear_data
grid_get 50000 62000 50 52500 66000 50
set tol 5e-6

set map_name map_htotal
task_read htotal.txt htotal
completer_set 1 3

solve
grid_unload 
file_save map_htotal.dat

