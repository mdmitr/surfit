load libsurfit[info sharedlibextension]

clear_data
grid_get 50000 62000 50 52500 66000 50
#grid_get 50000 62000 800 52500 66000 1600
set tol 5e-6

set map_name map_woc
areas_read cntrs/owc_area.xyz area2187 2187

set priority 1

fill_with_set

solve
grid_unload 
file_save map_woc.dat

