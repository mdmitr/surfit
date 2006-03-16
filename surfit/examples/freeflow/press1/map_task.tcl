#
load libfreeflow[info sharedlibextension]

clear_data
set tol 5e-7

set map_name map_task
grid_get  -1000 1000 5 -1000 1000 5

curv_read press.xyz press 
pnts_read press_c.xyz press_c

points
isoline 250 press
lcm_simple 16.4 1 1e-6 

cmofs

grid_unload
file_save map_task.dat