load libsurfit[info sharedlibextension]

clear_data
grid_get 50000 62000 50 52500 66000 50
grid_get 54000 60000 25 55000 62000 25
set tol 5e-5

set map_name map_heff
task_read heff.txt heff
completer_set 1 1.3

solve
grid_unload 
file_save map_heff.dat

