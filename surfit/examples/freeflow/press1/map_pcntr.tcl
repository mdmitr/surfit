#
load libfreeflow[info sharedlibextension]

clear_data
set tol 5e-7

set map_name map_pcntr
grid_get  -1000 1000 5 -1000 1000 5
curv_read press.xyz press
cntr_read pcntr.txt pcntr_center

isoline 250 press
lcm_simple 16.4 1 1e-6 
prod_contour pcntr_center

cmofs

grid_unload
file_save map_pcntr.dat