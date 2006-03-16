#
load libfreeflow[info sharedlibextension]

clear_data
set tol 5e-7

set map_name map_ptask
grid_get  -1000 1000 5 -1000 1000 5
curv_read press.xyz press
pnts_read debit_c.txt debit_c

isoline 250 press
lcm_simple 16.4 1 1e-6 
prod_points debit_c
cmofs

grid_unload
file_save map_ptask.dat