#
load libfreeflow[info sharedlibextension]

clear_data
set tol 5e-7

set map_name map_wtask_ptask
grid_get  -1000 1000 5 -1000 1000 5
curv_read press.xyz press 
pnts_read debit_c.txt debit_c
pnts_read press_c.xyz press_c

curve 250 press
lcm_simple 16.4 1 1e-6 
points_add 1 press_c
prod_points debit_c

surfit

grid_unload
file_save map_wtask_ptask.dat