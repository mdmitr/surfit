#
load libfreeflow[info sharedlibextension]

clear_data
set tol 5e-7

set map_name map_piso
grid_get  -1000 1000 5 -1000 1000 5
curv_read press.xyz press 
curv_read piso.txt piso_center

isoline 250 press
lcm_simple 16.4 1 1e-6 
prod_isoline -0.00159 piso_center

cmofs

grid_unload
file_save map_piso.dat